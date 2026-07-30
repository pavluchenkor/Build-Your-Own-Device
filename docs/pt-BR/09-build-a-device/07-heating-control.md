---
title: "Controle de aquecimento do gabinete: manutenção de temperatura e ventilador"
description: "Lógica do gabinete aquecido em idryer-core: manutenção de temperatura-alvo por histerese, proteção do aquecedor por termistor, ventilador e comandos do portal."
---

# Controle de aquecimento

Nesta página você conecta sensores, configurações e a parte de potência em uma lógica funcional. O dispositivo mantém a temperatura especificada no gabinete, protege o aquecedor de superaquecimento e responde aos comandos do portal.

A lógica é executada em `loop()` perto do atendimento de rede. Todos os temporizadores e limites são não-bloqueantes, sem `delay()`.

## O que deve acontecer

O comportamento do gabinete consiste em três regras simples:

1. **Manutenção de temperatura.** Se o ar no gabinete está mais frio que a meta na quantidade de histerese — ligar aquecimento. Quando atingiu a meta — desligar.
2. **Proteção do aquecedor.** O termistor controla o próprio aquecedor. Se ele superaqueceu acima do permitido — o aquecimento desliga independentemente da temperatura do ar.
3. **Ventilador.** Liga para dispersar o calor pelo gabinete e desliga quando o aquecimento não é necessário.

## Chaves de aquecedor e ventilador

O controlador liga o aquecedor e ventilador através de uma chave: módulo MOSFET (versão A) ou SSR (versão B) — veja [Esquema de conexão](03-wiring.md). Do ponto de vista do código, é apenas um pino GPIO: `HIGH` — ligado, `LOW` — desligado.

Descrever tal chave com uma pequena estrutura e ter duas instâncias — para o aquecedor e ventilador. Adicione isto a `src/main.cpp` (antes de `setup()`):

```cpp
struct GpioOutput {
    int pin;
    void begin() { pinMode(pin, OUTPUT); digitalWrite(pin, LOW); }
    void on()    { digitalWrite(pin, HIGH); }
    void off()   { digitalWrite(pin, LOW); }
};

static GpioOutput myHeater{4};   // GPIO4 — controle do aquecedor
static GpioOutput myFan{5};      // GPIO5 — controle do ventilador
```

Os números de pino são os mesmos de [Esquema de conexão](03-wiring.md). Em `setup()` ambas as chaves devem ser inicializadas: `myHeater.begin();` e `myFan.begin();`.

!!! warning "Estado seguro no início"
    `begin()` imediatamente define `LOW` — aquecedor e ventilador desligados, até a lógica decidir o contrário. Isto é importante: ao ligar a energia, o aquecedor não deve ficar aceso acidentalmente.

## Manutenção de temperatura por histerese

Para um gabinete em `40–45 °C`, histerese simples é suficiente: o aquecimento liga e desliga em torno da meta. É mais simples que PID completo e para manutenção suave de calor funciona de forma confiável.

A temperatura-alvo e histerese são tiradas do menu (`menu.target_temp`, `menu.hysteresis`) — ele já está conectado no [capítulo 6](06-menu.md). Adicione uma flag de estado e função de decisão:

```cpp
static bool s_heating = false;

static void controlLoop() {
    float air    = s_link.telemetry.airTempC[0];     // SHT31
    float target = (float)menu.target_temp;          // do menu
    float hyst   = (float)menu.hysteresis;           // do menu

    if (air < target - hyst) {
        s_heating = true;     // esfriou — aqueça
    } else if (air >= target) {
        s_heating = false;    // atingiu meta — parar
    }
}
```

A temperatura-alvo e histerese são tiradas do [menu](06-menu.md) — o usuário as muda do portal.

## Proteção do aquecedor por termistor

O ar aquece lentamente, mas a espiral do aquecedor — rapidamente. Sem controle separado, o aquecedor terá tempo de superaquecer antes de o ar atingir a meta. Portanto, o termistor do aquecedor define um limite rígido.

