# USB-TTL

Ein USB-TTL-Adapter oder USB-UART-Adapter ermöglicht Ihrem Computer, mit einem Mikrocontroller über UART durch USB zu kommunizieren.

Sie benötigen ihn für:

- Flashen einiger Platinen;
- Lesen von Protokollen;
- Debugging UART-Kommunikation;
- Konfigurieren von Modulen;
- Wiederherstellung einer Platine, wenn normales USB nicht funktioniert;
- Verbindung zu einem Gerät ohne eingebautes USB-UART.

Gängige Adapter verwenden Chips wie CH340, CP2102, FT232 und ähnlich.

## USB-TTL oder USB-UART

Verbraucherbeschreibungen sagen oft USB-TTL.

Technisch bedeutet das normalerweise einen USB-UART-Adapter mit TTL-Logikpegeln.

Das Wichtigste zu verstehen:

- USB-Seite verbindet sich mit dem Computer;
- UART-Seite verbindet sich mit dem Mikrocontroller;
- Der Adapter ist kein Programmierer für alle Platinen;
- Der Adapter ersetzt nicht ST-Link, wenn Sie STM32 durch SWD flashen müssen.

## Hauptpins

Normalerweise gibt es:

- `GND`;
- `TX`;
- `RX`;
- `VCC` oder `3V3`/`5V`;
- manchmal `DTR`;
- manchmal `CTS`, `RTS`.

Minimum für Kommunikation:

- `GND`;
- `TX`;
- `RX`.

Leistung wird nur verbunden, wenn Sie sicher sind, dass der Adapter die Platine mit Strom versorgen sollte.

## TX und RX sind kreuzverbunden

UART ist wie folgt verbunden:

```text
Adapter TX -> Platinen RX
Adapter RX -> Platinen TX
Adapter GND -> Platinen GND
```

`TX` ist Senden.

`RX` ist Empfangen.

Der Sender eines Geräts muss mit dem Empfänger des anderen verbunden sein.

Wenn Sie `TX` mit `TX` verbinden, funktioniert Kommunikation normalerweise nicht.

![Kreuzverbundene TX/RX in UART-Verbindung](../../../img/02-controllers/06-uart-tx-rx-crossover.png)

