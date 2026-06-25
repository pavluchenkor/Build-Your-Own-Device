# OLED-Bildschirm

Ein OLED-Bildschirm ist ein kleines Display zur Anzeige von Text, Zahlen, einfachen Symbolen und Gerätestatus. Im Gegensatz zu normalem LCD leuchtet OLED selbst und benötigt keine separate Hintergrundbeleuchtung. Kleine OLED-Module sind lesbar, benötigen wenig Platz und sind praktisch für einfache DIY-Geräte.

In einem iDryer-ähnlichen Gerät kann ein OLED-Display Temperatur, Luftfeuchtigkeit, Betriebsmodus, Fehler, Wi-Fi-Status, verbleibender Filament oder aktuelle Trocknungsphase anzeigen.

## Wann ist OLED sinnvoll

Ein OLED ist sinnvoll zu installieren, wenn Benutzer den Gerätestatus direkt auf dem Gehäuse sehen müssen:

- aktuelle Kammertemperatur;
- Luftfeuchtigkeit;
- Zieltemperatur;
- Betriebsmodus;
- Schaltuhren;
- Sensorfehler;
- Lüfter- oder Heizerstatus;
- Verbindungsstatus;
- einfaches Menü ohne großen Bildschirm.

Wenn das Gerät immer über Klipper, Web-Interface oder Mobile App verwaltet wird, ist ein separates OLED möglicherweise nicht notwendig. Es erhöht die Verdrahtung, benötigt Platz im Gehäuse, erfordert Code und ist ein weiterer Fehlerpunkt.

## Typische Größen und Controller

Die am häufigsten verwendeten kleinen OLED-Module:

- `128x32` Pixel;
- `128x64` Pixel;
- Diagonale ca. `0,91"` oder `0,96"`;
- monochrom: weiß, blau, gelb-blau;
- mit Controller `SSD1306` oder ähnlich `SH1106`.

`SSD1306` und `SH1106` sehen ähnlich aus, sind aber nicht immer vollständig code-kompatibel. Wenn eine Bibliothek für `SSD1306` eingestellt ist, das Modul aber tatsächlich `SH1106` ist, kann der Bildschirm ein verschobenes Bild, Müll oder gar nichts anzeigen.

Vor dem Kauf ist es wichtig, nicht nur die Bildschirmgröße, sondern auch den Controller, die Schnittstelle und die Versorgungsspannung zu prüfen.

## I2C und SPI

Kleine OLED-Module verbinden sich normalerweise über I2C oder SPI.

Ein I2C-Modul hat normalerweise 4 Kontakte:

- `VCC`;
- `GND`;
- `SDA`;
- `SCL`.

Ein SPI-Modul benötigt mehr Leitungen:

- `VCC`;
- `GND`;
- `SCK`/`CLK`;
- `MOSI`/`DIN`;
- `CS`;
- `DC`;
- manchmal `RST`.

I2C ist einfacher zu verdrahten und reicht normalerweise für Status, Temperatur und einfaches Menü aus. SPI ist schneller und besser, wenn der Bildschirm häufig aktualisiert wird, aber bei einem kleinen Statusdisplay ist dies selten entscheidend.

![Anschluss eines I2C-OLED-Displays an den Controller](../../img/03-common-components/08-oled-i2c-wiring.jpg)

