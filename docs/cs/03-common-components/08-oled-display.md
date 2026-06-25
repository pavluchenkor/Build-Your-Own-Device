# OLED displej

OLED displej je malá obrazovka pro zobrazení textu, čísel, jednoduchých ikon a stavu zařízení. Na rozdíl od běžného LCD se OLED sám osvětluje a nevyžaduje samostatné podsvícení. Malé OLED moduly jsou tedy čitelné, zabírají málo místa a jsou vhodné pro jednoduchá DIY zařízení.

V zařízení podobném iDryer může OLED zobrazovat teplotu, vlhkost, pracovní režim, chybu, stav Wi-Fi, zbývající filament nebo aktuální fázi sušení.

## Kdy je OLED užitečné

OLED stojí za to přidat, pokud uživatelé potřebují vidět stav zařízení přímo na krytu:

- aktuální teplota v komoře;
- vlhkost;
- cílová teplota;
- pracovní režim;
- časovač;
- chyba senzoru;
- stav ventilátoru nebo topení;
- stav připojení;
- jednoduchá nabídka bez velkého displeje.

Pokud je zařízení vždy spravováno přes Klipper, webové rozhraní nebo mobilní aplikaci, může být samostatné OLED zbytečné. Přidává přívody, prostor na krytu, kód a další bod selhání.

## Typické velikosti a řadiče

Nejčastější malé OLED moduly:

- `128x32` pixelů;
- `128x64` pixelů;
- úhlopříčka přibližně `0.91"` nebo `0.96"`;
- jednobarevné: bílé, modré, žluto-modré;
- s řadičem `SSD1306` nebo podobným `SH1106`.

`SSD1306` a `SH1106` vypadají podobně, ale v kódu nejsou vždy plně kompatibilní. Pokud je knihovna nastavena pro `SSD1306`, ale modul je vlastně `SH1106`, obrazovka může zobrazovat posuntý obraz, nesmysl nebo vůbec nefungovat.

Před nákupem je důležité kontrolovat nejen velikost obrazovky, ale také řadič, rozhraní a napájecí napětí.

## I2C a SPI

Malé OLED moduly se obvykle připojují přes I2C nebo SPI.

Modul I2C má obvykle 4 kontakty:

- `VCC`;
- `GND`;
- `SDA`;
- `SCL`.

Modul SPI obvykle potřebuje více linek:

- `VCC`;
- `GND`;
- `SCK`/`CLK`;
- `MOSI`/`DIN`;
- `CS`;
- `DC`;
- někdy `RST`.

I2C je jednodušší na zapojení a obvykle stačí na stav, teplotu a jednoduchou nabídku. SPI je rychlejší a lepší, pokud se obrazovka často překresluje, ale pro malý displej se stavem to zřídka kritické.

![Connecting I2C OLED display to controller](../../img/03-common-components/08-oled-i2c-wiring.jpg)

