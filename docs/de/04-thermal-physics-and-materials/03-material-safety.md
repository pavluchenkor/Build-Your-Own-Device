# Materialien, Entflammbarkeit und schädliche Emissionen

Material für Kammer, Trockner, Filter, Gehäuse oder Luftkanal kann nicht nur nach Preis, Dicke und Schneideleichtigkeit ausgewählt werden.

In einem beheizten Gerät muss Material nicht nur den normalen Betrieb aushalten, sondern auch angemessene Ausfälle: Lüfterstopp, Sensorfehler, festsitzender Schalter, schlechter Kontakt, überhitztes Terminal oder lokalisierter heißer Strom.

## Was "zum Heizen geeignet" bedeutet

Material ist nicht deshalb geeignet, weil es "nicht sofort schmilzt". Für ein beheiztes Gerät sind mehrere verschiedene Eigenschaften wichtig:

- maximale Dauerbetriegstemperatur;
- Erweichungstemperatur oder Wärmeverformungstemperatur;
- Entflammbarkeit;
- Rauchentwicklung;
- Toxizität von Verbrennungsprodukten;
- Widerstand von Klebstoff, Folie, Beschichtung oder Laminierung;
- Verhalten beim Kontakt mit heißer Luft;
- Herstelleranforderungen für die Montage.

Die Schmelztemperatur allein ist fast nutzlos. Kunststoff kann lange vor dem Schmelzen steif werden und Form verlieren. Isolierung kann ihre Abmessungen ändern. Klebstoff kann abplatzen. Ein gedrucktes Teil kann sich unter Last verformen.

## Betriebstemperatur und Sicherheitsspielraum

Zunächst müssen Sie verstehen, was die Temperatur nicht "im Durchschnitt in der Kammer" sein wird, sondern an bestimmten Orten:

- neben dem Heizer;
- am heißen Luftauslass;
- neben Terminals und Drähten;
- auf Metallfasteners;
- auf innerer Wand;
- auf gedruckten Teilen;
- unter Isolierung;
- auf Außenfläche.

Wenn die Kammer `45°C` hält, bedeutet das nicht, dass alle Teile innen auch `45°C` sind. Neben dem Heizer oder in der Luftleitung kann es viel heißer sein.

Praktische Regel: Material muss einen Sicherheitsspielraum für die Dauerbetriegstemperatur genau am Ort haben, an dem es sich befindet. Für Zone neben Heizer muss der Spielraum größer sein als für äußeres dekoratives Panel.

## Entflammbarkeit - Es ist nicht ein Wort

Die Dokumentation kann verschiedene Klassifizierungssysteme enthalten.

Für Kunststoffe wird oft UL 94 angegeben:

- `HB` - Horizontalmuster brennt langsamer als angegebenes Limit;
- `V-2`, `V-1`, `V-0` - Vertikalmuster muss sich selbst in angegebener Zeit selbstlöschend;
- `5VB`, `5VA` - strengere Tests für bestimmte Anwendungen;
- `HBF`, `HF-1`, `HF-2` - Klassen für Schäummaterialien.

Wichtig: UL 94 ist ein Kleinformat-Labortest an Proben. Es hilft, Materialien zu vergleichen, beweist aber nicht, dass eine selbstgebaute Kammer unter jedem Ausfall sicher ist.

In russischsprachiger Dokumentation für Baumaterialien können Sie treffen:

- `НГ` - nicht brennbar;
- `Г1-Г4` - Entflammbarkeitsstufen;
- `В1-В3` - Zündbarkeit;
- `Д1-Д3` - Rauchentwicklung;
- `Т1-Т4` - Toxizität von Verbrennungsprodukten;
- `РП1-РП4` - Flammenausbreitung über Oberfläche.

Wenn ein Verkäufer "selbstlöschend" schreibt, ersetzt dies das Datenblatt nicht. Material kann bei Überhitzung immer noch rauchen, tropfen, verkohlen, sich verformen oder schädliche Produkte freisetzen.

## Beispiel: XPS, EPS und PIR

Baustoffe-Isolierungsmaterialien sehen oft bequem für Kammer oder Trockner aus: Sie sind leicht, flach, billig, schneiden sich gut und isolieren gut. Aber sie müssen als Baumaterialien mit ihren eigenen Einschränkungen betrachtet werden, nicht als universelle Teile für einen Heizer.

