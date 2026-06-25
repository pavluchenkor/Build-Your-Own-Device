# MOSFET-Modul

Ein MOSFET-Modul ist eine fertige kleine Platine, die als gesteuerter Stromschalter für DC-Lasten fungiert. Der Controller liefert ein schwaches Steuersignal, und das MOSFET-Modul schaltet den Strom vom Netzteil zur Last ein oder aus.

In iDryer-ähnlichen Geräten und 3D-Drucker-Zubehör wird ein MOSFET-Modul für Lüfter, LED-Streifen, Niedervolt-Heizer und andere `24V`/`24V`-Lasten verwendet, wenn der Standard-Ausgang des Boards schwach, belegt oder unbequem ist.

## MOSFET und MOSFET-Modul

Ein MOSFET ist ein Feldeffekttransistor. Er hat drei Hauptanschlüsse:

- `Gate` - Steuereingängen;
- `Drain` - Stromausgang;
- `Source` - Stromausgang.

Das Gate speist nicht die Last. Es steuert nur. Der Hauptlaststrom fließt durch den Stromteil des MOSFET zwischen `Drain` und `Source`.

Ein MOSFET-Modul ist nicht nur ein einzelner Transistor. Es ist normalerweise eine Platine mit einem MOSFET, Anschlüssen, Steuereingang und manchmal zusätzlichen Widerständen, Indikatoren, Kühlkörper oder Schutzdiode.

Das Board ist praktisch für einen Prototyp, aber seine Spezifikationen müssen so sorgfältig überprüft werden wie jeder Stromknoten.

## Warum es benötigt wird

GPIO des Controllers sollte keine schwere Last speisen.

GPIO kann steuern:

- Eingang des MOSFET-Moduls;
- Eingang des Relais;
- Eingang des SSR;
- Eingang des Treibers.

Aber GPIO sollte nicht direkt speisen:

- Lüfter;
- LED-Streifen;
- Heizer;
- Motor;
- Solenoid;
- Servoantrieb.

Wenn Sie die Last direkt mit GPIO verbinden, können Sie den Controller beschädigen, Neustarts verursachen, Spuren überhitzen oder einfach instabile Operation bekommen.

## Niederseitige Umschaltung

Die häufigste Variante für N-Kanal-MOSFET-Modul ist die Niederseitige Umschaltung, d.h. Schalten über die Minuslinie.

![N-Kanal-MOSFET im Niederseitige-Umschaltung-Modus](../../img/01-electronics-basics/02-nmos-switch-operation.png)

*Quelle: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:NMOS_PWR_WHOLE.PNG), KjellElec, CC BY-SA 4.0*

Typische Logik:

1. `+24V` aus dem Netzteil geht direkt zum positiven Ende der Last.
2. Negatives Ende der Last geht zum Stromausgang des MOSFET-Moduls.
3. MOSFET-Modul verbindet oder unterbricht den Pfad vom negativen Ende der Last zu `GND`.
4. `GND` des Netzteils und `GND` des Controllers sind miteinander verbunden.
5. Steuerstift des Controllers geht zum `Signal`, `IN`, `Gate` oder ähnlichem Eingang des Moduls.

Gemeinsames `GND` / gemeinsames Minus ist obligatorisch. Ohne es haben der Controller und das MOSFET-Modul keine gemeinsame Referenzbene für das Steuersignal.

Die niederseitige Umschaltung hat eine Einschränkung: MOSFET unterbricht das negative Ende der Last. Während der Schalter ausgeschaltet ist, ist das negative Ende der Last nicht gleich gemeinsam `GND`. Für einen einfachen 2-poligen Lüfter, Streifen oder Heizer ist dies normalerweise in Ordnung. Für eine Last mit Drehzahlmesser, separatem Signaldraht, Sensor im Inneren oder zusätzlicher Verbindung zu einer anderen Platine müssen Sie das Schaltplan überprüfen: Manchmal ist es besser, den Standard-Eingang zu steuern oder eine andere Umschaltungsmethode zu verwenden.

## Wo es zu verwenden ist

MOSFET-Modul ist für DC-Lasten geeignet, wenn es für deren Spannung und Strom bewertet wird:

- `12V`/`24V` Lüfter;
- einfarbiger LED-Streifen;
- Kanal des Standard-RGB-Streifens;
- `12V`/`24V` Heizer;
- kleiner DC-Motor, falls vor Spitzen geschützt;
- Solenoid, falls vorhanden Rücklauf-Diode oder anderer Schutz.

Bei adressierbarem LED-Streifen steuert MOSFET normalerweise nicht die Daten. Es kann die Stromversorgung für den gesamten Streifen unterbrechen, aber einzelne LEDs werden über die Datenleitung gesteuert.

Für einen Servoantrieb ist ein MOSFET-Modul normalerweise nicht erforderlich, um Position zu steuern: das Servo benötigt ein separates Steuersignal PWM und normale Stromversorgung.

