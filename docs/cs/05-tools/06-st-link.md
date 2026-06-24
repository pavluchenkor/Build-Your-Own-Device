# ST-Link

ST-Link je programátor a debugger pro mikrokontroléry STM32.

V kontextu jednoduchých zařízení se používá pro:

- flashování desky STM32;
- obnovení desky po selhání flashování;
- připojení k čipu přes SWD;
- vymazání paměti;
- ověření, že je mikrokontrolér viditelný;
- někdy ladění programu.

ST-Link není potřeba pro všechny desky. ESP32, RP2040 a Arduino obvykle flashují jiným způsobem.

## Co je SWD

SWD je `Serial Wire Debug`.

Jedná se o rozhraní pro ladění a flashování pro ARM mikrokontroléry, běžně používané s STM32.

Pro základní připojení obvykle potřebujete:

- `SWDIO`;
- `SWCLK`;
- `GND`;
- někdy `NRST`;
- někdy `3.3V` nebo `VTref` jako referenční napětí cíle.

Důležité: `3.3V` na ST-Link neznamenání vždy "napájit desku odtud". Často ST-Link potřebuje vidět napětí cílové desky, aby porozuměl úrovním signálů.

## Minimální připojení

Obvykle připojíte:

```text
ST-Link SWDIO -> deska SWDIO
ST-Link SWCLK -> deska SWCLK
ST-Link GND   -> deska GND
ST-Link NRST  -> deska NRST, pokud je potřeba reset
ST-Link 3.3V/VTref -> 3.3V cíl, pokud vyžaduje konkrétní ST-Link
```

Deska STM32 je často napájena z normálního napájení nebo USB.

Před připojením zkontrolujte dokumentaci pro váš konkrétní ST-Link a desku.

![Nucleo desky pro STM32 s vestavěným ST-Link debuggerem](../../img/02-controllers/04-stm32-nucleo-boards.jpg)

*Zdroj: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:STM32_Nucleo_boards.jpg), Avandalen, CC BY-SA 4.0*

## Napájení desky

Nejčastější zmatek: je deska napájena ST-Linkem nebo odděleně?

Možnosti:

1. Deska je napájena odděleně, ST-Link se pouze připojuje k SWD a GND.
2. ST-Link poskytuje 3,3V malé cílové desce, pokud je to skutečně navrženo.
3. ST-Link pouze čte `VTref`, ale neměl by napájet desku.

Nemůžete slepě připojovat více zdrojů napájení.

Pokud je deska již napájena USB nebo napájecím zdrojem, nepřipojujte napájení z ST-Link, dokud si nejste jistí, že schéma to umožňuje.

## Jak se ST-Link liší od DFU

DFU je flashovací režim přes USB bootloader, pokud je dostupný.

ST-Link funguje přes SWD přímo s mikrokontrolérem.

ST-Link je užitečný, když:

- DFU není dostupný;
- bootloader je poškozený nebo se nepoužívá;
- flashování vypnulo USB;
- deska nebude vstupovat do normálního flashovacího režimu;
- potřebujete vymazat paměť;
- potřebujete obnovit přístup STM32.

Ale pokud se deska normálně flashuje přes USB/DFU nebo SD kartu, ST-Link nemusí být potřeba.

## Připojit pod resetem

Někdy firmware přeruší přístup SWD.

Například:

- SWD piny se používají jako normální GPIO;
- firmware rychle uspatí čip;
- kód se zasekne hned po spuštění;
- režimy hodin/napájení jsou nastaveny nesprávně.

V takových případech pomáhá režim `Connect under reset`.

Myšlenka: ST-Link drží reset a pokusuje se připojit, než se spustí špatný firmware.

To často vyžaduje připojení `NRST`.

## Jak vědět, že ST-Link vidí desku

V STM32CubeProgrammer nebo podobném nástroji obvykle vidíte:

