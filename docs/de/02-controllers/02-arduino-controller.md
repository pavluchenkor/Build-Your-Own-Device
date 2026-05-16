# Arduino Controller

Arduino ist nicht ein bestimmter Mikrocontroller, sondern ein Ökosystem aus Boards, Bibliotheken, Beispielen und Entwicklungsumgebung. Wenn ein Einsteiger „Arduino" sagt, meint er meist Arduino Uno, Nano oder ein kompatibles Board auf Basis des ATmega328P.

Für die Ausbildung ist Arduino nach wie vor sehr nützlich: GPIO, Tasten, LEDs, PWM, Analogeingabe, I2C, SPI und einfache Sensoren lassen sich leicht verstehen. Für ein neues Gerät rund um einen 3D-Drucker ist Arduino Uno/Nano jedoch nicht immer die beste Wahl.

## Warum Arduino beliebt ist

Stärken von Arduino:

- viele Lernmaterialien;
- einfache Arduino IDE;
- viele fertige Bibliotheken;
- verständliche Beispiele wie Blink;
- bequem zum schnellen Testen eines Sensors auf dem Tisch;
- kompatible Module leicht zu finden;
- alte Boards sind gut dokumentiert.

Wenn das Ziel ist, die Grundlagen von Mikrocontrollern zu verstehen, ist Arduino gut. Es senkt die Einstiegshürde und ermöglicht schnelle Ergebnisse.

## Arduino als Lernboard

Arduino eignet sich für:

- Testen eines Tasters, Endschalters oder Sensors;
- einfachen Thermistortest über einen Spannungsteiler;
- Testen von I2C OLED;
- Testen eines SPI RFID-Moduls;
- Erzeugen von PWM für einen kleinen Test;
- Lesen einer Analogspannung;
- schnelle Experimente auf einem Steckbrett.

In diesem Modus ist Arduino ein ausgezeichnetes Laborwerkzeug. Das Endgerät muss nicht darauf aufgebaut werden: Man kann zunächst die Schaltung und den Sensor verstehen und die Lösung dann auf ESP32, RP2040, STM32 oder ein Druckerboard übertragen.

## Uno und Nano im Überblick

Klassische Arduino Uno und Nano basieren in der Regel auf dem ATmega328P.

Typische Eigenschaften:

- `5V`-Logik;
- 16 MHz Takt;
- 32 KB Flash-Speicher;
- 2 KB SRAM;
- 14 digitale Pins;
- 6 PWM-Pins bei Uno/Nano-Klasse;
- 6 Analogeingänge bei Uno, 8 bei Nano;
- USB zum Flashen und zur Stromversorgung des Boards.

Das reicht für Lern-Sketches und einfache eigenständige Aufgaben, aber nicht für komplexe Logik, Netzwerk, Webinterface, große Bibliotheken und komfortable Integration mit modernen Systemen.

## Original, Klon und Arduino-kompatibel

Man muss unterscheiden:

- originale Arduino-Boards;
- günstige Uno/Nano-Klone;
- Arduino-kompatible Boards mit anderen Mikrocontrollern;
- moderne Arduino-Boards mit Wi-Fi, USB-C, Arm-Chips und anderer Logik.

Ein Nano-Klon für wenige Euro kann für Experimente geeignet sein, aber Qualität von USB-UART, Regler, Lötstellen und Bootloader kann variieren. Manchmal muss man für einen Nano-Klon in der Arduino IDE einen alten Bootloader oder einen anderen Prozessor auswählen.

Wenn das Gerät lange ohne Aufsicht betrieben werden soll, sind Boardqualität, Regler, Steckverbinder und Dokumentation wichtiger als der niedrigste Preis.

## 5V-Logik

Alte Arduino Uno/Nano verwenden `5V`-Logik.

Das ist bei einigen alten Modulen praktisch, aber gefährlich für `3.3V`-Geräte:

- ESP32 verträgt in der Regel keine `5V` an GPIO;
- viele OLED-, RFID-, Sensor- und Funkmodule sind für `3.3V` ausgelegt;
- I2C-Pull-ups auf `5V` können ein `3.3V`-Gerät beschädigen;
- manche Moduleingänge sind `5V`-kompatibel, aber das muss in der Dokumentation geprüft werden.

