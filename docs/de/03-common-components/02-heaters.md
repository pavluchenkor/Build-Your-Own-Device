---
title: "Heizungen für Filamenttrockner und beheizte Kammern"
description: "Heizung für Filamenttrockner oder aktive 3D-Drucker-Kammer auswählen: 12V, 24V, Netzspannung, Leistung, Steuerung und Sicherheit."
---

# Heizungen für Filamenttrockner und beheizte Kammern

Die Heizung bestimmt Aufheizgeschwindigkeit und Sicherheitsgrenzen des Filamenttrockners oder der beheizten Kammer. Diese Seite erklärt Heizertypen, Leistungswahl, Steuerung über MOSFET oder SSR und Fehler, die Überhitzung verursachen können.

Ein Heizer ist ein Laster, der elektrische Energie in Wärme umwandelt. In einem einfachen DIY-Gerät ist dies die gefährlichste Komponente: Ein Fehler bei einem Lüfter führt normalerweise zu schlechtem Luftstrom, aber ein Heizer-Fehler kann zu Überhitzung, geschmolzenem Gehäuse, beschädigter Verdrahtung oder Brandrisiko führen.

In 3D-Druckern und iDryer-ähnlichen Geräten befinden sich Heizer am Druckkopf, Druckbett, Kammer, Filamenttrockner, Luftkanal oder separates Heizmodul.

## Wo es verwendet wird

Typische Aufgaben:

- Heizen des Druckkopfes;
- Heizen des Druckbetts;
- Vorwärmen der Druckerkammer;
- Trocknung von Filament;
- Vorwärmen der Luft vor einem Filter oder Kanal;
- Eine einheitliche Temperatur in einem kleinen Prozessvolumen.

Dies sind unterschiedliche Aufgaben. Ein Heizer für einen Metalldruckkopf, eine Silikonbettmatte und ein Luft-PTC-Modul sind nicht ohne Neuberechnung von Leistung, Montage, Luftstrom und Schutz austauschbar.

## Arten von Heizern

Häufige Optionen:

- Patrone;
- Silikongummi-Heizmatte;
- PTC-Heizer;
- Keramik-Heizelement;
- fertiges Gebläse-Heizer-Modul;
- Heizplatte;
- Netz-Heizplatte;
- Nichrom- oder Widerstandswicklung in einem fertigen Gehäuse.

Eine Heizpatrone wird üblicherweise in einen Metallblock eingeführt. Sie benötigen guten thermischen Kontakt mit dem Metall und eine zuverlässige Temperatursensor-Montage.

Eine Silikongummi-Matte wird üblicherweise auf eine flache Fläche geklebt oder gepresst. Sie benötigt eine flache Fläche, gute Haftung, einen Temperatursensor und Schutz vor Ablösung.

Ein PTC-Heizer begrenzt den Temperaturanstieg teilweise aufgrund seiner Eigenschaften, ersetzt aber nicht den Regler, Sensor, Sicherung, Gehäuse und Luftstromprüfung. PTC macht ein Gerät nicht automatisch sicher.

Ein fertiges Gebläse-Heizer-Modul kombiniert Heizer und Luftstrom, muss aber dennoch auf Spannung, Leistung, Temperatur, Gehäusematerialien und Notfallschutz überprüft werden.

## Spannung, Leistung und Strom

Vor dem Anschluss müssen Sie Folgendes finden:

- Betriebsspannung;
- Leistung;
- Strom;
- Stromtyp: DC oder AC;
- maximale Temperatur;
- Draht-Betriebstemperatur;
- Befestigungsmethode;
- Luftstrom-Anforderungen;
- zulässige Steuerungsmethode.

Der Strom wird nach der Formel berechnet:

```text
Strom = Leistung / Spannung
```

Beispiele:

```text
24V 120W -> 5A
24V 240W -> 10A
24V 300W -> 12,5A
230V 300W -> etwa 1,3A
```

Ein Niederfluten-Hochleistungs-Heizer ist sicherer für die Spannung, erfordert aber große Ströme. Große Ströme erfordern eine ordnungsgemäße Stromversorgung, Drähte, Anschlüsse, MOSFET/SSR und Sicherung.

Ein Netz-Heizer bei `110-230V AC` kann hohe Leistung mit niedrigerem Strom liefern, aber das Schockrisiko ist viel höher. Für den Netz-Teil benötigen Sie Wissen über elektrische Sicherheit, Gehäuse, Anschlüsse, Isolierung, Erdung falls erforderlich, Sicherungen und galvanische Isolierung der Steuerung.

## Heizer-Steuerung

Der Regler sollte den Heizer nicht direkt über GPIO mit Strom versorgen. GPIO stellt nur ein Steuersignal zur Verfügung.

Typische Leistungssteuerungsoptionen:

- MOSFET - für DC-Heizer `12V`/`24V`;
- DC-SSR - für DC-Heizer, wenn ordnungsgemäß für DC bewertet;
- AC-SSR - für Netz-AC-Heizer;
- Mechanisches Relais - für seltenes Ein-/Ausschalten, aber nicht für häufiges PID/PWM;
- fertiger Stromausgang - nur wenn für den erforderlichen Strom und Spannung bewertet.

AC-SSR und DC-SSR sind unterschiedliche Geräte. Der falsche Typ kann den Heizer nicht ausschalten oder unsicher funktionieren.

Ein typisches MOSFET-Modul für Arduino/ESP32 kann nicht als `110-230V AC`-Schalter verwendet werden. Wenn das Modul nicht für Netzlasten ausgelegt ist, kann es nicht an das Netz angeschlossen werden.

## Sicherheitsebenen

Ein Heizer kann nicht als "Regler schaltet ihn ein - Regler schaltet ihn aus" ausgelegt sein. Sie benötigen mehrere Schutzebenen.

![Ebenen der sicheren Heizer-Steuerung](../../img/03-common-components/02-heater-safety-stack.svg)

Minimale Logik:

- Stromversorgung ist für den Strom ausgelegt;
- Sicherung wird für Verdrahtung und Last ausgewählt;
- Stromschalter passt zum Lasttyp;
- Temperatursensor wird am richtigen Ort montiert;
- Firmware verfügt über `min_temp`, `max_temp` und Heizverifikation;
- Es gibt unabhängigen Hardware-Thermoschutz: Thermosicherung, Thermostat oder Bimetall-Schalter;
- Gehäuse und Materialien halten die tatsächliche Temperatur aus;
- Erste Prüfung wird unter Aufsicht durchgeführt.

Der Hardware-Thermoschutz muss unabhängig vom Regler funktionieren. Im einfachen Fall wird er in der Heizer-Stromversorgung in Reihe geschaltet, um den Stromkreis physisch zu unterbrechen. Dies ist kein weiterer Sensor für die Firmware.

Wenn der Regler hängt bleibt, der Sensor abfällt, ein MOSFET kurzschließt oder ein SSR stecken bleibt, muss der Schutz die Stromversorgung des Heizers unterbrechen.

## Temperatursensor

Ein Heizer kennt seine eigene Temperatur nicht. Der Regler trifft die Entscheidung basierend auf dem Sensor.

Wenn der Sensor:

- schlecht gepresst ist;
- am falschen Ort ist;
- abfällt;
- der falsche Typ in der Firmware ist;
- schlechten thermischen Kontakt hat;
- Luft statt des kritischen Teils misst;

kann der Regler weiter heizen, obwohl die tatsächliche Temperatur bereits gefährlich ist.

Beim Druckkopf ist der Sensor-Kontakt mit dem Metallblock wichtig. Beim Luftheizer ist es wichtig zu verstehen, was gemessen wird: Elementtemperatur, Lufttemperatur nach dem Element, Kammertemperatur oder Temperatur in der Nähe der Spule. Dies sind verschiedene Punkte und können sich erheblich unterscheiden.

## Luftstrom und Wärmeleitung

Ein Heizer gibt Leistung ab, aber diese Leistung muss sicher dorthin gehen, wo sie bestimmt ist.

Für einen Luftheizer ist der Luftstrom kritisch:

- Ohne Strömung kann das Element lokal überhitzen;
- schwache Belüftung entfernt Wärme nicht;
- ein verstopfter Filter ändert den Heizbetrieb;
- Kunststoffkanäle können erweichen;
- ein Temperatursensor sieht möglicherweise nicht, was am Element passiert.

Beim Kammer-Heizer ist es wichtig, nicht nur die Ziellufttemperatur zu überprüfen, sondern auch die Temperatur in der Nähe des Heizers, der Drähte, des SSR/MOSFET, der Anschlüsse und der Kunststoffteile.

## Drähte, Anschlüsse und Stecker

Ein Heizer läuft oft lange Zeit und verbraucht erheblichen Strom. Schlechte Kontakte werden zur Wärmequelle.

Überprüfen Sie:

- Drahtquerschnitt;
- Isolations-Temperaturklasse;
- Anschluss-Stromstärkebeständigkeit;
- Crimpen-Qualität;
- Schraubenfestigkeit;
- Ferrolen auf adern Drähten;
- Zugentlastung;
- Abstand zu heißen Teilen;
- Fehlen von exponierten Leitern.

Wenn ein Anschluss dunkler wird, riecht, Kunststoff erweicht oder heiß wird, muss die Stromversorgung ausgeschaltet und die Ursache gefunden werden. Erhöhen Sie nicht einfach die Sicherung oder ziehen Sie sie später an.

## Was vor dem Kauf zu überprüfen ist

Überprüfen Sie vor dem Kauf eines Heizers:

- was sollte geheizt werden: Metall, Luft, Bett, Kammer;
- Spannung und Stromtyp;
- Leistung;
- Strom;
- Betriebstemperatur;
- maximale Oberflächentemperatur;
- Luftstrom-Anforderungen;
- Befestigungsmethode;
- Draht- und Isolationsmaterial;
- kompatibler Stromschalter;
- Platz für Temperatursensor;
- Platz für unabhängigen Thermoschutz;
- Gehäuse und umliegende Materialien;
- Verfügbarkeit technischer Beschreibung oder klarer Dokumentation.

Wenn die Produktseite Spannungs-, Leistungs-, Temperatur- und Anwendungsinformationen fehlen, ist ein solcher Heizer nicht für ein sicheres erstes Projekt geeignet.

## Erste Prüfung

Das erste Heizen wird kurz und unter Aufsicht durchgeführt.

Verfahren:

1. Überprüfen Sie den Heizerwiderstand und vergleichen Sie mit `R = U^2 / P`-Berechnung, wenn Spannung und Leistung bekannt sind.
2. Überprüfen Sie auf Kurzschlüsse, falls zutreffend.
3. Wenn es ein Metallgehäuse oder Schutzerdung `PE` gibt, überprüfen Sie, dass der Heizer nicht mit dem Gehäuse kurzschließt.
4. Überprüfen Sie die Versorgungsspannung ohne den Heizer.
5. Überprüfen Sie, dass der Steuerschalter die Last ausschaltet.
6. Überprüfen Sie, dass der Temperatursensor einen vernünftigen Wert anzeigt.
7. Bei `12V`/`24V`-Heizer, falls möglich, durch ein Labornetzgerät mit Strombegrenzung oder temporärer Sicherung starten.
8. Aktivieren Sie Heizen bei niedriger Leistung oder kurz.
9. Beobachten Sie, ob die Temperatur am richtigen Ort ansteigt.
10. Überprüfen Sie, dass der Ausschalt-Befehl das Heizen tatsächlich stoppt.
11. Überprüfen Sie das Heizen von Drähten, Anschlüssen, MOSFET/SSR und Gehäuse.
12. Überprüfen Sie den Notfallschutz durch ein Szenario, das Sie sicher simulieren können.

Lassen Sie einen neuen Heizer beim ersten Starten nicht unbeaufsichtigt.

## Typische Fehler

- Heizer an falscher Spannung angeschlossen;
- Strom nicht berechnet;
- Heizer über schwachen Stecker mit Strom versorgt;
- MOSFET für Netz-AC-Heizer verwendet;
- AC-SSR und DC-SSR verwechselt;
- SSR ohne Kühlkörper installiert, wenn nötig;
- Sicherung vergessen;
- kein unabhängiger Thermoschutz;
- schlechte Temperatursensor-Montage;
- Gehäuse aus PLA in Heizernähe gefertigt;
- Luftstrom nicht berücksichtigt und Filter verstopft;
- auf dem Tisch getestet, aber nicht im Gehäuse;
- Netzwerk-Teil exponiert gelassen;
- Sicherung erhöht statt zu finden, warum sie auslöste.

## Hauptpunkt

Ein Heizer wird nach der Aufgabe, Spannung, Leistung, Wärmeübertragungsmethode und Sicherheit ausgewählt. Sie können es nicht als einfache "Zweitleiter-Last" behandeln.

Berechnen Sie zuerst den Strom, wählen Sie Stromschalter, Verdrahtung und Sicherung. Stellen Sie dann Temperatursensor, Firmware-Schutz, unabhängigen Hardware-Thermoschutz, ein ordnungsgemäßes Gehäuse und praxisnahe Tests sicher.

## Referenzmaterialien

- [Klipper Configuration Reference: heater_generic and verify_heater](https://www.klipper3d.org/Config_Reference.html#heater_generic) - Heizer-Einstellungen, Temperatursensoren, `min_temp`, `max_temp` und Heizverifikation in Klipper.
- [Marlin Configuration: Temperature Ranges and Thermal Protection](https://marlinfw.org/docs/configuration/configuration.html#temperature-ranges) - Temperaturgrenzen, `MINTEMP`, `MAXTEMP` und Thermoschutz in Marlin.
- [Omron: Overview of Solid-state Relays](https://www.ia.omron.com/support/guide/18/introduction.html) - grundlegende Erklärung von SSR, Typen, Anwendung und thermische Maßnahmen.
- [Sensata/Crydom: SSR Heat Sink Reference](https://www.sensata.com/resources/brochure-solid-state-relays-heat-sink-reference) - warum SSR einen Kühlkörper benötigt und wie das Wärmeverhalten mit dem Laststrom zusammenhängt.
- [Omega: Cartridge Heaters](https://www.omega.nl/prodinfo/cartridge-heaters.html) - praktische Anmerkungen zur Heizpatronenanlage, Thermalkontakt und Leistungsauswahl.
