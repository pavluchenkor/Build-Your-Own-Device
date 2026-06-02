# Multimeter

Ein Multimeter ist das wichtigste erste Diagnosetool.

Sie können damit überprüfen:

- ob Strom vorhanden ist;
- ob Spannung korrekt ist;
- wo Plus und Minus sind;
- ob ein Draht gebrochen ist;
- ob eine Sicherung intakt ist;
- ob ein Thermistor funktionsfähig erscheint;
- ob es Spannungssag unter Last gibt.

Aber es ist leicht, Fehler mit einem Multimeter zu machen, wenn Sie die Modi verwechseln. Die gefährlichsten Fehler betreffen Strommessung und Netzspannungsmessung.

## Sonden und Häfen

Ein Multimeter hat normalerweise:

- `COM` - Common-Buchse, wohin Sie fast immer die schwarze Sonde einfügen;
- `V/Ohm/mA` oder ähnliche Buchse - für Spannung, Widerstand, Kontinuität und kleine Ströme;
- `10A` oder `A` - separate Buchse für großen Strom.

Vor der Messung immer überprüfen:

- welche Buchse die rote Sonde einfügt ist;
- welcher Modus ausgewählt ist;
- was genau Sie messen werden.

Ein häufiger Fehler: Nach Strommessung vergessen Sie, die Sonde von `A` zurück auf `V/Ohm` zu bewegen, versuchen dann Spannung zu messen. Dies kann einen Kurzschluss verursachen.

## DC-Spannung messen

DC ist direkte (konstante) Spannung. In unseren Geräten ist dies normalerweise:

- `3.3V`;
- `5V`;
- `12V`;
- `24V`.

Verfahren:

1. Schwarze Sonde in `COM`.
2. Rote Sonde in die `V`-Buchse.
3. DC-Spannungsmodus wählen: normalerweise `V` mit gerader Linie.
4. Schwarze Sonde auf negativ oder `GND`.
5. Rote Sonde auf positiv.
6. Display lesen.

Wenn ein Minuszeichen vor der Zahl auf dem Display erscheint, sind die Sonden vertauscht. Dies ist nützlich: Sie können Polarität so bestimmen.

![Digital-Multimeter mit Sonden](../../../img/05-tools/02-digital-multimeter.jpg)

*Quelle: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Aneng_AN870_multimeter_02.jpg), Retired electrician, CC0 Public Domain*

## Wo man Spannung misst

Begrenzen Sie sich nicht auf die Stromversorgungsausgabe.

Überprüfen Sie:

- auf Stromversorgungsterminals;
- auf Board-Eingang;
- auf Lasten-Terminals;
- auf einem DC-DC-Modul;
- auf Lüfter;
- auf Servo;
- auf LED-Streifen.

Wenn Stromversorgung 24V zeigt aber Last zeigt merklich weniger, Sag auf Drähten, Terminals oder Steckern suchen.

Für Stromversorgungsdiagnose ist es wichtig, unter Last zu messen, nicht nur im Leerlauf.

## AC-Spannung messen

AC ist alternierende Spannung, wie 110-230V aus dem Netz.

Netzspannung ist gefährlich.

Wenn Sie nicht verstehen, was Sie tun, messen Sie nicht offene Netzteile mit einem Multimeter. Besser, fertig sichere Module, geschlossene Terminals und Fachhelp nutzen.

Wenn Sie doch messen, benötigen Sie:

- Multimeter mit Sicherheitskategorie **CAT II** oder **CAT III** — dies steht auf dem Gerätekörper neben Spannung, zum Beispiel `CAT II 600V`. CAT I ist für Haushaltsnetz nicht geeignet. CAT III und CAT IV bieten extra Sicherheit für komplexere Installationen;
- ordnungsgemäß funktionierende Sonden mit einer Kategorie nicht niedriger als das Multimeter;
- trockene Hände;
- geschlossene und stabile Montage;
- Verständnis, wo Phase und Nullleiter sind;
- keine versehentlich offenen Kontaktpunkte.

Für die meisten Aufgaben mit Niederspannungselektronik reichen DC-Messungen aus.

## Kontinuitätsprüfung

Kontinuität zeigt, ob zwei Punkte elektrisch verbunden sind.

Es ist nützlich zu überprüfen:

- ob ein Draht intakt ist;
- ob `GND` verbunden ist;
- ob ein Kabel nicht gebrochen ist;
- ob eine Schaltfläche funktioniert;
- ob eine Sicherung intakt ist;
- ob benachbarte Kontakte kurzgeschlossen sind.

Verfahren:

1. Stromversorgung ausschalten.
2. Multimeter auf Kontinuitätsmodus einstellen: normalerweise Schallsymbol oder Diodenzeichen.
3. Sonden zusammen berühren - es sollte ein Piepton ertönen.
4. Die zwei Punkte berühren, die Sie überprüfen möchten.
5. Wenn es piept, gibt es eine leitende Verbindung zwischen den Punkten.

Kontinuitätsprüfung wird an einer stromfreien Schaltung durchgeführt.

## Widerstand

Widerstand wird in Ohm gemessen.

Für unsere Aufgaben ist dies nötig um:

- einen Thermistor zu überprüfen;
- auf gebrochenen Draht überprüfen;
- eine Sicherung überprüfen;
- festzustellen, ob es einen Kurzschluss gibt;
- einen Widerstand zu überprüfen.

