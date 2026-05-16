# Crimp-Stecker

Crimpen ist eine Methode, um einen Draht mit einem Terminal oder Kontakt zu verbinden, ohne zu löten.

Ein gutes Crimp bietet:

- elektrischen Kontakt;
- mechanische Draht-Halterung;
- Isolierungs-Unterstützung;
- Wiederholbarkeit;
- bequeme Montage und Wartung.

Ein schlechtes Crimp kann heiß werden, auseinanderfallen, zufällige Fehler verursachen und fast normal aussehen.

## Warum Crimpen oft besser ist als Löten

Für Stecker und Terminals ist Crimpen oft besser als Löten, weil:

- der Draht bleibt flexibel;
- der Kontakt ist von Hersteller entworfen;
- Isolierung wird beibehalten;
- die Verbindung behandelt Vibration besser;
- der Stecker kann auseinandergenommen und gewartet werden;
- kein Risiko, das Kunststoff-Stecker-Gehäuse während des Lötens zu schmelzen.

Löten ist gut für Pads und Drähte, sollte aber einen ordentlichen Kontakt in einem Stecker nicht ersetzen, wenn der Hersteller Crimpen beabsichtigte.

## Arten von Terminals und Steckern

In einfachen Geräten finden Sie oft:

- Dupont - schwache Signal-Verbindungen für Breadboards;
- JST-XH/JST-PH und ähnlich - Sensoren, Lüfter, kleine Module;
- Ferrules - Spitzen für mehrsträngigen Draht in Schraubenterminals;
- Faston - flache Terminals für einige Power-Verbindungen;
- Ring- und Gabel-Terminals;
- Schrauben-Terminals;
- platinen-montierte Terminal-Blöcke.

Jeder Typ benötigt seinen eigenen Kontakt, seine eigene Drahtdicke und sein eigenes Werkzeug.

## Sie benötigen das richtige Werkzeug

Zange ist nicht ein Crimp-Werkzeug.

Sie können einen Kontakt zusammenquetschen, damit er zu halten scheint, aber Sie bekommen kein ordentliches Crimp.

Für gutes Crimpen benötigen Sie:

- einen Terminal für die korrekte Drahtdicke;
- korrekte Abisolierlänge;
- korrekte Werkzeug-Matrix;
- korrekte Kontakt-Position in der Matrix;
- separate Zonen für Strang- und Isolierungs-Crimp;
- keine beschädigten Strände.

Professionelle Stecker-Hersteller bieten Crimp-Spezifikationen, Crimp-Höhe, Abisolierlänge und Zugkraft. Für DIY-Montage haben Sie nicht immer vollständige Kontrolle, aber das Prinzip ist gleich: Kontakt, Draht und Werkzeug müssen zusammenpassen.

## Open Barrel Crimp

Viele kleine Kontakte, wie JST oder Dupont, haben zwei Paare von "Flügeln":

- ein Paar quetscht den bloßen Leiter;
- das andere Paar hält die Isolierung.

Gutes Ergebnis:

- der Leiter ist in der korrekten Zone sichtbar;
- Isolierung wird von hinteren Flügeln gehalten;
- die exponierte Länge ist nicht zu lang;
- Leiter-Strände stehen nicht heraus;
- Kontakt ist nicht schief;
- Kontakt tritt in den Stecker-Körper ein und verriegelt sich.

Wenn Isolierung in die Leiter-Crimp-Zone eintrat, wird der elektrische Kontakt schlecht sein.

Wenn nur der Leiter gequetscht wird und Isolierung nicht gehalten wird, kann der Draht bei Bewegung brechen.

## Ferrules

Für mehrsträngigen Draht in einem Schrauben-Terminal sind Ferrules oft nützlich.

Sie:

- sammeln alle Strände zusammen;
- verhindern, dass Strände sich trennen;
- verbessern das Sitzen im Terminal;
- reduzieren das Risiko, dass einige Strände außen gelassen werden;
- machen die Verbindung ordentlicher.

Dies ist besonders nützlich für Power-Drähte, Terminal-Blöcke und Zusammenbauten, die gewartet werden.

Aber Ferrules müssen auch die Drahtdicke passen und mit der richtigen Matrix gequetscht werden.

## Wie man ein Crimp überprüft

Nach dem Crimpen überprüfen:

