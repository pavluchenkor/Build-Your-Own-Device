# ST-Link

ST-Link ist ein Programmierer und Debugger für STM32 Mikrocontroller.

Im Kontext einfacher Geräte wird es verwendet um:

- eine STM32 Platine zu flashen;
- eine Platine nach fehlgeschlagenem Flash wiederherzustellen;
- sich mit dem Chip durch SWD zu verbinden;
- Speicher zu löschen;
- zu überprüfen, dass der Mikrocontroller sichtbar ist;
- manchmal das Programm zu debuggen.

ST-Link wird nicht für alle Platinen benötigt. ESP32, RP2040 und Arduino flashen normalerweise anders.

## Was ist SWD

SWD ist `Serial Wire Debug`.

Es ist eine Debug- und Flash-Schnittstelle für ARM Mikrocontroller, üblicherweise mit STM32 verwendet.

Für grundlegende Verbindung benötigen Sie normalerweise:

- `SWDIO`;
- `SWCLK`;
- `GND`;
- manchmal `NRST`;
- manchmal `3.3V` oder `VTref` als Ziel-Referenz-Spannung.

Wichtig: `3.3V` auf ST-Link bedeutet nicht immer "die Platine von hier mit Strom versorgen". Oft benötigt ST-Link die Ziel-Platinen-Spannung um die Signal-Pegel zu verstehen.

## Minimale Verbindung

Normalerweise verbinden Sie:

```text
ST-Link SWDIO -> Platinen SWDIO
ST-Link SWCLK -> Platinen SWCLK
ST-Link GND   -> Platinen GND
ST-Link NRST  -> Platinen NRST, wenn Reset nötig ist
ST-Link 3.3V/VTref -> 3.3V Ziel, falls nötig für spezifische ST-Link
```

Die STM32 Platine wird oft von ihrer normalen Stromversorgung oder USB versorgt.

Vor dem Verbinden überprüfen Sie die Dokumentation für Ihren spezifischen ST-Link und die Platine.

![Nucleo Platinen für STM32 mit eingebautem ST-Link Debugger](../../../img/02-controllers/04-stm32-nucleo-boards.jpg)

*Quelle: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:STM32_Nucleo_boards.jpg), Avandalen, CC BY-SA 4.0*

## Platinen-Stromversorgung

Die häufigste Verwirrtheit: wird die Platine von ST-Link oder separat versorgt?

Optionen:

1. Platine wird separat versorgt, ST-Link verbindet sich nur mit SWD und GND.
2. ST-Link versorgt 3.3V zu einer kleinen Ziel-Platine, falls sie wirklich dafür entworfen ist.
3. ST-Link liest nur `VTref` aber sollte die Platine nicht versorgen.

Sie können nicht blindlings mehrere Stromquellen verbinden.

Wenn die Platine bereits von USB oder einer Stromversorgung versorgt wird, verbinden Sie keine Stromversorgung von ST-Link, bis Sie sicher sind, dass die Schaltung es erlaubt.

## Wie ST-Link sich von DFU unterscheidet

DFU ist ein Flash-Modus durch einen USB Bootloader, falls vorhanden.

ST-Link funktioniert durch SWD direkt mit dem Mikrocontroller.

ST-Link ist nützlich wenn:

- DFU nicht vorhanden ist;
- der Bootloader ist beschädigt oder nicht verwendet;
- Flashen deaktivierte USB;
- die Platine wird nicht in normalen Flash-Modus eintreten;
- Sie Speicher löschen müssen;
- Sie STM32 Zugriff wiederherstellen müssen.

Aber wenn eine Platine normalerweise durch USB/DFU oder SD Karte flasht, wird ST-Link möglicherweise nicht benötigt.

## Verbindung unter Reset

Manchmal bricht Firmware SWD Zugriff ab.

Zum Beispiel:

- SWD Pins werden als normales GPIO verwendet;
- Firmware lässt den Chip schnell schlafen;
- Code hängt direkt nach dem Start;
- Clock/Power Modi sind falsch eingestellt.

In solchen Fällen hilft `Connect under reset` Modus.

Die Idee: ST-Link hält Reset und versucht zu verbinden, bevor schlechte Firmware ausführt.

Dies erfordert oft das Verbinden von `NRST`.

## Wie man weiß, dass ST-Link die Platine sieht

In STM32CubeProgrammer oder ähnlichem Werkzeug sehen Sie normalerweise:

- ob ST-Link verbunden ist;
- ob das Ziel gefunden wird;
- welcher Chip erkannt wird;
- ob Sie Speicher lesen können;
- ob Sie Flash löschen können.

Wenn ST-Link als USB Gerät sichtbar ist aber das Ziel nicht gefunden wird, ist das Problem oft die Platinen-Verbindung:

- Ziel-Platine hat keine Stromversorgung;
- kein gemeinsames `GND`;
- `SWDIO` und `SWCLK` sind vertauscht;
- `VTref` ist nicht verbunden, falls nötig;
- SWD Frequenz zu hoch;
- Chip ist gesperrt;
- Firmware verhindert Verbindung;
- `Connect under reset` wird benötigt.

## SWD Frequenz

Wenn Kommunikation instabil ist, versuchen Sie die SWD Frequenz zu reduzieren.

Auf langen Drähten, schlechten Dupont Jumpern oder instabilen Platinen kann hohe Frequenz mit Verbindung interferieren.

Für Platinen-Recovery ist langsam und zuverlässig besser als schnell.

## Häufige Fehler

- `GND` vergessen;
- `SWDIO` und `SWCLK` vertauscht;
- Stromversorgung von ST-Link und USB gleichzeitig verbunden ohne die Schaltung zu verstehen;
- Ziel-Platine nicht versorgt;
- `NRST` nicht verbunden, wenn `Connect under reset` nötig ist;
- SWD Frequenz zu hoch eingestellt;
- versucht ESP32 oder RP2040 mit ST-Link zu flashen;
- versucht sich mit einem gesperrten Chip zu verbinden ohne Readout-Schutz zu verstehen;
- lange schlechte Qualitäts-Drähte verwendet;
- ST-Link Firmware nicht aktualisiert oder Treiber nicht installiert.

## Was Sie nicht tun können

Sie können nicht:

- 5V auf eine 3.3V STM32 Platine ohne Überprüfung anwenden;
- mehrere Stromquellen blind verbinden;
- ST-Link zu einer Platine unter Netzspannung ohne sichere Isolierung und Gehäuse verbinden;
- SWD Drähte mit Stromversorgung ändern, wenn es ein Risiko von Kurzschluss gibt;
- annehmen, dass ein Klone ST-Link das gleiche Pinout wie das Original hat.

Klone ST-Link Pinouts können sich unterscheiden. Überprüfen Sie immer die Markierungen auf Ihrem spezifischen Adapter.

## Das Wesentliche

- ST-Link wird für STM32 durch SWD benötigt.
- Minimum: `SWDIO`, `SWCLK`, `GND`, manchmal `NRST` und `VTref`.
- Die Platine sollte richtig versorgt werden, aber nicht unbedingt von ST-Link.
- DFU und ST-Link sind unterschiedliche Flash-Methoden.
- `Connect under reset` hilft den Zugriff nach schlechter Firmware wiederherzustellen.
- Wenn das Ziel nicht gefunden wird, überprüfen Sie zuerst Stromversorgung, `GND`, `SWDIO/SWCLK`, `NRST` und SWD Frequenz.

## Referenzmaterialien

- [STMicroelectronics: UM1075 ST-LINK/V2 User Manual](https://www.st.com/resource/en/user_manual/dm00026748-st-link-v2-in-circuit-debugger-programmer-for-stm8-and-stm32-stmicroelectronics.pdf) - offizielle ST-LINK/V2 Manual, SWD/JTAG Pins, Ziel VCC und GND.
- [STMicroelectronics: UM2237 STM32CubeProgrammer User Manual](https://www.st.com/resource/en/user_manual/um2237-stm32cubeprogrammer-software-description-stmicroelectronics.pdf) - ST-LINK Verbindungsmodi, einschließlich Normal, Connect under reset und Hot plug.
- [ST Wiki: ST-LINK](https://wiki.st.com/stm32mpu/wiki/ST-LINK) - ST-LINK Übersicht als Hardware-Sonde für STM32/STM8 und unterstützte Protokolle.
- [Klipper: Installation](https://www.klipper3d.org/Installation.html) - allgemeiner MCU Vorbereitung-Prozess für Klipper.
- [STMicroelectronics: STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) - offizielles ST Werkzeug zum Flashen STM32 durch ST-LINK/SWD, UART, USB DFU, SPI, I2C und CAN Bootloader.
