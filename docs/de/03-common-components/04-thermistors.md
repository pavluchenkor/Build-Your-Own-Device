# Thermistoren

Ein Thermistor ist ein Temperatursensor, dessen Widerstand sich bei Erwärmung oder Abkühlung ändert. In 3D-Druckern, Trocknern und kleinen Heizgeräten wird er oft als Rückmeldung zur Steuerung des Heizers verwendet.

Die häufigste Option in der 3D-Druck-Gemeinschaft ist NTC-Thermistor `100K`. NTC bedeutet, dass mit steigender Temperatur der Widerstand abnimmt. `100K` bedeutet normalerweise etwa `100 kOhm` bei `25°C`.

## Wo es verwendet wird

Thermistoren werden verwendet, um die Temperatur zu messen von:

- Druckkopf;
- beheiztem Druckbett;
- Druckerkammer;
- Filamenttrockner;
- Luftkanal;
- Heizmodul;
- Elektronikbereich, wenn einfacher Überhitzungsschutz erforderlich ist.

In einem Gerät mit einem Heizer ist ein Thermistor kein dekorativer Sensor. Er bestimmt, wann der Regler die Leistung reduziert, die Heizung deaktiviert oder mit einem Fehler stoppt.

## NTC 100K, Beta und Nachschlagetabellen

Verschiedene Thermistoren können gleich aussehen, aber unterschiedliche Eigenschaften haben.

Wichtige Parameter:

- Widerstand bei `25°C`, beispielsweise `100 kOhm`;
- Typ: NTC oder PTC;
- Beta, beispielsweise `3950K`;
- Widerstands-/Temperatur-Nachschlagetabelle;
- Betriebstemperaturbereich;
- Genauigkeit;
- Paket: Glaskugel, Patrone, Schraubsensor, Mantel;
- Draht-Isolierung.

Wenn die Firmware den falschen Sensortyp auswählt, wird die Temperatur falsch angezeigt. Der Fehler kann bei Raumtemperatur klein und bei Betriebstemperatur gefährlich sein.

Die Phrase "100K-Thermistor" reicht also nicht immer aus. Für die Firmware ist ein spezifisches Modell oder zumindest die richtige Beta/Tabelle wichtig.

## Wie der Regler die Temperatur misst

Ein Thermistor wird normalerweise über einen Spannungsteiler mit Pullup-Widerstand an einen analogen Eingang angeschlossen. Der Regler misst die Spannung, konvertiert sie in Widerstand und verwendet dann eine Nachschlagetabelle oder Formel, um die Temperatur zu erhalten.

![Spannungsteiler mit Thermistor zur Temperaturmessung](../../../img/03-common-components/04-thermistor-voltage-divider.svg)

*Quelle: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Thermistor_potential_divider.svg), Sjlegg, Public Domain*

In Klipper wird dies durch `sensor_type`, `sensor_pin`, manchmal `pullup_resistor` oder einen benutzerdefinierten `[thermistor]`-Abschnitt eingestellt.

In Marlin wird der Thermistor-Typ durch Sensorkonfigurationsparameter und Temperaturgrenzen ausgewählt.

Für den Benutzer ist die wichtigste Erkenntnis einfach: Die Firmware muss genau den Sensortyp kennen, der im Gerät installiert ist.

## Offener Stromkreis und Kurzschluss

Ein Thermistor und seine Verdrahtung können ausfallen.

Typische Symptome:

- unterbrochener Draht;
- schlechter Kontakt des Anschlusses;
- Drähte kurzgeschlossen;
- beschädigte Isolierung;
- Sensor rutschte aus der Mantelöffnung;
- Draht abgescheuert in einem beweglichen Teil;
- Sensor zeigt Raumtemperatur an, obwohl Heizung erfolgt.

Die Firmware verfügt normalerweise über Schutzvorrichtungen wie `MINTEMP`, `MAXTEMP`, Heizverifikation und Thermisches-Durchgehen-Schutz. Aber diese Schutzvorrichtungen funktionieren nur, wenn der Sensor und die Firmware ordnungsgemäß eingestellt sind und der Stromteil tatsächlich ausgeschaltet werden kann.

Wenn ein Sensor vom Heizer abfällt, aber elektrisch angeschlossen bleibt, ist dies besonders gefährlich: Die Firmware kann "niedrige Temperatur" sehen und weiter heizen.

## Thermischer Kontakt

Die Thermistor-Montage ist oft wichtiger, als es scheint.

Der Sensor sollte die Temperatur des Ortes messen, den Sie tatsächlich steuern möchten. Für einen Druckkopf ist es der Heizblock. Für ein Bett ist es die Oberfläche oder ein Ort, der mit der tatsächlichen Betttemperatur zusammenhängt. Für einen Luftheizer ist es ein Punkt, der durch Sicherheits- und Steuerungslogik ausgewählt wird.

Der thermische Kontakt wird beeinflusst durch:

- Sensordruck;
- Wärmeleitpaste;
- Montageloch;
- Mantel;
- Schraubenmontage;
- Lücke;
- Material um den Sensor;
- Draht-Zustand;
- Verschmutzung oder getrocknete Paste;
- Vibration und lose Befestigung.

Wenn ein Thermistor nur seitlich ein Teil berührt, kann er langsam reagieren und eine falsche Temperatur anzeigen. Der PID-Regler erhält dann verzögerte Informationen und die Temperatur kann den Ziel überschießen.

