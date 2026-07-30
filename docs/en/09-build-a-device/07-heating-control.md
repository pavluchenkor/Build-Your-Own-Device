---
title: "Cabinet heating control: temperature maintenance and fan"
description: "Heating cabinet logic on idryer-core: maintaining target temperature by hysteresis, heater protection by thermistor, fan, and portal commands."
---

# Heating control

On this page you connect sensors, settings, and power control into working logic. The device maintains a set temperature in the cabinet, protects the heater from overheating, and responds to commands from the portal.

Logic runs in `loop()` alongside network servicing. All timers and thresholds are non-blocking, without `delay()`.

## What should happen

Cabinet behavior follows three simple rules:

1. **Temperature maintenance.** If the cabinet air is cooler than the target by the hysteresis value — turn on heating. When the target is reached — turn off.
2. **Heater protection.** A thermistor monitors the heater itself. If it overheats beyond the limit — heating turns off regardless of air temperature.
3. **Fan.** Turns on to distribute heat throughout the cabinet, and turns off when heating is not needed.

## Heater and fan switches

The controller turns the heater and fan on and off through a switch: a MOSFET module (version A) or SSR (version B) — see [Wiring Diagram](03-wiring.md). From the code perspective it is simply a GPIO pin: `HIGH` — on, `LOW` — off.

Describe such a switch with a small structure and create two instances — for the heater and fan. Add this to `src/main.cpp` (before `setup()`):

```cpp
struct GpioOutput {
    int pin;
    void begin() { pinMode(pin, OUTPUT); digitalWrite(pin, LOW); }
    void on()    { digitalWrite(pin, HIGH); }
    void off()   { digitalWrite(pin, LOW); }
};

static GpioOutput myHeater{4};   // GPIO4 — heater control
static GpioOutput myFan{5};      // GPIO5 — fan control
```

Pin numbers are the same as in the [Wiring Diagram](03-wiring.md). In `setup()` both switches must be initialized: `myHeater.begin();` and `myFan.begin();`.

!!! warning "Safe state on startup"
    `begin()` immediately sets `LOW` — heater and fan are off until logic decides otherwise. This is important: when power is applied, the heater must not accidentally turn on.

## Temperature maintenance by hysteresis

For a cabinet in the `40–45 °C` range, simple hysteresis is sufficient: heating turns on and off around the target. This is simpler than full PID and works reliably for gentle heat maintenance.

Target temperature and hysteresis are taken from the menu (`menu.target_temp`, `menu.hysteresis`) — it is already connected in [chapter 6](06-menu.md). Add a state flag and decision function:

```cpp
static bool s_heating = false;

static void controlLoop() {
    float air    = s_link.telemetry.airTempC[0];     // SHT31
    float target = (float)menu.target_temp;          // from menu
    float hyst   = (float)menu.hysteresis;           // from menu

    if (air < target - hyst) {
        s_heating = true;     // cooled down — heating on
    } else if (air >= target) {
        s_heating = false;    // reached target — stop
    }
}
```

Target temperature and hysteresis are taken from the [menu](06-menu.md) — the user changes them from the portal.

## Heater protection by thermistor

Air heats slowly, while the heater element heats quickly. Without separate control, the heater can overheat before the air reaches the target. Therefore, the heater thermistor sets a hard ceiling.

```cpp
static const float HEATER_MAX_C = 80.0f;   // heater temperature ceiling

static void applyHeater() {
    float heaterTemp = s_link.telemetry.heaterTempC[0];   // thermistor

    bool allow = s_heating && heaterTemp < HEATER_MAX_C;

    if (allow) {
        myHeater.on();
        s_link.telemetry.heaterPower01[0] = 1.0f;   // reflect in telemetry
    } else {
        myHeater.off();
        s_link.telemetry.heaterPower01[0] = 0.0f;
    }
}
```

!!! warning "Heater ceiling is protection, not climate control"
    `HEATER_MAX_C` limits the heater element temperature, not the air. The value depends on heater design and enclosure materials. Choose it with margin below the temperature at which printed parts deform — see [Heat-resistant materials](../07-3d-printing/04-heat-resistant-materials.md).

For smoother heating instead of on/off switching, you can control power via PWM; the `heaterPower01[0]` field accepts values from `0.0` to `1.0`. For a cabinet with gentle heat maintenance, the simple logic above is usually sufficient.

