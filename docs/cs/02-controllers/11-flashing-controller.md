# Nahrání firmwaru kontroléru

Firmware (`firmware`) je program zapsaný do flash paměti mikrokontroléru. Bez firmwaru deska neví, co má dělat s piny, sensory, ventilátory a rozhraními.

Důležité: neplést si firmware a konfiguraci. Firmware se zapisuje do kontroléru. Konfigurace Klipperu obvykle žije na hostiteli v `printer.cfg` a říká již nahrané MCU, které piny a parametry použít.

## Firmware, bootloader, konfigurace

Tři různé koncepty:

- **firmware** - hlavní program mikrokontroléru;
- **bootloader** - malý program, který pomáhá napsat hlavní firmware;
- **konfigurace** - nastavení zařízení, např. `printer.cfg` v Klipperu.

Bootloader se spustí první a může přijmout nový firmware přes USB, UART, DFU, SD kartu, CAN nebo jiný mechanismus. Pokud je bootloader náhodou vymazán, nahrání desky se může stát obtížným: někdy je potřeba ST-LINK/SWD, USB-UART nebo jiný programátor.

## Obecný postup

Před nahráním je normální postup:

1. Zjistit přesný model desky.
2. Zjistit přesný mikrokontrolér.
3. Najít rozložení pinů, schéma a pokyny výrobce.
4. Pochopit, zda je potřeba samostatný firmware nebo Klipper MCU firmware.
5. Najít připravenou konfiguraci nebo příklad pro tuto desku.
6. Vybrat správný způsob nahrání.
7. Vytvořit nebo stáhnout správný soubor.
8. Dát desku do režimu nahrávání.
9. Napsat firmware.
10. Ověřit, že se deska objeví v systému.
11. Ověřit komunikaci s hostitelem a základní piny bez zatížení.

Nemůžete uhodnout nastavení firmwaru. Pro Klipper jsou zvláště důležité typ mikrokontroléru, posun bootloaderu, hodinová reference a komunikační rozhraní.

## Typické metody nahrávání

Různé desky se nahrávají jinak:

![Hlavní cesty pro nahrání kontroléru](../../img/02-controllers/11-controller-flashing-paths.svg)

Běžné varianty:

- **USB paměťové zařízení / UF2** - deska se objeví jako disk, `.uf2` je na něj zkopírován;
- **USB DFU** - deska přejde do DFU režimu, firmware se napíše přes USB;
- **USB sériový / UART bootloader** - firmware přes sériový port;
- **ST-LINK / SWD** - programátor se připojí k SWD pinům;
- **SD karta** - některé desky 3D tiskárny se nahrávají se souborem na kartě;
- **CAN/Katapult/CanBoot** - firmware přes CAN bootloader;
- **Arduino bootloader** - nahrání skicet přes Arduino IDE nebo avrdude.

Neexistuje jedna univerzální metoda pro všechny desky. Metoda je určena konkrétní deskou, bootloaderem a firmwarem.

## RP2040 a UF2

Pro Raspberry Pi Pico a mnoho desek RP2040 je nejjednodušší způsob `BOOTSEL` a UF2.

Obvykle:

1. Podržte `BOOTSEL`.
2. Připojte USB.
3. Deska se objeví jako disk `RPI-RP2`.
4. Zkopírujte soubor `.uf2`.
5. Disk zmizí, deska se restartuje.

BOOTSEL Pica je v ROM mikrokontroléru, takže jej nelze náhodou smazat normálním nahráním. To činí RP2040 pro začátečníky vhodným.

## STM32: DFU, ST-LINK, SD karta

Desky STM32 se nahrávají různým způsobem.

Možné možnosti:

- vestavěný USB DFU bootloader;
- UART bootloader;
- ST-LINK/SWD;
- SD karta na desce tiskárny;
- bootloader výrobce desky;
- CAN bootloader.

Pro STM32 je posun bootloaderu často důležitý. Například pokud bootloader zabere první `8 KiB`, Klipper musí být sestaven se správným posunem. Pokud je vybrán špatně, deska se po nahrání nemusí spustit.

ST-LINK/SWD je užitečný jako nízkoúrovňová volba: často může obnovit desku, pokud normální bootloader nefunguje. Ale to vyžaduje SWD piny, programátor a pochopení připojení.

## Klipper: make menuconfig

Pro firmware Klipperu obvykle děláte:

```bash
cd ~/klipper
make menuconfig
make
```

V `make menuconfig` vyberete:

- architekturu mikrokontroléru;
- model procesoru;
- posun bootloaderu;
- hodinovou referenci;
- komunikační rozhraní: USB, sériový, CAN atd.;
- někdy další parametry pro konkrétní desku.

Správné hodnoty jsou často napsány v komentářích na začátku připraveného konfiguračního souboru pro desku. Pokud takový konfigurační soubor existuje, přečtěte si nejprve jeho horní komentáře.

