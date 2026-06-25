# TRIAC

Ein TRIAC oder Thyristor ist ein Halbleiterschalter für Wechselstrom. Er wird verwendet, um eine Wechselstromlast ein- oder auszuschalten: zum Beispiel ein Netzheizerlement, eine Glühlampe oder ein anderes einfaches Gerät an `110-230V AC`.

Bei selbstgebauten Geräten ist dies ein Hochrisiko-Thema. Das TRIAC selbst macht die Netzspannung nicht sicher. Es bietet nur eine Möglichkeit, eine Wechselstromlast ohne mechanische Kontakte zu steuern.

## Unterschied zwischen TRIAC und MOSFET

Das MOSFET-Modul aus dem vorherigen Artikel wird üblicherweise für Gleichstromlasten verwendet: `5V`, `12V`, `24V`.

Das TRIAC wird für Wechselstromlasten verwendet. Es wird durch einen Steuerpuls eingeschaltet und führt Strom, bis der Strom darunter unter die Haltespannung fällt. Bei Netzwechselstrom geschieht dies normalerweise bei der Nulldurchgang der Sinuswelle.

In der Praxis:

- MOSFET - typische Wahl für `12V`/`24V` Lüfter, LED-Streifen oder Gleichstromheizer;
- TRIAC – typisches Element in Wechselstrom-Stromreglern und vielen Wechselstrom-SSRs;
- SSR - fertig montiertes Halbleiterrelais mit Optokoppler, TRIAC/Thyristor, Gehäuse, Anschlüssen und manchmal Kühlkörper.

Für einen Anfänger ist es bei einer Netzlast oft sicherer, ein fertig montiertes SSR oder ein zertifiziertes Modul zu verwenden, als eine eigene TRIAC-Schaltung auf einem Steckboard zu montieren.

## Warum es für Wechselstromlasten verwendet wird

Eine leistungsstarke Gleichspannung erfordert hohen Strom.

Zum Beispiel:

```text
24V 240W -> 10A
24V 300W -> 12,5A
230V 300W -> etwa 1,3A
```

Bei `24V` benötigen Sie dicke Drähte, eine leistungsstarke Stromversorgung, ein starkes MOSFET, normale Anschlüsse und Kühlung. Bei `230V AC` ist der Strom niedriger, aber es gibt gefährliche Netzspannung und alle elektrischen Sicherheitsanforderungen.

Der TRIAC-Ansatz ist nicht "besser" und nicht "einfacher". Es ist ein anderer Kompromiss: weniger Strom im Stromkreis, aber viel höhere Anforderungen an Isolation, Gehäuse, Sicherung, Abstände und Qualifikationen.

## Typische Architektur

Der Controller ist normalerweise nicht direkt mit dem TRIAC verbunden.

Eine typische sichere Architektur sieht folgendermaßen aus:

![AC-Dimmerschaltung mit TRIAC](../../img/01-electronics-basics/03-triac-dimmer-circuit.svg)

*Quelle: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:TRIAC_based_dimmer_circuit.svg), Osbertjoel, CC BY-SA 4.0*

Es hat:

- Niederspannungsseite: Controller und Steuerwiderstand;
- Optoisolator TRIAC: übermittelt Befehle durch optische Isolation;
- Netzseite: Power-TRIAC, Wechselstromlast, Sicherung, Anschlüsse und Gehäuse;
- manchmal Snubber-Schaltung und Varistor/TVS für Rauschen und Spitzen.

Der Optoisolator TRIAC wird für galvanische Isolation benötigt. Das bedeutet, es gibt keine direkte elektrische Verbindung zwischen dem Mikrocontroller und dem Netzteil. Die Steuerung wird durch Licht im Optokoppler übertragen.

Die galvanische Isolation reduziert das Risiko, dass die Netzspannung den Controller, USB und Computer erreicht. Dies macht jedoch den Netzbereich nicht sicher zu berühren.

## Nulldurchgang und Phasenanschnitt

Optoisolator-TRIACs gibt es mit und ohne Nulldurchgang.

Ein Optoisolator-TRIAC mit Nulldurchgang schaltet die Last nahe dem Nulldurchgang der Netzspannung ein. Dies ist bequem für einfaches Ein-/Ausschalten eines Heizers oder einer anderen Widerstandslast: weniger Rauschen und sanfteres Schalten.

Ein Optoisolator-TRIAC ohne Nulldurchgang wird verwendet, wenn eine Phasenregelung der Leistung erforderlich ist, zum Beispiel bei einem Dimmer. Eine solche Schaltung ist komplexer: Sie müssen den Nulldurchgang erkennen, die Verzögerung zählen und Rauschen berücksichtigen.

