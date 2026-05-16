# Anschluss eines Lüfters

Ein Lüfter scheint eine einfache Komponente zu sein: Stromversorgung anschließen und er dreht sich.

In der Praxis entstehen Probleme aus vier Dingen:

- Auswahl eines Lüfters mit falscher Spannung;
- Anschluss an einen schwachen Controller-Ausgang;
- Mangelndes Verständnis der Unterschiede zwischen 2-Pin-, 3-Pin- und 4-Pin-Lüftern;
- Platzierung des Lüfters, wo er aufgrund eines Filters, Gitters oder Kanals unter Druck mangelt.

In iDryer-ähnlichen Geräten wird ein Lüfter normalerweise für Luftzirkulation, Lüfterkühlung, Kammerabluft, Filtration oder Elektronikkühlung benötigt.

## Was vor dem Anschluss zu prüfen ist

Vor dem Anschluss die Lüfterparameter finden:

- Spannung: `5V`, `12V` oder `24V`;
- Strom oder Leistung;
- Steckertyp: 2-Pin, 3-Pin oder 4-Pin;
- PWM-Steuerungsfähigkeit;
- Vorhandensein eines tachometrischen Signals;
- Luftstrom;
- statischer Druck;
- Geräuschpegel;
- Betriebstemperatur.

Diese Daten sind auf einem Etikett, einer Produktseite oder im technischen Datenblatt zu finden.

Zum Beispiel enthält ein Lüfterdatenblatt normalerweise nicht nur Spannung und Strom, sondern auch Luftstrom, statischen Druck, Lautstärke `SPL dB(A)`, Betriebstemperatur und Lebensdauer. Diese sind nützlicher als die Auswahl eines Lüfters nur nach Größe.

## Keinen Lüfter von GPIO mit Strom versorgen

GPIO eines Controllers ist ein Steuersignal, kein Stromausgang.

Einen Lüfter niemals direkt von GPIO mit Strom versorgen. Dies kann den Controller beschädigen oder zu Neustarts führen, wenn der Lüfter startet.

Die korrekte Logik:

- der Lüfter erhält Strom von einer Stromversorgung oder einem Board-Stromausgang;
- der Controller verwaltet nur Ein/Aus oder Geschwindigkeit;
- wenn ein externes MOSFET-Modul verwendet wird, müssen die Stromversorgung `GND` und Controller `GND` gemeinsam sein.

![N-Kanal-MOSFET im Schaltmodus (low-side) zur Laststeuerung](../../../img/01-electronics-basics/02-nmos-switch-operation.png)

*Quelle: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:NMOS_PWR_WHOLE.PNG), KjellElec, CC BY-SA 4.0*

## Einfachste Option: 2-Pin-Lüfter

Ein 2-Pin-Lüfter hat normalerweise nur:

- `+` Stromversorgung;
- `-` Stromversorgung.

Wenn es ein 24V-Lüfter ist, mit 24V verbinden. Wenn es ein 12V-Lüfter ist, mit 12V verbinden.

Für einfache Ein/Aus-Steuerung können Sie verwenden:

- einen dedizierten Lüfterausgang auf der Karte, falls für die erforderliche Spannung und Stromstärke bewertet;
- ein externes MOSFET-Modul für DC-Lasten;
- einen separaten Lüfterregler.

Wenn der Lüfter kontinuierlich laufen soll, kann er direkt an eine angemessene Stromversorgung über eine Sicherung oder geschützte Stromleitung angeschlossen werden. In einem Gerät mit Heizer ist es jedoch oft besser, wenn der Lüfter vom Controller als Teil der Sicherheitslogik gesteuert wird.

## 3-Pin-Lüfter

Ein 3-Pin-Lüfter hat normalerweise:

- Stromversorgung;
- Masse;
- tachometrisches Signal.

Das tachometrische Signal ermöglicht das Überwachen der Lüfterdrehzahl. Es steuert die Geschwindigkeit nicht selbst.

