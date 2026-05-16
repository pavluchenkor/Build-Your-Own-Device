# Halbleiterrelais

Ein Halbleiterrelais oder SSR ist ein Relais ohne mechanische Kontakte. Sie wenden ein schwaches Steuersignal vom Controller auf den SSR-Eingang an, und der SSR-Ausgang schaltet eine Last ein oder aus.

Bei einfachen Geräten für 3D-Drucker wird SSR am häufigsten für einen Netzheizkörper verwendet: Kammer, Trockner, Tisch oder separates Heizmodul. Es ist eine praktische Möglichkeit, eine `110-230V AC`-Last von Elektronik mit niedriger Spannung zu steuern, aber keine Möglichkeit, das Netz sicher zu machen.

Wenn das Projekt `110-230V AC` hat, muss der Strombereich in einem Gehäuse mit Sicherung, normalen Anschlüssen, Isolierung, Zugentlastung für Kabel und Verständnis der Elektrosicherheit montiert werden.

## Unterschied zwischen SSR und ordentlichem Relais

Ein gewöhnliches elektromagnetisches Relais klickt, weil die Kontakte physisch im Inneren bewegt werden. Die Relaisspule benötigt Strom, oft benötigt sie einen Transistor-Treiber, Schutzdiode, und die Kontakte können funkeln, flattern und verschleißen.

SSR schaltet die Last mit Halbleitern. Daher hat es kein Klicken, keinen mechanischen Kontaktverschleiß und eignet sich besser für häufiges Ein-/Ausschalten von Heizern.

Aber SSR ist kein "Relais ohne Nachteile".

SSR hat seine eigenen Einschränkungen:

- es wird warm;
- benötigt oft Kühlkörper;
- kann kleine Leckströme im ausgeschalteten Zustand haben;
- toleriert Überlasten und Spitzen schlechter als ein ordnungsgemäß gewählter Schütz;
- kann im "Ein"-Zustand ausfallen;
- muss für Wechsel- oder Gleichstromlast gewählt werden;
- ersetzt nicht Sicherung, Gehäuse und Notschutz durch Temperaturschutz.

Für seltenes Schalten von Stromkreisen ist ein ordentliches Relais oder Schütz möglicherweise geeigneter. Für häufige Steuerung von Widerstandsheizkörpern ist SSR oft praktischer.

## Was ist in AC SSR enthalten

Ein AC SSR enthält normalerweise:

- Steuersignaleingangschaltung;
- optische Isolation;
- Auslöseschaltung;
- Power TRIAC oder Thyristorpaar;
- Snubber-Schaltung oder anderen Spitzenschutz;
- Leistungsanschlüsse für die Last.

Einfach gesagt, es ist eine fertig montierte TRIAC-Schaltung in einem Gehäuse. Daher ist SSR praktisch, wenn Sie nicht den Optoisolator-TRIAC, den TRIAC, den Snubber, die Platinen-Abstände und den Netzbetrieb selbst berechnen möchten.

Ein fertig montiertes Gehäuse eliminiert nicht die Notwendigkeit der Überprüfung. Besonders wenn das SSR billig ist, keine technische Spezifikation hat oder eine verdächtig hohe Stromwertung auf dem Gehäuse hat.

## AC SSR und DC SSR

SSR muss nach Lasttyp gewählt werden:

- **AC SSR** - für Wechselstrom, zum Beispiel Netzheizkörper `110-230V AC`;
- **DC SSR** - für Gleichstrom, zum Beispiel `12V` oder `24V` Gleichstromlast.

Dies sind unterschiedliche Geräte. AC SSR kann nicht automatisch auf einen `24V` Gleichstromheizkörper gesetzt werden: es könnte nicht ausschalten. DC SSR kann nicht als geeignet für `230V AC` betrachtet werden: es kann gefährlich sein und nicht für so einen Stromkreis ausgelegt.

Sie müssen nicht nur die `AC`- oder `DC`-Kennzeichnung überprüfen, sondern auch den Ausgangsspannungsbereich.

Beispiele für Kennzeichnungen:

```text
Eingang: 3-32V DC
Ausgang: 24-380V AC
```

Das bedeutet:

- Eingang wird durch Niederspannungs-DC-Signal gesteuert;
- Ausgang schaltet Wechselstromlast im angegebenen Bereich;
- Sie müssen die Last nicht über den Eingang durch das SSR stromversorgen.

Überprüfen Sie vor dem Kauf die Zeilen `Input`, `Output`, `Load voltage`, `Load current` und das Verbindungsdiagramm des Herstellers.

## Typisches Verbindungsdiagramm

SSR wird normalerweise in der Stromleitung der Last unterbrochen. Der Controller verbindet sich nur mit dem SSR-Eingang, während der Stromkreis der Last durch den SSR-Ausgang geht.

![Interne Struktur des Halbleiterrelais SSR](../../../img/01-electronics-basics/04-ssr-internal-structure.png)

