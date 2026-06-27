---
title: "Řízení vytápění skříně: údržba teploty a ventilátor"
description: "Logika vytápěné skříně na idryer-core: udržování cílové teploty histerezí, ochrana ohřívače termistorem, ventilátor a příkazy portálu."
---

# Řízení vytápění

Na této stránce spojujete senzory, nastavení a výkonovou část v pracovní logiku. Zařízení udržuje v skříni zadanou teplotu, chrání ohřívač před přehřátím a reaguje na příkazy z portálu.

Logika se provádí v `loop()` vedle údržby sítě. Všechny časovače a prahy jsou neblokující, bez `delay()`.

## Co by se mělo stát

Chování skříně se skládá ze tří jednoduchých pravidel:

1. **Údržba teploty.** Pokud je vzduch ve skříni chladnější než cíl o hodnotu histereze — zapnout vytápění. Když dosáhne cíle — vypnout.
2. **Ochrana ohřívače.** Termistor kontroluje samotný ohřívač. Pokud se přehřál nad přípustnou hranici — vytápění se vypne nezávisle na teplotě vzduchu.
3. **Ventilátor.** Zapíná se, aby se rozprostřelo teplo po skříni, a vypíná se, když vytápění není potřeba.

## Klíče ohřívače a ventilátoru

Ohřívač a ventilátor řadič zapíná pomocí klíče: MOSFET modul (verze A) nebo SSR (verze B) — viz [Schéma zapojení](03-wiring.md). Z pohledu kódu je to jednoduše výstup GPIO: `HIGH` — zapnuto, `LOW` — vypnuto.

Popišme takový klíč malou strukturou a máme dva výskyty — pro ohřívač a ventilátor. Přidejte to do `src/main.cpp` (před `setup()`):

```cpp
struct GpioOutput {
    int pin;
    void begin() { pinMode(pin, OUTPUT); digitalWrite(pin, LOW); }
    void on()    { digitalWrite(pin, HIGH); }
    void off()   { digitalWrite(pin, LOW); }
};

static GpioOutput myHeater{4};   // GPIO4 — řízení ohřívače
static GpioOutput myFan{5};      // GPIO5 — řízení ventilátoru
```

Čísla výstupů jsou stejná jako v [Schématu zapojení](03-wiring.md). V `setup()` oba klíče musí být inicializovány: `myHeater.begin();` a `myFan.begin();`.

!!! warning "Bezpečný stav při spuštění"
    `begin()` okamžitě nastaví `LOW` — ohřívač a ventilátor jsou vypnuty, dokud logika nerozhodne jinak. To je důležité: při zapnutí napájení by se ohřívač neměl náhodou zapnout.

## Údržba teploty histerezí

Pro skříň na `40–45 °C` je dostačující jednoduchá hystereze: vytápění se zapíná a vypíná kolem cíle. To je jednodušší než plný PID a pro měkké udržování tepla funguje spolehlivě.

Cílovou teplotu a hysterezí vezmeme z menu (`menu.target_temp`, `menu.hysteresis`) — je již připojeno v [kapitole 6](06-menu.md). Přidejte příznak stavu a funkci rozhodování:

```cpp
static bool s_heating = false;

static void controlLoop() {
    float air    = s_link.telemetry.airTempC[0];     // SHT31
    float target = (float)menu.target_temp;          // z menu
    float hyst   = (float)menu.hysteresis;           // z menu

    if (air < target - hyst) {
        s_heating = true;     // vychladla — topíme
    } else if (air >= target) {
        s_heating = false;    // dosáhla cíle — stop
    }
}
```

Cílová teplota a hystereze se berou z [menu](06-menu.md) — uživatel je mění z portálu.

## Ochrana ohřívače termistorem

Vzduch se ohřívá pomalu, ale spirála ohřívače — rychle. Bez samostatného řízení se ohřívač stihne přehřát dříve, než se vzduch dostane na cíl. Proto termistor ohřívače nastavuje tvrdý strop.

```cpp
static const float HEATER_MAX_C = 80.0f;   // strop teploty ohřívače

static void applyHeater() {
    float heaterTemp = s_link.telemetry.heaterTempC[0];   // termistor

    bool allow = s_heating && heaterTemp < HEATER_MAX_C;

    if (allow) {
        myHeater.on();
        s_link.telemetry.heaterPower01[0] = 1.0f;   // odrazit v telemetrii
    } else {
        myHeater.off();
        s_link.telemetry.heaterPower01[0] = 0.0f;
    }
}
```

!!! warning "Strop ohřívače — to je ochrana, ne seřízení klimatu"
    `HEATER_MAX_C` omezuje teplotu samotného ohřívače, ne vzduchu. Hodnota závisí na konstrukci ohřívače a materiálech skříně. Vyberte ji s rezervou pod teplotu, při které se deformují tištěné díly — viz [Žáruvzdorné materiály](../07-3d-printing/04-heat-resistant-materials.md).