| Material | Wo es angemessen sein kann | Hauptrisiken | Was zu überprüfen ist |
| --- | --- | --- | --- |
| XPS, extrudiertes Polystyrol | Außenisolierung von Kältezonen, falls von heißem Teil getrennt | begrenzte Betriebstemperatur, Verformung, Entflammbarkeit, Rauch im Feuer | technische Beschreibung, maximale Temperatur, Brandeigenschaften, Schutzschicht |
| EPS, expandiertes Polystyrol | nur vorsichtig und weit entfernt von heißen Zonen | niedrige Wärmewiderstand, Entflammbarkeit, Verformung, Rauch | Materialdatenblatt, kein direktes Heizen, mit nicht brennbarer Schicht abdecken |
| PIR / Polyiso | Bauart-Isolierung, manchmal besseres Brandverhalten als Polystyrfolblätter | nicht automatisch nicht brennbar, hängt von Belag und spezifischem Produkt ab | technische Beschreibung, Betriebstemperatur, Brandreaktionsklasse, Herstellereinschränkungen |
| Mineralwolle | Wärmeisolierung, wenn Fasern zulässig sind und hoher Wärmewiderstand nötig | Staub, Fasern, Kompression, Feuchtigkeit, Luftstromdichtung erforderlich | zulässige Temperatur, Bindemittel, Schutzbelag, Montage |
| Metall | Schirm, innere Wand, Wärmeverteiler | Wärmebrücken, heiße Außenfläche, scharfe Kanten | Erdung für Netzbereich, Temperatur, Drahtisolierung |
| 3D-gedruckter Kunststoff | Befestigungen und Abdeckungen außerhalb heißer Zone | Erweichung, Kriechen unter Last, Entflammbarkeit | Material, Verformungstemperatur, tatsächliche Teiltemperatur |

Für XPS im technischen Datenblatt des Herstellers wird oft eine maximale Betriebstemperatur von etwa `74°C` (`165°F`) angegeben. Dies bedeutet nicht, dass alle XPS gleich sind, zeigt aber die Größenordnung der Einschränkung: Dieses Material kann nicht automatisch neben einen Heizer oder heiße Luft gestellt werden.

Für EPS werden Empfehlungen gefunden, Betriebstemperaturen um `75°C` zu halten; darüber kann das Material die Abmessungsstabilität verlieren. Wieder muss der genaue Wert aus der spezifischen Produktdokumentation entnommen werden.

PIR/Polyiso kann in einzelnen Produkten einen höheren zulässigen Bereich haben, beseitigt aber nicht die Überprüfung von Brandeigenschaften, Belag, Klebstoff, Rauch und Herstellerempfehlungen.

## Sichere Material-"Stack"

Für eine geheizte Kammer ist es oft besser, nicht von "Wandmaterial" sondern von Schichten zu denken.

![Beispiel von Materialschichten neben Wärme](../../img/04-thermal-physics-and-materials/03-safe-material-stack.svg)

Beispiel für solidere Logik:

- innen in heißer Zone - Metall, Keramik, Glas oder anderes Material, das Temperatur aushält und nicht von lokaler Überhitzung Feuer fängt;
- weiter - Luftspalt oder Isolierung, wenn sie wirklich nötig ist;
- außen - Gehäuse, das nicht zu gefährlicher Temperatur heizt;
- Drähte und Terminals berühren nicht die Isolierung und sind nicht in Zonen verborgen, wo Überhitzung unbemerkt bleibt;
- es gibt unabhängigen Überhitzungsschutz, wenn Regelausfall zu gefährlichem Heizen führen könnte.

Isolierung sollte nicht das erste Material sein, das den Heizer sieht.

## 3D-gedruckte Teile in der Nähe von Wärme

Gedruckter Kunststoff ist bequem für Halterungen, Abdeckungen, Sensorhalter und Luftkanäle. Aber in einer beheizten Kammer kann es sich schlechter verhalten als es aus der Spule erscheint.

Typische Risiken:

- PLA verliert schnell Steifheit bei Wärmung und unter Last;
- PETG ist besser als PLA, kann aber auch kriechen und sich verformen;
- ABS/ASA tolerieren normalerweise warm Kammer besser, erfordern aber echte Temperaturverifizierung;
- PC und Konstruktionsmaterialien können mehr aushalten, erfordern aber richtige Druckqualität und beseitigen Brandbeurteilung nicht.

