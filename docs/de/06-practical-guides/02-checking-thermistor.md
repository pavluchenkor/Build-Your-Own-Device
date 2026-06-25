# Überprüfung eines Thermistors

Ein Thermistor ist ein Temperatursensor, der seinen Widerstand bei Erwärmung oder Abkühlung ändert.

In 3D-Druckern, Trocknern und Kammerheizungen ist der häufigste Typ ein NTC-Thermistor mit einem Nennwert von `100K`. NTC bedeutet, dass der Widerstand mit steigender Temperatur abnimmt.

Sie müssen einen Thermistor überprüfen, wenn:

- die Temperaturmessungen unrealistisch sind;
- die Temperatur sprunghaft schwankt;
- der Heizer einen Fehlerzustand aufruft;
- die Firmware `MINTEMP`, `MAXTEMP`, `Thermal runaway` oder ähnliches meldet;
- der Thermistor ersetzt, bewegt oder neu gecrimpt wurde;
- das Gerät zum ersten Mal zusammengebaut wurde.

## Zuerst Stromversorgung ausschalten

Der Widerstand wird nur in stromlosen Schaltkreisen gemessen.

Vor der Überprüfung:

1. Schalten Sie das Gerät aus.
2. Trennen Sie die Stromversorgung vom Stromnetz oder der Stromversorgung.
3. Warten Sie, bis der Heizer abgekühlt ist.
4. Trennen Sie den Thermistor von der Karte, falls Sie den Sensor selbst messen müssen.

Wenn Sie den Widerstand messen, während der Thermistor an der Karte angeschlossen ist, können die Messwerte durch andere Schaltkreiskomponenten verzerrt werden. Wenn Sie den Widerstand mit eingeschalteter Stromversorgung messen, können Sie das Multimeter oder die Karte beschädigen.

## Was ein NTC 100K haben sollte

Ein typisches NTC `100K` hat einen Widerstand von etwa `100 kOhm` bei `25°C`.

Das bedeutet nicht, dass das Multimeter immer genau `100.0 kOhm` anzeigt.

Es ist normal, dass die Ablesung bei Raumtemperatur leicht abweicht:

- in einem kühlen Raum ist der Widerstand höher;
- in einem warmen Raum ist der Widerstand niedriger;
- verschiedene Thermistor-Typen haben unterschiedliche Tabellen;
- lange Drähte und schlechte Kontakte können die Messung beeinflussen.

Die Hauptprüfung ist einfach: Ein 100K NTC bei Raumtemperatur sollte Dutzende oder etwa hundert Kilohm lesen, nicht `0 Ohm` oder `OL`.

## Messen mit einem Multimeter

Stellen Sie Ihr Multimeter auf Widerstandsmodus `Ohm` ein.

Wenn Ihr Multimeter nicht autorangierend ist, wählen Sie einen Bereich über `100 kOhm`, z.B. `200 kOhm` oder `2 MOhm`.

Dann:

1. Trennen Sie den Thermistor von der Karte.
2. Berühren Sie die Multimeter-Sonden mit den zwei Thermistordrähten.
3. Halten Sie nicht gleichzeitig die Metallenden der Sonden und Drähte: Ihr Körper kann Parallelwiderstand hinzufügen.
4. Warten Sie, bis sich der Messwert stabilisiert.
5. Notieren Sie den Wert.

![Digitales Multimeter zur Messung der Thermistorwiderstand](../../img/05-tools/02-digital-multimeter.jpg)

*Quelle: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Aneng_AN870_multimeter_02.jpg), Ruhestand Elektriker, CC0 Public Domain*

## Schneller Wärmetest mit Ihrem Finger

Nach der Messung bei Raumtemperatur können Sie den Sensor vorsichtig mit Ihren Fingern erwärmen.

Bei einem NTC-Thermistor sollte der Widerstand zu sinken beginnen.

Zum Beispiel:

- war bei Raumtemperatur um `100 kOhm`;
- wurde niedriger nach Fingererwärmung.

Exakte Zahlen spielen keine Rolle hier. Die Richtung der Änderung spielt eine Rolle.

Wenn sich der Widerstand überhaupt nicht ändert, zufällig springt oder verschwindet, wenn der Draht bewegt wird, könnte das Problem im Sensor, Draht, Crimp oder Stecker liegen.

## Bruch und Kurzschluss

