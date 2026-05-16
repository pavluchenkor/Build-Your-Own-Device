# Oszilloskop

Ein Oszilloskop zeigt, wie sich ein Signal über die Zeit verändert.

Ein Multimeter kann "etwa 3.3V" zeigen oder "es gibt Frequenz". Ein Oszilloskop zeigt Signalform: Pulse, Kanten, Sag, Rauschen, Bounce, UART-Pakete, PWM.

![Bildschirm eines digitalen Oszilloskops](../../../img/04-tools/07-digital-oscilloscope.jpg)

*Quelle: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Digital_oscilloscope.jpg), premek.v, Public Domain*

Ein PWM Signal auf dem Oszilloskop-Bildschirm sieht so aus:

![Animation von PWM: Tastverhältnis-Änderung und Signal-Wellenform](../../../img/04-tools/07-pwm-signal-waveform.gif)

*Quelle: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Pwm.gif), Mik81, CC0 Public Domain*

Sie benötigen eines nicht für jeden einfachen Bau. Aber wenn sich ein Gerät instabil verhält, kann ein Oszilloskop in Minuten offenbaren, was ein Multimeter nicht sehen kann.

## Was Sie sehen können

In iDryer-ähnlichen Geräten ist ein Oszilloskop nützlich um zu zeigen:

- Lüfter PWM;
- MOSFET Modul PWM;
- UART `TX/RX`;
- 5V oder 3.3V Sag bei Servo-Start;
- Stromversorgung Rauschen;
- Knopf Bounce;
- tachometrisches Lüfter Signal;
- kurze Glitches, die ein Multimeter mittelt.

Ein Oszilloskop antwortet nicht nur "gibt es Spannung" sondern "was passiert mit dem Signal über die Zeit".

## Die wichtigste Warnung

Die meisten Tischoszilloskope haben die Sonden-Erde mit der Netzschutzerde verbunden.

Dies bedeutet: der Erdungsclip der Sonde ist nicht "nur ein anderer Draht".

Wenn Sie den Erdungsclip an einem Punkt befestigen, der nicht `GND` der Niederspannungsschaltung ist, können Sie einen Kurzschluss durch das Oszilloskop erzeugen.

Es ist besonders gefährlich, in den Netzbereich 110-230V AC, SSR, Stromversorgung oder Hochspannungs-Abschnitte mit einer normalen Sonde zu gehen.

Sie können nicht:

- die Ozilloskop-Erde zum "Schweben" der Messung trennen;
- den Sonden-Grund an einen anderen Spannungspunkt verbinden;
- Netzspannung mit einer normalen Sonde ohne Verständnis der Schaltung messen;
- annehmen, dass die beiden Kanäle völlig unabhängig sind: Kanal-Gründe sind oft verbunden.

Für Schwebe-Messungen, Hochseiten-Messungen und Hochspannungs-Messungen benötigen Sie ordentliche Methoden: Differenz-Sonde, isoliertes Gerät oder einen anderen sicheren Ansatz.

## Wie man eine Sonde anschließt

Für Niederspannungsschaltungen:

1. Sonde mit dem Oszilloskop verbinden.
2. Sonden-Erde mit `GND` des Geräts verbinden.
3. Sonden-Spitze mit dem Signal verbinden.
4. Wählen Sie die korrekte Sonden-Einstellung: `1x` oder `10x`.
5. Stellen Sie sicher, dass das Oszilloskop auf den gleichen Faktor eingestellt ist.

Für die meisten digitalen Signale verwenden Sie `10x`: die Sonde lädt die Schaltung weniger und zeigt normalerweise Signalform besser.

## PWM

PWM ist ein Puls Signal.

Das Oszilloskop zeigt:

- Frequenz;
- Tastverhältnis;
- Logik Hoch-Pegel;
- Logik Tief-Pegel;
- Kanten;
- Jitter;
- Rauschen.

Für einen Lüfter oder MOSFET hilft dies verstehen:

- ob der Pin ein Signal ausgibt;
- ob 3.3V oder 5V Pegel ausreichend ist;
- ob Frequenz der Einstellung entspricht;
- ob Tastverhältnis auf Befehl ändert;
- ob Signal nicht sägt, wenn Last verbunden ist.

## UART

UART auf dem Oszilloskop sieht wie eine Abfolge von Pulsen aus.

Das Oszilloskop hilft sehen:

- ob es Aktivität auf `TX` gibt;
- ob Logik-Pegel nicht vertauscht sind;
- was das Idle Pegel ist;
- ob es starkes Rauschen gibt;
- ob Baud-Rate ungefähr passt.

Zum Dekodieren von Text ist ein Logik-Analyzer oder USB-UART Adapter bequemer. Aber ein Oszilloskop zeigt schnell, ob das Signal physikalisch lebendig ist.

## Stromversorgung Sag

Ein Multimeter sieht möglicherweise keinen kurzen Sag.

Zum Beispiel könnte eine 5V Leitung beim Servo-Start um wenige Millisekunden sinken. Das Multimeter zeigt fast normal 5V, aber der Controller ist bereits neu gestartet.

Ein Oszilloskop ermöglicht Ihnen zu sehen:

- wie viel Spannung sinkt;
- wie lange der Sag dauert;
- ob es Spitzen gibt;
- ob ein Kondensator hilft;
- ob die Situation mit einer anderen Stromversorgung oder Drähten sich ändert.