Für einen Heizer in einem Trockner oder einer Kammer ist normalerweise keine Dimmerstufenkontrolle erforderlich. Oft ist ein langsames Ein-/Ausschalten oder Burstbetrieb ausreichend, wenn das gewählte Modul dies unterstützt und sicher für die Last ist.

## Welche Lasten sind geeignet

Ein TRIAC ist am einfachsten mit Widerstandslasten im Wechselstrom zu verwenden:

- Heizer;
- Glühlampe;
- einfache Wärmelast ohne Elektronik.

Vorsicht vor:

- Motoren;
- Wechselstromlüftern;
- Transformatoren;
- Solenoiden;
- Stromversorgungen;
- elektronischen Treibermodulen;
- Lasten mit hohem Einschaltstrom.

Eine induktive Last verschiebt die Phase des Stroms relativ zur Spannung und kann den normalen TRIAC-Ausfall beeinträchtigen. Es kann andere TRIAC-Typen, Snubber-Schaltung, Varistor oder ein anderes Schaltverfahren erfordern.

Eine Stromversorgung oder ein elektronischer Treiber sollte nicht als normale Widerstandslast betrachtet werden. Wenn er Elektronik im Inneren hat, kann die TRIAC-Steuerung schlecht oder gefährlich funktionieren.

## Snubber-Schaltung

Der Snubber ist eine RC-Schaltung (Widerstand + Kondensator parallel zum TRIAC), die scharfe Spannungsschwankungen dämpft und ein falsches TRIAC-Auslösen verhindert.

Dies kann hilfreich sein:

- bei induktiven Lasten;
- bei schnellem Rauschen im Netz;
- bei falschem TRIAC-Auslösen;
- bei Ausschaltproblemen.

Ein typischer Ausgangspunkt für eine Widerstandslast von 200–400 W bei 230 V: **100 nF + 100 Ω**. Der Kondensator muss vom Typ X2 oder gleichwertig sein und für den Netzbetrieb ausgelegt. Dies ist keine universelle Lösung, sondern ein Startwert. Für eine andere Last werden die Werte nach dem TRIAC-Datenblatt und den Anwendungshinweisen des Herstellers neu berechnet.

Wenn Sie keine Erfahrung mit Wechselstromschaltungen haben, ist es besser, ein fertig montiertes Modul oder SSR zu verwenden, bei dem der Snubber bereits vom Hersteller berechnet wurde.

## Wärmeentwicklung und Kühlkörper

Ein TRIAC wird während des Betriebs warm. Es ist kein perfekter Schalter: Es gibt einen Spannungsabfall über ihm, was Wärme erzeugt.

Sie müssen überprüfen:

- Laststrom;
- TRIAC-Gehäuse;
- Durchlassspannungsabfall;
- Kühlkörperanforderungen;
- Umgebungstemperatur;
- Temperatur im Gehäuse;
- Abstand zu Kunststoff und Drähten;
- Sicherheitsreserven.

In der technischen Spezifikation gibt es viele Parameter. Für die erste Wahl reichen drei aus:

- `IT(RMS)` — maximaler RMS-Strom durch TRIAC. Sollte höher als der Laststrom mit Sicherheitsreserve sein, bei tatsächlicher Kühlung.
- `VDRM`/`VRRM` — maximale Spannung im ausgeschalteten Zustand. Für 230 V Netz wählen Sie TRIAC mit 600 V oder höher.
- `IGT` — Gate-Strom. Sollte den Möglichkeiten des Optoisolator-TRIACs entsprechen.

Andere Parameter (`dV/dt`, `Tj`, `Rth`, `Rth`) sind für genaue Berechnungen oder bei Problemen in der realen Schaltung wichtig.

Die Stromwertung in der technischen Spezifikation ist unter bestimmten Kühlungsbedingungen angegeben. In einem geschlossenen, warmen Gehäuse ohne Kühlkörper ist der wirklich maximale Strom niedriger.

## TRIAC und SSR

Ein SSR für eine Wechselstromlast verwendet oft einen Optokoppler und TRIAC oder Thyristor als Leistungsstufe.

Vorteile eines fertig montiertes SSR:

- bequeme Anschlüsse;
- eindeutige Steuereingang;
- Gehäuse;
- angegebene Parameter;
- oft einfacher zu montieren und mechanisch zu kühlen.

Nachteile:

- SSR wird auch warm;
- der richtige Typ ist erforderlich: AC-Ausgangs-SSR für Wechselstromlast;
- viele SSRs benötigen Kühlkörper;
- der Markt hat viele Fälschungen und Module mit übertriebenen Spezifikationen;
- SSR ersetzt nicht die Sicherung, das Gehäuse und die elektrische Sicherheit.

Wenn die Aufgabe darin besteht, einen Netzheizkörper in einem echten Gerät zu steuern, ist ein fertig montiertes hochwertiges SSR oft praktischer als eine selbstgebaute Schaltung mit separatem TRIAC.

