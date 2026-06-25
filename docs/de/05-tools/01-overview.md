# Werkzeuge

Dieser Abschnitt handelt nicht von Werkzeugsammlung.

Es geht um den minimalen Satz, der Ihnen hilft, ein Gerät sicher zu montieren, Verbindungen zu überprüfen und einfache Fehler zu finden, ohne zu raten.

In selbstgebauten Geräten rund um iDryer und 3D-Drucker sind Werkzeuge für praktische Aufgaben nötig:

- überprüfen, ob 24V auf der Stromversorgung vorhanden ist;
- verstehen, ob Plus und Minus vertauscht sind;
- Kontinuität auf einem Draht überprüfen;
- einen Thermistor testen;
- sehen, ob UART-Signal ankommt;
- einen Controller flashen;
- einen richtigen Stecker machen;
- Stromversorgungssag finden;
- verstehen, warum ein Lüfter oder Heizer nicht einschaltet.

## Minimalsatz

Für die meisten einfachen Bau sind nützlich:

- Multimeter;
- USB-UART oder USB-TTL-Adapter;
- Lötkolben;
- Crimpwerkzeug;
- Drahtzange und -abisolierer;
- Schrumpfschlauch;
- ordentliche Terminals und Stecker;
- ST-Link, wenn Sie mit STM32 arbeiten;
- Oszilloskop oder mindestens Multimeter mit Frequenzzähler für komplexere Diagnose.

Nicht alles muss sofort gekauft werden. Aber ein Multimeter und ordentliche Drahtwerkzeuge zahlen sich normalerweise schnell aus.

## Werkzeuge ersetzen Verständnis nicht

Ein Multimeter macht den Netzbereich nicht sicher.

Ein Lötkolben behebt keine schlechte Schaltung.

Ein Oszilloskop ist nicht nötig, wenn Plus und Minus vertauscht sind.

Also die Reihenfolge ist:

1. Verstehen, was verbunden sein sollte.
2. Stromversorgung überprüfen.
3. Verdrahtung überprüfen.
4. Sensoren und Signale überprüfen.
5. Nur dann komplexe Probleme suchen.

## Was wird in diesem Abschnitt sein?

- `02-multimeter.md` - Messung von DC-Spannung, Kontinuität, Widerstand, Sicherungen und warum Strommessung gefährlicher ist.
- `03-usb-ttl-adapter.md` - USB-UART-Adapter, TX/RX/GND, 3,3V/5V-Logikpegel, Flashen und Protokolle.
- `04-soldering.md` - Drähte, Pads, Module löten, kalte Lötstellen, Schrumpfschlauch und Zugentlastung.
- `05-crimping-connectors.md` - Dupont, JST, Ferrules, Faston, Terminals und Crimp-Qualitätsprüfungen.
- `06-st-link.md` - ST-Link, STM32, SWD, Platten-Recovery nach fehlgeschlagenem Flashen.
- `07-oscilloscope.md` - PWM, UART, Stromversorgungssag, Rauschen und kritische Sicherheitswarnung über Netzspannung.

## Was es wert ist, richtig zu kaufen

Es gibt Dinge, auf denen Sie nicht sparen sollten:

- ein Multimeter mit ordentlichen Sonden und Kontinuitätsmodus;
- ein Lötkolben mit Temperaturregelung;
- hochwertiges Lot und Flussmittel;
- Crimpwerkzeug für spezifische Terminals;
- Stecker und Terminals, die für nötige Strom bewertet sind;
- Schrumpfschlauch;
- Drähte von richtiger Dicke.

Schlechtes Crimpen oder schwache Terminals können mehr Probleme verursachen als schlechte Firmware.

## Was Sie nicht tun können

Sie können nicht:

- Widerstand in geschalteter Schaltung messen;
- Strom gleich wie Spannung messen;
- Multimeter in 110-230V AC ohne Verständnis für Sicherheit pieksen;
- Netzbereich "irgendwie" löten;
- Dupont für Heizer verwenden;
- Drähte wechseln, wenn Strom ein ist;
- offene Netzteile auf dem Tisch halten;
- denken, dass wenn ein Draht "hält", der Kontakt gut ist.

## Das Wesentliche

- Multimeter ist das erste Diagnosetool.
- USB-UART wird für Protokolle, Flashen und Kommunikation mit UART-Geräten benötigt.
- Löten und Crimpen sind unterschiedliche Aufgaben, und für Stecker ist Crimpen oft besser.
- ST-Link wird benötigt, wenn Sie mit STM32 und SWD arbeiten.
- Oszilloskop wird nicht von allen benötigt, zeigt aber schnell Signale, Sag und Rauschen.
- Für Netzbereich zählen Kontaktqualität, Drahtdicke und Sicherheit mehr als Montageaussehen.

## Referenzmaterialien

- [SparkFun: How to Use a Multimeter](https://learn.sparkfun.com/tutorials/how-to-use-a-multimeter/all) - Multimeter-Grundlagen: Spannung, Strom, Widerstand, Kontinuität.
- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - Hardware-Prüfungen für Strom, Verbindungen und Wärme.
- [SparkFun: Serial Communication](https://learn.sparkfun.com/tutorials/serial-communication) - UART und grundlegende serielle Kommunikationslogik.
- [Adafruit: Guide to Excellent Soldering](https://learn.adafruit.com/adafruit-guide-excellent-soldering) - praktischer Lötleitfaden und Verbindungsqualität.
- [STMicroelectronics: ST-LINK/V2 User Manual](https://www.st.com/resource/en/user_manual/um1075-stlinkv2-incircuit-debuggerprogrammer-for-stm8-and-stm32-stmicroelectronics.pdf) - offizielle ST-Link-Dokumentation und SWD/SWIM.
