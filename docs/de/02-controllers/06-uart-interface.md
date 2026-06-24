# UART-Schnittstelle

UART ist eine einfache serielle Datentransmissionsschnittstelle zwischen zwei Geräten. Erweiterung: `Universal Asynchronous Receiver/Transmitter`.

In praktischen Projekten hörst du normalerweise „UART", „seriell", „TX/RX" oder „UART-Port". Der Schlüsselpunkt für Anfänger ist: UART überträgt Daten auf der `TX`-Leitung, empfängt auf der `RX`-Leitung, und beide Geräte benötigen eine gemeinsame `GND` für den ordnungsgemäßen Betrieb.

## Wo UART verwendet wird

UART findet sich fast überall:

- Debug-Logs von Mikrocontrollern;
- Flashing von Boards über USB-UART-Adapter;
- Host-zu-MCU-Kommunikation in einigen Klipper-Szenarien;
- GPS-, RFID-, Fingerabdruck- und Sensormodule;
- TMC-Schrittmotor-Treiberkonfiguration;
- Kommunikation zwischen zwei Mikrocontrollern;
- Service-Port auf dem Board.

UART ist praktisch, da es wenige Drähte benötigt und gut für einfachen Text-, Befehls- und Diagnosefunk funktioniert.

## TX, RX und GND

Minimale Verbindung:

- `TX` - Übertragung;
- `RX` - Empfang;
- `GND` - gemeinsame Masse.

TX eines Geräts wird mit RX des anderen verbunden:

![Kreuzweise verbundene TX/RX und gemeinsame GND in UART-Verbindung](../../img/02-controllers/06-uart-tx-rx-crossover.png)

