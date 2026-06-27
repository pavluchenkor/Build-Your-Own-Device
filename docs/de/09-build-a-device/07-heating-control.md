---
title: "Heizungsmanagement des Schranks: Temperaturregelung und Lüfter"
description: "Logik des beheizten Schranks auf idryer-core: Halten der Zieltemperatur durch Hysterese, Heizerschutz durch Thermistor, Lüfter und Portal-Befehle."
---

# Heizungsmanagement

Auf dieser Seite verbinden Sie Sensoren, Einstellungen und Leistungsteile zu einer funktionierenden Logik. Das Gerät hält die eingestellte Temperatur im Schrank, schützt den Heizer vor Überhitzung und reagiert auf Befehle vom Portal.

Die Logik wird in `loop()` neben der Netzwerkbereitstellung ausgeführt. Alle Timer und Schwellwerte sind nicht-blockierend, ohne `delay()`.

## Was sollte passieren

Das Verhalten des Schranks besteht aus drei einfachen Regeln:

1. **Temperaturregelung.** Wenn die Luft im Schrank unter dem Ziel um den Hysterese-Wert liegt – Heizung einschalten. Wenn das Ziel erreicht ist – ausschalten.
2. **Heizerschutz.** Der Thermistor überwacht den Heizer selbst. Wenn er über das zulässige Maß hinaus überhitzt wird – wird die Heizung unabhängig von der Lufttemperatur ausgeschaltet.
3. **Lüfter.** Er wird eingeschaltet, um die Wärme im Schrank zu verteilen, und ausgeschaltet, wenn keine Heizung erforderlich ist.

## Schalter für Heizer und Lüfter

Der Controller schaltet Heizer und Lüfter über einen Schalter ein: MOSFET-Modul (Version A) oder SSR (Version B) – siehe [Schaltplan](03-wiring.md). Aus Code-Sicht ist dies einfach ein GPIO-Ausgang: `HIGH` – eingeschaltet, `LOW` – ausgeschaltet.

Beschreiben Sie einen solchen Schalter mit einer kleinen Struktur und erstellen Sie zwei Instanzen – für Heizer und Lüfter. Fügen Sie dies zu `src/main.cpp` (vor `setup()`) hinzu:

```cpp
struct GpioOutput {
    int pin;
    void begin() { pinMode(pin, OUTPUT); digitalWrite(pin, LOW); }
    void on()    { digitalWrite(pin, HIGH); }
    void off()   { digitalWrite(pin, LOW); }
};

static GpioOutput myHeater{4};   // GPIO4 – Heizungssteuerung
static GpioOutput myFan{5};      // GPIO5 – Lüftersteuerung
```

Die Pin-Nummern sind dieselben wie im [Schaltplan](03-wiring.md). In `setup()` müssen beide Schalter initialisiert werden: `myHeater.begin();` und `myFan.begin();`.

!!! warning "Sicherer Zustand beim Start"
    `begin()` setzt sofort `LOW` – Heizer und Lüfter sind ausgeschaltet, bis die Logik anderes entscheidet. Das ist wichtig: Bei der Stromversorgung sollte der Heizer nicht versehentlich eingeschaltet werden.

## Temperaturregelung durch Hysterese

Für einen Schrank bei `40–45 °C` ist eine einfache Hysterese ausreichend: Die Heizung wird um das Ziel herum ein- und ausgeschaltet. Dies ist einfacher als vollwertiger PID und funktioniert bei sanfter Wärmeregelung zuverlässig.

Die Zieltemperatur und Hysterese werden aus dem Menü (`menu.target_temp`, `menu.hysteresis`) entnommen – es ist bereits in [Kapitel 6](06-menu.md) angeschlossen. Fügen Sie ein Zustandsflag und eine Entscheidungsfunktion hinzu:

```cpp
static bool s_heating = false;

static void controlLoop() {
    float air    = s_link.telemetry.airTempC[0];     // SHT31
    float target = (float)menu.target_temp;          // aus Menü
    float hyst   = (float)menu.hysteresis;           // aus Menü

    if (air < target - hyst) {
        s_heating = true;     // abgekühlt – heizen
    } else if (air >= target) {
        s_heating = false;    // Ziel erreicht – stopp
    }
}
```

Die Zieltemperatur und Hysterese werden aus dem [Menü](06-menu.md) entnommen – der Benutzer ändert sie vom Portal aus.

## Heizerschutz durch Thermistor

Die Luft wärmt sich langsam auf, die Heizerspirale schnell. Ohne separate Kontrolle kann sich der Heizer überhitzen, bevor die Luft das Ziel erreicht. Daher setzt der Heizer-Thermistor eine harte Obergrenze.

```cpp
static const float HEATER_MAX_C = 80.0f;   // Obergrenze der Heizer-Temperatur

static void applyHeater() {
    float heaterTemp = s_link.telemetry.heaterTempC[0];   // Thermistor

    bool allow = s_heating && heaterTemp < HEATER_MAX_C;

    if (allow) {
        myHeater.on();
        s_link.telemetry.heaterPower01[0] = 1.0f;   // in Telemetrie widerspiegeln
    } else {
        myHeater.off();
        s_link.telemetry.heaterPower01[0] = 0.0f;
    }
}
```

!!! warning "Heizer-Obergrenze ist Schutz, nicht Klimaregelung"
    `HEATER_MAX_C` begrenzt die Temperatur des Heizers selbst, nicht der Luft. Der Wert hängt von der Heizerkonstruktion und den Gehäusematerialien ab. Wählen Sie ihn mit einem Puffer unterhalb der Temperatur, bei der die gedruckten Teile verformen – siehe [Hitzebeständige Materialien](../07-3d-printing/04-heat-resistant-materials.md).

Für sanfteres Heizen können Sie die Leistung statt Ein-/Ausschalten über PWM steuern und das Feld `heaterPower01[0]` akzeptiert Werte von `0.0` bis `1.0`. Für einen Schrank mit sanfter Wärmeregelung ist die obige einfache Logik normalerweise ausreichend.

## Lüfter

Der Lüfter verteilt die Wärme im Schrank. Die einfachste Logik – schalte ihn zusammen mit der Heizung ein:

```cpp
static void applyFan() {
    bool fanOn = s_heating;          // läuft, während wir heizen
    if (fanOn) myFan.on(); else myFan.off();
    s_link.telemetry.fanOn[0] = fanOn;   // in Telemetrie widerspiegeln
}
```

Im seriellen Controller wird der Lüfter nach Temperatur mit separaten Ein- und Ausschaltgrenzen gesteuert (z.B. Einschalten bei `55 °C`, Ausschalten bei `35 °C`), damit er an der Grenze nicht zittert. Für den Schrank können Sie denselben Ansatz anwenden und die Grenzen an Menüparameter binden.

## In loop() zusammenstellen

```cpp
void loop() {
    s_link.loop();          // Netzwerk und automatische Veröffentlichung

    // Sensoren (siehe Schritt "Sensoren"):
    s_climate.tick(millis());
    SensorReading c = s_climate.get();
    if (c.ok) {
        s_link.telemetry.airTempC[0]       = c.temperature;
        s_link.telemetry.airHumidityPct[0] = c.humidity;
    }
    s_link.telemetry.heaterTempC[0] = readHeaterTempC();

    controlLoop();   // entscheiden, zu heizen oder nicht
    applyHeater();   // auf Heizer anwenden + Schutz
    applyFan();      // auf Lüfter anwenden
}
```

Die Telemetrie-Felder (`heaterPower01`, `fanOn`) veröffentlicht die Fassade selbst – im Portal ist sichtbar, ob das Gerät gerade heißt und ob der Lüfter läuft.

