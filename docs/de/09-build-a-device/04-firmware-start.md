---
title: "Firmware-Start auf idryer-core: Erststart und Portal-Bindung"
description: "PlatformIO-Projekt auf der idryer-core-Bibliothek erstellen: platformio.ini, secrets.h, Device-Konfiguration, erste Firmware für ESP32 und Bindung zum iDryer-Portal."
---

# Firmware-Start auf dem Kern

Auf dieser Seite erstellen Sie ein Firmware-Projekt, bringen den ESP32 in den Online-Status auf dem Portal und prüfen, dass der Netzwerk-Teil funktioniert. Sensoren und Heizlogik werden in den nächsten Schritten hinzugefügt.

Der Ansatz basiert auf der Fassade `iDryer::Link`. Sie beschreiben das Gerät mit einer einzigen Struktur `iDryer::Config`, rufen `link.begin()` und `link.loop()` auf — der Kern kümmert sich selbst um die gesamte Netzwerkverbindung.

## 1. Bereiten Sie die Tools vor

Sie benötigen:

- VS Code mit PlatformIO-Erweiterung;
- USB-Kabel;
- Wi-Fi-Netzwerk `2.4 GHz` (ESP32 funktioniert nicht mit reinen `5 GHz`-Netzwerken).

Was eine Controller-Firmware ist und wie sie auf die Platine gelangt — [Controller-Firmware](../02-controllers/11-flashing-controller.md).

## 2. Erstellen Sie ein Projekt

In PlatformIO ist ein Projekt ein Ordner mit einer festen Struktur. Erstellen Sie einen Projektordner (z. B. `my-cabinet`) und öffnen Sie ihn in VS Code. Darin sollten sich diese Dateien befinden:

```text
my-cabinet/
├── platformio.ini        # Buildeinstellungen (wird in Schritt 4 ausgefüllt)
├── include/
│   └── secrets.h         # Wi-Fi-Login und Passwort (Schritt 3)
├── lib/
│   └── idryer-core/      # Kern-Bibliothek (Symlink oder Kopie)
└── src/
    └── main.cpp          # Gerätecode: Config + setup() + loop()
```

Alle unten stehenden Code-Fragmente gehen in diese Dateien — jeder Schritt gibt an, in welche. Erstellen Sie die Ordner `include/`, `lib/` und `src/` manuell, wenn sie nicht vorhanden sind.

Legen Sie die Bibliothek `idryer-core` in `lib/` — PlatformIO findet Bibliotheken dort automatisch. Das Einfachste ist, einen Symlink zur heruntergeladenen Bibliothek zu erstellen:

```bash
ln -s /path/to/idryer-core lib/idryer-core
```

Dies ist auch für die Menü-Generierung erforderlich (Kapitel 6) — der Hook sucht den Generator im `lib/idryer-core/`-Verzeichnis.

## 3. Erstellen Sie secrets.h

Kopieren Sie das Beispiel `secrets.h.example` aus der Bibliothek in `include/secrets.h` Ihres Projekts und geben Sie die Daten Ihres Netzwerks an:

```cpp
#define WIFI_SSID      "your-ssid"
#define WIFI_PASSWORD  "your-password"
```

Fügen Sie `include/secrets.h` zu `.gitignore` hinzu, damit das Passwort nicht in das Repository gelangt.

## 4. Konfigurieren Sie platformio.ini

Füllen Sie `platformio.ini` im Projektverzeichnis aus:

```ini
[env:cabinet]
platform    = espressif32
framework   = arduino
board       = esp32-c3-devkitm-1

lib_deps =
    bblanchon/ArduinoJson @ ^6.21.0
    knolleary/PubSubClient
    densaugeo/base64 @ ^1.4.0
    links2004/WebSockets @ ^2.4.0
    https://github.com/jnthas/Improv-WiFi-Library.git

build_flags =
    -DIDRYER_API_BASE='"https://portal.idryer.org/api"'
    -DMQTT_BROKER='"mqtt.idryer.org"'
    -DMQTT_PORT=8883
    -DMQTT_USE_TLS=1
```

Ersetzen Sie `board` durch Ihre Platine (z. B. `esp32-s3-devkitc-1`). Sie müssen `idryer-core` nicht in `lib_deps` angeben — sie liegt in `lib/` (Schritt 2).

!!! note "Wozu all diese Abhängigkeiten"
    `ArduinoJson`, `PubSubClient`, `base64`, `WebSockets` und `Improv-WiFi-Library` werden von der `idryer-core`-Bibliothek selbst benötigt (MQTT, WebSocket-Zugriff über LAN, Wi-Fi-Provisioning). Ohne eine davon schlägt der Build mit einem Fehler wie `... .h: No such file` fehl. Die Flags `MQTT_BROKER` und `MQTT_PORT` sind ebenfalls erforderlich — ohne sie wird der Kern nicht kompiliert (`'MQTT_BROKER' was not declared`).

## 5. Beschreiben Sie das Gerät in Config

