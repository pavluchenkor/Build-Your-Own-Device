# Wägezelle anschließen

Eine Wägezelle misst Kraft oder Gewicht durch winzige Verformung eines Metallträgers, einer Taste oder einer Plattform.

In Geräten wie iDryer kann eine Wägezelle das Spulengewicht, die verbleibende Filamentlänge oder die Mechanismuslast schätzen.

Wichtig: Eine Wägezelle wird fast nie direkt mit einem Controller verbunden. Ihr Signal ist zu schwach. Normalerweise wird ein HX711-Modul oder ein ähnlicher Verstärker/ADC zwischen den Sensor und den Controller platziert.

## Was du brauchst

Minimale Ausrüstung:

- Wägezelle mit dem benötigten Gewichtsbereich;
- HX711 Modul;
- Controller: Arduino, ESP32, RP2040, STM32 oder anderes Board;
- starre mechanische Montage;
- bekannte Masse zur Kalibrierung;
- kurze, saubere Drähte.

Wenn die Mechanik schlecht ist, kann die Schaltung nicht helfen. Eine Wägezelle kann perfekt verdrahtet sein, aber aufgrund von Fehlausrichtung, Spiel oder falscher Lastanwendung bedeutungslose Werte liefern.

## Wie die Verbindung angeordnet ist

Die Wägezelle wird mit analogen Drähten mit HX711 verbunden.

HX711 verbindet sich mit digitalen Drähten mit dem Controller.

Typische Kette:

```text
load cell -> HX711 -> controller
```

HX711 hat normalerweise zwei Seiten:

- Eingang von Wägezelle: `E+`, `E-`, `A+`, `A-` oder ähnlich;
- Verbindung zum Controller: `VCC`, `GND`, `DT`/`DOUT`, `SCK`/`CLK`.

![HX711 und Wägezellen-Verbindungsdiagramm](../../../img/06-practical-guides/04-hx711-load-cell-fritzing.jpg)

*Quelle: [SparkFun Electronics](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide/all), CC BY-SA 4.0*

## Wägezellen-Drähte

Eine häufige vierdrähtige Wägezelle hat normalerweise:

- `E+` - Brückenversorgung Plus;
- `E-` - Brückenversorgung Minus;
- `S+`, `A+` oder `O+` - positives Messsignal;
- `S-`, `A-` oder `O-` - negatives Messsignal.

Häufiges Farbschema:

- rot - `E+`;
- schwarz - `E-`;
- grün oder blau - `A+`;
- weiß - `A-`.

Farben sind aber keine Regel. Unterschiedliche Sensoren können unterschiedlich sein. Falls es ein Datenblatt für die spezifische Wägezelle gibt, folge ihm.

Falls der Sensor einen fünften Draht, Folie oder Schirm hat, ist es oft elektromagnetische Abschirmung. Verwirre es nicht mit einem Brückenmessdraht. Normalerweise wird die Abschirmung auf einer Seite mit `GND` oder Gehäuse verbunden, wenn die Dokumentation dies sagt, aber nicht mit Messung `A+`/`A-`.

Wenn es kein Drahtschemata gibt, verbinde die Wägezelle nicht „zufällig". Finde zuerst das Sensor-Datenblatt oder überprüfe die Brücke nach Anleitung des Herstellers: falsche Drähte geben leicht instabile Werte oder überlasten den HX711-Eingang.

## Verbindung von HX711 mit dem Controller

Auf der Controller-Seite benötigst du normalerweise vier Leitungen:

- `VCC` - Modul-Stromversorgung;
- `GND` - gemeinsames Negativ;
- `DT`, `DOUT` oder `DATA` - Daten;
- `SCK`, `CLK` oder `PD_SCK` - Takt.

Bei vielen HX711-Modulen kann die Stromversorgung `3.3V` oder `5V` sein, überprüfe aber das spezifische Modul. Falls der Controller auf 3.3V läuft, ist es praktisch, ein Modul und eine Stromversorgung zu verwenden, die mit 3.3V Logik kompatibel sind.

