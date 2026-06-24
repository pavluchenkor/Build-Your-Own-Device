# STM32 Controller

STM32 ist eine große Familie von 32-Bit-Mikrocontrollern von STMicroelectronics, die auf Arm Cortex-M-Kernen basieren. Es ist weder ein einzelnes Board noch ein einzelner Chip: Unter dem Namen STM32 gibt es Dutzende von Serien und Hunderte von Modellen.

In der Welt der 3D-Drucker ist STM32 weit verbreitet. Viele fertige Druckerplatinen, Erweiterungsplatinen, CAN-Boards und Controller verwenden STM32. Für Klipper und Druckerperipherie ist es eine der praktischsten Optionen, wenn man bereit ist, mit einer bestimmten Platine zu arbeiten.

## Wo STM32 nützlich ist

STM32 eignet sich gut für:

- Haupt-3D-Druckerplatine;
- zusätzliche MCU in Klipper;
- Platine zur Steuerung von Lüftern, Sensoren und Ausgängen;
- CAN-Board oder Toolhead-Board;
- ernstere individuelle Platinen;
- Aufgaben, die Timer, PWM, ADC, UART, SPI, I2C, CAN oder USB erfordern;
- Projekte, die ein fertiges industrielles Ökosystem und Dokumentation benötigen.

Wenn RP2040 ein einfacher und klarer Einstieg ist, ist STM32 eine weite Welt von Controllern, in der man einen Chip für nahezu jede Aufgabe auswählen kann. Flexibilität hat jedoch ihren Preis in Form von Komplexität.

## STM32 ist eine Familie

Man kann nicht sagen „Ich habe ein STM32" und aufhören zu wählen. Man muss das genaue Modell kennen.

Beispiele für Serien:

- **STM32F0 / STM32C0 / STM32G0** — Budget- und Massenmarktserie;
- **STM32F1** — alte, aber sehr bekannte Serie, häufig in Blue Pill und alten Platinen zu finden;
- **STM32F4** — leistungsstärkere Serie, beliebt in Controllern;
- **STM32G4** — interessant für Steuerungs-, Timer- und Analogperipherieaufgaben;
- **STM32H7** — leistungsstarke High-End-Controller;
- **STM32L / STM32U** — Serien mit Fokus auf niedrigen Stromverbrauch.

Für einen typischen Nutzer kommt es nicht auf das Marketing der Serie an, sondern auf konkrete Dinge:

- ob es Unterstützung in der benötigten Firmware gibt;
- wie viele GPIO tatsächlich auf der Platine zugänglich sind;
- ob USB, CAN, UART, I2C, SPI vorhanden sind;
- wie viel Flash und RAM vorhanden ist;
- wie man es flasht;
- ob ein ordentliches Pinout und Schaltplan vorhanden sind.

## Die Platine ist wichtiger als der Chipname

Derselbe STM32 kann auf sehr unterschiedlichen Platinen verbaut sein.

Häufige Varianten:

- **Blue Pill / Black Pill** — günstige kleine Platinen, oft mit STM32F103 oder STM32F4-Klasse, aber die Qualität von Klonen variiert;
- **STM32 Nucleo** — offizielle ST-Entwicklungsplatinen mit integriertem ST-LINK;
- **fertige 3D-Druckerplatine** — hat bereits Treiber, Anschlüsse, MOSFET-Ausgänge, Thermistoreingänge, Sicherungen und Stromanschlüsse;
- **Toolhead/CAN-Board** — spezialisierte Platine für einen Druckerkopf oder ein Remote-Modul;
- **individuelle Platine** — erfordert vollständiges Design für Stromversorgung, USB, SWD, Schutz und Routing.

Für ein erstes praktisches Projekt ist es meist einfacher, eine fertige Platine mit Dokumentation zu besorgen, als ein blankes STM32 oder einen zufälligen Klon ohne Schaltplan.

## STM32 und Klipper

STM32 ist einer der Hauptwege für eine Klipper-MCU.

Typische Architektur:

![Nucleo-Platinen für STM8 und STM32 von STMicroelectronics](../../img/02-controllers/04-stm32-nucleo-boards.jpg)

*Quelle: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Nucleo-board.jpg), Avandalen, CC BY-SA 4.0*

Der Klipper-Host läuft auf einem Linux-Gerät, und die STM32-Platine steuert physisch die Pins: schaltet MOSFET-Ausgänge, liest Thermistoren, steuert Lüfter, empfängt Endstoppsignale und kommuniziert mit dem Host über USB, UART oder CAN.

