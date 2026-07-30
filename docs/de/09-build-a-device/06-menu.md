---
title: "Gerätemenü aus YAML: Einstellungen in NVS und auf dem Portal"
description: "Wie man ein Gerätemenü auf idryer-core in menu.yaml beschreibt: Zieltemperatur und Hysterese werden in NVS gespeichert und durch Widgets auf dem iDryer-Portal angezeigt."
---

# Menü aus YAML

Das Menü ist ein Satz von Geräteeinstellungen: Zieltemperatur, Hysterese, Ventilator-Schwellwerte. Auf `idryer-core` wird das Menü in einer einzigen Datei `menu.yaml` beschrieben, und alles Übrige – C++-Strukturen, Speicherung im nichtflüchtigen Speicher (NVS) und Veröffentlichung auf dem Portal – wird automatisch generiert.

Dies ist einer der Schlüsselbausteine des Kerns. Sie schreiben keinen Code zur Speicherung von Einstellungen und erfinden keine Formate für das Portal – Sie zählen nur die Parameter in YAML auf.

## Warum ein Menü

Nach den vorherigen Schritten liest das Gerät Sensoren, aber alle Schwellwerte sind im Code hartcodiert. Das Menü löst drei Aufgaben gleichzeitig:

- **Speicherung**: Werte überstehen einen Neustart (NVS);
- **Fernverwaltung vom Portal**: jeder Parameter wird zu einem Widget (Schieberegler, Schalter);
- **Single Source of Truth**: eine Datei beschreibt Speicher und Schnittstelle.

## Wie es funktioniert

Eine Datei `menu.yaml` wird während des Builds durch einen Generator verarbeitet:

```text
menu.yaml → (pio run build) → C++-Dateien in src/menu/ + NVS + JSON für Portal
```

Ein Punkt mit dem Feld `role:` ist für das Portal sichtbar und wird als Widget angezeigt. Ein Punkt ohne `role:` ist privat, nur für die interne Gerätelogik.

!!! warning "Bearbeiten Sie nicht die generierten Dateien"
    Die Dateien `menu_state.*`, `menu_bindings.*`, `menu_ids.h` und andere werden vom Generator erstellt. Bearbeiten Sie nur `menu.yaml` und bauen Sie neu auf – andernfalls werden Ihre Änderungen überschrieben.

## Schritt 1. Kopieren Sie die Vorlage

Es gibt eine Menü-Vorlage in der Bibliothek. Kopieren Sie sie in Ihr Projekt:

```bash
mkdir -p src/menu
cp path/to/idryer-core/menu/menu.template.yaml src/menu/menu.yaml
```

## Schritt 2. Aktivieren Sie die Generierung beim Build

Kopieren Sie das Hook-Beispiel aus dem `iDryer-Storage`-Projekt (Sie können es unverändert verwenden):

```bash
mkdir -p extra_scripts
cp path/to/iDryer-Storage/extra_scripts/pre_gen_menu.py extra_scripts/pre_gen_menu.py
```

Fügen Sie dann in `platformio.ini` in die Sektion `[env:cabinet]` die Zeile `-Isrc/menu` ein (damit der Code `#include <menu_state.h>` sehen kann) und verbinden Sie den Hook über `extra_scripts`:

```ini
[env:cabinet]
; ... platform / board / lib_deps aus Kapitel 4 – ohne Änderungen ...

build_flags =
    -Isrc/menu                      ; ← hinzugefügt: Pfad zum generierten Menu
    -DIDRYER_API_BASE='"https://portal.idryer.org/api"'
    -DMQTT_BROKER='"mqtt.idryer.org"'
    -DMQTT_PORT=8883
    -DMQTT_USE_TLS=1

extra_scripts =                     ; ← hinzugefügt
    pre:extra_scripts/pre_gen_menu.py
```

Der Hook findet den Generator selbst unter `lib/idryer-core/menu/menu_gen.py`, daher muss die Bibliothek über `lib/` (Symlink oder Kopie) verbunden sein, wie in Kapitel 4 beschrieben.

## Schritt 3. Beschreiben Sie die Schrank-Parameter

Öffnen Sie `src/menu/menu.yaml`. Die Vorlage enthält bereits einen Root-Punkt `root` mit einem `children`-Array und Beispielparametern. Löschen Sie die Beispiele (`my_param`, `my_flag`, `my_mode_group`) und fügen Sie Ihre eigenen in `children` hinzu. Die letzten zwei Punkte – `units_count` und `language` – lassen Sie an Ort und Stelle: Dies ist ein fester Vertrag mit dem Portal.

Für einen Basis-Schrank reichen einige wenige Parameter.

Zieltemperatur für die Lagerung:

```yaml
- id: target_temp
  type: value
  role: storage.target_temperature   # macht den Parameter zu einem Widget auf dem Portal
  title: { ru: "ТЕМПЕРАТУРА", en: "TARGET TEMP" }
  unit:  { ru: "°C", en: "°C" }
  vtype: uint16
  min: 30
  max: 50
  step: 1
  bind: target_temp            # NVS-Schlüssel (≤ 15 Zeichen)
  persist: true
  scope: global
  default: 45
```

