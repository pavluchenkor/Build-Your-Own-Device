# I2C Interface

I2C ist eine Kommunikationsschnittstelle für kleine Mikrochips und Module in der Nähe des Controllers. Erweiterung: `Inter-Integrated Circuit`. In der Dokumentation ist oft der Begriff `I2C bus` zu finden.

Grundprinzip: Mehrere Geräte können an dieselben zwei Signalleitungen `SDA` und `SCL` angeschlossen werden, sofern sie unterschiedliche Adressen haben.

## Wo I2C verwendet wird

Bei einfachen Geräten rund um einen 3D-Drucker wird I2C häufig verwendet für:

- OLED-Displays;
- Temperatur-, Feuchtigkeits-, Druck- und Lichtsensoren;
- Echtzeituhrmodule;
- GPIO-Erweiterungen;
- einige Encoder- und Tastenmodule;
- I2C-Multiplexer;
- einige RFID/NFC-Module;
- kleine Hilfsplatinen.

I2C funktioniert gut für kurze Verbindungen innerhalb eines Gehäuses. Bei langen Leitungen über den gesamten Drucker oder in der Nähe von Stromleitungen wird es riskanter.

## SDA, SCL, Stromversorgung und GND

Ein I2C-Modul hat typischerweise 4 Anschlüsse:

- `VCC` oder `VIN` - Stromversorgung;
- `GND` - gemeinsame Masse;
- `SDA` - Daten;
- `SCL` - Taktsignal.

Eine Schaltung mit mehreren Geräten sieht so aus:

![I2C bus: one master and three devices on common SDA/SCL](../../img/02-controllers/07-i2c-bus-topology.svg)

*Quelle: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:I2C.svg), Cburnett, CC BY-SA 3.0*

Alle Geräte am selben I2C-Bus sind an dasselbe `SDA`, `SCL` und `GND` angeschlossen. Die Stromversorgung kann gemeinsam genutzt werden, jedoch müssen Spannung und Logikpegel für jedes Modul geprüft werden.

## Geräteadressen

Jedes I2C-Gerät hat eine Adresse. Kleine OLEDs verwenden zum Beispiel oft `0x3C`, manche Sensoren `0x76`, `0x77`, `0x68`, `0x69` usw.

Wenn zwei Geräte am selben Bus dieselbe Adresse haben, kann der Controller sie nicht einzeln ansprechen.

Möglichkeiten bei Adresskonflikten:

- Adresse per Jumper oder Lötbrücke ändern, sofern das Modul dies unterstützt;
- eine andere Modulvariante wählen;
- einen I2C-Multiplexer verwenden;
- Geräte auf verschiedene I2C-Busse aufteilen, wenn Controller und Firmware dies erlauben.

Die Adresse wird häufig im Hexadezimalformat (`hex`) angegeben: `0x3C`. Manche Firmware oder Konfigurationen erfordern jedoch das Dezimalformat (`decimal`). So entspricht `0x3C` in Dezimal dem Wert `60`. Die Dokumentation des jeweiligen Systems muss dazu geprüft werden.

## Pull-up-Widerstände

I2C-Leitungen arbeiten über Pull-up-Widerstände. Geräte am Bus können `SDA` oder `SCL` in der Regel auf Low ziehen, der High-Pegel entsteht durch den Pull-up zur Logikversorgung.

Ohne Pull-ups funktioniert der Bus möglicherweise nicht. Zu viele Module mit eigenen Pull-ups an einem Bus können jedoch ebenfalls ein Problem sein: Der Gesamtwiderstand wird zu klein, die Leitungen werden stärker belastet, Signalflanken und -pegel können sich verschlechtern.

In der Praxis:

- viele OLEDs und Sensorplatinen haben bereits Pull-up-Widerstände eingebaut;
- bei einem kurzen, einfachen Bus funktioniert das meistens sofort;
- bei vielen Geräten müssen Modulschaltpläne und die Summe der Pull-ups geprüft werden;
- bei einem instabilen Bus sind Pull-up-Widerstände eine der ersten Prüfstellen.