*Quelle: [SparkFun Electronics](https://learn.sparkfun.com/tutorials/serial-communication/all), CC BY-SA 4.0*

Regel:

```text
Device A TX -> Device B RX
Device A RX <- Device B TX
Device A GND -> Device B GND
```

Der häufigste Fehler ist die Verbindung von `TX` mit `TX` und `RX` mit `RX`. Manchmal sind die Markierungen des Moduls verwirrend. Wenn also keine Verbindung hergestellt wird, überprüfe zunächst den Pinout und die Dokumentation, anstatt alle Drähte zufällig zu wechseln.

## UART, USB und USB-UART

UART ist nicht USB.

Ein Computer hat normalerweise keine bloßen UART-Pins. Deshalb wird ein USB-UART-Adapter benötigt: Er verbindet sich auf der einen Seite mit dem USB des Computers und stellt auf der anderen Seite `TX`-, `RX`-, `GND`- und manchmal `VCC`-, `DTR`-, `CTS`-Leitungen bereit.

Beispiele:

- Computer liest Logs von einem Board über USB-UART;
- USB-UART flasht ein Board ohne eingebautes USB;
- Host verbindet sich mit MCU über seriell;
- Adapter hilft, ein Board nach fehlgeschlagenem Flashing wiederherzustellen.

Verwirre einen USB-Anschluss auf einem Board nicht mit UART-Pins auf dem Header. Bei einigen Boards ist USB bereits mit einem integrierten USB-UART-Chip verbunden, während bei anderen USB direkt zum Mikrocontroller geht.

## Logikpegel: 3.3V, 5V, RS-232

UART beschreibt die Datentransmissionsmethode, garantiert aber keine sicheren Spannungspegel.

In der DIY-Elektronik ist TTL/CMOS UART am häufigsten:

- `3.3V` UART - ESP32, RP2040, STM32 und viele moderne Boards;
- `5V` UART - Arduino Uno/Nano und einige ältere Module.

Das Anlegen eines `5V`-Signals an einen `3.3V`-Mikrocontroller-Eingang kann das Board beschädigen. Für inkompatible Pegel ist ein Spannungswandler oder eine andere Anpassungsschaltung erforderlich.

Es gibt auch RS-232, das separat ist. Dies ist nicht einfach „UART auf einem DB9-Stecker". RS-232 hat unterschiedliche Spannungspegel und unterschiedliche elektrische Logik. Du kannst einen echten RS-232-Port nicht direkt mit einem Mikrocontroller GPIO verbinden. Ein Spannungswandler ist erforderlich, z. B. eine MAX232-ähnliche Schaltung oder einen fertigen Adapter.

## Geschwindigkeit und Format

UART-Geschwindigkeit muss übereinstimmen. Häufige Werte:

```text
9600
57600
115200
250000
1000000
```

Wenn die Geschwindigkeit nicht übereinstimmt, zeigt das Terminal Müll oder Stille an.

Es gibt auch Transmissionsformat. `8N1` wird häufig verwendet:

- `8` - 8 Datenbits;
- `N` - keine Parität;
- `1` - ein Stoppbit.

Für die meisten einfachen Aufgaben reicht es aus, die gleiche Geschwindigkeit und das Standard-Format `8N1` einzustellen, es sei denn, die Moduldokumentation schreibt etwas anderes vor.

## UART in 3D-Druckern

In 3D-Druckern erfüllt UART oft drei verschiedene Rollen.

**Host- und Board-Kommunikation**

Einige Boards können über seriell/UART mit dem Host kommunizieren. In Klipper wird dies im Abschnitt `[mcu]` über `serial` beschrieben.

**TMC-Treiberkonfiguration**

Einige Schrittmotortreiber verwenden UART zum Konfigurieren von Strom, stealthChop/spreadCycle, Diagnose und Statusabfrage. Der Motor selbst wird normalerweise nicht von UART, sondern von `STEP`- und `DIR`-Signalen gesteuert.

**Debug und Flashing**

UART kann für Logs, Bootloader-Modus und Board-Recovery über USB-UART-Adapter verwendet werden.

## Ein UART - normalerweise zwei aktive Geräte

Klassisches UART ist eine Verbindung zwischen zwei Geräten. Du kannst nicht blind mehrere Sender mit einer `RX`-Leitung verbinden.

Probleme:

- zwei Geräte ziehen gleichzeitig die `TX`-Leitung;
- Daten vermischen sich;
- ein Modul empfängt Befehle, die für ein anderes bestimmt sind;
- möglicher elektrischer Konflikt.

Manchmal kann eine `TX` von mehreren Empfängern gehört werden, aber dies ist eine bewusste Entscheidung und nicht als universelle Regel geeignet. Für Anfänger ist es sicherer anzunehmen: Ein UART-Port - Ein Gerätepaar.

## Was vor dem Anschließen zu prüfen ist

Vor dem Anschließen von UART prüfe:

- wo sind `TX` und `RX`;
- ist eine gemeinsame `GND` erforderlich;
- Logikpegel: `3.3V` oder `5V`;
- ist dies TTL UART oder RS-232;
- Übertragungsgeschwindigkeit;
- Format, falls angegeben;
- ist dieses UART nicht von USB-Logs oder Flashing besetzt;
- gibt es einen anderen Sender, der mit dieser Leitung verbunden ist;
- müssen Power oder nur `TX`/`RX`/`GND` verbunden werden.

Stromversorgung vom USB-UART-Adapter wird nur verbunden, wenn klar ist, dass das Board von ihm mit Strom versorgt werden soll. Oft werden für Diagnosen nur `TX`, `RX` und `GND` benötigt.

## Typische Fehler

- Verbindung von `TX` mit `TX`, `RX` mit `RX`;
- Vergessen der gemeinsamen `GND`;
- Anlegen von `5V` UART an einen `3.3V`-Eingang;
- Verwechselung von TTL UART und RS-232;
- Auswahl der falschen Baudrate;
- Stromversorgung von einem USB-UART-Adapter mit einem bereits angetriebenen Board verbinden;
- Verwendung von UART-Pins, die von USB-Logs oder Bootloader besetzt sind;
- Verbindung mehrerer Sender mit einer Leitung;
- Denken, UART kann eine starke Last direkt antreiben.

## Wichtigste Erkenntnisse

UART ist eine einfache Schnittstelle für den Datenaustausch zwischen zwei Geräten. Du benötigst kreuzweise verbundene `TX`/`RX`, gemeinsame `GND`, übereinstimmende Geschwindigkeit und kompatible Logikpegel.

UART ist keine Stromversorgung und funktioniert nicht als Stromausgabe. Es überträgt Daten, nicht zum Drehen von Motoren oder zum direkten Aktivieren von Heizgeräten.

## Verwandte Materialien

- [SparkFun: Serial Communication](https://learn.sparkfun.com/tutorials/serial-communication/all) - gute praktische Erklärung von UART, TX/RX, Baudrate, TTL-Seriell, RS-232 und häufigen Fehlern.
- [SparkFun: Serial Communication - UARTs](https://learn.sparkfun.com/tutorials/serial-communication/uarts) - was UART in einem Mikrocontroller tut und warum TX/RX erforderlich sind.
- [Adafruit: Serial UART on FT232H](https://learn.adafruit.com/adafruit-ft232h-breakout/serial-uart) - Beispiel eines USB-UART-Adapters und Anschließen von TX/RX/GND an ein serielles Gerät.
- [SparkFun: Serial Basic CH340C Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide) - Beispiel eines USB-UART-Adapters, RX/TX/VCC/GND-Pins und Loopback-Test.
- [Klipper: Configuration reference - `[mcu]`](https://www.klipper3d.org/Config_Reference.html#mcu) - wie die serielle MCU-Verbindung in der Klipper-Konfiguration beschrieben wird.
