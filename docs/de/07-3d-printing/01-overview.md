# 3D-Druck

Dieser Abschnitt ist kein 3D-Druck-Kurs.

Er dient einem anderen Zweck: Um zu verstehen, welche gedruckten Teile sicher in einem selbstgebauten Gerät verwendet werden können und welche zu einer Risiko in der Nähe von Heizungen, Elektronik, Verdrahtung und beweglichen Teilen werden.

In Projekten wie iDryer wird 3D-Druck normalerweise für folgende Zwecke verwendet:

- Gehäuse;
- Abdeckungen;
- Luftkanäle;
- Lüfterbefestigungen;
- Sensorhalter;
- Führungen;
- Griffe und Klammern;
- dekorative oder Service-Platten.

Ein Teil zu drucken ist einfach. Es mehrere Monate sicher in einem warmen Gehäuse funktionieren zu lassen, ist schwieriger.

## Wichtigste Fragen

Bevor du ein Teil für ein Gerät druckst, musst du nicht nur „passt das STL in den Slicer" antworten, sondern mehrere Fragen beantworten:

- wo wird das Teil platziert;
- welche Temperatur wird dort sein;
- ist ein Heizer in der Nähe;
- ist 110-230V AC in der Nähe;
- wird das Teil eine Last halten;
- wird es Drähte berühren;
- wird es heiße Luft lenken;
- kann es ersetzt oder gewartet werden;
- was passiert, wenn es sich verformt.

Falls die Verformung eines Teils einen Sensor verschieben, den Luftstrom blockieren, einen Draht näher an einen heißen Bereich bringen oder eine Heizerbefestigung lockern kann, ist es nicht mehr nur ein „kosmetischer Fehler".

## STL ist keine Montageanleisung

STL beschreibt die Form eines Teils, teilt dir aber nicht mit:

- aus welchem Material du es druckst;
- in welcher Ausrichtung es zu drucken ist;
- wie viele Wände zu verwenden sind;
- welche Füllung anzulegen ist;
- wo Stützen benötigt werden;
- welche Schrauben zu verwenden sind;
- welche Temperatur das Teil verträgt;
- in welche Richtung es schwächer wird.

Dasselbe Modell kann je nach Material, Ausrichtung und Arbeitsbedingungen eine normale Abdeckung oder eine schlechte Strukturhalterung sein.

Daher benötigt ein funktionierendes Teil nicht nur ein STL, sondern auch Kontext: Material, Druckeinstellungen, Installationslage, Last und Temperaturregime.

## Material ist wichtiger als Erscheinung

Für einen Prototypen funktioniert PLA oft. Es druckt leicht und produziert ein schönes aussehendes Teil.

Aber für Teile in der Nähe von Wärme ist PLA eine schlechte Wahl. Das Problem ist nicht, dass es sofort schmilzt, sondern dass es allmählich an Steifheit und Form bei Temperaturen in einem geschlossenen Gehäuse oder in der Nähe eines Heizers verlieren kann.

Für funktionierende Teile um einen Trockner, Kammer oder Heizer verwendest du normalerweise:

- ABS;
- ASA;
- wärmebeständigere technische Materialien, wenn du Erfahrung und einen geeigneten Drucker hast.

Material wird basierend auf Bedingungen ausgewählt:

- Betriebstemperatur;
- Steifheit;
- Schlagzähigkeit;
- Schrumpfung und Verformung;
- Geruch und Emissionen beim Drucken;
- Verhalten beim Erhitzen;
- Hersteller-Dokumentation.

## Temperatur im Gehäuse

Die Temperatur in einem geschlossenen Gehäuse unterscheidet sich von der Raumtemperatur.

Selbst wenn der Heizer das Kunststoff nicht berührt, kann ein Teil sein:

- in einem heißen Luftstrom;
- in der Nähe des Heizers;
- in der Nähe einer Wärmeleitung;
- in der Nähe der Stromversorgung;
- in einem Bereich mit schlechter Belüftung;
- auf einer Wand, die sich langsam erwärmt.

Daher kannst du die Sicherheit nicht mit der Aussage „das Teil berührt den Heizer nicht" beurteilen. Du musst verstehen, welche Temperatur an diesem Ort während des längeren Betriebs sein wird.

![Zonen in einem gedruckten Gehäuse für ein beheiztes Gerät](../../../img/07-3d-printing/01-printed-device-zones.svg)

## Festigkeit hängt von der Schichtrichtung ab

FDM-Teile sind nicht in alle Richtungen gleich stark.

Die Schichtrichtung beeinflusst, wie ein Teil bricht:

- entlang der Kunststofflinien ist es normalerweise stärker;
- zwischen Schichten ist es oft schwächer;
- dünne Pfosten und Klammern können zwischen Schichten brechen;
- Schrauben können ein Teil delaminierten, wenn die Geometrie nicht dafür ausgelegt ist.