Po sestavení se soubor firmwaru obvykle objeví v `~/klipper/out/`. Dále se napíše pomocí metody vhodné pro konkrétní desku.

## Ověření po nahrání

Po nahrání musíte ověřit více než jen "nahrávač napsal úspěch".

Zkontrolujte:

- zda se zařízení objeví v systému;
- zda je přítomné `/dev/serial/by-id/...`, pokud používáte USB/sériový;
- zda je viditelný `canbus_uuid`, pokud používáte CAN;
- zda cesta odpovídá `printer.cfg`;
- zda nejsou v Klipperu chyby komunikace;
- zda piny odpovídají rozložení pinů konkrétní desky;
- zda základní vstupy/výstupy fungují bez zatížení;
- zda je ventilátor/MOSFET/SSR v bezpečném stavu vypnutý.

Pro první kontrolu nepřipojujte topidlo jako finální zatížení. Nejprve ověřte komunikaci, sensory a logiku za bezpečných podmínek.

## Co uložit před nahráním

Před změnou firmwaru je užitečné uložit:

- aktuální `printer.cfg`;
- starou verzi firmwaru, pokud je k dispozici;
- model desky a mikrokontrolér;
- nalezená sériová cesta nebo CAN UUID;
- foto připojení;
- rozložení pinů;
- nastavení `make menuconfig`;
- odkaz na pokyny výrobce.

Pokud se něco pokazí, tato data pomohou rychle obnovit.

## Co se může pokazit

Běžné problémy:

- USB kabel je pouze nabíjecí;
- deska nepřešla do bootloaderu;
- vybrán špatný mikrokontrolér;
- vybrán špatný posun bootloaderu;
- vybráno špatné komunikační rozhraní;
- firmware zapsaný, ale deska je hledán na špatném místě;
- sériová cesta se změnila po opětovném připojení;
- SD karta není přečtena deskou;
- soubor firmwaru pojmenován nesprávně pro bootloader desky;
- DFU/USB-UART ovladač není nainstalován;
- deska napájena ze dvou stran;
- po nahrání konfigurace odkazuje na staré piny.

Neměňte vše v odpovědi na první chybu. Lépe jít krok za krokem: kabel, režim bootloaderu, model MCU, nastavení sestav, metoda zápisu, vzhled systémového zařízení, konfigurace.

## Nahrání a bezpečnost

Firmware může zapínat a vypínat výstupy, ale nenahrazuje bezpečnost hardwaru.

Pro topidla potřebujete:

- správný spínač napájení;
- pojistku;
- nezávislou tepelnou ochranu;
- správný teplotní senzor;
- bezpečný kryt;
- kontrola chování při chybě firmwaru, zablokování MCU nebo ztrátě komunikace.

Po nahrání kontroléru nepřipojujte topidlo bez ověření, že je pin vybrán správně, logika zapnutí není invertována a funkčnost bezpečnostních limitů.

## Typické chyby

- plést si firmware a `printer.cfg`;
- nahrát soubor ze podobné, ale jiné desky;
- nepřečíst komentáře na začátku připraveného Klipperu konfig;
- vybrat špatný posun bootloaderu;
- smazat bootloader bez pochopení důsledků;
- použít nabíjecí USB kabel;
- nedát desku do režimu nahrávání;
- hledat CAN desku v `/dev/serial/by-id`;
- hledat USB-sériovou desku přes `canbus_uuid`;
- připojit zatížení výkonu před ověřením pinů;
- neuložit starou konfiguraci.

## Klíčový závěr

Firmware je program uvnitř kontroléru, konfigurace je jeho operační nastavení. Pro každou desku musíte znát přesný model, mikrokontrolér, bootloader, metodu nahrání a parametry sestav.

Pro RP2040 je UF2/BOOTSEL obvykle nejjednodušší. Pro STM32 zkontrolujte konkrétní desku: DFU, ST-LINK, SD karta, UART nebo CAN bootloader. Pro Klipper nejprve najděte připravený config a komentáře pro `make menuconfig`.

## související materiály

- [Klipper: Installation - Building and flashing the micro-controller](https://www.klipper3d.org/Installation.html#building-and-flashing-the-micro-controller) - oficiální postup pro `make menuconfig`, `make` a ověření sériové cesty.
- [Klipper: Bootloaders](https://www.klipper3d.org/Bootloaders.html) - proč se bootloadery liší mezi deskami, proč je potřeba posun bootloaderu a jak se různé MCU nahrávají.
- [Raspberry Pi Documentation: Pico-series microcontrollers](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html) - BOOTSEL, UF2 a Pico/RP2040/RP2350 specifika.
- [Raspberry Pi Documentation: C/C++ SDK - Your First Binaries](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html#your-first-binaries) - oficiální příklad BOOTSEL, USB paměťového zařízení `RPI-RP2` a nahrávání Pica přes UF2.
- [STMicroelectronics: STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) - oficiální STM32 nástroj pro nahrávání přes ST-LINK/SWD, UART, USB DFU, SPI, I2C a CAN bootloader.
