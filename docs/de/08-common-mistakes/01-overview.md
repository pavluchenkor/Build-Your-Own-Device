# Häufige Fehler

Dieser Abschnitt dient nicht dazu Sie zu kritisieren.

Er ist da um Ihnen zu helfen, häufige Fehler in einem DIY-Gerät schnell zu identifizieren: durchhängende Stromversorgung, lockerer Draht, Sensor zeigt Müll, Controller startet neu, Heizer verhält sich seltsam.

Das Abschnittformat ist unkompliziert:

- Symptom;
- wahrscheinliche Ursache;
- was überprüfen;
- was nicht tun;
- wie sicher reparieren.

## Die Hauptregel der Diagnostik

Wenn sich das Gerät seltsam verhält, ändern Sie nicht sofort die Firmware, löten Sie nicht alles um oder erhöhen Sie nicht die Stromversorgung.

Zuerst überprüfen Sie die Grundlagen:

1. Stromversorgung;
2. Polarität;
3. gemeinsames `GND`;
4. Anschlüsse und Steckverbinder;
5. Sensoren;
6. Stromschalter;
7. Firmware und Konfiguration.

Die meisten Probleme bei einfachen Geräten stellen sich nicht als „komplexe Elektronik“ heraus, sondern als Stromversorgung, Verdrahtung oder falsche Verbindungen.

## Wann stoppen

Schalten Sie sofort die Stromversorgung aus wenn:

- Brandgeruch erscheint;
- Draht wird heiß;
- Anschluss wird heiß;
- Stecker wird dunkel;
- Gehäuse wurde an einer unerwarteten Stelle heiß;
- Heizer lässt sich nicht ausschalten;
- Schutzschalter oder Sicherung fliegt;
- Temperatursensor zeigt Müll;
- Gerät funktioniert nur wenn Sie den Draht bewegen.

Nicht "es nochmal einschalten um zu schauen". Wenn etwas heizt, riecht oder Funken wirft, finden Sie zuerst die Ursache ohne Stromversorgung.

## Hauptgruppen von Fehlern

In diesem Abschnitt sind Fehler in Gruppen unterteilt:

- `02-power-mistakes.md` - schwache Stromversorgung, falsche Spannung, durchhängen, dünne Drähte, kein Spielraum.
- `03-wiring-mistakes.md` - umgekehrte Polarität, schlechte Anschlüsse, kein gemeinsames GND, schlechte Steckverbinder.
- `04-controller-mistakes.md` - ungeeignetes Board, 3.3V/5V Logik, GPIO statt Stromausgang, falsche Firmware.
- `05-heater-ssr-mistakes.md` - Heizer, SSR, MOSFET, 110-230V AC, Temperatursensor, Kühlkörper und Schutz.
- `06-diagnostic-checklist.md` - allgemeine Überprüfungsreihenfolge wenn Gerät nicht funktioniert.

## Warum Stromversorgung zuerst überprüft wird

Stromversorgung beeinflusst fast alles.

Wenn die Stromversorgung schwach oder die Drähte dünn sind, Symptome können wie ein Firmware-Problem aussehen:

- Controller startet neu;
- Wi-Fi fällt ab;
- Bildschirm flackert;
- Servo ruckt;
- Lüfter startet nicht;
- Sensoren zeigen zufällige Werte;
- Heizer heizt schlecht.

Bis die Stromversorgung mit einem Multimeter unter Last überprüft wird, ist es schwierig alles andere zuverlässig zu diagnostizieren.

## Warum Verdrahtung wichtiger ist als es scheint

Eine schlechte Verbindung kann „fast normal“ funktionieren.

Das ist genau was gefährlich ist:

- heute funktioniert es;
- wenn gerüttelt wird es getrennt;
- wenn geheizt wird wird der Kontakt schlechter;
- Anschluss wird allmählich dunkel;
- Draht fängt an heiß zu werden;
- Sensor erscheint und verschwindet.

Wenn das Gerät sein Verhalten ändert wenn Sie den Draht bewegen, ist dies kein Softwarefehler. Dies ist ein Verbindungsproblem.

## Warum Schutz nicht deaktiviert werden darf

Thermisches Durchgehen, `MINTEMP`, `MAXTEMP`, "Heizer heizt nicht" und ähnliche Fehler existieren nicht um den Benutzer zu ärgern.

Dies sind Zeichen dass der Controller der Temperaturablesing nicht mehr traut oder gefährliche Heizverhalten sieht.

Schlechte Idee:

- thermischen Schutz deaktivieren;
- Temperaturgrenzen ohne Verständnis der Ursache erweitern;
- Sicherung mit einer größeren ersetzen;
- Thermostat direkt kurzschließen;
- Schutz "zum Testen" kurzschließen.

Richtige Idee: die Ursache für das Auslösen des Schutzes finden.

## Wie man diesen Abschnitt liest

Wenn das Gerät überhaupt nicht funktioniert, beginnen Sie mit der Diagnose-Checkliste.

Wenn das Symptom klar ist, gehen Sie zu relevanten Artikel:

- Reboots, Flackern, schwache Wärme - Stromversorgung;
- funktioniert wenn Sie den Draht bewegen - Verdrahtung;
- Board nicht erkannt oder Pins reagieren nicht - Controller;
- Heizer will nicht ausschalten oder SSR wird heiß - Heizer und SSR;
- alles ist unklar - allgemeine Checkliste.

## Wichtige Punkte

- Die meisten Fehler beginnen mit Stromversorgung, Verdrahtung und falschen Verbindungen.
- Wenn etwas heizt, riecht oder wird dunkel, schalten Sie Stromversorgung aus.
- Diagnostik verläuft von einfach zu komplex.
- Firmware-Schutz und Hardware-Schutz darf nicht zur Bequemlichkeit deaktiviert werden.
- AC Netzspannung 110-230V kann nicht "auf dem Arbeitstisch" ohne Verständnis der Elektrosicherheit diagnostiziert werden.

## Referenzen

- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - grundlegender Ansatz zum Überprüfen von Verbindungen, Stromversorgung, Heizen und Hardwareproblemen.
- [SparkFun: How to Power a Project](https://learn.sparkfun.com/tutorials/how-to-power-a-project/voltagecurrent-considerations) - Spannung, Strom und Auswahl der Stromversorgung für ein elektronisches Projekt.
- [Tom's Hardware: How to Fix 3D Printer Thermal Runaway](https://www.tomshardware.com/3d-printing/how-to-fix-3d-printer-thermal-runaway) - praktische Analyse von Temperatursensor, Heizer, Lüfter, Stromversorgung und Verdrahtung während thermischen Durchgehens.
- [Klipper Configuration Reference: verify_heater](https://www.klipper3d.org/Config_Reference.html#verify_heater) - offizielle Heizer-Verifizierung und Temperatursensor-Überprüfung durch erwarteten Temperaturanstieg und kumulierten Fehler.
- [SparkFun Qwiic Power Meter guide](https://docs.sparkfun.com/SparkFun_Qwiic_Power_Meter_ACS37800/hardware_assembly/) - Beispiel der Notwendigkeit von gemeinsamen `GND` beim Messen/Steuern externe Last.