Wenn Arduino mit einem `3.3V`-Modul verbunden wird, benötigt man einen Pegelwandler oder eine Schaltung, bei der die Pegel bekanntermaßen kompatibel sind.

## GPIO versorgt keine Lasten

Ein Arduino-Pin kann eine LED über einen Widerstand ansteuern oder ein Steuersignal liefern. Er sollte keinen Lüfter, Heizung, Servo, Relais oder LED-Streifen direkt versorgen.

Typische Schaltung:

![Arduino Uno Rev3 mit ATmega328P-Mikrocontroller](../../../img/02-controllers/02-arduino-uno-rev3.jpg)

*Quelle: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Arduino_Uno_Rev3_with_Atmega328P.jpg), HonCode, CC0 Public Domain*

Für Lasten werden benötigt:

- MOSFET oder Treiber für DC-Lüfter, LED-Streifen oder DC-Heizung;
- Transistortreiber und Schutzdiode für die Relaisspule;
- SSR oder Relais für AC-Netzlast;
- separate Stromversorgung für Servo;
- gemeinsame GND, wo die Niederspannungsschaltung es erfordert.

GPIO ist ein Befehl, kein Leistungsausgang.

## PWM und analogWrite

In Arduino bedeutet `analogWrite()` bei Uno/Nano in der Regel PWM, kein echter Analogausgang. Das Board schaltet den Pin schnell ein und aus und ändert das Tastverhältnis des Signals.

Das eignet sich für:

- LED-Helligkeit;
- Steuereingang für einen Treiber;
- einfaches PWM für einen Lüfter oder ein MOSFET-Modul;
- Lernexperimente.

Es gibt jedoch Einschränkungen:

- PWM ist nicht an allen Pins verfügbar;
- PWM-Frequenz ist fest oder ändert sich auf nicht offensichtliche Weise;
- `analogWrite()` und `analogRead()` sind verschiedene Dinge;
- ein 4-poliger PC-Lüfter kann eine andere Frequenz und einen korrekten Open-Collector/Open-Drain-Ansatz erfordern;
- Heizungen und SSRs können nicht einfach beliebiges schnelles PWM verwenden, ohne den Leistungsabschnitt zu verstehen.

## Analogeingänge

Arduino Uno/Nano eignet sich für einfache Analogmessungen:

- Potentiometer;
- Thermistor über Spannungsteiler;
- Lichtsensor;
- einfacher Spannungssensor über Spannungsteiler.

Ein Analogeingang darf jedoch keine Spannung über seinem sicheren Bereich sehen. Bei Uno/Nano ist das in der Regel der Bereich relativ zur `5V`-Versorgung oder dem gewählten `AREF`. Bei höheren Spannungen werden Teiler und Schutz benötigt.

Für genaue Temperaturmessungen braucht man nicht nur `analogRead()`, sondern auch:

- korrekte Spannungsteilerschaltung;
- Widerstandswert;
- Thermistortabelle oder Beta-Parameter;
- stabile Versorgung/Referenzspannung;
- Rauschfilterung;
- mechanischen Sensorkontakt mit dem Objekt.

## Arduino und Klipper

Einige alte AVR-Boards finden sich historisch bedingt in der Nähe von 3D-Druckern, aber für ein neues Gerät rund um Klipper ist es besser, nicht mit Uno/Nano zu beginnen.

Gründe:

- begrenzter Speicher;
- schwache Leistung;
- 5V-Logik kann mit modernen `3.3V`-Modulen kollidieren;
- kein Netzwerk ohne zusätzliche Module;
- kein praktischer Weg für einen neuen Klipper-MCU.

Wenn ein zusätzlicher MCU für Klipper benötigt wird, ist es in der Regel praktischer, RP2040, STM32 oder ein fertiges 3D-Druckerboard zu verwenden. Arduino kann für Ausbildung, Steckbrettaufbau und das Testen einzelner Sensoren behalten werden.

## Wann Arduino noch geeignet ist

Arduino ist geeignet, wenn:

- eine Idee schnell getestet werden soll;
- erklärt werden soll, wie etwas funktioniert;
- das Gerät sehr einfach ist und kein Netzwerk benötigt;
- ein funktionierender Sketch vorhanden ist;
- Verständlichkeit wichtiger ist als Kompaktheit und Leistung;
- es sich um einen Lehraufbau handelt, nicht um fertige Leistungselektronik.