- zda je ST-Link připojen;
- zda je cíl nalezen;
- který čip je zjištěn;
- zda můžete číst paměť;
- zda můžete vymazat flash.

Pokud je ST-Link viditelný jako USB zařízení, ale cíl nebude nalezen, problém je obvykle v připojení desky:

- cílová deska nemá napájení;
- žádný společný `GND`;
- `SWDIO` a `SWCLK` jsou prohozeny;
- `VTref` není připojen, pokud je potřeba;
- frekvence SWD příliš vysoká;
- čip je uzamčen;
- firmware brání připojení;
- potřeba režimu `Connect under reset`.

## Frekvence SWD

Pokud je komunikace nestabilní, zkuste snížit frekvenci SWD.

Na dlouhých vodičích, špatných propojovacích vodičích Dupont nebo nestabilních deskách může vysoká frekvence narušit připojení.

Pro zotavení desky je pomalé a spolehlivé lepší než rychlé.

## Běžné chyby

- zapomenut `GND`;
- prohozeny `SWDIO` a `SWCLK`;
- připojeno napájení z ST-Link a USB zároveň bez pochopení schématu;
- cílová deska nebyla napájena;
- `NRST` nebyl připojen, když je potřeba `Connect under reset`;
- frekvence SWD nastavena příliš vysoká;
- pokus flashovat ESP32 nebo RP2040 pomocí ST-Link;
- pokus připojit k uzamčenému čipu bez pochopení ochrany čtení;
- použití dlouhých drátů s nízkou kvalitou;
- neaktualizoval ST-Link firmware nebo nenainstaloval ovladač.

## Co nemůžete dělat

Nemůžete:

- přiložit 5V na desku STM32 3,3V bez kontroly;
- připojit více zdrojů napájení slepě;
- připojit ST-Link k desce pod napětím sítě bez bezpečné izolace a krytu;
- měnit vodiče SWD se zapnutým napájením, pokud je riziko zkratu;
- předpokládat, že klon ST-Link má stejné rozpojení jako originál.

Rozpojení klonů ST-Link se mohou lišit. Vždy zkontrolujte značení na svém konkrétním adaptéru.

## Podstatné

- ST-Link je potřeba pro STM32 přes SWD.
- Minimum: `SWDIO`, `SWCLK`, `GND`, někdy `NRST` a `VTref`.
- Deska by měla být napájena správně, ale ne nutně z ST-Link.
- DFU a ST-Link jsou různé metody flashování.
- `Connect under reset` pomáhá obnovit přístup po špatném firmware.
- Pokud cíl není nalezen, nejdříve zkontrolujte napájení, `GND`, `SWDIO/SWCLK`, `NRST` a frekvenci SWD.

## Referenční materiály

- [STMicroelectronics: UM1075 ST-LINK/V2 User Manual](https://www.st.com/resource/en/user_manual/dm00026748-st-link-v2-in-circuit-debugger-programmer-for-stm8-and-stm32-stmicroelectronics.pdf) - oficiální příručka ST-LINK/V2, piny SWD/JTAG, cílové VCC a GND.
- [STMicroelectronics: UM2237 STM32CubeProgrammer User Manual](https://www.st.com/resource/en/user_manual/um2237-stm32cubeprogrammer-software-description-stmicroelectronics.pdf) - režimy připojení ST-LINK, včetně Normal, Connect under reset a Hot plug.
- [ST Wiki: ST-LINK](https://wiki.st.com/stm32mpu/wiki/ST-LINK) - přehled ST-LINK jako hardwarové sondy pro STM32/STM8 a podporované protokoly.
- [Klipper: Installation](https://www.klipper3d.org/Installation.html) - obecný proces přípravy MCU pro Klipper.
- [STMicroelectronics: STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) - oficiální nástroj ST pro flashování STM32 přes ST-LINK/SWD, UART, USB DFU, SPI, I2C a CAN bootloadery.