Für iDryer-ähnliche Peripheriegeräte macht STM32 Sinn, wenn:

- das Gerät Teil der Klipper-Konfiguration sein soll;
- eine fertige Druckerplatine mit Leistungsausgängen benötigt wird;
- CAN benötigt wird;
- ein industriellerer Platinenansatz gewünscht ist;
- bereits eine STM32-Platine und eine bekannte Konfiguration vorhanden sind.

Wenn man schnell ein paar Pins und Sensoren hinzufügen möchte, ist RP2040 oft einfacher. Wenn eine fertige leistungsstarke Platine mit Anschlüssen und Treibern benötigt wird, kann eine STM32-Platine besser sein.

## Flashen: USB, DFU, UART, SWD, ST-LINK

STM32 hat keine einheitliche Flash-Methode für alle Platinen.

Möglichkeiten:

- **USB-Bootloader / DFU** — Flashen über integrierten USB-Bootloader, sofern Platine und Chip dies unterstützen;
- **UART-Bootloader** — Flashen über serielle Pins im richtigen BOOT-Modus;
- **SWD über ST-LINK** — zuverlässige Methode zum Flashen und Debuggen über einen Programmer;
- **integrierter ST-LINK auf Nucleo** — praktisch für die Entwicklung;
- **Bootloader auf Druckerplatine** — manchmal erfolgt das Flashen per SD-Karte, USB oder einem speziellen Bootloader des Herstellers.

Daher muss man vor dem Kauf einer Platine nicht nur nach einem Chip-Datenblatt suchen, sondern nach Anleitungen für diese spezifische Platine. Für Klipper ist es besonders wichtig, die Kommentare in einer fertigen Platinenkonfiguration und die Herstelleranweisungen zu lesen.

## Nucleo, Blue Pill und Druckerplatinen

**STM32 Nucleo**-Platinen sind praktisch zum Lernen und Prototyping. Sie haben in der Regel einen integrierten ST-LINK, Arduino Uno V3-Anschlüsse und ST-Morpho-Pins, die Zugang zu mehr Signalen bieten. Das ist eine gute Option, wenn man STM32 erlernen und ein offizielles Flash-Tool haben möchte.

**Blue Pill / Black Pill** sind wegen Preis und Größe attraktiv, aber Klone haben oft Probleme: falscher Chip, schwacher Regler, schlechtes USB, kein ordentlicher Schaltplan, seltsamer Bootloader. Für Experimente sind sie nützlich, für ein zuverlässiges Gerät — nur nach Überprüfung.

**Fertige 3D-Druckerplatinen** sind für Heizungen, Lüfter und Sensoren oft praktischer, weil die Leistungssektion bereits ausgeführt ist: Es gibt Klemmen, MOSFET-Ausgänge, Thermistoreingänge, Stromversorgung, Sicherungen oder Platz dafür. Aber auch eine fertige Platine erfordert die Überprüfung von Strömen, Anschlüssen, Kühlung und Sicherheit.

## 3,3-V-Logik und GPIO

Die meisten STM32 arbeiten mit `3.3V`-Logik.

Wichtig:

- keine `5V` an Pins anlegen, sofern das Chip-Datenblatt nicht ausdrücklich angibt, dass dieser Pin `5V` verträgt;
- Arduino-Shield-Kompatibilität auf Nucleo bedeutet nicht, dass alle Signale wie bei einem `5V` Arduino Uno sicher sind;
- I2C-Pull-ups sind in der Regel auf `3.3V`;
- GPIO sollte keine Last direkt versorgen;
- Lüfter, LED-Streifen, Heizungen, Relais und Servos werden über Treiber und separate Stromversorgung angeschlossen.

Auch wenn einige STM32-Pins `5V` akzeptieren, ist das keine Erlaubnis, alles anzuschließen. Man muss die Pinout-Tabelle und die elektrischen Eigenschaften für den spezifischen Chip überprüfen.

## Warum STM32 oft für Drucker gewählt wird

STM32 eignet sich gut für 3D-Druckerplatinen, weil es viele nützliche Peripheriegeräte hat:

- Timer und PWM für Lüfter, Heizungen und Signale;
- ADC für Thermistoren und Sensoren;
- UART/SPI für Schrittmotortreiber und Module;
- I2C für Displays und Sensoren;
- USB für die Kommunikation mit dem Host;
- CAN in einigen Serien und Platinen;
- ausreichend Leistung für Echtzeit-MCU-Aufgaben.

