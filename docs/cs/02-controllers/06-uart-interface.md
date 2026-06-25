# Rozhraní UART

UART je jednoduché sériové rozhraní na přenos dat mezi dvěma zařízeními. Rozšíření: `Universal Asynchronous Receiver/Transmitter`.

V praktických projektech obvykle slyšíte "UART", "sériový", "TX/RX" či "UART port". Pro začátečníka klíčový bod je: UART vysílá data na linku `TX`, přijímá na `RX` a obě zařízení potřebují společnou `GND` na správný provoz.

## Kde se UART používá

UART se najde skoro všude:

- logy ladění z mikrokontroleérů;
- nahrávání desek přes USB-UART adaptér;
- komunikace host-MCU v některých scénářích Klipperu;
- GPS, RFID, biometrické a modulové sensory;
- konfigurace TMC stepper driveru;
- komunikace mezi dvěma mikrokontroleéry;
- servisní port na desce.

UART je vhodný, protože vyžaduje málo vodičů a funguje dobře na jednoduchý text, příkazy a diagnostickou výměnu.

## TX, RX a GND

Minimální připojení:

- `TX` - vysílání;
- `RX` - přijímání;
- `GND` - společná zem.

TX jednoho zařízení se spojuje s RX druhého:

![Křížem spojené TX/RX a společná GND v UART spojení](../../img/02-controllers/06-uart-tx-rx-crossover.png)