*Quelle: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:SSR.png), Thomas Verdyck, CC BY-SA 3.0*

Wichtige Punkte:

- SSR-Eingang und SSR-Ausgang sind unterschiedliche Seiten des Geräts;
- Niederspannungsseite sollte nicht mit Netzseite verbunden sein;
- SSR wird in der Unterbrecher der Stromlast platziert, normalerweise `Line`;
- Schutzerde `PE` wird nicht durch das SSR unterbrochen;
- Sicherung muss die Verdrahtung und Last schützen;
- Heizer benötigt unabhängigen Temperaturschutz;
- gesamter Netzbereich muss vor Berührung geschlossen sein.

SSR wird nicht als Trennschalter betrachtet. Zur Wartung benötigen Sie eine physische Möglichkeit, Strom auszuschalten: Schalter, Brecher, Stecker oder andere Standard-Stromkreis-Unterbrechung. In der Praxis können es verschiedene Systeme nach lokalen Regeln, Stromtyp, Schutzerdung und Gehäuse geben. Wenn Sie sich nicht sicher sind, sollte eine qualifizierte Person den Stromkreis überprüfen.

## Nulldurchgang, zufälliges Einschalten und Steuerung

AC SSR kommt mit verschiedenen Einschaltmethoden.

**Nulldurchgang-SSR** schaltet die Last nahe dem Nulldurchgang der Netzspannung ein. Dies ist eine gute Option für einfaches Ein-/Ausschalten eines Widerstandsheizkörpers: weniger Rauschen und sanfteres Schalten.

**Zufälliges Einschalten-SSR** schaltet den Ausgang fast sofort nach dem Steuersignal ein. Dieser Typ wird verwendet, wenn unterschiedliche Logik erforderlich ist, Phasenregelung oder spezifische Lastanforderungen.

Für eine Kammer, einen Trockner oder einen einfachen Heizer ist normalerweise keine schnelle Dimmerstromregelung erforderlich. Oft ist langsame Steuerung ausreichend: zum Beispiel den Heizer einige Sekunden einschalten, nicht hundertmal pro Sekunde zucken.

Nicht alle SSRs eignen sich für Phasenregelung. Wenn Sie speziell einen Phasenstromregler benötigen, ist dies ein separater Gerätetyp und ein separates Thema mit Rauschen, Heizung und Lastanforderungen.

## Leckstrom

SSR kann einen kleinen Strom auch im "ausgeschalteten" Zustand führen. Dies wird Leckstrom genannt.

Für einen leistungsstarken Heizer erzeugt solch ein Strom normalerweise keine merkliche Heizung, aber für eine kleine Lampe, LED-Treiber, Stromversorgung oder sehr kleine Last kann es merklich sein: Anzeige kann schwach leuchten, Stromversorgungseingang kann sich seltsam verhalten.

Daher sollte SSR nicht als idealer Stromkreis-Unterbrecher betrachtet werden. Vor dem ersten Heizer-Einschalten überprüfen Sie, dass die Last nicht heizt, wenn das Steuersignal entfernt wird. Es ist besser, den SSR-Ausgang zuerst mit einer sicheren kleinen Last, einer Lampe oder einem Multimeter zu testen, nicht unmittelbar mit dem Hauptheizer.

Zur Wartung, Notfall-Abschaltung und vollständiger Isolation benötigen Sie einen Schalter, Brecher, Sicherung, Stecker oder andere physische Möglichkeit zum Ausschalten von Strom.

## Wärmeentwicklung und Kühlkörper

SSR wird während des Betriebs warm. Im eingeschalteten Zustand gibt es einen Spannungsabfall über dem Leistungselement, was Wärme erzeugt.

Sie müssen überprüfen:

- Laststrom;
- maximaler SSR-Strom bei echter Temperatur;
- Spannungsabfall am Ausgang;
- Kühlkörperanforderungen;
- Temperatur im Gehäuse;
- Kühlkörper-Ausrichtung und Luftstrom;
- Qualität des thermischen Kontakts zwischen SSR und Kühlkörper;
- Temperatur von Anschlüssen und Drähten nach Test.

Das Etikett `25A` oder `40A` bedeutet nicht, dass das SSR diesen Strom ohne Kühlkörper in einem geschlossenen Gehäuse neben einem Heizer verträgt. Hersteller geben normalerweise Strom unter spezifischen Kühlungsbedingungen an.

Praktische Regel für ein einfaches Projekt: wählen Sie nicht SSR genau für Laststrom. Plan Reserve, verwenden Sie Kühlkörper, lesen Sie die technische Spezifikation, und überprüfen Sie Temperatur im echten Gehäuse. `50%` Reserve ist die untere Grenze für erste Schätzung, keine Garantie für jede Installation.

## SSR schützt den Heizer nicht

SSR ist ein Stromschalter, kein Sicherheitssystem.

Ein Heizer benötigt unabhängige Ebenen:

