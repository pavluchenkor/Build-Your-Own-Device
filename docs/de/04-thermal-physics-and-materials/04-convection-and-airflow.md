# Konvektion und Luftstrom

Konvektion ist die Wärmeübertragung durch Luftstrom. In einem Trockner, Druckerkammer, beheiztem Filter oder iHeater-ähnlichem Gerät bestimmt Luft oft, ob Wärme dort ankommt, wo sie benötigt wird.

Ein Heizer selbst konvertiert nur elektrische Leistung in Wärme. Der Lüfter und Luftkanal bestimmen, ob diese Wärme gleichmäßig über die Kammer verteilt ist oder ein kleiner gefährlicher Hotspot bleibt.

## Drei Modi eines Heizers

Derselbe `100 W` Heizer kann völlig unterschiedlich funktionieren.

![Konvektionszellen: warme Luft steigt, kalte fällt](../../../img/04-thermal-physics-and-materials/04-convection-cells.svg)

*Quelle: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Convection_cells.svg), McSush, CC BY-SA 3.0*

Ohne Luftstrom:

- Heizer heizt sich in lokaler Zone stark auf;
- Luft in der Nähe heizt sich auf, aber durchmischt sich schlecht;
- entfernter Kammerteil bleibt möglicherweise kalt;
- Kunststoff, Terminals oder Isolierung in der Nähe können überhitzen;
- Temperatursensor zeigt möglicherweise nicht, was neben dem Heizer passiert.

Mit schwachem oder falschem Luftstrom:

- etwas Wärme geht in Kammer;
- Mischung erfolgt;
- aber Strom kann Heizer umgehen;
- Filter, Sieb oder enger Kanal können Luftstrom sehr reduzieren;
- Hotspots bleiben.

Mit normalem Strom:

- Luft geht durch heiße Zone;
- Wärme entweicht vom Heizer in Kammer;
- Temperatur wird gleichmäßiger;
- PID-Regelung funktioniert vorhersagbarer;
- Nachbarteile überhitzen lokal weniger.

Luftstrom erzeugt keine zusätzliche Leistung. Er hilft, bereits erzeugte Wärme zu entfernen und an den richtigen Ort zu bringen.

## Natürliche und erzwungene Konvektion

Es gibt zwei nützliche Modi:

- natürliche Konvektion - warme Luft steigt von selbst;
- erzwungene Konvektion - Strom wird durch Lüfter, Gebläse oder Zentrifugallüfter erzeugt.

Für kleine beheizte Geräte ist natürliche Konvektion oft unzureichend. Sie ist langsam, hängt von Gehäuseform ab und erzeugt leicht Temperaturzonen.

Erzwungene Konvektion ist normalerweise besser, wenn Sie:

- schnell Wärme vom Heizer entfernen müssen;
- Kammer gleichmäßig heizen;
- Luft durch Filter leiten;
- Filament trocknen;
- Leistungselektronik kühlen;
- Temperatursensor in singhaftem Luftstrom halten.

## Lüfter ist nicht nur Größe

Der Satz "Ich werde einen 40-mm-Lüfter einbauen" sagt Ihnen fast nichts über das Ergebnis.

Für ein echtes Gerät sind wichtig:

- Luftstrom;
- Gegendruck;
- Betriebspunkt nach Installation im Gehäuse;
- Stromrichtung;
- Widerstand von Sieben, Filtern und Luftkanälen;
- Lufttemperatur am Lüfter;
- Lärm und Vibration;
- Ressource unter Last;
- Startstrom;
- Drehzahlzähler oder Regelung.

Der Katalog listet oft maximalen Strom und maximalen Gegendruck auf. In einem echten Gerät arbeitet der Lüfter nicht an diesen idealen Punkten. Filter, Sieb, enger Kanal, Luftkanalwendung und dichter Heizer erzeugen Widerstand, sodass der tatsächliche Strom viel niedriger sein kann.

Wenn Luft durch Filter, Radiator, Wabengitter oder enge Stelle gehen muss, benötigen Sie oft nicht nur "mehr CFM" sondern Lüfter oder Zentrifugalgebläse mit angemessenem Gegendruck.

## Luftweg

Gutes Design antwortet auf vier Fragen:

1. Woher wird Luft gezogen?
2. Was geht sie durch?
3. Wo gibt sie Wärme ab?
4. Wo kehrt sie zurück?

Für Kammer oder Trockner ist geschlossene Zirkulation nützlich:

```text
Kammer -> Lüfter -> Heizer -> heißer Strom -> Kammer -> Rückgabe
```

Für einen Filter kann andere Logik gelten:

```text
Kammer -> Filter -> Lüfter -> Abgas oder Rückgabe
```

Das Wichtigste ist, dass Strom nicht den einfachsten unnützen Weg vorbei am Heizer oder Filter nimmt. Luft wählt immer den Weg mit geringerem Widerstand.

## Temperatursensor muss den richtigen Ort sehen

Schlechte Optionen:

- Sensor ist direkt am Heizer und sieht lokale Überhitzung;
- Sensor ist in toter Zone und sieht kalte Ecke;
- Sensor berührt Metallwand und misst Wand, nicht Luft;
- Sensor ist vor Heizer, obwohl Temperatur danach zählt;
- Sensor wird von Strom geblasen, der nicht Kammertemperatur widerspiegelt.

