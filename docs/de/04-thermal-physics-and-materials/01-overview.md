# Thermophysik und Materialien

Dieser Abschnitt ist für Geräte mit einem Heizer, einer Kammer, einem Filamenttrockner, einem Filter mit wärmerer Luft, Luftkanälen, Lüftern, Isolierung oder gedruckten Teilen in der Nähe hoher Temperaturen notwendig.

Sie finden hier keinen akademischen Physikkurs. Das Ziel ist praktisch: verstehen, wohin die Wärme geht, warum das Gehäuse ungleichmäßig heiß wird, warum ein Material für eine Kammerwand geeignet ist, während ein anderes erweichen, rauchen oder zum Brandrisiko werden kann.

## Warum das wichtig ist

In einem einfach beheizten Gerät kann man nicht nur so denken:

```text
Heizer eingebaut -> es ist heiß geworden
```

In der Praxis muss man andere Fragen beantworten:

- wohin geht die Wärme vom Heizer;
- wo entstehen Hotspots;
- was sieht der Temperatursensor;
- hält das Material längeres Heizen aus;
- was passiert bei Lüfterausfall;
- was passiert bei Fest-MOSFET/SSR;
- landen Draht, Terminal oder Kunststoff in der Überhitzungszone;
- gibt es unabhängigen Überhitzungsschutz.

Ein Gerät kann auf dem Display `45°C` angezeigt werden, aber neben dem Heizer, Terminal oder in der Luftleitung kann es viel heißer sein. Daher ist nicht nur die Zielkammertemperatur wichtig, sondern auch die lokalen Temperaturen der Teile.

## Drei Wärmegangarten

Wärme überträgt sich auf drei Hauptwegen:

![Drei Wärmeübertragungsmechanismen: Leitung, Konvektion und Strahlung](../../img/04-thermal-physics-and-materials/01-heat-transfer-kettle.png)

*Quelle: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Kettle-convection-conduction-radiation.png), P.wormer, CC BY-SA 3.0*

**Wärmeleitung** - Wärme geht durch ein Material. Zum Beispiel leitet eine Metallhalterung Wärme schnell von einer heißen Zone zum Gehäuse.

**Konvektion** - Wärme wird von einem Luftstrom getragen. Zum Beispiel leitet ein Lüfter Wärme vom Heizer ab und verteilt sie in der Kammer.

**Strahlung** - eine heiße Oberfläche überträgt Wärme durch Infrarotstrahlung. Zum Beispiel kann ein stark beheiztes Element nahegelegenen Kunststoff ohne direkten Kontakt heizen.

In einem echten Gerät funktionieren alle drei Mechanismen schnell immer gleichzeitig.

## Material ist Teil des Thermischen Systems

Das Material des Gehäuses, der Wand, des Luftkanals oder der Montage beeinflusst das Temperaturregime.

Metall:

- leitet Wärme gut;
- kann Wärme aus der heißen Zone ableiten;
- kann die äußere Oberfläche heiß machen;
- löst das Isolations- und Elektrische-Sicherheitsproblem nicht von selbst.

Kunststoff:

- leitet Wärme schlecht;
- kann für ein Gehäuse bequem sein;
- kann erweichen und Festigkeit verlieren;
- kann entflammbar sein oder bei Überhitzung rauchen.

Isolierung:

- reduziert Wärmeverlust;
- hilft, die Kammertemperatur zu halten;
- kann lokale Überhitzung verstärken;
- benötigt Schutzschicht und Brandschutzprüfung.

Es gibt kein universelles "bestes Material". Es gibt ein Material, das für einen bestimmten Ort, eine Temperatur, eine Last und ein Fehlerszenario geeignet ist.

## Betriebstemperatur ist nicht Schmelztemperatur

Anfänger schauen oft nur auf die Schmelztemperatur. Das ist ein Fehler.

Das Material kann früher ungeeignet werden:

- erweichen;
- Form verlieren;
- schrumpfen;
- Festigkeit verlieren;
- anfangen zu riechen;
- Zersetzungsprodukte freisetzen;
- entflammbarer werden.

