# Heizer- und SSR-Fehler

Der Heizer ist die gefährlichste Last in einem einfachen DIY-Gerät.

Ein Lüfter könnte nicht starten. Ein Sensor könnte falsche Ablesungen geben. Aber ein Heizer mit einem Fehler kann das Gehäuse überhitzen, Kunststoff schmelzen, Verdrahtung beschädigen oder ein Feuerrisiko schaffen.

Wenn das Gerät 110-230V AC hat und Sie keine Elektrosicherheit verstehen, ist die richtige Aktion zu stoppen und einen Spezialisten um Hilfe zu fragen.

## Symptome

Gefährliche Zeichen:

- SSR wird erheblich heiß;
- Heizer will nicht ausschalten;
- Temperatur steigt obwohl Befehl aus ist;
- Temperatur steigt zu schnell oder unangemessen;
- Temperatursensor zeigt falschen Wert;
- Anschluss dunkel geworden;
- Draht oder Stecker wird heiß;
- Schutzschalter oder Sicherung fliegt;
- Gehäuse riecht nach Kunststoff oder Verbrennung;
- Gerät ist gefährlich zu berühren;
- Heizen setzt sich nach Controller-Fehler fort.

Wenn sich Heizer nicht wie erwartet verhält, schalten Sie Stromversorgung aus.

## AC SSR und DC SSR verwechselt

SSRs kommen für verschiedene Last-Typen.

AC SSR ist für Wechselstrom. DC SSR ist für Gleichstrom.

Fehler:

- AC SSR auf DC Heizer;
- DC SSR auf 230V AC;
- gekauft "SSR 40A" ohne zu verstehen was auf dem Gehäuse geschrieben ist.

Falscher SSR-Typ könnte die Last nicht ausschalten oder gefährlich funktionieren.

Bevor Sie verbinden überprüfen Sie:

- Ausgangstyp: AC oder DC;
- zulässige Last-Spannung;
- zulässiger Strom;
- Steuereingangs-Spannung;
- Hersteller-Verbindungsdiagramm;
- wird Kühlkörper benötigt.

## SSR ohne Kühlkörper

SSR wird während des Betriebs heiß.

Auch wenn das Gehäuse großen Strom sagt, bedeutet es nicht dass das Relais es ohne Kühlkörper in einem geschlossenen Gehäuse halten wird.

Überprüfen Sie:

- Laststrom;
- Spannungsabfall über SSR;
- dissipierte Kraft;
- Kühlkörper-Anforderungen;
- SSR-Gehäuse-Temperatur nach Betrieb;
- gibt es Luftstrom.

Wenn SSR so heiß ist dass es schwierig ist von Hand zu halten, ist dies Grund zu stoppen und herauszufinden.

## MOSFET für 110-230V AC

Normale MOSFET-Module für Arduino/ESP32 sind meist für DC-Lasten: 12V oder 24V.

Sie können nicht als einfacher Schalter für AC Netzspannung 110-230V verwendet werden.

Für Netzlast brauchen Sie verschiedene Komponenten, verschiedene Isolation, verschiedene Anschlüsse, Erdung, Sicherungen und Verständnis der Elektrosicherheit.

Wenn Sie nicht sicher dass das ausgewählte Modul für Netzlast entworfen ist, verbinden Sie es nicht zum Netz.

## Keine Sicherung

Eine Sicherung macht das Gerät nicht völlig sicher, aber sie begrenzt die Folgen einiger Fehler.

Schlechte Ideen:

- "Ich werde es später hinzufügen";
- "Stromversorgung schützt sich selbst";
- "mein Heizer ist klein";
- "wenn Sicherung fliegt werde ich eine größere einlegen".

Sicherung wird für den Schaltkreis, die Verdrahtung und die Last ausgewählt. Sie kann nicht nur erhöht werden weil sie fliegt.

Wenn Sicherung fliegt, finden Sie die Ursache.

## Kein unabhängiger thermischer Schutz

Firmware und Temperatursensor sind nicht der einzige Schutz.

Für Heizer ist unabhängiger Hardware-Schutz nützlich:

- Thermostat;
- thermische Sicherung;
- Bimetall-Schalter;
- separater Notfall-Heizer-Stromabschalter.

Solcher Schutz muss unabhängig von Controller und Firmware arbeiten.

Wenn Controller hängt, Pin in An-Zustand hängt, SSR ausfällt oder Sensor getrennt wird, Hardware-Schutz kann letzte Verteidigungslinie sein.

## Temperatursensor schlecht montiert

Heizer wird durch Rückmeldung vom Sensor gesteuert.

Wenn Sensor:

- getrennt;
- schlecht gepresst;
- am falschen Ort;
- keine thermische Kontakt;
- zeigt Lufttemperatur statt Heizer;
- falscher Typ in Firmware ausgewählt;

Controller könnte weiterheizen weil er falsche Temperatur sieht.

Schlechter thermischer Kontakt ist einer der gefährlichsten Fehler in Heiz-Systemen.

## Falsche Heizer-Kraft

Heizer-Kraft muss vor Verbindung berechnet werden.

Beispiel:

```text
24V 120W -> 5A
24V 240W -> 10A
230V 300W -> etwa 1.3A
```

Für niedervoltstarke Heizer Strom wird schnell groß. Das erfordert richtige Drähte, Anschlüsse, MOSFET/SSR und Stromversorgung.

Für Netzheizer ist Strom weniger aber Schockhazard viel höher.

## Schwache Anschlüsse und Drähte

Ein Anschluss der "irgendwie hält" kann unter Strom heiß werden.

Gründe:

- schlechter Kontakt;
- Isolierung angeklemmt;
- Draht zu dünn;
- Anschluss nicht für Strom bewertet;
- geflochtener Draht ohne Aderendhülse ausgefranst;
- Schraube von Wärme und Vibration gelockert.

Dunkler Anschluss, Geruch, Erwärmung oder Kunststoff-Erweichung herum ist Grund Gerät auszuschalten.

## Was nicht zu tun

Sie können nicht:

- Netzteil unter Stromversorgung auf Arbeitstisch halten;
- Drähte unter Stromversorgung ändern;
- Arduino MOSFET-Modul für 230V AC nutzen;
- SSR ohne Kühlkörper nutzen wenn benötigt;
- thermischen Schutz deaktivieren;
- Notfall-Thermostat kurzschließen;
- Sicherung "so dass es nicht fliegt" erhöhen;
- Heizer beim ersten Test unbeaufsichtigt lassen;
- PLA-Montage in der Nähe des Heizers nutzen.

## Was überprüfen

Vor erstem Heizen:

1. Heizer-Spannung.
2. Kraft und Strom.
3. Stromschalter-Typ: MOSFET, AC SSR, DC SSR, Relais.
4. Strom-Spielraum.
5. SSR oder MOSFET Kühlkörper, wenn benötigt.
6. Sicherung.
7. Erdung, wenn benötigt.
8. Anschlüsse und Drähte.
9. Temperatursensor-Montage.
10. Richtig `sensor_type` in Firmware.
11. `min_temp` und `max_temp`.
12. Unabhängiger thermischer Schutz.
13. Verhalten wenn Controller aus ist.
14. Anschluss- und SSR-Temperatur nach kurzem Test.

## Wichtige Punkte

- Heizer kann nicht wie normale kleine Last getestet werden.
- AC SSR und DC SSR sind verschiedene Geräte.
- SSR benötigt oft Kühlkörper.
- MOSFET-Modul für DC-Lasten funktioniert nicht für 110-230V AC.
- Temperatursensor muss fest an richtigem Ort montiert sein.
- Hardware-thermischer Schutz muss unabhängig von Firmware sein.
- Wenn es Geruch, Anschluss-Erwärmung oder unerwartetes Heizer-Verhalten gibt, schalten Sie Stromversorgung aus.

## Referenzen

- [Klipper Configuration Reference: verify_heater](https://www.klipper3d.org/Config_Reference.html#verify_heater) - offizielle Heizer-Verifizierung und Temperatursensor-Überprüfung durch Anstiegsrate und kumulierten Fehler.
- [Tom's Hardware: How to Fix 3D Printer Thermal Runaway](https://www.tomshardware.com/3d-printing/how-to-fix-3d-printer-thermal-runaway) - Überprüfung von Thermistor, Heizer-Patrone, Lüfter, Stromversorgung und Verdrahtung während thermischen Durchgehens.
- [Marlin Configuration: Temperature Ranges and Thermal Protection](https://marlinfw.org/docs/configuration/configuration.html#temperature-ranges) - `MINTEMP`, `MAXTEMP` und thermischer Schutz als Teil der Sicherheit.
- [Sensata/Crydom SSR Heat Sink Selection](https://www.sensata.com/sites/default/files/a/sensata-ssr-heat-sink-selection-white-paper.pdf) - warum SSR thermische Berechnung und Kühlkörper bei erheblichen Strömen benötigt.
- [Omron: Solid State Relay Basics](https://components.omron.com/us-en/products/basic-knowledge/relays/solid-state-relays) - grundlegende Information über SSR, Anwendung, Erwärmung und Unterschiede von mechanischen Relais.
