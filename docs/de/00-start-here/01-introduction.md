# Erste Schritte

Du druckst bereits auf einem 3D-Drucker und möchtest einen Filamenttrockner bauen. Aber wenn du das Schaltplan öffnest, entstehen sofort Fragen: Welches Netzteil, wo geht die Masse hin, MOSFET oder SSR, warum brauchst du einen Kühlkörper. Dieser Abschnitt beantwortet diese Fragen Schritt für Schritt — von der ersten Stromberechnung bis zum funktionierenden Gerät.

Nach diesem Abschnitt wirst du verstehen, was du baust, warum genau auf diese Weise, wo Gefahren lauern könnten und wie du das Gerät vor dem Einschalten prüfst.

Der Abschnitt führt dich allmählich von einfachen Konzepten zu echten Ergebnissen.

Der Weg geht hier von einfach zu komplex:

1. Zuerst verstehen Sie Leistung, Strom, Last und grundlegende Sicherheit.
2. Dann erfahren Sie, welche Controller existieren und welchen Sie wählen sollten.
3. Dann verstehen Sie grundlegende Komponenten: Heizer, Lüfter, Sensoren, Displays, RFID und Wägezellen.
4. Dann lernen Sie, minimale Werkzeuge zu verwenden: Multimeter, USB-UART, Lötkolben, Crimpzange.
5. Dann gehen Sie zu praktischen Verbindungen über.
6. Dann denken Sie über das Gehäuse und die 3D-gedruckten Teile nach.
7. Am Ende haben Sie eine Liste häufiger Fehler und eine Diagnose-Checkliste zur Hand.

Die Hauptidee:

Du musst nicht alle Elektronik auf einmal verstehen. Es reicht aus, Schritt für Schritt vorzugehen und jedes Mal den nächsten kleinen Schritt zu verstehen.

Was dieser Abschnitt vermitteln sollte:

- Verständnis dafür, wie sich Niederspannungskreise `12V`/`24V DC` von der Netzspannung `110-230V AC` unterscheiden;
- Fähigkeit, den Laststrom grob zu berechnen;
- Verständnis, wann man MOSFET, SSR oder Relais braucht;
- Verständnis, wie sich ESP32, Arduino, RP2040 und STM32 in der Praxis unterscheiden;
- Verständnis, warum für Klipper MCU RP2040 oder STM32 besser sind;
- Grundlegendes Verständnis von Sensoren, Lüftern, Heizern und Displays;
- Minimale Multimeter-Diagnosefähigkeiten;
- Verständnis, welche gedruckten Teile in der Nähe von Wärme platziert werden können;
- Liste von Fehlern, die man besser nicht wiederholt.

Was dieser Abschnitt nicht tut:

- ersetzt keinen Elektrikker beim Arbeiten mit `110-230V AC`;
- unterrichtet kein tiefes Schaltungsdesign;
- versucht nicht, alle Physik zu erklären;
- gibt keine Erlaubnis, gefährliche Geräte ohne Sicherheitsverständnis zusammenzubauen.

Wie man liest:

- wenn das Thema neu ist — gehen Sie in Ordnung vor;
- wenn Sie bereits Geräte gebaut haben — öffnen Sie den benötigten Abschnitt als Referenz;
- wenn das Gerät nicht funktioniert — schauen Sie zuerst unter `08-common-mistakes`;
- wenn Sie mit `110-230V AC` arbeiten — lesen Sie zuerst alles über Sicherheit, SSR, Drähte, Anschlüsse und Schutzleiter.

## Referenzmaterialien

- [SparkFun: Voltage, Current, Resistance, and Ohm's Law](https://learn.sparkfun.com/tutorials/voltage-current-resistance-and-ohms-law) - grundlegende Konzepte von Spannung, Strom, Widerstand, geschlossenem Stromkreis und Ohmsches Gesetz.
- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/all) - praktische Reihenfolge der anfänglichen Diagnose: Stromversorgung, Verbindungen, Polarität, Lötstellen, Kabel und Spannungsabfälle.
- [Fluke: How to Measure Resistance with a Digital Multimeter](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-resistance) - warum Widerstandsmessungen mit ausgeschalteter Stromversorgung durchgeführt werden und warum ein Multimeter zur Komponentenprüfung benötigt wird.
- [OSHA: Electrical Incidents - Grounding](https://www.osha.gov/etools/construction/electrical-incidents/grounding) - warum Schutzleiter notwendig sind und warum die Arbeit mit Netzspannung separate Sicherheitsdisziplin erfordert.

## Siehe auch

- [Lastberechnung 24V](../01-electronics-basics/01-load-calculation-24v.md) - erstes praktisches Thema über Spannung, Strom, Leistung und Stromversorgungsreserven.
- [Häufige Komponenten](../03-common-components/01-overview.md) - Übersicht der Teile, die am häufigsten in einfachen Geräten vorkommen.
- [Werkzeuge](../05-tools/01-overview.md) - was Sie zum Prüfen, Flashen, Löten und Diagnostizieren brauchen.
- [Praktische Anleitungen](../06-practical-guides/01-connecting-fan.md) - Beispiel einer ersten sicheren Lastverbindung über den Controller.
- [Häufige Fehler](../08-common-mistakes/01-overview.md) - worauf Sie achten sollten, wenn das Gerät nicht angeht, überhitzt, Geräusche macht oder instabil läuft.
