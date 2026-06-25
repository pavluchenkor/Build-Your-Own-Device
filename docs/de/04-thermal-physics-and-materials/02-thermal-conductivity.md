# Wärmeleitung

Die Wärmeleitung zeigt, wie leicht ein Material Wärme durch sich selbst überträgt.

Für einen selbstgebauten Trockner, eine Kammer, einen Filter, einen Luftkanal oder ein Gehäuse ist dies keine abstrakte Physik. Die Wärmeleitung bestimmt, ob Wärme nach außen entweicht, ob ein Hotspot neben dem Heizer entsteht, wie heiß die Außenwand wird und ob ein gedrucktes Teil erweichen wird.

## Einfache Idee

Wärme neigt immer dazu, von einer heißeren Zone zu einer kälteren zu entweichen. Je höher die Wärmeleitung eines Materials, desto leichter geht Wärme hindurch.

Die Wärmeübertragungsgeschwindigkeit wird beeinflusst durch:

- Material;
- Wanddicke;
- Kontaktfläche;
- Temperaturdifferenz;
- Kontaktqualität zwischen den Teilen;
- Vorhandensein von Luft, Spalten und Isolierung.

Eine dünne Aluminiumplatte kann Wärme schnell im ganzen Gehäuse verteilen. Eine dicke Schicht Mineralwolle oder Schaumisolierung hingegen verhindert, dass Wärme entweicht.

## Referenzwerte für Materialien

Die folgenden Werte sind nur zum Verständnis von Größenordnungen. Für einen echten Bau überprüfen Sie das Datenblatt des spezifischen Materials.

| Material | Ungefähre Wärmeleitung, `W/(m*K)` | Was dies praktisch bedeutet |
| --- | ---: | --- |
| Kupfer | etwa `400` | ausgezeichneter Wärmeleiter, für Wärmeableitung geeignet, aber leitet Wärme schnell dorthin, wo sie nicht immer nötig ist |
| Aluminium | etwa `200-240` | verteilt Wärme gut, nützlich als Platte, Radiator oder Wärmeverteiler |
| Stahl | etwa `15-60` | leitet Wärme schlechter als Aluminium, aber Schrauben und Posten können immer noch thermische Brücken sein |
| Glas | etwa `1` | leitet Wärme viel schlechter als Metall, ist aber nicht im konventionellen Sinne eine Isolierung |
| Allgemeiner Kunststoff | etwa `0,1-0,5` | leitet Wärme schlecht, kann aber erweichen und entflammbar sein |
| Mineralwolle, Fiberglas | etwa `0,04` | reduziert Wärmeverlust wirksam, benötigt aber Schutz vor Staub, Feuchtigkeit und mechanischen Beschädigungen |
| Expandiertes Polystyrol / Polyurethan-Schaum | etwa `0,03` | gute Isolierung, aber in der Nähe von Wärme sind Betriebstemperatur und Brandeigenschaften wichtig |
| Luft | etwa `0,026` | leitet Wärme selbst schlecht, überträgt aber Wärme durch Konvektion, wenn sie sich bewegt |

Die Haupterkenntnis: Metall und Isolierung unterscheiden sich nicht um einen Faktor von zwei, sondern um Größenordnungen. Daher kann selbst ein kleines Metallteil das thermische Bild erheblich verändern.

## Wärmebrücke

Eine Wärmebrücke ist ein Pfad, durch den Wärme leichter entweicht als durch den Rest der Struktur.

![Klassische Wärmebrücke durch ein Gehäuse](../../img/04-thermal-physics-and-materials/02-thermal-bridge-classic.png)

*Quelle: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Pont_thermique_classique.png), AmisDeLaThermique, CC BY-SA 3.0*

Typische Wärmebrücken:

- Metallschraube durch eine isolierte Wand;
- Aluminiumplatte verbunden mit dem äußeren Gehäuse;
- Metallposten zwischen heißer Kammer und äußerem Bedienfeld;
- Terminalblock oder Befestigung neben dem Heizer;
- Luftkanal, der direkt ein heißes Teil berührt.

Eine Wärmebrücke ist nicht immer schlecht. Manchmal ist sie nötig, um Wärme von einem Stromschalter, Radiator oder heißem Knoten abzuleiten. Das Problem beginnt, wenn die Brücke zufällig ist: Die Kammer verliert Wärme, die Außenfläche wird heiß und Kunststoff neben der Brücke heizt sich mehr als erwartet auf.

## Metall: Wärmesenke oder Unbeabsichtigtes Heizen

Metall ist bequem in beheizten Geräten zu verwenden:

- als Schirm zwischen Heizer und Kunststoff;
- als Wärmeverteilungsplatte;
- als Basis für Heizerhalterung;
- als Radiator für Leistungselektronik;
- als nicht brennbare innere Oberfläche.

Aber Metall macht ein Gerät nicht automatisch sicher. Wenn eine Metallplatte eine heiße Zone und das äußere Gehäuse berührt, kann sie Wärme nach außen leiten. Wenn Kunststoff daran verschraubt ist, kann dieser Kunststoff durch die Befestigung aufheizen. Wenn Sie mit dem Gerät durchgehen, benötigen Sie in der Nähe der Kante Durchführungen, Schutz vor Abschürfung und Temperaturspielraum für die Isolierung.

## Isolierung: Weniger Verlust, Mehr Verantwortung

