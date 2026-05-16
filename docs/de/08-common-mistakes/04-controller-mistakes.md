# Controller-Fehler

Ein Controller ist keine universelle Kiste wo Sie alles direkt anschließen können.

Er liest Sensoren, gibt Steuersignale ab und kommuniziert mit dem Host. Aber Stromlasten müssen durch geeignete Ausgänge, MOSFETs, Relais, SSRs oder Treiber betrieben werden.

## Symptome

Typische Zeichen von Controller- oder Verbindungsproblemen:

- Board nicht erkannt via USB;
- Firmware startet nicht;
- Pins reagieren nicht;
- Controller startet neu;
- Controller wird erheblich heiß;
- Board stoppt Arbeiten nach Modul-Verbindung;
- ESP32 verliert Wi-Fi wenn Last eingeschaltet wird;
- Sensor nicht sichtbar obwohl Stromversorgung vorhanden;
- Klipper verbindet nicht zu MCU;
- Befehle arbeiten auf falschen Pin.

## Falscher Controller gewählt

Bevor Sie ein Board wählen müssen Sie die Aufgabe verstehen.

Für ein einfaches autonomes Wi-Fi-Gerät kann ESP32 eine gute Wahl sein.

Für ein zusätzliches MCU in Klipper ist oft praktischer zu suchen:

- RP2040;
- STM32;
- vorgefertigtes 3D-Drucker-Board.

Arduino Uno/Nano sind nützlich zum Lernen und einfache Experimente, aber für ein neues seriöses Gerät um einen Drucker stoßen Sie schnell auf Einschränkungen.

Der Fehler ist ein Board nur zu wählen weil "es populär ist", ohne zu überprüfen:

- Anzahl benötigter Pins;
- Logik-Pegel;
- Stromversorgung;
- Firmware-Unterstützung;
- USB/UART/CAN Verfügbarkeit;
- Unterstützung für benötigte Bibliotheken;
- Ausgangsstrom;
- Entwicklungsumgebung.

## ESP32 als Klipper MCU

ESP32 ist nützlich als separates IoT/Wi-Fi-Gerät.

Aber erwarten Sie nicht automatisch dass ESP32 die beste Wahl als Klipper MCU ist.

Wenn das Ziel Integration mit Klipper als zusätzliches MCU ist, schauen Sie zuerst auf offizielle und bewährte Optionen für Klipper. Für neue Hardware-Erweiterungen ist es oft einfacher und zuverlässiger RP2040 oder STM32 zu nutzen.

ESP32 ist gut wenn das Gerät sollte:

- autonom arbeiten;
- Wi-Fi haben;
- Daten via MQTT oder HTTP bereitstellen;
- Web-Schnittstelle haben;
- mit Home Assistant kommunizieren;
- separat von Klipper arbeiten.

## 3.3V und 5V Logik

Viele moderne Controller funktionieren mit 3.3V Logik.

Zum Beispiel:

- ESP32;
- RP2040;
- viele STM32.

Der Fehler ist ein 5V Signal auf einen Eingang der nur für 3.3V vorgesehen ist anzulegen.

Dies kann:

- den Pin sofort beschädigen;
- den Controller später beschädigen;
- instabile Operationen verursachen;
- ein Modul brechen das scheint okay.

Bevor Sie verbinden überprüfen Sie:

- Modul-Stromspannung;
- Eingang/Ausgang Logik-Pegel;
- gibt es einen Pegel-Wandler;
- akzeptiert Eingang 5V;
- was ist im technischen Beschreibung geschrieben.

## GPIO betreibt keine Last

GPIO ist ein Signalpin.

Er muss nicht betreiben:

- Lüfter;
- Servo;
- Heizer;
- LED-Streifen;
- Relais ohne Treiber;
- Solenoid;
- Motor.

GPIO kann einen Befehl senden. Laststrom muss durch einen Stromausgang, MOSFET, Treiber, Relais oder separates Modul gehen.

Wenn Last direkt auf GPIO verbunden ist, können Sie den Pin oder das ganze Board beschädigen.