```cpp
static const float HEATER_MAX_C = 80.0f;   // limite de temperatura do aquecedor

static void applyHeater() {
    float heaterTemp = s_link.telemetry.heaterTempC[0];   // termistor

    bool allow = s_heating && heaterTemp < HEATER_MAX_C;

    if (allow) {
        myHeater.on();
        s_link.telemetry.heaterPower01[0] = 1.0f;   // refletir na telemetria
    } else {
        myHeater.off();
        s_link.telemetry.heaterPower01[0] = 0.0f;
    }
}
```

!!! warning "Limite do aquecedor — é proteção, não configuração de clima"
    `HEATER_MAX_C` limita a temperatura do próprio aquecedor, não do ar. O valor depende do design do aquecedor e dos materiais do gabinete. Escolha com margem abaixo da temperatura em que peças plásticas deformam — veja [Materiais termoresistentes](../07-3d-printing/04-heat-resistant-materials.md).

Para aquecimento mais suave em vez de ligar/desligar "tudo ou nada", você pode controlar potência via PWM, e o campo `heaterPower01[0]` aceita valores de `0.0` para `1.0`. Para um gabinete com manutenção suave de calor, a lógica simples acima geralmente é suficiente.

## Ventilador

O ventilador dispersa o calor pelo gabinete. Lógica mais simples — ligá-lo junto com o aquecimento:

```cpp
static void applyFan() {
    bool fanOn = s_heating;          // girar enquanto aquece
    if (fanOn) myFan.on(); else myFan.off();
    s_link.telemetry.fanOn[0] = fanOn;   // refletir na telemetria
}
```

No controlador em série, o ventilador é controlado pela temperatura com limites separados de ligação e desligação (por exemplo, liga a `55 °C`, desliga a `35 °C`), para que ele não oscile no limite. Para um gabinete você pode aplicar a mesma abordagem, vinculando os limites a parâmetros do menu.

## Montando em loop()

```cpp
void loop() {
    s_link.loop();          // rede e autopublicação

    // sensores (veja passo "Sensores"):
    s_climate.tick(millis());
    SensorReading c = s_climate.get();
    if (c.ok) {
        s_link.telemetry.airTempC[0]       = c.temperature;
        s_link.telemetry.airHumidityPct[0] = c.humidity;
    }
    s_link.telemetry.heaterTempC[0] = readHeaterTempC();

    controlLoop();   // decidir se aquece ou não
    applyHeater();   // aplicar ao aquecedor + proteção
    applyFan();      // aplicar ao ventilador
}
```

Os campos de telemetria (`heaterPower01`, `fanOn`) a fachada publica automaticamente — no portal você vê se o dispositivo está aquecendo agora e se o ventilador está funcionando.

## Comandos do portal

O portal envia iniciar e parar a manutenção de calor como comandos. O handler é registrado pelo método `s_link.onCommand(nome, callback)` — **depois** de `s_link.begin()`. Comandos de ação chegam com nome `invoke` e campo `action` (função do menu, por exemplo `storage.start` / `storage.stop`).

Para análise JSON, você precisa dos cabeçalhos `<ArduinoJson.h>` e `<string.h>` (para `strcmp`) — adicione-os aos outros `#include` no início do arquivo. O próprio handler é definido em `setup()`:

```cpp
s_link.onCommand("invoke", [](JsonObjectConst data) {
    const char* action = data["action"] | "";
    if (strcmp(action, "storage.start") == 0) {
        s_heating = true;
        s_link.status.mode[0]        = iDryer::UnitMode::Storage;
        s_link.status.targetTempC[0] = (float)menu.target_temp;
        s_link.publishStatusNow();
    } else if (strcmp(action, "storage.stop") == 0) {
        s_heating = false;
        myHeater.off();
        s_link.status.mode[0] = iDryer::UnitMode::Idle;
        s_link.publishStatusNow();
    }
});
```

