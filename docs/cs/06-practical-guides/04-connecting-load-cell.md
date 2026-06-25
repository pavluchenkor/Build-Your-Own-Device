# Připojení tenzometru

Tenzometr měří sílu nebo váhu skrz nepatrné deformace kovového nosníku, tlačítka nebo platformy.

V zařízeních podobných iDryer-u může tenzometr odhadnout váhu cívky, zbývající filament nebo zátěž mechanismu.

Hlavní bod: tenzometr se téměř nikdy nepřipojuje přímo ke kontroléru. Jeho signál je příliš malý. Obvykle je mezi senzor a kontrolér umístěn modul HX711 nebo podobný zesilovač/ADC.

## Co potřebujete

Minimální souprava:

- tenzometr potřebného rozsahu váhy;
- modul HX711;
- kontrolér: Arduino, ESP32, RP2040, STM32 nebo jiná deska;
- tuhá mechanická montáž;
- známá hmota pro kalibraci;
- krátké, úhledné vodiče.

Pokud je mechanika špatná, obvod jí nepomůže. Tenzometr lze správně zapojit, ale dává nesmyslné údaje kvůli chybném zarovnání, vůli nebo zátěži aplikované na špatném místě.

## Jak je připojení uspořádáno

Tenzometr se připojuje k HX711 s analogovými vodiči.

HX711 se připojuje k kontroléru s digitálními vodiči.

Typický řetězec:

```text
tenzometr -> HX711 -> kontrolér
```

HX711 obvykle má dvě strany:

- vstup z tenzometru: `E+`, `E-`, `A+`, `A-` nebo podobné;
- připojení k kontroléru: `VCC`, `GND`, `DT`/`DOUT`, `SCK`/`CLK`.

![Schéma připojení HX711 a tenzometru](../../img/06-practical-guides/04-hx711-load-cell-fritzing.jpg)

*Zdroj: [SparkFun Electronics](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide/all), CC BY-SA 4.0*

## Vodiče tenzometru

Typický čtyřvodičový tenzometr obvykle má:

- `E+` - napájení mostu plus;
- `E-` - napájení mostu minus;
- `S+`, `A+` nebo `O+` - pozitivní měřicí signál;
- `S-`, `A-` nebo `O-` - negativní měřicí signál.

Běžné barevné schéma:

- červená - `E+`;
- černá - `E-`;
- zelená nebo modrá - `A+`;
- bílá - `A-`.

Ale barvy nejsou zákon. Různé senzory se mohou lišit. Pokud existuje specifikace pro konkrétní tenzometr, řiďte se jím.

Pokud má senzor pátý vodič, folii nebo stínění, je to často elektromagnetické stínění. Nezaměňujte si jej s mostikovým měřicím vodičem. Obvykle je stínění připojeno na `GND` nebo kryt na jedné straně, pokud to dokumentace říká, ale ne na měřicí `A+`/`A-`.

Pokud neexistuje schéma vodičů, nepřipojujte tenzometr "náhodně". Nejdřív najděte specifikaci tenzometru nebo změřte most podle průvodce výrobce: nesprávné vodiče snadno dávají nestabilní údaje nebo přetěžují vstup HX711.

## Připojení HX711 k kontroléru

Na straně kontroléru obvykle potřebujete čtyři linky:

- `VCC` - napájení modulu;
- `GND` - společná záporná;
- `DT`, `DOUT` nebo `DATA` - data;
- `SCK`, `CLK` nebo `PD_SCK` - hodiny.

U mnoha modulů HX711 může být napájení `3.3V` nebo `5V`, ale zkontrolujte konkrétní modul. Pokud běží kontrolér na 3.3V, je vhodné použít modul a napájení kompatibilní s logikou 3.3V.

Piny `DT` a `SCK` se obvykle mohou připojit na běžné GPIO. Toto není I2C nebo SPI v obvyklém smyslu, ale jednoduché dvouvodičové rozhraní HX711.

## Mechanika je důležitější než obvod

Tenzometr se musí deformovat tak, jak výrobce zamýšlel.

Pro paprskový senzor se obvykle jedna strana montuje na pevný podklad a druhá strana nese zátěž. Pokud jsou obě strany tuze připevněny na jednu součást, senzor se nebude normálně ohýbat.

Zkontrolujte:

- kde je montážní strana senzoru;
- kam by měla být aplikována zátěž;
- kterým směrem by měla jít síla;
- zda jsou potřebné podložky;
- zda pohyblivá část neprolamuje kryt;
- bez chybného zarovnání;
- bez bočního zatížení;
- šrouby nejsou přetaženy;
- cívka nebo platforma nepřistane mimo pracovní zónu senzoru.

Pro váhu cívky je zvláště důležité, aby veškerá zátěž procházela senzorem, ne částečně skrz stěnu pouzdra, osu, kabel nebo ozdobný kryt.

## Nepřetěžujte senzor

Rozsah tenzometru není doporučením, ale limitem měření.

Pokud je 1 kg senzor umístěn tam, kde cívka a držák mohou překročit limit, senzor bude fungovat špatně nebo se trvale deformuje.

Zvolte rozsah s rezervou:

- maximální váha cívky;
- váha držáku;
- možné nárazy;
- chybné zarovnání;
- bezpečnostní rezerva pro chybu uživatele.

Ale příliš velký rozsah také není vždy dobrý. 100 kg senzor bude vnímat malou cívku hůře než 5 kg nebo 10 kg senzor se stejnou mechanikou a elektronikou.

