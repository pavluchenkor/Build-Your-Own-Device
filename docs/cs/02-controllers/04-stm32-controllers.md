# Řadiče STM32

STM32 je velká rodina 32bitových mikrokontroleérů od STMicroelectronics na bázi Arm Cortex-M jader. Není to jedna deska nebo jeden čip: pod názvem STM32 je desítky řad a několik modelů.

Ve světě 3D tiskáren je STM32 velmi běžný. Mnoho hotových desek tiskáren, expanzních desek, CAN desek a kontrolérů používá STM32. Pro Klipper a periférie tiskárny je to jedním z nejpraktičtějších řešení, pokud jste připraveni pracovat s konkrétní deskou.

## Kde je STM32 užitečný

STM32 je vhodný pro:

- hlavní desku 3D tiskárny;
- dodatečný MCU v Klipperu;
- desku na ovládání ventilátoru, sensoru a výstupu;
- CAN desku nebo desku na hlavu nástrojů;
- vážnější vlastní desku;
- úlohy vyžadující timery, PWM, ADC, UART, SPI, I2C, CAN nebo USB;
- projekty vyžadující hotový průmyslový ekosystém a dokumentaci.

Pokud je RP2040 jednoduché a jasné začátek, STM32 je širokým světem kontrolérů, kde si můžete vybrat čip pro skoro jakoukoli úlohu. Ale flexibilita přichází s cenou složitosti.

## STM32 je rodina

Nemůžete říct "dostal jsem STM32" a skončit s výběrem. Musíte znát přesný model.

Příklady řad:

- **STM32F0 / STM32C0 / STM32G0** — rozpočtové a masové řady;
- **STM32F1** — stará, ale velmi známá řada, často se vyskytuje v Blue Pill a starých deskách;
- **STM32F4** — výkonnější řada, populární v kontrolérech;
- **STM32G4** — zajímavá na řízení, timer a úlohy periferií;
- **STM32H7** — výkonné high-end kontroléry;
- **STM32L / STM32U** — řady zaměřené na nízkou spotřebu.

Pro typického uživatele na marketingu řady nezáleží, ale na konkrétních věcech:

- je tam podpora ve firmware, který potřebujete;
- kolik GPIO je skutečně exponováno na desce;
- má USB, CAN, UART, I2C, SPI;
- kolik flash a RAM;
- jak se nahraje;
- existuje správné rozložení pinů a schéma.

## Deska je důležitější než jméno čipu

Stejný STM32 může být na velmi různých deskách.

Běžné varianty:

- **Blue Pill / Black Pill** — levné malé desky, často s STM32F103 nebo třídou STM32F4, ale kvalita klonů se liší;
- **STM32 Nucleo** — oficiální ST vývojové desky s vestavěným ST-LINK;
- **hotová deska 3D tiskárny** — již má drivery, konektory, MOSFET výstupy, termistorové vstupy, pojistky a konektor napájení;
- **deska na hlavu nástrojů/CAN** — specializovaná deska na hlavu tiskárny nebo vzdálený modul;
- **vlastní deska** — vyžaduje úplný návrh napájení, USB, SWD, ochrany a vedení.

Pro první praktický projekt je obvykle jednodušší koupit hotovou desku s dokumentací než holý STM32 nebo náhodný klon bez schématu.

## STM32 a Klipper

STM32 je jednou z hlavních cest pro MCU Klipperu.

Typická architektura:

![Desky Nucleo pro STM8 a STM32 od STMicroelectronics](../../img/02-controllers/04-stm32-nucleo-boards.jpg)

*Zdroj: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Nucleo-board.jpg), Avandalen, CC BY-SA 4.0*

Host Klipperu běží na Linux zařízení a deska STM32 fyzicky ovládá piny: přepíná MOSFET výstupy, čte termistory, ovládá ventilátory, přijímá signály koncového spínače a komunikuje s hostem přes USB, UART nebo CAN.

Pro periferie podobné iDryer má STM32 smysl, pokud:

- zařízení by mělo být součástí konfigurace Klipperu;
- potřebujete hotovou desku tiskárny se silovými výstupy;
- potřebujete CAN;
- potřebujete průmyslovější přístup k desce;
- již máte desku STM32 a známou konfiguraci.

Pokud potřebujete rychle přidat pár pinů a senzorů, je RP2040 často jednodušší. Pokud potřebujete hotovou výkonnou desku s konektory a drivery, deska STM32 může být lepší.

## Nahrávání: USB, DFU, UART, SWD, ST-LINK

STM32 nemá jednu univerzální metodu nahrávání pro všechny desky.

Možnosti:

- **USB bootloader / DFU** — nahrávání přes vestavěný USB bootloader, pokud je deska a čip podporují;
- **UART bootloader** — nahrávání přes sériové piny ve správném BOOT režimu;
- **SWD přes ST-LINK** — spolehlivý způsob nahrávání a ladění přes programátor;
- **vestavěný ST-LINK na Nucleo** — pohodlný na vývoj;
- **bootloader na desce tiskárny** — někdy se nahrávání dělá přes SD kartu, USB nebo speciální bootloader výrobce.

Takže před nákupem desky musíte hledat nejen datasheet čipu, ale pokyny pro konkrétní desku. Pro Klipper je obzvláště důležité číst komentáře v hotové konfiguraci desky a pokyny výrobce.

## Nucleo, Blue Pill a desky tiskáren

**Desky STM32 Nucleo** jsou vhodné na učení a prototypování. Obvykle mají vestavěný ST-LINK, konektory Arduino Uno V3 a ST morpho piny, které poskytují přístup k více signálům. Toto je dobrá volba, pokud chcete naučit se STM32 a máte oficiální nástroj na nahrávání.

