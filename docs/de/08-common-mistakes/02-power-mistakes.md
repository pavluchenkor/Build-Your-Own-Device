# Stromversorgungsfehler

Stromversorgung ist das erste was überprüft wird wenn sich das Gerät seltsam verhält.

Eine schwache Stromversorgung, dünner Draht oder schlechter Anschluss können wie ein Firmware-, Wi-Fi-, Sensor- oder Controllerfehler aussehen.

## Symptome

Typische Zeichen von Stromversorgungsproblemen:

- Controller startet neu;
- Bildschirm flackert;
- Wi-Fi auf ESP32 fällt ab;
- Lüfter startet und stoppt;
- Servo ruckt;
- Heizer heizt schwach;
- USB verschwindet wenn Last eingeschaltet wird;
- MOSFET, Anschluss oder Draht wird heiß;
- Sensoren zeigen instabile Werte;
- Gerät funktioniert ohne Last aber bricht wenn Heizer oder Motor verbunden wird.

Wenn ein Symptom genau dann erscheint wenn die Last eingeschaltet wird, fast immer müssen Stromversorgung und Verdrahtung überprüft werden.

## Stromversorgung ohne Spielraum

Sie können eine Stromversorgung nicht genau zur Last-Stromversorgung wählen.

Wenn die Last `100W` verbraucht, wird eine `100W` Stromversorgung an ihrem Limit arbeiten. Sie kann überhitzen, Spannung durchhängen und schlecht mit Einschaltstromstößen umgehen.

Praktische Regel für diesen Abschnitt:

**minimaler Stromspielraum ist 50%, sofern die Dokumentation einer bestimmten Komponente nicht mehr erfordert.**

Beispiel:

```text
Heizer: 24V 120W
Strom: 120W / 24V = 5A
minimaler 50% Spielraum: 7.5A
```

Außerdem ist die Stromversorgung mindestens `24V 7.5A` zu wählen, und in der Praxis oft größer, wenn es Lüfter, Controller, Beleuchtung und andere Lasten gibt.

## Gesamtstrom nicht berechnet

Sie müssen nicht eine Komponente sondern das ganze Gerät berechnen.

Zum Beispiel:

- Heizer;
- Lüfter;
- Servo;
- LED-Streifen;
- Controller;
- Display;
- Sensoren;
- DC-DC-Wandler.

Ströme addieren sich. Einschaltstromstöße und kurze Spitzen müssen auch berücksichtigt werden.

Ein Servo oder Lüfter kann kurzzeitig mehr als im Normalbetrieb zeichnen. Wenn der Spielraum klein ist wird genau dieser Moment den Controller zum Neustart verursachen.

## Verwechselt 12V und 24V

Der einfachste und gefährlichste Fehler:

- 12V Lüfter angeschlossen auf 24V;
- 5V Modul angeschlossen auf 12V;
- 24V Heizer erwartet normal von 12V zu arbeiten;
- 3.3V Modul von 5V ohne Überprüfung betrieben.

Bevor Sie verbinden überprüfen Sie:

- Last-Etikett;
- Stromversorgungs-Etikett;
- Spannung mit Multimeter;
- Verbindungsdiagramm;
- Controller und Modul-Spannungsetikett.

Verlassen Sie sich nicht nur auf Drahtfarbe oder ähnlicher Steckertyp.

## Spannungsabfall auf Drähten

Draht hat Widerstand.

Je länger der Draht und je größer der Strom, desto größer der Spannungsabfall und die Erwärmung.

Symptome:

- Stromversorgung gibt 24V, aber Last bekommt weniger;
- Heizer heizt schwächer als erwartet;
- Lüfter startet schlecht;
- Servo ruckt;
- Draht merklich warm;
- Anschluss wird heiß.

Überprüfen Sie Spannung nicht nur bei Stromversorgungsausgang sondern auch bei der Last während des Betriebs.

Wenn Spannung unter Last erheblich sinkt, könnte das Problem bei Draht, Anschluss, Stecker, Stromversorgung oder zu großer Last liegen.

## Kein gemeinsames Erdung

Wenn ein Controller ein externes Modul oder eine Last steuert, wird oft gemeinsames Erdung benötigt.

Zum Beispiel:

- Controller steuert ein MOSFET-Modul;
- Controller stellt PWM auf einen 4-Pin-Lüfter;
- Controller steuert ein Servo mit separater Stromversorgung;
- HX711, RFID oder anderes Modul wird separat betrieben.

Ohne gemeinsames `GND` könnte das Signal nicht das richtige Niveau haben. Gerät könnte nicht funktionieren oder zufällig funktionieren.

Gemeinsames Erdung bedeutet nicht dass die gesamte Last durch den Controller betrieben werden muss. Es ist nur die gemeinsame Referenzstufe für das Signal.

## Controller von lärmiger Leitung betrieben

Motoren, Lüfter, Servos, Heizer und LED-Streifen können Spannungsabfälle und Lärmerzeugen.

Wenn der Controller von der gleichen Leitung ohne richtigen DC-DC, Filterung und Spielraum betrieben wird, kann er Neustart.

Häufige Lösungen:

- separater richtiger DC-DC für Controller;
- kurze Controller-Stromdrähte;
- gemeinsames `GND` an klarem Punkt;
- Kondensator in der Nähe der Last, wenn passend;
- Trennung von Strom- und Logik-Verdrahtung;
- richtige Stromversorgung mit Spielraum.

## Was mit Multimeter überprüfen

Mindestens:

1. Stromversorgungsspannung ohne Last.
2. Stromversorgungsspannung unter Last.
3. Spannung an Last-Anschlüssen unter Last.
4. Polarität.
5. Anwesenheit gemeinsamen Erdung.
6. Draht- und Anschlusswärmung nach kurzem Test.

Wenn das Gerät nur ohne Last funktioniert, messen Sie es unter Last. Spannung ohne Last könnte normal aussehen.

## Was nicht zu tun

Sie können nicht:

- Stromversorgung "bis zum Limit" nutzen;
- Sicherungsetikett erhöhen weil es fliegt;
- dünne Dupont-Drähte für Stromlast nutzen;
- Stromdrähte ohne richtigen Anschluss verdrehen;
- Heizer durch schwachen Stecker betreiben;
- Last direkt auf GPIO verbinden;
- Gerät wiederholt einschalten wenn Draht oder Anschluss heiß wird.

Wenn etwas heizt, zuerst Stromversorgung ausschalten und Ursache finden.

## Typische Fehler

- Laststrom nicht berechnet;
- Stromversorgung ohne Spielraum gewählt;
- Einschaltstromspitze von Lüfter oder Servo vergessen;
- 12V und 24V verwechselt;
- 5V Controller von instabiler Leitung;
- kein gemeinsames `GND`;
- Draht zu dünn;
- Draht zu lang für Strom;
- Anschluss nicht gut angezogen;
- Load funktioniert aber Spannung sinkt erheblich.

## Wichtige Punkte

- Stromversorgung wird zuerst überprüft.
- Berechnen Sie Strom für alle Lasten, nicht nur ein Teil.
- Mindestens 50% Stromspielraum benötigt.
- Spannung muss unter Last gemessen werden.
- Gemeinsames `GND` ist oft zwingend erforderlich für die Steuerung von externen Modulen.
- Dünner oder langer Draht kann Spannungsabfall und Erwärmung verursachen.

## Referenzen

- [SparkFun: How to Power a Project](https://learn.sparkfun.com/tutorials/how-to-power-a-project/voltagecurrent-considerations) - grundlegende Überlegungen zu Spannung, Strom und Stromversorgung für Microcontroller-Projekte.
- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - Überprüfung von Stromversorgung, Verbindungen und Erwärmung bei der Fehlerbehebung.
- [ProdataKey: How does wire gauge affect line loss?](https://support.pdk.io/hc/en-us/articles/360047588514-How-does-wire-gauge-affect-line-loss?) - warum Länge, Querschnitt und Strom Spannungsabfall und Verluste beeinflussen.
- [WiringCalcs: Voltage Drop Explained](https://wiringcalcs.com/guides/voltage-drop-explained-guide/) - praktische Erklärung von Spannungsabfall, Drahtwiderstand und Stromeffekt.
- [SparkFun Qwiic Power Meter guide](https://docs.sparkfun.com/SparkFun_Qwiic_Power_Meter_ACS37800/hardware_assembly/) - Beispiel von gemeinsamen `GND` beim Messen/Steuern externe Last.
