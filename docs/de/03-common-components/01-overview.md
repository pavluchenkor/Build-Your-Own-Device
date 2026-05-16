# Häufige Komponenten

Häufige Komponenten sind die Teile und Module, die Sie beim Zusammenbau eines iDryer-ähnlichen Geräts oder von 3D-Drucker-Peripheriegeräten am häufigsten antreffen.

Zweck dieses Abschnitts:

Dieser Abschnitt dient als Nachschlagewerk für Teile, die Sie während der Montage tatsächlich in den Händen halten.

Sie benötigen hier kein tiefes Elektronik-Wissen. Das Hauptziel ist, Ihnen zu helfen zu verstehen:

- was diese Komponente ist;
- warum Sie sie benötigen;
- wie sie typischerweise angeschlossen wird;
- wodurch Sie sie ersetzen können;
- welche Parameter beim Kauf wichtig sind;
- was beim ersten Anschluss am häufigsten kaputt geht.

Format jeder Seite:

- was es ist;
- wo es in iDryer und 3D-Drucker-Peripheriegeräten verwendet wird;
- wie eine typische Verbindung aussieht;
- wichtige Eigenschaften;
- typische Fehler;
- eine kurze Checkliste vor dem Kauf.

Geplante Dateien:

- `02-heaters.md` - Heizer: PTC, Silikonmatten, Patronen, 12V/24V/110-230V AC.
- `03-fans.md` - Lüfter: 2-polig, 3-polig, 4-polig PWM, Spannung, Strom, Geräusch, Luftstrom.
- `04-thermistors.md` - Thermistoren: NTC 100K, Nachschlagetabellen, Montage, Leerlauf-/Kurzschluss.
- `05-led-strips.md` - LED-Streifen: 5V/12V/24V, normale und adressierbare, Strom pro Meter.
- `06-servo-motors.md` - Servomotoren: Leistung, Signal, Winkel, Spitzenstrom.
- `07-load-cells.md` - Wägezellen: HX711, Kalibrierung, mechanische Montage.
- `08-oled-display.md` - OLED: I2C/SPI, Adresse, Stromversorgung, wenn nötig.
- `09-touchscreen.md` - TFT/Touch: UART/SPI/HDMI, Stromversorgung, Kompatibilität.
- `10-rfid-and-nfc.md` - RFID/NFC: Karten, Tags, Frequenzen, Verbindung.

## Referenzmaterialien

- [Klipper Configuration Reference](https://www.klipper3d.org/Config_Reference.html) - offizielle Klipper-Abschnitte zu Heizern, Lüftern, Temperatursensoren, Servomotoren und Displays in der Konfiguration.
- [DigiKey: Selecting A Fan](https://www.digikey.com/en/articles/selecting-a-fan) - praktische Lüfterauswahl nach Luftstrom, Gegendruck, Gehäusewiderstand und thermischer Aufgabe.
- [Adafruit: MOSFET Driver](https://learn.adafruit.com/adafruit-mosfet-driver) - warum hochwertige Lasten nicht direkt mit GPIO verbunden werden und warum Sie einen Schalter benötigen.
- [SparkFun: Load Cell Amplifier HX711 Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide) - Beispiel einer Wägezelle, HX711, Stromversorgung, Signaldraht und Kalibrierung.
- [Adafruit: PN532 RFID/NFC Breakout Wiring](https://learn.adafruit.com/adafruit-pn532-rfid-nfc/breakout-wiring) - Beispiel einer Komponente, bei der Sie vorher Stromversorgung, Logikpegel und gewählte Schnittstelle überprüfen müssen.

## Siehe auch

- [Heizer](02-heaters.md) - der riskanteste Ladentyp: Leistung, Temperatur, SSR/MOSFET und unabhängiger Schutz.
- [Lüfter](03-fans.md) - Luftstrom, Gegendruck, 2-polig/3-polig/4-polig und Stromversorgung.
- [Thermistoren](04-thermistors.md) - Temperatursensor als Grundlage für die Heizer-Rückmeldung.
- [Einen Lüfter anschließen](../05-practical-guides/01-connecting-a-fan.md) - praktisches Beispiel für den Komponentenanschluss durch einen Schalter.
- [Heizer- und SSR-Fehler](../07-common-mistakes/05-heater-and-ssr-errors.md) - häufige Fehler bei hochwertiger und Netzlasten.