## Befehle vom Portal

Das Portal sendet Starten und Stoppen der Wärmeregelung als Befehle. Der Handler wird mit der Methode `s_link.onCommand(name, callback)` registriert – **nach** `s_link.begin()`. Action-Befehle kommen mit dem Namen `invoke` und dem Feld `action` (Rolle aus Menü, z.B. `storage.start` / `storage.stop`).

Zum Parsen von JSON benötigen Sie Header `<ArduinoJson.h>` und `<string.h>` (für `strcmp`) – fügen Sie diese zu den anderen `#include` am Anfang der Datei hinzu. Der Handler selbst wird in `setup()` gesetzt:

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

- `storage.start` / `storage.stop` – die gleichen Rollen, die Sie im [Menü](06-menu.md) gesetzt haben; das Portal zeichnet Buttons danach.
- `iDryer::UnitMode::Storage` – der Modus der sanften Wärmeregelung. Dies ist der Hauptmodus des Schranks.
- `s_link.status.mode[0]` und `targetTempC[0]` zeigen den aktuellen Zustand der Kammer im Portal.
- `publishStatusNow()` aufrufen Sie nach jeder Statusänderung, damit das Portal es sofort sieht, ohne auf einen Timer zu warten.

!!! warning "Keine delay() im Handler"
    Der `onCommand`-Handler wird vom Netzwerk-Callback aufgerufen. Jede Blockierung darin reißt die MQTT-Sitzung. Ändern Sie Flags und Status, und führen Sie die eigentliche Arbeit in `loop()` durch.

## Vollständige `src/main.cpp` nach diesem Kapitel

Dies ist die endgültige, vollständige Datei des Geräts. Neue Zeilen gegenüber dem vorherigen Kapitel sind mit `// ← Kapitel 7` gekennzeichnet. Diese Datei liegt auch als fertiges Beispiel im Ordner `example/09-cabinet/` des Repositoriums und wird mit dem Befehl `pio run -e cabinet` erstellt.

??? note "Was vorher war – `src/main.cpp` nach Kapitel 6"

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
#include <ArduinoJson.h>          // ← Kapitel 7 (onCommand: JsonObjectConst)
#include <string.h>              // ← Kapitel 7 (strcmp)
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

// ← Kapitel 7: Schalter für Heizer und Lüfter
struct GpioOutput {
    int pin;
    void begin() { pinMode(pin, OUTPUT); digitalWrite(pin, LOW); }
    void on()    { digitalWrite(pin, HIGH); }
    void off()   { digitalWrite(pin, LOW); }
};
static GpioOutput myHeater{4};
static GpioOutput myFan{5};

// ← Kapitel 7: Logik der Temperaturregelung
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
    myHeater.begin();              // ← Kapitel 7
    myFan.begin();                 // ← Kapitel 7
    menu.initDefaults();
    s_link.begin();

    s_link.onCommand("invoke", [](JsonObjectConst data) {   // ← Kapitel 7
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

    controlLoop();   // ← Kapitel 7
    applyHeater();   // ← Kapitel 7
    applyFan();      // ← Kapitel 7
}
```

## Überprüfung des Ergebnisses

Nach diesem Schritt:

- Der Start vom Portal versetzt den Schrank in den Storage-Modus, das Gerät beginnt zu heizen;
- Die Lufttemperatur nähert sich dem Ziel an und bleibt im Hysterese-Bereich;
- Der Heizer bleibt nicht über `HEATER_MAX_C`;
- Lüfter und Heizleistung sind in der Telemetrie sichtbar;
- Das Stoppen vom Portal schaltet die Heizung aus und versetzt in den Idle-Modus.

## Was kommt als nächstes

Die Logik ist fertig. Es bleibt, das Gerät in das Gehäuse einzubauen und unter Strom zu überprüfen – [Montage und Überprüfung](08-assembly-and-check.md).
