---
title: "Lüfter und Luftstrom im Filamenttrockner"
description: "Warum Luftstrom im Filamenttrockner und in der beheizten Kammer wichtig ist: Lüfterwahl, Luftstrom, statischer Druck, Geräusch und gleichmäßige Erwärmung."
---

# Lüfter und Luftstrom im Filamenttrockner

Ein Lüfter bewegt nicht nur Luft: Er verteilt Wärme, reduziert lokale Hotspots und hilft, Filament gleichmäßig zu trocknen. Diese Seite hilft bei der Lüfterwahl und erklärt den Einfluss des Luftstroms auf Gehäuse, Heizung und Temperatursensor.

Ein Lüfter ist ein Motor mit einer Schaufel, die Luft bewegt. Bei Geräten rund um einen 3D-Drucker benötigen Sie ihn nicht nur "zum Blasen", sondern um Luft durch die richtige Zone zu drücken: einen Heizer, eine Spule, einen Filter, einen Radiator, eine Kammer oder ein Elektronikfach.

Lüfter der gleichen Größe können sehr unterschiedlich funktionieren. Einer drückt Luft gut im offenen Raum, ein anderer drückt Luft besser durch einen Filter oder Kanal, ein dritter ist leiser, aber schwächer bei Widerstand.

## Wo es verwendet wird

Bei iDryer-ähnlichen Projekten werden Lüfter verwendet für:

- Luftzirkulation im Trockner;
- Wärmeleitung vom Heizer zur Kammer;
- Luftableitung aus der Druckerkammer;
- Filterung durch HEPA/Aktivkohlefilter;
- Elektronikkühhlung;
- Radiator-Kühlung;
- Temperaturausgleich im Gehäuse.

Für die Kammerwärmung ist ein Lüfter besonders wichtig. Der Heizer gibt Wärme ab und der Luftstrom entfernt diese Wärme vom Element und transportiert sie weiter. Ohne ordnungsgemäßen Luftstrom kann der Heizer lokal überhitzen, während die Kammer schlecht heizt.

## Luftstrom und Gegendruck

In der technischen Beschreibung eines Lüfters sehen Sie normalerweise zwei wichtige Parameter:

- Luftstrom - oft in `CFM` oder `m3/h`;
- Gegendruck - oft in `mmH2O`, `Pa` oder `Zoll H2O`.

Der Luftstrom zeigt, wie viel Luft ein Lüfter unter idealen Bedingungen mit wenig Widerstand pumpen kann.

Der Gegendruck zeigt, wie gut ein Lüfter Luft durch Widerstand drücken kann: ein Filter, ein Grill, ein Radiator, ein enger Kanal oder ein langer Luftschlauch.

Praktische Regel:

- für offene Zirkulation ist Luftstrom wichtiger;
- für Filter, Radiatoren, dichte Grills und Kanäle ist Gegendruck wichtiger;
- für ein echtes Gehäuse ist der Betriebspunkt wichtig, nicht nur die maximale Zahl in den Spezifikationen.

Wenn Sie einen leisen Gehäuselüfter auf einen dichten Filter setzen, kann er kaum Luft drücken, obwohl der Luftstrom im offenen Raum stark zu sein scheint.

## Axial- und Radiallüfter

Ein Axiallüfter drückt Luft entlang der Rotationsachse. Dies sind typische quadratische Lüfter `40x40`, `60x60`, `80x80`, `120x120 mm`.

Ein Radiallüfter nimmt Luft von der Seite und bläst sie durch einen engen Ausgang. Es funktioniert oft besser für Kanäle, Düsen, Filter und Orte, wo Sie Druck benötigen.

Für freie Zirkulation in einer Kammer ist ein Axiallüfter normalerweise bequem. Für einen kompakten Kanal, Filter oder gerichteten Fluss ist ein Radiallüfter manchmal besser.

## 2-polig, 3-polig und 4-polig

Lüfter unterscheiden sich oft in der Anzahl der Drähte.

![3-poliger Stecker auf einem Computerlüfter](../../img/03-common-components/03-fan-3pin-connector.jpg)

*Quelle: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Three-pin_connector_on_a_computer_fan.jpg), Dsimic, CC BY-SA 4.0*

2-polig:

- `+V`;
- `GND`.

Ein solcher Lüfter erhält einfach Strom. Sie können die Geschwindigkeit durch Änderung der Versorgungsspannung oder PWM auf der Stromleitung steuern, wenn das Board und der Lüfter dies unterstützen.

