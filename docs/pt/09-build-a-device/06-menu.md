---
title: "Menu do dispositivo de YAML: configurações em NVS e no portal"
description: "Como descrever o menu do dispositivo em idryer-core em menu.yaml: temperatura-alvo e histerese são armazenadas em NVS e exibidas como widgets no portal iDryer."
---

# Menu de YAML

Menu é um conjunto de configurações do dispositivo: temperatura-alvo, histerese, limiares de ventoinha. Em `idryer-core` o menu é descrito num único ficheiro `menu.yaml`, e tudo o resto - estruturas C++, armazenamento em memória não-volátil (NVS) e publicação no portal - é gerado automaticamente.

Este é um dos blocos-chave do núcleo. Não escreve código de armazenamento de configurações nem inventa formato para o portal - apenas lista parâmetros em YAML.

## Por que menu

Após os passos anteriores o dispositivo lê sensores, mas todos os limiares estão "cosidos" no código. O menu resolve três tarefas simultaneamente:

- **armazenamento**: valores sobrevivem a reinicializações (NVS);
- **gestão do portal**: cada parâmetro se torna um widget (controlo deslizante, interruptor);
- **fonte única de verdade**: um ficheiro descreve memória e interface.

## Como funciona

Um ficheiro `menu.yaml` passa através de um gerador durante a construção:

```text
menu.yaml → (compilação pio run) → ficheiros C++ em src/menu/ + NVS + JSON para portal
```

Um item com campo `role:` é visível no portal e exibido como widget. Um item sem `role:` é privado, apenas para lógica interna do dispositivo.

!!! warning "Não edite ficheiros gerados"
    Ficheiros `menu_state.*`, `menu_bindings.*`, `menu_ids.h` e outros são criados pelo gerador. Edite apenas `menu.yaml` e recompile - caso contrário as suas alterações serão sobrescritas.

## Passo 1. Copie o modelo

Há um modelo de menu na biblioteca. Copie para o projecto:

```bash
mkdir -p src/menu
cp caminho/para/idryer-core/menu/menu.template.yaml src/menu/menu.yaml
```

## Passo 2. Conecte a geração durante a compilação

Copie um exemplo de hook do projecto `iDryer-Storage` (pode ser levado como está, não precisa configurar):

```bash
mkdir -p extra_scripts
cp caminho/para/iDryer-Storage/extra_scripts/pre_gen_menu.py extra_scripts/pre_gen_menu.py
```

Depois em `platformio.ini` adicione à secção `[env:cabinet]` a linha `-Isrc/menu` (para o código ver `#include <menu_state.h>`) e conecte o hook através de `extra_scripts`:

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

O hook encontrará automaticamente o gerador no caminho `lib/idryer-core/menu/menu_gen.py`, portanto a biblioteca deve estar conectada através de `lib/` (symlink ou cópia), como descrito no capítulo 4.

## Passo 3. Descreva os parâmetros do armário

Abra `src/menu/menu.yaml`. O modelo já tem um item raiz `root` com matriz `children` e exemplos de parâmetros. Remova os exemplos (`my_param`, `my_flag`, `my_mode_group`) e adicione os seus dentro de `children`. Os últimos dois itens - `units_count` e `language` - deixe no lugar: este é um contrato fixa com o portal.

Para um armário básico basta alguns parâmetros.

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

Histerese (quanto graus a temperatura pode descer abaixo do alvo antes de o aquecimento retomar):

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

!!! note "role: - é uma lista fechada"
    O valor `role:` não pode ser inventado arbitrariamente - deve ser da lista `canonical_roles` do contrato do núcleo. Se não há papel apropriado, a compilação parará e mostrará a lista permitida. Para armazém de armazenamento as funções adequadas são da família `storage.*`: `storage.target_temperature`, `storage.target_humidity`, `storage.start`, `storage.stop`. A lista completa está na cabeça `menu.template.yaml`. Parâmetros sem `role:` (como histerese acima) funcionam como configurações internas: armazenadas em NVS, mas não saem para o portal.

Restrições que não podem ser violadas:

- `bind` - não mais de 15 caracteres (limite de chave NVS);
- não adicione o campo `widget:` em `menu.yaml` - o tipo de widget é determinado pelo contrato por `role:`.

!!! warning "Verifique o item ignore_external_cmd do modelo"
    No modelo há um item `ignore_external_cmd`, e seu `bind` tem 19 caracteres, o que excede o limite de 15. Se deixar assim, a geração falhará: `bind 'ignore_external_cmd' ... tem 19 caracteres, limite 15`. Ou remova este item, ou encurte `bind` para `ign_ext_cmd` (como em produtos reais). Para um armário básico pode ser simplesmente removido.

## Passo 4. Compile o projecto e verifique geração

```bash
pio run -e cabinet
```

Durante a compilação o hook pré-compilado instala dependências (uma vez) e gera ficheiros C++ do menu. Se `menu.yaml` não mudou - a geração é pulada (`up-to-date`).

Verifique que a geração passou. No log de compilação aparece uma linha sobre geração de menu, e na pasta `src/menu/` - ficheiros gerados:

```text
src/menu/
├── menu.yaml          # seu ficheiro (fonte)
├── menu_state.h/.cpp  # objecto menu com todos os parâmetros
├── menu_bindings.*    # acesso por bind + escrita em NVS
├── menu_ids.h
└── menu_meta.h        # e outros
```

Se a compilação caiu com mensagem sobre `role:` desconhecida - significa que o papel não está da lista `canonical_roles`. Corrija-o e recompile. Ficheiros com marca autogen não edite à mão.

## Passo 5. Conecte o menu no principal

Para usar o código do menu, conecte em `src/main.cpp` duas coisas:

1. Cabeçalho do menu gerado:

    ```cpp
    #include <menu_state.h>      // objecto menu com todos os parâmetros
    ```

2. Carregamento de padrões em `setup()` - **antes** de `s_link.begin()`:

    ```cpp
    menu.initDefaults();         // estabelecer valores padrão do YAML
    ```

Após isto os parâmetros estão disponíveis através do objecto global `menu`:

```cpp
uint16_t target = menu.target_temp;   // acesso directo ao valor
```

Estes valores usa na lógica de aquecimento no próximo passo. Quando o utilizador muda o parâmetro no portal, o núcleo aplica automaticamente o novo valor e o armazena em NVS.

## Completo `src/main.cpp` após este capítulo

Relativamente ao capítulo anterior foram adicionadas apenas duas linhas (marcadas `// ← capítulo 6`): inclusão do menu e `menu.initDefaults()`.

??? note "O que era — `src/main.cpp` após o capítulo 5"

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

Após o firmware:

- na carátula do dispositivo no portal aparece a configuração de temperatura-alvo;
- mudança de valor no portal é armazenada e sobrevive a reinicializações;
- parâmetros internos (histerese) estão disponíveis no código através de `menu`.

## O que vem a seguir

Configurações são descritas e armazenadas. Agora as ligamos ao hardware em [Controlo de aquecimento](07-heating-control.md): o aquecedor mantém a temperatura-alvo, a ventoinha liga-se pelo limiar.