Isolierung reduziert Wärmeverlust, beseitigt aber nicht die Temperaturregelung.

Wenn Sie eine Kammer isolieren:

- ist es für den Heizer leichter, die Temperatur zu erhöhen;
- das Gehäuse kann auf der Außenseite kälter werden;
- die Kühlzeit erhöht sich;
- die lokale Temperatur neben dem Heizer kann steigen;
- Lüfterausfall oder festsitzender Schalter wird gefährlicher.

Daher kann die Isolierung nicht als „Verbesserung“ hinzugefügt werden, ohne sie erneut zu testen. Nach der Isolierung müssen Sie die Temperaturen in der Kammer, am Heizgerät, an den Drähten, an den Anschlüssen und auf der Außenfläche erneut messen.

## Luftspalt funktioniert auch

Statische Luft leitet Wärme schlecht. Daher können Luftspalte, Doppelwände und Schäumaterialien die Wärmeübertragung reduzieren.

Aber wenn Luft anfängt zu fließen, beginnt die Konvektion. Dann wird Wärme durch den Luftstrom übertragen, nicht nur durch Wärmeleitung. Daher kann ein Spalt, durch den ein heißer Strom fließt, das Gehäuse mehr aufheizen als eine dicke Wand ohne Fluss.

In der Praxis bedeutet stirbt:

- lassen Sie keine versehentlichen Spalten neben dem Heizer;
- richten Sie keinen heißen Strom direkt auf Kunststoff;
- behandeln Sie Luftspalte nicht als Schutz, wenn ein Strom durch sie fließt;
- überprüfen Sie die Temperatur im echten Betriebsmodus, nicht nur an einem kalten Gerät.

## Was man im Datenblatt des Materials nachschlagen sollte

Für Material in der Nähe von Wärme ist Wärmeleitung nicht das Einzige, das wichtig ist.

Überprüfen Sie:

- maximale Dauerbetriegstemperatur;
- Erweichungstemperatur oder Wärmeverformungstemperatur;
- Entflammbarkeit und Brandverhaltenklasse;
- Zulässigkeit des Kontakts mit heißer Luft;
- Verhalten von Klebeschicht, Folie, Beschichtung oder Laminierung;
- Herstellerempfehlungen für die Verwendung;
- Verfügbarkeit von SDS/Sicherheitsdatenblatt, wenn das Material heiß werden oder verarbeitet werden kann.

Wenn ein Material keine klare Dokumentation hat, stellen Sie es nicht in die Nähe des Heizgeräts und verwenden Sie es nicht als einzigen Schutz.

## Praktische Überprüfungsreihenfolge

Für Gehäuse, Kammer oder Trockner ist es bequem, wie folgt vorzugehen:

1. Identifizieren Sie die heiße Zone: Heizer, Luftauslass, Terminals, Stromschalter.
2. Trennen Sie die heiße Zone mit Metall, Keramik oder einem anderen geeigneten Material vom Kunststoff.
3. Überprüfen Sie, wohin das Metall Wärme leitet.
4. Fügen Sie Isolierung nur dort hinzu, wo sie keine gefährlichen heißen Knoten verdeckt.
5. Messen Sie die Temperatur nach der Wärmung an mehreren Stellen.
6. Überprüfen Sie den Lüfterausfallmodus, wenn der Heizer vom Luftstrom abhängt.
7. Fügen Sie unabhängigen Überhitzungsschutz dort hinzu, wo Überhitzung gefährlich ist.

Ein Temperatursensor in der Kammer zeigt nicht das gesamte thermische Bild. Sie benötigen Messungen neben dem Heizgerät, auf Befestigungen, auf Drähten, am Gehäuse und auf gedruckten Teilen.

## Wichtigste Erkenntnis

Wärmeleitung hilft Ihnen zu verstehen, wohin Wärme wirklich geht. Metall kann eine nützliche Wärmesenke oder eine unbeabsichtigte Wärmebrücke sein. Isolierung kann die Effizienz verbessern, aber gleichzeitig die Folgen eines Ausfalls verstärken.

Jede Änderung am Gehäuse, an der Isolierung, an Befestigungen oder am Luftkanal muss durch Temperaturmessung im echten Betriebsmodus überprüft werden.

## Materialien zu diesem Thema

- [Engineering ToolBox: Thermal Conductivity of Common Materials](https://www.engineeringtoolbox.com/thermal-conductivity-d_429.html) - Referenzwerte der Wärmeleitung für Metalle, Kunststoffe, Luft, Glas und Isolierung.
- [Engineering ToolBox: Conductive Heat Transfer](https://www.engineeringtoolbox.com/conductive-heat-transfer-d_428.html) - Beziehung zwischen Wärmefluss, Material, Wanddicke, Fläche und Temperaturdifferenz.
- [NASA Glenn Research Center: Heat Transfer](https://www1.grc.nasa.gov/beginners-guide-to-aeronautics/heat-transfer-3/) - grundlegende Erklärung der Wärmeübertragung vom heißen Körper zum kalten.
- [U.S. Department of Energy: Principles of Heating and Cooling](https://www.energy.gov/energysaver/principles-heating-and-cooling) - einfache Erklärung von Wärmeleitung, Konvektion, Strahlung und Rolle der Isolierung.
- [Prusa Knowledge Base: Material table](https://help.prusa3d.com/materials) - praktische Referenz für Temperaturverhalten beliebter 3D-Druckmaterialien.
