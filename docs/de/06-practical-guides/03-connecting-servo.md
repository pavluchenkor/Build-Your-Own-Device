# Servo anschließen

Ein Servo ist ein kleiner Motor mit Getriebe und Steuerelektronik. Du kannst ihm sagen, in welcher Position sich die Welle drehen soll.

Bei Geräten wie iDryer kann ein Servo eine Klappe öffnen, einen kleinen Riegel bewegen, einen mechanischen Schalter betätigen oder den Luftstrom umleiten.

Der Hauptfehler bei Servos: Die Annahme, dass es eine „kleine Sache" ist und du sie von einem beliebigen 5V-Pin des Controllers versorgen kannst. Ein Servo kann besonders beim Start, bei plötzlichen Bewegungen oder wenn der Mechanismus festsitzt erheblichen Strom ziehen.

## Drei Drähte

Ein typisches Hobby-Servo hat drei Drähte:

- Stromversorgung: normalerweise `5V` oder `6V`;
- Masse: `GND`;
- Signal: Steuerpulse vom Controller.

Häufige Farben:

- rot - Stromversorgung;
- schwarz oder braun - Masse;
- gelb, orange oder weiß - Signal.

Du kannst dich aber nicht blindlings auf Farben verlassen. Verschiedene Hersteller verwenden möglicherweise unterschiedliche Farbschemen. Vor dem Anschließen überprüfe die Markierung, Produktseite oder das Datenblatt.

## Stromversorgung getrennt, Signal getrennt

Der Signaldraht versorgt das Servo nicht mit Strom. Er teilt dem Servo nur mit, wohin es sich drehen soll.

Das Servo bezieht Energie vom Stromversorgungsdraht.

Die richtige Logik ist:

- der Controller liefert nur das Steuersignal;
- das Servo wird von einer 5V/6V-Quelle versorgt, die seinen Strom bewältigen kann;
- der Controller-GND und der Servo-Stromversorgungs-GND sind verbunden.

![Servo-Drahtkodierung](../../img/03-common-components/06-servo-color-code.jpg)

