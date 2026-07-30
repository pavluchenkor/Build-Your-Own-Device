---
title: "Filtro inteligente: sensor VOC e telemetria"
description: "Leitura SGP40 por I2C e publicação do campo próprio vocIndex na telemetria do iDryer através do callback onTelemetryPublish."
---

# Sensor e telemetria

Neste capítulo, o filtro começa a medir o ar e enviar dados para a nuvem. O truque-chave é **seu próprio campo na telemetria**: o dicionário do ecossistema não sabe nada sobre VOC, mas o núcleo permite adicionar qualquer campo à telemetria.

## 1. Biblioteca do sensor

Em `platformio.ini`, adicione a `lib_deps`:

```ini
    adafruit/Adafruit SGP40 Sensor
```

## 2. Leitura do SGP40

Em `src/main.cpp` (pinos — do [esquema](03-wiring.md)):

```cpp
#include <Wire.h>
#include <Adafruit_SGP40.h>

static Adafruit_SGP40 s_sgp;
static int32_t g_vocIndex = -1;   // -1 = sem dados ainda

static void initVocSensor() {
    Wire.begin(/*SDA=*/8, /*SCL=*/9);
    if (!s_sgp.begin()) {
        Serial.println("[VOC] SGP40 not found, check wiring");
    }
}

static void readVocSensor() {
    // measureVocIndex() faz sua própria compensação interna do sensor.
    // Índice: ~100 = ar normal, maior = mais sujo (máx 500).
    g_vocIndex = s_sgp.measureVocIndex();
}
```

Adicione a chamada de `initVocSensor()` em `setup()` após `s_link.begin()`, e `readVocSensor()` em `loop()` uma vez por segundo (com timer millis, não `delay`!):

```cpp
static uint32_t s_lastReadMs = 0;

void loop() {
    s_link.loop();

    uint32_t now = millis();
    if (now - s_lastReadMs >= 1000) {
        s_lastReadMs = now;
        readVocSensor();
    }
}
```

!!! warning "Sem delay() no loop"
    `s_link.loop()` deve ser chamado constantemente — nele residem Wi-Fi, MQTT e comandos do portal. `delay(1000)` vai congelar tudo isso. Use apenas timers millis.

## 3. Seu próprio campo na telemetria

A cada `telemetryPeriodMs`, o núcleo coleta automaticamente uma mensagem JSON de telemetria e a envia para a nuvem. Para nosso dispositivo (uma unidade, com apenas ventilador do vocabulário), o núcleo coleta uma mensagem assim:

```json
{
  "units": [ { "unitId": "U1", "fanStatus": false } ],
  "rssi": -52,
  "uptime": 120
}
```

Vamos entender a estrutura:

- `units` — matriz de **unidades** (câmaras) do dispositivo. O secador iDryer em série pode ter até quatro câmaras independentes, então a telemetria é sempre uma matriz, mesmo com uma única câmara;
- `units[0]` — primeira (e nossa única) unidade: especificamos `unitsCount = 1` em `Config`;
- `fanStatus` — campo do vocabulário, apareceu por causa de `hasFan = true`;
- `rssi`, `uptime` — nível de Wi-Fi e tempo de funcionamento, o núcleo adiciona sempre.

Nesta mensagem não há nada sobre VOC — o núcleo não sabe sobre nosso sensor. Mas logo antes do envio, o núcleo oferece ao seu código a oportunidade de adicionar seus próprios campos à mensagem. Para isto, você registra um **callback** (callback, "chamada de retorno") — uma função que você dá ao núcleo, e o núcleo a chama em cada publicação, passando o JSON montado dentro (o argumento `doc` — é ele mesmo).

Em `setup()`:

```cpp
s_link.onTelemetryPublish([](JsonObject doc) {
    // doc — a mensagem de telemetria montada pelo núcleo (ver JSON acima).
    // Adicionamos nosso campo vocIndex à primeira unidade.
    if (g_vocIndex >= 0) {
        doc["units"][0]["vocIndex"] = g_vocIndex;
    }
});
```

A linha `doc["units"][0]["vocIndex"] = g_vocIndex;` significa: "na mensagem `doc`, pegue a matriz `units`, nela o elemento `0` (nossa única unidade) e escreva ali o campo `vocIndex`". O nome do campo você escolhe — no [próximo capítulo](06-card.md) você se referirá a ele para mostrar o valor no cartão.

!!! note "Se encontrar a palavra hook"
    No código-fonte do núcleo, este callback é chamado `PublishHook` — "hook" (gancho) significa a mesma coisa: um ponto onde a biblioteca permite "pendurar" sua função. Os termos são intercambiáveis; nesta documentação dizemos "callback".

!!! note "Lambda e por que ela é "vazia""
    A construção `[](JsonObject doc) { ... }` é chamada de **lambda** — uma função sem nome, escrita no local de uso, para não exportá-la separadamente e inventar um nome.

    Os colchetes no início — "lista de captura": listam variáveis locais que a função leva com ela. A regra do núcleo: **os colchetes são sempre vazios** (`[]`) — a lambda não captura nada e não leva nenhum estado junto (isto é chamado de *stateless*, "sem estado").

    A razão é técnica: lambdas com captura exigem alocação de memória dinâmica, e alocações frequentes em ESP32 fragmentam a heap e, no pior caso, caem o Wi-Fi. Por isto o núcleo aceita apenas funções simples.

    Conclusão prática: tudo que o callback precisa, armazene em variáveis **globais** — como nosso `g_vocIndex`. Esta regra se aplica a todos os callbacks `idryer-core`.

O estado do ventilador é publicado pelo caminho do dicionário — apenas escreva nele quando você liga/desliga (lógica — no [capítulo 7](07-auto-logic.md)):

```cpp
s_link.telemetry.fanOn[0] = fanIsOn;
```

## 4. Verificação

Após carregar no fluxo MQTT do dispositivo (ou no log serial de publicações), a telemetria fica assim:

```json
{
  "units": [ { "unitId": "U1", "fanStatus": false, "vocIndex": 103 } ],
  "rssi": -52,
  "uptime": 120
}
```

`vocIndex` — seu próprio campo, foi para a nuvem junto com o `fanStatus` do vocabulário. O portal já o recebe e salva, mas ainda não sabe o que fazer com ele: mostre a ele isto no próximo capítulo.

Respire para o sensor ou aproxime um marcador — o índice deve crescer notavelmente em segundos.
