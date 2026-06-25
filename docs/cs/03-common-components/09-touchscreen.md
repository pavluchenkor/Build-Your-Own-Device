# Dotykový displejs

Dotykový displej není jen displej. Je to displej plus uživatelský vstup. Nesmí jen zobrazovat teplotu nebo tlačítko, ale musí zařízení říci, kde jste se dotknuli.

Z tohoto důvodu je dotykový displej téměř vždy složitější než OLED. Musíte si vybrat nejen velikost a rozlišení, ale pochopit, kdo kreslí rozhraní, kdo zpracovává dotyky, jaké rozhraní se používá a zda váš zvolený firmware to podporuje.

## Kdy je dotykový displej užitečný

Dotykový displej má smysl, pokud zařízení potřebuje úplné místní rozhraní:

- volba režimu sušení;
- nastavení teploty a času;
- seznam profilů materiálu;
- potvrzení chyb;
- ruční řízení ventilátoru, osvětlení nebo tlumiče;
- nastavení Wi-Fi;
- zobrazení stavu bez telefonu nebo počítače.

Pokud potřebujete pouze zobrazit teplotu, chybu a režim, obvykle stačí OLED, pár tlačítek, otočný kodér nebo webové rozhraní. Dotykový displej přidává náklady, energii, prostor na krytu, firmware, kabely a další bod selhání.

## Hlavní otázka: Kdo kreslí rozhraní

Než budete nakupovat, odpovězte na hlavní otázku: kde žije uživatelské rozhraní.

Existuje několik různých tříd obrazovek:

![Třídy dotykových displejů a kdo kreslí rozhraní](../../img/03-common-components/09-touchscreen-classes.svg)

Raw TFT je jednoduchá obrazovka s řadičem jako `ILI9341`, `ILI9488`, `ST7789`, plus samostatný dotykový řadič jako `XPT2046` nebo `FT5x06`. Vaš mikrořadič nebo firmware kreslí rozhraní. To je flexibilní, ale vyžaduje kód, paměť, ovladače a kalibraci.

Chytrý UART/HMI displej je obrazovka s vlastním firmware a editorem rozhraní, jako Nextion. Mikrořadič odesílá příkazy přes UART a obrazovka zobrazuje stránky a prvky. To snižuje zátěž MCU, ale váš projekt váže na nástroje a protokol té obrazovky.

Printer TFT, jako BTT TFT35, má často svůj vlastní režim dotykové obrazovky přes UART a klasickou emulaci LCD 12864 přes konektory EXP. Tato obrazovka je vhodná pro desky Marlin/3D tiskárny, ale není univerzálním panelem pro jakékoli DIY zařízení.

HDMI/DSI/USB obrazovka pro hostitele Linux funguje jako běžný monitor a dotykové zařízení pro Raspberry Pi nebo jiný počítač Linux. To je vhodné pro KlipperScreen, ale nepřipojuje se přímo k malému ESP32 jako jednoduchý modul.

## Rozhraní připojení

Dotykové displeje používají různá rozhraní.

Běžné možnosti:

- SPI - často na malém TFT pro ESP32/Arduino;
- I2C - často na kapacitních dotykových řadičích, někdy na dotykových řadičích;
- UART - na chytrých displejích a některých TFT 3D tiskáren;
- EXP1/EXP2/EXP3 - na obrazovkách kompatibilních s deskami 3D tiskáren;
- HDMI + USB - na Linux obrazovkách pro Raspberry Pi;
- DSI - na některých Raspberry Pi obrazovkách;
- paralelní RGB/8080 - na rychlejších TFT, ale více vodičů a požadavků.

Nemůžete si vybrat obrazovku pouze podle úhlopříčky. Dvě obrazovky `3.5"` mohou být zcela odlišné: jeden SPI modul pro ESP32, druhý UART panel s vlastním firmware, třetí HDMI obrazovka pro Raspberry Pi.

## Rezistivní a kapacitní dotek

Část dotyku se také liší.

Rezistivní dotek:

- reaguje na tlak prstem, stylusem nebo nehtem;
- často vyžaduje kalibraci;
- obvykle horší pro gesta;
- může být levnější;
- najde se s řadiči jako `XPT2046`.