*Quelle: [SparkFun Electronics](https://learn.sparkfun.com/tutorials/serial-communication/all), CC BY-SA 4.0*

## Gemeinsamer Grund

Der Adapter `GND` und Platinen `GND` müssen verbunden sein.

Ohne gemeinsamen Grund funktioniert UART möglicherweise nicht oder arbeitet instabil.

Auch wenn die Platine von separater Stromversorgung versorgt wird, wird Grund immer noch als gemeinsames Signalpegel benötigt.

## 3.3V und 5V Logikpegel

Dies ist einer der wichtigsten Punkte.

Der Adapter kann mit Logik funktionieren bei:

- `3.3V`;
- `5V`;
- umschaltbar `3.3V/5V`.

Viele moderne Platinen und Module verwenden 3.3V Logik: ESP32, RP2040, viele STM32.

Wenn Sie ein 5V UART-Signal an eine 3.3V Eingabe anwenden, können Sie den Pin oder die ganze Platine beschädigen.

Vor dem Anschließen überprüfen:

- welche Logikebene die Platine verwendet;
- welche Logikebene der Adapter verwendet;
- was der 3.3V/5V Jumper macht;
- ob der Jumper nur die `VCC`-Leistung oder auch die `TX/RX`-Pegel ändert.

Einige Adapter liefern 5V Leistung aber 3.3V Logik-Signale. Andere ändern sowohl Leistung als auch Pegel. Überprüfen Sie die Dokumentation des spezifischen Adapters.

## Leistung vom Adapter

Sie müssen `VCC` nicht immer verbinden.

Oft ist es sicherer, nur zu verbinden:

- `GND`;
- `TX`;
- `RX`.

Stromversorgung der Platine von ihrer normalen Quelle.

Sie können `VCC` vom Adapter verbinden wenn:

- die Platine für diese Spannung bewertet ist;
- der Adapter-Strom innerhalb der Platinen-Fähigkeit ist;
- es keinen anderen Strom gleichzeitig gibt;
- die Platinen-Dokumentation das Stromzuführen durch diesen Pin erlaubt.

Ein gefährlicher Fehler ist das Zuführen von Strom von sowohl USB-UART Adapter als auch separater Stromversorgung gleichzeitig, was die Quellen in Konflikt bringt.

## DTR und Auto-Reset

Einige Platinen verwenden `DTR` für automatischen Reset während des Flashens.

Zum Beispiel können Arduino Pro Mini und ähnliche Platinen DTR durch einen Kondensator für Auto-Reset verwenden.

Wenn Flashen nicht automatisch beginnt, kann das sein weil:

- DTR nicht verbunden ist;
- manueller Reset nötig ist;
- der falsche Adapter ausgewählt ist;
- der falsche Bootloader ausgewählt ist;
- Geschwindigkeit oder Platine in der IDE falsch ausgewählt ist.

Für einfaches Protokoll-Lesen wird DTR normalerweise nicht benötigt.

## Wie man überprüft, ob der Adapter vom System sichtbar ist

Auf macOS und Linux erscheint der Adapter normalerweise als Gerät in `/dev`.

Beispiele:

```bash
ls /dev/tty.*
ls /dev/cu.*
ls /dev/ttyUSB*
ls /dev/ttyACM*
```

Auf Windows erscheint er als `COM` Port.

Wenn der Port nicht erscheint:

- überprüfen Sie das USB-Kabel;
- versuchen Sie einen anderen USB-Port;
- überprüfen Sie den Treiber;
- überprüfen Sie, ob es nicht nur ein Ladekabel ist;
- sehen Sie, welcher Chip auf dem Adapter ist: CH340, CP2102, FT232.

Billige Adapter benötigen manchmal einen separaten Treiber, besonders auf Windows.

## Loopback-Test

Einfache Methode um den Adapter zu überprüfen:

1. Verbinden Sie die `TX` und `RX` des Adapters zusammen.
2. Öffnen Sie ein serielles Terminal.
3. Wählen Sie den Port und die Geschwindigkeit.
4. Geben Sie Text ein.

Wenn die Zeichen, die Sie eingeben, zurückkommen, funktioniert der Adapter und Port wahrscheinlich.

Nach dem Test, entfernen Sie den Jumper zwischen `TX` und `RX`.

## Häufige Fehler

- `TX` verbunden mit `TX` und `RX` mit `RX`;
- gemeinsames `GND` vergessen;
- 5V Ebene für eine 3.3V Platine ausgewählt;
- `VCC` verbunden, obwohl die Platine bereits separat mit Strom versorgt ist;
- USB-Kabel erwies sich als Nur-Laden;
- CH340/CP210x/FTDI Treiber nicht installiert;
- falscher COM Port ausgewählt;
- UART Geschwindigkeit passt nicht;
- USB-UART zum Flashen von STM32 durch SWD erwartet;
- verwirrt Boot-Modus oder Reset während des Flashens.

## Das Wesentliche

- USB-UART Adapter wird für UART-Kommunikation zwischen Computer und Platine benötigt.
- Minimum für Kommunikation: `GND`, `TX`, `RX`.
- Adapter `TX` geht zu Platinen `RX`, Adapter `RX` geht zu Platinen `TX`.
- Überprüfen Sie 3.3V/5V Logikpegel vor dem Verbinden.
- `VCC` wird nur verbunden, wenn Sie definitiv Leistung vom Adapter benötigen.
- Wenn Adapter nicht sichtbar, überprüfen Sie Kabel, Treiber und USB-Port.

## Referenzmaterialien

- [SparkFun: Serial Basic Hookup Guide](https://learn.sparkfun.com/tutorials/serial-basic-hookup-guide) - USB-zu-Seriell-Adapter, TX/RX/GND, VCC, DTR und 3.3V/5V Umschaltung.
- [SparkFun: Serial Basic CH340C Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide/serial-basic-overview) - moderner CH340C USB-UART Adapter, Pins, LEDs und Spannungswahl.
- [SparkFun: Serial Communication](https://learn.sparkfun.com/tutorials/serial-communication) - UART-Grundlagen, TX/RX und serielle Kommunikation.
- [Silicon Labs: CP210x USB to UART Bridge VCP Drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) - offizielle CP210x Virtual COM Port Treiber.
- [Adafruit FTDI TTL-232 USB Type C Cable](https://www.adafruit.com/product/4364) - Beispiel Kabel mit 5V Leistung und 3.3V Logik, zeigt warum Leistung und Signal-Pegel separat gelesen werden müssen.
