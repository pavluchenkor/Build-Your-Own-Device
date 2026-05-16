# OLED-Bildschirm

Ein OLED-Bildschirm ist ein kleines hochkontrast Display, das über eine digitale Schnittstelle wie I2C oder SPI gesteuert wird.

Typische Größen: 128x64 oder 128x32 Pixel. Sie sind energieeffizient, haben keine Hintergrundbeleuchtung-Rauschen und funktionieren bei verschiedenen Winkeln.

## Wo es verwendet wird

In iDryern und ähnlichen Geräten:

- Anzeige des Status (Temperatur, Zeit, Feuchte);
- Menüsystem für Benutzereinstellungen;
- Fehlermedl dungen;
- Echtzeit-Daten wie Gewicht oder Luftstrom;
- einfache Visualisierung des Prozess.

Nicht ideal für sehr heiße Bereiche direkt neben Heizern.

## I2C oder SPI

OLED-Bildschirme verwenden normalerweise eine dieser Schnittstellen:

**I2C:**

- meist 4 Pins: GND, VCC, SCL, SDA;
- einfach zu implementieren;
- langsamere Datenrate als SPI;
- möglich, mehrere Geräte am selben Bus zu haben;
- I2C-Adresse: normalerweise `0x3C` oder `0x3D`.

**SPI:**

- normalerweise 5-7 Pins: GND, VCC, CLK, MOSI, CS, und optional RESET;
- höhere Datenrate;
- weniger Interferenz;
- jedes Gerät braucht eigenes Chip-Select.

Für einfache Anwendungen ist I2C praktisch. Für hohe Datenrate oder wenn Sie SPI für andere Geräte benötigen, kann SPI besser sein.

## Spannungsversorgung

Die meisten OLED-Bildschirme arbeiten mit `3.3V` oder `5V`.

Überprüfen Sie:

- Betriebsspannung;
- Stromverbrauch (normalerweise `20-50 mA`);
- ob der Display ein Regler hat oder externe Stromversorgung braucht;
- Logikpegel (3.3V oder 5V).

Bei 3.3V-Displays von 5V-Systemen können Level-Shifter nötig sein.

## Display-Größe und Auflösung

Typische OLED-Bildschirme:

- 128x64 - für detaillierte Informationen;
- 128x32 - für einfache Anzeige;
- andere Größen sind seltener.

Kleinere Bildschirme brauchen weniger Speicher und Verarbeitungsleistung.

## Montage und Sichtlinie

OLED-Bildschirme brauchen:

- klare Sichtlinie zum Benutzer;
- Winkel von etwa 0-60° für gute Sichtbarkeit;
- Schutz vor Staub und Feuchtigkeit, wenn im Freien;
- Schutz vor direkter Sonneneinstrahlung (kann ausgewaschen aussehen).

Eine leichte Neigung oder ein Fenster zum Schutz kann helfen.

## Firmware-Unterstützung

Die Steuerung eines OLED erfordert Bibliotheken und Firmware:

- Arduino: `Adafruit_SSD1306` oder ähnliche;
- Klipper: spezielle Module für Display;
- ESP32: verschiedene OLED-Bibliotheken verfügbar.

Die häufigste ist der SSD1306-Controller für I2C OLED-Bildschirme.

## Was vor dem Kauf zu überprüfen ist

Vor dem Kauf überprüfen Sie:

- Auflösung (128x64 oder 128x32);
- Schnittstelle (I2C oder SPI);
- Betriebsspannung;
- Größe und Form;
- Farbe (weiss, blau, gelb);
- Controller-Chip (meist SSD1306);
- I2C-Adresse oder SPI-Pin-Layout;
- Verfügbarkeit von Datenblatt und Beispielcode;
- Betriebstemperaturbereich.

Für ein einfaches Projekt: ein `128x64` I2C OLED mit SSD1306.

## Typische Fehler

- falsche Spannungsversorgung (3.3V statt 5V oder umgekehrt);
- I2C-Adresse falsch in Firmware eingestellt;
- Daten- und Taktsignale vertauscht;
- Fehlender Pull-Up-Widerstand (manchmal erforderlich);
- OLED zu nah an Heizer/Heiße Luft;
- Display-Firmware nicht unterstützt;
- Speicher für Grafikpuffer zu groß auf kleinen Controllern.

## Hauptpunkt

Ein OLED-Bildschirm ist praktisch für Status und einfache Benutzerinteraktion. I2C ist für die meisten Anwendungen ausreichend. Überprüfen Sie Spannungsversorgung, I2C-Adresse und Firmware-Unterstützung.

## Referenzmaterialien

- [Adafruit: SSD1306 OLED Display](https://learn.adafruit.com/adafruit-oled-displays-for-arduino) - Datasheet, Anschlussmöglichkeiten, Arduino-Code.
- [Klipper Configuration Reference: Displays](https://www.klipper3d.org/Config_Reference.html#display) - Klipper-Unterstützung für SSD1306 und andere Bildschirme.
- [SSD1306 Datasheet](https://en.wikipedia.org/wiki/File:SSD1306.pdf) - offizielle Spezifikationen des Controllers.
