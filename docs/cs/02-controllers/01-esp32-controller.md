# Řadič ESP32

ESP32 je rodina mikrokontroleérů od Espressifu s Wi-Fi, Bluetooth a rozsáhlou sadou periferií. V DIY zařízeních se volí, když chcete vytvořit samostatný modul: připojuje se ke sítí, čte sensory, zobrazuje stránku v prohlížeči a ovládá jednoduché výstupy.

Pro zařízení kolem 3D tiskárny je ESP32 užitečný nikoli jako "další silová deska", ale jako malý síťový kontrolér: senzor teploty/vlhkosti, ventilační modul, jednoduchý filtr s webovým rozhraním, samostatný monitoring kamer nebo samostatná sušička.

## Kde je ESP32 užitečný

Typické úlohy:

- Wi-Fi senzor teploty a vlhkosti;
- oddělený kontrolér ventilátoru přes MOSFET modul;
- ovládání relé nebo SSR nízkonapěťovým signálem;
- OLED displej přes I2C;
- RFID/NFC čtečka přes SPI nebo UART;
- servo se samostatným napájením;
- jednoduchá webová stránka pro stav a nastavení;
- integrace s MQTT, Home Assistant nebo vlastní lokální logikou;
- autonomní prototyp, který nemusí být součástí Klipperu.

ESP32 je vhodný, když by mělo zařízení fungovat odděleně od tiskárny a vyměňovat si data po síti. Pokud je úkolem pouze přidat piny do Klipperu, je obvykle lepší podívat se na RP2040, STM32 nebo hotovou desku tiskárny.

## Typická architektura zařízení

ESP32 přímo nenapájí zátěž. Vydává řídicí signály a oddělené moduly dělají vlastní práci se napájením.

![Vývojová deska ESP32 s GPIO piny](../../img/02-controllers/01-esp32-dev-board.jpg)

*Zdroj: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:ESP32_Dev_Board.jpg), Edwiyanto, CC BY-SA 4.0*

V praxi to vypadá takto:

- ESP32 je napájen z USB nebo stabilního `5V` na vývojové desce;
- samotná logika ESP32 běží na `3.3V`;
- sensory se připojují na GPIO, I2C, SPI, UART nebo ADC;
- ventilátory, LED pásky, DC topidla se připojují přes MOSFET nebo driver;
- síťová topidla se připojují pouze přes vhodné AC SSR/relé a bezpečnou sekci napájení;
- servo je napájen z oddělného `5V/6V` zdroje, ESP32 poskytuje pouze signál.

GPIO není zdroj napájení pro zátěž. Pin může přepínat vstup driveru, ale neměl by přímo napájet ventilátor, topidlo, relé, servo nebo LED pásku.

## Co ESP32 znamená na desce

Označení "ESP32" může znamenat různé věci:

- samotný čip ESP32;
- modul s čipem, flash pamětí a anténou, například ESP32-WROOM;
- vývojová deska s USB, regulátorem napájení, tlačítky a exponovanými piny;
- novější varianty: ESP32-S3, ESP32-C3, ESP32-C6 a další.

Pro první projekt je pohodlnější použít vývojovou desku než holý modul. Vývojová deska už má USB, regulátor napájení, tlačítka `BOOT`/`EN` a piny pro breadboard.

Před nákupem zkontrolujte:

- přesné jméno desky a čipu;
- zda má USB-C nebo micro-USB;
- který USB-UART nebo vestavěný USB se používá;
- zda existuje schéma a rozložení pinů;
- které GPIO jsou skutečně exponované;
- jaký regulátor napájení je na desce;
- zda má správnou anténu a místo kolem ní;
- zda velikost desky vyhovuje vašemu pouzdru.

## Logika 3.3V

ESP32 pracuje s logickou úrovní `3.3V`. To znamená, že typická úroveň `HIGH` na GPIO je přibližně `3.3V`, nikoli `5V`.

Co na tom záleží:

- neaplikujte `5V` na GPIO ESP32;
- u senzorů a modulů `5V` může být potřeba měnič úrovně;
- pull-up rezistory I2C by měly být připojeny na `3.3V`, pokud je sběrnice připojena k ESP32;
- některé hotové MOSFET/SSR moduly nemusí spolehlivě fungovat na `3.3V`;
- napájení zátěže se nemůže brát z GPIO.

Mnoho senzorů je již k dispozici v `3.3V` variantách. Pro ESP32 je to nejlepší volba.

## Napájení

Vývojové desky mají obvykle vstup USB a pin `5V`/`VIN`, přičemž ESP32 sám je napájen regulátorem `3.3V`.

Běžné chyby:

- napájení ESP32 ze slabého USB kabelu;
- napájení serva, ventilátoru nebo relé z pinu `3.3V` na desce;
- připojení velké zátěže k pinu `5V` bez pochopení, odkud ten proud pochází;
- nepřipojení společné GND mezi ESP32 a nízkonapěťovým driverem;
- reset ESP32, když se Wi-Fi spustí kvůli poklesu napájení.

Wi-Fi odebírá pulzní proud. Pro stabilní provoz jsou důležité kvalitní kabel, regulátor, kondenzátory na desce a oddělené napájení pro zátěž.

## GPIO a speciální piny

ESP32 má mnoho GPIO, ale ne každý pin je stejně vhodný.

V klasickém ESP32:

- některé piny jsou vázány na nahrávání čipu, jedná se o přepínací piny;
- `GPIO6-GPIO11` jsou obvykle obsazeny flash pamětí a nepoužívají se;
- `GPIO34-GPIO39` jsou pouze pro vstup;
- `GPIO1` a `GPIO3` se často používají jako UART pro firmware a logy;
- některé piny mohou být obsazeny LED, tlačítkem nebo jinými obvody na konkrétní vývojové desce.

Přepínací piny určují režim spouštění při startu. Pokud externí obvod přetáhne takový pin špatným způsobem, ESP32 se nemusí spustit nebo může vstoupit do režimu aktualizace firmwaru.

Praktické pravidlo: u první verze používejte piny z rozložení vaší konkrétní desky a vyhněte se pinům označeným `BOOT`, `FLASH`, `STRAP`, `TX0`, `RX0`, `GPIO6-GPIO11`, pokud nerozumíte jejich úloze.

## ADC na ESP32

ESP32 může měřit analogové napětí přes ADC, ale není laboratorním multimetrem.

Co na tom záleží:

- v klasickém ESP32 jsou ADC1 a ADC2;
- ADC2 koliduje s Wi-Fi, takže u Wi-Fi zařízení je lepší používat piny ADC1;
- rozsah měření závisí na nastavení útlumu;
- měření může vyžadovat kalibraci;
- nemůžete aplikovat napětí nad bezpečnou úroveň GPIO na ADC;
- termistor obvykle vyžaduje dělič napětí a správnou tabulku/model v firmwaru.

Pokud potřebujete přesný teplotní senzor, je často jednodušší použít digitální senzor nebo hotový modul se známou knihovnou. U NTC termistoru ESP32 funguje, ale obvod a nastavení ADC musí být ověřeny.

## PWM, I2C, SPI a UART

ESP32 je vhodný pro periferie:

- PWM přes LEDC je vhodný pro ventilátory, podsvícení a signály servomotoru;
- I2C je vhodný pro OLED displeje a mnoho senzorů;
- SPI je vhodný pro RFID moduly, displeje a rychlá zařízení;
- UART je vhodný pro GPS, některé sensory, ostatní kontroléry a ladění.

ESP32 má flexibilní GPIO matici: mnoho signálů lze přiřadit různým pinům. Ale to neznamená, že kterýkoli pin je vždy dobrá volba. Specifické omezení desky, flash paměť, boot piny a obsazené UART se stále musí zvážit.

## ESP32 a Klipper

