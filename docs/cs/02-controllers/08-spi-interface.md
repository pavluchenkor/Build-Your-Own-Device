# Rozhraní SPI

SPI je rychlé sériové komunikační rozhraní mezi kontrolérem a periferiálními zařízeními. Rozšíření: `Serial Peripheral Interface`.

SPI se často používá tam, kde je potřeba rychlejší přenos dat než I2C, nebo když je zařízení navrženo pro SPI: displej, SD karta, RFID modul, senzor, driver či čip paměti.

## Kde se SPI používá

V 3D tiskárnách a zařízeních podobných iDryer se SPI může vyskytovat v:

- RFID/NFC modulech jako RC522;
- OLED/TFT displeji;
- SD kartách;
- akcelerometrech pro input shaper;
- stepper driverech, například TMC2130/TMC5160;
- čipech paměti;
- ADC/DAC a expanzních deskách;
- některých senzorech a specializovaných modulech.

SPI je obvykle rychlejší než I2C, ale vyžaduje více vodičů a pečlivější výběr pinů.

## Základní linky

Typický SPI používá:

- `SCK` nebo `CLK` - hodinový signál;
- `MOSI` - data od kontroléru k zařízení;
- `MISO` - data od zařízení k kontroléru;
- `CS`, `SS` nebo `NSS` - výběr konkrétního zařízení;
- `GND` - společná zem;
- napájení modulu.

Diagram se dvěma zařízeními:

![SPI: základní výměna operace mezi master a slave zařízením](../../img/02-controllers/08-spi-basic-operation.png)

*Zdroj: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:SPI_basic_operation,_single_Main_%26_Sub.svg), Em3rgent0rdr, CC0 Public Domain*

`SCK`, `MOSI` a `MISO` mohou být sdíleny více zařízeními. Ale každé zařízení obvykle potřebuje vlastní `CS`.

## CS místo adres

V I2C se zařízení rozlišují podle adres. V SPI obvykle nejsou adresy. Kontrolér si vybere zařízení oddělou `CS` linkou.

Příklad:

```text
SCK  -> běžné všem SPI zařízením
MOSI -> běžné
MISO -> běžné
CS1  -> RFID modul
CS2  -> displej
CS3  -> SD karta
```

Když chce kontrolér mluvit s RFID modulem, aktivuje `CS1`. Když chce mluvit s displejem, aktivuje `CS2`.

Nejčastěji je `CS` aktivní nízko: v klidu je linka `HIGH`, na výběr zařízení je `LOW`. Ale to musí být ověřeno v technickém datalisty.

## MOSI/MISO a nová jména

Ve starých a velmi běžných schématech jsou jména:

- `MOSI` - Master Out Slave In;
- `MISO` - Master In Slave Out;
- `SS` - Slave Select.

V novější dokumentaci můžete vidět neutrální jména:

- `PICO` - Peripheral In Controller Out, ekvivalent MOSI;
- `POCI` - Peripheral Out Controller In, ekvivalent MISO;
- `CS` - Chip Select.

V elektronice 3D tiskáren jsou `MOSI`, `MISO`, `SCK`, `CS` stále velmi běžné. Hlavní věc je pochopit směr signálu a zkontrolovat rozložení pinů konkrétního modulu.

## MISO nemusí být potřeba

Ne každé SPI zařízení skutečně posílá data zpět.

Například jednoduchý displej může jen přijímat příkazy a pixely. Pak linka `MISO` může chybět nebo se nepoužívá.

Ale na zařízení, která čtou data, je `MISO` potřeba:

- RFID modul;
- SD karta;
- senzor;
- driver s diagnostikou;
- čip paměti.

Pokud má modul reagovat a `MISO` není připojena či je prohozena, inicializace může selhat.

## Rychlost SPI a režim

SPI má rychlost. Může být mnohem vyšší než I2C, ale to neznamená, že musíte nastavit maximum hned.

Práce je ovlivňena:

- délkou vodiče;
- kvalitou zem;
- modulem a jeho datalistem;
- úrovní šumu;
- frekvencí kontroléru;
- zvoleným SPI režimem.

SPI režim je nastaven parametry polarity a fáze hodinky: `CPOL` a `CPHA`. Režim 0 se často používá, ale ne vždy. Pokud je režim špatný, zařízení nemusí reagovat či vrátit špatná data.

Ve větši hotových knihoven je režim už nastaven. Ale pokud připojujete neobvyklý modul či píšete nízkoúrovňovou konfiguraci, musíte zkontrolovat datalist.

## 3.3V a 5V

Stejně jako ostatní rozhraní SPI nezaručuje bezpečné napěťové úrovně.

ESP32, RP2040, STM32 a mnoho moderních modulů pracují s logikou `3.3V`. Arduino Uno/Nano často používá `5V`.

Před připojením ověřte:

- napájení modulu;
- logickou úroveň `SCK`, `MOSI`, `MISO`, `CS`;
- zda je sladění úrovní;
- zda modul toleruje `5V` na vstupech signálů;
- zda vstup kontroléru toleruje `5V`.

