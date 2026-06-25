# Adaptéry USB-UART

USB-UART adaptér je potřebný, aby se počítač či Linux host mohl komunikovat se zařízeními UART přes USB. Převádí USB na běžné sériové linky `TX`, `RX` a `GND`.

Takový adaptér je často potřebný na nahrávání, logy, diagnostiku a obnovu desek bez správného USB konektoru.

## Kde se to potřebuje

USB-UART adaptér je užitečný na:

- nahrávání některých desek mikrokontroléru;
- čtení sériových logů;
- přístup na konzolu zařízení;
- diagnostiku režimu bootloaderu;
- připojení Arduino Pro Mini a některých klonů Nano;
- práci s deskami bez vestavěného USB;
- obnovu po selhání nahrávání;
- dočasné spojení MCU k hostu přes sériový.

Pokud deska již má správný USB a objeví se jako sériové zařízení, oddělený USB-UART adaptér nemusí být potřebný.

## Co to má

Typické kontakty:

- `TX` nebo `TXO` - vysílání z adaptéru do zařízení;
- `RX` nebo `RXI` - přijímání ze zařízení;
- `GND` - společná zem;
- `VCC`, `3V3` nebo `5V` - napájení, pokud je potřebné;
- `DTR` - často používané na auto-reset/nahrávání;
- `RTS`, `CTS` - linky řízení toku či boot/reset scénáře.

Schéma zapojení:

![USB-UART adaptér na čipu CH340T](../../img/02-controllers/10-usb-uart-ch340-adapter.jpg)

*Zdroj: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:15938_-_USBtoSerial_1.jpg), SparkFun Electronics, CC BY 2.0*

Na jednoduché čtení logů stačí často jen `TX`, `RX` a `GND`. Napájení se přiojuje jen, pokud je jasné, že by měla být deska napájena z adaptéru.

## Jak připojit TX a RX

Spojení je křížem:

```text
TX adaptéru -> RX zařízení
RX adaptéru <- TX zařízení
GND adaptéru -> GND zařízení
```

Pokud není spojení, první kontrola je: nejsou `TX` a `RX` prohozeni, je tam společná `GND`, shoduje se rychlost a je vybraný správný COM/tty port.

## 3.3V a 5V

USB-UART adaptéry přicházejí v:

- `3.3V` jen;
- `5V` jen;
- s přepínačem `3.3V/5V`;
- s jumperem či mostem;
- s `VCC` jednoho napětí, ale signály jiné úrovně.

To záleží: napětí `VCC` a úroveň `TX/RX` nejsou vždy zřejmé z nálepek.

ESP32, RP2040 a STM32 typicky používají logiku `3.3V`. Arduino Uno/Nano často používá `5V`. Pokud aplikujete signál `5V` na vstup `3.3V`, můžete desku poškodit.

Před připojením zkontrolujte dokumentaci adaptéru a desky. Nespoléhejte se jen na barvu jumpeřu či nálepku na pouzdru.

## TTL UART a RS-232

USB-UART adaptér na mikrokontroleéry obvykle vydává TTL/CMOS UART: `3.3V` nebo `5V`.

To není totéž jako skutečný RS-232.

RS-232 má různé napěťové úrovně a nemůže se připojit přímo na GPIO mikrokontroléru. Pokud potřebujete pracovat se skutečným portem RS-232, potřebujete USB-RS232 adaptér či měnič úrovně, ne obyčejný USB-UART TTL.

## Napájení z adaptéru

Pin `VCC` na adaptéru může být užitečný, ale často se zneužívá.

Bezpečný přístup:

- na logy a diagnostiku napřed spojte jen `TX`, `RX`, `GND`;
- nepřipojujte `VCC`, pokud je deska již napájena z USB, napájecího zdroje či jiného obvodu;
- nenapájejte motory, servomotory, relé, topidla a LED pásky přes USB-UART;
- ověřte, kolik proudu adaptér skutečně může poskytnout;
- chápu, že `VCC` může být `3.3V` nebo `5V`.

Pokud spojíte dva napájecí zdroje bez pochopení obvodu, můžete dostat zpětné napájení, nestabilitu či poškození desky.

## DTR a RTS

Některé desky používají `DTR` a `RTS` na auto-reset či vstup bootloaderu.

Příklady:

- Arduino Pro Mini často používá `DTR` přes kondenzátor na reset během nahrávání;
- desky ESP32 mohou používat `DTR`/`RTS` na auto-ovládání `EN` a `BOOT`;
- některé bootloader scénáře vyžadují ruční stisknutí tlačítka, pokud tyto linky nejsou spojeny.

