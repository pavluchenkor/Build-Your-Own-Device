# Tepelně odolné materiály

Pro součásti blízko tepla záleží ne na štítku "tepelně odolné", ale na skutečném chování materiálu v jejich konkrétním designu.

Součást nemusí táhnout, ale již může:

- změkčit se;
- ohnout se;
- lézt pod šroubem;
- změnit velikost;
- ztratit tuhost;
- uvolnit upevnění;
- posunout senzor;
- zablokovat proudění vzduchu.

Proto je "teplota tání" téměř nikdy hlavním parametrem pro pouzdro, držák nebo vzduchový kanál.

## Co se počítá jako horká zóna

Horká zóna není jen tam, kde sedí topný prvek.

V domácím zařízení mohou horké oblasti zahrnovat:

- proud vzduchu po topném prvku;
- stěna blízko topného prvku;
- bod montáže termistoru;
- vzduchový kanál;
- oblast nad napájecím zdrojem;
- umístění blízko SSR nebo MOSFET s chladičem;
- uzavřená komora, která se zcela ohřeje.

Pokud je součást v takové zóně, materiál se volí s rezervou a testuje se v skutečné montáži.

## Pracovní teplota, ne tání

Tání je již pozdní stadium problému.

Pro tištěnou součást je důležitější:

- při jaké teplotě ztrácí tuhost;
- zda je tam zátěž;
- kolik hodin bude pracovat;
- je tam horký vzduch;
- je tam vibrace;
- drží šroub nebo spoj;
- co se stane, pokud se deformuje.

Senzorový držák se může stát nebezpečným již před viditelným selháním. Pokud se senzor posune od povrchu, ovladač může pokračovat v ohřívání, protože čte špatnou teplotu.

## Základní možnosti

Hrubá hierarchie materiálů:

- PLA - pro studené prototypy a dekorativní součásti daleko od tepla.
- PETG - základní volba pro mírné teploty a jednoduché pracovní součásti.
- ABS/ASA - lepší pro teplejší a mechanicky zatížené součásti, pokud máte tiskové podmínky.
- PA/nylon - odolný technický materiál, ale velmi závislý na vlhkosti a tiskových podmínkách.
- PC/polykarbonát - více tepelně odolný a silný materiál, ale obtížný tisk.
- Kompozity s uhlíkovým nebo skleněným plnidlem - mohou být pevnější a stabilnější, ale vyžadují vhodnou trysku a porozumění vlastnostem.
- Kov, skleněné vlákno, keramika nebo hotové tepelně odolné součásti - kde plast již není vhodný.

Toto není hodnocení "lepší-horší". Jedná se o seznam možností s různou složitostí, cenou a riziky.

## PETG

PETG funguje pro mnoho součástí v zóně mírné teploty:

- kryty elektroniky;
- držáky ventilátorů;
- senzorové držáky teploty daleko od topného prvku;
- vzduchové kanály pro mírné proudění;
- prvky pouzdra, které nenáší kritickou bezpečnost.

Ale PETG se může změkčit a lézt pod zátěží. Pokud součást drží topný prvek, napájecí svorku nebo bezpečnostní senzor, musí být PETG použit velmi opatrně.

## ABS a ASA

ABS a ASA obvykle fungují lépe v teplejších zónách než PETG.

Jsou zvažovány pro:

- pouzdro komory;
- vzduchové kanály;
- držáky v teplém prostředí;
- technické součásti;
- součásti, které musí déle zachovat tvar.

Ale mají cenu:

- těžší tisk;
- zkroucení;
- zápach;
- potenciálně škodlivé páry;
- nejlépe tištěno v uzavřené komoře;
- vyžaduje větrání.

ASA je často upřednostňována pro součásti, kde záleží na odolnosti vůči UV a trvanlivosti. ABS může být levnější a více dostupné.

## PA / Nylon

PA nebo nylon se používá pro technické součásti se mechanickou zátěží.

Výhody:

- vysoká odolnost vůči nárazům;
- dobrá odolnost vůči opotřebení;
- nízké tření;
- dobrá mechanická houževnatost;
- některé varianty mají dobrou odolnost vůči teplotě.

Nevýhody:

- silně absorbuje vlhkost;
- vyžaduje sušení;
- může se zkroutit;
- obtížný tisk;
- vyžaduje správný povrch a podmínky.

Mokrý nylon se tiskne špatně: bublinky, syčení, špatný povrch a slabá síla. Pro jednoduchý kryt pouzdra je nylon obvykle zbytečný.

## PC / Polykarbonát

Polykarbonát je zvažován, když potřebujete vysokou pevnost a odolnost vůči teplotě.

