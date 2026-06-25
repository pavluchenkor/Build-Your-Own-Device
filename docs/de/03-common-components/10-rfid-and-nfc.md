# RFID und NFC

RFID (Radio Frequency Identification) und NFC (Near Field Communication) sind kabellose Technologien für die Identifikation von Tags oder Karten.

Im Kontext von iDryern und 3D-Drucker-Peripheriegeräten werden sie verwendet, um Filament-Typen zu identifizieren, Material-Eigenschaften zu speichern oder Zugriff zu kontrollieren.

## RFID vs. NFC

**RFID:**

- Längere Reichweite (bis zu mehrere Meter);
- niedrigere Frequenzen (125 kHz LF, 13,56 MHz HF);
- verschiedene Protokolle;
- Tag muss nicht aktiviert sein (passive Tags);
- größere Reichweite, aber weniger Sicherheit.

**NFC:**

- Kürzere Reichweite (normalerweise 4-10 cm);
- Höhere Frequenz (13,56 MHz);
- ähnliche Technologie wie HF RFID;
- mehr Sicherheit und Verschlüsselung möglich;
- wird häufig für Zahlungen und Authentifizierung verwendet.

Für iDryer: NFC ist oft praktischer wegen der Näherung (Tag muss nah sein).

## Frequenzen und Standards

Häufige RFID/NFC-Frequenzen:

- 125 kHz LF (Low Frequency) - lange Reichweite, einfache Tags;
- 13,56 MHz HF (High Frequency) - mittlere Reichweite, höhere Kapazität;
- UHF (860-960 MHz) - lange Reichweite, passive Tags;
- 2,4 GHz ISM - aktive Tags, bessere Sicherheit.

NFC basiert normalerweise auf 13,56 MHz HF.

## Leser und Module

Typische Module für Mikrocontroller:

- **PN532:** NFC/RFID-Leser, I2C oder UART, 13,56 MHz;
- **RC522:** RFID-Leser, SPI, 13,56 MHz;
- **MFRC522:** Ähnlich RC522;
- **RDM6300:** UART-RFID-Leser, 125 kHz.

Für NFC: PN532 ist am verbreitetesten.
Für RFID: RC522/MFRC522 für HF, RDM6300 für LF.

## Anschluss und Schnittstelle

**PN532 (I2C oder UART):**

- I2C: GND, VCC, SCL, SDA;
- UART: GND, VCC, TX, RX;
- einfach mit Arduino oder ESP32 zu verbinden.

**RC522 (SPI):**

- GND, VCC, SCK, MOSI, MISO, CS, RST;
- schneller als I2C;
- benötigt 3,3V-Level (nicht 5V direkt).

## Tags und Karten

Typische NFC/RFID-Tags:

- ISO/IEC 14443A (Mifare Classic, Ultralight) - häufig;
- ISO/IEC 14443B - alternative;
- Verschiedene Speichergrößen: 64 B, 512 B, 4 kB, 32 kB.

Für Filament-ID: ein paar Bytes reichen aus (Material-Code, Temperatur, Hersteller).

## Verschlüsselung und Sicherheit

Einige Tags haben Verschlüsselung:

- Mifare Classic hat schwache Sicherheit (DES);
- Mifare Plus hat stärkere Verschlüsselung;
- Ultralight C hat AES;
- NFC Type 2 kann passwortgeschützt sein.

Für eine einfache Material-Identifikation ist einfache Verschlüsselung ausreichend.

## Firmware-Unterstützung

Arduino und ESP32:

- `MFRC522` Bibliothek für RC522;
- `PN532` Bibliothek für PN532;
- Lesen, Schreiben, Authentifizierung möglich.

Für Klipper:

- PN532-Unterstützung ist begrenzt;
- externe Firmware oder separate µController möglich.

## Praktischer Einsatz im Filament-Dryer

Typisches Szenario:

1. NFC-Tag auf Filament-Spule kleben;
2. Tag-Daten: Material (PLA/PETG/etc.), Temperatur, Trocknungszeit;
3. Leser beim Filament-Eingang;
4. Beim Einsetzen: Daten lesen, Programm automatisch einstellen;
5. Oder: Tag-ID als Referenz in der Materialdatenbank speichern.

## Was vor dem Kauf zu überprüfen ist

Vor dem Kauf überprüfen Sie:

- Leser-Typ (PN532 für NFC, RC522 für RFID HF);
- Schnittstelle (I2C, SPI, UART);
- Betriebsspannung (normalerweise 3,3V oder 5V);
- Reichweite;
- Verfügbarkeit von Bibliotheken für Ihr Entwicklungssystem;
- Preis und Verfügbarkeit von Tags/Karten;
- Sicherheit-Anforderungen;
- Betriebstemperaturbereich.

Für ein einfaches Projekt: PN532 I2C-Modul mit NFC-Tags.

## Typische Fehler

- Leser an falsche Spannung angeschlossen;
- Falsche Logikpegel (5V statt 3,3V);
- SPI-Pins vertauscht (SCK/MOSI/MISO);
- I2C-Adresse falsch konfiguriert (normalerweise 0x48 für PN532);
- Tag zu weit weg vom Leser;
- Antenne abgeschirmt oder blockiert;
- Firmware-Bibliothek nicht unterstützt;
- Speicherformat des Tags falsch interpretiert;
- Keine Authentifizierung für Mifare Classic (unverschlüsselt auslesen).

## Hauptpunkt

RFID/NFC-Tags können Material-Identifikation und Konfiguration automatisieren. PN532 ist praktisch für NFC-Anwendungen, RC522 für RFID. Überprüfen Sie Schnittstelle, Spannungspegel und Bibliotheks-Unterstützung. Für Filament: einfache Tag-Daten und Speicherung ausreichend.

## Referenzmaterialien

- [Adafruit: PN532 RFID/NFC Breakout Wiring](https://learn.adafruit.com/adafruit-pn532-rfid-nfc/breakout-wiring) - Anschluss, Firmware-Setup, Code-Beispiele.
- [SparkFun: RC522 RFID Reader](https://learn.sparkfun.com/tutorials/rc522-rfid-reader) - RC522 Anschluss, SPI-Schnittstelle, Mifare-Tag-Zugriff.
- [NXP PN532 Datasheet](https://www.nxp.com/products/wireless/nfc-readers-and-transceivers/nfc-readers-and-transceivers:PN532) - offizielle Spezifikationen.
- [NFC TagWriter by NXP](https://play.google.com/store/apps/details?id=com.nxp.nfc.tagwriter) - Anwendung zum Schreiben/Lesen von NFC-Tags auf Android-Phones.
