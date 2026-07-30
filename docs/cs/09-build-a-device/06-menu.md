---
title: "Nabídka zařízení z YAML: nastavení v NVS a na portálu"
description: "Jak popsat nabídku zařízení v idryer-core v menu.yaml: cílová teplota a hystereze se ukládají v NVS a zobrazují se widgety na portálu iDryer."
---

# Nabídka z YAML

Nabídka je soubor nastavení zařízení: cílová teplota, hystereze, prahy ventilátoru. V `idryer-core` se nabídka popisuje jedním souborem `menu.yaml`, zatímco vše ostatní — C++-struktury, ukládání do paměti bez napájení (NVS) a publikace na portál — se generují automaticky.

Jedná se o jeden z klíčových prvků jádra. Nepíšete kód pro ukládání nastavení a nevymýšlíte formát pro portál — pouze vypíšete parametry v YAML.

## Proč je nabídka potřebná

Po předchozích krocích zařízení čte senzory, ale všechny prahy jsou „pevně zakódovány" v kódu. Nabídka řeší tři úkoly najednou:

- **Ukládání**: hodnoty přežijí restart (NVS);
- **Správa z portálu**: každý parametr se stane widgetem (posuvník, přepínač);
- **Jediný zdroj pravdy**: jeden soubor popisuje jak paměť, tak rozhraní.

## Jak to funguje

Jeden soubor `menu.yaml` prochází generátorem během sestavení:

```text
menu.yaml → (pio run) → C++-soubory v src/menu/ + NVS + JSON pro portál
```

Položka s polem `role:` je viditelná portálu a zobrazuje se jako widget. Položka bez `role:` — je soukromá, pouze pro interní logiku zařízení.

!!! warning "Neupravujte vygenerované soubory"
    Soubory `menu_state.*`, `menu_bindings.*`, `menu_ids.h` a další vytváří generátor. Upravujte pouze `menu.yaml` a znovu sestavte — jinak budou vaše změny přepsány.

## Krok 1. Zkopírujte šablonu

V knihovně je šablona nabídky. Zkopírujte ji do projektu:

```bash
mkdir -p src/menu
cp path/to/idryer-core/menu/menu.template.yaml src/menu/menu.yaml
```

## Krok 2. Připojte generování během sestavení

Zkopírujte vzor háku z projektu `iDryer-Storage` (můžete jej použít takový, jaký je, není potřeba jej konfigurovat):

```bash
mkdir -p extra_scripts
cp path/to/iDryer-Storage/extra_scripts/pre_gen_menu.py extra_scripts/pre_gen_menu.py
```

Poté v `platformio.ini` přidejte do oddílu `[env:cabinet]` řádek `-Isrc/menu` (aby kód viděl `#include <menu_state.h>`) a připojte hák pomocí `extra_scripts`:

```ini
[env:cabinet]
; ... platform / board / lib_deps z kapitoly 4 — beze změn ...

build_flags =
    -Isrc/menu                      ; ← přidáno: cesta k vygenerované nabídce
    -DIDRYER_API_BASE='"https://portal.idryer.org/api"'
    -DMQTT_BROKER='"mqtt.idryer.org"'
    -DMQTT_PORT=8883
    -DMQTT_USE_TLS=1

extra_scripts =                     ; ← přidáno
    pre:extra_scripts/pre_gen_menu.py
```

Hák sám najde generátor na cestě `lib/idryer-core/menu/menu_gen.py`, takže knihovna musí být připojena přes `lib/` (symlink nebo kopie), jak je popsáno v kapitole 4.

## Krok 3. Popište parametry skříně

Otevřete `src/menu/menu.yaml`. V šabloně je již kořenová položka `root` s polem `children` a příklady parametrů. Odstraňte příklady (`my_param`, `my_flag`, `my_mode_group`) a přidejte své vlastní do `children`. Poslední dvě položky — `units_count` a `language` — ponechte na místě: jedná se o pevný kontrakt s portálem.

Pro základní skříň postačují pouze některé parametry.

Cílová teplota skladování:

```yaml
- id: target_temp
  type: value
  role: storage.target_temperature   # učiní parametr widgetem na portálu
  title: { ru: "ТЕМПЕРАТУРА", en: "TARGET TEMP" }
  unit:  { ru: "°C", en: "°C" }
  vtype: uint16
  min: 30
  max: 50
  step: 1
  bind: target_temp            # NVS-klíč (≤ 15 znaků)
  persist: true
  scope: global
  default: 45
```

