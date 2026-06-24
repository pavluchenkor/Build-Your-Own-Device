# 3D tisk

Tato sekce není kurzem 3D tisku.

Slouží jinému účelu: pomoci pochopit, které tištěné součásti lze bezpečně používat v domácím zařízení a které se stávají rizikem blízko topných prvků, elektroniky, drátů a pohyblivých součástí.

V projektech podobných iDryeru se 3D tisk obvykle používá pro:

- enclosures;
- covers;
- air ducts;
- fan brackets;
- sensor holders;
- guides;
- handles and clips;
- decorative or service panels.

Tisk součásti je snadný. Aby součást pracovala bezpečně v teplém pouzdře po dobu měsíců, je obtížnější.

## Klíčové otázky

Než začnete tisknout součást pro zařízení, musíte odpovědět nejen na otázku "vejde se STL do kráječe", ale na několik otázek:

- kde bude součást umístěna;
- jaká bude teplota;
- je v blízkosti topný prvek;
- je v blízkosti 110-230V AC;
- bude součást nést zátěž;
- bude se dotýkat drátů;
- bude dirigovat horký vzduch;
- lze ji vyměnit nebo opravit;
- co se stane, pokud se deformuje.

Pokud deformace součásti může posunout senzor, zablokovat proudění vzduchu, přiblížit drát k horké oblasti nebo uvolnit montáž topného prvku, jde již nejen o "kosmetickou vadu"

## STL není instrukce k montáži

STL popisuje tvar součásti, ale neříká vám:

- z jakého materiálu to tisknout;
- v jaké orientaci to tisknout;
- kolik zdí použít;
- jaké vyplnění použít;
- kde jsou potřeba podpěry;
- jaké šrouby použít;
- jakou teplotu část odolá;
- v jakém směru bude slabší.

Stejný model může být normálním krytem nebo špatným strukturálním držákem v závislosti na materiálu, orientaci a pracovních podmínkách.

Proto pracující součást potřebuje nejen STL, ale také kontext: materiál, nastavení tisku, místo instalace, zátěž a režim teploty.

## Materiál je důležitější než vzhled

Pro prototyp PLA často funguje. Tiskuje se snadno a vytváří pěkně vypadající část.

Ale pro součásti blízko tepla je PLA špatná volba. Problém není v tom, že se hned roztaje, ale že může postupně ztrácet tuhost a tvar při teplotách v uzavřeném pouzdře nebo blízko topného prvku.

U pracovních součástí kolem sušičky, komory nebo topného prvku obvykle zvažujete:

- ABS;
- ASA;
- odolnější inženýrské materiály, pokud máte zkušenosti a vhodnou tiskárnu.

Materiál je vybrán na základě podmínek:

- pracovní teplota;
- tuhost;
- odolnost vůči nárazům;
- smrštění a deformace;
- zápach a emise během tisku;
- chování při zahřátí;
- dokumentace výrobce.

## Teplota uvnitř pouzdra

Teplota uvnitř uzavřeného pouzdra se liší od pokojové teploty.

I když se topný prvek nedotýká plastu, část může být:

- v horkém proudu vzduchu;
- blízko topného prvku;
- blízko chladiče;
- blízko napájecího zdroje;
- v oblasti se špatným větráním;
- na stěně, která se pomalu ohřívá.

Proto nemůžete posoudit bezpečnost pouze frází "součást se nedotýká topného prvku". Musíte pochopit, jaká bude teplota na daném místě během dlouhodobého provozu.

![Zóny v tištěném pouzdru pro ohřívané zařízení](../../img/07-3d-printing/01-printed-device-zones.svg)

## Síla závisí na směru vrstvy

Součásti FDM nejsou stejně silné ve všech směrech.

Směr vrstvy ovlivňuje, jak se součást zlomí:

- podél plastových linií je obvykle silnější;
- mezi vrstvami je často slabší;
- tenké příspěvky a klipy se mohou přelamovat mezi vrstvami;
- šrouby mohou zničit součást, pokud geometrie není pro to navržena.

U konstrukčních držáků je důležité myslet na to, kam půjde zatížení.

