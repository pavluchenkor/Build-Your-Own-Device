---
title: "Controlo de aquecimento do armário: manutenção de temperatura e ventoinha"
description: "Lógica de armário aquecido em idryer-core: manutenção de temperatura-alvo por histerese, protecção do aquecedor por termistor, ventoinha e comandos do portal."
---

# Controlo de aquecimento

Nesta página você liga sensores, configurações e secção de potência em lógica funcional. O dispositivo mantém a temperatura estabelecida no armário, protege o aquecedor contra sobreaquecimento e responde a comandos do portal.

A lógica é executada em `loop()` junto à manutenção de rede. Todos os temporizadores e limiares são sem bloqueio, sem `delay()`.

## O que deve acontecer

O comportamento do armário é composto por três regras simples:

1. **Manutenção de temperatura.** Se o ar no armário é mais frio que o alvo pela quantidade de histerese - ligar aquecimento. Quando chegou ao alvo - desligar.
2. **Protecção do aquecedor.** O termistor controla o próprio aquecedor. Se sobreaqueceu acima do permitido - o aquecimento é desligado independentemente da temperatura do ar.
3. **Ventoinha.** Ligada para distribuir calor pelo armário, e desligada quando o aquecimento não é necessário.

## Chaves do aquecedor e ventoinha

O aquecedor e ventoinha o controlador liga via chave: módulo MOSFET (versão A) ou SSR (versão B) - veja [Esquema de ligação](03-wiring.md). Do ponto de vista do código é apenas um pino GPIO: `HIGH` - ligado, `LOW` - desligado.

Descreveremos tal chave com uma pequena estrutura e criaremos dois casos - para aquecedor e ventoinha. Adicione isto a `src/main.cpp` (antes de `setup()`):

```cpp
struct GpioOutput {
    int pin;
    void begin() { pinMode(pin, OUTPUT); digitalWrite(pin, LOW); }
    void on()    { digitalWrite(pin, HIGH); }
    void off()   { digitalWrite(pin, LOW); }
};

static GpioOutput myHeater{4};   // GPIO4 — controlo do aquecedor
static GpioOutput myFan{5};      // GPIO5 — controlo da ventoinha
```

Os números de pinos são os mesmos de [Esquema de ligação](03-wiring.md). Em `setup()` ambas as chaves devem ser inicializadas: `myHeater.begin();` e `myFan.begin();`.

!!! warning "Estado seguro no arranque"
    `begin()` imediatamente coloca `LOW` - aquecedor e ventoinha estão desligados até a lógica decidir o contrário. Isto é importante: ao ligar a alimentação o aquecedor não deve acabar acidentalmente ligado.

## Manutenção de temperatura por histerese

Para armário a `40-45 °C` é suficiente histerese simples: aquecimento liga e desliga em torno do alvo. Isto é mais simples que PID completo e para manutenção suave de calor funciona de forma fiável.

A temperatura-alvo e histerese pegam-se do menu (`menu.target_temp`, `menu.hysteresis`) - já está conectado no [capítulo 6](06-menu.md). Adicione uma bandeira de estado e função de decisão:

```cpp
static bool s_heating = false;

static void controlLoop() {
    float air    = s_link.telemetry.airTempC[0];     // SHT31
    float target = (float)menu.target_temp;          // do menu
    float hyst   = (float)menu.hysteresis;           // do menu

    if (air < target - hyst) {
        s_heating = true;     // arrefecemos — aquecemos
    } else if (air >= target) {
        s_heating = false;    // chegámos ao alvo — parar
    }
}
```

A temperatura-alvo e histerese são pegadas do [menu](06-menu.md) - o utilizador muda-as do portal.

## Protecção do aquecedor por termistor

O ar aquece lentamente, mas a espiral do aquecedor aquece rapidamente. Sem controlo separado o aquecedor terá tempo para sobrequecer antes que o ar chegue ao alvo. Portanto o termistor do aquecedor estabelece um limite duro.

```cpp
static const float HEATER_MAX_C = 80.0f;   // limite de temperatura do aquecedor

static void applyHeater() {
    float heaterTemp = s_link.telemetry.heaterTempC[0];   // termistor

    bool allow = s_heating && heaterTemp < HEATER_MAX_C;

    if (allow) {
        myHeater.on();
        s_link.telemetry.heaterPower01[0] = 1.0f;   // reflectir em telemetria
    } else {
        myHeater.off();
        s_link.telemetry.heaterPower01[0] = 0.0f;
    }
}
```

