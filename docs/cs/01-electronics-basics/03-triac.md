# TRIAC

TRIAC, neboli tyristor, je výkonový polovodičový spínač střídavého proudu. Používá se tam, kde chcete zapínat nebo ovládat zátěž na střídavém proudu: například topidlo v síti, žárovku nebo jiné jednoduché zařízení na `110-230V AC`.

Pro domácí zařízení je to téma vysokého rizika. TRIAC sám o sobě nedělá síťové napětí bezpečným. Poskytuje pouze způsob, jak ovládat zátěž na střídavém proudu bez mechanických kontaktů.

## Jak se TRIAC liší od MOSFET

Modul MOSFET z předchozího článku se obvykle používá pro stejnosměrné zátěže: `5V`, `12V`, `24V`.

TRIAC se používá pro zátěže na střídavém proudu. Aktivuje se řídicím pulsem a vede proud, dokud proud přes něj neklesne pod hodnotu drž. V síti na střídavém proudu se to obvykle děje kolem nulového průchodu sinusovky.

V praxi:

- MOSFET - typická volba pro `12V`/`24V` ventilátor, LED pás nebo stejnosměrné topidlo;
- TRIAC - typický prvek v regulátorech střídavého výkonu a mnoho AC SSR;
- SSR - hotové polovodičové relé, které může obsahovat optokuplér, TRIAC/tyristor, kryt, svorky a někdy chladič.

Pro začátečníka je pro zátěž v síti často bezpečnější zvážit hotové SSR nebo certifikovaný modul, než si sestavovat vlastní obvod TRIAC na nepájivém poli.

## Proč se používá pro zátěže na střídavém proudu

Výkonná zátěž při nízkém napětí vyžaduje vysoký proud.

Například:

```text
24V 240W -> 10A
24V 300W -> 12.5A
230V 300W -> přibližně 1.3A
```

Na `24V` potřebujete silné vodiče, výkonný zdroj, silný MOSFET, normální svorky a chlazení. Na `230V AC` je proud nižší, ale existuje nebezpečné síťové napětí a všechny elektrické bezpečnostní požadavky.

Přístup přes TRIAC není "lepší" a není "jednodušší". Je to jiný kompromis: menší proud v silové části, ale mnohem vyšší nároky na izolaci, kryt, pojistku, vzdálenosti a kvalifikaci.

## Typická architektura

Řídič není obvykle připojen přímo k TRIAC.

Typická bezpečná architektura vypadá takto:

![Obvod AC dimeru s TRIAC](../../img/01-electronics-basics/03-triac-dimmer-circuit.svg)

*Zdroj: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:TRIAC_based_dimmer_circuit.svg), Osbertjoel, CC BY-SA 4.0*

Má:

- nízkovoltáž: řídič a řídící rezistor;
- optoisolace TRIAC: přenáší příkaz přes optickou izolaci;
- část v síti: výkonný TRIAC, zátěž AC, pojistka, svorky a kryt;
- někdy obvod tlumení a varistor/TVS pro šum a skokové přepětí.

Optoisolace TRIAC je potřebná pro galvanickou izolaci. To znamená, že mezi mikrokontrolérem a částí v síti není přímé elektrické spojení. Řízení se přenáší světlem v optokupleru.

Galvanická izolace snižuje riziko, že by síťové napětí dosáhlo řídícího prvku, USB a počítače. Ale to nemusí část v síti bezpečnou na dotyk.

## Nulový průchod a fázové řízení

Optoisolace TRIAC mají nulový průchod a bez něj.

Optoisolace TRIAC s nulovým průchodem zapíná zátěž blízko nulového průchodu síťového napětí. To je pohodlné pro jednoduché zapnutí/vypnutí topidla nebo jiné odporové zátěže: méně šumu a měkčího přepínání.

Optoisolace TRIAC bez nulového průchodu se používá tam, kde je potřeba fázové řízení výkonu, například dimer. Takový obvod je složitější: musíte detekovat nulový průchod, počítat zpoždění a brát v úvahu šum.