- `storage.start` / `storage.stop` — as mesmas funções que você definiu no [menu](06-menu.md); o portal desenha botões a partir delas.
- `iDryer::UnitMode::Storage` — modo de manutenção suave de calor. Este é o modo principal do gabinete.
- `s_link.status.mode[0]` e `targetTempC[0]` mostram no portal o estado atual da câmera.
- Chame `publishStatusNow()` depois de cada mudança de status para que o portal veja imediatamente, não esperando pelo temporizador.

!!! warning "Sem delay() no handler"
    O handler `onCommand` é chamado de um callback de rede. Qualquer bloqueio dentro dele quebra a sessão MQTT. Mude flags e status, mas faça o trabalho real em `loop()`.

## Completo `src/main.cpp` após este capítulo

Este é o arquivo final e completo do dispositivo. Novas linhas em relação ao capítulo anterior são marcadas `// ← capítulo 7`. Este mesmo arquivo está como exemplo pronto na pasta `example/09-cabinet/` do repositório e é compilado com `pio run -e cabinet`.

??? note "O que foi — `src/main.cpp` após o capítulo 6"

    ```cpp
    #include <iDryer.h>
    #include <Wire.h>
    #include <math.h>
    #include "Sht31ClimateSensor.h"
    #include <menu_state.h>

    static const iDryer::Config CFG = {
        .deviceType        = iDryer::DeviceType::Dryer,
        .unitsCount        = 1,
        .hasHeater         = true,
        .hasFan            = true,
        .hasAirTemp        = true,
        .hasAirHumidity    = true,
        .hasHeaterTemp     = true,
        .telemetryPeriodMs = 5000,
        .statusPeriodMs    = 10000,
        .hardwareVersion   = "1.0",
        .firmwareVersion   = "0.1.0",
        .model             = "DIY Storage Cabinet",
    };
    static iDryer::Link s_link(CFG);

    static Sht31ClimateSensor s_climate(&Wire);
    static bool               s_climateOk = false;

    static const int   THERM_PIN  = 2;
    static const float SERIES_R   = 4700.0f;
    static const float NOMINAL_R  = 100000.0f;
    static const float NOMINAL_T  = 25.0f;
    static const float BETA       = 3950.0f;

    static float readHeaterTempC() {
        int   raw = analogRead(THERM_PIN);
        float v   = (float)raw / 4095.0f;
        float r   = SERIES_R * (1.0f - v) / v;
        float tK  = 1.0f / (1.0f / (NOMINAL_T + 273.15f) + logf(r / NOMINAL_R) / BETA);
        return tK - 273.15f;
    }

    void setup() {
        Serial.begin(115200);
        Wire.begin(8, 9);
        s_climateOk = s_climate.begin();
        menu.initDefaults();
        s_link.begin();
    }

    void loop() {
        s_link.loop();

        if (s_climateOk) {
            s_climate.tick(millis());
            SensorReading r = s_climate.get();
            if (r.ok) {
                s_link.telemetry.airTempC[0]       = r.temperature;
                s_link.telemetry.airHumidityPct[0] = r.humidity;
            }
        }
        s_link.telemetry.heaterTempC[0] = readHeaterTempC();
    }
    ```

