---
title: "Menu do dispositivo em YAML: configurações em NVS e no portal"
description: "Como descrever o menu do dispositivo em idryer-core em menu.yaml: temperatura-alvo e histerese são salvos em NVS e exibidos com widgets no portal iDryer."
---

# Menu em YAML

Menu é um conjunto de configurações do dispositivo: temperatura-alvo, histerese, limites de ventilador. Em `idryer-core`, o menu é descrito em um arquivo `menu.yaml`, e todo o resto — estruturas C++, salvamento em memória não-volátil (NVS) e publicação no portal — é gerado automaticamente.

Este é um dos blocos-chave do núcleo. Você não escreve código de armazenamento de configurações e não inventa formato para o portal — você apenas lista parâmetros em YAML.

## Por que menu

Após os passos anteriores, o dispositivo lê sensores, mas todos os limites estão "codificados" no código. Menu resolve três tarefas de uma vez:

- **armazenamento**: valores sobrevivem ao reinício (NVS);
- **gerenciamento do portal**: cada parâmetro se torna um widget (slider, alternador);
- **fonte única de verdade**: um arquivo descreve tanto memória quanto interface.

## Como funciona

Um arquivo `menu.yaml` passa por um gerador durante a construção:

```text
menu.yaml → (pio run) → arquivos C++ em src/menu/ + NVS + JSON para portal
```

Um item com campo `role:` é visível ao portal e exibido como widget. Um item sem `role:` é privado, apenas para lógica interna do dispositivo.

!!! warning "Não edite os arquivos gerados"
    Arquivos `menu_state.*`, `menu_bindings.*`, `menu_ids.h` e outros são criados pelo gerador. Edite apenas `menu.yaml` e reconstrua — senão suas mudanças serão sobrescritas.

## Passo 1. Copie o template

A biblioteca tem um template de menu. Copie-o para seu projeto:

```bash
mkdir -p src/menu
cp path/to/idryer-core/menu/menu.template.yaml src/menu/menu.yaml
```

## Passo 2. Conecte a geração durante a construção

Copie o exemplo do hook do projeto `iDryer-Storage` (você pode pegar como está, não precisa configurar):

```bash
mkdir -p extra_scripts
cp path/to/iDryer-Storage/extra_scripts/pre_gen_menu.py extra_scripts/pre_gen_menu.py
```

Depois em `platformio.ini` adicione em `[env:cabinet]` a string `-Isrc/menu` (para que o código veja `#include <menu_state.h>`) e conecte o hook via `extra_scripts`:

```ini
[env:cabinet]
; ... platform / board / lib_deps do capítulo 4 — sem mudanças ...

build_flags =
    -Isrc/menu                      ; ← adicionado: caminho para menu gerado
    -DIDRYER_API_BASE='"https://portal.idryer.org/api"'
    -DMQTT_BROKER='"mqtt.idryer.org"'
    -DMQTT_PORT=8883
    -DMQTT_USE_TLS=1

extra_scripts =                     ; ← adicionado
    pre:extra_scripts/pre_gen_menu.py
```

O hook encontrará automaticamente o gerador no caminho `lib/idryer-core/menu/menu_gen.py`, então a biblioteca deve estar conectada via `lib/` (symlink ou cópia), como descrito no capítulo 4.

## Passo 3. Descreva os parâmetros do gabinete

Abra `src/menu/menu.yaml`. No template já há um item raiz `root` com array `children` e exemplos de parâmetros. Remova os exemplos (`my_param`, `my_flag`, `my_mode_group`) e adicione os seus dentro de `children`. Os dois últimos itens — `units_count` e `language` — deixe no lugar: é um contrato fixo com o portal.

Para um gabinete básico, alguns parâmetros são suficientes.

Temperatura-alvo de armazenamento:

```yaml
- id: target_temp
  type: value
  role: storage.target_temperature   # torna o parâmetro um widget no portal
  title: { ru: "ТЕМПЕРАТУРА", en: "TARGET TEMP" }
  unit:  { ru: "°C", en: "°C" }
  vtype: uint16
  min: 30
  max: 50
  step: 1
  bind: target_temp            # chave NVS (≤ 15 caracteres)
  persist: true
  scope: global
  default: 45
```

Histerese (quantos graus a temperatura pode cair abaixo da meta antes de o aquecimento ligar novamente):

