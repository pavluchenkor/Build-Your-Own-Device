# Servomotoren

Ein Servomotor ist ein Motor mit eingebautem Feedback und Regler. Im Gegensatz zu einfachen Motoren, die sich einfach drehen, steuert ein Servo seine Position basierend auf einem Eingangssignal.

In iDryer-ähnlichen Geräten werden Servos verwendet, um Positionen zu steuern: Klappen, Verschlüsse, Umlenker oder andere mechanische Elemente.

## Wo es verwendet wird

In iDryern und ähnlichen Geräten:

- Filament-Drossel oder Schieber;
- Lufttür oder Klappe;
- Umlenker oder Lenker;
- Spulen-Drehvorrichtung (selten);
- Notverschluss.

Servos sind praktisch für diskrete Positionen: offen/geschlossen, Position A/B/C.

## Servo-Grundlagen

Ein typischer Servo hat:

- Stromversorgungsleitung (z.B. `5V` oder `6V`);
- Masseleitung;
- Steuersignal-Leitung (PWM).

Das Steuersignal ist ein PWM-Signal mit einer spezifischen Pulsbreite:

- etwa `1 ms` - eine Extremposition (z.B. 0°);
- etwa `1,5 ms` - Mittelposition (z.B. 90°);
- etwa `2 ms` - andere Extremposition (z.B. 180°).

Die Frequenz ist normalerweise etwa `50 Hz`.

Verschiedene Servos können unterschiedliche Bereiche haben. Überprüfen Sie das Datenblatt.

## Servo-Spannungen und Strom

Überprüfen Sie:

- Betriebsspannung;
- Ruhestrom (wenn nicht in Bewegung);
- aktive Bewegungsstrom;
- Spitzenstrom (beim Anfahren unter Last);
- maximales Drehmoment;
- Geschwindigkeit;
- Betriebstemperaturbereich;
- Verdrahtung und Stecker.

Ein kleiner 5V-Servo kann `100 mA` im Ruhezustand und `500 mA` unter Last ziehen. Mehrere Servos können bedeutende Stromspitzen erzeugen.

Die Stromversorgung muss stabil sein. Ein Spannungsabfall kann dazu führen, dass der Servo zittert oder falsch positioniert wird.

## PWM-Steuerung

Das PWM-Steuersignal wird normalerweise von einem Mikrocontroller erzeugt.

In Klipper / KLIPPER-basierten Systemen:

```
[servo my_servo]
pin: PE5
minimum_pulse_width: 0.001
maximum_pulse_width: 0.002
```

Bei `0.001` = 1 ms (eine Extremposition) und `0.002` = 2 ms (andere Extremposition).

Einige Servos haben andere Bereiche. Überprüfen Sie das Datenblatt oder experimentieren Sie mit dem Bereich.

## Mechanische Befestigung

Servos haben verschiedene Befestigungsmethoden:

- Befestigungslöcher für Schrauben;
- Klemmleisten;
- Adapter und Gelenkstücke.

Die Befestigung muss stabil sein. Ein locker montierter Servo kann zittern oder nicht genau positionieren.

## Drehmoment und Last

Das Servomaximaldr drehmoment ist in `kg·cm` oder `N·cm` angegeben.

Überprüfen Sie:

- Erforderliches Drehmoment für die Last;
- Hebelarm und Kraft;
- ob die Last gleichmäßig oder plötzlich ist;
- Vibrationen und Resonanz.

Ein Servo mit zu wenig Drehmoment wird zittern und nicht die Position halten.

## Verschleiß und Lebensdauer

Servos haben Zahnräder und Lager. Bei häufiger Bewegung oder Überlast können sie verschleißen.

Überprüfen Sie:

- Betriebszyklen;
- Lebensdauer des Herstellers;
- Lagerverschleiß bei häufiger Bewegung;
- thermische Grenzen bei langer Aktivierung.

Für häufige Bewegungen ist ein robuster Servo mit Metallgetriebe besser als einer mit Kunststoffgetrieben.

## Was vor dem Kauf zu überprüfen ist

Vor dem Kauf eines Servos überprüfen Sie:

- Betriebsspannung;
- Strom (Ruhezustand und Bewegung);
- Maximaldrehmoment;
- Betriebsbereich (normalerweise etwa 180°);
- Geschwindigkeit;
- Größe und Form;
- Befestigungsmethode;
- Steckertyp;
- Betriebstemperaturbereich;
- Metallgetriebe oder Kunststoffgetriebe;
- Verfügbarkeit des Datenblatts.

Für ein Gerät, das lange läuft: ein robuster Servo mit Metallgetriebe.

## Typische Fehler

- Servo an falsche Spannung angeschlossen;
- PWM-Frequenz falsch eingestellt;
- Steuersignal falsch verdrahtet (kein gemeinsames GND);
- PWM-Pulsbreite außerhalb des Bereichs;
- Servo unter Überlast;
- zu schwaches Drehmoment für die Anwendung;
- Servo nicht mechanisch stabil befestigt;
- Servo bei hoher Spannung zitternd;
- Servo bei niedriger Spannung schwach oder nichtfunktionsfähig;
- mehrere Servos an einen schwachen Stromausgang angeschlossen.

## Hauptpunkt

Ein Servo steuert Position über PWM. Überprüfen Sie die PWM-Frequenz und Pulsbreite, die Stromversorgung, das Drehmoment und die mechanische Befestigung. Ein stabiler Servo mit genug Drehmoment und ausreichend Stromversorgung ist zuverlässiger.

## Referenzmaterialien

- [Arduino: Servo Library](https://www.arduino.cc/reference/en/libraries/servo/) - Arduino-Servo-Steuerung, PWM-Bereiche, typische Pulsweitenwerte.
- [Klipper Configuration Reference: Servo](https://www.klipper3d.org/Config_Reference.html#servo) - Klipper-Servo-Steuerung, minimum/maximum_pulse_width.
- [Spektrum: RC Servo Specifications](https://www.spektrumrc.com/howto/ars-rc-servo-specifications-explained/) - Servo-Spezifikationen, Drehmoment, Geschwindigkeit, PWM-Bereiche.
