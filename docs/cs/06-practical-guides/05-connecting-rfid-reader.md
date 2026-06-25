# Připojení čtečky RFID

RFID/NFC čtečka umožňuje číst kartu, štítek nebo přívěšek bez drátového kontaktu.

V zařízeních podobných iDryer-u to může být užitečné pro identifikaci cívky, výběr profilu materiálu, přístup k servisu nebo experimenty s sledováním spotřeby.

Hlavní chyba: koupíte "RFID modul" a předpokládáte, že jakákoli karta se bude čist z jakékoli vzdálenosti na jakémkoli kontroléru. Ve skutečnosti musíte ověřit frekvenci, typ štítku, rozhraní, napájení, logické úrovně a umístění antény.

## Populární moduly

Běžné moduly zahrnují:

- RC522 / MFRC522;
- PN532;
- hotové USB/UART RFID čtečky;
- NFC moduly s I2C, SPI nebo UART.

Pro jednoduché 3D tiskárny projekty jsou nejběžnější 13.56 MHz moduly a štítky: karty, přívěšky, NTAG/MIFARE kompatibilní štítky.

## Co kontrolovat před připojením

Před připojením najděte:

- frekvenci modulu;
- podporované typy karet a štítků;
- rozhraní: SPI, I2C nebo UART;
- napájecí napětí;
- logické úrovně;
- rozpis pinů desky;
- výběr rozhraní přes jumper nebo pájecích můstek;
- vzdálenost čtení;
- požadavky na anténu a umístění.

Pokud je modul hodnocen na `3.3V`, nemůžete jej jednoduše připojit na `5V` logiku bez kontroly. Některé desky mají napěťové regulátory, ale postrádají úpravu logických úrovní na signálních vodičích.

## RC522: typické SPI připojení

Levné moduly RC522 obvykle běží na `3.3V` a nejčastěji se připojují přes SPI.

Typické linky:

- `VCC` - napájení `3.3V`;
- `GND` - zem;
- `SCK` - SPI signál hodin;
- `MOSI` - data z kontroléru na modul;
- `MISO` - data z modulu na kontrolér;
- `SDA`, `SS` nebo `CS` - SPI výběr čipu;
- `RST` - reset;
- `IRQ` - přerušení, často nepoužívané v jednoduchých projektech.

![RFID modul RC522 (MFRC522) pro čtení 13.56 MHz karet](../../img/06-practical-guides/05-rfid-rc522-module.jpg)

*Zdroj: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:RFID-RC522_photo.jpg), Giacomo Alessandroni, CC BY-SA 4.0*

Názvy pinů se mohou lišit. Například na RC522 pin `SDA` často znamená `SS`/`CS` pro SPI, ne I2C linku `SDA`. To je běžný zdroj zmatku.

## PN532: SPI, I2C nebo UART

PN532 je flexibilnější modul. V závislosti na desce se může jednat:

- SPI;
- I2C;
- UART.

Ale nemůžete se jednoduše připojit na jakékoli piny. Na mnoha PN532 deskách je rozhraní vybráno jumper, DIP přepínače nebo pájecím můstkem.

Před připojením zkontrolujte:

- které rozhraní je fyzicky vybráno na desce;
- které piny odpovídají vybranému rozhraní;
- zda jsou potřebné pull-up rezistory pro I2C;
- zda je potřeba pull-up nebo reset pin;
- zda jsou logické úrovně kompatibilní s kontrolérem.

Pokud deska říká "3.3V logika", nepřipojujte jej přímo na 5V GPIO.

## Společná zem

Jako ostatní moduly, je potřeba společná zem.

Pokud je RFID modul napájen z jednoho zdroje a kontrolér z druhého, jejich `GND` musí být připojeny.

Bez společné zemi se SPI/I2C/UART nemusí fungovat nebo funguje nestabilně.

## Štítek musí odpovídat čtečce

RFID/NFC není jediný univerzální standard.

Modul může fyzicky číst pouze štítky podporované jeho čipem a knihovnou.

Zkontrolujte:

- frekvenci štítku;
- typ karty nebo přívěšku;
- podporuje modul MIFARE, NTAG, ISO14443A nebo potřebný typ;
- potřebujete pouze číst UID nebo také číst/psát data;
- podporuje zvolená knihovna potřebnou operaci.

Pro jednoduchy výběr profilu materiálu stačí často pouze čtení UID štítku a uložení mapování UID -> materiál v firmwaru nebo hostitelu.

## Vzdálenost čtení

Vzdálenost čtení pro malé RFID/NFC moduly je obvykle krátká.

Výsledky závisí na:

- velikosti antény;
- typu štítku;
- orientaci štítku;
- vzdálenosti;
- plastu v pouzdru;
- nedalekého kovu;
- interferenci;
- výkonu modulu.

Kov blízko antény může výrazně zhoršit čtení. Pokud je čtečka namontována v sušičce, komoře nebo držáku cívky, testujte vzdálenost ve skutečné montáži, ne jen na lavici.