Ein Multimeter hilft dabei, schnell einen normalen Sensor von einem offensichtlichen Fehler zu unterscheiden.

Typische Zeichen:

- `OL`, `über Grenze`, `1` auf der linken Seite der Anzeige, oder unendlicher Widerstand - offener Stromkreis;
- fast `0 Ohm` - Kurzschluss;
- Wert springt erheblich, wenn der Draht bewegt wird - schlechter Kontakt oder unterbrochener Leiter;
- Wert um `100 kOhm` bei Raumtemperatur und sinkt mit Erwärmung - sieht aus wie ein gesundes NTC 100K.

Verschiedene Multimeter verwenden unterschiedliche Bezeichnungen für offene Stromkreise. Normalerweise ist es `OL` oder ein Wert jenseits des ausgewählten Bereichs.

## Überprüfung der Verdrahtung

Der Thermistor kann in Ordnung sein, während das Problem in der Verdrahtung liegt.

Überprüfen:

- der Stecker ist vollständig eingesetzt;
- Stifte sind nicht aus dem Steckergehäuse herausgekommen;
- Drähte sind nicht ausgefranst;
- keine Isolationsschäden in der Nähe des Heizers;
- keine Drahtspannung, wenn Achsen oder Abdeckung bewegt werden;
- das Kabel verläuft nicht direkt neben Heizer-Stromdrähten ohne Grund;
- der Crimp-Ort ist sicher.

Wenn sich die Messwerte ändern, wenn Sie den Draht bewegen, ist dies keine "Sensorfunktion". Dies ist ein Kontaktproblem, das behoben werden muss, bevor der Heizer eingeschaltet wird.

## Überprüfung in Klipper

Im Klipper wird der Sensortyp in der Konfiguration festgelegt.

Beispiel für einen typischen Kammertemperatursensor:

```ini
[temperature_sensor chamber]
sensor_type: Generic 3950
sensor_pin: PA0
min_temp: 0
max_temp: 100
```

Beispiel für einen Kammerheizer:

```ini
[heater_generic chamber_heater]
gcode_id: C
heater_pin: PA8
sensor_type: Generic 3950
sensor_pin: PA0
control: watermark
min_temp: 0
max_temp: 90
```

Pin-Namen hier sind typisch. Überprüfen Sie in einem echten Gerät die Pinbelegung Ihres Boards.

Wichtig: `sensor_type` muss mit dem realen Sensor übereinstimmen. Zwei Thermistoren können identisch aussehen, haben aber unterschiedliche Tabellen. Wenn Sie den falschen Typ wählen, kann die Temperatur besonders im Arbeitsheizbreich erheblich ungenau sein.

## Was in der Benutzeroberfläche zu überwachen ist

Überprüfen Sie nach der Verbindung die Temperatur in der Klipper-Oberfläche, dem Großsegel, der Flüssigkeit oder einer anderen Benutzeroberfläche.

Bei Raumtemperatur sollte die Ablesung nahe der tatsächlichen Raumtemperatur liegen.

Verdächtige Zeichen:

- liest deutlich niedriger als Realität;
- liest deutlich höher als Realität;
- die Temperatur springt um Dutzende Grad;
- die Temperatur ändert sich, wenn Sie den Draht bewegen;
- die Temperatur steigt nicht, wenn die Heizung an ist;
- die Temperatur steigt sehr langsam;
- die Temperatur steigt, obwohl der Heizer aus ist.

Wenn der Sensor am Heizer sitzt, starten Sie nicht mit ausgedehntem Heizen, bis die Messungen vernünftig aussehen.

## Firmware-Fehler

In der 3D-Drucker-Firmware sind Temperaturfehler kein geringes Problem, sondern Teil der Sicherheit.

Für eine typische Schaltung mit einem NTC und dem Onboard-Pull-up:

- Sensorfehler sieht oft wie zu niedrige Temperatur oder `MINTEMP` aus;
- Kurzschluss sieht oft wie zu hohe Temperatur oder `MAXTEMP` aus;
- schlechter thermischer Kontakt kann `Heating failed` oder `Thermal runaway` verursachen;
- starke Abkühlung des Heizbocks kann einen Fehler verursachen, weil die Temperatur zu langsam ansteigt oder nicht hält.

Fehlernamen hängen von der Firmware ab, aber die Bedeutung ist gleich: Der Controller vertraut der Temperatur nicht mehr oder sieht, dass die Heizung nicht wie erwartet funktioniert.

