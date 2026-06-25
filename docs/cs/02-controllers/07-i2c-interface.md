# Rozhraní I2C

I2C je komunikační rozhraní pro malé mikročipy a moduly blízko kontroléru. Rozšíření: `Inter-Integrated Circuit`. V dokumentaci často vidíte `I2C sběrnice`.

Hlavní myšlenka: více zařízení se může připojit ke stejným dvěma signálním linkám `SDA` a `SCL`, pokud mají různé adresy.

## Kde se I2C používá

V jednoduchých zařízeních kolem 3D tiskárny se I2C často používá na:

- OLED displeje;
- senzory teploty, vlhkosti, tlaku a světla;
- hodiny reálného času;
- expanzéry GPIO;
- některé enkodéry a modulové tlačítka;
- I2C multiplexery;
- některé RFID/NFC moduly;
- malé pomocné desky.

I2C funguje dobře na krátká spojení v jednom pouzdru. Na dlouhé vodiče přes celou tiskárnu nebo blízko napájecích linek se to stává rizikovým.

## SDA, SCL, napájení a GND

Typický I2C modul má 4 kontakty:

- `VCC` nebo `VIN` - napájení;
- `GND` - společná zem;
- `SDA` - data;
- `SCL` - hodinový signál.

Obvod s více zařízeními vypadá takto:

![I2C sběrnice: jeden master a tři zařízení na společné SDA/SCL](../../img/02-controllers/07-i2c-bus-topology.svg)

*Zdroj: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:I2C.svg), Cburnett, CC BY-SA 3.0*

Všechna zařízení na stejné I2C sběrnici se připojují na stejné `SDA`, `SCL` a `GND`. Napájení může být společné, ale jeho napětí a logické úrovně musí být ověřeny pro každý modul.

## Adresy zařízení

Každé I2C zařízení má adresu. Například malé OLED obvykle používají `0x3C`, některé sensory `0x76`, `0x77`, `0x68`, `0x69` a tak dále.

Pokud mají dvě zařízení na stejné sběrnici stejnou adresu, kontrolér je nemůže jednotlivě správně adresovat.

Co s konflikty adres:

- změňte adresu přes jumper nebo mosty, pokud modul podporuje;
- vyberte si jinou variantu modulu;
- používejte I2C multiplexer;
- rozdělte zařízení na různé I2C, pokud kontrolér a firmware získáte.

Adresa je často v hexadecimálním formátu (`hex`): `0x3C`. Ale firmware nebo config mohou vyžadovat některý desítkový formát (`decimal`). Například `0x3C` v desítce je `60`. Musíte zkontrolovat dokumentaci konkrétního systému.

## Pull-up rezistory

I2C linky fungují přes pull-up rezistory. Zařízení na sběrnici mohou typicky tahat `SDA` nebo `SCL` dolů a vysoká úroveň přichází z pull-up na napájecí logice.

Bez pull-upů sběrnice nemusí fungovat. Ale příliš mnoho modulů s vlastními pull-upy na jedné sběrnici může být také problém: celkový odpor je příliš malý, linky jsou více zatíženy, hrany signálů a úrovně se degradují.

Prakticky:

- mnoho OLED a modulů senzoru již má pull-up rezistory;
- na krátké jednoduché sběrnici to obvykle funguje hned;
- pokud je více zařízení, musíte zkontrolovat schémata modulů a celkové pull-upy;
- pokud je sběrnice nestabilní, jedním z prvních kontrol jsou pull-up rezistory.

Běžný počáteční odpor pro oddělené sběrnice je kolem `4.7 kOhm`, ale pull-upy v hotových modulech mohou být různé.

## 3.3V a 5V

I2C je obzvláště citlivý na napěťové úrovně, protože `SDA` a `SCL` jsou obvykle taženy na nějaké napájecí napětí.

ESP32, RP2040 a STM32 typicky pracují s logikou `3.3V`. Arduino Uno/Nano často pracuje s logikou `5V`.

Nebezpečná situace:

- kontrolér `3.3V`;
- I2C modul napájen z `5V`;
- pull-up rezistory na modulu tahají `SDA` a `SCL` na `5V`.

V tomto případě může se objevit `5V` na GPIO kontroléru. To může poškodit mikrokontroleér.

Před připojením ověřte:

- jaké napětí je modul napájen;
- na jaké napětí jsou `SDA` a `SCL` taženy;
- zda je na modulu měnič úrovně;
- zda je modul kompatibilní s kontrolérem `3.3V`.

Pokud si nejste jistí, používejte napájení `3.3V` na I2C moduly nebo měnič úrovně.

## Rychlost

Typické I2C rychlosti:

```text
100000   # standardní režim, 100 kHz
400000   # rychlý režim, 400 kHz
```

Na krátké vodiče a normální moduly často funguje `400 kHz`. Ale na dlouhé vodiče, slabé pull-upy, mnoho zařízení nebo hlučné prostředí je lepší začít s `100 kHz`.

