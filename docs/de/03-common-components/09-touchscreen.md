# Touchscreen

Ein Touchscreen ist nicht nur ein Display. Es ist ein Display plus Benutzereingabe. Es muss nicht nur Temperatur oder einen Knopf anzeigen, sondern dem Gerät sagen, wo du berührt hast.

Aus diesem Grund ist ein Touchscreen fast immer komplexer als OLED. Du musst nicht nur Größe und Auflösung wählen, sondern verstehen, wer die Schnittstelle zeichnet, wer Berührungen verarbeitet, welche Schnittstelle verwendet wird und ob deine gewählte Firmware sie unterstützt.

## Wann ist Touchscreen sinnvoll

Ein Touchscreen macht Sinn, wenn das Gerät eine vollständige lokale Schnittstelle benötigt:

- Trocknungsmodus wählen;
- Temperatur und Zeit einstellen;
- Materialprofilliste;
- Fehler bestätigen;
- manuelle Lüfter-, Beleuchtungs- oder Drosselklappensteuerung;
- Wi-Fi-Einrichtung;
- Status ohne Telefon oder Computer anzeigen.

Wenn du nur Temperatur, Fehler und Modus anzeigen musst, reichen normalerweise OLED, ein paar Tasten, Encoder oder Web-Interface aus. Ein Touchscreen erhöht Kosten, Stromverbrauch, Gehäuseplatz, Firmware, Kabel und einen weiteren Fehlerpunkt.

## Hauptfrage: Wer zeichnet die Schnittstelle

Vor dem Kauf beantwort die Hauptfrage: wo lebt die Benutzeroberfläche.

Es gibt mehrere verschiedene Bildschirmklassen:

![Klassen von Touchscreens und wer die Schnittstelle zeichnet](../../img/03-common-components/09-touchscreen-classes.svg)

Raw TFT ist ein einfacher Bildschirm mit einem Controller wie `ILI9341`, `ILI9488`, `ST7789`, plus einem separaten Touch-Controller wie `XPT2046` oder `FT5x06`. Dein Mikrocontroller oder deine Firmware zeichnet die Schnittstelle. Das ist flexibel, erfordert aber Code, Speicher, Treiber und Kalibrierung.

Smart UART/HMI-Display ist ein Bildschirm mit eigenem Firmware und Interface-Editor, wie Nextion. Der Mikrocontroller sendet Befehle über UART, und der Bildschirm zeigt Seiten und Elemente. Das reduziert die MCU-Last, bindet dein Projekt aber an die Tools und das Protokoll dieses Bildschirms.

Printer TFT, wie BTT TFT35, hat oft seinen eigenen Touchscreen-Modus über UART und klassische 12864 LCD-Emulation über EXP-Stecker. Dieser Bildschirm ist praktisch für Marlin/3D-Printer-Platinen, ist aber kein universelles Bedienfeld für jedes DIY-Gerät.

HDMI/DSI/USB-Bildschirm für Linux-Host funktioniert wie ein normaler Monitor und Touch-Gerät für Raspberry Pi oder anderen Linux-Computer. Das passt zu KlipperScreen, verbindet sich aber nicht direkt zu kleinem ESP32 als einfaches Modul.

## Verbindungsschnittstellen

Touchscreens verwenden verschiedene Schnittstellen.

Häufige Optionen:

- SPI - oft auf kleinem TFT für ESP32/Arduino;
- I2C - oft auf kapazitiven Touch-Controllern, manchmal auf Touch-Controllern;
- UART - auf Smart Displays und einigen 3D-Printer TFTs;
- EXP1/EXP2/EXP3 - auf Bildschirmen, die mit 3D-Printer-Platinen kompatibel sind;
- HDMI + USB - auf Linux-Bildschirmen für Raspberry Pi;
- DSI - auf einigen Raspberry-Pi-Bildschirmen;
- paralleles RGB/8080 - auf schnelleren TFTs, aber mehr Drähte und Anforderungen.

Du kannst einen Bildschirm nicht nur nach der Diagonale wählen. Zwei `3,5"`-Bildschirme können völlig unterschiedlich sein: ein SPI-Modul für ESP32, zweites UART-Panel mit eigenem Firmware, drittes HDMI-Screen für Raspberry Pi.

## Resistiver und kapazitiver Touch

Der Touch-Teil variiert auch.

Resistiver Touch:

- reagiert auf Finger, Stylus oder Fingernagel-Druck;
- erfordert oft Kalibrierung;
- normalerweise schlechter für Gesten;
- kann billiger sein;
- zu finden mit Controllern wie `XPT2046`.

Kapazitiver Touch:

- reagiert auf einen Finger;
- normalerweise angenehmer zu bedienen;
- kann mehrere Berührungen unterstützen;
- hat oft einen separaten Controller wie `FT5x06`, `GT911` Familien;
- funktioniert schlechter mit dicken Handschuhen und einigen Schutzabdeckungen.

