# Řadič RP2040

RP2040 je mikrokontroleér Raspberry Pi. Nejznámější deska na něm je Raspberry Pi Pico.

Pro DIY periferie kolem 3D tiskárny je RP2040 jednou z nejpraktičtějších voleb: je levný, dobře zdokumentován, pracuje s logikou `3.3V`, je pohodlný na nahrávání přes USB a je vhodný jako dodatečný MCU pro Klipper.

## Kde je RP2040 užitečný

RP2040 je vhodný pro:

- dodatečnou I/O desku pro Klipper;
- kontrolér ventilátoru přes MOSFET/drivery;
- čtení termistorů a jednoduchých analogových senzorů;
- připojení OLED přes I2C;
- připojení RFID/NFC přes SPI nebo UART;
- ovládání servomotoru PWM signálem;
- jednoduchou samostatnou desku bez Wi-Fi;
- testovací pult na sensory a rozhraní.

Pokud potřebujete síťování ze startovního balíčku, je jednodušší podívat se na ESP32 nebo Pico W. Pokud potřebujete dodatečný drátový MCU pro Klipper, je RP2040 často pohodlnější.

## Proč je Raspberry Pi Pico vhodný

Raspberry Pi Pico je hotová vývojová deska na bázi RP2040. Má USB, flash paměť, regulátor napájení, tlačítko `BOOTSEL` a exponované piny.

Výhody Pica:

- nízké náklady;
- slušná dokumentace a rozložení pinů;
- USB pro nahrávání a komunikaci;
- mnoho GPIO;
- logika `3.3V`;
- 2 UART, 2 SPI, 2 I2C;
- 16 PWM kanálů;
- 3 ADC vstupy na exponovaných pinech Pica;
- PIO pro nestandardní rozhraní;
- pohodlné nahrávání UF2 přes USB paměťové zařízení.

Pro první projekt je lepší koupit Pico nebo Pico H se připájenými piny než holý čip RP2040. Holý čip vyžaduje vlastní desku, flash paměť, napájení, USB, vedení a testování.

## BOOTSEL a UF2

Jednou ze sil Pica je jednoduchý proces nahrávání:

1. Podržte tlačítko `BOOTSEL`.
2. Připojte USB k počítači.
3. Deska se objeví jako USB disk.
4. Zkopírujte soubor `.uf2` firmwaru.
5. Deska se restartuje s novým firmwarem.

To je pohodlné pro MicroPython, CircuitPython, projekty C/C++ a firmware Klipperu. Pro začátečníka je tato metoda obvykle srozumitelnější než ST-Link, DFU nebo oddělený USB-UART.

## RP2040 a Klipper

RP2040 je dobrým kandidátem na dodatečný MCU v Klipperu.

Typické schéma:

![Raspberry Pi Pico s čipem RP2040](../../img/02-controllers/03-rp2040-pico-photo.jpg)

*Zdroj: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Raspberry_Pi_Pico_oblique.jpg), Phiarc, CC BY-SA 4.0*

Myšlenka je:

- Linux host s Klipperem zůstává primárním kontrolérem;
- Pico/RP2040 se nahraje s firmwarem Klipperu MCU;
- do `printer.cfg` se přidá sekce hlavního nebo dodatečného `[mcu]`;
- piny RP2040 lze použít na ventilátory, sensory, PWM a další periferie;
- síťové zátěže se stále připojují přes MOSFET, driver, relé nebo SSR.

To je užitečné, když potřebujete separovat část periferie do samostatného bloku: například ventilátory, senzory kamer, filtr, podsvícení, tlačítko, koncový spínač nebo servisní výstupy.

## GPIO a logika 3.3V

RP2040 pracuje s logikou `3.3V`. To znamená:

- neaplikujte `5V` na GPIO;
- u modulů `5V` může být potřeba měnič úrovně;
- pull-up rezistory I2C by měly být na `3.3V`;
- GPIO by nemělo přímo napájet zátěž;
- ventilátor, LED pásku, relé nebo topidlo vyžaduje externí spínač/driver.

Pokud je modul "Arduino-kompatibilní", neznamená to, že je bezpečný pro RP2040. Musíte zkontrolovat vstupní úrovně a pull-upy.

## Napájení

Pico je obvykle napájen z USB nebo přes pin `VSYS`. Deska má regulátor na napájení mikrokontroléru.

Praktická pravidla:

- nenapájejte motory, servomotory a relé z pinu `3V3` na Picu;
- používejte oddělené napájení na zátěž;
- připojte společnou GND s nízkonapěťovými drivery;
- zkontrolujte, odkud pochází napájení k `VSYS` a USB;
- zvažte proud externí modulů, ne jen samotného Pica.

Pokud se Pico resetuje, když se spustí servo nebo ventilátor, je skoro vždycky napájení, zem nebo šum.

## ADC na Picu

