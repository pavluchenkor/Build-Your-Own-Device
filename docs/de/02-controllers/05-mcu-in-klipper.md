# MCU in Klipper

Klipper besteht aus zwei Hauptteilen:

- **Host** — ein Linux-Computer mit Klipper, zum Beispiel ein Raspberry Pi, Orange Pi, Mini-PC oder ein anderes Gerät;
- **MCU** — eine Mikrocontroller-Platine, die Pins physisch steuert.

Der Host trifft übergeordnete Entscheidungen, liest die Konfiguration, verarbeitet G-Code und plant Aktionen. Der MCU führt präzise Befehle auf der Hardware aus: schaltet Ausgänge, liest Eingänge, zählt Zeit, erzeugt PWM und meldet den Status zurück an den Host.

## Was ist ein MCU in Klipper

MCU steht für Micro-Controller Unit (Mikrocontroller-Einheit).

Im Kontext von Klipper ist es eine konkrete Platine:

- Haupt-3D-Druckerplatine;
- separate RP2040-Platine;
- separate STM32-Platine;
- CAN/Toolhead-Platine;
- zusätzliche I/O-Platine.

Ein MCU „denkt nicht wie der gesamte Drucker." Er führt Low-Level-Befehle aus, die der Host sendet. Diese Trennung macht Klipper flexibel: Man kann einen zweiten oder dritten MCU hinzufügen und dessen Pins in einer gemeinsamen Konfiguration verwenden.

## Wie es aussieht

Vereinfachtes Schema:

![Klipper-Host und mehrere MCUs](../../../img/02-controllers/05-klipper-host-mcu-architecture.svg)

Der Host kommuniziert mit dem MCU über USB, UART oder CAN. In der Klipper-Konfiguration erhält jeder MCU einen eigenen Abschnitt, und die Pins dieses MCU werden dann in den Einstellungen für Lüfter, Sensoren, Heizungen, Ausgänge und andere Module verwendet.

## Was der Host macht

Der Host:

- speichert und liest `printer.cfg`;
- nimmt G-Code und Benutzerbefehle entgegen;
- pflegt die übergeordnete Logik;
- plant Aktionen über die Zeit;
- synchronisiert die Kommunikation mit dem MCU;
- entscheidet, wann ein Lüfter, eine Heizung oder ein anderer Ausgang geschaltet wird;
- empfängt Messwerte und Status vom MCU.

Der Host legt selbst keinen Strom an einen Lüfter an und liest keinen Thermistor direkt aus, wenn diese Pins auf einer externen Platine liegen. Er teilt dem MCU mit, was zu tun ist.

## Was der MCU macht

Der MCU:

- steuert GPIO physisch;
- liest Eingänge und Sensoren;
- erzeugt PWM;
- führt Befehle zum richtigen Zeitpunkt aus;
- meldet Ergebnisse an den Host;
- wechselt bei Fehlern in den Abschaltzustand, wenn Firmware und Konfiguration entsprechend eingerichtet sind.

Wenn beispielsweise in der Konfiguration ein Lüfter an Pin `PA8` definiert ist, ändert der MCU mit diesem Pin dessen Zustand. Der Host sendet nur den Befehl.

## Was `[mcu]` bedeutet

In `printer.cfg` beschreibt der Abschnitt `[mcu]` den Mikrocontroller, mit dem Klipper sich verbinden soll.

Beispiel für USB/Seriell:

```ini
[mcu]
serial: /dev/serial/by-id/usb-Klipper_stm32f446xx_...
```

Für einen zusätzlichen MCU wird ein Name vergeben:

```ini
[mcu chamber]
serial: /dev/serial/by-id/usb-Klipper_rp2040_...
```

Danach können Pins des zusätzlichen MCU mit einem Präfix angegeben werden:

```ini
[temperature_sensor chamber_air]
sensor_type: Generic 3950
sensor_pin: chamber:gpio26

[fan_generic chamber_fan]
pin: chamber:gpio15
```

Die Logik ist einfach: `chamber:gpio15` bedeutet „Pin `gpio15` am MCU mit dem Namen `chamber`".