Für ein Werkstattgerät ist resistiver Touch manchmal praktischer, weil du ihn mit einem Fingernagel oder Stylus drücken kannst. Für ein schönes Bedienfeld auf dem Gehäuse fühlt sich kapazitiv normalerweise moderner an.

## Stromversorgung, Hintergrundbeleuchtung und Strom

Ein TFT-Bildschirm zieht mehr als ein kleines OLED. Der Hauptstromverbraucher ist die Hintergrundbeleuchtung.

Vor dem Anschluss überprüfe:

- Bildschirm-Stromversorgungsspannung;
- Hintergrundbeleuchtungsstrom;
- ob du eine separate 5V-Quelle brauchst;
- ob Hintergrundbeleuchtungshelligkeit einstellbar ist;
- ob Logikpegel kompatibel sind;
- ob der Bildschirm die Board-Stromversorgung überlädt;
- ob die Stromversorgung abfällt, wenn die Hintergrundbeleuchtung eingeschaltet wird.

Wenn der Bildschirm weiß wird, flimmert, den Controller neu startet oder Touch-Ereignisse verliert, überprüfe zuerst Stromversorgung und Masse, nicht den Interface-Code.

Für ein Gerät mit Heizer sollte der Bildschirm nicht von einem zufälligen schwachen Pin mit Strom versorgt werden. Er sollte Teil eines ordnungsgemäßen Stromversorgungsschemas mit klarem Spielraum sein.

## Firmware und Kompatibilität

Ein schöner Bildschirm ist nutzlos, wenn deine gewählte Firmware ihn nicht unterstützt.

Für ESP32/Arduino-Ansatz musst du überprüfen:

- gibt es einen Display-Treiber;
- gibt es einen Touch-Controller-Treiber;
- gibt es genug GPIO;
- gibt es genug RAM/PSRAM für Puffer;
- welches Graphics-Framework wird verwendet;
- wer wird das Menü schreiben.

Für ESPHome überprüfe die Unterstützung für den spezifischen Display-Treiber und die Touchscreen-Komponente. Zum Beispiel benötigen ILI9xxx-Displays und XPT2046-Touch SPI und separate Konfiguration, und resistiver Touch benötigt Kalibrierung.

Für Klipper gibt es normalerweise zwei verschiedene Welten:

- kleine Displays, die mit MCU verbunden und in Klipper-Konfiguration beschrieben sind;
- KlipperScreen auf Linux-Host, wo der Bildschirm als Monitor und Touch-Gerät funktioniert.

KlipperScreen benötigt normalerweise einen Bildschirm, auf dem Linux einen Desktop oder eine Konsole anzeigen kann. Dies ist nicht dasselbe wie ein kleines UART TFT, das mit einer Printer-Platine verbunden ist.

Für Marlin/Printer-Platinen überprüfe, ob der spezifische Bildschirm den benötigten Modus unterstützt: UART-Touch-Modus, 12864-Emulation, EXP1/EXP2/EXP3, spezifischer Controller-Typ in der Firmware-Konfiguration.

## Smart Display und Nextion-ähnliche Bildschirme

Smart Display ist praktisch, weil der Bildschirm Seiten, Tasten, Schriftarten und Bilder speichert. Der Controller sendet Befehle über UART und empfängt Touch-Ereignisse.

Vorteile:

- weniger Last auf Mikrocontroller;
- weniger Grafikcode in der Hauptfirmware;
- du kannst die Schnittstelle im Bildschirm-Editor zeichnen;
- nur UART und Stromversorgung nötig.

Nachteile:

- du musst einen separaten Editor und Protokoll erlernen;
- Schnittstelle ist oft im Bildschirm gespeichert;
- schwieriger, UI- und Gerätfirmware-Versionen synchron zu halten;
- Nicht alle Elemente verhalten sich wie in einer regulären App;
- Bildschirmwechsel kann Neuentwurf erfordern.

Für ein einfaches Gerät kann Smart Display eine gute Lösung sein, wenn du ein schönes Bedienfeld ohne Linux-Host brauchst. Aber es ist kein "normaler Monitor": es ist ein separates Modul mit eigener Logik.

## Gehäuse, Kabel und Wartung

Ein Touchscreen ist etwas, das Benutzer mit ihren Händen berühren werden. Also ist Mechanik wichtig, nicht nur Drähte.

Überprüfe im Voraus:

- Der Bildschirm befindet sich nicht in einer heißen Zone.
- es gibt eine Rahmen oder Schutzhalterung;
- Kabel biegt sich nicht scharf, wenn die Abdeckung geöffnet wird;
- Kabel kann zur Wartung getrennt werden;
- Stecker kann nicht rückwärts eingeführt werden;
- Gehäuse drückt nicht auf den Bildschirm;
- es gibt Zugang zu SD-Karte oder USB für Updates, wenn nötig;
- Benutzer berührt keine Stromteile beim Bildschirmgebrauch;
- Touch-/Display-Verdrahtung ist von Heizer-Drähten getrennt.

Für Geräte mit Heizer ist es besser, den Bildschirm in die Benutzerzone zu verschieben, weg von heißer Luft und Stromteilen.

## Was vor dem Kauf zu überprüfen ist

Vor dem Kauf eines Touchscreens überprüfe:

- Diagonale und Auflösung;
- Display-Typ: raw TFT, Smart UART, Printer TFT, HDMI/DSI;
- Display-Schnittstelle;
- Touch-Schnittstelle;
- Display-Controller: zum Beispiel `ILI9341`, `ILI9488`, `ST7789`;
- Touch-Controller: zum Beispiel `XPT2046`, `FT5x06`, `GT911`;
- Stromversorgung und Hintergrundbeleuchtungsstrom;
- Logikpegel;
- Unterstützung in der Firmware;
- Verfügbarkeit von Dokumentation und Beispielen;
- Verfügbarkeit von Bibliotheken;
- RAM/PSRAM-Anforderungen;
- Board-Dimensionen, Löcher und Kabel;
- Betriebstemperatur;
- Firmware-/Interface-Update-Methode.

Wenn die Produktbeschreibung Display-Controller, Schnittstelle, Stromversorgung und Verbindungsbeispiele fehlen, ist es besser, solch einen Bildschirm für dein erstes Projekt nicht zu verwenden.

## Typische Fehler

- Bildschirm "für Arduino" gekauft, aber das Projekt ist KlipperScreen auf Linux;
- HDMI-Bildschirm gekauft und versucht, direkt mit ESP32 zu verbinden;
- UART Smart Display gekauft, aber erwartet, dass es wie ein normales TFT funktioniert;
- raw TFT gewählt, aber Zeit für Menü und Grafikcode nicht geplant;
- nicht genug GPIO für SPI-Display und Touch-Controller;
- nicht genug RAM für Bildschirmpuffer;
- Touch-Controller nicht überprüft;
- resistiven Touch nicht kalibriert;
- Bildschirm flimmert aufgrund schwacher Hintergrundbeleuchtungsstromversorgung;
- Kabel läuft neben Heizer-Stromversorgungsleitungen;
- Bildschirm in heißer Zone montiert;
- Schnittstelle sieht schön aus, aber Hauptfehler ist schwer zu sehen.

## Hauptpunkt

Wähle einen Touchscreen nach Architektur, nicht nach Diagonale. Entscheide zuerst, wer die Schnittstelle zeichnet: Mikrocontroller, der Bildschirm selbst, Printer-Firmware oder Linux-Host. Überprüfe dann Schnittstelle, Stromversorgung, Touch-Controller, Firmware-Unterstützung und Gehäusemechanik.

Für einen einfachen Heizer, Trockner oder Filter reichen normalerweise OLED, Tasten oder Web-Interface aus. Verwende einen Touchscreen, wenn Benutzer wirklich eine lokale Schnittstelle benötigen.

## Referenzmaterialien

- [KlipperScreen: Hardware](https://klipperscreen.github.io/KlipperScreen/Hardware/) - Anforderungen und Bildschirmbeispiele für KlipperScreen, einschließlich HDMI/DSI/Raspberry-Pi-Optionen.
- [BIGTREETECH TouchScreenFirmware](https://github.com/bigtreetech/BIGTREETECH-TouchScreenFirmware) - Firmware und BTT TFT-Modi: Touch-Modus, Marlin/12864-Emulation, EXP-Stecker und Einstellungen.
- [BIGTREETECH TFT35 V3.0 Repository](https://github.com/bigtreetech/BIGTREETECH-TFT35-V3.0) - Dokumentation und Dateien für beliebte 3D-Printer-TFT35.
- [Adafruit 3,5-Zoll-TFT-Touchscreen-Breakout](https://learn.adafruit.com/adafruit-3-5-color-320x480-tft-touchscreen-breakout) - Beispiel von raw TFT mit SPI/8-Bit-Modi, separatem Touch und Bibliotheken.
- [ESPHome: Touchscreen-Komponenten](https://esphome.io/components/touchscreen) - Dokumentation zu Touch-Komponenten, Kalibrierung und Verknüpfung von rohen Touch-Koordinaten zu Display-Koordinaten.
- [ESPHome: ILI9xxx TFT LCD Series](https://esphome.io/components/display/ili9xxx/) - Beispiel der raw TFT-Display-Unterstützung auf ESPHome und wichtige Speicherbegrenzungen.
