# Gehäusedesign

Ein Gerätegehäuse ist nicht einfach eine Kiste um Komponenten.

Es muss sicher halten:

- Heizer;
- Lüfter;
- Sensoren;
- Stromversorgung;
- Controller;
- Anschlüsse;
- Drähte;
- Steckverbinder;
- Display oder Schalter;
- mechanische Teile.

Bei einem beheizten Gerät kann ein schlechtes Gehäuse auch mit guter Elektronik ein Problem schaffen: Luftstrom blockieren, den Controller überhitzen, einen Draht durchscheuern oder Kunststoff zu nahe an ein heißes Teil bringen.

## Mit Komponentenlayout beginnen

Bevor das Gehäuse modelliert wird, müssen echte Komponenten angeordnet werden:

- Controller-Board;
- Stromversorgung oder DC-DC-Wandler;
- Lüfter;
- Heizer;
- Temperatursensor;
- Anschlüsse;
- Sicherung;
- Drähte;
- Steckverbinder;
- Schalter, Display, RFID oder andere Module.

Das Gehäuse wird nach echten Teileabmessungen entworfen, nicht "ungefähr dieser Größe".

Überprüfen Sie:

- wo Steckverbinder angebracht sind;
- wo USB herausführt;
- wo der Reset-Schalter betätigt wird;
- wie der Deckel abgenommen wird;
- wie der Lüfter ausgetauscht wird;
- wo das Stromkabel verlegt wird;
- wie das Board befestigt wird.

## Zonen trennen

Bei einem beheizten Gerät ist es nützlich, in Zonen zu denken:

- heiße Zone;
- Elektronikzone;
- Stromversorgungszone;
- Benutzerzone;
- Servicebereich.

Heiße Zone ist der Heizer, der heiße Luftstrom, der Temperatursensor und nahegelegene Teile.

Elektronikzone ist der Controller, Display, niedervoltige Sensoren und Logikdrähte.

Stromversorgungszone ist die Stromversorgung, SSR, MOSFET, Anschlüsse, Sicherungen, Netzeingang wenn vorhanden.

Benutzerzone ist alles was mit Händen berührt wird: Schalter, Griffe, Abdeckungen, Display, RFID-Lesegerät Standort.

Diese Zonen sollten sich nicht zufällig überschneiden.

## Platzieren Sie die Elektronik nicht direkt neben dem Heizer

Controller, Display, DC-DC und Drähte mögen Überhitzung nicht.

Lassen Sie:

- Abstand zum Heizer;
- Luftspalt;
- Abschirmung oder Trennwand wenn nötig;
- Belüftung für Elektronik;
- Zugang um Temperatur nach der Montage zu überprüfen.

Wenn Elektronik in einer geschlossenen Tasche ohne Belüftung sitzt, kann sie auch ohne direkten Kontakt mit dem Heizer überhitzen.

## Luft muss dort fließen wo nötig

Ein Lüfter allein garantiert keinen Luftstrom.

Das Gehäuse muss Luft leiten:

- durch den Heizer;
- durch die Spule oder Arbeitszone;
- durch einen Filter wenn vorhanden;
- vorbei am Sensor am richtigen Punkt;
- außen oder in einer Schleife wie gestaltet.

Schlechtes Design kann zu einem schönen Lüfter und fast null nützlichem Fluss führen. Luft folgt dem Weg des geringsten Widerstands, durch Spalte, um Filter oder vorbei am Heizer.

Für Luftkanäle vermeiden Sie:

- scharfes Verengen;
- unnötige Kurven;
- dünne lange Kanäle;
- Gitter mit kleiner offener Fläche;
- Filter ohne einen Lüfter mit ausreichendem statischen Druck.

## Befestigungen für echte Schrauben machen

Verlassen Sie sich nicht darauf, dass eine selbstschneidende Schraube in einem dünnen Pfosten für immer hält.

Für ein Gehäuse das häufig zerlegt wird, ist besser:

- Messing-Wärmeeinsätze;
- Muttern in Taschen;
- richtige Board-Abstandshalter;
- standardisierte Schrauben;
- Unterlegscheiben wo Kunststoff einbeult.

Für gedruckte Abstandshalter, wichtig:

- angemessener Durchmesser;
- gerundete Basis;
- keine dünnen Wände;
- korrekte Druckausrichtung;
- Materialfreiraum um das Loch.

Wenn der Deckel oft geöffnet wird, verschleißen nackte Kunststoffgewinde schnell.

## Drähte dürfen nicht scheuern

Drähte im Gehäuse müssen befestigt werden.

Sie benötigen:

- Kabelkanäle;
- Platz für Bindungen;
- Zugentlastung am Kabeleingang;
- Radien statt scharfkantiger Kanten;
- Abstand vom Lüfter;
- Abstand vom Heizer;
- Schutz vor Quetschung durch den Deckel.

Schlimmes Szenario: Der Benutzer zieht ein externes Kabel und die Kraft geht direkt zu einem Anschluss oder Board-Pin.

Besser ist wenn das Kabel zuerst vom Gehäuse befestigt wird, dann zum Stecker oder Anschluss reicht.

## Nicht Netzspannung mit Niedervoltkombinieren

Wenn das Gerät 110-230V AC hat, muss das Gehäuse viel strenger entworfen werden.

