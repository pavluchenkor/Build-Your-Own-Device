# Touchscreen (TFT)

Ein Touchscreen ist ein farbiges Display mit Touch-Erkennung. Im Gegensatz zu OLED-Bildschirmen (schwarz-weiß oder wenig Farbe) können TFT-Bildschirme Farbe anzeigen.

In iDryern werden Touchscreens für komplexere Bedienoberflächen verwendet: Menü-Navigation, Grafiken, Echtzeit-Kurven.

## Wo es verwendet wird

In iDryern und ähnlichen Geräten:

- Bedienoberfläche für den Benutzer;
- grafische Anzeige von Prozessparametern;
- Einstellung von Temperaturen und Zeiten;
- Visualisierung von Kurven (Temperatur über Zeit);
- Status-Anzeigen und Warnmeldungen.

Ein Touchscreen erfordert mehr Stromversorgung und Programmlogik als OLED.

## TFT-Schnittstellen

Typische TFT-Schnittstellen:

**SPI:**

- Schnell für kleine Bildschirme;
- normalerweise `5V` logisch;
- Pins: GND, VCC, SCK, MOSI, MISO, CS, DC, RESET.

**UART/Serial:**

- Langsamere Bild-Updates;
- einfacher zu verdrahten;
- vordefinierte AT-Befehle zum Zeichnen.

**Parallel (RGB/16-bit):**

- Schnellste Schnittstelle;
- benötigt viele GPIO-Pins;
- hauptsächlich auf großen Boards.

Für kleine Projektboards ist meist SPI oder UART praktisch.

## Größe und Auflösung

Typische Größen:

- 3,5" oder 4" (diagonale);
- Auflösung: 480x320 oder 320x240 typisch.

Größere Bildschirme brauchen mehr Speicher für Grafikpuffer. Ein 480x320-Bildschirm mit 16-Bit Farbe braucht etwa 307 kB RAM nur für den Puffer.

## Touch-Erkennung

Der Touchscreen hat zwei Teile:

1. **Display:** zeigt Bilder an;
2. **Touchpanel:** erkennt Berührungen über Widerstandsänderung oder kapazitive Änderung.

Die Touch-Daten werden normalerweise über UART oder ein anderes Protokoll übertragen.

Überprüfen Sie:

- ob Touch getrennt verdrahtet ist;
- Touch-Auflösung und Kalibrierungsbereich;
- Koordinaten-Mapping (Bildschirm-Koordinaten vs. Touch-Koordinaten).

## Stromversorgung

Ein TFT-Bildschirm verbraucht mehr als OLED:

- Display: `50-200 mA`;
- Hintergrundbeleuchtung: `100-300 mA` (wenn vorhanden);
- Total: `150-500 mA` abhängig von Größe und Typ.

Ein schwacher Stromversorger kann Flackern oder Instabilität verursachen.

## Firmware-Unterstützung

Die meisten Touchscreens brauchen Hersteller-spezifische Firmware oder AT-Befehlssätze:

- Arduino/ESP32: UART-Kommunikation möglich;
- Klipper: eingeschränkter Support für Touchscreens;
- custom Firmware: häufig erforderlich für komplexe GUIs.

Touchscreens sind komplexer als OLED-Bildschirme in der Firmware-Integration.

## Kalibrierung und Koordinaten

Der Touchscreen braucht Kalibrierung, um korrekt auf Berührungen zu reagieren:

- Bildschirm-Auflösung: z.B. 480x320;
- Touch-Rohwerte: z.B. 0-4095;
- Kalibrierungspunkte: normalerweise 3-4 Punkte.

Eine schlechte Kalibrierung führt dazu, dass Berührungen falsch erkannt werden.

## Wärme und Sichtbarkeit

Ein TFT mit Hintergrundbeleuchtung kann in heißer Umgebung Probleme haben:

- Hintergrundbeleuchtung wird dunkler bei Hitze;
- Display kann bei sehr hoher Temperatur beschädigt werden;
- typischer Betriebsbereich: `0-50°C`.

Ein Kühlkörper oder Belüftung kann helfen.

## Was vor dem Kauf zu überprüfen ist

Vor dem Kauf überprüfen Sie:

- Größe und Auflösung;
- Schnittstelle (SPI, UART, parallel);
- ob Touch enthalten ist;
- Betriebsspannung (normalerweise 5V);
- Stromverbrauch;
- Größe und Form;
- Touch-Auflösung und Genauigkeit;
- Hintergrundbeleuchtung (Ström und Helligkeitssteuerung);
- Verfügbarkeit von Dokumentation oder Code-Beispielen;
- Betriebstemperaturbereich.

Für ein Anfängerprojekt: ein kleines `3,5"` UART-TFT mit Touch.

## Typische Fehler

- falsche Spannungsversorgung;
- zu schwache Stromversorgung (Flackern, Instabilität);
- falsche Schnittstellen-Protokolleinstellung;
- SPI-Pins vertauscht;
- Touch nicht kalibriert;
- Koordinaten nicht korrekt gemappt;
- Display zu nah an Heizer;
- Hintergrundbeleuchtung an falsches Steuersignal;
- Firmware-Unterstützung nicht vorhanden.

## Hauptpunkt

Ein Touchscreen ist komplexer als ein einfacher OLED-Bildschirm. Überprüfen Sie Schnittstelle, Stromversorgung, Touch-Kalibrierung und Firmware-Unterstützung sorgfältig. Bei Anfängern: UART-basierte Bildschirme sind einfacher als reine SPI.

## Referenzmaterialien

- [Seeed Studio: UART LCD Module](https://wiki.seeedstudio.com/2.8-inch-TFT-Touch-Shield-v2.0/) - UART-basierter Touchscreen, Befehle, Kalibrierung.
- [ITDB: TFT LCD Library](http://henningkarlsen.com/electronics/library.php?id=52) - Beliebte Arduino-Bibliothek für TFT-Bildschirme.
- [4D Systems: Serial LCD Protocol](https://4dsystems.com.au/products/uLCD) - Beispiel von seriellen (UART) Touchscreen-Protokollen.
