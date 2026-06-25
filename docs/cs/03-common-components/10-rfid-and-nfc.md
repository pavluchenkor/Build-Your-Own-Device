# RFID a NFC

RFID je identifikace na rádiové frekvenci. NFC je související technologie pro velmi krátký dosah, často na frekvenci `13.56 MHz`.

V jednoduchém DIY zařízení je to způsob, jak přečíst kartu, klíčenku, nálepku nebo štítek bez dráté ho kontaktu. Například uživatel přinese štítek s cívkou filamentu a zařízení vybere profil materiálu.

Hlavní chyba je myšlenka, že "RFID" znamená univerzální kompatibilitu. V praxi potřebujete shodu frekvencí, typ štítku, mikrořadič čtečky, knihovnu, rozhraní, napájení a umístění antény, aby se všechno vyrovnalo.

## Kde se používá

V projektech podobných iDryer lze RFID/NFC použít pro:

- identifying a filament spool;
- selecting a material profile;
- propojení nastavení s tagem;
- service access;
- user action confirmation;
- consumable tracking;
- experimenty se štítky na nádobách, cívkách nebo kazetách.

Pro výběr materiálového profilu často stačí pouze načtení UID tagu a uložení tabulky `UID -> material`. Tento přístup však musí mít ruční záložní řešení: pokud se značka nečte, uživatel může stále ručně vybrat profil.

## RFID a NFC v jednoduchých termínech

RFID je širokýterm. Zahrnuje různé frekvence, normy, dosahy a typy štítků.

NFC obvykle znamená komunikaci v blízkém poli na `13.56 MHz`, kompatibilní s částí ekosystému RFID. NFC je známý z bankovních karet, telefonů, NTAG nálepek a MIFARE karet, ale to neznamená, že nějaký čtečka NFC přečte jakoukoliv kartu a jakákoliv data.

Pro malá DIY zařízení jsou nejčastější moduly `13.56 MHz`:

- RC522 / MFRC522;
- PN532;
- hotové USB/UART čtečky RFID/NFC;
- NFC moduly s SPI, I2C nebo UART.

Existují další systémy RFID, jako `125 kHz` přístupové karty nebo UHF RFID. Nejsou kompatibilní s moduly NFC `13.56 MHz`.

## RC522

RC522 je levný a běžný modul `13.56 MHz` pro karty a štítky. Často se používá s Arduino a ESP32.

Pros:

- cheap;
- many examples;
- vhodné pro jednoduché čtení UID;
- obvykle se připojuje přes SPI.

Cons:

- často pracuje pouze s napájením a logikou `3.3V`;
- cheap module quality varies;
- rozsah čtení je malý;
- podpora typu karty je omezená;
- pin `SS` na desce často znamená `CS`/`SDA` pro SPI, ne I2C `SDA`.

RC522 funguje, pokud potřebujete číst UID z karet typu MIFARE nebo klíčenky na krátkou vzdálenost. Pro širší úlohy NFC je obvykle vhodnější PN532.

## PN532

PN532 je flexibilnější NFC/RFID ovladač. Mnoho modulů PN532 může pracovat prostřednictvím:

- SPI;
- I2C;
- UART.

Vybrané rozhraní je ale obvykle potřeba fyzicky nastavit na desce: propojky, DIP přepínače nebo pájení. Nemůžete připojit modul přes I2C, pokud je nastaven na režim SPI.

PN532 se často volí, pokud potřebujete:

- more interface options;
- better NFC scenario support;
- pracovat s různými typy značek;
- Python/CircuitPython/Raspberry Pi scenarios;
- better documented module.

Ale ani PN532 není kouzelná univerzální čtečka. Musíte zkontrolovat konkrétní typy karet, knihovnu a pracovní režim.

## Frekvence a typ štítku

Štítek musí odpovídat čtečce.

Před nákupem štítků zkontrolujte:

- frekvence: `13.56 MHz`, `125 kHz` nebo jiná;
- typ: MIFARE Classic, NTAG213/215/216, ISO14443A nebo jiný;
- zda potřebujete pouze přečíst UID;
- zda potřebujete číst/psát vlastní data;
- zda vaše zvolená knihovna podporuje potřebné operace;
- zda můžete fyzicky umístit štítek na cívku nebo kryt.

Pokud je úkolem vybrat profil materiálu, obvykle je jednoduší pouze přečíst UID a uložit profil zvlášť. Zápis dat do štítku komplikuje projekt: musíte myslet na formát dat, kompatibilitu, ochranu zápisu a chyby zápisu.

## UID - Ne bezpečnost

UID karty nebo štítku je vhodný k použití jako identifikátor. Ale UID není spolehlivá ochrana.

Pro profil cívky je to normální: pokud je UID znám, vyberte profil. Chyba není kritická, protože uživatel může kontrolovat materiál ručně.

Pro přístup k nebezpečným funkcím, režimům servisu nebo odemknutí topného tělesa je UID sám o sobě slabý. Některé UID lze kopírovat nebo padělat a některé karty mají známá bezpečnostní omezení.

Praktické pravidlo:

- UID je vhodný pro pohodlí a identifikaci spotřebního materiálu;
- UID by neměl být jedinou ochranou pro nebezpečné režimy;
- pro topná tělesa a součásti napájení vždy potřebujete samostatné bezpečnostní kontroly.

## Napájení a logické úrovně

Mnoho modulů RFID/NFC je hodnoceno na `3.3V` logiku. To je obzvláště důležité pro modul ů RC522 a PN532.

Zkontrolujte:

- napájecí napětí modulu;
- logickou úroveň na SPI/I2C/UART;
- zda má deska regulátor;
- zda mají signálové linky sladění úrovně;
- zda jsou potřeba pull-up rezistory I2C;
- zda je potřeba společné uzemnění s regulátorem.

Přítomnost `5V` pinu na desce modulu neznamená vždy, že signálové linky tolerují `5V`. Některé moduly lze napájet z `5V` přes regulátor, ale logika zůstává `3.3V`.

## Rozhraní připojení

Modul RFID/NFC se může připojit přes SPI, I2C nebo UART.

SPI:

- rychlý a běžný;
- vyžaduje `SCK`, `MOSI`, `MISO`, `CS`;
- na RC522 pin `SDA` často ve skutečnosti znamená `CS`;
- důležité není zaměňovat `MOSI` a `MISO`.

I2C:

- používá `SDA` a `SCL`;
- lze sdílet sběrnici s jinými zařízeními;
- potřebuje správné pull-up rezistory;
- důležité je zkontrolovat adresu a vybraný režim modulu.

UART:

- používá `TX` a `RX`;
- `TX` jednoho zařízení jde na `RX` druhého;
- pohodlný pro některé hotové čtečky;
- potřebuje shodující se rychlost a protokol.

Podrobné připojení RC522 SPI je v praktické sekci: [Připojení čtečky RFID](../06-practical-guides/05-connecting-rfid-reader.md).

## Anténa a kryt

RFID/NFC funguje přes anténu. Na malých modulech je obvykle vytištěna přímo na desce.

Čtení je ovlivněno:

- velikostí antény;
- orientací štítku;
- vzdáleností;
- plastem krytu;
- kovem v blízkosti;
- vodiči a vedením elektrické sítě v blízkosti;
- napájením modulu;
- typem štítku;
- kde uživatel přinese kartu.

Kov poblíž antény může výrazně zhoršit čtení. Pokud je čtečka namontována poblíž kovového rámu tiskárny, šroubů, obrazovky, zdroje napájení nebo hliníkového panelu, dosah se může výrazně zhoršit.

Pro kryt je lepší vytvořit jasnou zónu: "přiveďte štítek sem". Neočekávejte, že se štítek na cívce vždy automaticky přečte přes plast, vzduch, hřídel, držák a okolní součásti.

## Logika zařízení

RFID by měl zlepšit pohodlí, ne narušit řízení.