Pokud držák ventilátoru jednoduše visí na stěně, to je jedna věc. Pokud držák drží topný prvek nebo osu cívky, orientace tisku a tloušťka stěny se stávají důležitými.

## Pouzdro musí být opravitelné

Dobrý kryt není jen pěkná krabice.

Musí to umožňovat:

- přístup k svorkám;
- výměnu ventilátoru;
- kontrolu teplotního senzoru;
- utažení upevnění;
- odstranění ovladače;
- výměnu vodiče;
- vidět, zda se něco přehřálo nebo ztmavlo.

Pokud potřebujete rozebrat polovinu zařízení, abyste se dostali k pojistce nebo svorkě, bude opravovat se méně často. Toto je špatná inženýrská praxe.

## Tištěná součást nesmí ohrozit bezpečnost

Tištěný kryt může být užitečný, ale nesmí obrátit malou chybu v nebezpečnou situaci.

Špatné scénáře:

- topný prvek se změkčil;
- vzduchový kanál se zkroutil a proudění vzduchu přes topný prvek se snížilo;
- držák termistoru se posunul;
- drát se otřel o ostrou hranu;
- svorka skončila pevně proti plastu;
- kryt zablokoval větrání napájecího zdroje;

Pro horké a nosné zóny je lépe myslet tímto způsobem: pokud se tištěná část deformuje, zařízení by mělo zůstat bezpečné nebo vstoupit do stavu chyby, ne pokračovat v slepém ohřívání.

## Co bude v této sekci

Sekce obsahuje několik praktických témat:

- `02-what-is-stl.md` - proč STL neobsahuje materiál, orientaci, sílu nebo pokyny k montáži.
- `03-materials-petg-abs-asa.md` - základní volby mezi PETG, ABS a ASA.
- `04-heat-resistant-materials.md` - jak myslet na součásti blízko tepla.
- `05-enclosure-design.md` - zóny pouzdra, větrání, upevnění, přístup a zapojení.
- `06-why-pla-is-risky.md` - proč je PLA vhodný pro prototypy, ale riskantní blízko tepla.

## Co tato sekce nedělá

Zde nebude úplný kurz 3D tisku.

Nebudeme se ponořovat do:

- všechny plasty na světě;
- nastavení retrakce;
- dekorativní následné zpracování;
- umělecké modely;
- dokonalou kalibraci tiskárny;
- konkrétní výběr značky vlákna.

Zaměření je jednoduché: součásti pro skutečné zařízení musí být dostatečně silné, odolné vůči teplu, opravitelné a bezpečné.

## Klíčové poznatky

- STL je pouze geometrie, ne bezpečné pokyny k montáži.
- Materiál je vybrán na základě pracovní teploty a zátěže, ne na vzhledu.
- PLA je vhodné pro prototypy, ale riskantní blízko tepla.
- Orientace tisku ovlivňuje sílu.
- Pouzdro by mělo oddělit horkou zónu, elektroniku, napájecí vedení a zónu uživatele.
- Tištěná součást by neměla být jedinou věcí chránící bezpečnost zařízení.

## Reference

- [Prusa Knowledge Base: Material guide](https://help.prusa3d.com/category/material-guide_220) - overview of popular materials, print conditions, and properties.
- [Prusa Knowledge Base: PLA](https://help.prusa3d.com/article/pla_2062) - description of PLA as a simple material for prototypes and parts without high temperature load.
- [Prusa Knowledge Base: Enclosure guidepost](https://cdn.help.prusa3d.com/article/enclosure-guidepost_366332) - why a closed print chamber is needed and how ambient temperature affects printing and materials.
- [Bambu Lab: 3D Printer Filament Comparison Guide](https://bambulab.com/en-us/filament-guide) - comparative table of materials, including PLA, PETG, ABS, ASA, and engineering plastics.
- [Makelab: Is 3D printing strong enough for functional parts?](https://help.makelab.com/help/article/is-3d-printing-strong-enough-for-functional-parts) - practical notes on material, print orientation, walls, infill, and functional parts.