Pro topidlo v sušičce nebo komoře obvykle není potřebné řízení úrovně dimeru. Často stačí pomalé zapnutí/vypnutí nebo řízení shluků, pokud je to podporováno vybraným modulem a bezpečné pro zátěž.

## Jaké zátěže jsou vhodné

TRIAC se nejsnáze používá s odporovými zátěžemi na AC:

- topidlo;
- žárovka;
- jednoduchá tepelná zátěž bez elektroniky.

Buďte opatrní s:

- motory;
- ventilátory AC;
- transformátory;
- solenoidy;
- zdroji napětí;
- elektronickými ovladači;
- zátěžemi s velkým nárazovým proudem.

Induktivní zátěž posouvá fázi proudu vůči napětí a může interferovat s normálním vypnutím TRIAC. Může vyžadovat jiné typy TRIAC, obvod tlumení, varistor nebo jinou metodu spínání.

Zdroj napětí nebo elektronický ovladač by se neměl považovat za normální odporovou zátěž. Pokud má svou vlastní elektroniku, řízení TRIAC může fungovat špatně nebo nebezpečně.

## Obvod tlumení

Tlumení je RC obvod (rezistor + kondenzátor paralelně s TRIAC), který tlumí prudké změny napětí a zabraňuje falešnému spuštění TRIAC.

Může pomoci:

- s induktivními zátěžemi;
- s rychlým šumem v síti;
- s falešným spuštěním TRIAC;
- s problémy vypnutí.

Typický výchozí bod pro odporovou zátěž 200–400 W na 230 V: **100 nF + 100 Ω**. Kondenzátor musí být typu X2 nebo ekvivalentní, hodnocený pro provoz v síťovém obvodu. Toto není univerzální řešení, ale výchozí hodnota. Pro jinou zátěž se hodnoty přepočítávají podle datalisty TRIAC a aplikačních poznámek výrobce.

Pokud nemáte zkušenosti s obvody na AC, je lépe použít hotový modul nebo SSR, kde je tlumení již vypočítáno výrobcem.

## Ohřev a chladič

TRIAC se během provozu zahřívá. Není to dokonalý spínač: na něm je pokles napětí, což znamená, že se generuje teplo.

Musíte zkontrolovat:

- proud zátěže;
- pouzdro TRIAC;
- pokles napětí v zapnutém stavu;
- požadavky na chladič;
- teplota okolí;
- teplota uvnitř obalu;
- vzdálenost od plastu a vodičů;
- rezerva parametrů.

V technické specifikaci je mnoho parametrů. Pro první volbu stačí tři:

- `IT(RMS)` — maximální efektivní proud přes TRIAC. Měl by být vyšší než proud zátěže s rezervou, při aktuálním chlazení.
- `VDRM`/`VRRM` — maximální napětí v otevřeném stavu. Pro síť 230 V zvolte TRIAC s hodnocením 600 V a vyšší.
- `IGT` — brána proud. Měl by odpovídat možnostem optoisolace TRIAC.

Ostatní parametry (`IH`, `dV/dt`, `Tj`, `Rth`) jsou důležité pro přesný výpočet nebo když jsou problémy v reálném obvodu.

Proudové hodnocení v technické specifikaci je dáno za určitých chladicích podmínek. V uzavřeném, teplém pouzdru bez chladiče je skutečný maximální proud nižší.

## TRIAC a SSR

SSR pro zátěž AC často používá optokuplér a TRIAC nebo výkonový stupeň tyristoru uvnitř.

Výhody hotového SSR:

- pohodlné svorky;
- jasný vstup řízení;
- kryt;
- uvedené parametry;
- často snazší mechanické připojení a chlazení.

Nevýhody:

- SSR se také zahřívá;
- je potřebný správný typ: AC-výstupní SSR pro AC zátěž;
- mnoho SSR vyžaduje chladič;
- trh má mnoho padělků a modulů s nadhodnocenou specifikací;
- SSR nenahrazuje pojistku, kryt a elektrickou bezpečnost.

Je-li úkolem ovládat topidlo v síti v reálném zařízení, je hotové kvalitní SSR často praktičtější než domácí obvod se samostatným TRIAC.