Pro měkčí ohřev místo zapínání/vypínání „všechno nebo nic" lze řídit výkon pomocí PWM a pole `heaterPower01[0]` přijímá hodnoty od `0.0` do `1.0`. Pro skříň s měkkým udržováním tepla je výše uvedená jednoduchá logika obvykle dostačující.

## Ventilátor

Ventilátor rozprostírá teplo po skříni. Nejjednodušší logika — zapínáme ho spolu s vytápěním:

```cpp
static void applyFan() {
    bool fanOn = s_heating;          // točíme, zatímco topíme
    if (fanOn) myFan.on(); else myFan.off();
    s_link.telemetry.fanOn[0] = fanOn;   // odrazit v telemetrii
}
```

V sériovém řadiči je ventilátor řízený teplotou se samostatnými prahy zapnutí a vypnutí (například zapnutí při `55 °C`, vypnutí při `35 °C`), aby se nedvíhal na hranici. Pro skříň lze aplikovat stejný přístup, vázáním prahů na parametry menu.

## Montáž v loop()

```cpp
void loop() {
    s_link.loop();          // síť a automatické publikování

    // senzory (viz krok „Senzory"):
    s_climate.tick(millis());
    SensorReading c = s_climate.get();
    if (c.ok) {
        s_link.telemetry.airTempC[0]       = c.temperature;
        s_link.telemetry.airHumidityPct[0] = c.humidity;
    }
    s_link.telemetry.heaterTempC[0] = readHeaterTempC();

    controlLoop();   // rozhodujeme, topit nebo ne
    applyHeater();   // aplikujeme na ohřívač + ochrana
    applyFan();      // aplikujeme na ventilátor
}
```

Pole telemetrie (`heaterPower01`, `fanOn`) fasáda publikuje sama — na portálu je vidět, zda zařízení právě topí a zda ventilátor funguje.

## Příkazy z portálu

Spuštění a zastavení údržby tepla portál posílá jako příkazy. Obslužná rutina se registruje metodou `s_link.onCommand(jméno, callback)` — **po** `s_link.begin()`. Příkazy akcí přicházejí s názvem `invoke` a polem `action` (role z menu, např. `storage.start` / `storage.stop`).

Pro analýzu JSON jsou potřeba záhlaví `<ArduinoJson.h>` a `<string.h>` (pro `strcmp`) — přidejte je k ostatním `#include` na začátku souboru. Samotná obslužná rutina se umisťuje do `setup()`:

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

- `storage.start` / `storage.stop` — stejné role, které jste nastavili v [menu](06-menu.md); portál podle nich kreslí tlačítka.
- `iDryer::UnitMode::Storage` — režim měkkého udržování tepla. To je hlavní režim skříně.
- `s_link.status.mode[0]` a `targetTempC[0]` zobrazují na portálu aktuální stav komory.
- `publishStatusNow()` volejte po každé změně stavu, aby portál viděl změnu hned, bez čekání na časovač.

!!! warning "Žádné delay() v obslužné rutině"
    Obslužná rutina `onCommand` se volá z síťového callbacku. Jakékoli blokování v ní přeruší MQTT-relaci. Měňte příznaky a stav, práci samu dělej v `loop()`.

## Úplný `src/main.cpp` po této kapitole

Toto je finální, hotový soubor zařízení. Nové řádky oproti předchozí kapitole jsou označeny `// ← kapitola 7`. Stejný soubor leží jako hotový příklad ve složce `example/09-cabinet/` repozitáře a sestavuje se příkazem `pio run -e cabinet`.

??? poznámka "Co bylo — `src/main.cpp` po kapitole 6"

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
#include <ArduinoJson.h>          // ← kapitola 7 (onCommand: JsonObjectConst)
#include <string.h>              // ← kapitola 7 (strcmp)
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

// ← kapitola 7: klíče ohřívače a ventilátoru
struct GpioOutput {
    int pin;
    void begin() { pinMode(pin, OUTPUT); digitalWrite(pin, LOW); }
    void on()    { digitalWrite(pin, HIGH); }
    void off()   { digitalWrite(pin, LOW); }
};
static GpioOutput myHeater{4};
static GpioOutput myFan{5};

// ← kapitola 7: logika údržby teploty
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
    myHeater.begin();              // ← kapitola 7
    myFan.begin();                 // ← kapitola 7
    menu.initDefaults();
    s_link.begin();

    s_link.onCommand("invoke", [](JsonObjectConst data) {   // ← kapitola 7
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

    controlLoop();   // ← kapitola 7
    applyHeater();   // ← kapitola 7
    applyFan();      // ← kapitola 7
}
```

## Kontrola výsledku

Po tomto kroku:

- spuštění z portálu převede skříň do režimu Storage, zařízení začne topit;
- teplota vzduchu se přiblíží k cíli a zůstane v mezích histereze;
- ohřívač nepřekročí `HEATER_MAX_C`;
- ventilátor a výkon topení jsou vidět v telemetrii;
- zastavení z portálu vypne vytápění a převede do režimu Idle.

## Co dál

Logika je hotova. Zbývá složit zařízení do skříně a zkontrolovat pod napájením — [Montáž a kontrola](08-assembly-and-check.md).