Kapacitní dotek:

- reaguje na prst;
- obvykle se používá lépe;
- může podporovat více dotykův;
- často má samostatný řadič, jako je rodina `FT5x06`, `GT911`;
- funguje hůře s tlustými rukavicemi a některými ochranným kryty.

Pro zařízení v dílně je rezistivní dotek někdy praktičtější, protože na něj můžete stisknout nehtem nebo stylusem. Pro hezký panel na krytu se kapacitní dotek obvykle cítí modernější.

## Napájení, podsvícení a proud

TFT obrazovka kreslí více než malý OLED. Hlavním spotřebitelem energie je podsvícení.

Před připojením zkontrolujte:

- screen power voltage;
- backlight current;
- whether you need a separate 5V source;
- zda je nastavitelný jas podsvícení;
- zda jsou logické úrovně kompatibilní;
- zda obrazovka přetěžuje regulátor desky;
- zda se při zapnutí podsvícení sníží napájení.

Pokud obrazovka zbělá, bliká, restartuje ovladač nebo ztratí dotykové události, nejprve zkontrolujte napájení a kostru, nikoli kód rozhraní.

U zařízení s ohřívačem by obrazovka neměla být napájena náhodně slabým kolíkem. Mělo by být součástí správného schématu napájení s jasnou rezervou.

## Firmware a kompatibilita

Krásná obrazovka je k ničemu, pokud váš zvolený firmware ji nepodporuje.

Pro přístup ESP32/Arduino musíte zkontrolovat:

- existuje ovladač displeje;
- existuje ovladač dotykového řadiče;
- máte dost GPIO;
- máte dost RAM/PSRAM pro vyrovnávací paměť;
- jaký grafický framework se používá;
- kdo bude psát nabídku.

Pro ESPHome zkontrolujte podporu konkrétního ovladače displeje a komponenty dotykové obrazovky. Například zobrazení ILI9xxx a dotek XPT2046 potřebují SPI a samostatnou konfiguraci a rezistivní dotek potřebuje kalibraci.

Pro Klipper existují obvykle dva různé světy:

- malé displeje připojené k MCU a popsané v konfiguraci Klipperu;
- KlipperScreen na hostiteli Linux, kde obrazovka funguje jako monitor a dotykové zařízení.

KlipperScreen obvykle potřebuje obrazovku, kde může Linux zobrazit plochu nebo konzoli. To není totéž jako malý UART TFT připojený k desce tiskárny.

Pro Marlin/desky tiskáren zkontrolujte, zda konkrétní obrazovka podporuje potřebný režim: režim dotykové UART, emulaci 12864, EXP1/EXP2/EXP3, konkrétní typ řadiče v konfiguraci firmware.

## Chytrý displej a obrazovky podobné Nextion

Chytrý displej je vhodný, protože obrazovka ukládá stránky, tlačítka, fonty a obrázky. Kontroler odesílá příkazy přes UART a získává dotykové události.

Výhody:

- menší zatížení mikrořadiče;
- méně grafického kódu v hlavním firmware;
- rozhraní můžete kreslit v editoru obrazovky;
- potřebný pouze UART a napájení.

Nevýhody:

- musíte se naučit samostatný editor a protokol;
- rozhraní je často uloženo v obrazovce;
- obtížnější udržovat UI a verze firmware zařízení v synchronizaci;
- ne všechny prvky se chují jako v běžné aplikaci;
- výměna obrazovky může vyžadovat přepracování.

Pro jednoduché zařízení může být chytrý displej dobré řešení, pokud potřebujete hezký panel bez hostitele Linux. Ale to není "normální monitor": je to samostatný modul s vlastní logikou.

## Kryt, kabely a obsluha

Dotykový displej je něco, čeho se uživatelé budou dotýkat svýma rukama. Mechanika proto záleží, ne jen vodiče.

Zkontrolujte předem:

- obrazovka není v horké zóně;
- existuje rám nebo ochranná montáž;
- kabel se při otevírání krytu neohýbá ostře;
- kabel lze odpojit pro obsluhu;
- konektor nemůže jít dozadu;
- kryt nestlačuje obrazovku;
- existuje přístup na kartu SD nebo USB pro aktualizace, pokud je potřeba;
- uživatel se nedotýká součástí napájení při používání obrazovky;
- vedení dotyku/displeje je odděleno od vedení topného tělesa.

Pro zařízení s topným tělesem je lepší přesunout obrazovku do uživatelské zóny, daleko od horkého vzduchu a součástí napájení.

## Co zkontrolovat před nákupem

Před nákupem dotykové obrazovky zkontrolujte:

- úhlopříčku a rozlišení;
- typ displeje: raw TFT, chytrý UART, printer TFT, HDMI/DSI;
- rozhraní displeje;
- dotykové rozhraní;
- řadič displeje: například `ILI9341`, `ILI9488`, `ST7789`;
- dotykový řadič: například `XPT2046`, `FT5x06`, `GT911`;
- napájení a proud podsvícení;
- logické úrovně;
- podporu ve firmware;
- dostupnost dokumentace a příkladů;
- dostupnost knihoven;
- požadavky na RAM/PSRAM;
- rozměry desky, otvory a kabel;
- provozní teplotu;
- metodu aktualizace firmware/rozhraní.

Pokud popisu produktu chybí řadič displeje, rozhraní, napájení a příklady připojení, je lepší takovou obrazovku pro svůj první projekt nepoužívat.

## Typické chyby

- koupeno obrazovku "pro Arduino", ale projekt je KlipperScreen na Linux;
- koupena HDMI obrazovka a pokus připojit ji přímo k ESP32;
- koupena UART chytrá obrazovka, ale očekáváno, že bude fungovat jako běžný TFT;
- zvolen raw TFT, ale neplánován čas na kód nabídky a grafiky;
- nedostatek GPIO pro displej SPI a dotykový řadič;
- nedostatek RAM pro vyrovnávací paměť obrazovky;
- nekontrolování dotykového řadiče;
- nekalibrování rezistivního dotyku;
- blikání obrazovky z důvodu slabého napájení podsvícení;
- kabel běží vedle drátů napájení topného tělesa;
- obrazovka namontována v horké zóně;
- rozhraní vypadá pěkně, ale hlavní chyba je těžko viditelná.

## Hlavní bod

Vyberte si dotykovou obrazovku podle architektury, ne úhlopříčky. Nejdříve se rozhodněte, kdo kreslí rozhraní: mikrořadič, samotná obrazovka, firmware tiskárny nebo hostitel Linux. Poté zkontrolujte rozhraní, napájení, dotykový řadič, podporu firmware a mechaniku krytu.

Pro jednoduchouhřívač, sušičku nebo filtr, obvykle stačí OLED, tlačítka nebo webové rozhraní. Použijte dotykovou obrazovku, pokud uživatelé opravdu potřebují místní rozhraní.

## Reference Materials

- [KlipperScreen: Hardware](https://klipperscreen.github.io/KlipperScreen/Hardware/) - requirements and screen examples for KlipperScreen, including HDMI/DSI/Raspberry Pi options.
- [BIGTREETECH TouchScreenFirmware](https://github.com/bigtreetech/BIGTREETECH-TouchScreenFirmware) - firmware and BTT TFT modes: touch mode, Marlin/12864 emulation, EXP connectors and settings.
- [BIGTREETECH TFT35 V3.0 repository](https://github.com/bigtreetech/BIGTREETECH-TFT35-V3.0) - documentation and files for popular 3D printer TFT35.
- [Adafruit 3.5 inch TFT Touchscreen Breakout](https://learn.adafruit.com/adafruit-3-5-color-320x480-tft-touchscreen-breakout) - example of raw TFT with SPI/8-bit modes, separate touch and libraries.
- [ESPHome: Touchscreen Components](https://esphome.io/components/touchscreen) - documentation on touch components, calibration and linking raw touch coordinates to display coordinates.
- [ESPHome: ILI9xxx TFT LCD Series](https://esphome.io/components/display/ili9xxx/) - example of raw TFT display support on ESPHome and important memory limitations.