## Kde umístit čtečku

Pro cívku s filamentem je nejlepší umístit RFID/NFC čtečku tam, kde uživatel záměrně přináší štítek.

Nenavrhujte logiku za předpokladu, že se štítek bude vždy automaticky číst.

Praktické možnosti:

- "přineš štítek sem" zóna na pouzdru;
- umístění blízko držáku cívky;
- servisní zóna pro přístupovou kartu;
- oddělený panel s krátkou vzdáleností čtení.

Pokud je štítek na cívce, testujte s různými cívkami, různými orientacemi štítků, různými plasty a blízkostí kovu.

## První spuštění

Před integrací:

1. Připojte modul na lavici.
2. Spusťte příklad z knihovny pro váš modul.
3. Ověřte, že se karta nebo štítek čtou stabilně.
4. Zaznamenejte UID několika štítků.
5. Zkontrolujte, že nepodporované karty neprolomí logiku.
6. Namontujte modul v pouzdru a znovu testujte.

V tomto stadiu nebudujte složité systémy profilů hned. Nejdřív dosáhněte stabilního čtení UID.

## Příklad logiky zařízení

Pro profil materiálu může být jednoduchá logika:

1. Uživatel přináší štítek.
2. Zařízení čte UID.
3. UID se vyhledá v tabulce.
4. Pokud je UID známo, je vybrán profil materiálu.
5. Pokud je UID neznámé, zařízení vyzývá k ručnímu výběru profilu.

RFID by neměl být jedinou metodou řízení. Potřebujete manuální zálohu: profil v menu, tlačítko, obrazovka nebo nastavení rozhraní.

## Co kontrolovat po montáži

Ověřte:

- modul dostává správné napjetí;
- logické úrovně jsou kompatibilní s kontrolérem;
- správné rozhraní je vybráno;
- `MOSI`, `MISO`, `SCK`, `CS` nejsou pro SPI;
- `SDA`, `SCL` nejsou zaměněny pro I2C;
- `TX` a `RX` jsou správně zkřížené pro UART;
- existuje společná zem;
- reset/IRQ jsou připojeny podle požadavků knihovny;
- štítky správného typu se čtou;
- vzdálenost čtení je normální v pouzdru;
- kov a vodiče neblokují anténu;
- zařízení funguje normálně, pokud se štítek nečte.

## Běžné chyby

- připojení 3.3V RC522 na 5V napájení nebo 5V logiku;
- zaměňování RC522 `SDA` s I2C `SDA`;
- zapomenutí `CS`/`SS` na SPI;
- prohození `MOSI` a `MISO`;
- výběr jednoho rozhraní na PN532 s jumper, ale zapojení jiného;
- použití nepodporovaného typu karty;
- umístění antény přímo vedle kovu;
- testování vzdálenosti čtení na lavici, ale ne v pouzdru;
- vytvoření RFID jedinou metodou výběru profilu;
- uložení důležité logiky pouze v UID bez kontroly chyby čtení.

## Klíčové body

- RFID/NFC modul musí být zvolen pro specifické štítky a rozhraní.
- RC522 obvykle potřebuje `3.3V` a SPI.
- PN532 se může fungovat přes SPI, I2C nebo UART, ale rozhraní musí být vybráno na desce.
- Společná zem je vyžadována.
- Kov blízko antény může výrazně zhoršit čtení.
- Pro profily materiálu stačí UID štítku, ale potřeba manuální výběr zálohy.
- Testujte v skutečném pouzdru, ne jen na lavici.

## Související čtení

- [Adafruit: PN532 RFID/NFC Breakout Wiring](https://learn.adafruit.com/adafruit-pn532-rfid-nfc/breakout-wiring) - připojení PN532, výběr rozhraní SPI/I2C/UART a varování logiky 3.3V.
- [Adafruit: PN532 RFID/NFC průvodce, jednotná stránka](https://learn.adafruit.com/adafruit-pn532-rfid-nfc?view=all) - úplný průvodce PN532, zapojení, CircuitPython, Raspberry Pi a výběr rozhraní.
- [Stránka produktu Adafruit PN532](https://www.adafruit.com/product/364) - schopnosti PN532, podpora NFC/RFID štítků a rozhraní 3.3V UART/I2C/SPI.
- [NXP: MFRC522 Standardní výkonný MIFARE a NTAG frontend](https://www.nxp.com/products/rfid-nfc/nfc-hf/nfc-readers/standard-performance-mifare-and-ntag-frontend:MFRC52202HN1) - oficiální stránka MFRC522/RC522 pro 13.56 MHz MIFARE/NTAG scénáře.
- [DigiKey: Specifikace MFRC522 od NXP](https://www.digikey.com/htmldatasheets/production/993456/0/0/1/mfrc522.html) - technická specifikace MFRC522: podporované karty, napájení, komunikační rozhraní s kontrolérem a vliv antény/napájení na vzdálenost.
