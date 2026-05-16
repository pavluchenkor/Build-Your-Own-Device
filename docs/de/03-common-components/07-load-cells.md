# Wägezellen

Eine Wägezelle ist ein Sensor, der Gewicht oder Kraft misst. Sie wird häufig mit einem HX711-Verstärker verwendet, um digitale Werte für einen Mikrocontroller bereitzustellen.

In iDryer-ähnlichen Geräten werden Wägezellen verwendet, um das Filamentgewicht zu überwachen: Überprüfung des Filament-Status, Erfassung von leeren Spulen oder Wiegen des getrockneten Filaments.

## Wo es verwendet wird

In Dryern und Peripheriegeräten:

- Filament-Gesamtgewicht;
- verbrauchte Filament-Menge;
- Spulen-Status (voll/leer);
- Gewichtskalibrierung oder Kalibrierprotokolle.

Eine Wägezelle mit bekannter Kalibrierung kann Gewicht mit Genauigkeit von wenigen Grammen messen.

## Wägezellen-Typen und Nennwerte

Typische Wägezellen für 3D-Drucker:

- `50 kg` - für große Spulen;
- `10 kg` - für Standardspulen;
- `5 kg` - für kleine Spulen oder teilweise Gewichtskontrolle.

Die Einheit ist normalerweise in `kg` oder `lbs`.

Überprüfen Sie:

- Bereich (z.B. 0-50 kg);
- Genauigkeit;
- Ausgangsempfindlichkeit (mV/V);
- Materialkonstruktion (Aluminium, Stahl);
- Verdrahtung und Stecker.

Für Filament braucht es nicht extrem genaue Wägezellen. Eine billige `10 kg`-Wägezelle mit etwa `±50 g` Fehler ist ausreichend.

## HX711 Verstärker

Der HX711 ist ein beliebter Verstärker für Wägezellen. Er konvertiert das kleine mV-Signal der Wägezelle in digitale Werte.

Verbindung:

- `E+` (Stromversorgung) zum Stromversorgungs-positiv;
- `E-` (Referenzspannung) zu GND;
- `A+`/`A-` oder `B+`/`B-` - je nach Kanal;
- `GND` - zu Masse des Controllers;
- `DT` (Daten) - zu GPIO des Controllers;
- `SCK` (Takt) - zu GPIO des Controllers.

Der HX711 benötigt Stromversorgung. Die digitale Schnittstelle kann von `5V`- oder `3.3V`-Logik gesteuert werden, aber die Stromversorgung sollte stabil sein.

## Kalibrierung

Ein HX711 funktioniert nicht ohne Kalibrierung.

Kalibrierungsprozess:

1. Sensor mit bekanntem Gewicht lesen (z.B. 0 ohne Last, 5 kg mit bekanntem Gewicht);
2. ADC-Rohwerte aufzeichnen;
3. Kalibrierungsfaktoren berechnen;
4. In der Firmware speichern oder in EEPROM.

Beispiel:

```
Rohwert ohne Last: 0
Rohwert mit 5 kg: 10000
Kalibrierungsfaktor = 10000 / 5 = 2000 pro kg
```

Dann wird ein beliebiger Rohwert in Gewicht konvertiert: `Gewicht = Rohwert / 2000`.

Die Kalibrierung kann sich mit Temperatur ändern. Für genaue Messungen kann eine Temperaturkompensation erforderlich sein.

## Mechanische Montage

Die Wägezelle muss mechanisch korrekt montiert werden, um genaue Messungen zu erhalten.

Überprüfen Sie:

- die Spule sitzt zentriert auf der Wägezelle;
- die Belastung ist vertikal (nicht schräg);
- die Wägezelle wird nicht verdreht;
- keine zusätzliche horizontale Kraft;
- Vibrationen werden minimiert.

Eine falsch montierte Wägezelle gibt fehlerhafte oder unstabile Messwerte.

## Spule und Belastungsverteilung

Wenn Sie eine asymmetrische Last (z.B. Filament auf einer Seite einer Spule) haben, kann die Messung instabil sein.

Für stabilere Messungen:

- ein symmetrisches Design bevorzugen;
- mehrere Wägezellen verwenden (eine an jedem Lager);
- mechanische Führungen, um Bewegungen zu minimieren.

Eine Wägezelle kann nur vertikale Kräfte gut messen.

## Störung und Filterung

Ein HX711 kann EMI von Motoren, Heizern oder PWM-Signalen aufnehmen.

Maßnahmen:

- HX711 in der Nähe des Controllers montieren;
- Verdrahtung von HX711 und Wägezelle kurz und verdrillt;
- GND-Sternpunkt verwenden;
- Firmware-Filter: gleitender Durchschnitt oder Medianfilter auf die Rohwerte anwenden.

Eine digitale Filterung in der Firmware kann Messungen stabiler machen.

## Was vor dem Kauf zu überprüfen ist

Vor dem Kauf überprüfen Sie:

- Bereich und Nenngewicht;
- Ausgangsempfindlichkeit (mV/V);
- Material und Konstruktion;
- Verdrahtung und Steckertyp;
- ob es bereits einen HX711 hat oder nur der Sensor;
- Verfügbarkeit von Kalibrierdaten;
- ob der HX711-Breakout einzeln oder mit Wägezelle kommt.

Für ein einfaches Projekt: ein günstiges Set mit `10 kg`-Wägezelle und HX711 Breakout.

## Typische Fehler

- Wägezelle an falsche Spannung angeschlossen;
- HX711 nicht kalibriert;
- Wägezelle nicht zentriert montiert;
- zusätzliche horizontale Kräfte auf die Wägezelle;
- Verdrahtung nicht verdrillt, EMI-Störung;
- fehlende oder falsche GND-Verbindung;
- mehrere Wägezellen ohne separate Verstärker;
- Firmware liest ADC direkt statt über HX711 I2C/SPI.

## Hauptpunkt

Eine Wägezelle mit HX711 kann zuverlässiges Gewicht messen mit Kalibrierung. Mechanische Montage und Verdrahtung sind genauso wichtig wie der Sensor selbst. Digitale Filterung in der Firmware kann Messungen stabilisieren.

## Referenzmaterialien

- [HX711 Datasheet](https://www.avia-semiconductor.com/en/HX711-pdf.html) - offizielle Spezifikationen, Pinbelegung, Schnittstelle.
- [SparkFun: Load Cell Amplifier HX711 Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide) - praktisches Beispiel, Kalibrierungscode, Firmware-Beispiele.
- [Arduino: HX711 Library](https://github.com/bogde/HX711) - Arduino-Bibliothek für HX711, Kalibrierungscode.