Für Gehäuse, Montage oder Luftkanal ist die zulässige Betriebstemperatur, Erweichungstemperatur, Brandeigenschaften und Herstellerempfehlungen wichtiger.

## Luft muss richtig fließen

Ein Lüfter in einem beheizten Gerät ist nicht „zum Anschauen“ da. Er bestimmt, wie Wärme aus dem Heizer entweicht.

Ohne ordentliche Strömung:

- Heizer kann lokal überhitzen;
- Kammer heizt sich ungleichmäßig auf;
- Sensor zeigt möglicherweise nicht die richtige Temperatur an;
- Nachbarteile können heißer als erwartet werden;
- PID-Regelung funktioniert schlechter.

Aber der Lüfter muss auch richtig ausgewählt und installiert werden: Durchfluss, Gegendruck, Richtung, Filter, Sieb und Luftkanal können das Ergebnis vollständig verändern.

## Was man bei jedem beheizten Gerät überprüfen sollte

Vor Montage und erstem Test überprüfen:

- Heizer-Leistung;
- Temperatur neben dem Heizer;
- Lufttemperatur nach dem Heizer;
- Temperatur der Terminals und Drähte;
- Temperatur des Gehäuses und gedruckter Teile;
- ob das Material Betriebstemperatur mit Sicherheitsspielraum aushält;
- ob brennbares Material in der Nähe der heißen Zone ist;
- gibt es eine Sicherung;
- gibt es unabhängigen Überhitzungsschutz;
- was passiert bei Lüfterausfall;
- was passiert bei Ausfällen des Temperatursensors.

Der erste Test wird unter Beobachtung und mit der Möglichkeit, die Stromversorgung schnell zu unterbrechen, durchgeführt.

## Wie man diesen Abschnitt liest

Der Abschnitt besteht aus drei praktischen Themen:

- [Wärmeleitung](02-thermal-conductivity.md) - warum Metall, Kunststoff, Glas und Isolierung sich unterschiedlich verhalten.
- [Materialien, Entflammbarkeit und schädliche Emissionen](03-material-safety.md) - wie man Material in der Nähe von Wärme wählt und was man im Datenblatt liest.
- [Konvektion und Luftstrom](04-convection-and-airflow.md) - warum derselbe Heizer mit unterschiedlichem Luftstrom unterschiedlich funktioniert.

## Wichtigste Erkenntnis

Ein beheiztes Gerät ist nicht nur ein Heizer und Sensor. Es ist ein Thermisches System: Heizer, Luft, Gehäuse, Materialien, Drähte, Terminals, Lüfter, Sensoren und Notschutz.

Wenn ein Material bequem, billig und leicht zu schneiden ist, bedeutet das nicht, dass es in die Nähe eines Heizers gestellt werden kann. Überprüfen Sie zunächst die Temperatur, Wärmeübertragung, Brandeigenschaften, Dokumentation und Fehlerszenarien.

## Materialien zu diesem Thema

- [U.S. Department of Energy: Principles of Heating and Cooling](https://www.energy.gov/energysaver/principles-heating-and-cooling) - einfache Erklärung von Wärmeleitung, Konvektion und Strahlung.
- [NASA Glenn Research Center: Heat Transfer](https://www1.grc.nasa.gov/beginners-guide-to-aeronautics/heat-transfer-3/) - grundlegende Erklärung der Wärmeübertragung von einem heißeren Körper zu einem kälteren.
- [Engineering ToolBox: Conductive Heat Transfer](https://www.engineeringtoolbox.com/conductive-heat-transfer-d_428.html) - Wärmeleitung, Temperaturgradient, Materialdicke und mehrschichtige Wände.
- [UL Solutions: Combustion Fire Tests for Plastics](https://www.ul.com/services/combustion-fire-tests-plastics) - warum Kunststoffmaterialien nach Brennverhalten verglichen werden, nicht nur nach Schmelztemperatur.

## Siehe auch

- [iDryer-Dokumentation: Heizer](../03-common-components/02-heaters.md) - lokaler Artikel über Heizerauswahl, Stromschalter, Sensor und unabhängigen Überhitzungsschutz.
