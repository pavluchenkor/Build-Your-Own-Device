# Verdrahtungsfehler

Verdrahtung bricht das Gerät mehr kaputt als die Elektronik selbst.

Schlechter Kontakt, umgekehrte Polarität oder schwacher Anschluss können wie ein Firmware-, Sensor- oder Controllerfehler aussehen.

## Symptome

Typische Zeichen von Verdrahtungsproblemen:

- Gerät funktioniert manchmal, dann nicht;
- Board nur erkannt wenn Kabel bewegt wird;
- Sensoren zeigen Müll;
- Temperatur springt;
- Lüfter startet zeitweise;
- USB fällt ab;
- Anschluss wird heiß;
- Draht wird dunkel oder riecht;
- Modul funktioniert auf dem Arbeitstisch, aber nicht im Herbst;
- nach Schließung des Deckels funktioniert Gerät nicht.

Wenn ein Symptom sich ändert wenn der Draht bewegt wird, überprüfen Sie zuerst die Verdrahtung.

## Umgekehrte Plus und Minus

Polarität kann nicht "nach Farbe" überprüft werden.

Roter Draht ist oft Plus, schwarzer Draht oft Minus, aber das ist keine Garantie. In einem DIY-Gerät könnte der vorherige Erbauer oder Sie selbst die Farben verwechselt haben.

Bevor Sie verbinden:

- überprüfen Sie Board-Markierungen;
- überprüfen Sie Modul-Pinout;
- messen Sie Spannung mit Multimeter;
- überprüfen Sie wo `+` und wo `GND`;
- verbinden Sie Modul nicht wenn Pinout unklar ist.

Umgekehrte Polarität kann sofort ein Board, Sensor, Lüfter oder DC-DC zerstören.

## Kein gemeinsames Erdung

Gemeinsames Erdung wird benötigt wenn ein Modul separat betrieben wird und das Signal vom Controller kommt.

Beispiele:

- Servo mit separater 5V Stromversorgung;
- MOSFET-Modul für Lüfter;
- 4-Pin PWM Lüfter;
- HX711;
- RFID-Modul;
- externer Sensor.

Ohne gemeinsames `GND` könnte das Signal nicht sinnvoll sein. Gerät könnte nicht reagieren, rucken oder instabil funktionieren.

## Schlechter Kontakt im Anschluss

Anschluss könnte angeklemmt aussehen, aber Draht schlecht halten.

Gründe:

- Draht nicht ganz eingeführt;
- Isolierung angeklemmt statt Leiter;
- geflochtener Draht ausgefranst;
- Schraube gelockert;
- Anschluss nicht für Strom bewertet;
- Draht zu dünn oder zu dick für Anschluss;
- keine Aderendhülse wo benötigt.

Schlechter Kontakt verursacht Erwärmung. Erwärmung verschlimmert Kontakt. Dies ist ein gefährlicher Zyklus.

Nach kurzem Test unter Last überprüfen ob Anschlüsse und Steckverbinder heiß werden.

## Dupont nicht für Stromlast

Dupont-Drähte sind praktisch für Steckbretter und schwache Signale.

Aber sie können nicht als normale Stromverdrahtung angesehen werden für:

- Heizer;
- kraftvolle Lüfter;
- LED-Streifen;
- Servos mit großem Strom;
- Geräte-Stromversorgung;
- 110-230V AC.

Dupont könnte schlecht halten, kleine Kontaktfläche haben und bei Strömen heiß werden für die es nicht entworfen ist.

Für den Stromteil benötigen Sie richtige Anschlüsse, Steckverbinder, Drahtquerschnitt und Zugentlastung.

## TX und RX

Für UART wird oft Kreuzverdrahtung benötigt:

- `TX` eines Geräts zu `RX` eines anderen;
- `RX` eines Geräts zu `TX` eines anderen;
- gemeinsames `GND`.

Typische Fehler:

- verbunden `TX` zu `TX`;
- verbunden `RX` zu `RX`;
- vergessen `GND`;
- falsche Geschwindigkeit gewählt;
- Logikpegel passen nicht zusammen: 5V und 3.3V.