## Fan

The fan distributes heat throughout the cabinet. The simplest logic is to turn it on with the heater:

```cpp
static void applyFan() {
    bool fanOn = s_heating;          // spin while heating
    if (fanOn) myFan.on(); else myFan.off();
    s_link.telemetry.fanOn[0] = fanOn;   // reflect in telemetry
}
```

In the production controller, the fan is controlled by temperature with separate on and off thresholds (for example, turn on at `55 °C`, turn off at `35 °C`) to prevent chatter at the boundary. For a cabinet, the same approach can be applied by linking thresholds to menu parameters.

## Putting it together in loop()

```cpp
void loop() {
    s_link.loop();          // network and auto-publish

    // sensors (see "Sensors" step):
    s_climate.tick(millis());
    SensorReading c = s_climate.get();
    if (c.ok) {
        s_link.telemetry.airTempC[0]       = c.temperature;
        s_link.telemetry.airHumidityPct[0] = c.humidity;
    }
    s_link.telemetry.heaterTempC[0] = readHeaterTempC();

    controlLoop();   // decide whether to heat
    applyHeater();   // apply to heater + protection
    applyFan();      // apply to fan
}
```

Telemetry fields (`heaterPower01`, `fanOn`) are published by the facade itself — on the portal you can see whether the device is heating now and whether the fan is running.

## Commands from the portal

The portal sends heat maintenance start and stop as commands. The handler is registered with the `s_link.onCommand(name, callback)` method — **after** `s_link.begin()`. Action commands arrive with the name `invoke` and a field `action` (a role from the menu, for example `storage.start` / `storage.stop`).

To parse JSON you need the headers `<ArduinoJson.h>` and `<string.h>` (for `strcmp`) — add them to the other `#include` statements at the beginning of the file. The handler itself goes in `setup()`:

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

- `storage.start` / `storage.stop` — the same roles you set in the [menu](06-menu.md); the portal draws buttons from them.
- `iDryer::UnitMode::Storage` — gentle heat maintenance mode. This is the cabinet's primary mode.
- `s_link.status.mode[0]` and `targetTempC[0]` show the current chamber state on the portal.
- Call `publishStatusNow()` after each status change so the portal sees it immediately, without waiting for the timer.

!!! warning "No delay() in the handler"
    The `onCommand` handler is called from a network callback. Any blocking inside it breaks the MQTT session. Change flags and status, but do the actual work in `loop()`.

## Complete `src/main.cpp` after this chapter

This is the final, complete file for the device. Lines new relative to the previous chapter are marked `// ← chapter 7`. This same file is available as a ready example in the `example/09-cabinet/` folder of the repository and builds with the command `pio run -e cabinet`.

??? note "What it was — `src/main.cpp` after chapter 6"

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
#include <ArduinoJson.h>          // ← chapter 7 (onCommand: JsonObjectConst)
#include <string.h>              // ← chapter 7 (strcmp)
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

// ← chapter 7: heater and fan switches
struct GpioOutput {
    int pin;
    void begin() { pinMode(pin, OUTPUT); digitalWrite(pin, LOW); }
    void on()    { digitalWrite(pin, HIGH); }
    void off()   { digitalWrite(pin, LOW); }
};
static GpioOutput myHeater{4};
static GpioOutput myFan{5};

// ← chapter 7: temperature maintenance logic
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
    myHeater.begin();              // ← chapter 7
    myFan.begin();                 // ← chapter 7
    menu.initDefaults();
    s_link.begin();

    s_link.onCommand("invoke", [](JsonObjectConst data) {   // ← chapter 7
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

    controlLoop();   // ← chapter 7
    applyHeater();   // ← chapter 7
    applyFan();      // ← chapter 7
}
```

## Checking the result

After this step:

- starting from the portal puts the cabinet in Storage mode, the device begins heating;
- air temperature approaches the target and stays within the hysteresis range;
- heater does not exceed `HEATER_MAX_C`;
- fan and heater power are visible in telemetry;
- stopping from the portal turns off heating and switches to Idle.

## What's next

Logic is ready. It remains to assemble the device into the enclosure and test under power — [Assembly and check](08-assembly-and-check.md).