Například RC522 typicky vyžaduje napájení a logiku `3.3V`. Připojení na Arduino `5V` bez sladění úrovní je špatný nápad.

## SPI v Klipperu

V Klipperu se SPI používá na různá zařízení: TMC drivery, akcelerometry, některé displeje a sensory.

Konfigurace může obsahovat:

- `cs_pin` - pin výběru zařízení;
- `spi_bus` - hardwarová SPI sběrnice;
- `spi_speed` - rychlost v Hz;
- `spi_software_sclk_pin`;
- `spi_software_mosi_pin`;
- `spi_software_miso_pin`.

Pokud je zařízení připojeno na dodatečný MCU, piny by měly patřit tomu MCU. Stejně jako u ostatních sekcí Klipperu je konkrétní rozložení pinů desky důležitější než odhady.

Hrubá představa:

```ini
[some_spi_device]
cs_pin: chamber:gpio9
spi_software_sclk_pin: chamber:gpio10
spi_software_mosi_pin: chamber:gpio11
spi_software_miso_pin: chamber:gpio12
```

To není hotová konfigurace konkrétního zařízení, ale ilustrace: všechny SPI piny musí být na MCU, ke kterému je modul skutečně připojen.

## Délka vodiče a interference

SPI může fungovat rychle, ale nemá rád dlouhé, chaotické zapojení.

Praktická pravidla:

- udržujte `SCK`, `MOSI`, `MISO`, `CS` krátké;
- vedete blízko `GND`;
- nevedete paralelně s vodiči topidla a motoru;
- snižte `spi_speed`, pokud jsou chyby;
- používejte správné konektory;
- nevedete SPI přes celou tiskárnu bez důvodu;
- pro vzdálené uzly si spíše vyberte CAN, UART/RS-485 nebo oddělený MCU blízko modulu.

Linka `SCK` je obzvláště citlivá: je to hodinový signál. Pokud je špinavá, všechna komunikace může být nestabilní.

## SPI a RC522

RC522 je dobrý příklad SPI modulu s matením v pojmenování.

Na mnohých deskách RC522 je pin `SDA` skutečně používán jako `SS`/`CS` pro SPI. To není I2C `SDA`.

Na RC522 typicky potřebujete:

- `3.3V`;
- `GND`;
- `SCK`;
- `MOSI`;
- `MISO`;
- `SDA`/`SS`/`CS`;
- `RST`;
- někdy `IRQ`, ale v jednoduchých projektech se často nepoužívá.

Podrobný diagram je v praktickém článku: [Připojení RFID čtečky](../06-practical-guides/05-connecting-rfid-reader.md).

## Co zkontrolovat před připojením

Před připojením SPI modulu ověřte:

- napájení modulu;
- logickou úroveň;
- rozložení pinů konkrétní desky;
- kde jsou `SCK`, `MOSI`, `MISO`, `CS`;
- zda se potřebují `RST`, `DC`, `IRQ` či jiné piny;
- který `CS` je přiřazen zařízení;
- zda se `CS` nekonfliktu s jiným modulem;
- zda je potřeba hardwarový nebo softwarový SPI;
- jakou rychlost dokumentace doporučuje;
- zda firmware toto zařízení podporuje.

## Typické chyby

- prohození `MOSI` a `MISO`;
- zapomenutí `CS`;
- připojení dvou zařízení na jeden `CS`;
- nepřipojení společné `GND`;
- aplikace `5V` na modul SPI `3.3V`;
- plení si `SDA` na RC522 s I2C `SDA`;
- výběr příliš vysoké rychlosti;
- příliš dlouhé vodiče;
- připojení modulu na jeden MCU, ale zadání pinů z druhého;
- myšlenka, že SPI je silové rozhraní na řízení zátěže.

## Klíčové pozorování

SPI je rychlé rozhraní na moduly blízko kontroléru. Obvykle potřebujete `SCK`, `MOSI`, `MISO`, `CS`, napájení a `GND`.

Hlavní rozdíl od I2C: SPI obvykle nemá adresy a každé zařízení se vybírá oddělou `CS`. Před připojením ověřte rozložení pinů, logickou úroveň, rychlost, délku vodiče a podporu firmwaru.

## související materiály

- [SparkFun: Serial Peripheral Interface](https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi) - praktický výklad SPI, datových linek, nových jmen PICO/POCI a logiky základní výměny.
- [SparkFun: SPI Chip Select](https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi/chip-select-cs) - proč je `CS` potřeba a jak připojit více SPI zařízení.
- [Adafruit: SPI Devices](https://learn.adafruit.com/circuitpython-basics-i2c-and-spi/spi-devices) - srovnání SPI vs I2C, oddělená `CS`, rychlost, polarita/fáze a omezení.
- [DigiKey: SPI Simplifies Device Communication](https://www.digikey.com/en/articles/why-how-to-use-serial-peripheral-interface-simplify-connections-between-multiple-devices) - možnosti připojení více SPI zařízení a role `CS`.
- [Klipper Configuration Reference: Common SPI settings](https://www.klipper3d.org/Config_Reference.html) - `spi_speed`, `spi_bus`, softwarový SPI a parametry `cs_pin` v Klipperu.
