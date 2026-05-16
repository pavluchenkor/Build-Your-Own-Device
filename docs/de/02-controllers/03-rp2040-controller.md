# RP2040 Controller

RP2040 ist ein Mikrocontroller von Raspberry Pi. Das bekannteste Board auf seiner Basis ist der Raspberry Pi Pico.

Für DIY-Peripherie rund um einen 3D-Drucker ist RP2040 eine der praktischsten Optionen: günstig, gut dokumentiert, arbeitet mit `3.3V`-Logik, lässt sich bequem über USB flashen und eignet sich hervorragend als zusätzlicher MCU für Klipper.

## Wofür RP2040 nützlich ist

RP2040 eignet sich gut für:

- zusätzliches I/O-Board für Klipper;
- Lüftersteuerung über MOSFET/Treiber;
- Auslesen von Thermistoren und einfachen Analogsensoren;
- Anschluss von OLED über I2C;
- Anschluss von RFID/NFC über SPI oder UART;
- Servoansteuerung mit PWM-Signal;
- einfaches eigenständiges Board ohne Wi-Fi;
- Testumgebung für Sensoren und Schnittstellen.

Wenn Netzwerkfähigkeit direkt benötigt wird, ist es einfacher, ESP32 oder Pico W zu nehmen. Für einen zusätzlichen kabelgebundenen MCU bei Klipper ist RP2040 oft die bequemere Wahl.

## Warum der Raspberry Pi Pico praktisch ist

Raspberry Pi Pico ist ein fertiges Entwicklerboard auf Basis von RP2040. Es verfügt bereits über USB, Flash-Speicher, Spannungsregler, einen `BOOTSEL`-Knopf und herausgeführte Pins.

Vorteile des Pico:

- günstiger Preis;
- gute Dokumentation und Pinout;
- USB zum Flashen und zur Kommunikation;
- viele GPIO;
- `3.3V`-Logik;
- 2 UART, 2 SPI, 2 I2C;
- 16 PWM-Kanäle;
- 3 ADC-Eingänge an den herausgeführten Pico-Pins;
- PIO für nicht standardmäßige Schnittstellen;
- komfortables UF2-Flashen über USB-Massenspeicher.

Für ein erstes Projekt ist es besser, einen Pico oder Pico H mit aufgelöteten Pins zu kaufen als einen nackten RP2040-Chip. Ein nackter Chip erfordert ein eigenes Board, Flash-Speicher, Stromversorgung, USB, Routing und Tests.

## BOOTSEL und UF2

Eine der Stärken des Pico ist ein einfacher Flash-Vorgang:

1. `BOOTSEL`-Knopf gedrückt halten.
2. USB mit dem Computer verbinden.
3. Das Board erscheint als USB-Laufwerk.
4. Die `.uf2`-Firmware-Datei kopieren.
5. Das Board startet mit der neuen Firmware neu.

Dies ist praktisch für MicroPython, CircuitPython, C/C++-Projekte und Klipper-Firmware. Für Einsteiger ist diese Methode in der Regel verständlicher als ST-Link, DFU oder ein separates USB-UART.

## RP2040 und Klipper

RP2040 ist ein guter Kandidat für einen zusätzlichen MCU in Klipper.

Typisches Schema:

![Raspberry Pi Pico mit RP2040-Chip](../../../img/02-controllers/03-rp2040-pico-photo.jpg)

*Quelle: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Raspberry_Pi_Pico_oblique.jpg), Phiarc, CC BY-SA 4.0*

Die Idee dahinter:

- Linux-Host mit Klipper bleibt der primäre Controller;
- Pico/RP2040 wird mit Klipper-MCU-Firmware geflasht;
- ein Haupt- oder zusätzlicher `[mcu]`-Abschnitt wird in `printer.cfg` eingetragen;
- RP2040-Pins können für Lüfter, Sensoren, PWM und andere Peripherie genutzt werden;
- Lasten werden weiterhin über MOSFET, Treiber, Relais oder SSR angeschlossen.

Das ist nützlich, wenn ein Teil der Peripherie in einen separaten Block ausgelagert werden soll: zum Beispiel Lüfter, Kamerasensoren, Filter, Beleuchtung, Taster, Endstops oder Serviceausgänge.

## GPIO und 3.3V-Logik

RP2040 arbeitet mit `3.3V`-Logik. Das bedeutet:

- kein `5V` an GPIO anlegen;
- für `5V`-Module kann ein Pegelwandler erforderlich sein;
- I2C-Pull-ups sollten auf `3.3V` gehen;
- GPIO darf keine Last direkt versorgen;
- Lüfter, LED-Streifen, Relais oder Heizung benötigen einen externen Schalter/Treiber.

Wenn ein Modul „Arduino-kompatibel" ist, bedeutet das nicht, dass es sicher für RP2040 ist. Eingangspegel und Pull-ups müssen geprüft werden.

## Stromversorgung

Pico wird in der Regel über USB oder den `VSYS`-Pin versorgt. Das Board verfügt über einen Regler zur Versorgung des Mikrocontrollers.

Praktische Regeln:

- keine Motoren, Servos und Relais vom `3V3`-Pin des Pico betreiben;
- separate Stromversorgung für Lasten verwenden;
- gemeinsame GND mit Niederspannungstreibern verbinden;
- prüfen, woher die Spannung für `VSYS` und USB kommt;
- den Strombedarf externer Module berücksichtigen, nicht nur des Pico selbst.

Wenn Pico beim Start eines Servos oder Lüfters zurücksetzt, liegt das Problem fast immer an Stromversorgung, Masse oder Störungen.