**Blue Pill / Black Pill** jsou atraktivní cenou a velikostí, ale klony často mají problémy: špatný čip, slabý regulátor, špatný USB, bez správného schématu, zvláštní bootloader. Na experimenty jsou užitečné, na spolehlivé zařízení — pouze po ověření.

**Hotové desky 3D tiskáren** jsou pro topidla, ventilátory a sensory často praktičtější, protože je sekce napájení již vedena: jsou tam svorky, MOSFET výstupy, termistorové vstupy, napájení, pojistky či místo pro ně. Ale i hotová deska vyžaduje kontrolu proudů, konektorů, chlazení a bezpečnosti.

## Logika 3.3V a GPIO

Většina STM32 pracuje s logikou `3.3V`.

Důležité:

- neaplikujte `5V` na piny, pokud datalist čipu konkrétně neřekne, že pin akceptuje `5V`;
- kompatibilita štítu Arduino na Nucleo neznamená, že všechny signály jsou bezpečné jako na `5V` Arduino Uno;
- pull-up rezistory I2C jsou obvykle na `3.3V`;
- GPIO by nemělo přímo napájet zátěž;
- ventilátory, LED pásky, topidla, relé a servomotory se připojují přes drivery a oddělené napájení.

I když některé piny STM32 akceptují `5V`, není to povolení spojit všechno. Musíte zkontrolovat tabulku rozložení pinů a elektrické charakteristiky konkrétního čipu.

## Proč je STM32 často vybrán pro tiskárny

STM32 je vhodný pro desky 3D tiskáren, protože má spoustu užitečných periferií:

- timery a PWM na ventilátory, topidla a signály;
- ADC na termistory a sensory;
- UART/SPI na stepper drivery a moduly;
- I2C na displeje a sensory;
- USB na komunikaci s hostem;
- CAN v některých řadách a deskách;
- dostatek výkonu pro real-time úlohy MCU.

Ale samotný mikrokontroleér desku bezpečnou neučiní. Topidla, silové MOSFET, SSR, pojistky, konektory a tepelná ochrana zůstávají samostatným inženýrským úkolem.

## Co zkontrolovat před nákupem

Před nákupem desky STM32 zkontrolujte:

- přesný model mikrokontroléru;
- zda je podpora v Klipperu nebo firmware, který potřebujete;
- kolik flash a RAM;
- jak se deska nahraje;
- zda má USB, CAN, UART či jiné potřebné rozhraní;
- zda existuje oficiální rozložení pinů a schéma;
- které piny jsou obsazeny LED, USB, oscilátorem, boot režimem nebo SWD;
- které piny tolerují `5V` a které ne;
- které silové výstupy jsou na desce a jaký proud tolerují;
- zda jsou pojistky, svorky a správné napájení;
- jak srozumitelná je dokumentace výrobce.

Pokud je deska prodávána pouze s hezkou fotkou bez schématu, není to dobrý základ pro zařízení s topidlem.

## Běžné chyby

- myšlenka, že STM32 je jedna konkrétní deska;
- nákup klonu Blue Pill a očekávání chování oficiální desky;
- nekontrolování přesného modelu čipu;
- nepochopení, jak se deska nahraje;
- plení si DFU, BOOT0, UART a ST-LINK;
- připojení modulu `5V` k pinu, který `5V` nesnese;
- používání SWD pinů jako normálních GPIO a ztráta schopnosti nahrávání/ladění;
- myšlenka, že GPIO je silový výstup;
- výběr desky bez schématu na topidlo;
- nekontrolování hotové konfigurace Klipperu před nákupem.

## Klíčové body

STM32 je výkonná a praktická rodina mikrokontroleérů, zejména na desky 3D tiskáren a MCU Klipperu. Ale musíte vybrat ne "STM32 všeobecně", ale konkrétní desku s konkrétním čipem, rozložením pinů, metodou nahrávání a dokumentací.

Na první jednoduchý kontrolér je RP2040 často jednodušší. Na hotové elektroniky tiskáren, CAN desky a vážnější periferie je STM32 často správnou volbou.

## Související materiály

- [STMicroelectronics: STM32 32-bit Arm Cortex MCUs](https://www.st.com/en/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-mcus.html) — oficiální přehled rodiny STM32, řad, výkonu a nástrojů.
- [STMicroelectronics: STM32 Mainstream MCUs](https://www.st.com/en/microcontrollers-microprocessors/stm32-mainstream-mcus.html) — přehled masových řad STM32C0, G0, F0, F1, G4 a jejich postavení.
- [STMicroelectronics: STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) — oficiální nástroj STM32 na nahrávání přes ST-LINK/SWD, UART, USB DFU, I2C, SPI a CAN bootloader.
- [STMicroelectronics: NUCLEO-F103RB](https://www.st.com/en/product/nucleo-f103rb) — příklad oficiální desky Nucleo se vestavěným ST-LINK, konektory Arduino Uno V3 a ST morpho piny.
- [ST UM1724: STM32 Nucleo-64 boards user manual](https://www.st.com/resource/en/user_manual/dm00105823-stlink-v2-in-circuit-debugger-programmer-for-stm8-and-stm32-stmicroelectronics.pdf) — dokumentace pro Nucleo-64, konektory, ST-LINK a varování na `3.3V` I/O.
- [Klipper: Code overview](https://www.klipper3d.org/Code_Overview.html) — architektura Klipperu a kontext MCU, včetně STM32 ve stromu zdrojů.