Arduino ist keine gute Wahl, wenn:

- Wi-Fi out of the box benötigt wird;
- eine enge Integration mit Klipper erforderlich ist;
- viel Speicher benötigt wird;
- viele moderne `3.3V`-Sensoren benötigt werden;
- das Gerät kompakt, langlebig und industriell sauber sein muss;
- ein Leistungsabschnitt mit Heizung vorhanden ist, bei dem unabhängige Schutzmaßnahmen wichtig sind.

## Was vor dem Kauf zu prüfen ist

Vor dem Kauf eines Arduino-kompatiblen Boards prüfen:

- ob es ein Original, ein Klon oder ein kompatibles Board ist;
- welcher Mikrocontroller verbaut ist;
- `5V`- oder `3.3V`-Logik;
- welcher USB-UART-Chip verwendet wird;
- ob es einen Treiber für den eigenen Computer gibt;
- welcher Bootloader benötigt wird;
- wie viel Flash und SRAM vorhanden ist;
- wie viele PWM- und Analogeingänge vorhanden sind;
- ob ein Schaltplan und ein Pinout vorhanden sind;
- Qualität von Spannungsregler und Steckverbindern;
- ob das Board für die endgültige Aufgabe geeignet ist.

## Häufige Fehler

- annehmen, Arduino sei ein bestimmtes Board;
- `5V` Arduino direkt mit `3.3V`-Modul verbinden;
- eine Last von GPIO versorgen;
- ein Servo vom `5V`-Pin versorgen und Resets erhalten;
- `analogWrite()` als echten Analogausgang verwenden;
- falschen Bootloader für einen Nano-Klon auswählen;
- keinen Treiber für den USB-UART installieren;
- versuchen, ohne triftigen Grund ein modernes vernetztes Gerät auf Uno aufzubauen;
- einen Lernsteckbrettaufbau in ein geschlossenes Leistungsgerät übertragen, ohne Stromversorgung, Verkabelung und Schutz zu überarbeiten.

## Wichtigste Punkte

Arduino ist ein gutes Lern-Ökosystem und ein praktisches Werkzeug für schnelle Tests. Es eignet sich hervorragend zum Verständnis von GPIO, PWM, ADC und Sensoren.

Aber klassische Uno/Nano sind alte `5V`-Boards mit begrenztem Speicher und ohne Netzwerk. Für ein neues Gerät rund um einen 3D-Drucker sind ESP32, RP2040, STM32 oder ein fertiges Druckerboard oft praktischer, während Arduino als Lern- und Diagnosewerkzeug erhalten bleibt.

## Weiterführende Materialien

- [Arduino Docs: UNO R3](https://docs.arduino.cc/hardware/uno-rev3) — offizielle Uno R3-Spezifikationen: ATmega328P, `5V`, Pins, PWM, Analogeingänge und Board-Ressourcen.
- [Arduino Store: UNO Rev3 Tech Specs](https://store.arduino.cc/collections/arduino/products/arduino-uno-rev3) — Tabelle mit Spannung, GPIO-Strom, Speicher, Frequenz und Board-Abmessungen.
- [Arduino Store: Arduino Nano](https://store-usa.arduino.cc/products/arduino-nano) — Nano-Spezifikationen, Stromversorgung, Speicher, digitale und analoge Pins.
- [Arduino Help Center: Select the right processor for Arduino Nano](https://support.arduino.cc/hc/en-us/articles/4401874304274-Select-the-right-processor-for-Arduino-Nano) — warum Nano und Nano-Klone unterschiedliche Bootloader haben können.
- [Arduino Language Reference](https://docs.arduino.cc/language-reference/) — offizielle Referenz für `pinMode`, `digitalWrite`, `analogRead`, `analogWrite`, PWM und Grundfunktionen.
- [Arduino Help Center: Use PWM output with Arduino](https://support.arduino.cc/hc/en-us/articles/9350537961500-Use-PWM-output-with-Arduino) — Liste der PWM-Pins für gängige Boards und Einschränkungen von `analogWrite()`.
