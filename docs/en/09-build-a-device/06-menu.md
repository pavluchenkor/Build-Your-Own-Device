---
title: "Device Menu from YAML: Settings in NVS and on Portal"
description: "How to describe device menu in idryer-core using menu.yaml: target temperature and hysteresis are stored in NVS and displayed as widgets on the iDryer portal."
---

# Menu from YAML

A menu is a set of device settings: target temperature, hysteresis, fan thresholds. On `idryer-core`, the menu is described by a single file `menu.yaml`, while everything else — C++ structures, storage in non-volatile memory (NVS), and publication to the portal — is generated automatically.

This is one of the key blocks of the core. You do not write code for storing settings or invent a format for the portal — you only list parameters in YAML.

## Why a menu

After the previous steps, the device reads sensors, but all thresholds are hard-coded. The menu solves three tasks at once:

- **storage**: values survive a reboot (NVS);
- **control from the portal**: each parameter becomes a widget (slider, switch);
- **single source of truth**: one file describes both memory and interface.

## How it works

A single `menu.yaml` file is processed by a generator during build:

```text
menu.yaml → (pio run build) → C++ files in src/menu/ + NVS + JSON for portal
```

An item with a `role:` field is visible to the portal and displayed as a widget. An item without `role:` is private, for internal device logic only.

!!! warning "Do not edit generated files"
    The files `menu_state.*`, `menu_bindings.*`, `menu_ids.h`, and others are created by the generator. Edit only `menu.yaml` and rebuild — otherwise your changes will be overwritten.

## Step 1. Copy the template

The library includes a menu template. Copy it to your project:

```bash
mkdir -p src/menu
cp path/to/idryer-core/menu/menu.template.yaml src/menu/menu.yaml
```

## Step 2. Enable generation during build

Copy the hook sample from the `iDryer-Storage` project (you can use it as-is, no configuration needed):

```bash
mkdir -p extra_scripts
cp path/to/iDryer-Storage/extra_scripts/pre_gen_menu.py extra_scripts/pre_gen_menu.py
```

Then in `platformio.ini`, add `-Isrc/menu` to the `[env:cabinet]` section (so the code can see `#include <menu_state.h>`) and connect the hook via `extra_scripts`:

```ini
[env:cabinet]
; ... platform / board / lib_deps from chapter 4 — unchanged ...

build_flags =
    -Isrc/menu                      ; ← added: path to generated menu
    -DIDRYER_API_BASE='"https://portal.idryer.org/api"'
    -DMQTT_BROKER='"mqtt.idryer.org"'
    -DMQTT_PORT=8883
    -DMQTT_USE_TLS=1

extra_scripts =                     ; ← added
    pre:extra_scripts/pre_gen_menu.py
```

The hook will find the generator automatically at `lib/idryer-core/menu/menu_gen.py`, so the library must be connected via `lib/` (symlink or copy), as described in chapter 4.

## Step 3. Describe cabinet parameters

Open `src/menu/menu.yaml`. The template already includes a root item `root` with an array `children` and example parameters. Remove the examples (`my_param`, `my_flag`, `my_mode_group`) and add your own inside `children`. Keep the last two items — `units_count` and `language` — in place: these are fixed contracts with the portal.

A basic cabinet needs only a few parameters.

Target storage temperature:

```yaml
- id: target_temp
  type: value
  role: storage.target_temperature   # makes the parameter a widget on portal
  title: { ru: "ТЕМПЕРАТУРА", en: "TARGET TEMP" }
  unit:  { ru: "°C", en: "°C" }
  vtype: uint16
  min: 30
  max: 50
  step: 1
  bind: target_temp            # NVS key (≤ 15 characters)
  persist: true
  scope: global
  default: 45
```

Hysteresis (how many degrees the temperature can drop below target before heating turns on again):

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

!!! note "role: is a closed list"
    The value of `role:` cannot be arbitrary — it must be from the `canonical_roles` list in the core contract. If no suitable role exists, the build will stop and show the list of allowed values. For a storage cabinet, roles from the `storage.*` family are suitable: `storage.target_temperature`, `storage.target_humidity`, `storage.start`, `storage.stop`. The full list is in the header of `menu.template.yaml`. Parameters without `role:` (like hysteresis above) work as internal settings: they are stored in NVS but not exposed to the portal.

Restrictions that cannot be violated:

- `bind` — no longer than 15 characters (NVS key limit);
- do not add a `widget:` field to `menu.yaml` — the widget type is determined by the contract based on `role:`.

!!! warning "Check the ignore_external_cmd item in the template"
    The template includes an `ignore_external_cmd` item whose `bind` is 19 characters, exceeding the 15-character limit. If left as-is, generation will fail: `bind 'ignore_external_cmd' ... has 19 characters, limit 15`. Either remove this item or shorten `bind` to `ign_ext_cmd` (as in real products). For a basic cabinet, you can simply delete it.

## Step 4. Build the project and verify generation

```bash
pio run -e cabinet
```

During the build, the pre-hook will install dependencies (once) and generate C++ menu files. If `menu.yaml` has not changed, generation is skipped (`up-to-date`).

Verify that generation succeeded. The build log should show a message about menu generation, and the `src/menu/` folder should contain generated files:

```text
src/menu/
├── menu.yaml          # your file (source)
├── menu_state.h/.cpp  # menu object with all parameters
├── menu_bindings.*    # access by bind + write to NVS
├── menu_ids.h
└── menu_meta.h        # and others
```

If the build fails with a message about an unknown `role:` — the role is not in the `canonical_roles` list. Fix it and rebuild. Do not edit files marked autogen.

## Step 5. Connect menu to main

To use the menu code, connect two things in `src/main.cpp`:

1. The header of the generated menu:

    ```cpp
    #include <menu_state.h>      // menu object with all parameters
    ```

2. Loading defaults in `setup()` — **before** `s_link.begin()`:

    ```cpp
    menu.initDefaults();         // set default values from YAML
    ```

After this, parameters are accessible through the global `menu` object:

```cpp
uint16_t target = menu.target_temp;   // direct access to the value
```

You use these values in the heating logic in the next step. When the user changes a parameter on the portal, the core applies the new value and saves it to NVS itself.

## Complete `src/main.cpp` after this chapter

Compared to the previous chapter, only two lines were added (marked `// ← chapter 6`): menu inclusion and `menu.initDefaults()`.

??? note "What it looked like — `src/main.cpp` after chapter 5"

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
#include <menu_state.h>           // ← chapter 6

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
    menu.initDefaults();           // ← chapter 6
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

## Verify the result

After flashing:

- the target temperature setting appears in the device card on the portal;
- changing the value on the portal is saved and survives a reboot;
- internal parameters (hysteresis) are available in the code via `menu`.

## What's next

Settings are described and stored. Now let's connect them to hardware in [Heating Control](07-heating-control.md): the heater maintains the target temperature, the fan turns on at a threshold.