Dies ist besonders nützlich für ESP32, Servos, Lüfter und DC-DC.

## Rauschen und Interferenz

Rauschen auf Power oder Signal Leitungen kann Sensoren und Kommunikation brechen.

Ein Oszilloskop hilft sehen:

- DC-DC Welligkeit;
- Motor Spitzen;
- Rauschen neben dem Heizer;
- Knopf Bounce;
- Interferenz auf einem langen Draht.

Aber verstehen Sie die Grenzen: schlechte Sonden-Erde-Verbindung kann Rauschen der Anzeige selbst hinzufügen. Eine kurze Sonden-Erde-Feder oder kurzer Erde-Draht gibt oft ein ehrlicheres Bild als ein langer Clip.

## Multimeter mit Frequenz-Messung

Manchmal wird ein Oszilloskop für erste Überprüfungen nicht benötigt.

Einige Multimeter können Signal-Frequenz messen. In den Spezifikationen könnte dies `Hz`, `Frequenz` oder `Frequenz-Zähler` genannt werden.

Dies ist nützlich, wenn Sie schnell verstehen müssen:

- ob ein PWM Signal überhaupt existiert;
- ob sich Frequenz mit Anpassung ändert;
- ob Controller Ausgang funktioniert;
- ob es Aktivität auf einer einfachen digitalen Leitung gibt.

Zum Beispiel, wenn ein Controller PWM zu einem Lüfter oder MOSFET Modul ausgeben sollte, ein Frequenz-messendes Multimeter kann zeigen, dass das Signal existiert und seine Frequenz ungefähr dem erwarteten Wert entspricht.

Aber ein Multimeter zeigt nicht Signalform. Es wird nicht zeigen:

- Logik Hoch-Pegel;
- Puls Breite;
- PWM Tastverhältnis;
- Signal Kanten;
- kurze Dips;
- Rauschen und Interferenz;
- Leitungs-Verzerrung.

Also ein Frequenz-messendes Multimeter ist ein gutes Werkzeug für schnelle Überprüfungen, aber nicht ein vollständiger Oszilloskop-Ersatz.

## Was vor der Messung zu überprüfen ist

Vor dem Anschließen einer Sonde:

1. Was ist `GND` in der Schaltung?
2. Ist dieser Punkt mit Netzschutzerde verbunden?
3. Gibt es keine Netzspannung?
4. Ist die Sonde für die Spannung bewertet?
5. Ist `10x` ausgewählt, falls nötig?
6. Sind die Sonde und der Kanal auf die gleiche Weise eingestellt?
7. Sind Kanal-Gründe nicht verschiedene Schaltungs-Punkte verbunden?
8. Können Sie zuerst das Signal auf der Niederspannungsseite überprüfen?

Wenn Sie Zweifel über 110-230V AC haben, verbinden Sie das Oszilloskop nicht.

## Häufige Fehler

- Erdungsclip an einem Spannungspunkt, nicht `GND` befestigt;
- versucht die Ozilloskop-Erde vom Netz zu "trennen";
- Netzspannung mit einer normalen Sonde ohne Differenz gemessen;
- vergessen, dass Kanal-Gründe verbunden sind;
- Sonde auf `10x`, Ozilloskop auf `1x` eingestellt;
- lange Sonden-Erde verwendet und extra Rauschen gesehen;
- nur mit Multimeter geschaut und einen kurzen Sag verpasst;
- ein UART Problem ist Software wenn es keine physikalische Signal-Leitung gibt.

## Das Wesentliche

- Ein Oszilloskop zeigt Signalform über die Zeit.
- Es ist nützlich für PWM, UART, Stromversorgung Sag, Rauschen und kurze Glitches.
- Ein normales Tisch-Oszilloskop Grund ist mit Netzschutzerde verbunden.
- Sie können den Sonden-Grund nicht an einem beliebigen Schaltungs-Punkt verbinden.
- Für Schwebe und Hochspannungs-Messungen werden spezielle sichere Methoden benötigt.
- Ein Frequenz-messendes Multimeter ist nützlich, aber kein Oszilloskop-Ersatz.

## Referenzmaterialien

- [SparkFun: How to Use an Oscilloscope](https://learn.sparkfun.com/tutorials/how-to-use-an-oscilloscope/introduction) - grundlegende praktische Einführung zu Oszilloskopen, Signalen und Kontrollen.
- [Tektronix: How to Use an Oscilloscope](https://www.tek.com.cn/documents/primer/how-to-use-an-oscilloscope) - Erdung, Einrichtung, Kontrollen und grundlegende Oszilloskop-Verwendung.
- [Tektronix: ABCs of Probes Primer](https://www.tek.com/en/documents/whitepaper/abcs-probes-primer) - Warnungen über Sonden-Erde, Netzerde und Gefahr von Schwebe-Messungen mit normalem Oszilloskop.
- [Tektronix: Floating Oscilloscope Measurements and Operator Protection](https://www.tek.com/en/documents/technical-brief/floating-oscilloscope-measurements-and-operator-protection) - warum das Trennen von Ozilloskop-Netzerde gefährlich ist und welche sicheren Alternativen existieren.
- [Keysight: Floating an oscilloscope](https://docs.keysight.com/kkbopen/how-can-i-float-an-infiniium-or-infiniivision-x-oscilloscope-isolating-it-from-mains-power-607258715.html) - Keysight empfiehlt nicht, das Erden zu umgehen und schlägt Differenz-Sonden vor.