3-polig:

- `+V`;
- `GND`;
- tachometrisches Signal (`tach`/`sense`).

Der dritte Draht gibt normalerweise ein Geschwindigkeitssignal aus. Es steuert die Geschwindigkeit nicht selbst.

4-polig PWM:

- `GND`;
- `+V`;
- tachometrisches Signal (`tach`/`sense`);
- PWM-Steuersignal.

Bei einem 4-poligen PWM-Lüfter wird die Stromversorgung normalerweise konstant geliefert und die Geschwindigkeit wird durch eine separate PWM-Leitung eingestellt. Dies ist nicht dasselbe wie das schnelle Umschalten der Lüfterstromversorgung.

## PWM und Drehzahlmesser

PWM ist ein Steuersignal, das die gewünschte Geschwindigkeit einstellt. Computer 4-polige PWM-Lüfter haben normalerweise eine Frequenz um `25 kHz` und die Stromversorgung bleibt konstant.

Wenn der PWM-Draht nicht angeschlossen ist, laufen viele 4-polige Lüfter auf voller Geschwindigkeit.

Das tachometrische Signal zeigt RPM. Es ist nötig, wenn das Gerät verstehen soll:

- ob der Lüfter dreht oder stillsteht;
- ob die Geschwindigkeit dem Befehl entspricht;
- ob ein Filter oder Kanal zu viel Widerstand erzeugt;
- ob der Lüfter blockiert ist.

Ein Drehzahlmesser ersetzt nicht die Temperaturkontrolle. In einem Gerät mit einem Heizer müssen Sie sowohl Temperatur als auch Luftstromstatus überwachen, wenn der Lüfterausfall gefährlich ist.

## Spannung und Strom

Überprüfen Sie vor dem Anschluss:

- Lüfterspannung: `5V`, `12V`, `24V`;
- Betriebsstrom;
- Startstrom;
- Steckertyp;
- Pinbelegung;
- ob es PWM hat;
- ob es einen Drehzahlmesser hat;
- Betriebstemperatur;
- Luftstromrichtung;
- Geräuschpegel;
- Lebensdauer und Lagertyp.

Sie können einen Lüfter nicht direkt von der GPIO des Reglers mit Strom versorgen. GPIO ist ein Signal, keine Stromausgabe. Der Lüfterstrom muss von der Stromversorgung, einem Board-Stromausgang oder einem MOSFET-Modul kommen.

Beim Start kann ein Lüfter kurzzeitig mehr Strom ziehen als im normalen Betrieb. Wenn mehrere Lüfter an einen Ausgang angeschlossen sind, addieren sich ihre Ströme.

## Geräusch, Vibration und Lager

Das Geräusch hängt von mehr als nur RPM ab.

Der Sound wird beeinflusst durch:

- Schaufelform;
- Ausbalancierung;
- Lagertyp;
- Befestigung;
- Grill;
- Kanal;
- Filter;
- Gehäuseresonanz;
- mehrere Lüfter in der Nähe.

Technische Beschreibungen listen Geräusche in `dB(A)` auf, aber in einem echten Gehäuse kann der Lüfter anders klingen. Ein Grill mit schlechter Geometrie, eine nahe Wand oder starre Befestigung an einem dünnen Panel können einen guten Lüfter laut machen.

Für ein Gerät, das stundenlang läuft, ist es besser, einen Lüfter nicht nur nach Preis und Größe, sondern auch nach Lebensdauer, Lager und Temperatur zu wählen.

## Temperatur und Installationsort

Ein Lüfter, der auf einer Werkbank gut funktioniert, kann in einer heißen Kammer schnell verschleißen.

Überprüfen Sie:

- Lüfter-Betriebstemperatur;
- Lufttemperatur in der Nähe des Heizers;
- Entfernung vom Heizelement;
- ob heißer Fluss den Motor direkt trifft;
- ob die Befestigung erweicht;
- ob Drähte austrocknen;
- ob der Lüfter mit Staub oder Fasern verstopft wird.

Wenn der Lüfter für die Heizer-Luftzirkulation verantwortlich ist, sollte sein Ausfall in der Sicherheitslogik berücksichtigt werden. Sie können einen Heizer nicht so auslegen, dass ein stillstehender Lüfter sofort eine gefährliche Temperatur ohne Notfallabschaltung erzeugt.

## Filter und Kanäle