```cpp
#include <Wire.h>
#include <ArduinoJson.h>          // ← capítulo 7 (onCommand: JsonObjectConst)
#include <string.h>              // ← capítulo 7 (strcmp)
#include <math.h>
#include <iDryer.h>
#include "Sht31ClimateSensor.h"
#include <menu_state.h>

static const iDryer::Config CFG = {
    .deviceType        = iDryer::DeviceType::Dryer,
    .unitsCount        = 1,
    .hasHeater         = true,
    .hasFan            = true,
    .hasAirTemp        = true,
    .hasAirHumidity    = true,
    .hasHeaterTemp     = true,
    .telemetryPeriodMs = 5000,
    .statusPeriodMs    = 10000,
    .hardwareVersion   = "1.0",
    .firmwareVersion   = "0.1.0",
    .model             = "DIY Storage Cabinet",
};
static iDryer::Link s_link(CFG);

static Sht31ClimateSensor s_climate(&Wire);
static bool               s_climateOk = false;

static const int   THERM_PIN  = 2;
static const float SERIES_R   = 4700.0f;
static const float NOMINAL_R  = 100000.0f;
static const float NOMINAL_T  = 25.0f;
static const float BETA       = 3950.0f;

static float readHeaterTempC() {
    int   raw = analogRead(THERM_PIN);
    float v   = (float)raw / 4095.0f;
    float r   = SERIES_R * (1.0f - v) / v;
    float tK  = 1.0f / (1.0f / (NOMINAL_T + 273.15f) + logf(r / NOMINAL_R) / BETA);
    return tK - 273.15f;
}

// ← capítulo 7: chaves do aquecedor e ventilador
struct GpioOutput {
    int pin;
    void begin() { pinMode(pin, OUTPUT); digitalWrite(pin, LOW); }
    void on()    { digitalWrite(pin, HIGH); }
    void off()   { digitalWrite(pin, LOW); }
};
static GpioOutput myHeater{4};
static GpioOutput myFan{5};

// ← capítulo 7: lógica de manutenção de temperatura
static bool        s_heating    = false;
static const float HEATER_MAX_C = 80.0f;

static void controlLoop() {
    float air    = s_link.telemetry.airTempC[0];
    float target = (float)menu.target_temp;
    float hyst   = (float)menu.hysteresis;
    if (air < target - hyst)  s_heating = true;
    else if (air >= target)   s_heating = false;
}

static void applyHeater() {
    float heaterTemp = s_link.telemetry.heaterTempC[0];
    bool  allow = s_heating && heaterTemp < HEATER_MAX_C;
    if (allow) myHeater.on(); else myHeater.off();
    s_link.telemetry.heaterPower01[0] = allow ? 1.0f : 0.0f;
}

static void applyFan() {
    if (s_heating) myFan.on(); else myFan.off();
    s_link.telemetry.fanOn[0] = s_heating;
}

void setup() {
    Serial.begin(115200);
    Wire.begin(8, 9);
    s_climateOk = s_climate.begin();
    myHeater.begin();              // ← capítulo 7
    myFan.begin();                 // ← capítulo 7
    menu.initDefaults();
    s_link.begin();

    s_link.onCommand("invoke", [](JsonObjectConst data) {   // ← capítulo 7
        const char* action = data["action"] | "";
        if (strcmp(action, "storage.start") == 0) {
            s_heating = true;
            s_link.status.mode[0]        = iDryer::UnitMode::Storage;
            s_link.status.targetTempC[0] = (float)menu.target_temp;
            s_link.publishStatusNow();
        } else if (strcmp(action, "storage.stop") == 0) {
            s_heating = false;
            myHeater.off();
            s_link.status.mode[0] = iDryer::UnitMode::Idle;
            s_link.publishStatusNow();
        }
    });
}

void loop() {
    s_link.loop();

    if (s_climateOk) {
        s_climate.tick(millis());
        SensorReading r = s_climate.get();
        if (r.ok) {
            s_link.telemetry.airTempC[0]       = r.temperature;
            s_link.telemetry.airHumidityPct[0] = r.humidity;
        }
    }
    s_link.telemetry.heaterTempC[0] = readHeaterTempC();

    controlLoop();   // ← capítulo 7
    applyHeater();   // ← capítulo 7
    applyFan();      // ← capítulo 7
}
```

## Verificação de resultado

Após este passo:

- iniciar do portal coloca o gabinete no modo Storage, o dispositivo começa a aquecer;
- a temperatura do ar sobe até a meta e é mantida dentro da histerese;
- o aquecedor não ultrapassa `HEATER_MAX_C`;
- ventilador e potência de aquecimento são visíveis na telemetria;
- parar do portal desliga o aquecimento e coloca em Idle.

## O que vem a seguir

A lógica está pronta. Falta montar o dispositivo no gabinete e verificar sob energia — [Montagem e verificação](08-assembly-and-check.md).
