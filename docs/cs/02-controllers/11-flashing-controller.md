# Nahrání firmwaru kontroléru

Firmware je program zapsaný do flash paměti mikrokontroléru. Bez firmwaru deska neví, co má dělat s piny, sensory, ventilátory a rozhraními.

Důležité: neplešte si firmware a konfiguraci. Firmware se zapisuje do kontroléru. Konfigurace Klipperu obvykle žije na hostiteli v `printer.cfg` a říká již nahranému MCU, které piny a parametry použít.

## Firmware, bootloader, konfigurace

Tři různé koncepty:

- **firmware** - hlavní program mikrokontroléru;
- **bootloader** - malý program, který pomáhá napsat hlavní firmware;
- **konfigurace** - nastavení zařízení, například `printer.cfg` v Klipperu.

Bootloader se spustí první a může přijmout nový firmware přes USB, UART, DFU, SD kartu, CAN či jiný mechanismus. Pokud se bootloader náhodou vymaže, nahrání desky se může stát obtížným: někdy je potřeba ST-LINK/SWD, USB-UART či jiný programátor.

## Obecná cesta

Před nahráním je normální postup:

1. Zjistit přesný model desky.
2. Zjistit přesný mikrokontroleér.
3. Najít rozložení pinů, schéma a pokyny výrobce.
4. Pochopit, zda je potřeba samostatný firmware či firmware Klipperu MCU.
5. Najít hotovou konfiguraci nebo příklad pro tuto desku.
6. Vybrat správný způsob nahrání.
7. Vytvořit nebo stáhnout správný soubor.
8. Dát desku do režimu nahrávání.
9. Nahrajte firmware.
10. Ověřit, že se deska objeví v systému.
11. Ověřit komunikaci s hostem a základní piny bez zátěže.

Nemůžete hádat nastavení firmware. Pro Klipper jsou zvláště důležité typ mikrokontroléru, offset bootloaderu, hodinová reference a komunikační rozhraní.

## Typické metody nahrávání

Různé desky se nahrávají různě:

![Hlavní cesty na nahrání kontroléru](../../img/02-controllers/11-controller-flashing-paths.svg)

Běžné varianty:

- **USB paměťové zařízení / UF2** - deska se objeví jako disk, `.uf2` se zkopíruje;
- **USB DFU** - deska vejde do režimu DFU, firmware se napíše přes USB;
- **USB sériový / UART bootloader** - firmware přes sériový port;
- **ST-LINK / SWD** - programátor se spojí na SWD piny;
- **SD karta** - některé desky 3D tiskáren se nahrávají se souborem na kartě;
- **CAN/Katapult/CanBoot** - firmware přes CAN bootloader;
- **Arduino bootloader** - nahrání skicet přes Arduino IDE či avrdude.

Neexistuje jedna univerzální metoda pro všechny desky. Metoda je určena konkrétní deskou, bootloaderem a firmwarem.

## RP2040 a UF2

Na Raspberry Pi Pico a mnoho desek RP2040 je nejjednoduší cesta `BOOTSEL` a UF2.

Obvykle:

1. Podržte `BOOTSEL`.
2. Připojte USB.
3. Deska se objeví jako disk `RPI-RP2`.
4. Zkopírujte soubor `.uf2`.
5. Disk zmizí, deska se restartuje.

BOOTSEL Pica je v ROM mikrokontroléru, takže jej nemůžete náhodou smazat normálním nahráním. To činí RP2040 vhodný pro začátečníky.

## STM32: DFU, ST-LINK, SD karta

Desky STM32 se nahrávají různě.

Možné varianty:

- vestavěný USB DFU bootloader;
- UART bootloader;
- ST-LINK/SWD;
- SD karta na desce tiskárny;
- bootloader výrobce desky;
- CAN bootloader.

Na STM32 je offset bootloaderu často důležitý. Například pokud bootloader zabere prvních `8 KiB`, Klipper musí být sestaven se správným offsetem. Pokud je vybrán špatně, deska se po nahrání nemusí spustit.

ST-LINK/SWD je užitečný jako nízkoúrovňová volba: často může obnovit desku, pokud normální bootloader nefunguje. Ale to vyžaduje SWD piny, programátor a pochopení spojení.

## Klipper: make menuconfig

Na firmware Klipperu obvykle děláte:

```bash
cd ~/klipper
make menuconfig
make
```

V `make menuconfig` vyberete:

- architekturu mikrokontroléru;
- model procesoru;
- offset bootloaderu;
- hodinovou referenci;
- komunikační rozhraní: USB, sériový, CAN atd.;
- někdy dodatečné parametry pro konkrétní desku.

Správné hodnoty jsou často psány v komentářích na začátku hotového konfiguračního souboru pro desku. Pokud takový config existuje, nejprve si přečtěte komentáře na začátku.

Po sestavě se soubor firmware obvykle objeví v `~/klipper/out/`. Dále se napíše metodou vhodnou pro konkrétní desku.