Normální logika pro cívku:

1. Uživatel přinese štítek.
2. Zařízení přečte UID.
3. UID se vyhledá v tabulce profilů.
4. Pokud je UID nalezen, je navržen profil materiálu.
5. Uživatel může potvrdit nebo změnit profil.
6. Pokud UID není nalezen nebo se nepřečetl, je k dispozici ruční výběr.

Špatná logika:

- zařízení se nemůže spustit bez štítku;
- neznámý štítek vybere náhodný profil;
- chyba čtení tiše zachová starý profil;
- profil se mění bez potvrzení uživatelem;
- UID je jedinou ochranou pro režim servisu.

Pro topné těleso je obzvlášť důležité, aby výběr profilu neobešel teplotní limity, senzory a nouzovou ochranu.

## Co zkontrolovat před nákupem

Před nákupem zkontrolujte:

- frekvenci modulu;
- podporované typy štítků;
- rozhraní: SPI, I2C, UART, USB;
- napájecí napětí;
- logické úrovně;
- dostupnost sladění úrovně;
- dostupnost dokumentace a rozložení pinů;
- jak je rozhraní vybráno na desce;
- zda existuje knihovna pro váš řadič;
- velikost antény;
- typ a velikost štítku;
- očekávaný dosah v reálném případě;
- zda je možné ruční výběr zálohy.

Pro první projekt si vyberte modul s dobrou dokumentací a příklady, ne nejlevnější bez schématu.

## Typické chyby

- koupena `125 kHz` karta pro čtečku `13.56 MHz`;
- připojení `3.3V` RC522 k `5V` napájení nebo logice;
- vzal pin `SDA` na RC522 pro I2C `SDA`;
- zaměnění `MOSI` a `MISO`;
- zapomenutí `CS`/`SS` v SPI;
- nastavení jednoho rozhraní na PN532 s jumpers, ale připojení jiného;
- nenení místění pull-up rezistorů I2C, kde byly potřeba;
- umístění antény poblíž kovu;
- testování čtení na pracovní ploše, ale ne v případě;
- RFID jediný způsob, jak vybrat profil;
- použití UID jako spolehlivé ochrany přístupu;
- nezpracování situace "štítek se nepřečetl".

## Hlavní bod

RFID/NFC je užitečný pro identifikaci cívky, výběr profilu materiálu a jednoduchý vstup servisu. Ale to není univerzální čtečka pro jakékoli karty a sám o sobě není spolehlivý bezpečnostní systém.

Nejdříve si vyberte frekvenci a typy štítků, pak modul, rozhraní, napájení a umístění antény. Potom otestujte čtení v reálném případě a určitě ponechte ruční výběr zálohy.

## Reference Materials

- [Adafruit: PN532 RFID/NFC Breakout Wiring](https://learn.adafruit.com/adafruit-pn532-rfid-nfc/breakout-wiring) - PN532 connection, SPI/I2C/UART selection and warning about `3.3V` logic.
- [Adafruit: PN532 RFID/NFC guide, single page](https://learn.adafruit.com/adafruit-pn532-rfid-nfc?view=all) - complete PN532 guide, CircuitPython/Python, interfaces and SEL jumper setup.
- [Adafruit PN532 product page](https://www.adafruit.com/product/364) - description of PN532 module, supported interfaces and NFC/RFID capabilities.
- [NXP: MFRC522 Standard performance MIFARE and NTAG frontend](https://www.nxp.com/products/rfid-nfc/nfc-hf/nfc-readers/standard-performance-mifare-and-ntag-frontend:MFRC52202HN1) - MFRC522/RC522 microchip page and its purpose for `13.56 MHz` MIFARE/NTAG scenarios.
- [DigiKey: MFRC522 Datasheet by NXP](https://www.digikey.com/htmldatasheets/production/993456/0/0/1/mfrc522.html) - technical description of MFRC522: `13.56 MHz` reader/writer, ISO/IEC 14443 A/MIFARE/NTAG support and communication interfaces.
