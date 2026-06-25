# Strom, Spannung und Lastleistung

Bevor Sie einen Heizer, Lüfter, LED-Streifen, Servoantrieb oder ein anderes Modul anschließen, müssen Sie drei Dinge verstehen:

- Spannung;
- Strom;
- Leistung.

Ohne dies ist es leicht, das falsche Netzteil zu kaufen, den Draht zu überlasten, den Stecker zu schmelzen, ein MOSFET-Modul zu beschädigen oder die Last mit dem Controller zu verbinden, so dass er instabil funktioniert.

## Wo die Parameter zu finden sind

Spannung, Strom und Leistung sind normalerweise zu finden:

- auf dem Komponentengehäuse;
- auf dem Energieversorgungsetikett;
- auf der Produktseite;
- in der technischen Spezifikation;
- in der Anleitung;
- in der Schaltung des Boards oder im Pinout.

Wenn der Parameter nicht angegeben ist, ist dies kein kleineres Problem. Es ist ein Grund zu stoppen und herauszufinden, was genau Sie anschließen.

Für Komponenten aus dem 3D-Drucker-Zubehör sehen typische Parameter wie folgt aus:

- Lüfter: `24V 0.2A`;
- Heizer: `24V 100W`;
- LED-Streifen: `24V 9.6W/m`;
- Servoantrieb: `5V`, der Strom hängt von der Last ab;
- Controller-Board: Der maximale Strom für jeden Ausgang ist separat angegeben.

## Spannung muss übereinstimmen

Eine Last ist für eine bestimmte Spannung ausgelegt.

Beispiele:

- Lüfter kann `5V`, `12V` oder `24V` sein;
- LED-Streifen kann `5V`, `12V` oder `24V` sein;
- Servoantrieb wird oft mit `5V` oder `6V` bewertet;
- Heizer kann `12V`, `24V` oder `110-230V AC` sein.

Wenn Sie einen `24V`-Lüfter an `12V` anschließen, funktioniert er möglicherweise gar nicht oder funktioniert schwach. Wenn Sie einen `12V`-Lüfter an `24V` anschließen, kann er schnell ausfallen.

Die Hauptregel:

**Die Stromversorgungsspannung muss der Lastspannung entsprechen.**

Verbinden Sie ein Gerät nicht einfach mit einer höheren Spannung, nur weil der Stecker physisch passt.

## Leistung zeigt die Größe der Last

Leistung zeigt, wie viel Energie die Last verbraucht oder in Arbeit, Wärme, Licht oder Bewegung umwandelt.

Die Leistung wird in Watt gemessen: `W`.

Beispiele:

- `24V 5W` - kleine Last;
- `24V 24W` - etwa `1A`;
- `24V 120W` - bereits etwa `5A`;
- `24V 240W` - etwa `10A`.

Heizer verbrauchen typischerweise viel Leistung. Lüfter verbrauchen weniger, können aber einen hohen Einschaltstrom haben. LED-Streifen können eine kleine Last sein, wenn sie kurz sind, oder eine ernstzunehmende Last, wenn sie lang und hell sind.

## Strom belastet Drähte und Stromelemente

Der Strom zeigt, wie viel Elektrizität durch Drähte, Anschlüsse, Stecker und Stromelemente fließt.

Der Strom verursacht oft praktische Probleme:

- Drähte heizen sich auf;
- Anschlüsse werden dunkel;
- Stecker schmelzen;
- MOSFET überhitzt;
- Stromversorgung reicht nicht aus;
- Gerät startet neu, wenn die Last eingeschaltet wird;
- Sicherung löst nicht zufällig aus, sondern wegen echter Überbelastung oder Fehler.

Daher reicht es nicht aus, nur die Spannung zu kennen. Sie müssen den Strom berechnen.

## Berechnungsformel

Für die meisten einfachen Berechnungen benötigen Sie die Leistungsformel:

```text
P = U * I
```

Wobei:

- `P` - Leistung in Watt `W`;
- `U` - Spannung in Volt `V`;
- `I` - Strom in Ampere `A`.

Um den Strom zu finden:

```text
I = P / U
```

![Ohmsches Gesetz: Schaltung mit Spannungsquelle, Strom und Widerstand](../../img/01-electronics-basics/01-ohms-law-circuit.svg)

*Quelle: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Ohm%27s_Law_with_Voltage_source_TeX.svg), GorillaWarfare, CC0 Public Domain*

Diese Formel ist nicht für eine Prüfung. Sie wird benötigt, um zu verstehen, ob das Netzteil, der Draht, der Anschluss, das MOSFET-Modul, das Relais, das SSR oder der Board-Ausgang es aushalten kann.

## Schnelltabelle für 24V

In 3D-Druckern und Zubehör ist `24V` verbreitet. Zur schnellen Bewertung ist es nützlich, sich zu merken:

| Leistung | Strom bei 24V |
|---:|---:|
| `12W` | `0.5A` |
| `24W` | `1A` |
| `48W` | `2A` |
| `96W` | `4A` |
| `120W` | `5A` |
| `240W` | `10A` |
| `300W` | `12.5A` |

Dies sind Näherungswerte, aber für die erste Wahl des Netzteils, des Drahts und des Stromschalters sind sie sehr nützlich.

## Beispiel: 24V 100W Heizer

Sie haben einen Heizer:

```text
24V 100W
```

Berechnen Sie den Strom:

```text
I = 100W / 24V = 4.17A
```

Das bedeutet, dass folgende Komponenten mehr als `4.17A` aushalten müssen:

- Stromversorgung;
- Draht;
- Anschlüsse;
- Stecker;
- MOSFET oder SSR;
- Sicherung und Sicherungshalter;
- Board-Spuren, wenn der Heizer mit dem Board verbunden ist.

Wenn das Netzteil mit `24V 5A` bewertet wird, kommt es dem Load formal nahe, aber mit fast keinem Spielraum. Für ein echtes Gerät ist es besser, mehr zu nehmen.

## Beispiel: mehrere Lasten

Nehmen Sie an, ein `24V`-Gerät hat:

- Heizer `100W`;
- Lüfter `24V 0.2A`;
- LED-Streifen `24V 1A`;
- ein weiterer Lüfter `24V 0.15A`.

Berechnen Sie den Heizer:

```text
100W / 24V = 4.17A
```

Addieren Sie sie:

```text
4.17A + 0.2A + 1A + 0.15A = 5.52A
```

Ein minimales Stromversorgung "enger Sitz" würde etwa `24V 6A` sein, aber das ist keine gute Wahl für den Langzeitbetrieb. Mit `50%` Spielraum:

```text
5.52A * 1.5 = 8.28A
```

Praktisch sollten Sie eine `24V 9A`, `24V 10A` oder größere Stromversorgung anschauen, wenn das Gehäuse, die Kühlung und die Sicherheit dies erlauben.

## Spielraum ist obligatorisch

Stromversorgung, Verdrahtung, Anschlüsse und Strommodule können nicht genau nach dem berechneten Strom ausgewählt werden.

Für diesen Leitfaden gelten einfache Regeln für die grobe erste Bewertung:

**planen Sie mindestens 50% Spielraum**, es sei denn, die Dokumentation eines bestimmten Komponentensfordert mehr. Dies ist keine universelle Garantie, sondern eine grobe Schätzung. Die endgültige Auswahl wird nach technischen Spezifikationen, Temperatur im Gehäuse, Kühlung, Derate und tatsächlicher Erwärmung von Anschlüssen/Drähten vorgenommen.

Spielraum ist notwendig, weil:

- Stromversorgung wird heiß;
- Temperatur im Gehäuse kann höher als Raumtemperatur sein;
- Lüfter und Motoren haben Einschaltstrom;
- Kontakte altern und lockern sich;
- Anschlüsse haben Strom- und Temperaturgrenzen;
- SSR und MOSFET erzeugen Wärme;
- Stromversorgung kann Derate haben - Reduktion der maximalen Leistung bei hoher Temperatur oder schlechter Belüftung.

Industrienetzteile haben oft eine Derating-Kurve in der technischen Spezifikation – eine Kurve der reduzierten maximalen Leistung mit steigender Temperatur. Derate bedeutet, dass der Hersteller bei höherer Temperatur oder schlechterer Belüftung die maximal zulässige Leistung reduziert. Daher bedeutet das Label `240W` auf einem Netzteil nicht immer, dass es im geschlossenen heißen Gehäuse sicher `240W` liefert.

## Schwachstelle kann nicht das Netzteil sein

Selbst wenn das Netzteil leistungsfähig ist, kann die Schaltung an einer anderen Stelle schwach sein.

Sie müssen die gesamte Schaltung überprüfen:

- Stromversorgungsausgang;
- Draht;
- Klemmenleiste;
- Stecker;
- Sicherung;
- MOSFET-Modul;
- Relais oder SSR;
- Board-Spuren;
- die Last selbst.

Beispielsweise kann ein Netzteil `10A` aushalten, aber ein kleiner Stecker oder ein schlechter Schraubklemmer kann bereits bei niedrigerem Strom heiß werden. Dies ist besonders wichtig für Heizer und LED-Streifen.

## Was ist ein Stromschalter

Ein Stromschalter ist ein gesteuerter Schalter.

Der Controller speist eine schwere Last nicht direkt. Er gibt ein schwaches Steuersignal, und der Stromschalter schaltet den Laststrom ein oder aus.

Beispiele:

- MOSFET-Modul für `12V`/`24V` DC-Lasten;
- Relais;
- SSR;
- fertiger Last-Treiber;
- Standard-Power-Ausgang des Boards, wenn dieser für die benötigte Last bewertet wird.

Für Heizer, Lüfter, LED-Streifen und Motoren gilt die Regel fast immer:

**GPIO des Controllers speist die Last nicht. GPIO nur Kontrollen.**

## Ein bisschen über Ohms Gesetz

Ohms Gesetz bezieht sich auf Spannung, Strom und Widerstand:

```text
U = I * R
```

Für diesen Artikel ist die einfache Idee wichtig: Wenn Sie Spannung an eine Last anlegen, fließt Strom durch sie. Wie viel Strom fließt, hängt von der Last selbst ab.

Aber nicht alle Lasten verhalten sich gleich:

- Heizer ist eine nahe resistive Last;
- Lüfter und Motor haben Einschaltstrom;
- Servoantrieb erhöht bei Blockierung scharf den Strom;
- LED-Streifen verbrauchen Strom je nach Länge und Helligkeit;
- Elektronisches Modul kann bei Einschaltung transienten Strom haben.

Daher ist es für ein echtes Gerät besser, Daten aus technischen Spezifikationen zu entnehmen oder den Strom mit einem Multimeter / Labornetzteil zu messen, wenn es sicher ist.

## Was vor dem Anschließen zu überprüfen ist

Bevor Sie die Last anschließen, beantworten Sie:

1. Für welche Spannung ist die Last bewertet?
2. Ist es eine DC- oder AC-Last?
3. Welche Leistung oder Strom ist angegeben?
4. Welchen Strom erhalten Sie aus der Formel `I = P / U`?
5. Welche anderen Lasten sind auf derselben Stromversorgung?
6. Gibt es mindestens `50%` Spielraum?
7. Halten Drähte, Anschlüsse, Stecker und Board es aus?
8. Was kontrolliert die Last: MOSFET, Relais, SSR oder Standard-Ausgang?
9. Wird eine Sicherung benötigt?
10. Was passiert, wenn ein Kurzschluss, Motorblockie oder Lüfterausfall auftritt?

Wenn dies ein Heizer oder Netzspannung `110-230V AC` ist, sind die Sicherheitsanforderungen höher. Der Netzabschnitt kann nicht durch Vermutung zusammengebaut werden: Sie benötigen ein geeignetes Gehäuse, eine Sicherung, Isolierung, Schutzleiter `PE`, Zugentlastung für Drähte und Überprüfung durch eine qualifizierte Person.

## Das Wichtigste

- Stromversorgungsspannung muss der Lastspannung entsprechen.
- Leistung zeigt die Größe der Last.
- Strom zeigt die Last auf Drähten, Anschlüssen, Steckern und Stromelemente.
- Grundformel: `I = P / U`.
- In einem `24W`-System ist `1A` etwa `120W`, `5A` ist etwa `240W`, `10A` ist etwa `10A`.
- Strömungen aller Lasten in einer Stromversorgung addieren sich.
- Sie benötigen mindestens `50%` Spielraum für grobe erste Schätzung; genaue Auswahl wird nach technischen Spezifikationen, Temperatur, Kühlung und Derate vorgenommen.
- Der Schwachpunkt kann nicht das Netzteil sein, sondern ein Anschluss, Stecker, Draht, MOSFET oder Board-Spur.
- GPIO des Controllers speist keine schwere Last, nur ein Stromschalter kontrolliert.

## Referenzmaterialien

- [SparkFun: Voltage, Current, Resistance, and Ohm's Law](https://learn.sparkfun.com/tutorials/voltage-current-resistance-and-ohms-law) - klare grundlegende Erklärung von Spannung, Strom, Widerstand und Ohms Gesetz.
- [DigiKey: Ohm's Law Calculator](https://www.digikey.com/en/resources/conversion-calculators/conversion-calculator-ohms) - Taschenrechner zur Berechnung von Spannungs-, Strom-, Widerstands- und Leistungsbeziehungen.
- [Mean Well: How to read a derating curve](https://meanwellpowersupplies.com/technical-articles/faq/how-to-read-a-derating-curve/) - warum die maximale Leistung eines Netzteils von Temperatur, Belüftung und Eingangsspannung abhängt.
- [DigiKey: Selecting and Applying AC/DC Power Supplies](https://www.digikey.com/en/articles/selecting-and-applying-ac-dc-power-supplies) - Auswahl eines Netzteils unter Berücksichtigung von Temperatur, Derate, Kabeln und Last-Typ.
- [Weidmuller: Derating curve / current-carrying capacity](https://www.weidmuller.com/en/products/connectivity/pcb_terminals_and_connectors/derating_curve.jsp) - warum die maximale Stromstärke von Anschlüssen und Steckverbindern von Temperatur und Design abhängt.