Aber der Mikrocontroller selbst macht eine Platine nicht sicher. Heizungen, Leistungs-MOSFETs, SSRs, Sicherungen, Anschlüsse und Thermoschutz bleiben eine separate ingenieurtechnische Aufgabe.

## Was vor dem Kauf zu prüfen ist

Vor dem Kauf einer STM32-Platine prüfen:

- genaues Mikrocontrollermodell;
- ob es Unterstützung in Klipper oder der benötigten Firmware gibt;
- wie viel Flash und RAM vorhanden ist;
- wie die Platine geflasht wird;
- ob USB, CAN, UART oder andere benötigte Schnittstellen vorhanden sind;
- ob ein offizielles Pinout und Schaltplan vorhanden sind;
- welche Pins von LEDs, USB, Oszillator, Boot-Modus oder SWD belegt sind;
- welche Pins 5V-tolerant sind und welche nicht;
- welche Leistungsausgänge auf der Platine vorhanden sind und für welchen Strom sie ausgelegt sind;
- ob Sicherungen, Klemmen und ordentliche Stromversorgung vorhanden sind;
- wie verständlich die Herstellerdokumentation ist.

Wenn eine Platine nur mit einem schönen Foto und ohne Schaltplan verkauft wird, ist das keine gute Grundlage für ein Gerät mit einer Heizung.

## Häufige Fehler

- zu glauben, STM32 sei eine bestimmte Platine;
- einen Blue Pill-Klon zu kaufen und das Verhalten einer offiziellen Platine zu erwarten;
- das genaue Chipmodell nicht zu prüfen;
- nicht zu verstehen, wie die Platine geflasht wird;
- DFU, BOOT0, UART und ST-LINK zu verwechseln;
- ein `5V`-Modul an einen `5V`-intoleranten Pin anzuschließen;
- SWD-Pins als reguläre GPIO zu verwenden und die Fähigkeit zum Flashen/Debuggen zu verlieren;
- zu glauben, GPIO sei ein Leistungsausgang;
- eine Platine ohne Schaltplan für eine Heizung zu wählen;
- die fertige Klipper-Konfiguration vor dem Kauf nicht zu prüfen.

## Wichtigste Punkte

STM32 ist eine leistungsstarke und praktische Mikrocontrollerfamilie, besonders für 3D-Druckerplatinen und Klipper-MCU. Aber man muss nicht „STM32 im Allgemeinen" wählen, sondern eine spezifische Platine mit einem bestimmten Chip, Pinout, Flash-Methode und Dokumentation.

Für einen ersten einfachen Controller ist RP2040 oft einfacher. Für fertige Druckerelektronik, CAN-Boards und ernstere Peripheriegeräte ist STM32 oft die richtige Wahl.

## Verwandte Materialien

- [STMicroelectronics: STM32 32-bit Arm Cortex MCUs](https://www.st.com/en/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-mcus.html) — offizielle Übersicht der STM32-Familie, Serien, Leistung und Tools.
- [STMicroelectronics: STM32 Mainstream MCUs](https://www.st.com/en/microcontrollers-microprocessors/stm32-mainstream-mcus.html) — Übersicht der Massenmarktserien STM32C0, G0, F0, F1, G4 und deren Positionierung.
- [STMicroelectronics: STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) — offizielles STM32-Flash-Tool über ST-LINK/SWD, UART, USB DFU, I2C, SPI und CAN-Bootloader.
- [STMicroelectronics: NUCLEO-F103RB](https://www.st.com/en/product/nucleo-f103rb) — Beispiel einer offiziellen Nucleo-Platine mit integriertem ST-LINK, Arduino Uno V3-Anschlüssen und ST-Morpho-Pins.
- [ST UM1724: STM32 Nucleo-64 boards user manual](https://www.st.com/resource/en/user_manual/dm00105823-stlink-v2-in-circuit-debugger-programmer-for-stm8-and-stm32-stmicroelectronics.pdf) — Dokumentation für Nucleo-64, Anschlüsse, ST-LINK und Hinweis zu `3.3V` I/O.
- [Klipper: Code overview](https://www.klipper3d.org/Code_Overview.html) — Klipper-Architektur und MCU-Backend-Kontext, einschließlich STM32 im Quellbaum.