Ein üblicher Startwiderstand für einen separaten Bus liegt bei etwa `4,7 kOhm`, die Pull-ups in fertigen Modulen können jedoch abweichen.

## 3,3 V und 5 V

I2C ist besonders empfindlich gegenüber Spannungspegeln, da `SDA` und `SCL` in der Regel auf eine bestimmte Versorgungsspannung hochgezogen werden.

ESP32, RP2040 und STM32 arbeiten typischerweise mit `3,3-V`-Logik. Arduino Uno/Nano arbeitet oft mit `5-V`-Logik.

Gefährliche Situation:

- `3,3-V`-Controller;
- I2C-Modul mit `5-V`-Versorgung;
- Pull-up-Widerstände des Moduls ziehen `SDA` und `SCL` auf `5 V`.

In diesem Fall kann `5 V` am GPIO des Controllers anliegen. Das kann den Mikrocontroller beschädigen.

Vor dem Anschluss prüfen:

- mit welcher Spannung das Modul versorgt wird;
- auf welchen Pegel `SDA` und `SCL` hochgezogen werden;
- ob ein Pegelwandler auf dem Modul vorhanden ist;
- ob das Modul mit einem `3,3-V`-Controller kompatibel ist.

Im Zweifelsfall `3,3-V`-Versorgung für I2C-Module verwenden oder einen Pegelwandler einsetzen.

## Geschwindigkeit

Typische I2C-Geschwindigkeiten:

```text
100000   # standard mode, 100 kHz
400000   # fast mode, 400 kHz
```

Bei kurzen Leitungen und normalen Modulen funktioniert `400 kHz` oft problemlos. Bei langen Leitungen, schwachen Pull-ups, vielen Geräten oder einer störungsreichen Umgebung empfiehlt sich der Start mit `100 kHz`.

In Klipper wird der Parameter `i2c_speed` nicht von allen MCUs gleichermaßen unterstützt. Laut Dokumentation verwenden viele Mikrocontroller `100000`, während manche Plattformen `400000` unterstützen. Es kann also nicht einfach eine hohe Geschwindigkeit eingetragen und davon ausgegangen werden, dass sie tatsächlich angewendet wird.

## I2C-Scanner

Ein I2C-Scanner ist ein kleines Programm oder Befehl, das alle Adressen durchläuft und zeigt, welche Geräte am Bus antworten.

Er hilft zu verstehen:

- ob der Controller das Modul erkennt;
- welche Adresse das Gerät hat;
- ob `SDA` und `SCL` vertauscht sind;
- ob Stromversorgung und gemeinsames `GND` vorhanden sind;
- ob ein Adresskonflikt besteht.

Der Scanner beweist jedoch nicht, dass das Gerät vollständig funktioniert. Er zeigt nur, dass unter dieser Adresse jemand antwortet.

## I2C in Klipper

In Klipper wird ein I2C-Gerät mit einem bestimmten MCU verbunden.

Die Konfiguration kann folgende Parameter enthalten:

- `i2c_mcu` - welcher MCU das Gerät angeschlossen ist;
- `i2c_bus` - Hardware-I2C-Bus, falls mehrere vorhanden sind;
- `i2c_software_scl_pin` und `i2c_software_sda_pin` - Software-I2C auf ausgewählten Pins;
- `i2c_address` - Geräteadresse;
- `i2c_speed` - Geschwindigkeit, sofern unterstützt.

Wichtig: `i2c_address` wird in Klipper häufig als Dezimalzahl angegeben, nicht im Hexadezimalformat. Wenn im Datenblatt `0x3C` steht, kann die Konfiguration `60` erfordern.

Ist das Gerät an einen zusätzlichen MCU angeschlossen, muss dieser ebenfalls angegeben werden. Andernfalls sucht Klipper das Gerät auf der Hauptplatine.

## Leitungslänge und Störungen

