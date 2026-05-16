# PETG, ABS und ASA

PETG, ABS und ASA werden oft als nächste Materialien nach PLA angesehen, wenn ein Teil nicht nur hübsch, sondern funktionierend sein muss.

In Geräten um einen Trockner, eine Druckerkammer oder einen Heizer beeinflußt die Materialauswahl die Sicherheit. Ein Teil kann nach dem Druck normal aussehen, aber nach einer Stunde in einem warmen Gehäuse kann es anfangen, weich zu werden, den Luftkanal zu verzerren, Befestigungselemente zu lockern oder einen Sensor zu verschieben.

## PETG

PETG ist oft ein gutes erstes funktionierendes Material nach PLA.

Es normalerweise:

- druckt leichter als ABS und ASA;
- riecht weniger beim Drucken;
- verzieht sich weniger;
- handhabt Temperatur besser als PLA;
- funktioniert gut für viele Halterungen, Abdeckungen, Halter und Luftkanäle unter moderaten Bedingungen.

Für Geräte wie iDryer kann PETG gut funktionieren für:

- Lüfter-Halterung weg vom Heizer;
- Elektronik-Abdeckung;
- Sensor-Halter in moderater Temperaturzone;
- Luftkanal für nicht-zu-heißer Luft;
- Prototyp-Gehäuse.

Aber PETG wird nicht automatisch wärmebeständig für irgendwelche heißen Zonen.

Falls ein Teil in der Nähe eines Heizers, in einem heißen Luftstrom oder unter konstanter Last sitzt, kann PETG allmählich an Steifheit verlieren und sich verformen.

## ABS

ABS ist ein technischeres Material als PLA und PETG.

Es funktioniert normalerweise besser für:

- Teile mit mechanischer Last;
- Gehäuse in wärmerer Umgebung;
- Halterungen, wo PETG bereits fragwürdig ist;
- Teile needing bessere Temperatur-Beständigkeit.

Nachteile von ABS:

- verzieht sich mehr;
- benötigt eine geschlossene Kammer oder stabile warme Umgebung beim Drucken;
- bemerkbar riechend;
- kann schädliche Dämpfe beim Drucken abgeben;
- nicht geeignet zum Drucken in einem Wohnbereich ohne Belüftung.

Wähle nicht ABS nur weil „es stärker ist". Du musst wissen, wie man es druckt. Schlecht gedrucktes ABS mit Delamination und interner Spannungen kann schlechter als gut gedrucktes PETG ausfallen.

## ASA

ASA ist ähnlich zu ABS in Zweck, aber oft besser für Außen- und technische Teile geeignet.

Vorteile von ASA:

- gute Temperatur-Beständigkeit;
- UV-Beständigkeit;
- weniger Geruch im Vergleich zu ABS, aber Geruch und Dämpfe sind noch vorhanden;
- normalerweise verzieht sich weniger als ABS;
- geeignet für funktionierende technische Teile.

Nachteile:

- benötigt auch gute Druckbedingungen;
- für große Teile ist eine geschlossene Druckkammer bevorzugt;
- schädliche Dämpfe möglich beim Drucken;
- Material ist teurer und anspruchsvoller als PETG.

ASA ist oft vernünftiger als ABS für Teile, die lange in einem Gerät oder in der Nähe von Fenstern/Sonnenlicht leben. Aber für eine kleine interne Elektronik-Abdeckung ist ASA nicht immer notwendig.

## Wo wird welches Material verwendet

Ein raues Leitfaden:

| Aufgabe | PETG | ABS/ASA |
| --- | --- | --- |
| Kalter Prototyp | funktioniert | funktioniert, aber oft übertrieben |
| Elektronik-Abdeckung weg von Wärme | funktioniert | funktioniert |
| Lüfter-Halter in moderater Zone | funktioniert | funktioniert |
| Luftkanal neben warmem Luftstrom | manchmal funktioniert | oft besser |
| Teil in heißer Kammer | überprüfe Temperatur | oft sinnvoller |
| Halter neben Heizer | riskant | benötigt auch Überprüfung, manchmal ist Metall erforderlich |
| Teil unter konstanter Last in Wärme | vorsichtig | besser, aber nicht automatisch sicher |
| Teil neben 110-230V AC | Material ist nicht die einzige Antwort | Material ist nicht die einzige Antwort |

Dies ist keine Berechtigungstabelle. Dies ist nur Anfänger-Logik.

Die echte Lösung hängt von Temperatur, Entfernung zum Heizer, Luftstrom, Last, Laufzeit und Konsequenzen des Ausfalls ab.

## Schmelztemperatur ist nicht der wichtigste Parameter

Für Gehäuse und Halterungen, was wichtig ist, ist nicht die Temperatur, bei der Material schmilzt.

Wichtiger ist wann es wird:

- erweichen;
- unter Last kriechen;
- Form verlieren;
- eine Schraube freisetzen;
- verzerren;
- Größe ändern.