## Kein gemeinsames GND

Ein Controller kann ein externes Modul nur steuern wenn sie eine gemeinsame Referenzstufe haben.

Typischer Fehler:

- Servo von separater 5V Stromversorgung;
- Signal kommt vom Controller;
- `GND` nicht verbunden;
- Servo ruckt oder reagiert nicht.

Gleich mit MOSFET-Modulen, PWM-Lüftern, einige Sensoren und externe Boards.

## Falsche Firmware

Board könnte okay sein, aber Firmware passt nicht.

Fehler:

- Firmware geflasht für falschen Mikrocontroller;
- falschen Bootloader gewählt;
- USB und UART Firmware vermischt;
- falschen seriellen Port gewählt;
- Klipper bestimmte falschen Geräte-Pfad;
- Pins in Config passen nicht zu Board;
- Firmware/Host nicht neu gestartet nach Flashen.

Bevor Sie flashen müssen Sie genau das Board- und Mikrocontroller-Modell kennen.

## Pin existiert auf Schaltplan aber nicht geeignet

Nicht jeder Pin ist gleich.

Pins können Einschränkungen haben:

- nur Eingang;
- von USB/UART/SPI verwendet;
- während Boot verwendet;
- bezogen auf Boot-Modus;
- unterstützt nicht benötigte PWM;
- hochgezogen oder runtergezogen;
- Konflikt mit anderem Modul.

Wenn Pin sich seltsam verhält, überprüfen Sie Board-Dokumentation, nicht nur GPIO-Nummer.

## Was überprüfen

Mini-Checkliste:

1. Ist das richtige Board für die Aufgabe gewählt?
2. Welche Stromversorgung braucht das Board?
3. Welche Logik: 3.3V oder 5V?
4. Gibt es gemeinsames `GND` mit externen Modulen?
5. Ist Last nicht von GPIO betrieben?
6. Unterstützt Board benötigte Schnittstelle?
7. Ist ausgewählter Pin nicht verwendet?
8. Ist Firmware richtig?
9. Ist Board via USB sichtbar?
10. Passen Konfiguration zum Board-Pinout?

## Was nicht zu tun

Sie können nicht:

- 5V auf 3.3V Eingang ohne Überprüfung anlegen;
- Load direkt auf GPIO verbinden;
- zufällige Firmware eines "ähnlichen" Boards flashen;
- Drähte unter Stromversorgung ändern;
- annehmen dass jeder GPIO jede Aufgabe passt;
- Controller-Erwärmung ignorieren;
- externe Module ohne gemeinsames Erdung verbinden wenn benötigt.

## Wichtige Punkte

- Controller steuert aber betreibt nicht direkt eine Last.
- 3.3V und 5V Logik müssen kompatibel sein.
- GPIO ist ein Signal, keine Stromversorgung.
- Für Klipper MCU schauen Sie oft auf RP2040/STM32, ESP32 ist bequemer als autonomes Wi-Fi-Gerät.
- Firmware und Pinout müssen zum aktuellenBoard passen.
- Wenn Board heiß wird oder stoppt erkannt zu werden, schalten Sie Stromversorgung aus und finden Sie Verbindungsfehler.

## Referenzen

- [Klipper: Installation](https://www.klipper3d.org/Installation.html) - allgemeiner Prozess Vorbereitung und Flashen MCU für Klipper.
- [Klipper: Config Reference, MCU](https://www.klipper3d.org/Config_Reference.html#mcu) - `[mcu]` Abschnitt, Seriell/CAN-Verbindung und zusätzliche MCUs.
- [Arduino: Digital Pins](https://docs.arduino.cc/learn/microcontrollers/digital-pins/) - grundlegende Erklärung digitaler Pins als Eingänge/Ausgänge, nicht Stromversorgung.
- [Espressif ESP32 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf) - offizielle elektrische Spezifikationen von ESP32.
- [Raspberry Pi Pico Datasheet](https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf) - offizielle Daten auf RP2040/Pico, Stromversorgung und GPIO.