Bei strukturellen Halterungen ist es wichtig, zu überlegen, wohin die Last gehen wird.

Wenn eine Lüfterhalterung einfach an einer Wand hängt, ist dies eine Sache. Falls eine Halterung einen Heizer oder eine Spulenachse hält, werden die Druckausrichtung und die Wandstärke wichtig.

## Gehäuse muss wartbar sein

Ein gutes Gehäuse ist nicht nur eine schöne Kiste.

Es muss ermöglichen:

- Zugang zu Klemmen;
- Austausch eines Lüfters;
- Inspekt eines Temperatursensors;
- Anziehen von Befestigungselementen;
- Entfernung eines Controllers;
- Austausch eines Drahtes;
- zu sehen, ob etwas überhitzt oder verdunkelt ist.

Falls du halbes Gerät auseinandernehmen musst, um auf eine Sicherung oder Klemme zuzugreifen, wird es weniger oft gewartet. Dies ist schlechte Engineeringpraxis.

## Gedrucktes Teil darf Sicherheit nicht beeinträchtigen

Ein gedrucktes Gehäuse kann nützlich sein, aber es muss einen kleinen Fehler nicht zu einer gefährlichen Situation machen.

Schlechte Szenarien:

- Heizer-Halterung erweicht;
- Luftkanal verzogen und Luftstrom durch Heizer reduziert;
- Thermistor-Halter verschoben;
- Draht rieb sich gegen eine scharfe Kante;
- Terminal endete eng gegen Kunststoff;
- Abdeckung blockierte Belüftung der Stromversorgung;

Bei heißen und belasteten Zonen ist es besser, so zu denken: Falls ein gedrucktes Teil sich verformt, sollte das Gerät entweder sicher bleiben oder einen Fehler eingeben, nicht blindlings weiter heizen.

## Was wird in diesem Abschnitt behandelt

Der Abschnitt behandelt mehrere praktische Themen:

- `02-what-is-stl.md` - warum STL kein Material, Ausrichtung, Festigkeit oder Montageanleitungen enthält.
- `03-materials-petg-abs-asa.md` - grundlegende Wahlmöglichkeiten zwischen PETG, ABS und ASA.
- `04-heat-resistant-materials.md` - wie man über Teile in der Nähe von Wärme denken sollte.
- `05-enclosure-design.md` - Gehäusezonen, Belüftung, Befestigung, Zugang und Verdrahtung.
- `06-why-pla-is-risky.md` - warum PLA für Prototypen praktisch ist, aber in der Nähe von Wärme riskant ist.

## Was dieser Abschnitt nicht tut

Es gibt keinen kompletten 3D-Druck-Kurs hier.

Wir werden nicht tauchen ein in:

- alle Kunststoffe der Welt;
- Rückzugs-Einstellungen;
- dekorative Nachbearbeitung;
- künstlerische Modelle;
- perfekte Drucker-Kalibrierung;
- spezifische Filament-Brand-Auswahl.

Der Fokus ist einfach: Teile für ein echtes Gerät müssen stark genug, wärmebeständig, wartbar und sicher sein.

## Wichtigste Erkenntnisse

- STL ist nur Geometrie, nicht sichere Montageanleitungen.
- Material wird basierend auf Betriebstemperatur und Last ausgewählt, nicht Erscheinung.
- PLA ist praktisch für Prototypen, aber riskant in der Nähe von Wärme.
- Druckausrichtung beeinflusst die Festigkeit.
- Gehäuse sollte die heiße Zone, Elektronik, Stromverdrahtung und Benutzerzone trennen.
- Ein gedrucktes Teil sollte nicht das einzige sein, das Gerätesicherheit schützt.

## Referenzen

- [Prusa Knowledge Base: Material guide](https://help.prusa3d.com/category/material-guide_220) - Übersicht über beliebte Materialien, Druckbedingungen und Eigenschaften.
- [Prusa Knowledge Base: PLA](https://help.prusa3d.com/article/pla_2062) - Beschreibung von PLA als einfaches Material für Prototypen und Teile ohne hohe Temperaturlast.
- [Prusa Knowledge Base: Enclosure guidepost](https://cdn.help.prusa3d.com/article/enclosure-guidepost_366332) - warum eine geschlossene Druckkammer erforderlich ist und wie Umgebungstemperatur Druck und Materialien beeinflusst.
- [Bambu Lab: 3D Printer Filament Comparison Guide](https://bambulab.com/en-us/filament-guide) - vergleichende Tabelle von Materialien, einschließlich PLA, PETG, ABS, ASA und technische Kunststoffe.
- [Makelab: Is 3D printing strong enough for functional parts?](https://help.makelab.com/help/article/is-3d-printing-strong-enough-for-functional-parts) - praktische Notizen zu Material, Druckausrichtung, Wänden, Füllung und funktionalen Teilen.