Für Teile neben Heizer können Sie sich nicht nur auf den Kunststoffnamen verlassen. Wichtig sind Filamentmarke, Druckeinstellungen, Dicke, Last, Schichtrichtung, Belüftung und tatsächliche Teiltemperatur.

## Was man vor dem Kaufen lesen sollte

Suchen Sie nach technischen Dokumenten, nicht Marketing:

- technische Beschreibung oder Produktdatenblatt;
- SDS/MSDS, wenn Material heiß, geschnitten, geschliffen oder verbrannt werden kann;
- Brandklassifizierung / Brandreaktion;
- UL 94 oder andere Entflammbarkeitsklasse für Kunststoffe;
- maximale Dauerbetriegstemperatur;
- Montagebeschränkungen;
- Einschränkungen des Kontakts mit Wärmequellen;
- Anforderungen an Abdeckung mit Belag, Metall, Trockenmauer oder anderer Schicht.

Wenn Material nur als "Isolierungsblatt" ohne ordentliches Datenblatt verkauft wird, sollte es nicht in einem selbstgebauten beheizten Gerät verwendet werden.

## Was ist definitiv nicht normal

Schlechte Lösungen:

- Schaumstoff oder XPS direkt neben Heizer kleben;
- heißer Strom auf unbekannten Kunststoff richten;
- Terminals und Drähte mit Isolierung abdecken;
- brennbares Material neben Netzbereich `110-230V AC` platzieren;
- sich auf einen Temperatursensor verlassen;
- Baumaterial ohne Verifizierung als sicher für Kammer behandeln;
- "selbstlöschend" als Ersatz für unabhängigen Überhitzungsschutz verwenden;
- erste Aufwärmung ohne Beobachtung und Messungen durchführen.

## Wichtigste Erkenntnis

Materialsicherheit ist nicht ein Parameter. Sie müssen Betriebstemperatur, Entflammbarkeit, Rauch, Toxizität von Verbrennungsprodukten, Klebstoffe, Belege und echte Fehlerszenarien betrachten.

Wenn Material keine klare Dokumentation hat, kann es nicht als primärer Schutz in der Nähe des Heizers platziert werden. Wenn Material entflammbar ist, muss es aus der heißen Zone entfernt, mit geeigneter Schicht abgedeckt und durch Messung im echten Betriebsmodus verifiziert werden.

## Materialien zu diesem Thema

- [UL Solutions: Combustion Fire Tests for Plastics](https://www.ul.com/services/combustion-fire-tests-plastics) - Erklärung von UL 94, vertikale/horizontale Tests, Kunststoff- und Schäumstoffklassen.
- [UL Solutions Code Authorities: UL 94 Rating Certifications and Limitations](https://code-authorities.ul.com/about/blog/understanding-ul-94-rating-certifications-and-limitations/) - Einschränkungen der UL 94-Anwendung auf echte Produkte und große Teile.
- [Russian Emergency Ministry: Federal Law No. 123-FZ, Technical Regulations on Fire Safety Requirements](https://mchs.gov.ru/uploads/document/2022-04-08/c907f456516c1f21009131cfdb944deb.pdf) - russische Feuerrisikoclassifizierung von Materialien: Entflammbarkeit, Zündbarkeit, Rauch, Toxizität, Flammenausbreitung.
- [DuPont: Styrofoam Brand XPS Product Information Sheet](https://www.dupont.com/content/dam/dupont/amer/us/en/performance-building-solutions/public/documents/en/styrofoam-brand-ultra-sl-pis-43-D100087-enUS.pdf) - Beispiel der XPS-technische Beschreibung mit maximaler Servicetemperatur `165°F`.
- [IKO: EPS Insulation in an IKO Roof System](https://www.iko.com/comm/documents/bulletin-eps-insulation-in-an-iko-roof-system/) - Beispiel der EPS-Betriebstemperatureinschränkung und Abmessungsstabilität.
- [Prusa Knowledge Base: Material table](https://help.prusa3d.com/materials) - praktische Referenz für Wärmewiderstand beliebter 3D-Druckmaterialien.