Für Kammer ist es normalerweise nützlich, Luft zu messen, wo Temperatur steuerbar sein sollte, aber nicht direkt am Heizer. Für Schutz vor Überhitzung neben Heizer ist separater Sensor oder unabhängiger Thermostat/thermischer Cutoff nötig.

Ein Sensor für Regelung und ein unabhängiges Notfallelement ist viel besser als ein Sensor, der für alles verantwortlich ist.

## Filter und Siebe können Strom töten

Ein Filter, Sieb, dekoratives Gitter oder enge Lücke fügt Widerstand hinzu.

Typische Fehler:

- dichter Filter auf schwachem Axiallüfter;
- Hälfte Eingang mit dekorativem Sieb blockiert;
- scharfe Wendung direkt nach Lüfter;
- Heizer so positioniert, dass Luft umgeht;
- vergessen, dass Filter mit Staub verstopft und Widerstand wächst;
- keinen Zugang für Filterwartung gelassen.

Wenn Gerät vom Strom abhängt, überprüfen Sie nicht nur "Lüfter dreht", sondern dass Luft wirklich den richtigen Weg geht.

## Was passiert bei Lüfterausfall

Gefährlichstes Szenario für Heizer mit Luftstrom:

```text
Lüfter gestoppt -> Heizer läuft weiter -> lokale Temperatur steigt schnell
```

Daher benötigt Heizer, der auf Luftstrom verlässt, Maßnahmen:

- unabhängiger Überhitzungsschutz neben heißer Zone;
- Leistungsbegrenzung;
- Material mit Temperaturspielraum;
- Abstand von Heizer zu Kunststoff und Isolierung;
- Lüfter-Drehzahlkontrolle, wenn Lüfter kritisch;
- Firmware-Check für Heizung, wenn Klipper oder ähnlich verwendet;
- erster Test unter Beobachtung.

Firmware hilft, aber ersetzt nicht körperlichen Schutz. MOSFET, SSR oder Relais können im EIN-Zustand ausfallen.

## Minimale Überprüfung nach Montage

Nach Bau eines beheizten Geräts überprüfen:

- Stromrichtung;
- gibt es Strom am Auslass, nicht nur Lüfterdrehung;
- Temperatur am Heizer;
- Temperatur nach Heizer;
- Temperatur in fernem Kammerteil;
- Temperatur von Drähten, Terminals und gedruckten Teilen;
- Temperatur des Lüfters;
- Verhalten bei teilweise blockiertem Filter;
- schaltet Heizung aus, wenn Sensor ausfällt;
- ploppt unabhängiger Überhitzungsschutz in gefährlichem Szenario.

Erste Aufwärmung unter Beobachtung. Messungen sind besser nach Stabilisierung und nach längerer Betrieb, weil Gehäuse, Befestigungen und Isolierung langsamer heizen als Luft.

## Verbindung zu Klipper

In Klipper sind mehrere Mechanismen nützlich:

- `heater_fan` - Lüfter dreht sich mit Heizer oder wenn Temperatur erreicht;
- `temperature_fan` - Lüfter wird von separatem Temperatursensor gesteuert;
- `verify_heater` - überprüft, dass Heizer sich wie erwartet verhält;
- `tachometer_pin` für Lüfter - ermöglicht zu sehen RPM, wenn Lüfter Drehzahlsignal unterstützt.

Dies ist kein komplettes Sicherheitsschema, aber gutes Kontrolllevel für Gerät, wo Temperatur und Strom wichtig sind.

## Wichtigste Erkenntnis

In beheiztem Gerät zählt nicht nur Heizer-Leistung sondern Luftweg. Guter Strom entfernt Wärme vom Heizer und bringt sie in Kammer. Schlechter Strom hinterlässt Hotspot, täuscht Sensor und erhöht Materialgefahr für Überhitzung.

Wenn Heizer auf Lüfter verlässt, muss Lüfterausfall separates Notfallszenario sein, nicht Überraschung.

## Materialien zu diesem Thema

- [Engineering ToolBox: Convective Heat Transfer](https://www.engineeringtoolbox.com/amp/convective-heat-transfer-d_430.html) - Erklärung von natürlicher und erzwungener Konvektion.
- [SANYO DENKI: Fan Airflow and Static Pressure](https://techcompass.sanyodenki.com/en/training/cooling/fan_basic/004/index.html) - warum maximaler Strom und maximaler Druck aus Katalog nicht gleich echtem Gerätebetrieb.
- [SANYO DENKI: Guideline in Selecting a Fan](https://products.sanyodenki.com/info/sanace/en/technical_material/select.html) - praktischer Ansatz zur Lüfterwahl nach Wärmeleistung, Temperaturanstieg und echten Tests.
- [DigiKey: Selecting a Fan](https://www.digikey.com/en/articles/selecting-a-fan) - Unterschied zwischen Axial- und Zentrifugallüftern, Auswirkung von Gehäuse und Stromwiderstand.
- [Klipper Documentation: Configuration Reference](https://www.klipper3d.org/Config_Reference.html) - Parameter für `heater_fan`, `temperature_fan`, `verify_heater` und Lüfter-Drehzahlzähler.

## Siehe auch

- [iDryer-Dokumentation: Lüfter anschließen](../05-practical-guides/01-connecting-a-fan.md) - lokale Anleitung zu Lüfter-Leistung, MOSFET, gemeinsamem GND und Klipper-Beispielen.