## Sensorpaket

Thermistoren werden in verschiedenen Paketen geliefert.

Glaskugel:

- billig;
- winzig;
- erfordert sorgfältige Montage;
- leicht, Draht oder Isolierung zu beschädigen.

Patronenthermistor:

- einfacher in das Heizblock-Loch einzusetzen;
- normalerweise mechanisch stabiler;
- wichtig ist, Durchmesser und Länge zu entsprechen.

Schraubthermistor:

- befestigt sich leicht auf einer Metalloberfläche;
- kann guten Kontakt geben, wenn ordnungsgemäß installiert;
- darf nicht überziehen oder den Draht beschädigen.

Sensor im Mantel:

- praktisch für Luft, Flüssigkeit oder Gehäuse;
- antwortet langsamer, wenn der Mantel massiv ist;
- der richtige Installationspunkt ist wichtig.

Die Paketauswahl hängt davon ab, was gemessen wird und wie der Sensor gewartet wird.

## Multimeter-Überprüfung

Die grundlegende Überprüfung kann mit einem Multimeter im Widerstandsmodus durchgeführt werden. Das detaillierte Verfahren befindet sich im praktischen Artikel: [Überprüfung eines Thermistors](../05-practical-guides/02-checking-a-thermistor.md).

Für einen typischen NTC `100K` bei Raumtemperatur um `25°C` erwarten Sie etwa `100 kOhm`. Der exakte Wert hängt von Temperatur und Toleranz ab.

Bei Erwärmung mit Fingern sollte NTC-Widerstand abnehmen. Wenn das Multimeter Stromkreisunterbrechung, Kurzschluss oder Wertsprung beim Ziehen des Drahts anzeigt, überprüfen Sie zuerst den Anschluss und die Verdrahtung.

Die Multimeter-Überprüfung ersetzt nicht die Kalibrierung und beweist nicht die Genauigkeit bei `200°C`, zeigt aber schnell ein offenes, Kurzschluss oder falschen Sensortyp.

## Was vor dem Kauf zu überprüfen ist

Überprüfen Sie vor dem Kauf eines Thermistors:

- Widerstand bei `25°C`;
- Beta oder exaktes Modell;
- Kompatibilität mit Firmware;
- Betriebstemperaturbereich;
- Sensorpaket;
- Drahtlänge und Material;
- Steckertyp;
- Befestigungsmethode;
- ob Sie eine Patrone, Schraube, Mantel oder Glaskugel benötigen;
- ob der Sensor zu Ihrem Heizblock oder Installationsort passt;
- Verfügbarkeit technischer Beschreibung oder klarer Informationen.

Für einen Druckkopf ist es besser, einen Sensor zu erhalten, der mechanisch zu einem bestimmten Block passt. Für eine Kammer oder Trockner ist der Installationsort, Drahtschutz und Messstabilität in Luftstrom wichtiger.

## Typische Fehler

- falsch `sensor_type` ausgewählt;
- denken, ein beliebiger `100K`-Thermistor sei gleich;
- Sensor ist schlecht gepresst;
- kein ordnungsgemäßer thermischer Kontakt;
- Sensor rutschte aus der Mantelöffnung;
- Draht am Sensorkörper abgescheuert oder brach;
- Anschlusskontakt ist schlecht;
- Verdrahtung unnötig neben Stromleitungen;
- Thermistor misst Luft, aber Regler denkt, dass er den Heizer misst;
- Firmware eingestellt ohne vernünftige `min_temp` und `max_temp`;
- Heizer ohne unabhängigen Hardware-Schutz eingeschaltet.

## Hauptpunkt

Ein Thermistor ist Rückmeldung für einen Heizer. Es ist wichtig, nicht nur "100K NTC" zu kaufen, sondern den richtigen Typ in der Firmware auszuwählen, den Sensor am richtigen Ort zu montieren und die Verdrahtung zu überprüfen.

Schlechter thermischer Kontakt oder falscher `sensor_type` können gefährlicher sein als ein völlig toter Sensor, da das System weiterhin funktioniert, aber Entscheidungen auf falscher Temperatur trifft.

## Referenzmaterialien

- [Klipper Configuration Reference: Temperature sensors](https://www.klipper3d.org/Config_Reference.html#temperature-sensors) - offizielle `sensor_type`, `pullup_resistor`, benutzerdefinierte `[thermistor]` und Temperatursensoren in Klipper.
- [Marlin Configuration: Temperature Ranges and Thermal Protection](https://marlinfw.org/docs/configuration/configuration.html#temperature-ranges) - Temperaturgrenzen, `MINTEMP`, `MAXTEMP` und Thermoschutz.
- [Vishay: NTC Thermistors](https://www.vishay.com/en/thermistors/ntc/) - NTC-Thermistor-Parameter: Widerstand bei `25°C`, Beta, Toleranz und Betriebsbereich.
- [RepRap Europe: Thermistor NTC100K](https://www.reprap-3d-printer.com/product/335-thermistor-ntc100k) - Beispiel typischer 3D-Drucker NTC `100K` mit Beta `3950` und `100 kOhm` bei `25°C`.
- [RepRap Europe: Thermistor Cartridge 100k HT-NTC B3950](https://reprap.eu/produto/?id=1245&nome=Thermistor+Cartridge+100k+HT-NTC+B3950) - Beispiel Patronenthermistor für Heizblock und mechanische Montage.