## První spuštění

Před instalací v zařízení testujte systém na lavici:

1. Připojte tenzometr k HX711.
2. Připojte HX711 k kontroléru.
3. Spusťte test kódu nebo knihovnu.
4. Ujistěte se, že se surové hodnoty mění, když stisknete senzor.
5. Odstraňte zátěž a zkontrolujte, že je hodnota poměrně stabilní.
6. Umístěte známou hmotu a zkontrolujte změnu.

V tomto stadiu neočekávejte přesnost na gram. Nejdřív musíte vidět, že senzor je živý, směr zátěže je správný a údaje se mění předvídatelně.

Pokud se hodnota snižuje se zvyšující se váhou, obvykle jen vyměňte `A+` a `A-` nebo vezměte znaménko v kódu.

## Tárování a kalibrace

Tenzometr bez kalibrace neví, co jsou gramy.

Typický proces:

1. Umístěte prázdnou platformu.
2. Tárujte: toto je nula s ohledem na váhu platformy.
3. Umístěte známou hmotu.
4. Vyberte kalibrační faktor.
5. Zkontrolujte několik různých vah.

Pro cívky s filamentem rozhodněte, co se počítá jako váha:

- celá cívka s plastem;
- pouze zbývající plast bez váhy prázdné cívky;
- změna váhy od počáteční hodnoty.

Pokud různé výrobci vyrábějí prázdné cívky s různými vahami, přesný výpočet zbytku vyžaduje znalost specifické váhy prázdné cívky nebo práci s hrubými odhady.

## Šum a nestabilní údaje

HX711 měří velmi malý signál, takže je systém citlivý na šum a mechanické problémy.

Příčiny nestabilních údajů:

- dlouhé vodiče z tenzometru na HX711;
- špatné kontakty;
- napájecí vodiče topidla vedle signálních vodičů;
- vibrace ventilátoru nebo tiskárny;
- měkké základny;
- vůle v montáži;
- teplotní drift;
- zátěž dotýkající se pouzdra obcházením senzoru.

Praktická opatření:

- udržujte HX711 blízko tenzometru;
- nevedete signální vodiče vedle napájecích vodičů topidla;
- zajistěte vodiče, aby netahaly senzor;
- používejte průměrování měření;
- kalibrujte po montáži do pouzdra;
- tárujte po zahřátí zařízení, pokud teplota výrazně ovlivňuje údaje.

## Co kontrolovat po montáži

Před použitím:

- senzor je hodnocen na potřebnou váhu;
- zátěž projde pracovní částí senzoru;
- upevnění neblokuje deformaci;
- HX711 dostává správné napájení;
- `DT` a `SCK` jsou připojeny na správné GPIO;
- existuje společná zem;
- surové hodnoty se mění pod zátěží;
- bez zátěže se údaje neposunují příliš rychle;
- známá hmota ukazuje očekávanou váhu po kalibraci;
- vodiče netahají platformu;
- cívka nebo držák se nedotýká pouzdra mimo senzor.

## Běžné chyby

- připojení tenzometru přímo na analogový vstup kontroléru;
- zaměňování `E+`/`E-` a `A+`/`A-`;
- důvěřování barevným kódům bez specifikace;
- zapomenutí kalibrace;
- tárování před konečnou mechanickou instalací;
- montáž senzoru tak, aby se nemohl ohýbat;
- přetížení senzoru;
- výběr příliš velkého rozsahu a ztráta citlivosti;
- nestabilita z dlouhých vodičů a interference;
- očekávání přesnosti na gram od pružného plastového těla bez tuhé mechaniky.

## Klíčové body

- Tenzometr se obvykle připojuje skrz HX711, ne přímo ke kontroléru.
- Vodiče senzoru jdou na `E+`, `E-`, `A+`, `A-`.
- HX711 se připojuje k kontroléru přes napájení, zem, `DT` a `SCK`.
- Mechanika záleží víc než obvod: zátěž musí projít senzorem správně.
- Tárování a kalibrace se známou hmotou jsou vyžadovány.
- Bez tuhé montáže a správné mechaniky nebudou přesné údaje.

## Související čtení

- [SparkFun: Průvodce připojením zesilovače tenzometru HX711](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide/all) - praktické připojení HX711 a tenzometru, barvy vodičů, `DT`/`SCK` a příklad kalibrace.
- [SparkFun: Stránka produktu zesilovače tenzometru HX711](https://www.sparkfun.com/sparkfun-load-cell-amplifier-hx711.html) - popis modulu HX711, účel a rozhraní mikrokontroléru.
- [DigiKey: Specifikace HX711 od Avia Semiconductor](https://www.digikey.com/en/htmldatasheets/production/1836471/0/0/1/hx711.html) - technická specifikace HX711: 24-bit ADC, diferenciální vstup mostu, zisk a digitální rozhraní.
- [Phidgets: Průvodce tenzometrem](https://cdn.phidgets.com/docs/Load_Cell_Guide) - praktické příklady mechanické instalace tenzometru a směr aplikace zátěže.
- [SparkFun vyřazený průvodce HX711: mechanická nastavení tenzometru](https://learn.sparkfun.com/tutorials/retired---load-cell-amplifier-hx711-breakout-hookup-guide) - užitečné ilustrace paprskových, tlačítko a platformy montáž senzorů.