Pins `DT` und `SCK` können normalerweise mit normalen GPIO verbunden werden. Dies ist nicht I2C oder SPI im üblichen Sinne, sondern eine einfache Zwei-Draht-HX711-Schnittstelle.

## Mechanik ist wichtiger als die Schaltung

Eine Wägezelle muss sich so verformen, wie der Hersteller es beabsichtigte.

Bei einem Balkensensor montiert sich normalerweise eine Seite auf einer festen Basis, die andere Seite trägt die Last. Falls beide Seiten starr an einem Teil montiert sind, biegt sich der Sensor nicht normal.

Überprüfe:

- wo ist die Montagseite des Sensors;
- wo sollte die Last angebracht werden;
- welche Richtung soll die Kraft gehen;
- ob Abstandhalter benötigt werden;
- ob das bewegliche Teil das Gehäuse frei macht;
- keine Fehlausrichtung;
- keine Seitenlast;
- Schrauben sind nicht überflüstert;
- die Spule oder Plattform landet nicht über der Arbeitszone des Sensors.

Beim Spulengewicht ist es besonders wichtig, dass die gesamte Last durch den Sensor geht, nicht teilweise durch die Gehäusewand, Achse, Kabel oder Zierverkleidung.

## Überlade den Sensor nicht

Der Bereich einer Wägezelle ist keine Empfehlung, sondern eine Messbegrenzung.

Wenn ein 1 kg Sensor an einem Ort platziert wird, an dem eine Spule und ein Halter dies überschreiten können, funktioniert der Sensor schlecht oder verformt sich dauerhaft.

Wähle den Bereich mit Sicherheitsspanne:

- maximales Spulengewicht;
- Haltergewicht;
- mögliche Rucke;
- Fehlausrichtung;
- Sicherheitsspanne für Benutzerfehler.

Aber auch ein zu großer Bereich ist nicht immer gut. Ein 100 kg Sensor erkennt eine kleine Spule schlimmer als ein 5 kg oder 10 kg Sensor mit identischer Mechanik und Elektronik.

## Erste Inbetriebnahme

Vor der Installation im Gerät teste das System auf der Werkbank:

1. Verbinde Wägezelle mit HX711.
2. Verbinde HX711 mit dem Controller.
3. Führe Test-Code oder Bibliothek aus.
4. Stelle sicher, dass sich Rohwerte ändern, wenn du auf den Sensor drückst.
5. Entferne die Last und überprüfe, dass der Wert ziemlich stabil ist.
6. Platziere eine bekannte Masse und überprüfe die Änderung.

In diesem Stadium verlange keine Gramm-Genauigkeit. Zunächst musst du sehen, dass der Sensor aktiv ist, die Lastrichtung korrekt ist und die Werte vorhersehbar ändern.

Falls der Wert sinkt, wenn das Gewicht steigt, tausche normalerweise `A+` und `A-` oder berücksichtige das Vorzeichen im Code.

## Tara und Kalibrierung

Eine Wägezelle ohne Kalibrierung weiß nicht, was Gramm sind.

Typischer Prozess:

1. Platziere leere Plattform.
2. Tara: Dies ist Null unter Berücksichtigung des Plattformgewichts.
3. Platziere eine bekannte Masse.
4. Wähle Kalibrierungsfaktor.
5. Überprüfe mehrere verschiedene Gewichte.

Für Filamentspulen, entscheide, was als Gewicht zählt:

- gesamte Spule mit Kunststoff;
- nur verbleibender Kunststoff ohne Leergewicht der Spule;
- Gewichtänderung vom Anfangswert.

Falls Leerspulen von verschiedenen Herstellern unterschiedlich wiegen, erfordert eine genaue Restberechnung das Wissen des spezifischen Leerspulengewichts oder die Arbeit mit groben Schätzungen.

## Rauschen und instabile Messwerte

HX711 misst ein sehr kleines Signal, daher ist das System empfindlich gegenüber Rauschen und mechanischen Problemen.

Ursachen für instabile Messwerte:

- lange Drähte vom Sensor zu HX711;
- schlechte Kontakte;
- Heizer-Stromdrähte neben Signaldrähten;
- Lüfter- oder Drucker-Vibration;
- weiche Basis;
- Spiel bei Montage;
- Temperaturdrift;
- Last berührt das Gehäuse, umgeht den Sensor.

Praktische Maßnahmen:

- halte HX711 nah bei der Wägezelle;
- führe Signaldrähte nicht neben Heizer-Stromdrähten;
- sichere Drähte, damit sie den Sensor nicht ziehen;
- nutze Messmittelung;
- kalibriere nach Montage im Gehäuse;
- tare nach Geräteaufwärmung, falls Temperatur merklich die Messwerte beeinflusst.

## Was nach dem Zusammenbau zu überprüfen ist

Vor Gebrauch:

- Sensor ist für das benötigte Gewicht bewertet;
- Last geht durch den funktionierenden Teil des Sensors;
- Befestigungen blockieren keine Verformung;
- HX711 empfängt richtige Stromversorgung;
- `DT` und `SCK` sind mit dem richtigen GPIO verbunden;
- gemeinsame Masse existiert;
- Rohwerte ändern sich unter Last;
- ohne Last werden Messwerte nicht zu schnell abgelenkt;
- bekannte Masse zeigt erwartet Gewicht nach Kalibrierung;
- Drähte ziehen die Plattform nicht;
- Spule oder Halter berührt das Gehäuse nicht über dem Sensor.

## Häufige Fehler

- Wägezelle direkt mit Controller-Analogeingang verbinden;
- Verwechselung von `E+`/`E-` und `A+`/`A-`;
- Drahfarben blind vertrauen ohne Datenblatt;
- Kalibrierung vergessen;
- Tara vor endgültiger mechanischer Installation;
- Sensor montieren, damit er nicht flexen kann;
- Sensor überladen;
- zu großen Bereich wählen und Empfindlichkeit verlieren;
- Instabilität durch lange Drähte und Störungen bekommen;
- Gramm-Genauigkeit von flexiblem Kunststoffkörper ohne starre Mechanik erwarten.

## Wichtigste Punkte

- Wägezelle verbindet sich normalerweise über HX711, nicht direkt mit dem Controller.
- Sensor-Drähte gehen zu `E+`, `E-`, `A+`, `A-`.
- HX711 verbindet sich mit dem Controller über Stromversorgung, Masse, `DT` und `SCK`.
- Mechanik ist wichtiger als die Schaltung: Last muss richtig durch den Sensor gehen.
- Tara und Kalibrierung mit bekannter Masse sind erforderlich.
- Ohne starre Montage und richtige Mechanik werden genaue Messwerte nicht erreicht.

## Weiterführende Lektüre

- [SparkFun: Load Cell Amplifier HX711 Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide/all) - praktische HX711 und Wägezellen-Verbindung, Drahfarben, `DT`/`SCK` und Kalibrierungsbeispiel.
- [SparkFun: Load Cell Amplifier HX711 product page](https://www.sparkfun.com/sparkfun-load-cell-amplifier-hx711.html) - HX711 Modul-Beschreibung, Zweck und Mikrocontroller-Schnittstelle.
- [DigiKey: HX711 Datasheet by Avia Semiconductor](https://www.digikey.com/en/htmldatasheets/production/1836471/0/0/1/hx711.html) - HX711 technisches Datenblatt: 24-Bit ADC, differenzieller Brückeneingang, Verstärkung und digitale Schnittstelle.
- [Phidgets: Load Cell Guide](https://cdn.phidgets.com/docs/Load_Cell_Guide) - praktische Beispiele der mechanischen Montage der Wägezelle und Lastanwendungsrichtung.
- [SparkFun retired HX711 guide: load cell mechanical setup](https://learn.sparkfun.com/tutorials/retired---load-cell-amplifier-hx711-breakout-hookup-guide) - nützliche Abbildungen der Balken-, Tasten- und Plattformen-Sensor-Montageoptionen.