Pico má ADC vstupy, které můžete použít na jednoduché analogové úlohy:

- termistor přes dělič napětí;
- potenciometr;
- snímač světla;
- měření nízkého napětí přes dělič napětí.

Omezení:

- ADC vstup nesmí přesáhnout bezpečné napětí GPIO;
- na měření `12V` nebo `24V` potřebujete dělič a ochranu;
- termistor vyžaduje správný rezistor, tabulku/model a mechanický kontakt;
- ADC nenahrazuje multimetr nebo průmyslový měřič.

Na topidla si pamatujte: ADC pouze čte senzor. Bezpečnost topidla je zajištěna spínačem napájení, limity firmware, pojistkou a nezávislou tepelnou ochranou.

## PIO v jednoduchých pojmech

PIO je Programmable I/O. RP2040 má malé programovatelné bloky, které mohou generovat nebo číst nestandardní signály bez trvalého zatížení hlavního kódu.

Začátečník nemusí začínat s PIO. Ale toto je jeden důvod, proč je RP2040 populární na rozhraní, timingu a nestandardních periferiích.

Pro jednoduché zařízení podobné iDryer je obvykle dost normální GPIO, PWM, I2C, SPI, UART a ADC.

## Pico, Pico W a Pico 2

Je důležité nepleist si desky:

- **Pico / Pico H** — klasická deska RP2040 bez Wi-Fi;
- **Pico W / Pico WH** — RP2040 s modulem Wi-Fi/Bluetooth na desce;
- **Pico 2 / Pico 2 W** — nová generace na bázi RP2350, to není RP2040.

Pokud článek nebo projekt říká RP2040, obvykle myslí prvou generaci Pica nebo kompatibilní desku. Pico 2 je konceptuálně podobný, ale je to jiný mikrokontroleér a kompatibilita firmware/pinů je třeba zkontrolovat zvlášť.

## Co zkontrolovat před nákupem

Před nákupem desky na bázi RP2040 zkontrolujte:

- zda je to originální Pico, Pico W nebo klon;
- zda jsou piny připájeny;
- zda má USB konektor, který potřebujete;
- zda existuje správné rozložení pinů;
- které GPIO jsou dostupné;
- zda potřebujete Wi-Fi;
- zda je deska vhodná pro firmware Klipperu;
- jak budou deska a zátěž napájeny;
- zda máte dostatek ADC/PWM/I2C/SPI/UART na úkol;
- zda je místo v pouzdru na montáž.

Pokud plánujete MCU Klipperu, zkontrolujte předem existující pokyny pro konkrétní desku a metodu nahrávání.

## Běžné chyby

- aplikace `5V` na GPIO RP2040;
- napájení serva nebo relé z `3V3`;
- zapomenutí společné GND s MOSFET/driverem;
- myšlenka, že Pico W je obyčejný Pico bez zohlednění využitých prostředků/napájení Wi-Fi;
- nákup Pica 2 s očekáváním přesného chování RP2040;
- měření `12V`/`24V` na ADC bez dělače;
- připojení topidla přímo k pinu;
- výběr RP2040 pro Wi-Fi úkol, když normální Pico nemá Wi-Fi;
- nekontrolování rozložení pinů konkrétního klonu.

## Klíčové body

RP2040 a Raspberry Pi Pico jsou silnou volbou na drátové DIY periferie a dodatečný MCU v Klipperu. Deska je levná, srozumitelná, dobře zdokumentovaná a pohodlná na nahrávání.

Ale RP2040 je mikrokontroleér `3.3V`, nikoli silový kontrolér. Zátěž se připojuje přes drivery, MOSFET, relé nebo SSR. Pro Wi-Fi úlohy potřebujete Pico W nebo jiný síťovaný kontrolér.

## Související materiály

- [Raspberry Pi: RP2040 specifications](https://www.raspberrypi.com/products/rp2040/specifications/) — oficiální specifikace RP2040: CPU, SRAM, UART/SPI/I2C, PWM, USB a PIO.
- [Raspberry Pi Documentation: Pico-series microcontrollers](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html) — rozdíly mezi Pico, Pico W, Pico 2, GPIO, ADC, PWM a variantami desek.
- [RP2040 Datasheet](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf) — podrobný technický popis mikrokontroléru, periferií, PIO, GPIO a ADC.
- [Raspberry Pi Pico Datasheet](https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf) — dokumentace pro samotnou desku Pico: napájení, USB, exponované GPIO a omezení desky.
- [Raspberry Pi Documentation: C/C++ SDK - Your First Binaries](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html#your-first-binaries) — oficiální příklad BOOTSEL, USB paměťového zařízení `RPI-RP2` a kopírování UF2 do Pica.
- [Klipper Configuration Reference](https://www.klipper3d.org/Config_Reference.html) — kontext podpory RP2040 v Klipperu a nastavení pro periferie jako I2C.
