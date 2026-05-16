# Diagnose-Checkliste

Diese Checkliste wird benötigt wenn das Gerät nicht funktioniert oder sich seltsam verhält.

Die Idee ist einfach: erst die Gefahr entfernen, dann Stromversorgung und Verdrahtung überprüfen, und erst danach zu Firmware, Sensoren und Lasten gehen.

## 1. Stoppen und Stromversorgung ausschalten

Zuerst schalten Sie das Gerät aus.

Besonders wenn es gibt:

- Geruch;
- Draht wird heiß;
- Anschluss wird heiß;
- Rauch;
- seltsamer Laut;
- Funken;
- Heizer will nicht ausschalten;
- Schutzschalter oder Sicherung fliegt.

Ändern Sie keine Drähte unter Stromversorgung.

## 2. Stromlast trennen

Vor der Diagnose ist besser temporär zu trennen:

- Heizer;
- kraftvoller LED-Streifen;
- Servo;
- Motor;
- externe Stromlast.

Zuerst überprüfen Sie Controller und Logik sind am Leben ohne gefährliche Last.

Wenn Gerät 110-230V AC hat, halten Sie nicht offen Netzteil unter Stromversorgung auf Arbeitstisch.

## 3. Stromversorgung überprüfen

Mit Multimeter überprüfen Sie:

- gibt es Spannung am Stromversorgungs-Ausgang;
- ist Spannung richtig;
- ist Polarität richtig;
- sinkt Spannung unter Last.

Zum Beispiel:

- 24V Leitung sollte etwa 24V sein;
- 12V Leitung sollte etwa 12V sein;
- 5V Leitung sollte etwa 5V sein;
- 3.3V Leitung sollte etwa 3.3V sein.

Annehmbare Abweichung hängt von Stromversorgung und Gerät ab, aber ein offensichtlicher Fehler wie 24V statt 12V sollte vor Last-Verbindung gefunden werden.

## 4. Polarität überprüfen

Überprüfen Sie wo Plus und Minus sind.

Vertrauen Sie nicht nur auf Drahtfarbe.

Überprüfen Sie:

- Board-Markierungen;
- Stromversorgungs-Markierungen;
- Modul-Pinout;
- Multimeter;
- Verbindungsdiagramm.

Umgekehrte Polarität tötet Modul oft sofort.

## 5. Gemeinsames GND überprüfen

Wenn es externes Modul oder separate Stromversorgung gibt, überprüfen Sie gemeinsames `GND`.

Das ist wichtig für:

- MOSFET-Modul;
- Servo;
- PWM-Lüfter;
- HX711;
- RFID;
- externe Sensoren;
- separater DC-DC.

Wenn Signale zwischen Geräten gehen, müssen sie eine gemeinsame Referenzstufe haben, sofern Schaltung spezielle Isolation nicht nutzt.

## 6. Anschlüsse und Steckverbinder überprüfen

Inspizieren Sie:

- Draht ganz eingeführt;
- Leiter angeklemmt, nicht Isolierung;
- keine freiliegenden Litzen;
- keine Dunkelheit;
- kein Geruch;
- Anschluss wackelt nicht;
- Stecker hält nicht "auf Treu";
- Gehäusedeckel quetscht Draht nicht.

Drähte mit Stromversorgung bewegen aus. Wenn Kontakt klar mechanisch sinkt, überprüfen Sie zuerst Verdrahtung.

## 7. Controller ohne Last überprüfen

Controller ohne Stromlast verbinden.

Überprüfen Sie:

- ist es via USB erkannt;
- startet Firmware;
- gibt es Kommunikation mit Host;
- wird Mikrocontroller nicht heiß;
- flickert Stromversorgung nicht;
- sind Logs sichtbar.

Wenn Controller nicht erkannt wird auch ohne Last, verbinden Sie nicht Heizer und Strommodulen wieder bis Sie die Ursache finden.

## 8. Firmware und Konfiguration überprüfen

Überprüfen Sie:

- Firmware gebaut für richtig Board;
- richtig Seriell/CAN/USB-Pfad ausgewählt;
- Pins in Config passen zu Pinout;
- `sensor_type` richtig;
- `min_temp` und `max_temp` angemessen;
- Ausgänge nicht versehentlich invertiert;
- keine Pin-Konflikte.

Wenn Heizer sich nach Konfiguration-Änderung entgegengesetzt verhält, zum Beispiel "aus", aber Temperatur steigt, schalten Sie Stromversorgung aus und überprüfen Sie Config und Stromschaltkreis.

## 9. Sensoren überprüfen

Vor Heizen überprüfen Sie Sensoren.

Für Thermistor:

- Temperatur wie Zimmer-Temperatur;
- kein `MINTEMP`;
- kein `MAXTEMP`;
- Ablesungen springen nicht;
- Widerstand wie erwartet;
- wenn von Hand geheizt ändern sich Ablesungen richtig.

Für andere Sensoren:

- Stromversorgung richtig;
- Schnittstelle richtig ausgewählt;
- Adresse oder Pins passen Config;
- Drähte kurz und nicht hängend.

## 10. Ausgang ohne Last überprüfen

Wenn MOSFET, Relais oder Board-Ausgang überprüft werden muss, machen Sie es zuerst ohne gefährliche Last.

