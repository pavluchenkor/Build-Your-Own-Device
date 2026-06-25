# USB-UART Adapter

Ein USB-UART-Adapter wird benötigt, damit ein Computer oder Linux-Host über USB mit einem UART-Gerät kommunizieren kann. Er wandelt USB in reguläre serielle Leitungen `RX`, `GND` und `GND` um.

Ein solcher Adapter wird häufig zum Flashen, für Logs, Diagnose und zur Wiederherstellung von Boards ohne ordentlichen USB-Anschluss benötigt.

## Wo er benötigt wird

USB-UART Adapter ist nützlich für:

- Flashen mancher Mikrocontroller-Boards;
- Lesen von seriellen Logs;
- Zugriff auf die Gerätekonsole;
- Diagnose im Bootloader-Modus;
- Verbinden von Arduino Pro Mini und manchen Nano-Klonen;
- Arbeiten mit Boards ohne eingebauten USB;
- Wiederherstellung nach fehlgeschlagenem Flashen;
- temporäre MCU-Verbindung zum Host über serielle Schnittstelle.

Wenn ein Board bereits ordentlichen USB hat und als serielles Gerät erscheint, wird möglicherweise kein separater USB-UART Adapter benötigt.

## Was er hat

Typische Kontakte:

- `TX` oder `TXO` - Übertragung vom Adapter zum Gerät;
- `RX` oder `RXI` - Empfang vom Gerät;
- `GND` - gemeinsame Masse;
- `VCC`, `3V3` oder `5V` - Stromversorgung, falls benötigt;
- `DTR` - häufig für Auto-Reset/Flashen verwendet;
- `RTS`, `CTS` - Flusskontrollleitungen oder Boot-/Reset-Szenarien.

Anschlussdiagramm:

![USB-UART Adapter mit CH340T-Chip](../../img/02-controllers/10-usb-uart-ch340-adapter.jpg)

*Quelle: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:15938_-_USBtoSerial_1.jpg), SparkFun Electronics, CC BY 2.0*

Für einfaches Log-Lesen sind `TX`, `RX` und `GND` oft ausreichend. Strom wird nur dann angeschlossen, wenn klar ist, dass das Board vom Adapter versorgt werden soll.

## Wie TX und RX angeschlossen werden

Die Verbindung ist überkreuz:

```text
TX adapter -> RX device
RX adapter <- TX device
GND adapter -> GND device
```

Wenn keine Verbindung besteht, wird zuerst geprüft: Sind `TX` und `RX` vertauscht, gibt es eine gemeinsame `GND`, stimmt die Geschwindigkeit, und ist der richtige COM/tty-Port ausgewählt.

## 3.3V und 5V

USB-UART-Adapter gibt es in:

- nur `3.3V`;
- nur `5V`;
- mit `3.3V/5V`-Schalter;
- mit Jumper oder Lötjumper;
- mit `VCC` einer Spannung, aber Signalen eines anderen Pegels.

Das ist wichtig: Der Pegel von `VCC` und der Pegel von `TX/RX` sind aus Beschriftungen nicht immer offensichtlich.

ESP32, RP2040 und STM32 verwenden typischerweise `3.3V` Logik. Arduino Uno/Nano verwenden oft `5V` Logik. Wenn man ein `5V`-Signal an einen `3.3V`-Eingang anlegt, kann das Board beschädigt werden.

Vor dem Anschluss die Dokumentation von Adapter und Board prüfen. Nicht nur auf Jumperfarbe oder Beschriftung auf dem Gehäuse verlassen.

## TTL UART und RS-232

USB-UART-Adapter für Mikrocontroller gibt in der Regel TTL/CMOS UART aus: `5V` oder `5V`.

Das ist nicht dasselbe wie echtes RS-232.

RS-232 hat andere Spannungspegel und kann nicht direkt an einen Mikrocontroller GPIO angeschlossen werden. Wenn man mit einem echten RS-232-Port arbeiten muss, wird ein USB-RS232-Adapter oder Pegelwandler benötigt, kein regulärer USB-UART TTL.

## Stromversorgung vom Adapter

Der `VCC`-Pin am Adapter kann nützlich sein, wird aber häufig falsch verwendet.

Sicheres Vorgehen:

- für Logs und Diagnose zunächst nur `TX`, `RX`, `GND` anschließen;
- `VCC` nicht anschließen, wenn das Board bereits über USB, Netzteil oder eine andere Schaltung versorgt wird;
- keine Motoren, Servos, Relais, Heizungen und LED-Streifen über USB-UART versorgen;
- prüfen, wie viel Strom der Adapter tatsächlich liefern kann;
- berücksichtigen, dass `VCC` `3.3V` oder `5V` sein kann.

Wenn man zwei Stromquellen anschließt, ohne die Schaltung zu verstehen, kann es zu Rückspeisung, Instabilität oder Board-Schäden kommen.

## DTR und RTS

Manche Boards verwenden `DTR` und `RTS` für Auto-Reset oder Bootloader-Eintritt.

Beispiele:

