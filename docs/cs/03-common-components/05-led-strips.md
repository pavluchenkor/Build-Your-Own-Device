# LED pásy

LED pás je pružná deska s LED a vodivými trasami. V tiskárně, sušičce nebo malém DIY zařízení se obvykle používá pro osvětlení komory, indikaci stavu, osvětlení pracovní plochy nebo dekorativní osvětlení krytu.

Hlavní chyba začátečníků je považovat LED pás za malou LED. I krátký pás může odebrat více proudu než ventilátor a dlouhý pás se stane úplnou energetickou zátěží.

## Kde se používá

V zařízeních pro kutily kolem 3D tiskárny jsou LED pásky užitečné pro:

- osvětlení komory tiskárny;
- osvětlení sušičky vláken;
- status indication: heating, drying, error, waiting;
- osvětlení pracovní plochy uvnitř krytu;
- měkké noční osvětlení bez hlavního světla;
- vizuální signál, když tisk skončí nebo dojde k chybě.

Pro provozní osvětlení je obvykle lepší jednoduchý bílý pruh. Pro indikaci režimu jsou vhodné RGB nebo adresovatelné proužky, ale jsou složitější na napájení a ovládání.

## Voltage: 5V, 12V or 24V

LED pásky se dodávají v různých napětích:

- `5V` - often addressable strips like WS2812/NeoPixel;
- `12V` - běžné bílé a RGB pásky;
- `24V` - vhodný pro delší úseky a 24V systémy.

Napětí pásku musí odpovídat napájecímu zdroji. K `24V` nelze připojit pásek `24V`. Proužek `12V` na `5V` může ztmavit nebo nemusí fungovat. Proužek `12V` na `24V` nebo `24V` bude téměř jistě poškozen.

Pokud vaše tiskárna již má `24V`, neznamená to, že se k ní může připojit jakýkoli proužek. Musíte si koupit přesně pásek `24V` nebo dát DC-DC měnič pro správné napětí.

## Pravidelné a adresovatelné proužky

Existují dva hlavní typy LED pásků.

Běžný pruh se rozsvítí najednou. Může to být:

- single-color white;
- warm/cold white;
- RGB pásek, který mění barvu po celé své délce;
- RGBW pásek se samostatným bílým kanálem.

Takový pásek nemá na každé LED žádný mikročip. Jas je řízen přepínáním napájení nebo PWM přes MOSFET, LED kontrolér nebo vhodný výstup na desce.

Adresovatelný pásek má řídící mikročip pro jednotlivé LED nebo skupiny LED. Umožňuje vám osvětlit různé části v různých barvách. Typické příklady: WS2812B, SK6812, proužky kompatibilní s NeoPixel.

Addressable strips require:

- výkon při správném napětí;
- společný `GND` s ovladačem;
- data wire `DIN`;
- správný směr dat podle šipky na proužku;
- often - 5V data signal level;
- opatrná síla bez velkých kapek.

Pro jednoduché osvětlení komory je adresovatelný pásek obvykle přehnaný. Pro hezkou indikaci a efekty je to pohodlné, ale vyžaduje více pozornosti na napájení.

## Proud a výkon

Vybírejte LED pásek nejen podle barvy a délky. Musíte znát jeho sílu.

Stránky produktů obvykle obsahují:

- napětí: například `24V` nebo `24V`;
- výkon na metr: například `9.6 W/m`, `14.4 W/m`, `14.4 W/m`;
- počet LED na metr;
- LED type: for example `3528`, `5050`, `2835`;
- strip width;
- protection degree: bare, silicone jacket, IP65/IP67;
- maximum length per section.

Proud se počítá jednoduše:

```text
current = power / voltage
```

Příklad: máte `24V` pásku `9.6 W/m` při napájení `9.6 W/m`.

```text
total power = 2 m × 9.6 W/m = 19.2 W
current = 19.2 W / 24 V = 0.8 A
```

U takového pásku se musí napájecí zdroj, MOSFET, vodiče a konektor pohodlně ovládat přes `30-50%`. Prakticky je lepší přidat okraj alespoň `30-50%`, zvláště pokud pás běží dlouhou dobu.