Deaktivieren Sie den thermischen Schutz nicht nur zum "Überprüfen". Wenn der Schutz auslöst, schauen Sie zuerst nach der Ursache bei Sensor, Verdrahtung, Montage, Heizer, PID-Einstellungen und Kühlung.

## Thermischer Kontakt

Ein elektrisch funktionierender Thermistor garantiert nicht die korrekte Temperatur.

Der Sensor muss Wärme gut vom Teil, das er misst, übertragen.

Überprüfen:

- der Sensor sitzt vollständig in der Hülse oder im Loch;
- es gibt normales Klemmen;
- kein Spalt zwischen Sensor und Oberfläche;
- thermische Paste ist nicht ausgetrocknet oder abgeblättert, falls verwendet;
- Befestigungen sind nicht locker;
- der Sensor ist nicht aus seinem Sitz herausgekommen;
- Drähte ziehen den Sensor nicht heraus.

Schlechter Kontakt ist gefährlich, weil der Sensor die Temperatur niedriger als Realität liest. Der Controller heizt weiter, während der echte Teil möglicherweise bereits überhitzt ist.

## Mini-Checkliste

Vor dem ersten Heizen:

- Thermistor-Widerstand sieht wie erwartet aus;
- NTC-Widerstand sinkt mit Fingererwärmung;
- kein offener Stromkreis oder Kurzschluss;
- Drähte reagieren nicht mit Sprüngen, wenn sie bewegt werden;
- Stecker ist korrekt eingesetzt;
- korrekter `sensor_type` ist in der Firmware gewählt;
- Temperatur in der Benutzeroberfläche sieht aus wie Raumtemperatur;
- Sensor ist sicher an der richtigen Stelle montiert;
- `min_temp` und `max_temp` sind vernünftig für das Gerät eingestellt.

## Häufige Fehler

- Widerstand messen, während die Karte unter Strom ist;
- nicht trennen des Sensors von der Karte und Erhalten seltsamer Werte;
- Verwechslung eines `100K` Thermistors mit einem anderen Sensortyp;
- Wahl des falschen `sensor_type`;
- sehen `OL` und denken, es bedeutet "100K";
- Annahme, dass jeder 100K NTC identisch ist;
- den Thermistor locker neben dem Heizer belassen;
- zu festes Anziehen eines Glassensors mit einer Schraube;
- an dem Draht ziehen, so dass der Sensor aus der Hülse herauskommt;
- Deaktivierung des thermischen Schutzes statt Behebung der Fehlerursache.

## Wichtigste Punkte

- Der Widerstand wird nur in stromlosen Schaltkreisen gemessen.
- Ein typisches NTC 100K ist bei `25°C` etwa `100 kOhm`.
- Wenn geheizt, sinkt der NTC-Widerstand.
- `OL` bedeutet meist offenen Stromkreis, fast `0 Ohm` bedeutet Kurzschluss.
- Die Firmware muss den korrekten Sensortyp auswählen.
- Guter thermischer Kontakt ist so wichtig wie funktionsfähige Verdrahtung.
- Starten Sie nicht den Heizer, wenn Temperaturmessungen falsch aussehen.

## Verwandte Lektüre

- [Klipper-Konfigurationsreferenz: Temperatursensoren](https://www.klipper3d.org/Config_Reference.html#temperature-sensors) - offizielle `sensor_type`, `sensor_pin`, `pullup_resistor` Parameter und Liste häufiger Thermistoren.
- [Marlin-Konfiguration: Temperaturbereiche und thermischer Schutz](https://marlinfw.org/docs/configuration/configuration.html#temperature-ranges) - Erklärung von `MINTEMP`, `MAXTEMP` und Thermal Runaway-Schutz.
- [Marlin Troubleshooting: Heating Failed](https://marlinfw.org/docs/basics/troubleshooting.html#heating-failed) - typische Fehlerursachen beim Heizen: Thermistor, langsamer Temperaturanstieg, thermischer Runaway.
- [RepRap Wiki: Thermistor](https://reprap.org/wiki/Thermistor) - grundlegende Beschreibung von NTC/PTC-Thermistoren und Überprüfung des Raumtemperaturwiderstands.
- [Fluke: Wie man Widerstand mit einem Digitalmultimeter misst](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-resistance) - sichere Vorgehensweise zum Messen des Widerstands mit einem digitalen Multimeter.