Ein Filter, Grill und Kanal können den nutzbaren Luftstrom erheblich reduzieren.

Typische Zeichen:

- Lüfter ist laut aber Luftstrom ist schwach;
- Filter bekommt kaum Luft durch;
- Luft umgeht den Filter durch Spalten;
- Temperatur in der Nähe des Heizers steigt schneller als Kammertemperatur;
- nach dem Anbau der Abdeckung ist der Luftstrom schlechter als auf der Werkbank.

Um eine Kammer effektiv zu filtern, müssen Sie nicht nur einen Lüfter anbringen, sondern auch einen Luftweg durch den Filter sicherstellen. Wenn Luft einen leichteren Weg durch eine Spalte hat, wird sie es nehmen.

## Was vor dem Kauf zu überprüfen ist

Überprüfen Sie vor dem Kauf eines Lüfters:

- Größe und Dicke;
- Spannung;
- Strom;
- Typ: axial oder radial;
- Luftstrom;
- Gegendruck;
- Geräusch;
- RPM;
- Lagertyp;
- 2-polig/3-polig/4-polig;
- Betriebstemperatur;
- Lebensdauer;
- Luftstromrichtung;
- Stecker und Pinbelegung;
- ob es zu einem Filter, Kanal oder freier Zirkulation passt.

Für einen Filter und engen Kanal wählen Sie einen Lüfter nicht nur nach CFM. Schauen Sie sich den Gegendruck an und testen Sie in echter Zusammensetzung.

## Typische Fehler

- 12V-Lüfter an 24V angeschlossen;
- 24V-Lüfter an 12V angeschlossen und dachte, es sei kaputt;
- Lüfter von GPIO mit Strom versorgt;
- keine gemeinsame Masse für externes MOSFET/PWM hergestellt;
- Startstrom nicht berücksichtigt;
- mehrere Lüfter an einen schwachen Ausgang angeschlossen;
- Lüfter nur nach Größe ausgewählt;
- Freilauf-Lüfter auf dichtem Filter installiert;
- denken, Tach-Draht sei ein Steuerdraht;
- denken, 4-polig PWM sei das Gleiche wie 2-polig;
- 4-polig PWM-Lüfter durch Ein-/Ausschalten der Stromversorgung steuern;
- Lüfter in heißer Zone ohne Temperaturprüfung installiert;
- Luftstrom nach dem Anbau von Abdeckung, Filter und Kanal nicht überprüft.

## Hauptpunkt

Ein Lüfter wird für die Aufgabe ausgewählt: freie Zirkulation, Filter, Kanal, Radiator, Heizer oder Elektronik-Kühlung. Für offenen Raum ist Luftstrom wichtig; für Filter und Kanäle ist Druck wichtig.

Überprüfen Sie Spannung, Strom, Drahttyp, PWM/Drehzahlmesser, Betriebstemperatur und echten Systemwiderstand. In einem Gerät mit einem Heizer sollte der Lüfter Teil eines sicheren thermischen Systems sein, nicht ein dekoratives Element.

## Referenzmaterialien

- [Noctua: Microcontroller guide for PWM and RPM monitoring](https://www.noctua.at/en/support/faqs/microcontroller-guide-pwm-setup-and-rpm-monitoring) - praktische Erklärung von 4-polig PWM, Drehzahlmesser, Leistung und PWM-Frequenz um 25 kHz.
- [Noctua: Fan pin configuration](https://www.noctua.at/faq-redirects/en/support/solutions/articles/101000081757-what-pin-configuration-do-noctua-fans-use-) - Standard 4-polige Lüfter-Pinbelegung und Verhalten, wenn nur Stromversorgung angeschlossen ist.
- [SANYO DENKI: Fan Airflow and Static Pressure](https://techcompass.sanyodenki.com/en/training/cooling/fan_basic/004/index.html) - Erklärung von Luftstrom, Gegendruck, Betriebspunkt und Systemwiderstand.
- [DigiKey: Selecting A Fan](https://www.digikey.ca/en/articles/selecting-a-fan) - Lüftertyp-Auswahl, Lüfterkurve, Systemwiderstand und Unterschied zwischen Axial- und Radiallüftern.
- [Klipper Configuration Reference: Fans](https://www.klipper3d.org/Config_Reference.html#fans) - offizielle Klipper-Abschnitte für Lüfter: `fan`, `heater_fan`, `temperature_fan`, `controller_fan` und `fan_generic`.