U pásků RGB musíte počítat s maximálním proudem všech kanálů. Bílá na RGB obvykle znamená, že jsou současně zapnuté červené, zelené a modré kanály.

U adresovatelných 5V pásků je hrubý odhad až `60 mA` na RGB pixel při plné bílé. V reálných efektech může být proud menší, ale nemůžete dimenzovat napájení a kabeláž na "obvykle ne na plný jas".

## Proč nemůžete napájet strip z GPIO

GPIO ovladače je výstup signálu, nikoli zdroj napájení.

LED pásek nelze připojit přímo ke kolíku mikrokontroléru. GPIO není dimenzováno na proud pásu. To může poškodit desku, způsobit restartování, nestabilní provoz nebo přehřátí stopy.

Correct logic:

- páskový proud pochází z napájecího zdroje;
- ovladač spravuje pouze zapnutí/vypnutí, jas nebo data;
- MOSFET, LED ovladač, LED kontrolér nebo výkonový výstup desky se stará o přepínání napájení;
- regulátor a uzemnění napájení jsou propojeny, pokud existuje řídicí signál.

## Připojení jednoduchého jednobarevného proužku

Pro bílý pásek `24V` nebo `24V` se často používá nízkostranný MOSFET: plus pásku je připojen k napájecímu plus a mínus pásu je přepínán modulem MOSFET.

![Close-up of LED strip with SMD diodes](../../img/03-common-components/05-led-strip-closeup.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:LED_strip_closeup.jpg), Akbermamps, CC BY 4.0*

Typický obvod:

1. Napájení `+` jde na LED pásek `+`.
2. LED pásek `-` jde na výstup MOSFET modulu.
3. Napájení `GND` jde do MOSFET modulu.
4. Regulátor `GND` je připojen ke zdroji `GND`.
5. Ovládací kolík ovladače jde na vstup modulu MOSFET.

Pokud již deska tiskárny má spravovaný výstup pro ventilátory nebo LED diody, můžete ji použít pouze v případě, že je dimenzována na potřebné napětí a proud. Bez kontroly výstupního limitu nemůžete připojit dlouhý pásek k libovolnému náhodnému konektoru.

## RGB Strip

Typický pás RGB má obvykle společné plus a tři spravované mínusy:

- `+V`;
- `R`;
- `G`;
- `B`.

Každý barevný kanál vyžaduje samostatný MOSFET kanál nebo připravený RGB ovladač. Jeden MOSFET pro celý RGB pásek jej může pouze zapnout a vypnout, ne změnit barvu.

Při výběru modulu MOSFET pro pásek RGB se podívejte na proud na kanál a celkový proud. Konektor, svorka a vodič musí také zvládnout zátěž.

## Addressable Strip

Adresovatelný pás má obvykle:

- `+5V` nebo jiné napájení, pokud se nejedná o 5V model;
- `GND`;
- `DIN` - data input;
- někdy `DOUT` - výstup dat do další sekce.

Důležitá pravidla:

- připojte data směrem k šipce na proužku;
- regulátor a pásek musí mít společné uzemnění;
- pro 5V adresovatelné pásky na 3,3V ovladači často potřebujete převodník úrovní;
- před dlouhým pásem je užitečný elektrolytický kondenzátor přes napájení;
- rezistor kolem `300-500 Ohm` je často umístěn v datovém vedení poblíž vstupu proužku;
- u dlouhého pásu je lepší dodávat energii nejen na začátku, ale i na dalších místech.

Pokud je adresovatelný pásek napájen ze samostatného zdroje, nelze použít pouze `GND` bez společného `GND`. Datový signál pak nemá správnou referenční úroveň a proužek bude náhodně blikat nebo nebude fungovat.

## Pokles napětí a vícebodové napájení

Dlouhý LED pásek může být na začátku jasný a na konci znatelně slabší. To není "špatný regulátor", je to pokles napětí na vodičích a měděné stopy pásku.

Čím nižší napětí a vyšší proud, tím horší problém. Pásky `12V` a `24V` tedy častěji potřebují napájení z více míst než pásky `24V` se stejným výkonem.

Signs of voltage drop:

- strip end is dimmer;
- bílá na RGB se změní na žlutou nebo červenou;
- addressable strip flickers during bright effects;
- ovladač se při rozjasnění restartuje;
- wires, connector or strip start become hot.

Solution:

- použijte pásek s vhodným napětím;
- použijte drát s dostatečnou tloušťkou;
- zapojte napájení na začátek a konec dlouhých úseků;
- rozdělit dlouhý pás na části;
- použijte pojistku na elektrickém vedení;
- don't route all current through weak connector or thin traces.

## Teplo a montáž

LED pásek sám o sobě produkuje teplo. To je zvláště patrné u světlých proužků v silikonovém plášti a u proužků namontovaných uvnitř uzavřeného pouzdra.

Bad mounting locations:

- next to a heater;
- na měkkém PLA uvnitř teplé komory;
- na povrchu, který neodvádí teplo;
- kde se pás dotýká pohyblivých částí;
- na krytu, který se často odstraňuje bez konektoru.

Pro dlouhou životnost je lepší pás namontovat na hliníkový profil nebo jiný povrch, který odvádí teplo. Pokud je proužek uvnitř komory tiskárny, zohledněte teplotu komory a teplotu vrstvy lepidla.

## Co zkontrolovat před nákupem

Před zakoupením LED pásku zkontrolujte:

- strip voltage;
- power per meter;
- total length;
- color: white, RGB, RGBW, addressable;
- control type;
- šířka pásu a místo montáže;
- installation location temperature;
- whether you need an aluminum profile;
- whether you need a MOSFET module or LED controller;
- zda napájecí zdroj zvládne dodatečnou zátěž;
- zda je k dispozici správný konektor pro servis.

Pro tiskovou komoru je obvykle praktičtější bílý pásek `24V`, pokud je celý systém již `5V`. Pro malý indikátor ESP32 může být vhodný krátký adresovatelný proužek `5V`. Pro dlouhé dekorativní RGB osvětlení je lepší vypočítat proud předem a přemýšlet o vícebodovém napájení.

## Typické chyby

- připojený pásek na špatné napětí;
- napájecí pásek od GPIO;
- nevypočítal proud pro celou délku;
- vybraný modul MOSFET bez okraje;
- spojený dlouhý pás s tenkým drátem;
- zapomněli jste na společnou zem mezi ovladačem a pásem;
- připojena data adresovatelného pásu k `DIN` místo `DIN`;
- v případě potřeby nenainstaloval převodník úrovní pro 5V adresovatelný pásek z 3,3V ovladače;
- napájen pouze jeden konec dlouhého pásu;
- instalován pás v horké zóně bez kontroly teploty;
- levá lišta bez konektoru na odnímatelném krytu.

## Hlavní bod

LED pásek není signální LED, je to zátěž. Nejprve zkontrolujte napětí a výkon, poté vypočítejte proud, vyberte vodič, MOSFET nebo ovladač a teprve poté připojte k desce.

Pro jednoduché osvětlení zvolte běžný bílý pruh při systémovém napětí. Pro efekty a indikaci můžete použít adresovatelný proužek, ale důležité jsou zejména napájení, společná zem, úroveň signálu a ochrana proti poklesu napětí.

## Reference Materials

- [Adafruit NeoPixel Überguide: Best Practices](https://learn.adafruit.com/adafruit-neopixel-uberguide/best-practices) - practical rules for addressable strips: common ground, data line resistor, capacitor and signal level.
- [Adafruit NeoPixel Überguide: Powering NeoPixels](https://learn.adafruit.com/adafruit-neopixel-uberguide/powering-neopixels) - detailed explanation of addressable strip power, voltage drop and multi-point power.
- [Adafruit RGB LED Strips: Usage](https://learn.adafruit.com/rgb-led-strips/usage) - example of managing regular RGB strips through power transistors/MOSFET, not directly from microcontroller.
- [SparkFun WS2812 Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/ws2812-breakout-hookup-guide/addressable-led-strips) - introduction to addressable WS2812 strips and their variants.
- [QuinLED: 12V vs 24V LED strip and voltage drop](https://quinled.info/2018/08/24/12v-vs-24v-led-strip-or-voltage-drop/) - practical explanation of why long strips suffer from voltage drop and why 24V is often better for long sections.