Mindestlogik:

- Netzeingang separat;
- Sicherung zugänglich aber geschützt;
- Netzanschlüsse abgedeckt;
- Niedervoltkdrähte nicht mit Netzdrähten vermischt;
- Benutzer kann den Netzteil nicht berühren;
- Draht kann unter Spannung nicht aus dem Anschluss gehen;
- Kunststoff berührt nicht heiße Anschlüsse und Stromkomponenten;
- Erdung ist wo erforderlich vorhanden.

Erfinden Sie nicht die Netzsicherheit "im Bild". Für den Netzteil brauchen Sie richtige Anschlüsse, Isolierung, Zugentlastung, Sicherungen und Verständnis der Sicherheitsanforderungen.

## Zugang für Service hinterlassen

Das Gerät benötigt Wartung.

Hinterlassen Sie Zugang zu:

- Sicherung;
- Anschlüsse;
- Controller;
- USB oder Service-Stecker;
- Temperatursensor;
- Lüfter;
- Filter;
- Heizer;
- Befestigungsschrauben.

Wenn der Austausch eines Lüfters das Ablöten von Drähten oder das Entfernen des Heizers erfordert, wird das Design nicht gut gewartet.

## Überprüfung bei echter Temperatur

Nach der Montage müssen Sie mehr als nur überprüfen ob alles passt.

Überprüfen Sie:

- Elektroniktemperatur nach längerer Betriebsdauer;
- Wandtemperatur in der Nähe des Heizers;
- löst sich Kunststoff auf;
- verformt sich der Luftkanal;
- werden Anschlüsse heiß;
- haben sich Spalte zu heißen Teilen verändert;
- riecht Kunststoff;
- berühren Drähte heiße Oberflächen.

Der erste Test ist am besten unter Aufsicht mit der Möglichkeit durchzuführen, die Stromversorgung schnell zu unterbrechen.

## Checkliste vor dem Drucken des Gehäuses

Überprüfen Sie vor dem Drucken:

1. Alle echten Komponenten sind gemessen.
2. Es gibt Abstand um Boards, Steckverbinder und Kabel.
3. Heiße Zone ist von Elektronik getrennt.
4. Luftstrom hat einen klaren Weg.
5. Lüfter kann ausgetauscht werden.
6. Filter kann ausgetauscht werden.
7. Temperatursensor kann überprüft und neu installiert werden.
8. Drähte laufen nicht durch scharfe Kanten.
9. Es gibt Plätze für Bindungen oder Clips.
10. Netzdrähte sind von Niedervoltkdrähten getrennt.
11. Deckel quetscht keine Kabel.
12. Schrauben und Einsätze haben genug Kunststoff um sich.
13. Material passt zur Betriebstemperatur.
14. Teilverformung macht das Gerät nicht unsicher.

## Häufige Fehler

- zuerst ein hübsches Gehäuse entwerfen, dann versuchen Drähte zu passen;
- keinen Platz für Steckverbinder lassen;
- Stromversorgungsbelüftung blockieren;
- Controller in eine heiße Ecke legen;
- Netz- und Signaldrähte zusammen verlegen;
- keine Zugentlastung für Kabel bereitstellen;
- dünne Abstandshalter für Schrauben verwenden;
- vergessen dass Filter und Lüfter Wartung benötigen;
- Gehäuse aus PLA für eine heiße Zone drucken;
- Gehäuse nach längerer Wärmezufuhr nicht überprüfen.

## Wichtige Erkenntnisse

- Gehäuse wird nach echten Komponenten und Drähten entworfen.
- Heiße Zone, Elektronik, Stromversorgung und Benutzerzone müssen getrennt sein.
- Luft muss entlang eines nützlichen Weges fließen, nicht nur "irgendwo blafen".
- Drähte müssen befestigt und vor scharfen Kanten, Wärme und Spannung geschützt werden.
- Netzspannung kann nicht mit Niedervoltelektronik gemischt werden.
- Wartung muss vor dem Drucken geplant werden, nicht nach der Montage.

## Referenzen

- [Protolabs Network: Enclosure design for 3D printing](https://www.hubs.com/knowledge-base/enclosure-design-3d-printing-step-step-guide/) - praktische Regeln für Wände, Spalte, Bolzen, Rippen und Halterungen.
- [Prusa Knowledge Base: Enclosure guidepost](https://help.prusa3d.com/article/enclosure-guidepost_366332) - warum Gehäuse Temperatur, Staub, Geruch, Zugang zu heißen Teilen und Stromversorgungsplatzierung außerhalb warmer Kammer beeinflusst.
- [FRC Design: Design for 3D Printing](https://www.frcdesign.org/design-handbook/structure/design-for-3d-printing/) - Tipps für Elektronik-Gehäuse, Portanbindung, Belüftung und Wärmeeinsätze.
- [3D On Demand: 3D printed enclosures guide](https://www.3d-demand.com/blog/3d-printed-enclosures-electronics-guide) - Design um interne Komponenten, Wanddicke, Clips und Wärmeableitung.
- [3DSearch: Custom electronics enclosures](https://www.3dsearch.app/blog/3d-printing-electronics-enclosures) - Belüftung, Board-Abstandshalter, Gewindeeinsätze, Spalte und praktische Abmessungen für FDM.
