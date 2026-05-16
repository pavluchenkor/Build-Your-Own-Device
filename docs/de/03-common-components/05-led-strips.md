# LED-Streifen

Ein LED-Streifen ist ein Streifen mit vielen kleinen Lichtern. In einem Dryer oder iDryer-ähnlichen Gerät wird er für Sicht, Wärmestrahlung oder einfach Beleuchtung verwendet.

Es gibt verschiedene LED-Streifen-Typen: einfache monochrome, RGB, RGBW, mit konstanter Helligkeit oder einzeln adressierbar.

Ein LED-Streifen mit vielen LEDs verbraucht Strom. Sie müssen die Gesamtleistung berechnen und sicherstellen, dass die Stromversorgung und Verkabelung damit umgehen können.

## Wo es verwendet wird

In iDryer-ähnlichen Projekten werden LED-Streifen verwendet für:

- Beleuchtung im Gehäuse;
- Sichtbarkeit innen;
- Wärmestrahlung zum Heizen (nicht für hohe Temperaturen);
- Anzeige des Status;
- einfache Visualisierung der Prozessparameter.

Nicht alle LED-Streifen können Hitze in unmittelbarer Nähe eines Heizers oder Luftstroms aushalten.

## Spannung und Stromversorgung

LED-Streifen verfügbare Spannungen:

- `5V` - häufig bei Computergebäuden;
- `12V` - sehr häufig;
- `24V` - für langere Streifen und bessere Spannungsstabilität.

Überprüfen Sie:

- Betriebsspannung;
- Stromverbrauch pro Meter (bei voller Helligkeit);
- Gesamtlänge des Streifens;
- maximale Länge ohne zusätzliche Stromversorgung;
- Spannung am Ende des Streifens nach Spannungsabfall;
- Steckertyp oder direkte Verdrahtung.

Ein langer `5V`-LED-Streifen kann am Ende zu dunkel sein, wenn nur an einem Ende Strom eingespeist wird. `24V`-LED-Streifen haben weniger Spannungsabfall.

## Arten von LED-Strei fen

Einfache (nicht adressierbar):

- alle LEDs leuchten zusammen mit derselben Helligkeit;
- benötigen 2 oder 3 Drähte (Leistung, GND, optional Steuerung);
- einfach zu kontrollieren mit PWM;
- weniger Kabledatenrate.

RGB und RGBW (einzeln adressierbar):

- jede LED kann eine eigene Farbe haben;
- benötigen 4 oder 5 Drähte (Stromversorgung, GND, Daten, optional Takt);
- benötigen spezielle Firmware-Unterstützung wie NeoPixel/WS2812;
- höhere Datenrate erforderlich;
- kompliziertere Logik.

Für einfache Beleuchtung sind einfache LED-Streifen mit PWM-Steuerung ausreichend.

## LED-Streifen-Merkblatt

Überprüfen Sie:

- Spannung: `5V`, `12V`, `24V`;
- LED-Typ: SMD (oberflächenmontiert) oder anderer;
- Stromverbrauch pro LED;
- Stromverbrauch pro Meter;
- Gesamtlänge;
- maximale durchgehende Länge ohne zusätzliche Stromversorgung;
- Steuerungsmethode: einfache PWM, SPI, I2C, andere;
- Helligkeit und Farbtemperatur;
- Gehäuse: offene, halbverkapselung oder vollständig vergossen;
- Wetterbeständigkeit falls außen;
- Befestigungsmethode und 3M-Kleber Qualität.

Für einen Innenraum eines Dryers mit Hitze und Luftstrom: überprüfen Sie Temperaturbeständigkeit und Material.

## Wärmeleistung von LED-Streifen

LEDs strahlen Wärmestrahlung aus und erzeugen auch Joule-Wärme. Eine intensive LED kann bis zu mehreren Watt pro Meter erzeugen.

Für Heizzwecke sind LEDs nicht ideal:

- Wärmeverteilung ist ungleichmäßig;
- Strom wird bei Licht (nutzlos für Heizung) verschwendet;
- spezialisierte Heizer (Kartuschen, PTC, Pads) sind effizienter.

Aber wenn der Platz begrenzt ist und Licht auch benötigt wird, können LEDs einen Teil der Heizlast tragen. Überprüfen Sie die Temperatur mit einem Sensor.

## Verkabelung und Strom

LED-Streifen mit vielen LEDs benötigen großzügige Verkabelung:

- Drahtquerschnitt basierend auf Strom und Länge;
- geringe Spannungsabfall akzeptieren;
- Stromanschluss nahe beim LED-Streifen, nicht am anderen Ende;
- Falls länge LED-Streifen: Multiple Stromversorgungspunkte hinzufügen;
- Masseleitung auch überprüfen: manchmal sind Sternpunkte wichtig.

Wenn der LED-Streifen am Ende dunkel ist oder flimmert, ist der Spannungsabfall das erste, das überprüft werden sollte.

## Befestigung und Koexistenz

LED-Streifen mit 3M-Kleber:

- kleben auf sauberen, trockenen Oberflächen;
- halten in gemäßigten Temperaturen;
- in heißer Umgebung oder feuchter Umgebung können sie abgelöst werden;
- Oberflächenreinigung mit Isopropanol vor dem Kleben.

Für heißere Bereiche:

- Befestigung mit Schellen oder Klammern;
- Wärmeschutz zwischen Streifen und Heizzone prüfen.

## Was vor dem Kauf zu überprüfen ist

Überprüfen Sie vor dem Kauf eines LED-Streifens:

- Spannungstyp: `5V`, `12V`, `24V`;
- Stromverbrauch pro Meter;
- Steuertyp: einfach/PWM oder adressierbar;
- Länge;
- LED-Dichte;
- Helligkeit;
- Farbtemperatur oder RGB/RGBW;
- Gehäuse und Schutz;
- Befestigungsmethode;
- Temperaturbeständigkeit;
- Verfügbarkeit von Datenblatt.

Für einen heißen Innenraum: Priorität auf Temperaturbeständigkeit legen.

## Typische Fehler

- Stromverbrauch pro Meter nicht berechnet;
- zu dünne Verdrahtung für die Länge;
- Stromversorgung nur an einem Ende langer Streifen;
- LED-Streifen neben heißem Bereich ohne Schutz;
- falsche Steuerlogik für adressierbare LEDs;
- erwartet, dass LEDs deutlich heizen können;
- Kleber auf schmutziger oder nasser Oberfläche;
- keinen Diffusor oder Schutzkanal zum Schutz der LEDs.

## Hauptpunkt

Ein LED-Streifen ist einfache Beleuchtung. Bei hohem Stromverbrauch überprüfen Sie die Verkabelung und Stromversorgung. Für Heizzwecke sind spezialisierte Heizer effizienter, aber LEDs können einen Teil der Last tragen. Temperatur- und Montagelokalität beachten.

## Referenzmaterialien

- [Adafruit: Addressable RGB LEDs](https://learn.adafruit.com/adafruit-neopixel-uberguide) - Erklärung von NeoPixel/WS2812, Datenprotokoll, Stromversorgung und Kontrolllogik.
- [SparkFun: APA102 Addressable LED Tape](https://learn.sparkfun.com/tutorials/apa102-addressable-led-tape) - Alternative zu NeoPixel mit Clock/Data-Schnittstelle.
- [Klipper Configuration Reference: LED Strips](https://www.klipper3d.org/Config_Reference.html#output_pin) - Klipper-LED-Steuerung über `output_pin`, PWM.