Ein Teil kann lange vor dem Schmelzen gefährlich werden.

Zum Beispiel kann ein Sensor-Halter um nur wenige Millimeter verschoben werden. Äußerlich scheint dies unbedeutend, aber der Controller wird bereits die falsche Temperatur sehen.

## Drucken von ABS/ASA erfordert Bedingungen

ABS und ASA benötigen oft:

- eine geschlossene Kammer;
- hohe Bett-Temperatur;
- stabile Temperatur um das Teil;
- gute Bett-Adhäsion;
- Schutz vor Entwürfen;
- Raum-Belüftung;
- sorgfältige Filament-Trocknung, falls erforderlich.

Falls du ABS/ASA auf einem offenen Drucker druckst, kann ein großes Teil verziehen, reißen oder delaminiieren.

Für kleine Teile kannst du manchmal ohne eine perfekte geschlossene Kammer auskommen, aber für ein Gehäuse, Luftkanal oder langes Teil plane für richtige Druckbedingungen von Anfang an.

## Wähle Material nicht separat von Design

Material ist nur Teil der Lösung.

Selbst gutes Material wird schlechte Geometrie nicht retten:

- dünne Wände;
- kleine Pfosten für Schrauben;
- scharfe innere Ecken;
- Last senkrecht zu Schichten;
- schlechte Montage zum Gehäuse;
- keine Lücke zu heißen Teilen;
- blockierte Belüftung.

Falls ein Teil einen Heizer, Stromstecker oder Temperatursensor hält, musst du nicht nur über Kunststoff, sondern auch über Metall-Halterungen, Abschirmung, Lücken und Fail-Safe-Schutz denken.

## Praktische Regel

Bei einem einfachen Gerät kannst du so denken:

- PLA - Prototyp, Vorlage, kaltes dekoratives Teil.
- PETG - grundlegender Minimum für viele funktionierende Teile bei moderater Temperatur.
- ABS/ASA - besser für heiße und mechanisch belastete Teile, falls du sie drucken kannst.
- Metall, Glasfaser, Keramik oder vorgefertigte nicht entflammbare Teile - wo Kunststoff in der Nähe von Wärme nicht länger geeignet ist.

Falls ein Teile-Ausfall zu Überhitzung, Kurzschluss oder Kontakt zwischen Draht und heißem Teil führen kann, muss Material mit großem Sicherheitsspielraum gewählt und in echtem Zusammenbau getestet werden.

## Häufige Fehler

- Gedanke, PETG ist vollständig wärmebeständig;
- Drucken von ABS/ASA ohne geschlossene Kammer und Delamination;
- Materialauswahl basierend auf Internet-Rat ohne die Temperatur im Gehäuse zu kennen;
- Placement von PETG-Luftkanal zu nah am Heizer;
- Verwendung von ABS/ASA in einem Wohnbereich ohne Belüftung;
- Gedanke, dass das Tauschen von PLA für ASA das Design automatisch sicher macht;
- Nicht Überprüfung des Teils nach einer Stunde Betrieb bei echter Temperatur;
- Vergessen, dass Schrauben und Last Kunststoff über die Zeit verformen können.

## Wichtigste Erkenntnisse

- PETG ist oft ein gutes Minimum für funktionierende Teile, aber nicht für irgendwelche heißen Zonen.
- ABS und ASA handhaben Temperatur besser, aber sind schwieriger zu drucken und benötigen Belüftung.
- ASA schlägt normalerweise ABS in UV-Beständigkeit und riecht oft weniger, benötigt aber immer noch Sorgfalt.
- Material wird basierend auf echter Temperatur, Last und Ausfalls-Konsequenzen gewählt.
- Für Teile in der Nähe eines Heizers ist manchmal die richtige Antwort nicht Kunststoff, sondern Metall oder eine vorgefertigte Halterung.

## Referenzen

- [Prusa Knowledge Base: PETG](https://help.prusa3d.com/article/petg_2059) - PETG Beschreibung, Druck, Festigkeit, Temperatur-Beständigkeit und Grenzen.
- [Prusa Knowledge Base: ABS](https://cdn.help.prusa3d.com/article/abs_2058) - ABS Eigenschaften, Druck-Anforderungen, Verziehen und Dampf-Warnung.
- [Prusa Knowledge Base: ASA](https://help.prusa3d.com/article/asa_5078) - ASA als technisches Material mit Temperatur- und UV-Beständigkeit, plus geschlossene Kammer-Anforderungen.
- [Bambu Lab: 3D Printer Filament Comparison Guide](https://bambulab.com/en-us/filament-guide) - vergleichende Tabelle von Materialien: PLA, PETG, ABS, ASA, PC, PA und Composites.
- [Bambu Lab: ASA Filament Guide](https://bambulab.com/en-us/filament/asa) - kurze ASA Beschreibung, seine Vor- und Nachteile und Anwendungsfälle.
