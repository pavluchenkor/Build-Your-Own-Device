---
title: "Controle de aquecimento do gabinete: manutencao de temperatura e ventilador"
description: "Logica do gabinete aquecido em idryer-core: manutencao de temperatura-alvo por histerese, protecao do aquecedor por termistor, ventilador e comandos do portal."
---

# Controle de aquecimento

Nesta pagina voce conecta sensores, configuracoes e a parte de potencia em uma logica funcional. O dispositivo mantem a temperatura especificada no gabinete, protege o aquecedor de superaquecimento e responde aos comandos do portal.

A logica e executada em `loop()` perto do atendimento de rede. Todos os temporizadores e limites sao nao-bloqueantes, sem `delay()`.

## O que deve acontecer

O comportamento do gabinete consiste em tres regras simples:

1. **Manutencao de temperatura.** Se o ar no gabinete esta mais frio que a meta na quantidade de histerese — ligar aquecimento. Quando atingiu a meta — desligar.
2. **Protecao do aquecedor.** O termistor controla o proprio aquecedor. Se ele superaqueceu acima do permitido — o aquecimento desliga independentemente da temperatura do ar.
3. **Ventilador.** Liga para dispersar o calor pelo gabinete e desliga quando o aquecimento nao e necessario.

## Chaves de aquecedor e ventilador

O controlador liga o aquecedor e ventilador atraves de uma chave: modulo MOSFET (versao A) ou SSR (versao B) — veja [Esquema de conexao](03-wiring.md). Do ponto de vista do codigo, e apenas um pino GPIO: `HIGH` — ligado, `LOW` — desligado.

Descrever tal chave com uma pequena estrutura e ter duas instancias — para o aquecedor e ventilador. Adicione isto a `src/main.cpp` (antes de `setup()`):

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

Os numeros de pino sao os mesmos de [Esquema de conexao](03-wiring.md). Em `setup()` ambas chaves devem ser inicializadas: `myHeater.begin();` e `myFan.begin();`.

!!! warning "Estado seguro no inicio"
    `begin()` imediatamente define `LOW` — aquecedor e ventilador desligados, ate a logica decidir o contrario. Isto e importante: ao ligar a energia, o aquecedor nao deve ficar aceso acidentalmente.

## Manutencao de temperatura por histerese

Para um gabinete em `40–45 °C`, histerese simples e suficiente: o aquecimento liga e desliga em torno da meta. E mais simples que PID completo e para manutencao suave de calor funciona confiavel.

A temperatura-alvo e histerese tiram do menu (`menu.target_temp`, `menu.hysteresis`) — ele ja esta conectado no [capitulo 6](06-menu.md). Adicione uma flag de estado e funcao de decisao:

```cpp
static bool s_heating = false;

static void controlLoop() {
    float air    = s_link.telemetry.airTempC[0];     // SHT31
    float target = (float)menu.target_temp;          // do menu
    float hyst   = (float)menu.hysteresis;           // do menu

    if (air < target - hyst) {
        s_heating = true;     // esfriou — aqueca
    } else if (air >= target) {
        s_heating = false;    // atingiu meta — parar
    }
}
```

A temperatura-alvo e histerese sao tiradas do [menu](06-menu.md) — o usuario as muda do portal.

## Protecao do aquecedor por termistor

O ar aquece lentamente, mas a espiral do aquecedor — rapidamente. Sem controle separado, o aquecedor tera tempo de superaquecer antes de o ar atingir a meta. Portanto, o termistor do aquecedor define um limite rigido.

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

!!! warning "Limite do aquecedor — e protecao, nao configuracao de clima"
    `HEATER_MAX_C` limita a temperatura do proprio aquecedor, nao do ar. O valor depende do design do aquecedor e dos materiais do gabinete. Escolha com margem abaixo da temperatura em que pecas plasticas deformam — veja [Materiais termoresistentes](../07-3d-printing/04-heat-resistant-materials.md).

Para aquecimento mais suave em vez de ligar/desligar "tudo ou nada", voce pode controlar potencia via PWM, e o campo `heaterPower01[0]` aceita valores de `0.0` para `1.0`. Para um gabinete com manutencao suave de calor, a logica simples acima geralmente e suficiente.

## Ventilador

O ventilador dispersa o calor pelo gabinete. Logica mais simples — liga-lo junto com o aquecimento:

```cpp
static void applyFan() {
    bool fanOn = s_heating;          // girar enquanto aquece
    if (fanOn) myFan.on(); else myFan.off();
    s_link.telemetry.fanOn[0] = fanOn;   // refletir na telemetria
}
```

No controlador em serie, o ventilador e controlado pela temperatura com limites separados de ligacao e desligacao (por exemplo, ligue a `55 °C`, desliga a `35 °C`), para que ele nao osciler no limite. Para um gabinete voce pode aplicar a mesma abordagem, vinculando os limites a parametros do menu.

## Montando em loop()

```cpp
void loop() {
    s_link.loop();          // rede e autopublicacao

    // sensores (veja passo "Sensores"):
    s_climate.tick(millis());
    SensorReading c = s_climate.get();
    if (c.ok) {
        s_link.telemetry.airTempC[0]       = c.temperature;
        s_link.telemetry.airHumidityPct[0] = c.humidity;
    }
    s_link.telemetry.heaterTempC[0] = readHeaterTempC();

    controlLoop();   // decidir se aquece ou nao
    applyHeater();   // aplicar ao aquecedor + protecao
    applyFan();      // aplicar ao ventilador
}
```

Os campos de telemetria (`heaterPower01`, `fanOn`) a fachada publica automaticamente — no portal voce ve se o dispositivo esta aquecendo agora e se o ventilador esta funcionando.

## Comandos do portal

O portal envia iniciar e parar a manutencao de calor como comandos. O handler e registrado pelo metodo `s_link.onCommand(nome, callback)` — **depois** de `s_link.begin()`. Comandos de acao chegam com nome `invoke` e campo `action` (funcao do menu, por exemplo `storage.start` / `storage.stop`).

Para analise JSON, voce precisa dos cabecalhos `<ArduinoJson.h>` e `<string.h>` (para `strcmp`) — adicione-os aos outros `#include` no inicio do arquivo. O proprio handler e definido em `setup()`:

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

- `storage.start` / `storage.stop` — as mesmas funcoes que voce definiu no [menu](06-menu.md); o portal desenha botoes delas.
- `iDryer::UnitMode::Storage` — modo de manutencao suave de calor. Este e o modo principal do gabinete.
- `s_link.status.mode[0]` e `targetTempC[0]` mostram no portal o estado atual da camera.
- Chame `publishStatusNow()` depois de cada mudanca de status para que o portal veja imediatamente, nao esperando pelo temporizador.

!!! warning "Sem delay() no handler"
    O handler `onCommand` e chamado de um callback de rede. Qualquer bloqueio dentro dele quebra a sessao MQTT. Mude flags e status, mas faca o trabalho real em `loop()`.

## O que vem a seguir

A logica esta pronta. Falta montar o dispositivo no gabinete e verificar sob energia — [Montagem e verificacao](08-assembly-and-check.md).