V Klipperu parametr `i2c_speed` není stejně podporován na všech MCU. Dokumentace uvádí, že mnoho mikrokontroleérů používá `100000`, zatímco některé platformy podporují `400000`. Takže nemůžete jen napsat vysokou rychlost a předpokládat, že se skutečně aplikuje.

## I2C scanner

I2C scanner je malý program či příkaz, který iteruje adresami a ukazuje, která zařízení na sběrnici reagují.

Pomáhá pochopit:

- vidí kontrolér modul;
- jaká je adresa zařízení;
- nejsou `SDA` a `SCL` prohozeni;
- je tam napájení a společná `GND`;
- je konflikt adres.

Ale scanner neprokazuje, že zařízení plně funguje. Jen ukazuje, že někdo reaguje na tu adresu.

## I2C v Klipperu

V Klipperu je I2C zařízení připojeno na konkrétní MCU.

Konfigurace může obsahovat parametry:

- `i2c_mcu` - na který MCU je zařízení připojeno;
- `i2c_bus` - hardwarová I2C sběrnice, pokud je více;
- `i2c_software_scl_pin` a `i2c_software_sda_pin` - softwarový I2C na vybraných pinech;
- `i2c_address` - adresa zařízení;
- `i2c_speed` - rychlost, pokud je podporována.

Důležité: `i2c_address` v Klipperu je často zadávána jako desítkové číslo, ne hex formát. Pokud datalist říká `0x3C`, config může vyžadovat `60`.

Pokud je zařízení připojeno na dodatečný MCU, musí se také zadat. Jinak bude Klipper hledat na hlavní desce.

## Délka vodiče a interference

I2C je navržen na krátká spojení. V malém pouzdru nebo na jedné desce je pohodlný. V 3D tiskárně jsou podmínky horší:

- motory v blízkosti;
- topidla v blízkosti;
- dlouhé vodiče;
- konektory na dveřích;
- napájecí linky ventilátorů a topidel;
- elektromagnetické rušení.

Praktická pravidla:

- udržujte `SDA` a `SCL` krátké;
- vedete je blízko `GND`;
- nevedete paralelně s napájecími vodiči topidla;
- nedělejte dlouhé páskové kabely na pohyblivé části bez důvodu;
- snižte rychlost na `100 kHz`, pokud jsou chyby;
- používejte správné konektory a úpravu proti tahu;
- na dlouhá spojení si vyberte jiné rozhraní: UART, CAN, RS-485 či místní MCU blízko sensoru.

## Co zkontrolovat před připojením

Před připojením I2C modulu ověřte:

- napájení modulu;
- logickou úroveň;
- na jaké napětí jsou `SDA` a `SCL` taženy;
- adresa zařízení;
- zda lze adresu změnit;
- zda není konflikt s jinými zařízeními;
- délku vodiče;
- zda je podpora firmwaru;
- který MCU a sběrnice je zařízení připojeno;
- zda je potřeba hardwarový nebo softwarový I2C.

## Typické chyby

- prohození `SDA` a `SCL`;
- zapomenutí společné `GND`;
- aplikace pull-upů `5V` na kontrolér `3.3V`;
- dvě zařízení mají stejnou adresu;
- zadaná hex adresa, kde byla potřeba desítková;
- používání příliš dlouhých vodičů;
- připojení mnoha modulů s pull-up rezistory;
- výběr modulu nepodporovaného firmwarem;
- připojení zařízení na dodatečný MCU bez zadání `i2c_mcu`;
- plení si I2C a I2S.

## Klíčové pozorování

I2C je pohodlný na malé displeje, sensory a pomocné moduly blízko kontroléru. Vyžaduje `SDA`, `SCL`, napájení a společnou `GND`.

Hlavní kontroly před připojením: adresa, úroveň `3.3V/5V`, pull-up rezistory, délka vodiče a podpora firmwaru. V hlučném prostředí tiskárny udržujte I2C krátký.

## Související materiály

- [SparkFun: I2C at the Hardware Level](https://learn.sparkfun.com/tutorials/i2c/i2c-at-the-hardware-level) - praktický výklad `SDA`, `SCL`, open-drain linek a pull-up rezistorů.
- [SparkFun: I2C tutorial](https://learn.sparkfun.com/tutorials/i2c/all) - obecný průvodce I2C, adresy, více zařízení na sběrnici a hardwarové rysy.
- [Adafruit: STEMMA QT technical specs](https://learn.adafruit.com/introducing-adafruit-stemma-qt/technical-specs) - příklad standardizovaného I2C konektoru, rozložení pinů, napájení a `GND`.
- [Adafruit: PCA9548 I2C multiplexer](https://learn.adafruit.com/adafruit-pca9548-8-channel-stemma-qt-qwiic-i2c-multiplexer/pinouts) - příklad řešení konfliktů duplicitních I2C adres přes multiplexer.
- [Klipper Configuration Reference: common I2C settings](https://www.klipper3d.org/Config_Reference.html) - `i2c_address`, `i2c_mcu`, `i2c_bus`, softwarový I2C a parametry `i2c_speed`.