I2C ist für kurze Verbindungen ausgelegt. Innerhalb eines kleinen Gehäuses oder auf einer Platine ist es komfortabel. In einem 3D-Drucker sind die Bedingungen schlechter:

- Motoren in der Nähe;
- Heizungen in der Nähe;
- lange Leitungen;
- Stecker an Türen;
- Stromleitungen von Lüftern und Heizungen;
- elektromagnetische Störungen.

Praktische Regeln:

- `SDA` und `SCL` kurz halten;
- nahe an `GND` verlegen;
- nicht parallel zu Heizungs-Stromleitungen führen;
- ohne besonderen Grund keine langen Flachbandkabel zu beweglichen Teilen verlegen;
- Geschwindigkeit auf `100 kHz` reduzieren, wenn Fehler auftreten;
- ordentliche Stecker und Zugentlastung verwenden;
- bei langen Verbindungen eine andere Schnittstelle wählen: UART, CAN, RS-485 oder einen lokalen MCU direkt am Sensor.

## Was vor dem Anschluss zu prüfen ist

Vor dem Anschluss eines I2C-Moduls prüfen:

- Modulversorgung;
- Logikpegel;
- auf welchen Pegel `SDA` und `SCL` hochgezogen werden;
- Geräteadresse;
- ob die Adresse geändert werden kann;
- ob ein Konflikt mit anderen Geräten besteht;
- Leitungslänge;
- ob Firmware-Unterstützung vorhanden ist;
- welcher MCU und Bus für das Gerät verwendet wird;
- ob Hardware-I2C oder Software-I2C benötigt wird.

## Typische Fehler

- `SDA` und `SCL` vertauscht;
- gemeinsames `GND` vergessen;
- `5-V`-Pull-ups an einem `3,3-V`-Controller angelegt;
- zwei Geräte haben dieselbe Adresse;
- Hexadezimaladresse angegeben, wo Dezimal erwartet wurde;
- zu lange Leitungen verwendet;
- viele Module mit Pull-up-Widerständen angeschlossen;
- ein von der Firmware nicht unterstütztes Modul gewählt;
- Gerät an einen zusätzlichen MCU angeschlossen, aber `i2c_mcu` nicht angegeben;
- I2C und I2S verwechselt.

## Fazit

I2C ist praktisch für kleine Displays, Sensoren und Hilfsmodule in der Nähe des Controllers. Es erfordert `SDA`, `SCL`, Stromversorgung und gemeinsames `GND`.

Wichtigste Prüfpunkte vor dem Anschluss: Adresse, `3,3-V/5-V`-Pegel, Pull-up-Widerstände, Leitungslänge und Firmware-Unterstützung. In der störungsreichen Druckerumgebung I2C kurz halten.

## Weiterführende Materialien

- [SparkFun: I2C at the Hardware Level](https://learn.sparkfun.com/tutorials/i2c/i2c-at-the-hardware-level) - praktische Erklärung zu `SDA`, `SCL`, Open-Drain-Leitungen und Pull-up-Widerständen.
- [SparkFun: I2C tutorial](https://learn.sparkfun.com/tutorials/i2c/all) - allgemeiner I2C-Leitfaden, Adressen, mehrere Geräte an einem Bus und Hardware-Besonderheiten.
- [Adafruit: STEMMA QT technical specs](https://learn.adafruit.com/introducing-adafruit-stemma-qt/technical-specs) - Beispiel eines standardisierten I2C-Steckverbinders, Pinbelegung, Stromversorgung und `GND`.
- [Adafruit: PCA9548 I2C multiplexer](https://learn.adafruit.com/adafruit-pca9548-8-channel-stemma-qt-qwiic-i2c-multiplexer/pinouts) - Beispiel zur Lösung von doppelten I2C-Adresskonflikten über einen Multiplexer.
- [Klipper Configuration Reference: common I2C settings](https://www.klipper3d.org/Config_Reference.html) - Parameter `i2c_address`, `i2c_mcu`, `i2c_bus`, Software-I2C und `i2c_speed`.