## Co nemůžete dělat

Nemůžete:

- sestavit obvod TRIAC v síti na nepájivém poli;
- nechat otevřenou část v síti pod proudem;
- připojit řídící prvek přímo k části v síti bez izolace;
- použít modul MOSFET pro nízké napětí místo TRIAC/SSR pro `230V AC`;
- dát náhodný kondenzátor do obvodu tlumení v síti;
- považovat "40A" štítek na levném modulu za dostatečné ověření;
- bez pojistky;
- umístit sítové svorky vedle USB, tlačítek a otevřených nízkovoltážních kontaktů;
- testovat takový obvod bez pochopení elektrické bezpečnosti.

Práce s `110-230V AC` vyžaduje znalosti, správné nástroje, kryt, kontrolu izolace a porozumění místním pravidlům. Pokud si nejste jisti, měl by kvalifikovaná osoba sestavu nebo kontrolu silové části provést.

## Co zkontrolovat před nákupem

Před nákupem TRIAC, modulu nebo SSR zkontrolujte:

- je to AC nebo DC zátěž;
- síťové napětí;
- proud zátěže a výkon;
- je to odporová nebo induktivní zátěž;
- je potřeba nulový průchod;
- je potřebné tlumení;
- maximální proud při aktuálním chlazení;
- je potřeba chladič;
- je tam optoisolace;
- svorky a rozestup pro síť;
- pojistka a kryt;
- je tam technická specifikace nebo dokumentace výrobce.

Pokud není dokumentace a modul má ovládat topidlo v síti, je to špatná volba.

## Běžné chyby

- používání TRIAC pro stejnosměrné zátěž;
- zmatek MOSFET, TRIAC a SSR;
- připojení zátěže v síti bez optoisolace;
- použití optoisolace TRIAC s nulovým průchodem a očekávání hladkého stmívání;
- použití TRIAC s motorem bez tlumení a kontroly typu zátěže;
- neinstalace chladiče;
- neúčtování teploty uvnitř obalu;
- použití náhodných svorek a tenkých vodičů;
- myšlenka, že SSR nebo TRIAC nahrazuje pojistku;
- ponechání otevřené části v síti vedle řídícího prvku a USB.

## Hlavní bod

TRIAC je výkonový spínač pro zátěže AC. Užitečný je pro zátěže v síti, například topidla, ale vyžaduje správný design části v síti.

Pro mikrokontrolér je potřebná optoisolace. Pro zátěž je potřebný správný TRIAC/SSR, pojistka, svorky, kryt, chladič je-li potřeba, a ověření bezpečnosti. Pokud nemáte zkušenosti s `110-230V AC`, nesestavujte si část v síti sami.

## Referenční materiály

- [STMicroelectronics: Standard and snubberless triacs documentation](https://www.st.com/en/thyristors-scr-and-ac-switches/standard-and-snubberless-triacs/documentation.html) - TRIAC výběr, parametry a aplikační poznámky k standardním/bez tlumení TRIAC.
- [ST AN437: RC snubber circuit design for TRIACs](https://www.alldatasheet.com/datasheet-pdf/pdf/696239/STMICROELECTRONICS/AN437.html) - podrobné vysvětlení, proč je tlumící RC obvod potřeba a jak ovlivňuje vypnutí TRIAC.
- [MOC3063 datasheet: zero-cross optoisolator TRIAC driver](https://www.alldatasheet.com/html-pdf/5043/MOTOROLA/MOC3063/258/1/MOC3063.html) - příklad optoisolace TRIAC pro rozhraní logiky s `115/240 VAC` zátěží.
- [Omron: Overview of Solid-state Relays](https://www.ia.omron.com/support/guide/18/introduction.html) - základní vysvětlení SSR jako polovodičového relé bez mechanických kontaktů.
- [Omron SSR glossary: phototriac, zero-cross, snubber](https://www.ia.omron.com/support/guide/31/further_information.html) - stručné definice fototiristoru, nulového průchodu a obvodu tlumení.