Hysterese (um wie viele Grad die Temperatur unter dem Sollwert abfallen kann, bevor die Heizung wieder anspringt):

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

!!! note "role: – eine abgeschlossene Liste"
    Der Wert `role:` kann nicht willkürlich erfunden werden – er muss aus der Liste `canonical_roles` des Kernvertrags stammen. Wenn keine passende Rolle existiert, stoppt der Build und zeigt die zulässigen Optionen an. Für einen Lagerungsschrank sind die Rollen der Familie `storage.*` geeignet: `storage.target_temperature`, `storage.target_humidity`, `storage.start`, `storage.stop`. Die vollständige Liste steht in der Kopfzeile von `menu.template.yaml`. Parameter ohne `role:` (wie Hysterese oben) funktionieren als interne Einstellungen: Sie werden in NVS gespeichert, aber nicht an das Portal übermittelt.

Einschränkungen, die nicht verletzt werden dürfen:

- `bind` – nicht länger als 15 Zeichen (NVS-Schlüssellimit);
- fügen Sie kein Feld `widget:` in `menu.yaml` ein – der Widget-Typ wird durch den Vertrag nach `role:` bestimmt.

!!! warning "Überprüfen Sie den Punkt ignore_external_cmd aus der Vorlage"
    In der Vorlage gibt es einen Punkt `ignore_external_cmd`, und sein `bind` beträgt 19 Zeichen, was das Limit von 15 überschreitet. Wenn Sie es so lassen, schlägt die Generierung fehl: `bind 'ignore_external_cmd' ... hat 19 Zeichen, Limit 15`. Entweder löschen Sie diesen Punkt oder verkürzen Sie `bind` auf `ign_ext_cmd` (wie in echten Produkten). Für einen Basis-Schrank können Sie ihn einfach löschen.

## Schritt 4. Erstellen Sie das Projekt und überprüfen Sie die Generierung

```bash
pio run -e cabinet
```

Beim Build wird der Pre-Hook Abhängigkeiten selbst installieren (einmalig) und C++-Menu-Dateien generieren. Wenn `menu.yaml` sich nicht geändert hat – wird die Generierung übersprungen (`up-to-date`).

Überprüfen Sie, dass die Generierung erfolgreich war. Im Build-Log erscheint eine Zeile über die Menu-Generierung, und im Ordner `src/menu/` befinden sich die generierten Dateien:

```text
src/menu/
├── menu.yaml          # Ihre Datei (Quelle)
├── menu_state.h/.cpp  # Menü-Objekt mit allen Parametern
├── menu_bindings.*    # Zugriff per bind + Speicherung in NVS
├── menu_ids.h
└── menu_meta.h        # und weitere
```

Wenn der Build mit einer Nachricht über eine unbekannte `role:` fehlschlägt – bedeutet das, dass die Rolle nicht aus der Liste `canonical_roles` stammt. Korrigieren Sie sie und bauen Sie neu auf. Bearbeiten Sie Dateien mit der Kennzeichnung autogen nicht von Hand.

## Schritt 5. Verbinden Sie das Menü mit dem Hauptprogramm

Um den Menü-Code zu verwenden, verbinden Sie zwei Dinge in `src/main.cpp`:

1. Der Header des generierten Menüs:

    ```cpp
    #include <menu_state.h>      // Menü-Objekt mit allen Parametern
    ```

2. Das Laden der Defaults in `setup()` – **vor** `s_link.begin()`:

    ```cpp
    menu.initDefaults();         // Standardwerte aus YAML setzen
    ```

Danach sind die Parameter über das globale Objekt `menu` zugänglich:

```cpp
uint16_t target = menu.target_temp;   // direkter Zugriff auf den Wert
```

Sie verwenden diese Werte in der Heizlogik im nächsten Schritt. Wenn der Benutzer den Parameter im Portal ändert, wendet der Kern automatisch den neuen Wert an und speichert ihn in NVS.

## Vollständiger `src/main.cpp` nach diesem Kapitel

Im Vergleich zum vorherigen Kapitel wurden nur zwei Zeilen hinzugefügt (markiert mit `// ← Kapitel 6`): Menü-Include und `menu.initDefaults()`.

??? note "Was war – `src/main.cpp` nach Kapitel 5"

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
#include <menu_state.h>           // ← Kapitel 6

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
    menu.initDefaults();           // ← Kapitel 6
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

## Ergebnis überprüfen

Nach der Firmware:

- im Portal auf der Gerätekarte erscheint die Einstellung der Zieltemperatur;
- Wertänderungen im Portal werden gespeichert und überstehen einen Neustart;
- interne Parameter (Hysterese) sind im Code über `menu` zugänglich.

## Was kommt als Nächstes

Die Einstellungen sind beschrieben und gespeichert. Jetzt verbinden wir sie mit der Hardware in [Heizungssteuerung](07-heating-control.md): Die Heizung hält die Zieltemperatur, der Ventilator schaltet sich basierend auf dem Schwellwert ein.
