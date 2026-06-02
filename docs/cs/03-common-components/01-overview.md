# Běžné součástky

Běžné součástky jsou díly a moduly, které se nejčastěji setkáte při montáži zařízení podobného iDryer nebo periferií 3D tiskárny.

Účel této sekce:

Tato sekce slouží jako reference pro díly, které skutečně držíte v rukou během montáže.

Zde nepotřebujete hluboké znalosti elektroniky. Hlavním cílem je vám pomoci pochopit:

- co tato součástka je;
- proč ji potřebujete;
- jak se obvykle připojuje;
- čím ji můžete nahradit;
- jaké parametry jsou důležité při nákupu;
- co se nejčastěji poruší při prvním připojení.

Formát každé stránky:

- co to je;
- kde se používá v iDryer a periferích 3D tiskárny;
- jak vypadá typické připojení;
- důležité vlastnosti;
- typické chyby;
- krátka kontrolní seznam před nákupem.

Navrhované soubory:

- `02-heaters.md` - topidla: PTC, silikonové podložky, kartuše, 12V/24V/110-230V AC.
- `03-fans.md` - ventilátory: 2-pin, 3-pin, 4-pin PWM, napětí, proud, hluk, průtok vzduchu.
- `04-thermistors.md` - termistory: NTC 100K, tabulky, montáž, otevřené/zkratované obvody.
- `05-led-strips.md` - LED pásy: 5V/12V/24V, normální a adresovatelné, proud na metr.
- `06-servo-motors.md` - servomotory: napájení, signál, úhel, špičkový proud.
- `07-load-cells.md` - váhové čidla: HX711, kalibrování, mechanická montáž.
- `08-oled-display.md` - OLED: I2C/SPI, adresa, napájení, kdy je potřeba.
- `09-touchscreen.md` - TFT/dotyková: UART/SPI/HDMI, napájení, kompatibilita.
- `10-rfid-and-nfc.md` - RFID/NFC: karty, štítky, frekvence, připojení.

## Referenční materiály

- [Klipper Configuration Reference](https://www.klipper3d.org/Config_Reference.html) - oficiální sekce Klipperu o topidlech, ventilátorech, teplotních senzorech, servomotorech a displejích v konfiguraci.
- [DigiKey: Selecting A Fan](https://www.digikey.com/en/articles/selecting-a-fan) - praktický výběr ventilátoru podle průtoku, statického tlaku, odporu pouzdra a tepelného úkolu.
- [Adafruit: MOSFET Driver](https://learn.adafruit.com/adafruit-mosfet-driver) - proč se vysokovýkonné zátěže nepřipojují přímo ke GPIO a proč potřebujete výkonový spínač.
- [SparkFun: Load Cell Amplifier HX711 Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide) - příklad váhového čidla, HX711, napájení, signálních vodičů a kalibrování.
- [Adafruit: PN532 RFID/NFC Breakout Wiring](https://learn.adafruit.com/adafruit-pn532-rfid-nfc/breakout-wiring) - příklad součástky, kde musíte předem zkontrolovat napájení, logické úrovně a vybrané rozhraní.

## Viz také

- [Topidla](02-heaters.md) - nejobjektivnější typ zátěže: napájení, teplota, SSR/MOSFET a nezávislá ochrana.
- [Ventilátory](03-fans.md) - průtok vzduchu, statický tlak, 2-pin/3-pin/4-pin a napájení.
- [Termistory](04-thermistors.md) - teplotní senzor jako základ pro zpětnou vazbu topidla.
- [Připojení ventilátoru](../06-practical-guides/01-connecting-fan.md) - praktický příklad připojení součástky přes výkonový spínač.
- [Chyby topidla a SSR](../08-common-mistakes/05-heater-ssr-mistakes.md) - běžné chyby s vysokovýkonem a sítě zátěží.
