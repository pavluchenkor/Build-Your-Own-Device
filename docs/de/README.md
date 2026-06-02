---
title: "Filamenttrockner selbst bauen"
description: "Praktische Dokumentation zum Bau eines Filamenttrockners, einer beheizten Kammer und von Zusatzmodulen für 3D-Drucker: Elektronik, Heizung, Luftstrom, Gehäuse und Sicherheit."
---

# Filamenttrockner selbst bauen

Dieser Abschnitt hilft dir, einen eigenen Filamenttrockner oder eine aktive beheizte Kammer für einen 3D-Drucker zu planen und zu bauen. Er behandelt Elektronikgrundlagen, Controller-Auswahl, Heizungen, Lüfter, Sensoren, Gehäusedesign und typische Fehler vor dem ersten Aufbau.

Dieser Abschnitt behandelt alles was Sie brauchen um einen Filament-Trockner von Grund auf zu bauen — von Elektronik-Grundlagen bis zu praktischen Verdrahtungs-Leitfäden.

Keine bisherige Elektronik-Erfahrung benötigt. Jeder Artikel konzentriert sich auf ein spezifisches Thema und verbindet sich zu verwandtem Material.

## Inhalte

### 00. Start hier

| Datei | Was ist drin |
|---|---|
| `00-start-here/01-introduction.md` | Für wen dieser Abschnitt ist, wie man ihn liest und warum der Weg von einfach zu komplex geht. |

### 01. Elektronik-Grundlagen

| Datei | Was ist drin |
|---|---|
| `01-electronics-basics/01-load-calculation-24v.md` | Spannung, Strom, Kraft, Ohm-Gesetz, 24V Last-Berechnung, Abwertung, Datenblatt-Lesen. |
| `01-electronics-basics/02-mosfet-module.md` | MOSFET als elektronischer Schalter, vorgefertigte Module, DC-Lasten, Lüfter, LED-Streifen, Heizer. |
| `01-electronics-basics/03-triac.md` | TRIAC für AC-Lasten, Optokoppler, galvanische Isolation, Snubber-Schaltung, Wärme und Kühlkörper. |
| `01-electronics-basics/04-solid-state-relay-ssr.md` | SSR, Unterschiede von mechanischen Relais, AC/DC Varianten, Kühlkörper, Spannung und Strom-Auswahl. |

### 02. Controller

| Datei | Was ist drin |
|---|---|
| `02-controllers/00-how-to-choose-controller.md` | Controller-Auswahl-Tabelle nach Aufgabe. Zuerst lesen. |
| `02-controllers/01-esp32-controller.md` | ESP32, Wi-Fi/Bluetooth, warum es nicht ideal als Klipper MCU ist. |
| `02-controllers/02-arduino-controller.md` | Arduino als Lernplattform, Einschränkungen für echte Geräte und Klipper. |
| `02-controllers/03-rp2040-controller.md` | RP2040/Pico, einfaches Flashen via BOOTSEL, Nutzung als Klipper MCU. |
| `02-controllers/04-stm32-controllers.md` | STM32 Familie, Drucker-Boards, DFU/SWD/ST-Link, Komplexität der Auswahl und Flashen. |
| `02-controllers/05-mcu-in-klipper.md` | Was ein MCU ist, Klipper Host-Rolle, Pin-Konfiguration, G-Code Planung. |
| `02-controllers/06-uart-interface.md` | UART serielle Schnittstelle, RX/TX Überkreuzung, GND, 3.3V/5V Pegel. |
| `02-controllers/07-i2c-interface.md` | I2C Bus, SDA/SCL, Geräte-Adressen, Displays, Sensoren, kurze Leitungen. |
| `02-controllers/08-spi-interface.md` | SPI, MOSI/MISO/SCK/CS, Displays, RFID, schneller Datenaustausch, separater CS pro Gerät. |
| `02-controllers/09-can-interface.md` | CAN Bus, Differenzpaar, Werkzeugkopf-Boards, Abschlüsse, Rausch-Immunität. |
| `02-controllers/10-usb-uart-adapters.md` | USB-UART Adapter, Flashen, serielle Logs, RX/TX, Spannungs-Pegel, häufige Fehler. |
| `02-controllers/11-flashing-controller.md` | Was Flashen bedeutet, UF2/USB/DFU/ST-Link Methoden, Klipper Bau-Prozess. |

### 03. Häufige Komponenten

| Datei | Was ist drin |
|---|---|
| `03-common-components/01-overview.md` | Was Komponenten sind, Liste von Themen und ihre Rolle im Gerät. |
| `03-common-components/02-heaters.md` | Heizer 12V/24V/110–230V AC, Kraft, Temperatursensor, Sicherheit. |
| `03-common-components/03-fans.md` | Luftstrom, statischer Druck, Lärmm, 2-Pin/3-Pin/4-Pin Typen. |
| `03-common-components/04-thermistors.md` | Thermistoren, thermischer Kontakt, thermische Paste/Hülse, PID Rückmeldung. |
| `03-common-components/05-led-strips.md` | LED-Streifen 5V/12V/24V, Strom pro Meter, MOSFET, Kraft, adressierbare Streifen. |
| `03-common-components/06-servo-motors.md` | Servo-Motoren, Kraft, Signal, Spitzenstrom, separate Stromversorgung. |
| `03-common-components/07-load-cells.md` | Last-Zellen, HX711 Verstärker, Montage-Mechanik, Kalibrierung. |
| `03-common-components/08-oled-display.md` | OLED Displays, I2C/SPI, Adresse, Kraft, wann ein Display nutzen. |
| `03-common-components/09-touchscreen.md` | TFT/Touch Bildschirme, UART/SPI/HDMI, Kraft, Kompatibilität. |
| `03-common-components/10-rfid-and-nfc.md` | RFID/NFC, Karten, Tags, Frequenzen, Verdrahtung, Anwendungs-Fälle. |