Wichtig: Widerstand wird nur an einer stromfreien Schaltung gemessen.

Wenn Sie Widerstand an einem energiehaltigen Board messen, können Sie falsche Messwerte oder Schaden am Multimeter erhalten.

## Thermistor testen

Für einen typischen NTC `100K` bei Raumtemperatur erwarten Sie etwa `100 kOhm`.

Wenn das Multimeter zeigt:

- `OL` oder Unendlich - wahrscheinlich offener Stromkreis;
- fast `0 Ohm` - wahrscheinlich Kurzschluss;
- Wert stark schwankend, wenn Sie den Draht bewegen - schlechter Kontakt;
- Widerstand bei Wärmung durch Ihre Finger abnehmend - sieht aus wie lebender NTC.

Genaue Werte hängen vom Thermistor-Typ und der Temperatur ab.

## Strom messen

Strommessung ist gefährlicher als Spannungsmessung.

Spannung wird parallel gemessen: Sonden berühren zwei Punkte.

Strom wird in Serie gemessen: Sie müssen den Stromkreis unterbrechen und das Multimeter inline verbinden, damit Strom durch das Gerät fließt.

Fehler - Multimeter in Strommodus stellen und die Sonden an Plus und Minus der Stromversorgung berühren. Das ist fast ein Kurzschluss durch das Multimeter.

Für einen Anfänger ist es besser zu:

- zuerst Strom aus Leistung berechnen;
- fertig Wattmeter/USB-Stromzähler/DC-Stromzähler verwenden;
- Strom nur messen, wenn Sie verstehen, wie man das Multimeter in Serie verbindet;
- mit korrektem Bereich und korrektem Hafen beginnen.

## Sicherung überprüfen

Sicherung an stromfreier Schaltung überprüfen.

Methoden:

- Kontinuität;
- Widerstandsmessung.

Eine gute Sicherung zeigt normalerweise Kontinuität und hat sehr niedrigen Widerstand.

Eine durchgebrannte Sicherung zeigt normalerweise keine Kontinuität.

Wenn eine Sicherung durchbrannte, können Sie nicht einfach eine höher bewertete einsetzen. Zuerst die Ursache finden.

## Wie man das Multimeter nicht ausbrennt

Minimale Regeln:

- Mode vor Messung überprüfen;
- rote Sondenbuchse vor Messung überprüfen;
- Widerstand nicht an energiehaltiger Schaltung messen;
- Strom nicht wie Spannung messen;
- nicht in 110-230V AC ohne Verständnis für Sicherheit gehen;
- mit höherem Bereich beginnen, wenn Multimeter nicht auto-Bereich ist;
- funktionierende Sonden verwenden;
- Metalltippel nicht mit Fingern berühren.

## Praktische Szenarien

24V-Stromversorgung überprüfen:

1. DC-Spannungsmodus.
2. Schwarze Sonde auf Negativ.
3. Rote Sonde auf Positiv.
4. Sollte etwa 24V zeigen.

Lüfter überprüfen:

1. Spannung auf Lüfter-Stecker messen.
2. Polarität überprüfen.
3. Spannung beim Start überprüfen.

Auf gebrochenen Draht überprüfen:

1. Stromversorgung trennen.
2. Kontinuitätsmodus.
3. Sonden auf beide Enden des Drahts.
4. Kein Piepton - möglicher offener Stromkreis.

Auf Kurzschluss zwischen `+` und `GND` überprüfen:

1. Stromversorgung trennen.
2. Kontinuität zwischen `+` und `GND` überprüfen.
3. Wenn es piept, wo es nicht sollte, auf Kurzschluss suchen.

## Das Wesentliche

- Für DC-Spannung verwende `V`-Modus mit gerader Linie.
- Widerstand und Kontinuität werden nur an stromfreien Schaltungen durchgeführt.
- Strom wird in Serie, nicht parallel gemessen.
- Nach Strommessung, Sonde von `A` zurück zur normalen `V/Ohm`-Buchse bewegen.
- Netzspannung ist gefährlich; offene 110-230V-Teile ohne Verständnis für Sicherheit nicht messen.
- Multimeter unter Last offenbart oft Probleme, die im Leerlauf unsichtbar sind.

## Referenzmaterialien

- [SparkFun: How to Use a Multimeter](https://learn.sparkfun.com/tutorials/how-to-use-a-multimeter/all) - praktischer Leitfaden zu Spannung, Strom, Widerstand, Kontinuität und Multimeter-Buchsen.
- [Fluke: How to Measure Resistance](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-resistance) - sichere Widerstandsmessung.
- [Fluke: How to Measure AC Voltage](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-ac-voltage) - AC-Spannungsmessung und Sonden-Verbindungsreihenfolge.
- [Fluke: How to Test for Continuity](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-test-for-continuity) - Kontinuitätsprüfung und Suche nach offenem Stromkreis.
- [Fluke: Choosing the correct fuse for your tester](https://www.fluke.com/en-us/learn/blog/digital-multimeters/choosing-the-correct-fuse-for-your-tester) - warum Stromeingabebuchsen ordentliche Sicherungen mit korrekter Spannung und Unterbrechungsleistung benötigen.
