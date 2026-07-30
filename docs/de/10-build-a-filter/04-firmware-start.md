---
title: "Intelligenter Filter: Firmware-Start und Bindung ans Portal"
description: "Filter-Firmware-Gerüst auf idryer-core: Config für Gerätetyp unbekannt, Erste Inbetriebnahme, PIN-Bindung ans Nutzerkonto."
---

# Firmware-Start

Das Projekt-Gerüst wiederholt vollständig [das Kapitel aus dem Gehäuse-Beispiel](../09-build-a-device/04-firmware-start.md): PlatformIO, `secrets.h`, `idryer-core` in `lib/`, gleiches `platformio.ini` (ersetzen Sie nur die Umgebung auf `filter`). Hier – nur das, was anders ist.

## Config: Gerät unbekannten Typs

Der Filter hat weder einen Heizer noch einen Klima-Sensor aus dem Ökosystem-Wörterbuch. Von „Wörterbuch"-Fähigkeiten hat er nur einen Lüfter. In `src/main.cpp`:

```cpp
#include <iDryer.h>

static const iDryer::Config CFG = {
    .deviceType        = iDryer::DeviceType::Unknown, // Gerät unbekannten Typs
    .unitsCount        = 1,
    // Peripherie: vom Ökosystem-Wörterbuch haben wir nur einen Lüfter.
    .hasFan            = true,
    // Telemetrie-Veröffentlichungs-Perioden:
    .telemetryPeriodMs = 5000,
    .statusPeriodMs    = 10000,
    // Identifikation im Portal:
    .hardwareVersion   = "1.0",
    .firmwareVersion   = "0.1.0",
    .model             = "DIY Air Filter",
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

!!! note "DeviceType::Unknown – das ist normal"
    Der Typ `Unknown` bedeutet „das Portal kennt diese Geräteart nicht". Früher war das ein Problem: Das Portal hatte keine Karte für unbekannte Typen. Jetzt ist das der Standardweg: Das gesamte Gerät-Interface wird vom Card-Manifest beschrieben ([Kapitel 6](06-card.md)), und das Portal baut die Karte danach. Der Typ wird nur für iDryer-eigene Geräte benötigt, die fertige Karten haben.

Das Flag `hasFan = true` gibt uns kostenlos: das Feld `fanStatus` in der Telemetrie, die „Lüfter"-Zelle auf der Karte und die Entity im Manifest – alles aus dem Ökosystem-Wörterbuch.

## VOC-Sensor ist nicht in Config – und sollte nicht sein

Achten Sie darauf: In `Config` gibt es kein Flag „hasVoc". Das Wörterbuch `has*` beschreibt Peripherie, die das Ökosystem kennt. Ihren eigenen Sensor fügen Sie nicht über das Wörterbuch hinzu, sondern durch zwei andere Mechanismen: Sie schreiben seine Messwerte in die Telemetrie mit eigenem Feld und deklarieren ihn im Card-Manifest – das sind die nächsten zwei Kapitel. Das ist die Essenz des Ansatzes: Das Wörterbuch muss nicht für jedes neue Gerät erweitert werden.

## Erste Inbetriebnahme und Bindung

Das Verfahren unterscheidet sich nicht vom Gehäuse-Beispiel:

1. Programmieren Sie die Platine, öffnen Sie den Serial Monitor.
2. Das Gerät hebt Wi-Fi auf (Daten aus `secrets.h`), registriert sich und druckt die PIN:
   ```text
   [CLOUD] PIN: 1234567 (expires in 600s)
   ```
3. Auf dem [Portal](https://portal.idryer.org/) – „Gerät hinzufügen" → PIN eingeben.
4. Nach der Bindung erscheint `Device claimed!` im Log, das Gerät wechselt zu `Online`.

Detaillierte Analyse der Bindung, Wi-Fi-Fehler und Neu-Bindung – im [Kapitel des Gehäuse-Beispiels](../09-build-a-device/04-firmware-start.md).

Das Gerät ist bereits im Portal sichtbar, aber die Karte ist noch fast leer – wir haben ja noch keine Daten. Gehen wir den Sensor anschließen.