### 04. Thermische Physik und Materialien

| Datei | Was ist drin |
|---|---|
| `04-thermal-physics-and-materials/01-overview.md` | Warum ein Abschnitt über Wärme, Materialien, Gehäuse, Isolation und Sicherheit. |
| `04-thermal-physics-and-materials/02-thermal-conductivity.md` | Wärme-Leitfähigkeit, Isolation, Wärme-Brücken, Material-Temperatur-Bewertungen. |
| `04-thermal-physics-and-materials/03-material-safety.md` | Entzündlichkeit, Dämpfe, Toxizität, PIR/XPS/EPS, Sicherheits-Datenblätter (SDS/MSDS). |
| `04-thermal-physics-and-materials/04-convection-and-airflow.md` | Konvektion, 100W Heizer mit kein Luftstrom vs. schwach vs. richtig Luftstrom, Wärme-Transfer. |

### 05. Werkzeuge (war 04 in EN Ordner-Struktur — Hinweis: Ordner ist `05-tools/`)

| Datei | Was ist drin |
|---|---|
| `05-tools/01-overview.md` | Werkzeug-Liste: Multimeter, USB-TTL, Löten, Krimpen, ST-Link, Oszilloskop. |
| `05-tools/02-multimeter.md` | Spannung, Kontinuität, Widerstand, Mess-Sicherheit. |
| `05-tools/03-usb-ttl-adapter.md` | USB-TTL/USB-UART, Flashen, serielle Logs, RX/TX, Spannungs-Pegel. |
| `05-tools/04-soldering.md` | Löt-Drähte, JST Steckverbinder, Thermistoren, häufige Fehler. |
| `05-tools/05-crimping-connectors.md` | Krimpen von Anschlüssen und Steckverbindern, Kontakt-Qualität, schlechte Krimpverbindungen. |
| `05-tools/06-st-link.md` | ST-Link, STM32, SWD Schnittstelle, Wiederherstellung nach fehlgeschlagenem Flash. |
| `05-tools/07-oscilloscope.md` | PWM, UART, Lärmm, Spannungs-Sag, Netzspannung-Sicherheit, Frequenz-Messung. |

### 06. Praktische Leitfäden (Ordner: `06-practical-guides/`)

| Datei | Was ist drin |
|---|---|
| `06-practical-guides/01-connecting-fan.md` | Lüfter-Verdrahtung, Spannung, Controller-seitige Steuerung, Lärmm. |
| `06-practical-guides/02-checking-thermistor.md` | Thermistor-Überprüfung mit Multimeter, Widerstand, Verdrahtung, Firmware-Ablesungen. |
| `06-practical-guides/03-connecting-servo.md` | Servo-Stromversorgung, Signal-Leitung, Spitzenstrom, Controller-Neustarts. |
| `06-practical-guides/04-connecting-load-cell.md` | Last-Zelle, HX711 Verstärker, Kraft, Signal-Drähte, Kalibrierung. |
| `06-practical-guides/05-connecting-rfid-reader.md` | RFID-Lesegerät, Kraft, SPI/UART/I2C, häufige Fehler. |

### 07. 3D-Druck (Ordner: `07-3d-printing/`)

| Datei | Was ist drin |
|---|---|
| `07-3d-printing/01-overview.md` | Warum ein Abschnitt auf gedruckten Teilen, Gehäuse, Kanälen und Mounts. |
| `07-3d-printing/02-what-is-stl.md` | STL Format, Begrenzungen, warum eine STL Datei nicht genug ist für Montage. |
| `07-3d-printing/03-materials-petg-abs-asa.md` | PETG, ABS, ASA — wo nutzen, Grenzen in Nähe Wärmequellen. |
| `07-3d-printing/04-heat-resistant-materials.md` | Materialien für Teile in der Nähe von Wärme, Verformung, Temperatur-Spielraum. |
| `07-3d-printing/05-enclosure-design.md` | Gehäuse-Design, Belüftung, Mounts, Abstand vom Heizer, Service-Zugang. |
| `07-3d-printing/06-why-pla-is-risky.md` | PLA in der Nähe von Wärme-Quellen, Erweichung, Verformung, Gehäuse-Fehler-Risiko. |

### 08. Häufige Fehler (Ordner: `08-common-mistakes/`)

| Datei | Was ist drin |
|---|---|
| `08-common-mistakes/01-overview.md` | Liste von typischen Fehlern und die Logik hinter dem Diagnose-Abschnitt. |
| `08-common-mistakes/02-power-mistakes.md` | Schwache Stromversorgungen, Spannungs-Sag, Strom-Kopfraum, schlechte Anschlüsse. |
| `08-common-mistakes/03-wiring-mistakes.md` | Getauschte Drähte, fehlende Erdung, RX/TX, dünne Drähte, schlechte Verbindungen. |
| `08-common-mistakes/04-controller-mistakes.md` | 3.3V/5V Niveaus nicht passen, falsches Board, Firmware, Signal-Pegel. |
| `08-common-mistakes/05-heater-ssr-mistakes.md` | Heizer, SSR, 110–230V AC, Kühlkörper, falscher Relais-Typ. |
| `08-common-mistakes/06-diagnostic-checklist.md` | Schnelle Schritt-für-Schritt Geräte-Diagnose-Abfolge. |