ESP32 je lépe chápán jako samostatné Wi-Fi/IoT zařízení blízko tiskárny, nikoli jako hlavní cesta pro dodatečný MCU v Klipperu.

Klipper je organizován jako host plus jeden nebo více MCU. Pro nové dodatečné MCU je obvykle praktičtější používat:

- RP2040;
- STM32;
- hotové desky 3D tiskárny.

ESP32 může vyměňovat data se systémem tiskárny odděleně: přes MQTT, HTTP API, Home Assistant, vlastní server nebo jinou integraci. Ale to už není stejné jako přidání `[mcu]` do konfigurace Klipperu a přímé používání pinů.

## Co zkontrolovat před nákupem

Před nákupem desky ESP32 zkontrolujte:

- přesný model: ESP32, S3, C3, C6 atd.;
- logické napětí;
- zda má USB a jak se deska nahrává;
- zda existuje oficiální rozložení pinů nebo schéma;
- které piny jsou bezpečné pro GPIO;
- které piny jsou jen pro vstup;
- které piny jsou obsazeny flash/PSRAM, USB, UART nebo LED;
- zda máte dostatek ADC/I2C/SPI/UART pro úkol;
- jak je deska napájena;
- zda se vejde do pouzdra;
- zda existuje knihovna nebo firmware pro váš scénář.

Pokud deska z tržiště nemá schéma a správné rozložení pinů, lze ji použít pro experimenty, ale není vhodná pro zařízení, které musí běžet bez dozoru po dlouhou dobu.

## Běžné chyby

- aplikace `5V` na GPIO ESP32;
- napájení zátěže z GPIO;
- napájení serva nebo relé ze slabého pinu `3.3V`;
- zapomenutí společné GND s MOSFET/driverem;
- výběr ADC2 pinu pro senzor a následné povolení Wi-Fi;
- používání boot přepínacího pinu, takže se ESP32 nespustí;
- používání `GPIO34-GPIO39` jako výstupy;
- nákup modulu bez rozložení pinů a schématu;
- myšlenka, že "ESP32 s Wi-Fi" automaticky znamená bezpečné řízení síťového topidla;
- pokus nahradit silovou elektroniku firmwarem.

## Klíčové body

ESP32 je dobrá volba pro autonomní Wi-Fi zařízení: sensory, webová rozhraní, jednoduché řízení ventilace, filtry, displeje a periferie.

Ale ESP32 pracuje s logikou `3.3V`, má speciální piny a neměl by přímo napájet zátěž. Pro silové obvody jsou potřebné MOSFET, drivery, relé nebo SSR, a pro síťové topidlo je potřebná úplná bezpečná sekce napájení.

## Související materiály

- [Espressif: ESP32 Wi-Fi & Bluetooth SoC](https://www.espressif.com/en/products/socs/esp32/datasheet) — oficiální přehled rodiny ESP32, modulů, vývojových desek a odkazů na dokumentaci.
- [Espressif: ESP32 Series Datasheet](https://documentation.espressif.com/esp32_datasheet_en.html) — charakteristiky čipu, periferie, ADC, PWM, UART, I2C, SPI a omezení pinů.
- [ESP-IDF Programming Guide: GPIO & RTC GPIO](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html) — tabulka GPIO, přepínací piny, piny jen pro vstup, flash/PSRAM piny a omezení ADC2 s Wi-Fi.
- [Espressif: ESP32 Hardware Design Guidelines](https://docs.espressif.com/projects/esp-hardware-design-guidelines/en/latest/esp32/esp-hardware-design-guidelines-en-master-esp32.pdf) — doporučení pro napájení, přepínací piny, GPIO, ADC a návrh desky.
- [Arduino-ESP32: LED Control API](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/ledc.html) — PWM/LEDC v Arduino-ESP32 pro ventilátory, podsvícení a další PWM signály.
- [Klipper: Code overview](https://www.klipper3d.org/Code_Overview.html) — kontext architektury Klipperu pro MCU a seznam podporovaných mikrokontrolérů v stromu zdrojů.