## Was Sie nicht tun können

Sie können nicht:

- eine Netz-TRIAC-Schaltung auf einem Steckboard montieren;
- den offenen Netzbereich unter Strom lassen;
- den Controller direkt an den Netzbereich ohne Isolation anschließen;
- ein niedriges MOSFET-Modul anstelle von TRIAC/SSR für `230V AC` verwenden;
- einen zufälligen Kondensator in die Netz-Snubber-Schaltung einbauen;
- das "40A"-Etikett auf einem billigen Modul als ausreichende Überprüfung betrachten;
- ohne Sicherung;
- Netzanschlüsse neben USB, Tasten und offenen Niederspannungskontakten platzieren;
- eine solche Schaltung ohne Verständnis der Elektrosicherheit testen.

Die Arbeit mit `110-230V AC` erfordert Wissen, ordnungsgemäße Werkzeuge, ein Gehäuse, eine Isolationsprüfung und das Verständnis lokaler Bestimmungen. Im Zweifelsfall sollte eine qualifizierte Person den Strombereich montieren oder überprüfen.

## Was vor dem Kauf zu überprüfen ist

Vor dem Kauf eines TRIACs, Moduls oder SSR überprüfen Sie:

- ist dies eine Wechselstrom- oder Gleichstromlast;
- Netzspannung;
- Laststrom und Leistung;
- ist es eine Widerstands- oder induktive Last;
- ist Nulldurchgang erforderlich;
- ist Snubber erforderlich;
- maximaler Strom bei tatsächlicher Kühlung;
- ist Kühlkörper erforderlich;
- gibt es optische Isolation;
- Anschlüsse und Abstände für das Netz;
- Sicherung und Gehäuse;
- gibt es technische Spezifikation oder Herstellerdokumentation.

Wenn es keine Dokumentation gibt und das Modul einen Netzheizkörper steuern muss, ist dies eine schlechte Wahl.

## Häufige Fehler

- TRIAC für Gleichstromlast verwenden;
- MOSFET, TRIAC und SSR verwechseln;
- Netzlast ohne optische Isolation anschließen;
- Nulldurchgang-Optoisolator-TRIAC verwenden und sanftes Dimmen erwarten;
- TRIAC mit Motor ohne Snubber und Lasttyp-Überprüfung verwenden;
- Kühlkörper nicht installieren;
- Temperatur im Gehäuse nicht berücksichtigen;
- zufällige Anschlüsse und dünne Drähte verwenden;
- denken, dass SSR oder TRIAC die Sicherung ersetzt;
- Netzbereich neben Controller und USB offen lassen.

## Die Hauptaussage

Das TRIAC ist ein Leistungsschalter für Wechselstromlasten. Es ist nützlich für Netz-Widerstandslasten wie Heizer, erfordert aber ein ordnungsgemäßes Netzbetriebskonzept.

Für einen Mikrocontroller ist optische Isolation erforderlich. Für die Last sind das richtige TRIAC/SSR, Sicherung, Anschlüsse, Gehäuse, Kühlkörper bei Bedarf und Sicherheitsüberprüfung erforderlich. Wenn Sie keine Erfahrung mit `110-230V AC` haben, bauen Sie den Strombereich nicht selbst.

## Referenzmaterialien

- [STMicroelectronics: Dokumentation zu Standard- und Snubberless-TRIACs](https://www.st.com/en/thyristors-scr-and-ac-switches/standard-and-snubberless-triacs/documentation.html) - TRIAC-Auswahl, Parameter und Anwendungshinweise zu Snubberless/Standard-TRIAC.
- [ST AN437: RC-Snubber-Schaltungsdesign für TRIACs](https://www.alldatasheet.com/datasheet-pdf/pdf/696239/STMICROELECTRONICS/AN437.html) - detaillierte Erklärung, warum Dämpfungs-RC-Schaltung erforderlich ist und wie sie den TRIAC-Ausfall beeinflusst.
- [MOC3063-Datenblatt: Nulldurchgang-Optoisolator-TRIAC-Treiber](https://www.alldatasheet.com/html-pdf/5043/MOTOROLA/MOC3063/258/1/MOC3063.html) - Beispiel eines Optoisolator-TRIACs für die Verbindung von Logik mit `115/240 VAC`-Lasten.
- [Omron: Überblick über Halbleiterrelais](https://www.ia.omron.com/support/guide/18/introduction.html) - grundlegende Erklärung von SSR als Halbleiterrelais ohne mechanische Kontakte.
- [Omron SSR-Glossar: Phototriac, Nulldurchgang, Snubber](https://www.ia.omron.com/support/guide/31/further_information.html) - kurze Definitionen von Phototriac, Nulldurchgang und Snubber-Schaltung.