!!! warning "O limite do aquecedor é protecção, não configuração climática"
    `HEATER_MAX_C` limita a temperatura do próprio aquecedor, não do ar. O valor depende da construção do aquecedor e materiais da carcaça. Escolha-o com margem abaixo da temperatura em que deformam os detalhes impressos - veja [Materiais à prova de calor](../07-3d-printing/04-heat-resistant-materials.md).

Para aquecimento mais suave em vez de ligar/desligar "tudo ou nada" pode controlar potência através de PWM e o campo `heaterPower01[0]` aceita valores de `0,0` a `1,0`. Para armário com manutenção suave de calor a lógica simples acima normalmente é suficiente.

## Ventoinha

A ventoinha distribui calor pelo armário. A lógica mais simples - ligá-la junto com o aquecimento:

```cpp
static void applyFan() {
    bool fanOn = s_heating;          // girar enquanto aquecemos
    if (fanOn) myFan.on(); else myFan.off();
    s_link.telemetry.fanOn[0] = fanOn;   // reflectir em telemetria
}
```

No controlador em série a ventoinha é controlada por temperatura com limiares separados de ligação e desligação (por exemplo, ligação a `55 °C`, desligação a `35 °C`), para não se mexer na borda. Para armário pode-se aplicar a mesma abordagem, ligando os limiares aos parâmetros do menu.

## Montagem em loop()

```cpp
void loop() {
    s_link.loop();          // rede e autopublicação

    // sensores (veja passo «Sensores»):
    s_climate.tick(millis());
    SensorReading c = s_climate.get();
    if (c.ok) {
        s_link.telemetry.airTempC[0]       = c.temperature;
        s_link.telemetry.airHumidityPct[0] = c.humidity;
    }
    s_link.telemetry.heaterTempC[0] = readHeaterTempC();

    controlLoop();   // decidimos, aquecer ou não
    applyHeater();   // aplicamos ao aquecedor + protecção
    applyFan();      // aplicamos à ventoinha
}
```

Os campos de telemetria (`heaterPower01`, `fanOn`) são publicados pela fachada - no portal vê-se se o dispositivo está a aquecer neste momento e se a ventoinha funciona.

## Comandos do portal

Arranque e paragem de manutenção de calor o portal envia como comandos. O manipulador é registado pelo método `s_link.onCommand(nome, colbak)` - **depois** de `s_link.begin()`. Comandos de acção chegam com nome `invoke` e campo `action` (papel do menu, por exemplo `storage.start` / `storage.stop`).

Para análise JSON são necessários cabehos `<ArduinoJson.h>` e `<string.h>` (para `strcmp`) - adicione-os ao resto de `#include` no início do ficheiro. O próprio manipulador é colocado em `setup()`:

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

- `storage.start` / `storage.stop` — os mesmos papéis que estabeleceu no [menu](06-menu.md); por eles o portal desenha botões.
- `iDryer::UnitMode::Storage` — modo de manutenção suave de calor. Este é o modo principal do armário.
- `s_link.status.mode[0]` e `targetTempC[0]` mostram no portal o estado actual da câmara.
- `publishStatusNow()` chame após cada mudança de estatuto para que o portal veja-o imediatamente, não esperando pelo temporizador.

!!! warning "Sem delay() no manipulador"
    O manipulador `onCommand` é chamado de um colbak de rede. Qualquer bloqueio dentro dele quebra a sessão MQTT. Mude as bandeiras e estatuto, e faça o trabalho em `loop()`.

## Completo `src/main.cpp` após este capítulo

Este é o ficheiro final e completo do dispositivo. Novas linhas relativas ao capítulo anterior são marcadas `// ← capítulo 7`. Este mesmo ficheiro está como exemplo pronto na pasta `example/09-cabinet/` do repositório e é compilado com `pio run -e cabinet`.

??? nota «O que era - `src/main.cpp` após capítulo 6»

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

// ← capítulo 7: chaves do aquecedor e ventoinha
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

- arranque do portal transiciona o armário para modo Storage, o dispositivo começa a aquecer;
- a temperatura do ar aumenta para o alvo e é mantida dentro da histerese;
- o aquecedor não sai acima de `HEATER_MAX_C`;
- ventoinha e potência de aquecimento são vistos em telemetria;
- paragem do portal desliga aquecimento e transiciona para Idle.

## O que vem a seguir

A lógica está pronta. Resta montar o dispositivo na carcaça e verificar sob funcionamento - [Montagem e verificação](08-assembly-and-check.md).