- Sicherung oder Brecher für Verdrahtung und Last;
- ordnungsgemäße Temperaturmesser;
- Software-Temperaturlimits;
- Heizungsprüfung in Firmware;
- unabhängiger Thermostat, Sicherungsschmelzer oder Bimetallschalter;
- Gehäuse aus Material, das echte Temperaturen verträgt;
- erster Test unter Beobachtung.

Wichtiger Fehlermodus: SSR kann zusammenbrechen und eingeschaltet bleiben. Daher muss der Notschutz durch Temperaturschutz die Heizerstromversorgung unabhängig vom Controller und SSR unterbrechen können.

## Welche Lasten sind geeignet

SSR ist am einfachsten mit Widerstandslasten im Wechselstrom zu verwenden:

- Heizer;
- Silikon-Heizmatte;
- Glühlampe;
- einfache Wärmelast ohne eingebaute Elektronik.

Vorsicht vor:

- Motoren;
- Wechselstromlüftern;
- Transformatoren;
- Solenoiden;
- Stromversorgungen;
- elektronischen Treibermodulen;
- Lasten mit hohem Einschaltstrom.

Induktive und elektronische Lasten können einen anderen SSR-Typ, Snubber, Varistor, Schütz oder separaten Stromkreis erfordern. Sie können SSR nicht allein nach dem "40A"-Etikett wählen.

## Was vor dem Kauf zu überprüfen ist

Vor dem Kauf von SSR überprüfen Sie:

- ist Last AC oder DC;
- Laststannung;
- Laststrom und Leistung;
- Steuereingangsspannung;
- Eingang-Kompatibilität mit Controller: `3.3V`, `5V`, `12V` oder andere Ebene;
- Einschalttyp: Nulldurchgang oder zufällig;
- maximaler Strom bei benötigter Kühlung;
- ist Kühlkörper erforderlich;
- gibt es technische Spezifikation;
- gibt es normales Verbindungsdiagramm;
- Anschlüsse und Isolations-Abstände;
- Hersteller-Qualität;
- wo Sicherung platziert;
- wo unabhängiger Temperaturschutz sein wird.

Wenn es keine Dokumentation gibt und das SSR einen Netzheizkörper steuern muss, ist dies eine schlechte Wahl.

## Häufige Fehler

- verwirrt SSR-Eingang und Ausgang;
- gekauft DC SSR statt AC SSR oder umgekehrt;
- nicht überprüft Ausgangsspannungsbereich;
- AC SSR an DC Heizer angeschlossen und waren überrascht, dass es nicht ausschaltet;
- wählte SSR genau für Laststrom;
- installiert SSR ohne Kühlkörper;
- installiert SSR in geschlossenem, heißem Gehäuse;
- nicht berücksichtigt Leckstrom;
- benutzt SSR als einzige Möglichkeit zur Notfall-Abschaltung;
- vergessen Sicherung;
- nicht installiert unabhängiger Temperaturschutz;
- hinterlassen Netzanschlüsse zugänglich;
- steuere SSR mit zu schnellem PWM ohne Verständnis von SSR-Typ und Last.

## Die Hauptaussage

SSR ist praktisch für häufige, ruhige Laststeuerung, besonders Netzheizkörper. Aber SSR muss für Lasttyp, Spannung, Strom, Einschaltmethode und thermischen Betriebspunkt gewählt werden.

Für `110-230V AC`-Last eliminiert SSR nicht die Elektrosicherheit. Sie benötigen Gehäuse, Sicherung, normale Verdrahtung, Kühlkörper bei Bedarf und unabhängigen Heizer-Temperaturschutz.

## Referenzmaterialien

- [Omron: Überblick über Halbleiterrelais](https://www.ia.omron.com/support/guide/18/introduction.html) - SSR-Design, optische Isolation, Typen und allgemeine Anwendungsprinzipien.
- [Omron: SSR-Glossar und Installationshinweise](https://www.ia.omron.com/support/guide/18/further_information.html) - Definitionen von `load voltage`, `leakage current`, `output ON voltage drop`, Nulldurchgang, Snubber und Anmerkungen zur Wärmeableit.
- [Panasonic: SSR-Betriebsprinzip](https://industry.panasonic.com/global/en/products/control/relay/solid-state/principle_operation) - Unterschied zwischen Nulldurchgang und zufällig SSR, Verhalten mit Widerstands- und induktiven Wechselstromlasten.
- [Sensata/Crydom: HS-Serie Kühlkörper](https://www.sensata.com/products/relays/solid-state-relays/ssr-accessories/hs-series-heat-sinks) - warum SSR Wärme erzeugt und warum Kühlkörper mit Strom und Temperatur übereinstimmen sollte.
- [DigiKey: Halbleiterrelais - Ein Grundüberblick](https://www.digikey.com/en/blog/solid-state-relays-a-basic-overview) - kurzer Überblick über SSR-Ausgabetypen, Nulldurchgang, zufälliges Einschalten und Einschränkungen gegenüber mechanischen Relais.