Hystereze (o kolik stupňů se může teplota snížit pod cíl, než se topení znovu zapne):

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

!!! note "role: — jedná se o uzavřený seznam"
    Hodnotu `role:` nemůžete vymýšlet libovolně — musí pocházet ze seznamu `canonical_roles` smlouvy jádra. Pokud není vhodná role, sestavení se zastaví a zobrazí seznam povolených. Pro skříň skladování se hodí role z rodiny `storage.*`: `storage.target_temperature`, `storage.target_humidity`, `storage.start`, `storage.stop`. Úplný seznam je v záhlaví `menu.template.yaml`. Parametry bez `role:` (jako hystereze výše) fungují jako interní nastavení: ukládají se v NVS, ale nezveřejňují se na portálu.

Omezení, která nesmíte porušit:

- `bind` — ne delší než 15 znaků (limit klíče NVS);
- nepřidávejte pole `widget:` do `menu.yaml` — typ widgetu určuje smlouva podle `role:`.

!!! warning "Zkontrolujte položku ignore_external_cmd ze šablony"
    V šabloně je položka `ignore_external_cmd` a její `bind` — 19 znaků, což překračuje limit 15. Pokud to ponecháte tak, jak to je, generování selhá: `bind 'ignore_external_cmd' ... má 19 znaků, limit je 15`. Buď odstraňte tuto položku, nebo zkraťte `bind` na `ign_ext_cmd` (jako v reálných produktech). Pro základní skříň jej můžete jednoduše odstranit.

## Krok 4. Sestavte projekt a zkontrolujte generování

```bash
pio run -e cabinet
```

Během sestavení pre-hook sám nainstaluje závislosti (jednou) a vygeneruje C++-soubory nabídky. Pokud se `menu.yaml` nezměnil — generování se přeskočí (`up-to-date`).

Zkontrolujte, že generování proběhlo. V logu sestavení se zobrazí řádek o generování nabídky a ve složce `src/menu/` — vygenerované soubory:

```text
src/menu/
├── menu.yaml          # váš soubor (zdroj)
├── menu_state.h/.cpp  # objekt menu se všemi parametry
├── menu_bindings.*    # přístup podle bind + zápis do NVS
├── menu_ids.h
└── menu_meta.h        # a další
```

Pokud sestavení selhalo se zprávou o neznámé `role:` — znamená to, že role není ze seznamu `canonical_roles`. Opravte ji a znovu sestavte. Soubory označené autogen neupravujte ručně.

## Krok 5. Připojte nabídku do hlavního souboru

Chcete-li použít kód nabídky, připojte do `src/main.cpp` dvě věci:

1. Záhlaví vygenerované nabídky:

    ```cpp
    #include <menu_state.h>      // objekt menu se všemi parametry
    ```

2. Načtení výchozích hodnot v `setup()` — **před** `s_link.begin()`:

    ```cpp
    menu.initDefaults();         // nastavit výchozí hodnoty z YAML
    ```

Poté jsou parametry přístupné přes globální objekt `menu`:

```cpp
uint16_t target = menu.target_temp;   // přímý přístup k hodnotě
```

Tyto hodnoty používáte v logice topení v dalším kroku. Když uživatel změní parametr na portálu, jádro automaticky aplikuje novou hodnotu a uloží ji do NVS.

## Kompletní `src/main.cpp` po této kapitole

Relativně k předchozí kapitole byly přidány pouze dva řádky (označeny `// ← kapitola 6`): připojení nabídky a `menu.initDefaults()`.

??? note "Co bylo — `src/main.cpp` po kapitole 5"

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
#include <menu_state.h>           // ← kapitola 6

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
    menu.initDefaults();           // ← kapitola 6
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

## Ověření výsledku

Po nahrání firmwaru:

- na portálu v kartě zařízení se zobrazí nastavení cílové teploty;
- změna hodnoty na portálu se uloží a přežije restart;
- interní parametry (hystereze) jsou přístupné v kódu přes `menu`.

## Co dále

Nastavení jsou popsány a ukládají se. Nyní je propojíme se železem v [Řízení topení](07-heating-control.md): topič udržuje cílovou teplotu, ventilátor se zapíná na základě prahu.