*Zdroj: [SparkFun Electronics](https://learn.sparkfun.com/tutorials/serial-communication/all), CC BY-SA 4.0*

Pravidlo:

```text
Zařízení A TX -> Zařízení B RX
Zařízení A RX <- Zařízení B TX
Zařízení A GND -> Zařízení B GND
```

Nejčastější chyba je připojení `TX` s `TX` a `RX` s `RX`. Někdy jsou označení modulů matoucí, takže pokud není spojení, nejprve ověřte rozložení pinů a dokumentaci místo náhodné změny všech vodičů.

## UART, USB a USB-UART

UART není USB.

Počítač typicky nemá prosté piny UART. Proto je potřeba USB-UART adaptér: na jedné straně se připojuje na USB počítače a na druhé poskytuje `TX`, `RX`, `GND` a někdy `VCC`, `DTR`, `CTS` linky.

Příklady:

- počítač čte logy z desky přes USB-UART;
- USB-UART nahraje desku bez vestavěného USB;
- host se spojuje s MCU po sériové lince;
- adaptér pomáhá obnovit desku po selhání nahrávání.

Neplešte si USB konektor na desce s UART piny na hlavici. Na některých deskách je USB už spojeno s vestavěným USB-UART čipem, na druhých jde USB přímo do mikrokontroléru.

## Logické úrovně: 3.3V, 5V, RS-232

UART popisuje metodu přenosu dat, ale nezaručuje bezpečné napěťové úrovně.

V DIY elektronice je TTL/CMOS UART nejčastější:

- `3.3V` UART - ESP32, RP2040, STM32 a mnoho moderních desek;
- `5V` UART - Arduino Uno/Nano a některé starší moduly.

Aplikace signálu `5V` na vstup mikrokontroléru `3.3V` může poškodit desku. Na nekompatibilní úrovně je potřeba měnič úrovně či jiný obvod na sladění.

Existuje také RS-232, což je odděleno. To není "jen UART na DB9 konektoru". RS-232 má různé napěťové úrovně a jinou elektrickou logiku. Nemůžete připojit skutečný port RS-232 přímo na GPIO mikrokontroléru. Potřebuje měnič úrovně, jako MAX232-ový obvod či hotový adaptér.

## Rychlost a formát

Rychlost UART si musí odpovídat. Běžné hodnoty:

```text
9600
57600
115200
250000
1000000
```

Pokud se rychlost neshoduje, terminál bude ukazovat nesmysly nebo ticho.

Existuje také formát přenosu. Často se používá `8N1`:

- `8` - 8 datových bitů;
- `N` - bez parity;
- `1` - jeden stop bit.

Na most jednoduché úlohy je nastavení stejné rychlosti a standardního `8N1` dostatečné, pokud dokumentace modulu nevyžaduje jinak.

## UART v 3D tiskárnách

V 3D tiskárnách UART často slouží třem různým rolím.

**Komunikace hostu a desky**

Některé desky se mohou komunikovat s hostitelem přes sériový/UART. V Klipperu se to popisuje v sekci `serial` přes `serial`.

**Konfigurace TMC driveru**

Některé stepper drivery používají UART na konfiguraci proudu, stealthChop/spreadCycle, diagnostiku a čtení stavu. Motor sám je obvykle řízen ne UART, ale signály `STEP` a `DIR`.

**Ladění a nahrávání**

UART lze používat na logy, režim bootloaderu a obnovu desky přes USB-UART adaptér.

## Jeden UART - obvykle dvě aktivní zařízení

Klasický UART je spojení mezi dvěma zařízeními. Nemůžete slepě spojovat více vysílačů na jednu `RX` linku.

Problémy:

- dvě zařízení současně tahají `TX` linku;
- data se smíchají;
- jeden modul přijme příkazy určené pro druhého;
- možný elektrický konflikt.

Někdy jeden `TX` mohou poslouchat více přijímačů, ale to je vědomé rozhodnutí a ne vhodné jako univerzální pravidlo. Pro začátečníky je bezpečnější předpokládat: jeden UART port - jedna dvojice zařízení.

## Co zkontrolovat před připojením

Před připojením UART ověřte:

- kde jsou `TX` a `RX`;
- potřebuje se společná `GND`;
- logická úroveň: `3.3V` nebo `5V`;
- je to TTL UART nebo RS-232;
- rychlost přenosu;
- formát, pokud je specifikován;
- není UART obsazen USB logy nebo nahráváním;
- není tu jiný vysílač připojený na tuto linku;
- potřebuje se připojit napájení nebo jen `TX`/`RX`/`GND`.

Napájení z USB-UART adaptéru se připojuje jen, je-li jasné, že by měla být deska napájena z něj. Často pro diagnostiku stačí jen `TX`, `RX` a `GND`.

## Typické chyby

- připojení `TX` s `TX`, `RX` s `RX`;
- zapomenutí společné `GND`;
- aplikace `5V` UART na `3.3V` vstup;
- zmatení TTL UART a RS-232;
- výběr špatné rychlosti;
- připojení napájení z USB-UART adaptéru na již napajenou desku;
- používání UART pinů obsazených USB logy nebo bootloaderem;
- připojení více vysílačů na jednu linku;
- myšlenka, že UART může přímo řídit výkonnou zátěž.

## Klíčové pozorování

UART je jednoduché rozhraní na výměnu dat mezi dvěma zařízeními. Potřebujete křížem propojené `TX`/`RX`, společnou `GND`, shodnou rychlost a kompatibilní logické úrovně.

UART není zdroj napájení a nejedná se o silový výstup. Přenáší data, ne spin motorů nebo aktivaci topidel přímo.

## Související materiály

- [SparkFun: Serial Communication](https://learn.sparkfun.com/tutorials/serial-communication/all) - dobrý praktický výklad UART, TX/RX, baudrate, TTL sériový, RS-232 a běžné chyby.
- [SparkFun: Serial Communication - UARTs](https://learn.sparkfun.com/tutorials/serial-communication/uarts) - co dělá UART uvnitř mikrokontroléru a proč jsou TX/RX potřeba.
- [Adafruit: Serial UART on FT232H](https://learn.adafruit.com/adafruit-ft232h-breakout/serial-uart) - příklad USB-UART adaptéru a připojení TX/RX/GND k sériovému zařízení.
- [SparkFun: Serial Basic CH340C Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide) - příklad USB-UART adaptéru, RX/TX/VCC/GND pinů a loopback testu.
- [Klipper: Configuration reference - `[mcu]`](https://www.klipper3d.org/Config_Reference.html#mcu) - jak se sériové spojení MCU popisuje v konfiguraci Klipperu.