*Quelle: [SparkFun Electronics](https://learn.sparkfun.com/tutorials/hobby-servo-tutorial/all), CC BY-SA 4.0*

## Warum du nicht von schwachem 5V versorgen kannst

Viele Boards haben einen 5V-Pin. Das bedeutet nicht, dass ein Servo sicher von ihm versorgt werden kann.

Beim Bewegen kann ein Servo viel mehr Strom ziehen, als seine Größe vermuten lässt. Wenn die Stromversorgung unzureichend ist, erscheinen typische Symptome:

- Controller startet neu;
- Bildschirm flimmert;
- USB-Verbindung bricht ab;
- Servo zuckt;
- Wi-Fi auf ESP32 fällt ab;
- Servo brummt, aber bewegt sich nicht;
- Spannungseinbruch beim Bewegungsstart.

Für ein kleines Servo funktioniert die vom Board gelieferte Stromversorgung manchmal, wenn das Board und die Quelle explizit für diesen Strom ausgelegt sind. Aber für ein echtes Gerät mit Klappe, Riegel oder Mechanismus ist es besser, eine separate 5V/6V DC-DC oder Stromversorgung mit Sicherheitsspanne zu verwenden.

## Gemeinsame Masse

Wenn das Servo von einer separaten Quelle versorgt wird, wird eine gemeinsame Masse benötigt.

Ohne gemeinsame Masse haben der Controller und das Servo kein gemeinsames Signalniveau. Das Servo kann nicht reagieren, zucken oder sich zufällig verhalten.

Einfache Verbindung:

1. `+5V` oder `+6V` von der Stromquelle geht zur Servo-Stromversorgung.
2. `GND` von der Stromquelle geht zur Servo-Masse.
3. Der Controller-GND ist mit derselben Masse verbunden.
4. Der Controller PWM/GPIO-Pin geht zum Servo-Signaldraht.

Servo-Stromversorgung und Controller-Stromversorgung können unterschiedlich sein, aber die Masse muss gemeinsam sein.

## Welches Signal erforderlich ist

Ein typisches Positions-Hobby-Servo wird durch Pulse gesteuert.

Typisches Signal:

- Puls etwa alle `20 ms`;
- etwa `1 ms` - eine Extreme des Bereichs;
- etwa `1.5 ms` - Mitte;
- etwa `2 ms` - andere Extreme des Bereichs.

Dies ist kein typisches PWM für LED-Helligkeit oder Lüfterdrehzahl. Hier ist die Pulsbreite in Mikrosekunden wichtig.

Die tatsächlichen Grenzen eines bestimmten Servos können unterschiedlich sein. Einige arbeiten sicher nicht von 0 bis 180 Grad, sondern weniger. Daher erfordern Extrempositionen sorgfältige Tests.

## Servo nicht gegen den Mechanismus klemmen

Ein Servo versucht, die befohlen Position beizubehalten.

Wenn eine Klappe gegen das Gehäuse stößt, ein Arm festsitzt oder der Mechanismus einen physischen Stopp erreicht, bevor der Befehl endet, drückt das Servo weiter. An diesem Punkt steigt der Strom, der Motor heizt sich auf, das Getriebe verschleißt.

Dies ist besonders kritisch für Klappen und Riegel.

Vor dem Dauerbetrieб überprüfe:

- der Mechanismus bewegt sich frei über den gesamten Bereich;
- keine Fehlausrichtung;
- keine Bindung von Gelenken;
- das Servo brummt nicht in der Endposition;
- extremer Winkel in der Firmware erzwingt den Mechanismus nicht in einem Stopp;
- bei ausgeschalteter Stromversorgung bleibt das Gerät sicher oder kehrt über Feder zurück, wie beabsichtigt.

Wenn ein Servo im Ruhezustand brummt, signalisiert dies oft Last, einen Stopp oder falsche Hebelgeometrie.

## Start- und Blockierstrom

Ein Servo hat normalen Betriebsstrom und Strom, wenn die Welle blockiert ist. Letzteres wird oft Blockierstrom genannt.

Blockierstrom tritt auf, wenn das Servo versucht, sich zu bewegen, aber die Welle blockiert oder der Mechanismus zu schwer ist.

Dieser Modus verursacht oft:

- Spannungseinbruch;
- Controller-Neustart;
- Drahtwärmung;
- DC-DC-Überhitzung;
- Getriebebruch.

Wenn das Datenblatt den Blockierstrom auflistet, wähle die Stromversorgung unter Berücksichtigung dieses Wertes und einer Sicherheitsspanne. Wenn es kein Datenblatt gibt, kannst du nicht davon ausgehen, dass ein Servo sicher auf „Sicht" läuft.

## Kondensator neben dem Servo

Manchmal hilft ein Elektrolyt-Kondensator zwischen `+5V` und `GND` neben dem Servo.

Es ersetzt keine ordnungsgemäße Stromversorgung, kann aber einen kurzen Einbruch beim Bewegungsstart glätten.

Für ein kleines Servo: Hunderte von Mikrofarad, wie `470 uF` oder mehr, mit Spannungsklasse über der Versorgungsspannung.

Die Polarität des Elektrolyt-Kondensators ist wichtig:

- Kondensator Plus zu `+5V`;
- Kondensator Minus zu `GND`.

Wenn das Gerät zuverlässig sein muss, wähle zuerst die richtige Stromversorgung und Verdrahtung, dann verwende einen Kondensator als zusätzliche Maßnahme.

## Beispiel-Klipper-Konfiguration

In Klipper wird ein Servo mit einem `[servo]`-Abschnitt beschrieben.

Beispiel:

```ini
[servo chamber_damper]
pin: PA8
maximum_servo_angle: 180
minimum_pulse_width: 0.001
maximum_pulse_width: 0.002
initial_angle: 90
```

Befehle:

```gcode
SET_SERVO SERVO=chamber_damper ANGLE=0
SET_SERVO SERVO=chamber_damper ANGLE=90
SET_SERVO SERVO=chamber_damper ANGLE=180
```

Pin-Namen hier sind typisch. Überprüfe in einem echten Gerät deinen Board-Pinout.

Bei der Mechanik beginne nicht gleich mit `0` und `180`. Teste zuerst einen sicheren Bereich wie `60`, `90`, `120`, dann erweitere die Winkel.

## Beispiel-Arduino/ESP32-Logik

Der Arduino-Ansatz verwendet normalerweise die Servo-Bibliothek:

```cpp
#include <Servo.h>

Servo damper;

void setup() {
  damper.attach(9);
  damper.write(90);
}

void loop() {
}
```

Dies ist nur ein Beispiel der Signallogik. Die Servo-Stromversorgung muss immer noch separat ausgelegt werden. Auch wenn der Signaldraht mit Arduino oder ESP32 verbunden ist, darf der Servo-Motor die Controller-Stromversorgung nicht überlasten.

## Was nach dem Anschließen zu überprüfen ist

Vor dem Einbau im Gehäuse:

- Servo empfängt die richtige Spannung;
- Stromquelle kann Servo-Strom bewältigen;
- Controller-Masse und Servo-Masse sind gemeinsam;
- Signaldraht ist mit dem richtigen Pin verbunden;
- Servo bewegt sich in die richtige Richtung;
- extreme Winkel beschädigen den Mechanismus nicht;
- Mechanismus sitzt nicht fest;
- Servo brummt nicht kontinuierlich;
- Drähte fangen nicht an Hebel oder Zahnrädern;
- Spannungseinbruch nach Bewegung tritt nicht auf;
- Controller startet nicht neu.

Teste die Mechanik unbelastet und unter echten Bedingungen. Eine Klappe, die von Hand leicht zu bewegen ist, kann nach dem Einbau im Gehäuse festsitzen.

## Häufige Fehler

- Servo von GPIO versorgen;
- Servo von schwachem 5V Board Pin versorgen;
- gemeinsame Masse vergessen;
- Drahfarben blind vertrauen;
- Stromversorgung falsch herum anschließen;
- zu dünne Drähte verwenden;
- Start- und Blockierstrom nicht berücksichtigen;
- Servo gegen mechanischen Stopp zwingen;
- Winkel `180` oder `180` verwenden, wenn der echte Mechanismus sicher nur in kleinerem Bereich läuft;
- Servo in der Nähe von Wärme montieren, ohne Betriebstemperatur zu überprüfen;
- kontinuierliches Rotations-Servo als reguläres Positions-Servo behandeln.

## Wichtigste Punkte

- Ein Servo hat drei Leitungen: Stromversorgung, Masse und Signal.
- Signal versorgt das Servo nicht mit Strom.
- Echte Geräte benötigen oft eine separate 5V/6V-Stromversorgung.
- Servo-Masse und Controller-Masse müssen gemeinsam sein.
- Die gefährlichste Last ist Blockierung oder mechanische Bindung.
- Extreme Winkel erfordern sorgfältige Auswahl, nicht sofortiges `0` und `180`.
- Wenn der Controller neu startet, wenn sich das Servo bewegt, überprüfe zuerst die Stromversorgung und gemeinsame Masse.

## Weiterführende Lektüre

- [Klipper Configuration Reference: Servo](https://www.klipper3d.org/Config_Reference.html#servo) - offizieller `[servo]`-Abschnitt, `SET_SERVO`, Winkel und Pulsbreite.
- [SparkFun: Hobby Servo Tutorial](https://learn.sparkfun.com/tutorials/hobby-servo-tutorial/introduction) - grundlegende Erklärung von Hobby-Servo, drei Drähten und Pulssteuerung.
- [SparkFun: Servo Trigger Hookup Guide](https://learn.sparkfun.com/tutorials/servo-trigger-hookup-guide/servo-motor-background) - Aufschlüsselung der Stromverbindung, typische Drahfarben und Hobby-Servo-Mechanik.
- [Adafruit: Arduino Lesson 14. Servo Motors](https://learn.adafruit.com/adafruit-arduino-lesson-14-servo-motors?view=all) - praktisches Beispiel der Verbindung, Spannungseinbruch-Verhalten und Kondensator neben dem Servo.
- [Arduino Servo Library Reference](https://www.arduino.cc/reference/en/libraries/servo/) - offizielle Servo-Bibliothek für Arduino-Ansatz.