- der Kontakt bewegt sich nicht auf dem Draht;
- Isolierung wird gehalten;
- der Leiter wird nicht herausgezogen;
- keine Strände werden geschnitten;
- exponierte Länge ist nicht zu lang;
- Kontakt tritt in den Stecker-Körper ein;
- Verriegelung klickt an der Stelle;
- Draht widerstellt sanftem Ziehen.

Ein sanfter Zug-Test ist nützlich: sorgfältig den Draht ziehen. Er sollte nicht aus dem Kontakt kommen.

Keine Notwendigkeit mit voller Kraft zu ziehen. Das Ziel ist offensichtlich schlechte Crimps vor Installation zu finden.

## Warum schlechte Crimps heiß werden

Ein schlechtes Crimp erzeugt hohen Widerstand.

Unter Strom wird dies Wärme.

Erst könnte der Terminal nur warm sein. Dann wird Kunststoff dunkel, Kontakt wird schlechter, Wärme steigt.

Dies ist besonders gefährlich für:

- Heizer;
- Lüfter mit signifikantem Strom;
- LED-Streifen;
- Stromversorgungen;
- SSR/MOSFET-Schaltungen;
- Netzverbindungen.

Wenn ein Terminal heiß wird, Stromversorgung ausschalten und die Verbindung neu machen.

## Dupont ist nicht für Power

Dupont ist bequem für Breadboards und schwache Signale.

Aber es kann nicht als ordentlicher Power-Stecker verwendet werden für:

- einen Heizer;
- Geräte-Stromversorgung;
- einen mächtigen LED-Streifen;
- Netzteile;
- einen Motor oder Servo mit großem Strom.

Selbst wenn der Stecker physisch in die Pins passt, bedeutet das nicht, dass er für den benötigten Strom, Vibration und Wärme bewertet ist.

## Häufige Fehler

- gequetscht mit Zange;
- falsche Dicke Terminal gewählt;
- zu viel Isolierung abgestreift;
- zu wenig Isolierung abgestreift;
- Isolierung statt Leiter gequetscht;
- Isolierungs-Unterstützung nicht gequetscht;
- einige Strände geschnitten;
- Kontakt verriegelte nicht im Körper;
- Power-Leitung auf Dupont gehalten;
- falsche Ferrule-Dicke;
- keinen Zug-Test gemacht;
- Terminal wird heiß, aber Gerät läuft weiter.

## Das Wesentliche

- Crimpen ist sowohl elektrischer Kontakt als auch mechanische Halterung.
- Kontakt, Draht und Werkzeug müssen zusammenpassen.
- Zange ersetzt nicht ein Crimp-Werkzeug.
- Für mehrsträngigen Draht in einem Schrauben-Terminal sind Ferrules oft nützlich.
- Schlechte Crimps können heiß und gefährlich sein.
- Power-Teile sollten sich nicht auf schwache Breadboard-Stecker verlassen.

## Referenzmaterialien

- [Molex: Quality Crimp Handbook](https://www.molex.com/content/dam/molex/molex-dot-com/products/automated/en-us/commercialcrimpbookpdf/638/63800/TM-638000029-001.pdf?inline=) - detailliertes Crimp-Qualitäts-Referenzmaterial, Zugkraft, Leiter- und Isolierungs-Crimp.
- [Molex: Industrial Crimp Quality Handbook](https://www.molex.com/content/dam/molex/molex-dot-com/products/automated/en-us/industrialcrimpbookpdf/640/64016/TM-640160065-001.pdf?inline=) - visuelle Überprüfung von offenen und geschlossenen Barrel-Crimp, Abisolierlänge, Drahtbürste und häufige Fehler.
- [JST: Application Tooling Guide, Crimp Style](https://www.jst.com/resources/application-tooling-guide/crimp-style/) - Beispiel wie spezifische JST Kontakte spezifische Werkzeuge, Abisolierlänge und Zugfestigkeit benötigen.
- [American Electrical: Wire Ferrules](https://www.americanelectrical.com/wire-ferrules/) - warum Ferrules nützlich für mehrsträngigen Draht in Terminal-Blöcken sind.
- [TE Connectivity: Wire Splices](https://www.te.com/en/products/terminals-splices/splices.html) - industrielle Crimp/Splice Verbindungstypen und warum Crimpen separat von zufälligem Zusammenquetschen konstruiert ist.