## Ověření po nahrání

Po nahrání musíte ověřit více než jen "nahrávač napsal úspěch".

Zkontrolujte:

- zda se zařízení objeví v systému;
- zda je přítomné `/dev/serial/by-id/...`, pokud používáte USB/sériový;
- zda je viditelné `canbus_uuid`, pokud používáte CAN;
- zda cesta odpovídá `printer.cfg`;
- zda nejsou v Klipperu chyby komunikace;
- zda piny odpovídají rozložení pinů konkrétní desky;
- zda základní vstupy/výstupy fungují bez zatížení;
- zda jsou ventilátor/MOSFET/SSR v bezpečném stavu vypnuty.

Na první kontrolu nepřipojujte topidlo jako finální zatížení. Nejprve ověřte komunikaci, sensory a logiku za bezpečných podmínek.

## Co uložit před nahráním

Před změnou firmware je užitečné uložit:

- aktuální `printer.cfg`;
- starou verzi firmware, pokud je dostupná;
- model desky a mikrokontroleér;
- nalezené sériové cesty či CAN UUID;
- foto spojení;
- rozložení pinů;
- nastavení `make menuconfig`;
- odkaz na pokyny výrobce.

Pokud se něco pokazí, tato data pomohou rychle obnovit.

## Co se může pokazit

Běžné problémy:

- USB kabel je jen nabíjecí;
- deska nepřešla do bootloaderu;
- vybrán špatný mikrokontroleér;
- vybrán špatný offset bootloaderu;
- vybráno špatné komunikační rozhraní;
- firmware zapsaný, ale deska je hledána na špatném místě;
- sériová cesta se změnila po opětovném připojení;
- SD karta není přečtena deskou;
- soubor firmware pojmenován špatně pro bootloader desky;
- ovladač DFU/USB-UART není nainstalován;
- deska napájena ze dvou stran;
- po nahrání konfigurace odkazuje na staré piny.

Neměňte vše v odpovědi na první chybu. Lépe jít krok za krokem: kabel, režim bootloaderu, model MCU, nastavení sestav, metoda zápisu, vzhled systémového zařízení, konfigurace.

## Nahrání a bezpečnost

Firmware může zapínat a vypínat výstupy, ale nenahrazuje bezpečnost hardwaru.

Na topidla potřebujete:

- správný spínač napájení;
- pojistku;
- nezávislou tepelnou ochranu;
- správný teplotní senzor;
- bezpečné pouzdro;
- kontrola chování při chybě firmware, zablokování MCU či ztráta komunikace.

Po nahrání kontroléru nepřipojujte topidlo bez ověření, že je pin vybrán správně, logika zapnutí není invertována a bezpečnostní limity fungují.

## Typické chyby

- plení si firmware a `printer.cfg`;
- nahrání souboru z podobné, ale jiné desky;
- nečtení komentářů na začátku hotového Klipperu config;
- výběr špatného offsetu bootloaderu;
- smazání bootloaderu bez pochopení důsledků;
- používání nabíjecího USB kabelu;
- nedání desky do režimu nahrávání;
- hledání CAN desky v `/dev/serial/by-id`;
- hledání USB-sériové desky přes `canbus_uuid`;
- připojení zátěže výkonu před ověřením pinů;
- neuložení staré konfigurace.

## Klíčový závěr

Firmware je program uvnitř kontroléru, konfigurace je jeho operační nastavení. Pro každou desku musíte znát přesný model, mikrokontroleér, bootloader, metodu nahrání a parametry sestav.

Na RP2040 je UF2/BOOTSEL obvykle nejjednoduší. Na STM32 zkontrolujte konkrétní desku: DFU, ST-LINK, SD karta, UART či CAN bootloader. Pro Klipper nejprve najděte hotový config a komentáře pro `make menuconfig`.

## Related materials

- [Klipper: Installation - Building and flashing the micro-controller](https://www.klipper3d.org/Installation.html#building-and-flashing-the-micro-controller) - oficiální postup pro `make menuconfig`, `make` a ověření sériové cesty.
- [Klipper: Bootloaders](https://www.klipper3d.org/Bootloaders.html) - proč se bootloadery liší mezi deskami, proč offset bootloaderu záleží a jak se různé MCU nahrávají.
- [Raspberry Pi Documentation: Pico-series microcontrollers](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html) - BOOTSEL, UF2 a specifikace Pico/RP2040/RP2350.
- [Raspberry Pi Documentation: C/C++ SDK - Your First Binaries](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html#your-first-binaries) - oficiální příklad BOOTSEL, USB paměťového zařízení `RPI-RP2` a nahrávání Pica přes UF2.
- [STMicroelectronics: STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) - oficiální nástroj STM32 na nahrávání přes ST-LINK/SWD, UART, USB DFU, SPI, I2C a CAN bootloader.