Die Geschwindigkeit eines 3-Pin-Lüfters wird normalerweise durch Reduzierung der Stromversorgungsspannung oder PWM auf der Stromleitung geändert, falls das spezifische Board und der Lüfter dies unterstützen. Aber diese Methode funktioniert möglicherweise nicht besser als ordnungsgemäße 4-Pin-PWM: Der Lüfter kann quieken, nicht bei niedriger Geschwindigkeit starten oder instabil laufen.

Wenn Geschwindigkeitssteuerung nicht erforderlich ist, kann ein 3-Pin-Lüfter wie ein normaler 2-Pin verwendet werden: Stromversorgung und Masse sind verbunden, der tachometrische Draht wird nicht verwendet.

## 4-Pin-PWM-Lüfter

Ein 4-Pin-PWM-Lüfter hat normalerweise:

- Masse;
- Stromversorgung;
- tachometrisches Signal;
- PWM-Steuersignal.

Der Hauptunterschied: Die Stromversorgung des Lüfters wird kontinuierlich angewendet, und die Geschwindigkeit wird durch ein separates PWM-Signal eingestellt.

Dies ist der richtige Weg, um Computer-PWM-Lüfter zu steuern. Gehen Sie nicht davon aus, dass ein 4-Pin-Lüfter durch ständiges Umschalten der Stromversorgung an und aus gesteuert werden muss. Für einen ordnungsgemäßen PWM-Lüfter sollte das Steuersignal zu einem separaten PWM-Pin gehen.

Computer-4-Pin-PWM-Lüfter haben oft einen Steuereingang, der für Open-Collector/Open-Drain-Signale mit internem Pull-up ausgelegt ist, nicht für irgendeine Spannung von GPIO. Wenden Sie nicht `12V` oder `24V` auf den PWM-Pin an. Überprüfen Sie die Lüfterdokumentation; wenn Open-Drain/Open-Collector erforderlich ist, verwenden Sie einen entsprechenden Transistorausgang oder GPIO-Modus.

Bei vielen 4-Pin-PWM-Lüftern liegt die typische PWM-Frequenz bei etwa `25 kHz`. Einige Lüfter arbeiten in einem nahe gelegenen Bereich, aber bei zu niedriger oder zu hoher Frequenz können sie sich unvorhersehbar verhalten: mit voller Geschwindigkeit laufen, stoppen oder Geräusche machen.

Wenn der PWM-Draht nicht angeschlossen ist, laufen viele 4-Pin-Lüfter mit voller Geschwindigkeit.

## Gemeinsamer GND / gemeinsames Negativ

Wenn der Lüfter von einer separaten Stromversorgung angetrieben wird und das PWM-Signal vom Controller kommt, ist ein gemeinsamer `GND` / gemeinsames Negativ erforderlich.

Ohne einen gemeinsamen `GND` haben der Controller und der Lüfter kein gemeinsames Referenzniveau. Infolgedessen funktioniert PWM möglicherweise nicht oder funktioniert intermittierend.

Einfache Regel:

- die positive Stromversorgung des Lüfters kommt von einer angemessenen Stromversorgung;
- die negative Stromversorgung des Lüfters ist mit dem Negativ der Stromversorgung verbunden;
- der Controller `GND` ist mit demselben Negativ verbunden;
- das Steuersignal funktioniert nur mit einem gemeinsamen Masse.

## Auswahl eines Lüfters für die Aufgabe

Für offene Kühlung ist Luftstrom wichtig.

Für einen Filter, Kühlkörper, enges Gitter, langen Kanal oder schmalen Kanal ist statischer Druck wichtiger.

Also für einen Druckerkammer-Filter kann ein gewöhnlicher ruhiger Gehäuselüfter schwach sein. Es wird in freier Luft gut blasen, aber kaum Luft durch einen HEPA-Filter, eine Holzkohleschicht oder einen engen Kanal drücken.

Richtlinien:

- für freie Luftzirkulation nach `CFM` oder `m³/h` schauen;
- für Filter, Kühlkörper und Kanäle ist statischer Druck essentiell;
- für leisen Betrieb nicht nur auf `dB(A)` schauen, sondern auch auf Montage, Gitter und Vibration;
- für eine beheizte Kammer auf die Betriebstemperatur des Lüfters schauen.

## Startstrom und Marge

Wenn ein Lüfter startet, kann er kurzzeitig mehr Strom ziehen als während des normalen Betriebs.

Wenn mehrere Lüfter an einen Ausgang angeschlossen sind, addieren sich ihre Ströme.

Überprüfen:

- maximale Ausgangsstromstärke der Karte;
- Strom eines Lüfters;
- Gesamtstrom aller Lüfter;
- mindestens 50% Marge;
- Erwärmung von Anschlüssen, Drähten und MOSFET-Modul bei längerer Betriebsdauer.

Wenn ein Lüfter beispielsweise `0.25A` zieht, ziehen vier solche Lüfter etwa `1A` ohne Berücksichtigung des Startstroms.

## Beispiel: Anschluss über MOSFET-Modul

Typischer Schaltkreis für einen 12V- oder 24V-Lüfter:

1. Das Positiv der Stromversorgung geht zum Positiv des Lüfters.
2. Das Negativ des Lüfters geht zum Stromausgang des MOSFET-Moduls.
3. Das Negativ der Stromversorgung geht zum MOSFET-Modul.
4. Der Controller `GND` ist mit dem Negativ der Stromversorgung verbunden.
5. Der Controller-Steuerstift geht zum MOSFET-Modul-Eingang.

Dies wird als Low-Side-Schaltung bezeichnet: Das MOSFET trennt das Negativ der Last.

Für einen einfachen 2-Pin-Lüfter ist dies eine Standard- und klare Option, wenn das MOSFET-Modul für die erforderliche Spannung und Stromstärke bewertet ist. Für einen 3-Pin-/4-Pin-Lüfter mit Tachometer oder separatem PWM-Eingang ist das "Abschneiden des Negativ" nicht immer gut: Das Überwachen der Drehzahl und die native PWM-Steuerung erfordern normalerweise einen konstanten gemeinsamen `GND`.

## Beispiel-Klipper-Konfiguration

Pin-Namen in Beispielen sind nicht universell. Vor dem Kopieren überprüfen Sie die Pinout Ihres Boards: Ein falscher `pin` kann den falschen Ausgang aktivieren.

Wenn der Lüfter an einen gesteuerten Ausgang angeschlossen ist und manuell gesteuert werden soll:

```ini
[fan_generic chamber_fan]
pin: PA8
max_power: 1.0
shutdown_speed: 0.0
kick_start_time: 0.5
off_below: 0.15
```

Steuerung:

```gcode
SET_FAN_SPEED FAN=chamber_fan SPEED=1.0
SET_FAN_SPEED FAN=chamber_fan SPEED=0.4
SET_FAN_SPEED FAN=chamber_fan SPEED=0
```

Wenn der Lüfter basierend auf der Kammertemperatur eingeschaltet werden soll:

```ini
[temperature_fan chamber_exhaust]
pin: PA8
max_power: 1.0
shutdown_speed: 0.0
kick_start_time: 2.0
off_below: 0.15
sensor_type: NTC 100K beta 3950
sensor_pin: PA0
min_temp: 0
max_temp: 80
target_temp: 45
control: watermark
```

Pin-Namen hier sind typisch. In einem echten Gerät überprüfen Sie die Pinout Ihres Boards.

## Was nach dem Anschluss zu überprüfen ist

Vor längerer Betriebsdauer überprüfen:

- der Lüfter dreht sich in der richtigen Richtung;
- Spannung stimmt mit dem Lüfter überein;
- das MOSFET-Modul wird nicht übermäßig heiß;
- Anschlüsse werden nicht übermäßig heiß;
- Drähte sind nicht zu dünn für den gewählten Strom;
- der Lüfter startet nach vollständigem Stopp;
- kein Quieken oder Stottern bei niedriger Geschwindigkeit;
- Luftstrom geht durch den benötigten Bereich, nicht um ihn herum;
- das Gitter, der Filter oder das Gehäuse drosselt den Fluss nicht mehr als erwartet.

Wenn der Lüfter in der Nähe eines Heizers ist, testen Sie ihn bei echter Kammertemperatur. Ein Lüfter, der auf der Werkbank einwandfrei funktioniert, kann in einem heißen Gehäuse schnell verschleißen.

## Häufige Fehler

- ein 12V-Lüfter an 24V anschließen;
- einen 24V-Lüfter an 12V anschließen und entscheiden, dass er kaputt ist;
- Lüfter von GPIO mit Strom versorgen;
- Vergessen von gemeinsamer Masse zwischen Controller und externer Stromversorgung;
- PWM-Steuerung von einem 3-Pin-Lüfter erwarten;
- Steuerung eines 4-Pin-PWM-Lüfters durch Abschneiden der Stromversorgung statt PWM-Pin;
- nicht berücksichtigung des Gesamtstroms mehrerer Lüfter;
- Auswahl eines Lüfters nach Größe ohne Überprüfung des statischen Drucks;
- Platzierung eines leisen Lüfters auf einem dichten Filter und Erhalt von nahezu null Fluss;
- Überprüfung der Flussrichtung nach der Installation nicht durchgeführt;
- Drähte ungesichert gelassen und Ausfransen gegen Lüfterrad oder Gehäuse.

## Wichtigste Punkte

- Die Lüfterspannung muss mit der Stromversorgung übereinstimmen.
- GPIO versorgt einen Lüfter nicht mit Strom, sondern steuert ihn nur.
- Für externe Stromversorgung ist ein gemeinsamer Masse mit dem Controller erforderlich.
- Ein 2-Pin-Lüfter ist am einfachsten über einen Stromausgang oder MOSFET zu steuern.
- 3-Pin fügt ein Tachometer hinzu, aber keinen separaten PWM-Eingang.
- 4-Pin-PWM wird am besten durch ein separates PWM-Signal gesteuert, nicht durch Stromschalten.
- Für Filter und Kanäle ist statischer Druck wichtiger als eine schöne `CFM`-Nummer.
- Nach der Montage überprüfen Sie nicht nur die Rotation, sondern den tatsächlichen Fluss durch die Konstruktion.

## Verwandte Lektüre

- [Noctua: PWM-Konfiguration und RPM-Überwachung eines Lüfters mit Mikrocontrollern](https://www.noctua.at/en/support/faqs/microcontroller-guide-pwm-setup-and-rpm-monitoring) - praktische Erklärung von 4-Pin-PWM, RPM-Signal, gemeinsamer Masse und typischer PWM-Frequenz.
- [Klipper-Konfigurationsreferenz: Lüfter](https://www.klipper3d.org/Config_Reference.html#fans) - offizielle Abschnitte `fan`, `heater_fan`, `controller_fan`, `temperature_fan` und `fan_generic`.
- [Voron-Dokumentation: Kammertemperatur und Abluftlüfter](https://docs.vorondesign.com/community/howto/alchemyEngine/chamber_temperature_exhaust_fan.html) - Beispiel der Steuerung des Kammerabluftlüfters nach Temperatur in Klipper.
- [DigiKey: Auswahl eines Lüfters](https://www.digikey.com/en/articles/selecting-a-fan) - Lüfterauswahl unter Berücksichtigung von Luftstrom, statischem Druck, Gehäusewiderstand und Filtern.
- [SANYO DENKI: Beispiel-Datenblatt für DC-Lüfter](https://products.sanyodenki.com/en/sanace/dc/dc-fan/109P0405F601/) - Beispiel für echte Parameter: Spannung, Strom, Luftstrom, statischer Druck, Lautstärke, Betriebstemperatur und Lebensdauer.