*Source: [Adafruit Learning System](https://learn.adafruit.com/adafruit-128x64-oled-featherwing/), CC BY-SA 3.0*

## Napájení a logické úrovně

OLED modul může být hodnocen na `3.3V`, na `5V`, nebo má regulátor a posun úrovně na desce. Zvenčí mohou takové moduly vypadat téměř totožně.

Před připojením zkontrolujte:

- jaké napájení je uvedeno na modulu nebo na stránce produktu;
- zda jsou linky `SDA`/`SCL` kompatibilní s logikou řadiče;
- zda má modul I2C Pull-up rezistory;
- zda Pull-upy nekonfrontují napětí řadiče.

Pro ESP32 a většinu moderních mikrořadičů je bezpečnější předpokládat logiku `3.3V`. Pokud OLED modul táhne I2C na `5V`, to může být problematické pro kontroler `3.3V`.

Mnoho populárních I2C OLED modulů funguje z `3.3V` a připojuje se přímo k ESP32, ale musíte kontrolovat konkrétní modul.

## Adresa I2C

I2C OLED má často adresy:

- `0x3C`;
- `0x3D`.

Pokud obrazovka nereaguje, adresa je první věc, kterou zkontrolovat po napájení a vodičích. Některé moduly umožňují změnit adresu přes jumper nebo pájením malého jumperu na desce.

Příznaky nesprávné adresy:

- sketch nebo firmware se spustí, ale obrazovka je prázdná;
- I2C skener vidí zařízení na jiné adrese;
- knihovna inicializuje displej bez viditelného výsledku;
- změna `0x3C` na `0x3D` to zprovozní.

## Co zobrazit na malé obrazovce

OLED `128x32` nebo `128x64` má velmi málo místa. Nepokoušejte se na něj vytvářet celé rozhraní smartphonu.

Dobrá sada pro sušičku nebo ohřívač:

- velká aktuální teplota;
- cílová teplota;
- vlhkost, pokud máte senzor;
- režim: `HEAT`, `DRY`, `IDLE`, `ERROR`;
- malá ikona ventilátoru/tepla;
- kód chyby nebo krátká zpráva.

Špatná sada:

- dlouhé věty;
- malé tabulky;
- mnoho položek nabídky na jedné obrazovce;
- neustále posouvající se text;
- dekorativní animace místo užitečného stavu.

Pro zařízení s topným tělesem je důležitější rychle vidět chybu než hezkou úvodní obrazovku.

## Vypalování a jas

OLED pixely stárnou ze svícení. Pokud na jednom místě dlouhé hodiny zobrazujete stejný jasný text, může se nakonec objevit stopa.

Pro DIY zařízení to vždy není kritické, ale je lepší:

- neuchovávat jas na maximu bez potřeby;
- vypnout obrazovku po nečinnosti;
- občas přesunout statické prvky;
- neustále neukazovat bílou výplň;
- používat krátké aktualizace místo další animace.

V teplé komoře nebo poblíž topného tělesa OLED také hůř trvá. Lepší je udržovat elektroniku v zóně s kontrolovanou teplotou nepřesahující rozsah modulu.

## Délka vodiče a interference

I2C se nemá rádo dlouhé vodiče, obzvláště poblíž motorů, topných těles a vedení elektrické sítě. Pokud je OLED na dveřích nebo odnímatelném panelu, dlouhý pružný kabel se může stát zdrojem rušení.

Praktická pravidla:

- udržujte `SDA` a `SCL` krátké;
- vychylte je pryč od napájecích drátů topného tělesa;
- používejte společné `GND`;
- nevytvářejte konektor, který by šel dozadu;
- pro odnímatelný kryt použijte správný konektor a ochranu před tahem;
- pokud je I2C nestabilní, nejdříve zkraťte vodiče a zkontrolujte Pull-upy.

SPI obvykle toleruje vyšší rychlost aktualizace lépe, ale má více vodičů a chyby připojení jsou běžnější.

## OLED nebo dotykový displej

OLED je vhodný pro zobrazení stavu. Nevyřeší problém vstupu bez tlačítek, otočného kódovače nebo jiného ovládání.

Pokud uživatelé často potřebují měnit nastavení přímo v zařízení, možná budete potřebovat:

- otočný kodér + OLED;
- několik tlačítek + OLED;
- TFT displej;
- dotykový displej;
- webové rozhraní nebo aplikace.

Neinstalujte dotykový displej jen proto, že se vám OLED zdá malý. U jednoduchých zařízení je malý OLED s jedním tlačítkem někdy spolehlivější a jasnější.

## Co zkontrolovat před nákupem

Před nákupem OLED modulu zkontrolujte:

- velikost: `128x32`, `128x64` nebo jinou;
- řadič: `SSD1306`, `SH1106`, `SH1107`;
- rozhraní: I2C nebo SPI;
- napájení: `3.3V`, `5V` nebo rozsah;
- logickou úroveň;
- adresu I2C, pokud je uvedena;
- podporu pin Reset;
- podporu v zvoleném firmware nebo knihovně;
- fyzické rozměry desky a montážní otvory;
- umístění konektoru;
- provozní teplotu;
- barvu a čitelnost v potřebném úhlu.

Pro zařízení ESP32 je I2C OLED `128x64` na `SSD1306` s adresou `0x3C` obvykle nejvýhodnější. Pro desku Klipper zkontrolujte, zda konkrétní deska podporuje váš zvolený sběrnici a jak je displej popsán v konfiguraci.

## Typické chyby

- záměna `SDA` a `SCL`;
- připojení napájení na nesprávné napětí;
- nekontrolování adresy I2C;
- výběr `SSD1306` v kódu, ale modul je `SH1106`;
- příliš dlouhé vodiče I2C;
- zapomenutí společného `GND`;
- připojení modulu Pull-up 5V do kontroleru 3.3V bez kontroly;
- výběr modulu SPI očekávajícího 4 piny jako I2C;
- umístění obrazovky v horké zóně;
- přidání displeje bez pochopení, jaký problém řeší uživatelům.

## Hlavní bod

OLED displej je vhodný pro krátký stav a jednoduché místní rozhraní. U většiny DIY zařízení je I2C OLED `128x64` dostačující, pokud je kompatibilní s napájením a podporován zvoleným firmware.

Před připojením zkontrolujte řadič displeje, rozhraní, napájení, adresu I2C a délku vodiče. Pokud je zařízení již vhodné prostřednictvím webového rozhraní, OLED nemusí být potřebné.

## Reference Materials

- [Adafruit: Monochrome OLED Breakouts](https://learn.adafruit.com/monochrome-oled-breakouts) - practical guide to small SSD1306 OLED, I2C/SPI connection, sizes and examples.
- [SparkFun: Qwiic Micro OLED Hookup Guide](https://learn.sparkfun.com/tutorials/qwiic-micro-oled-hookup-guide) - example of I2C OLED module, library and text/graphics output.
- [ESPHome: SSD1306 OLED Display](https://esphome.io/components/display/ssd1306) - documentation on `ssd1306_i2c`, `ssd1306_spi`, addresses, SSD1306/SH1106 models and configuration.
- [Klipper Configuration Reference: display](https://www.klipper3d.org/Config_Reference.html#display) - display support in Klipper, including `ssd1306` and `sh1106`.
- [SSD1306 Datasheet: Solomon Systech](https://www.radiolocman.com/datasheet/pdf.html?di=168297) - technical description of SSD1306 controller: resolution, I2C/SPI/parallel interfaces and commands.