Wenn UART nicht funktioniert, überprüfen Sie zuerst `TX/RX/GND`, dann Geschwindigkeit und Einstellungen.

## I2C und SPI

Für I2C:

- `SDA` muss zu `SDA` gehen;
- `SCL` muss zu `SCL` gehen;
- benötigen gemeinsames `GND`;
- Gerät-Adresse darf nicht kollidieren;
- Drähte müssen kurz sein.

Für SPI:

- `MOSI`, `MISO`, `SCK`, `CS` müssen zum Pinout passen;
- jedes Gerät hat sein eigenes `CS`;
- benötigen gemeinsames `GND`;
- lange Drähte können Verbindung unterbrechen.

RFID RC522 verwirrt oft Leute: Pin `SDA` auf dem Board könnte `SS/CS` für SPI bedeuten, nicht I2C `SDA`.

## Netz- und Signaldrähte

110–230 V Wechselstrom, Gleichstrom-Stromlast und schwache Signale dürfen nicht zufällig in einem Bündel liegen.

Probleme:

- Störung;
- Erwärmung;
- Isolierungsschaden;
- Risiko Netzteil zu berühren;
- schwierige Diagnostik;
- Benutzer-Gefahr.

Netzteil muss physisch getrennt sein. Niedervoltige Sensoren, UART/I2C/SPI und Thermistor-Drähte werden besser separat von Heizer-Stromdrähten verlegt.

## Freiliegende Litzen

Ein freiliegender Draht außerhalb eines Anschlusses ist schlecht.

Es kann:

- benachbarten Anschluss berühren;
- Gehäuse kurzschließen;
- unter den Deckel kommen;
- den Lüfter treffen;
- Gefahr während der Wartung schaffen.

Nach dem Einklemmen im Anschluss sollten keine langen bloßen Litzen herausstehen.

## Was überprüfen

Mini-Checkliste:

1. Stromversorgungs-Polarität.
2. Gemeinsames `GND`.
3. Pinout-Übereinstimmung.
4. Anschluss-Qualität.
5. Keine Isolierung angeklemmt statt Leiter.
6. Keine freiliegenden Litzen.
7. Drähte nicht straff.
8. Deckel quetscht Kabel nicht.
9. Strom- und Signaldrähte getrennt.
10. Stecker für Strom bewertet.
11. Gerät ändert Verhalten nicht wenn Draht bewegt wird.

## Was nicht zu tun

Sie können nicht:

- Drähte unter Stromversorgung ändern;
- Netzteil auf Arbeitstisch halten;
- Dupont für Heizer nutzen;
- geflochtenen Draht klemmen so dass manche Litzen herausstehen;
- Stromdrähte ohne richtiger Verbindung verdrehen;
- heiße Anschluss ignorieren;
- „manchmal funktioniert“ als normal ansehen.

## Wichtige Punkte

- Wenn Gerät auf Drahtbewegung reagiert, ist dies ein Verdrahtungsproblem.
- Polarität wird mit Multimeter überprüft, nicht nach Farbe.
- Gemeinsames `GND` wird für die meisten externen Module mit separater Stromversorgung benötigt.
- Dupont ist für Steckbretter und Signale geeignet, aber nicht für Stromlast.
- Netz- und Niedervoltkdrähte müssen getrennt sein.
- Heiße Anschluss ist Grund zu stoppen, nicht den Test fortzusetzen.

## Referenzen

- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - grundlegende Überprüfung von Verbindungen, Kontinuität, Neustart und Erwärmung.
- [SparkFun: Serial Communication](https://learn.sparkfun.com/tutorials/serial-communication) - UART, TX/RX und serielle Kommunikation.
- [SparkFun: I2C](https://learn.sparkfun.com/tutorials/i2c) - `SDA`, `SCL` Leitungen, Adressen und I2C typische Fehler.
- [SparkFun: Serial Peripheral Interface](https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi) - SPI Leitungen, `MOSI`, `MISO`, `SCK`, `SS/CS`.
- [FRC Design: Design for 3D Printing](https://www.frcdesign.org/design-handbook/structure/design-for-3d-printing/) - praktische Hinweise auf Elektronik-Gehäuse: Drähte, Belüftung, Portanbindung und Komponenten-Service-Entfernung.