```yaml
- id: hysteresis
  type: value
  title: { ru: "ГИСТЕРЕЗИС", en: "HYSTERESIS" }
  unit:  { ru: "°C", en: "°C" }
  vtype: uint8
  min: 1
  max: 5
  step: 1
  bind: hysteresis
  persist: true
  scope: global
  default: 2
```

!!! note "role: — é uma lista fechada"
    O valor `role:` não pode ser inventado arbitrariamente — deve ser da lista `canonical_roles` do contrato do núcleo. Se nenhuma função apropriada existe, a construção para e mostra a lista de permitidas. Para um gabinete de armazenamento, funções da família `storage.*` se adequam: `storage.target_temperature`, `storage.target_humidity`, `storage.start`, `storage.stop`. Lista completa — no cabeçalho `menu.template.yaml`. Parâmetros sem `role:` (como histerese acima) funcionam como configurações internas: armazenadas em NVS, mas não exportadas para o portal.

Limitações que não podem ser violadas:

- `bind` — não mais de 15 caracteres (limite de chave NVS);
- não adicione campo `widget:` em `menu.yaml` — o tipo de widget é determinado pelo contrato em `role:`.

!!! warning "Verifique o item ignore_external_cmd do template"
    O template tem um item `ignore_external_cmd`, e seu `bind` — 19 caracteres, excedem o limite de 15. Se deixar como está, a geração cai: `bind 'ignore_external_cmd' ... tem 19 caracteres, limite 15`. Ou remova este item, ou encurte `bind` para `ign_ext_cmd` (como em produtos reais). Para um gabinete básico você pode simplesmente removê-lo.

## Passo 4. Construa o projeto e verifique a geração

```bash
pio run -e cabinet
```

Durante a construção, o pre-hook instala automaticamente as dependências (uma vez) e gera arquivos C++ do menu. Se `menu.yaml` não mudou — a geração é pulada (`up-to-date`).

Verifique se a geração passou. No log de construção aparece uma linha sobre geração de menu, e na pasta `src/menu/` — arquivos gerados:

```text
src/menu/
├── menu.yaml          # seu arquivo (fonte)
├── menu_state.h/.cpp  # objeto menu com todos os parâmetros
├── menu_bindings.*    # acesso por bind + escrita em NVS
├── menu_ids.h
└── menu_meta.h        # e outros
```

Se a construção caiu com mensagem sobre `role:` desconhecida — significa a função está escrita fora da lista `canonical_roles`. Corrija-a e reconstrua. Arquivos marcados autogen não edite manualmente.

## Passo 5. Conecte o menu ao principal

Para usar o código do menu, conecte em `src/main.cpp` duas coisas:

1. Cabeçalho do menu gerado:

    ```cpp
    #include <menu_state.h>      // objeto menu com todos os parâmetros
    ```

2. Carregamento de padrões em `setup()` — **antes** de `s_link.begin()`:

    ```cpp
    menu.initDefaults();         // definir valores padrão de YAML
    ```

Depois os parâmetros são acessíveis através do objeto global `menu`:

```cpp
uint16_t target = menu.target_temp;   // acesso direto ao valor
```

Esses valores você usa na lógica de aquecimento no próximo passo. Quando o usuário muda o parâmetro no portal, o núcleo aplica automaticamente o novo valor e o salva em NVS.

## Completo `src/main.cpp` após este capítulo

Comparado ao capítulo anterior, apenas duas linhas foram adicionadas (marcadas `// ← capítulo 6`): conexão do menu e `menu.initDefaults()`.

??? nota «O que foi — `src/main.cpp` após capítulo 5»

    ```cpp
    #include <iDryer.h>
    #include <Wire.h>
    #include <math.h>
    #include "Sht31ClimateSensor.h"

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
#include <iDryer.h>
#include <Wire.h>
#include <math.h>
#include "Sht31ClimateSensor.h"
#include <menu_state.h>           // ← capítulo 6

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
    menu.initDefaults();           // ← capítulo 6
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

## Verificação de resultado

Após flashear:

- na página do dispositivo do portal uma configuração de temperatura-alvo aparece;
- a alteração do valor no portal é salva e sobrevive ao reinício;
- parâmetros internos (histerese) são acessíveis no código via `menu`.

## O que vem a seguir

As configurações estão descritas e armazenadas. Agora as conectamos com o hardware em [Controle de aquecimento](07-heating-control.md): o aquecedor mantém a temperatura-alvo, ventilador liga por limite.