## ADC am Pico

Pico verfügt über ADC-Eingänge, die für einfache Analogaufgaben genutzt werden können:

- Thermistor über Spannungsteiler;
- Potentiometer;
- Lichtsensor;
- Messung niedriger Spannungen über Spannungsteiler.

Einschränkungen:

- ADC-Eingang darf die sichere GPIO-Spannung nicht überschreiten;
- für die Messung von `12V` oder `24V` ist ein Teiler und Schutz erforderlich;
- ein Thermistor benötigt den richtigen Widerstand, eine Tabelle/ein Modell und mechanischen Kontakt;
- ADC ersetzt kein Multimeter oder Industriemessgerät.

Bei Heizelementen gilt: ADC liest nur den Sensor. Die Heizsicherheit wird durch den Leistungsschalter, Firmware-Grenzen, Sicherung und unabhängigen Wärmeschutz gewährleistet.

## PIO einfach erklärt

PIO ist Programmable I/O. RP2040 besitzt kleine programmierbare Blöcke, die nicht standardmäßige Signale erzeugen oder lesen können, ohne den Hauptcode dauerhaft zu belasten.

Einsteiger müssen nicht mit PIO beginnen. Aber das ist einer der Gründe, warum RP2040 für Schnittstellen, Timing und nicht standardmäßige Peripherie beliebt ist.

Für ein einfaches iDryer-ähnliches Gerät reichen in der Regel reguläre GPIO, PWM, I2C, SPI, UART und ADC aus.

## Pico, Pico W und Pico 2

Es ist wichtig, die Boards nicht zu verwechseln:

- **Pico / Pico H** — klassisches RP2040-Board ohne Wi-Fi;
- **Pico W / Pico WH** — RP2040 mit Wi-Fi/Bluetooth-Modul auf dem Board;
- **Pico 2 / Pico 2 W** — neue Generation auf Basis von RP2350, das ist kein RP2040.

Wenn ein Artikel oder Projekt RP2040 nennt, ist damit in der Regel die erste Generation Pico oder ein kompatibles Board gemeint. Pico 2 ist konzeptionell ähnlich, aber ein anderer Mikrocontroller — Firmware- und Pin-Kompatibilität muss separat geprüft werden.

## Was vor dem Kauf zu prüfen ist

Vor dem Kauf eines RP2040-basierten Boards prüfen:

- ob es sich um ein originales Pico, Pico W oder einen Klon handelt;
- ob Pins aufgelötet sind;
- ob der benötigte USB-Stecker vorhanden ist;
- ob ein ordentliches Pinout vorliegt;
- welche GPIO verfügbar sind;
- ob Wi-Fi benötigt wird;
- ob das Board für Klipper-Firmware geeignet ist;
- wie Board und Lasten versorgt werden;
- ob genug ADC/PWM/I2C/SPI/UART für die Aufgabe vorhanden sind;
- ob im Gehäuse Platz für die Montage ist.

Bei der Planung eines Klipper-MCU die vorhandenen Anleitungen für das jeweilige Board und die Flash-Methode im Voraus prüfen.

## Häufige Fehler

- `5V` an RP2040-GPIO anlegen;
- Servo oder Relais über `3V3` betreiben;
- gemeinsame GND mit MOSFET/Treiber vergessen;
- Pico W mit einem normalen Pico verwechseln und verwendete Ressourcen/Wi-Fi-Stromverbrauch nicht berücksichtigen;
- Pico 2 kaufen und exaktes RP2040-Verhalten erwarten;
- `12V`/`24V` am ADC ohne Teiler messen;
- Heizelement direkt an einen Pin anschließen;
- RP2040 für Wi-Fi-Aufgaben wählen, obwohl ein normaler Pico kein Wi-Fi hat;
- Pinout eines bestimmten Klons nicht prüfen.

## Wesentliche Punkte

RP2040 und Raspberry Pi Pico sind eine starke Wahl für kabelgebundene DIY-Peripherie und zusätzliche MCU in Klipper. Das Board ist günstig, verständlich, gut dokumentiert und bequem zu flashen.

RP2040 ist jedoch ein `3.3V`-Mikrocontroller, kein Leistungscontroller. Lasten werden über Treiber, MOSFET, Relais oder SSR angeschlossen. Für Wi-Fi-Aufgaben wird Pico W oder ein anderer vernetzter Controller benötigt.

## Weiterführende Materialien

- [Raspberry Pi: RP2040 specifications](https://www.raspberrypi.com/products/rp2040/specifications/) — offizielle RP2040-Spezifikationen: CPU, SRAM, UART/SPI/I2C, PWM, USB und PIO.
- [Raspberry Pi Documentation: Pico-series microcontrollers](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html) — Unterschiede zwischen Pico, Pico W, Pico 2, GPIO, ADC, PWM und Board-Varianten.
- [RP2040 Datasheet](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf) — detaillierte technische Beschreibung des Mikrocontrollers, Peripherie, PIO, GPIO und ADC.
- [Raspberry Pi Pico Datasheet](https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf) — Dokumentation für das Pico-Board selbst: Stromversorgung, USB, herausgeführte GPIO und Board-Einschränkungen.
- [Raspberry Pi Documentation: C/C++ SDK - Your First Binaries](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html#your-first-binaries) — offizielles Beispiel für BOOTSEL, USB-Massenspeicher `RPI-RP2` und das Kopieren von UF2 auf Pico.
- [Klipper Configuration Reference](https://www.klipper3d.org/Config_Reference.html) — Kontext der RP2040-Unterstützung in Klipper und Einstellungen für Peripherie wie I2C.