Alles Weitere geschieht in einer Datei — `src/main.cpp`. Öffnen Sie sie und schreiben Sie den Code aus diesem und den folgenden Schritten.

`iDryer::Config` ist der Datenblatt des Geräts. Die Flags `has*` teilen dem Portal mit, was das Gerät hat, und bestimmen, welche Telemetrie-Felder veröffentlicht werden.

Für einen beheizten Schrank am Anfang von `src/main.cpp`

```cpp
#include <iDryer.h>

static const iDryer::Config CFG = {
    .deviceType        = iDryer::DeviceType::Dryer,
    .unitsCount        = 1,
    // Peripherie:
    .hasHeater         = true,    // gesteuerter Heizer
    .hasFan            = true,    // Lüfter
    .hasAirTemp        = true,    // Lufttemperatur (SHT31)
    .hasAirHumidity    = true,    // Luftfeuchtigkeit (SHT31)
    .hasHeaterTemp     = true,    // Heizer-Temperatur (Thermistor)
    // Auto-Veröffentlichungsperioden:
    .telemetryPeriodMs = 5000,
    .statusPeriodMs    = 10000,
    // Identifizierung auf dem Portal:
    .hardwareVersion   = "1.0",
    .firmwareVersion   = "0.1.0",
    .model             = "DIY Storage Cabinet",
};

static iDryer::Link s_link(CFG);
```

!!! note "Die Flags has* sind ein Vertrag mit dem Portal"
    Ein Telemetrie-Feld, dessen entsprechendes Flag `false` ist, wird nicht veröffentlicht. Beispielsweise wird die Luftfeuchtigkeit ohne `hasAirHumidity = true` nicht in die Cloud gelangen, auch wenn Sie sie in den Code schreiben. Aktivieren Sie nur das, was physisch im Gerät vorhanden ist.

Die Liste der Komponenten und Flags finden Sie unter [Systemzusammensetzung](02-bom.md).

## 6. Minimale Hauptfunktion

Fügen Sie in derselben Datei nach dem `Config`-Block die Funktionen `setup()` und `loop()` hinzu. Für den ersten Start reicht es aus, den Link zu initialisieren und ihn in `loop()` zu drehen:

```cpp
void setup() {
    Serial.begin(115200);
    s_link.begin();
}

void loop() {
    s_link.loop();
}
```

Dies reicht aus, damit sich das Gerät mit Wi-Fi verbindet und zum Portal hochfährt. Sensoren werden in Schritt [Sensoren](05-sensors.md) hinzugefügt.

### Vollständiger `src/main.cpp` nach diesem Kapitel

Nehmen Sie beide Blöcke von oben in eine Datei — das ist die gesamte `src/main.cpp` bei diesem Schritt:

```cpp
#include <iDryer.h>

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

void setup() {
    Serial.begin(115200);
    s_link.begin();
}

void loop() {
    s_link.loop();
}
```

Das vorherige Kapitel zeigt, **was hinzugefügt werden soll** und den **vollständigen `src/main.cpp` nach den Änderungen**, damit Sie immer das große Ganze sehen, nicht verstreute Fragmente.

## 7. Flashen Sie

```bash
pio run -e cabinet -t upload
```

## 8. Öffnen Sie Serial Monitor

```bash
pio device monitor -b 115200
```

Erwartete Sequenz im Log:

```text
[CLOUD] Connecting to WiFi...
[CLOUD] WiFi connected, IP: 192.168.1.42
[CLOUD] Provisioning device...
[CLOUD] PIN: 1234567 (expires in 600s)
```

Wenn das Gerät bei der Zeile `PIN: ...` stehen bleibt — das ist normal. Gehen Sie zur Bindung über.

## 9. Binden Sie das Gerät an das Portal

1. Öffnen Sie [portal.idryer.org](https://portal.idryer.org/).
2. Gehen Sie zum Bereich **Add device**.
3. Geben Sie die PIN aus dem Serial Monitor ein.

Nach der Bindung wechselt das Gerät in den Status `Online`. Im Log wird angezeigt:

```text
[CLOUD] Device claimed!
[CLOUD] MQTT connected!
```

## Überprüfung des Ergebnisses

Bei diesem Schritt sollte das Gerät online auf dem Portal sein. Es gibt noch keine Sensordaten — das ist zu erwarten. Wenn sich das Gerät nicht verbindet:

- Prüfen Sie, dass das `2.4 GHz`-Netzwerk und das Passwort in `secrets.h` korrekt sind;
- Überprüfen Sie die ESP32-Stromversorgung (Spannungseinbrüche beim Start des Wi-Fi sind eine häufige Ursache für Neustarts);
- Siehe [Stromversorgungsfehler](../08-common-mistakes/02-power-mistakes.md) und [Controller-Fehler](../08-common-mistakes/04-controller-mistakes.md).

## Was kommt als Nächstes

Der Netzwerk-Teil funktioniert. Gehen Sie zu [Sensoren](05-sensors.md): Wir verbinden SHT31 und Thermistor und sehen deren Daten auf dem Portal.