Pokud nahrávání nezačíná automaticky, nemusi to být problem `TX/RX`. Může být, že `DTR`/`RTS` nejsou spojeny, je vybrán špatný bootloader, nebo musíte `BOOT`/`RESET` ručně stisknout.

## CH340, CP2102, FTDI

Populární USB-UART čipy:

- **CH340/CH341** - levné a rozšířené adaptéry;
- **CP2102/CP210x** - běžný USB-UART od Silicon Labs;
- **FT232/FTDI** - klasická volba, často dražší;
- **PL2303** - nalézá se ve starých adaptérech a kabelech.

Na moderních systémech se ovladač často instaluje automaticky, ale ne vždy. Pokud port se neobjevuje, zkontrolujte:

- USB kabel není jen nabíjecí;
- zařízení je detekováno systémem;
- zda je potřeba ovladač;
- zda starý ovladač není v konfliktu;
- zda port není obsazen jinou aplikací.

## Jak testovat adaptér

Jednoduchý loopback test:

1. Připojte adaptér k počítači.
2. Spojte `TX` adaptéru s `RX` adaptéru.
3. Otevřete sériový terminál.
4. Vyberte port a rychlost, například `115200`.
5. Napište znaky.
6. Pokud funguje, znaky se vrátí zpět.

To testuje sám adaptér, ovladač, kabel a terminální aplikaci bez externí desky.

## Co zkontrolovat před nákupem

Před nákupem USB-UART adaptéru ověřte:

- jaké jsou úrovně `TX/RX`: `3.3V`, `5V` či přepínatelné;
- jak se úroveň vybírá;
- jaký čip se používá: CH340, CP2102, FTDI či jiný;
- zda existují ovladače pro váš systém;
- zda jsou `DTR` a `RTS` přítomny, pokud je potřeba auto-nahrávání;
- jaký USB konektor;
- zda piny `GND`, `TX`, `RX`, `VCC` jsou v pohodlném pořadí;
- zda existuje schéma či dobrá dokumentace;
- kolik proudu lze brát z `VCC`, pokud je potřebné.

Na diagnostiku ESP32/RP2040/STM32 je adaptér s `3.3V` signály a jasným označením pohodlnější.

## Typické chyby

- připojení `TX` s `TX`, `RX` s `RX`;
- zapomenutí společné `GND`;
- výběr úrovně `5V` pro desku `3.3V`;
- připojení `VCC` na již napájenou desku;
- napájení zátěže přes USB-UART adaptér;
- plení si TTL UART s USB-RS232;
- používání nabíjecího USB kabelu;
- neinstalace ovladače CH340/CP2102/FTDI;
- výběr špatného COM/tty portu;
- nepřipojení `DTR`/`RTS` potřebných pro auto-nahrávání;
- ponechání sériového terminálu otevřeného, poté se divíte, proč nahrávač nemůže port otevřít.

## Klíčové pozorování

USB-UART adaptér je most mezi USB počítače a UART piny zařízení. Na minimální spojení potřebujete křížem propojené `TX/RX` a společnou `GND`.

Hlavní rizika: špatná úroveň `3.3V/5V`, zbytečné připojení napájení, plení si TTL UART s RS-232 a chybějící `DTR`/`RTS` linky na nahrávání.

## Related materials

- [SparkFun: Serial Basic CH340C Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide) - praktický průvodce USB-UART CH340C, `DTR/RX/TX/VCC/CTS/GND` piny, výběr napětí a loopback test.
- [SparkFun: Serial Basic Overview](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide/serial-basic-overview) - popis rozložení pinů a přepínání `3.3V/5V` na adaptéru.
- [Adafruit: FT232H Serial UART](https://learn.adafruit.com/adafruit-ft232h-breakout/serial-uart) - příklad USB-serial adaptéru, `TX`/`RX`, linky řízení toku a připojení na zařízení.
- [Silicon Labs: CP2102 USB to UART Bridge](https://www.silabs.com/interface/usb-bridges/classic/device.cp2102) - oficiální příklad USB-UART přemostovacího čipu a ovladačů Virtual COM Port.
- [Klipper Configuration Reference: `[mcu]`](https://www.klipper3d.org/Config_Reference.html#mcu) - jak se sériové spojení MCU popisuje v Klipperu přes `serial`.