*Quelle: [Adafruit Learning System](https://learn.adafruit.com/adafruit-128x64-oled-featherwing/), CC BY-SA 3.0*

## Spannungsversorgung und Logikpegel

Ein OLED-Modul kann für `3,3V`, `5V` oder ein Spannungsreguliermodul mit Pegelverschiebung auf der Platine ausgelegt sein. Äußerlich können solche Module fast identisch aussehen.

Vor dem Anschluss prüfen:

- welche Stromversorgung im Modul oder auf der Produktseite aufgelistet ist;
- ob `SDA`/`SCL`-Leitungen mit der Controller-Logik kompatibel sind;
- ob das Modul I2C Pull-ups hat;
- ob Pull-ups nicht mit der Controller-Spannung in Konflikt geraten.

Für ESP32 und die meisten modernen Mikrocontroller ist es sicherer, von `3,3V` Logik auszugehen. Wenn ein OLED-Modul I2C auf `5V` zieht, kann dies für einen 3,3V-Controller problematisch sein.

Viele beliebte I2C-OLED-Module funktionieren von `3,3V` und verbinden sich direkt mit ESP32, aber du musst das spezifische Modul überprüfen.

## I2C-Adresse

I2C-OLED hat oft Adressen:

- `0x3C`;
- `0x3D`.

Wenn der Bildschirm nicht antwortet, ist die Adresse das erste, das man nach Stromversorgung und Drähten überprüfen sollte. Einige Module ermöglichen es dir, die Adresse über einen Jumper oder durch Löten eines kleinen Jumpers auf der Platine zu ändern.

Zeichen für falsche Adresse:

- Skizze oder Firmware startet, aber Bildschirm ist leer;
- I2C-Scanner sieht Gerät unter anderer Adresse;
- Bibliothek initialisiert Display ohne sichtbares Ergebnis;
- Änderung von `0x3C` zu `0x3D` macht es funktionieren.

## Was auf einem kleinen Bildschirm angezeigt werden sollte

Ein `128x32`- oder `128x64`-OLED hat sehr wenig Platz. Versuche nicht, ein vollständiges Smartphone-Interface darauf zu machen.

Gute Einstellung für einen Trockner oder Heizer:

- große aktuelle Temperatur;
- Zieltemperatur;
- Luftfeuchtigkeit, falls ein Sensor vorhanden ist;
- Modus: `HEAT`, `DRY`, `IDLE`, `ERROR`;
- kleines Lüfter-/Heizer-Symbol;
- Fehlercode oder kurze Meldung.

Schlechte Einstellung:

- lange Sätze;
- winzige Tabellen;
- viele Menüpunkte auf einem Bildschirm;
- ständig rollender Text;
- dekorative Animation statt nützlichem Status.

Bei einem Gerät mit Heizer ist es wichtiger, einen Fehler schnell zu erkennen als einen hübschen Splash-Screen zu haben.

## Einbrennen und Helligkeit

OLED-Pixel altern durch das Glühen. Wenn du an einer Stelle über lange Zeit denselben hellen Text anzeigst, kann sich schließlich eine Spur abzeichnen.

Für ein DIY-Gerät ist dies nicht immer kritisch, aber es ist besser zu:

- Helligkeit nicht ständig auf Maximum halten, wenn nicht nötig;
- Bildschirm nach Leerlaufzeit ausschalten;
- statische Elemente gelegentlich verschieben;
- nicht ständig weiße Fläche anzeigen;
- kurze Updates statt zusätzliche Animation verwenden.

In einer warmen Kammer oder in der Nähe eines Heizers hat OLED auch eine kürzere Lebensdauer. Es ist besser, die Elektronik in einer Zone mit kontrollierter Temperatur im zulässigen Modulbereich zu halten.

## Drahtlänge und Interferenz

I2C mag lange Drähte nicht, insbesondere in der Nähe von Motoren, Heizern und Stromversorgungsleitungen. Wenn sich OLED auf einer Tür oder abnehmbarem Bedienfeld befindet, kann ein langes flexibles Kabel zu einer Störquelle werden.

Praktische Regeln:

- `SDA` und `SCL` kurz halten;
- sie von Heizer-Stromversorgungsleitungen fernhalten;
- gemeinsame `GND` verwenden;
- keinen Stecker machen, der rückwärts eingeht;
- für eine abnehmbare Abdeckung einen richtigen Stecker und Zugentlastung verwenden;
- wenn I2C instabil ist, erst Drähte kürzen und Pull-ups überprüfen.

SPI toleriert normalerweise höhere Aktualisierungsgeschwindigkeit besser, hat aber mehr Drähte und Verbindungsfehler sind häufiger.

## OLED oder Touchscreen

OLED ist gut zur Statusanzeige. Ohne Tasten, Encoder oder andere Steuerung wird das Eingabeproblem nicht gelöst.

Wenn Benutzer häufig Einstellungen direkt auf dem Gerät ändern müssen, könnte Folgendes nötig sein:

- Encoder + OLED;
- mehrere Tasten + OLED;
- TFT-Display;
- Touchscreen;
- Web-Interface oder App.

Installiere keinen Touchscreen nur, weil das OLED klein wirkt. Für einfache Geräte ist manchmal ein kleines OLED mit einer Schaltfläche zuverlässiger und klarer.

## Was vor dem Kauf zu überprüfen ist

Vor dem Kauf eines OLED-Moduls überprüfen:

- Größe: `128x32`, `128x64` oder andere;
- Controller: `SSD1306`, `SH1106`, `SH1107`;
- Schnittstelle: I2C oder SPI;
- Stromversorgung: `3,3V`, `5V` oder Bereich;
- Logikpegel;
- I2C-Adresse, falls aufgelistet;
- Unterstützung des Reset-Pins;
- Unterstützung in ausgewählter Firmware oder Bibliothek;
- physikalische Platinendimensionen und Montagelöcher;
- Steckerposition;
- Betriebstemperatur;
- Farbe und Lesbarkeit unter dem Winkel, den du benötigst.

Für ein ESP32-Gerät ist normalerweise ein I2C-OLED `SSD1306` auf `0x3C` mit Adresse `0x3C` am bequemsten. Für eine Klipper-Platine überprüfe, ob die spezifische Platine deinen gewählten Bus unterstützt und wie das Display in der Konfiguration beschrieben wird.

## Typische Fehler

- `SDA` und `SCL` verwechselt;
- Stromversorgung an falsche Spannung angeschlossen;
- I2C-Adresse nicht überprüft;
- `SSD1306` im Code ausgewählt, aber Modul ist `SH1106`;
- I2C-Drähte zu lang gemacht;
- gemeinsame `GND` vergessen;
- 5V Pull-up Modul an 3,3V Controller ohne Überprüfung angeschlossen;
- SPI-Modul ausgewählt mit Erwartung von 4 Pins wie I2C;
- Bildschirm in heißer Zone platziert;
- Display installiert, ohne zu verstehen, welches Problem es für Benutzer löst.

## Hauptpunkt

Ein OLED-Display ist gut für kurze Statusinformationen und einfaches lokales Interface. Bei den meisten DIY-Geräten reicht ein I2C-OLED `128x64`, wenn es stromversorgungstechnisch kompatibel und von der gewählten Firmware unterstützt wird.

Vor dem Anschluss prüfe den Display-Controller, die Schnittstelle, die Stromversorgung, die I2C-Adresse und die Drahtlänge. Wenn das Gerät bereits über Web-Interface praktisch ist, ist OLED möglicherweise nicht nötig.

## Referenzmaterialien

- [Adafruit: Monochrome OLED Breakouts](https://learn.adafruit.com/monochrome-oled-breakouts) - praktisches Handbuch für kleine SSD1306-OLED, I2C/SPI-Verbindung, Größen und Beispiele.
- [SparkFun: Qwiic Micro OLED Hookup Guide](https://learn.sparkfun.com/tutorials/qwiic-micro-oled-hookup-guide) - Beispiel eines I2C-OLED-Moduls, Bibliothek und Text-/Grafikausgabe.
- [ESPHome: SSD1306 OLED Display](https://esphome.io/components/display/ssd1306) - Dokumentation zu `ssd1306_i2c`, `ssd1306_spi`, Adressen, SSD1306/SH1106-Modellen und Konfiguration.
- [Klipper Configuration Reference: display](https://www.klipper3d.org/Config_Reference.html#display) - Display-Unterstützung in Klipper, einschließlich `ssd1306` und `sh1106`.
- [SSD1306 Datasheet: Solomon Systech](https://www.radiolocman.com/datasheet/pdf.html?di=168297) - technische Beschreibung des SSD1306-Controllers: Auflösung, I2C/SPI/Parallel-Schnittstellen und Befehle.