Výhody:

- vysoká odolnost vůči nárazům;
- vysoká odolnost vůči teplotě;
- dobrá tuhost;
- vhodné pro funkční součásti.

Nevýhody:

- obtížný tisk;
- vysoká teplota trysky a podložky;
- náchylné na zkroucení;
- potřebuje stabilní teplé prostředí;
- ne každá tiskárna je vhodná.

PC není "začátečnický" materiál. Pokud je tisk nestabilní, součást se může zdát normální, ale mít slabou sílu mezi vrstvami.

## Kompozity

Kompozitní vlákna obsahují plnidla: uhlíkové vlákno, skleněné vlákno, Kevlar nebo jiný materiál.

Mohou poskytnout:

- větší tuhost;
- méně deformace;
- lepší rozměrová stabilita;
- hezký technický povrch.

Ale neučiní základní plast magicky nehořlavým nebo plně odolným vůči teplotě.

Důležité:

- uhlíkové plnidlo opotřebovává mosazné trysky;
- je potřeba kalená nebo vhodná tryska;
- kompozit může být křehčí;
- vlastnosti závisí na konkrétním materiálu, ne jen na písmenech `CF` v názvu.

## Když plast nefunguje

Pro některá místa není správný materiál tištěný plast.

Lepší je zvážit kov, skleněné vlákno, keramiku nebo hotové průmyslové součásti pro:

- držák topného prvku;
- přímá horká zóna;
- kontakt s napájecím svorkama;
- montáž síťového vodiče;
- mechanická bariéra mezi 110-230V AC a uživatelem;
- místo, kde by deformace součásti mohla vést k požáru nebo elektrickému šoku.

Tištěná součást může držet tvar pouzdra, ale neměla by být jedinou ochranou před nebezpečným selháním.

## Jak zvolit materiál

Před výběrem materiálu odpovězte:

1. Jaká je maximální teplota na místě instalace?
2. Jak dlouho bude součást pracovat na tuto teplotu?
3. Je tam mechanická zátěž?
4. Jsou tam šrouby, spoje nebo konstantní stlačení?
5. Je tam blízko topný prvek, SSR, MOSFET, napájecí zdroj nebo 110-230V AC?
6. Co se stane, pokud se součást deformuje?
7. Můžete nahradit plast kovem nebo hotovým držákem?

Pokud je důsledek selhání vážný, nechcete "nejpohodlnější plast", ale design s rezervou a nezávislou ochranou.

## Běžné chyby

- hledíte jen na teplotu tání;
- myšlení, že PETG je bezpečné vedle jakéhokoli topného prvku;
- použití PLA v uzavřené horké komoře;
- tisk PC/nylonu bez vhodné tiskárny a získání slabé součásti;
- výběr kompozitu jen pro cool značení `CF`;
- umístění plastové součásti přímo vedle napájecího svorkama;
- nekontrolování součásti po dlouhém ohřívání;
- zapomenutí na zátěž šroubu a tečení materiálu;
- nezapočítání toho, že se uzavřené pouzdro zcela ohřeje.

## Klíčové poznatky

- Pracovní teplota je důležitější než teplota tání.
- Součást se může stát nebezpečnou před viditelným táním.
- PETG je základní volba pro mírnou zónu, ne univerzální tepelná ochrana.
- ABS/ASA lépe snáší teplo, ale vyžadují tiskové podmínky a větrání.
- Nylon a PC jsou technické materiály pro zkušené uživatele a vhodné vybavení.
- V horkých a nosných místech je často lepší kov nebo hotový tepelně odolný držák.

## Reference

- [Prusa Knowledge Base: Material guide](https://help.prusa3d.com/category/material-guide_220) - comprehensive Prusa catalog of materials with PLA, PETG, ABS, ASA, PC, Nylon, and composites.
- [Prusa Knowledge Base: Polycarbonate](https://help.prusa3d.com/article/polycarbonate-pc_165812) - PC properties, high temperature resistance, and print difficulty.
- [Prusa Knowledge Base: Polyamide / Nylon](https://help.prusa3d.com/article/polyamide-nylon_167188) - nylon as a technical material, moisture absorption, drying, and print requirements.
- [Bambu Lab: 3D Printer Filament Comparison Guide](https://bambulab.com/en-us/filament-guide) - material comparison by heat resistance, strength, moisture absorption, and drying needs.
- [Prusa Knowledge Base: Enclosure guidepost](https://cdn.help.prusa3d.com/article/enclosure-guidepost_366332) - why a closed chamber is important for materials that warp during cooling.