## Pin-Namen und Präfixe

Klipper verwendet Hardware-Pin-Namen.

Beispiele:

- für STM32: `PA4`, `PB0`, `PC13`;
- für RP2040: `gpio15`, `gpio26`;
- für Arduino/AVR kann es eigene Aliase geben.

Vor einem Pin-Namen können folgende Zeichen stehen:

- `!` — Logik invertieren;
- `^` — Pull-up aktivieren, wenn der MCU dies unterstützt;
- `~` — Pull-down aktivieren, wenn der MCU dies unterstützt.

Beispiel:

```ini
[gcode_button chamber_door]
pin: ^chamber:gpio12
```

Das ist kein „Klipper-Zauber", sondern eine konkrete Einstellung eines Eingangs-Pins an einem bestimmten MCU. Daher muss das Platinen-Pinout korrekt sein.

## Wozu ein zusätzlicher MCU benötigt wird

Ein zusätzlicher MCU ist nützlich, wenn Peripheriegeräte in einen separaten Block ausgelagert werden sollen.

Beispiele für iDryer-ähnliche Geräte:

- Temperatur- und Feuchtigkeitssensoren im Gehäuse;
- Zirkulationslüfter;
- Filterlüfter;
- Beleuchtung;
- Türtaster;
- Deckelsensor;
- Klappservo;
- separates Modul mit Wägezelle;
- zusätzliches OLED oder RFID;
- Notfall-Eingang, der praktischer in der Nähe des Geräts verlegt werden kann.

Dieser Ansatz ist sinnvoll, wenn das Gerät Teil eines Klipper-Systems sein soll und keine eigenständige WiFi-Box.

## MCU-Ansatz oder eigenständiger Controller

Es gibt zwei unterschiedliche Wege.

**MCU in Klipper**:

- das Gerät wird über `printer.cfg` gesteuert;
- Pins sind für Klipper sichtbar;
- vorhandene Abschnitte wie `fan_generic`, `temperature_sensor`, `heater_generic`, `output_pin` können verwendet werden;
- der Zustand ist in der Klipper-Oberfläche sichtbar;
- Kommunikation mit dem Host ist erforderlich.

**Eigenständiger Controller**:

- das Gerät trifft eigene Entscheidungen;
- kann WiFi, Weboberfläche, MQTT haben;
- muss nicht vom Drucker abhängen;
- erfordert eigene Firmware und Sicherheitslogik;
- verbindet sich nicht als regulärer `[mcu]` in Klipper.

ESP32 eignet sich oft gut für ein eigenständiges WiFi-Gerät. RP2040 und STM32 sind häufig praktischer als kabelgebundener MCU in Klipper.

## USB, UART und CAN

Die Kommunikation zwischen Host und MCU kann unterschiedlich sein.

**USB** — die häufigste und einfachste Option für eine oder zwei Platinen in der Nähe des Hosts. Praktisch für Pico, STM32-Platinen und viele Druckerplatinen.

**UART** — serielle Kommunikation über separate TX/RX-Pins. Kann bei einigen Platinen nützlich sein, erfordert jedoch sorgfältige Abstimmung von Pegel, Masse und Geschwindigkeit.

**CAN** — praktisch für entfernte Module, Toolhead-Platinen und eine stabilere kabelgebundene Architektur. CAN erfordert jedoch einen unterstützten Mikrocontroller, einen CAN-Transceiver, einen ordnungsgemäßen Bus, Abschlusswiderstände und die Einrichtung einer Linux-Schnittstelle.

Für einen ersten zusätzlichen Controller ist USB in der Regel einfacher. CAN ist sinnvoll, wenn es einen echten Grund gibt: längere Verkabelung, mehrere Knoten, Toolhead-Platine oder vorhandene CAN-Infrastruktur.

## MCU schützt nicht den Leistungsteil

Wichtig: Das Hinzufügen eines MCU macht eine Last nicht sicher.

Wenn ein MCU einen Lüfter, eine Heizung oder ein SSR steuert, wird dennoch benötigt:

- korrekter Leistungsschalter;
- geeignetes Netzteil;
- Leitungen und Klemmen für den Strom;
- Sicherung;
- unabhängiger Thermoschutz für die Heizung;
- sicheres Gehäuse;
- Überprüfung des Verhaltens bei Kommunikationsverlust oder ausgeschaltetem Host.

Wenn der Host die Kommunikation mit dem MCU verliert, kann Klipper das System herunterfahren, aber das ersetzt keinen Hardware-Schutz. Eine Heizung muss so ausgelegt sein, dass ein einzelner Ausfall von Firmware, Sensor, SSR oder Kommunikation nicht zu einem unsicheren Zustand führt.

## Was vor der Auswahl eines MCU zu prüfen ist

Vor dem Kauf einer Platine für einen Klipper-MCU prüfen:

- ob der Mikrocontroller von Klipper unterstützt wird;
- ob es eine fertige Konfiguration oder Anleitung für die Platine gibt;
- welche Kommunikationsmethode benötigt wird: USB, UART oder CAN;
- wie die Platine geflasht wird;
- ob genügend GPIO, ADC, PWM, I2C, SPI, UART vorhanden sind;
- welche Pins tatsächlich herausgeführt sind;
- was die GPIO-Logik ist: in der Regel `3.3V`;
- ob Treiber/MOSFET/SSR für Lasten benötigt werden;
- ob Dokumentation zu Stromversorgung und Pinout vorhanden ist;
- was passiert, wenn die Kommunikation mit dem MCU verloren geht.

Für einen ersten zusätzlichen MCU ist es in der Regel einfacher, RP2040/Pico oder eine bekannte STM32-Platine mit klarer Anleitung zu wählen.

## Häufige Fehler

- anzunehmen, der MCU enthält die gesamte Klipper-Logik;
- Host und MCU zu verwechseln;
- `[mcu chamber]` hinzuzufügen, aber dann Pins ohne das Präfix `chamber:` anzugeben;
- einen Pin aus einem fremden Pinout zu übernehmen;
- beim `make menuconfig` den falschen Mikrocontroller-Typ zu flashen;
- Bootloader-Offset und Platinen-Flash-Methode nicht zu prüfen;
- ein instabiles USB-Kabel zu verwenden;
- `5V` an einen `3.3V`-Eingang anzuschließen;
- eine Last direkt über GPIO zu versorgen;
- anzunehmen, ein Software-Shutdown ersetzt eine Sicherung und Thermosicherung.

## Kernpunkte

In Klipper ist ein MCU eine Platine, die Pins physisch steuert, während der Host die Arbeit plant und koordiniert. Ein zusätzlicher MCU ermöglicht es, das System zu erweitern und Peripheriegeräte näher am Gerät zu platzieren.

Für iDryer-ähnliche Aufgaben ist das praktisch für Lüfter, Sensoren, Filter, Beleuchtung, Taster und einige Aktoren. Der Leistungsteil und die Heizsicherheit bleiben jedoch eine separate Hardware-Aufgabe.

## Verwandte Materialien

- [Klipper: Codeübersicht](https://www.klipper3d.org/Code_Overview.html) — Klipper-Architektur, Aufteilung von Host-Code und Mikrocontroller-Code, Zeitmodell und GPIO.
- [Klipper: Konfigurationsreferenz – Mikrocontroller-Konfiguration](https://www.klipper3d.org/Config_Reference.html#micro-controller-configuration) — `[mcu]`, zusätzliches `[mcu name]`, Pin-Namensformat und Präfixe.
- [Klipper: Installation – Mikrocontroller bauen und flashen](https://www.klipper3d.org/Installation.html#building-and-flashing-the-micro-controller) — allgemeiner Ablauf von `make menuconfig`, Bauen und Flashen des MCU.
- [Klipper: Bootloader](https://www.klipper3d.org/Bootloaders.html) — warum verschiedene Platinen unterschiedliche Flash-Methoden haben und warum der Bootloader wichtig ist.
- [Klipper: CANBUS](https://www.klipper3d.org/CANBUS.html) — CAN-Kommunikation, `canbus_uuid`, USB-zu-CAN-Bridge und Hardware-Anforderungen.