- Arduino Pro Mini verwendet oft `DTR` über einen Kondensator für den Reset beim Flashen;
- ESP32-Boards können `DTR`/`RTS` verwenden, um `EN` und `BOOT` automatisch zu steuern;
- manche Bootloader-Szenarien erfordern manuelles Drücken einer Taste, wenn diese Leitungen nicht angeschlossen sind.

Wenn das Flashen nicht automatisch startet, ist es nicht immer ein `TX/RX`-Problem. Möglicherweise sind `DTR`/`RTS` nicht angeschlossen, der falsche Bootloader ist ausgewählt, oder `BOOT`/`RESET` muss manuell gedrückt werden.

## CH340, CP2102, FTDI

Verbreitete USB-UART Chips:

- **CH340/CH341** - günstige und weit verbreitete Adapter;
- **CP2102/CP210x** - verbreitetes Silicon Labs USB-UART;
- **FT232/FTDI** - klassische Option, oft teurer;
- **PL2303** - in alten Adaptern und Kabeln zu finden.

Auf modernen Systemen wird der Treiber oft automatisch installiert, aber nicht immer. Wenn der Port nicht erscheint, prüfen:

- USB-Kabel ist kein reines Ladekabel;
- Gerät wird vom System erkannt;
- ob ein Treiber benötigt wird;
- ob ein alter Treiber nicht im Konflikt steht;
- ob der Port nicht von einem anderen Programm belegt ist.

## Wie man den Adapter testet

Einfacher Loopback-Test:

1. Adapter an Computer anschließen.
2. `TX` des Adapters mit `RX` des Adapters verbinden.
3. Serielles Terminal öffnen.
4. Port und Geschwindigkeit auswählen, zum Beispiel `115200`.
5. Zeichen eingeben.
6. Wenn es funktioniert, werden die Zeichen zurückgegeben.

Damit werden Adapter selbst, Treiber, Kabel und Terminal-Programm ohne externes Board getestet.

## Was vor dem Kauf zu prüfen ist

Vor dem Kauf eines USB-UART Adapters prüfen:

- welche `TX/RX`-Pegel: `3.3V`, `5V` oder umschaltbar;
- wie der Pegel gewählt wird;
- welcher Chip verwendet wird: CH340, CP2102, FTDI oder anderer;
- ob Treiber für das eigene System vorhanden sind;
- ob `DTR` und `RTS` vorhanden sind, falls Auto-Flashen benötigt wird;
- welcher USB-Anschluss vorhanden ist;
- ob die Pins `TX`, `RX`, `VCC`, `VCC` in praktischer Reihenfolge angeordnet sind;
- ob es ein Schaltbild oder gute Dokumentation gibt;
- wie viel Strom von `VCC` bezogen werden kann, falls benötigt.

Für ESP32/RP2040/STM32-Diagnose ist ein Adapter mit `3.3V`-Signalen und klarer Beschriftung praktischer.

## Typische Fehler

- `TX` mit `TX`, `RX` mit `RX` verbinden;
- gemeinsame `GND` vergessen;
- `5V`-Pegel für `3.3V`-Board auswählen;
- `VCC` an ein bereits versorgtes Board anschließen;
- Last über USB-UART Adapter versorgen;
- USB-UART TTL mit USB-RS232 verwechseln;
- ein reines Ladekabel verwenden;
- CH340/CP2102/FTDI-Treiber nicht installieren;
- falschen COM/tty-Port auswählen;
- `DTR`/`RTS` nicht anschließen, wenn für Auto-Flashen benötigt;
- serielles Terminal offen lassen und sich dann wundern, warum der Flasher den Port nicht öffnen kann.

## Fazit

USB-UART Adapter ist eine Brücke zwischen Computer-USB und UART-Pins eines Geräts. Für eine minimale Verbindung werden überkreuz verbundene `TX/RX` und gemeinsame `GND` benötigt.

Hauptrisiken: falscher `3.3V/5V`-Pegel, unnötige Stromverbindung, TTL UART mit RS-232 verwechseln und fehlende `DTR`/`RTS`-Leitungen beim Flashen.

## Weiterführende Materialien

- [SparkFun: Serial Basic CH340C Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide) - praktischer Leitfaden zu USB-UART CH340C, `DTR/RX/TX/VCC/CTS/GND`-Pins, Spannungsauswahl und Loopback-Test.
- [SparkFun: Serial Basic Overview](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide/serial-basic-overview) - Pinout-Beschreibung und `3.3V/5V`-Umschaltung am Adapter.
- [Adafruit: FT232H Serial UART](https://learn.adafruit.com/adafruit-ft232h-breakout/serial-uart) - Beispiel eines USB-Seriell-Adapters, `TX`/`RX`, Flusskontrollleitungen und Verbindung zum Gerät.
- [Silicon Labs: CP2102 USB to UART Bridge](https://www.silabs.com/interface/usb-bridges/classic/device.cp2102) - offizielles Beispiel eines USB-UART-Bridge-Chips und Virtual COM Port-Treiber.
- [Klipper Configuration Reference: `[mcu]`](https://www.klipper3d.org/Config_Reference.html#mcu) - wie die serielle MCU-Verbindung in Klipper über `serial` beschrieben wird.