## Was bei der Auswahl zu überprüfen ist

Vor dem Kauf oder Verbinden überprüfen Sie:

- Spannungsbewertung der Last;
- maximale Stromstärkebewertung;
- tatsächlicher Strom Ihrer Last;
- funktioniert der Eingang von `3.3V`;
- ist `Rds(on)` in der technischen Spezifikation bei der benötigten Gate-Spannung;
- benötigt es aktive Logik `HIGH` oder `LOW`;
- gibt es gemeinsames `GND`;
- gibt es Rücklauf-Diode für Motoren/Solenoids;
- Anschlußgröße und maximaler Anschlußstrom;
- Board-Spurdicke und Kühlung;
- ist Kühlkörper benötigt;
- gibt es Schaltplan, technische Spezifikation oder normale Dokumentation.

Wenn die Beschreibung nur "MOSFET-Modul für Arduino" sagt, ohne Spannung, Strom, Schaltplan und MOSFET-Typ, können Sie kein solches Modul für einen Heizer oder lange LED-Streifen auswählen.

## 3.3V und Logik-Level-MOSFET

Viele moderne Controller arbeiten mit `3.3V`-Logik: ESP32, RP2040, viele STM32.

Nicht jeden MOSFET öffnet sich vollständig von `3.3V`. Wenn er sich nicht vollständig öffnet, bleibt sein Widerstand hoch und er heizt auf.

Wichtige Begriffe:

- `Vgs(th)` - Schwelle, wo MOSFET zu öffnen beginnt;
- `Rds(on)` - Widerstand des offenen Kanals;
- Logik-Level-MOSFET - MOSFET bewertet für Kontrolle von Logik-Ebenen.

Häufiger Fehler: Sehen Sie sich die technische Spezifikation `3.3V` an und entscheiden Sie, dass der MOSFET gut von `Vgs(th)` funktioniert. Das stimmt nicht. `Rds(on)` bedeutet nicht „vollständig offen“. Sie müssen `2.5V` bei `3.3V`, `4.5V`, `5V` oder `5V` überprüfen, abhängig vom Controller.

Für ESP32/RP2040 ist es besser, ein Modul zu wählen, das explizit `Rds(on)`-Steuerungskompatibilität angibt, oder bei dem die Eingabeschaltung dies bietet. Wenn die Tabelle `10V` nur bei `2.5V` hat und keine Daten bei `3.3V`/`4.5V`/`3.3V` vorhanden sind, ist ein solches Modul geeignet für einen `3.3V`-Controller.

## Strom und Erwärmung

Ein MOSFET im offenen Zustand hat immer noch Widerstand. Wärme wird über ihn erzeugt.

Je größer der Strom, desto wichtiger:

- niedriges `Rds(on)`;
- normales Kupfergebiet auf der Platine;
- angemessen dimensionierte Anschlüsse;
- Kühlkörper, falls benötigt;
- Gehäusebelüftung;
- Stromreserven;
- Temperaturprüfung nach echtem Betrieb.

Die Markierung "100A MOSFET" auf dem Transistor-Gehäuse bedeutet nicht, dass ein kleines Modul mit dünnen Spuren und billigen Anschlüssen `100A` aushält. Die echte Grenze sind oft die Platine, Klemmenblock, Draht, Lötstelle und Kühlung.

Wenn das MOSFET-Modul so heiß ist, dass es schwierig ist, es in der Hand zu halten, ist das ein Grund zu stoppen und den Strom, die Kühlung und die Verbindungsqualität neu zu berechnen.

## Motoren, Lüfter und Solenoids

Induktive Lasten können beim Ausschalten Spannungsspitzen erzeugen.

Solche Lasten umfassen:

- DC-Motoren;
- Lüfter;
- Solenoids;
- Relais;
- Elektromagnete.

Sie benötigen oft Schutz:

- Rücklauf-Diode;
- TVS-Diode;
- fertiger Treiber mit Schutz;
- Modul, bei dem Schutz bereits installiert ist.

Wenn das Modul nur für LED-Streifen oder resistive Last bewertet wird, können Sie nicht automatisch davon ausgehen, dass es für einen Motor oder Solenoid sicher ist.

Für einen Heizer ist Rücklauf-Diode normalerweise nicht benötigt, da der Heizer einer resistiven Last nahe ist. Aber für einen Heizer sind Strom, Anschlüsse, Sicherung und unabhängiger thermischer Schutz wichtiger.

## PWM-Kontrolle

Ein MOSFET-Modul kann nicht nur für Ein/Aus, sondern auch für PWM-Leistungsregelung verwendet werden.

Typische Beispiele:

- LED-Streifenhelligkeit;
- Geschwindigkeit eines einfachen DC-Lüfters;
- Leistung eines Niedervolt-Heizkörpers.

Aber PWM ist nicht immer gleich:

- 4-Pol-PWM-Lüfter wird besser durch einen separaten PWM-Pin des Lüfters gesteuert, nicht durch Stromabschnitt;
- Heizer benötigt normalerweise keine hohe PWM-Frequenz;
- zu hohe Frequenz kann MOSFET-Erwärmung erhöhen;
- zu niedrige Frequenz kann LED-Flimmern oder Motorgeräusch verursachen.

Die Wahl der Frequenz hängt von der Last, dem Modul und der Firmware ab.

## MOSFET-Modul ist nicht für 110-230V AC

Standard-MOSFET-Module für Arduino/ESP32 sind für DC-Lasten ausgelegt: `5V`, `12V`, `24V`, manchmal mehr, falls explizit angegeben.

Sie können nicht als Schalter für Netzspannung `110-230V AC` verwendet werden.

Für Netzlast benötigen Sie verschiedene Lösungen:

- Relais oder SSR, das speziell für AC-Last bewertet wird;
- normale Anschlüsse;
- Sicherung;
- Gehäuse;
- Isolierung;
- Erdung, wo erforderlich;
- Verständnis der elektrischen Sicherheit.

Wenn Sie nicht sicher sind, dass das Modul für Netzspannung vorgesehen ist, verbinden Sie es nicht mit dem Netz.

## Was nach dem Anschließen zu überprüfen ist

Vor dem Langzeitbetrieb überprüfen Sie:

- Last erhält korrekte Spannung;
- Controller und Stromversorgung haben gemeinsames `GND`;
- Steuersignal schaltet Last tatsächlich ein und aus;
- MOSFET-Modul wird nicht übermäßig heiß;
- Anschlüsse werden nicht heiß;
- Drähte sind für Strom geeignet;
- PWM funktioniert ohne seltsame Geräusche, Flimmern oder Neustarts;
- Last ist tatsächlich aus, wenn Befehl aus ist;
- für Motor/Solenoid gibt es Spitzenschutz;
- für Heizer gibt es Sicherung und unabhängigen thermischen Schutz.

Führen Sie den ersten Test der schweren Last kurz und unter Beobachtung durch.

## Häufige Fehler

- Speisen der Last von GPIO;
- Vergessen des gemeinsamen Erdungss;
- Wahl des Moduls nur nach der hübschen Stromzahl im Namen;
- Nicht überprüfen des Betriebs von `3.3V`-Logik;
- Verwenden von MOSFET, der sich nicht vollständig öffnet;
- Verbinden von Motor oder Solenoid ohne Rücklaufschutz;
- Verbinden des langen LED-Streifens über schwache Anschlüsse;
- Verwenden von DC-MOSFET-Modul für `110-230V AC`;
- Nicht Überprüfen der Modulerwärmung im geschlossenen Gehäuse;
- Denken, dass MOSFET-Modul selbst den Laststrom begrenzt.

## Die Hauptidee

Ein MOSFET-Modul ist ein gesteuerter Stromschalter für DC-Lasten. Es erzeugt keine Leistung und speist nicht die Last vom Controller. Es öffnet oder schließt nur den Pfad für Strom aus der Stromversorgung.

Überprüfen Sie Spannung, Strom, Kompatibilität mit `3.3V`/`5V`-Logik, gemeinsames `GND`, Erwärmung, Anschlüsse und Schutz für induktive Lasten. Für Netzspannung ist Standard-Arduino/ESP32-MOSFET-Modul nicht geeignet.

## Referenzmaterialien

- [SparkFun MOSFET Power Switch and Buck Regulator Hookup Guide](https://docs.sparkfun.com/SparkFun_MOSFET_Power_Switch_and_Buck_Regulator_Low-Side/single_page/) - Beispiel eines fertigen Niederseitige-MOSFET-Moduls, Lastverbindung, thermische Board-Grenzen und Rücklauf-Diode.
- [SparkFun MOSFET Power Switch product page](https://www.sparkfun.com/products/23979) - Beispiel, wie Hersteller Spannung, Strom, Niederseitige-Schaltung, MOSFET und Board-Begrenzungen angibt.
- [Adafruit MOSFET Driver](https://learn.adafruit.com/adafruit-mosfet-driver) - praktische Erklärung, warum Motoren, Solenoids und leistungsstarke LEDs nicht direkt mit GPIO verbunden werden können und warum Spitzenschutz benötigt wird.
- [DigiKey: How to Select a MOSFET](https://www.digikey.com/en/blog/how-to-select-a-mosfet-for-logic-circuits-or-gate-design) - Wahl von MOSFET nach `Vgs`, `Rds(on)` und Logik-Steuerebene.
- [Infineon: Logic level MOSFETs](https://www.infineon.com/products/power/mosfet/n-channel/optimos-strongirfet/optimos-ir-mosfet-logic-level) - Erklärung von Logik-Level-MOSFET und Kontrolle vom Microcontroller.