Optionen:

- kleiner Test-Lüfter;
- LED mit Widerstand;
- Multimeter;
- schwache sichere Last.

Starten Sie nicht Diagnose mit kraftvollem Heizer.

Für Heizer vor erstem Einschalten ist numerische Überprüfung nützlich: messen Sie Widerstand und vergleichen Sie zu erwartet `R = U^2 / P`. Wenn es Metall-Gehäuse oder `PE` gibt, überprüfen Sie keine Kurzschluss zu Gehäuse. Für `12V`/`24V` Heizer erstes Lauf ist besser durch Labor-Stromversorgung mit Strom-Limit oder vorübergehende Sicherung.

## 11. Stromschalter separat überprüfen

Für MOSFET/SSR/Relais überprüfen Sie:

- richtig Last-Typ: AC oder DC;
- richtig Spannung;
- richtig Anschlüsse;
- Steuereingang;
- gemeinsames `GND` wenn benötigt;
- Kühlkörper wenn benötigt;
- Eingang und Ausgang nicht gemischt.

AC SSR und DC SSR können nicht ausgetauscht werden.

Für SSR separat überprüfen "aus" Zustand: mit Steuerungssignal entfernt Last muss nicht heiß. Zuerst besser nutzen sichere kleine Last, Lampe oder Multimeter, nicht Haupt-Heizer.

## 12. Last mit kurzem Test verbinden

Wenn grundlegende Überprüfungen bestanden, verbinden Sie Last kurz und unter Aufsicht.

Überprüfen Sie:

- Last schaltet ein;
- Last schaltet aus;
- Anschlüsse werden nicht heiß;
- Drähte werden nicht heiß;
- MOSFET/SSR wird nicht extrem heiß;
- Sensor zeigt realistische Temperatur;
- Controller startet nicht neu;
- Sicherung fliegt nicht.

Erster Heizer-Test sollte nicht lang und unbeaufsichtigt sein.

## 13. Überprüfen nach wenigen Minuten Betrieb

Nach wenigen Minuten überprüfen Sie:

- Anschlüsse;
- Drähte;
- Stromversorgung;
- MOSFET;
- SSR;
- Gehäuse in der Nähe des Heizers;
- Sensor-Ablesungen;
- Controller-Stabilität.

Wenn etwas unerwartet heiß wurde, schalten Sie Stromversorgung aus und kehren Sie zurück zu Überprüfung von Stromversorgung, Verdrahtung und Stromschalter.

## Was nicht zu tun

Sie können nicht:

- Gerät wiederholt einschalten wenn etwas heizt oder riecht;
- 110-230V AC offen auf Arbeitstisch halten;
- Drähte unter Stromversorgung ändern;
- Sicherung "so dass es nicht fliegt" erhöhen;
- thermischen Schutz zum Testen deaktivieren;
- Notfall-Thermostat kurzschließen;
- kraftvollen Heizer ohne Temperatursensor testen;
- erstes Test unbeaufsichtigt lassen.

## Kurze Reihenfolge

Wenn Sie sehr kurze Reihenfolge brauchen:

1. Stromversorgung ausschalten.
2. Stromlast trennen.
3. Stromversorgungs-Spannung überprüfen.
4. Polarität überprüfen.
5. Gemeinsames `GND` überprüfen.
6. Anschlüsse und Drähte überprüfen.
7. Controller ohne Last überprüfen.
8. Firmware und Pinout überprüfen.
9. Sensoren überprüfen.
10. Ausgang ohne gefährliche Last überprüfen.
11. MOSFET/SSR/Relais überprüfen.
12. Last mit kurzem Test verbinden.
13. Drähte, Anschlüsse und Stromteilheiz überprüfen.

## Wichtige Punkte

- Diagnose beginnt mit Stromversorgung ausschalten und Risiko reduzieren.
- Stromlast besser getrennt für grundlegende Überprüfungen.
- Stromversorgung, Polarität, `GND` und Anschlüsse überprüft bevor Firmware.
- Heizer kann nicht als erster Test-Indikator verwendet werden.
- Wenn Schutz ausgelöst wurde, finden Sie Ursache, nicht Schutz deaktivieren.

## Referenzen

- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - grundlegende Abfolge zum Überprüfen von Verbindungen, Stromversorgung und Hardwareproblemen.
- [SparkFun: How to Power a Project](https://learn.sparkfun.com/tutorials/how-to-power-a-project/voltagecurrent-considerations) - wie man über Spannung, Strom und Projekt-Stromversorgung denkt.
- [Fluke: How to Measure Resistance with a Digital Multimeter](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-resistance) - sichere Widerstands-Messung auf de-energisiertem Schaltkreis.
- [Tom's Hardware: How to Fix 3D Printer Thermal Runaway](https://www.tomshardware.com/3d-printing/how-to-fix-3d-printer-thermal-runaway) - praktische Überprüfung von Thermistor, Heizer, Lüfter, Stromversorgung und Verdrahtung.
- [Klipper Configuration Reference: min_temp, max_temp and verify_heater](https://www.klipper3d.org/Config_Reference.html#verify_heater) - Software-Überprüfung von Temperatur, Sensor und erwartetem Heizer-Temperaturanstieg.
