---
title: "Skříň sušičky filamentu a aktivní vyhřívaná komora"
description: "Jak navrhnout skříň sušičky filamentu nebo vyhřívanou komoru 3D tiskárny: izolace, proudění vzduchu, materiály, bezpečnost a údržba."
---

# Skříň sušičky filamentu a aktivní vyhřívaná komora

Skříň určuje, jak rovnoměrně zařízení drží teplotu, jak bezpečně jsou umístěny topení a elektronika a jak snadno se sušička servisuje. Stránka popisuje zásady návrhu pro sušičky filamentu, aktivní komory a podobné topné moduly.

Pouzdro zařízení není jen krabice kolem komponent.

Musí bezpečně obsahovat:

- topný prvek;
- ventilátor;
- sensors;
- power supply;
- ovladač;
- svorky;
- wires;
- connectors;
- display or buttons;
- mechanical parts.

Pro ohřívané zařízení může špatné pouzdro vytvořit problém i s dobrou elektronikou: blokování proudění vzduchu, přehřátí ovladače, otlačení vodiče nebo přiblížení plastu příliš blízko k horté součásti.

## Začněte s rozvržením komponent

Před modelováním pouzdra uspořádejte skutečné komponenty:

- controller board;
- power supply or DC-DC converter;
- ventilátor;
- topný prvek;
- teplotní senzor;
- svorky;
- pojistka;
- wires;
- connectors;
- buttons, display, RFID, or other modules.

Pouzdro je navrženo kolem skutečných rozměrů součástí, ne "přibližně takové velikosti".

Zkontrolujte:

- kde se nacházejí konektory;
- kde USB vychází;
- kde se stiskne tlačítko reset;
- jak se kryt sejme;
- jak se ventilátor vyměňuje;
- kde pojede napájecí vodič;
- jak bude deska namontována.

## Oddělené zóny

V ohřívaném zařízení je užitečné myslet na zóny:

- horká zóna;
- elektronická zóna;
- zóna napájecího vedení;
- uživatelská zóna;
- servisní zóna.

Horká zóna je topný prvek, horký proud vzduchu, teplotní senzor a sousední části.

Elektronická zóna je ovladač, displej, senzory nízkého napětí, logické vodiče.

Zóna napájecího vedení je napájecí zdroj, SSR, MOSFET, svorky, pojistky, vstup sítě, pokud je přítomen.

Uživatelská zóna je vše, co se dotýkají rukou: tlačítka, úchyty, kryty, displej, umístění čtečky RFID.

Tyto zóny by se neměly protínat náhodně.

## Neumisťujte elektroniku přímo vedle topného prvku

Ovladač, displej, DC-DC a vodiče se nerada přehřívají.

Ponechte:

- vzdálenost od topného prvku;
- vzduchová mezera;
- stínidlo nebo přepážka, pokud je potřeba;
- větrání elektroniky;
- přístup ke kontrole teploty po montáži.

Pokud elektronika sedí v uzavřené kapse bez ventilace, může se přehřát i bez přímého kontaktu s topným prvkem.

## Vzduch musí proudit tam, kde je potřeba

Sám ventilátor nezaručuje proudění vzduchu.

Pouzdro musí řídit vzduch:

- přes topný prvek;
- přes cívku nebo pracovní zónu;
- přes filtr, pokud je přítomen;
- kolem senzoru v správném bodě;
- ven nebo v smyčce podle návrhu.

Špatný návrh může mít za následek pěkný ventilátor a téměř nulový užitečný průtok. Vzduch bude následovat cestu nejmenšího odporu, přes mezery, kolem filtrů nebo kolem topného prvku.

Pro vzduchové kanály se vyhněte:

- ostrému zúžení;
- zbytečnému ohýbání;
- tenkým dlouhým kanálům;
- mřížkám s malou otevřenou plochou;
- filtrům bez ventilátoru s dostatečným statickým tlakem.

## Vytvořte montáže pro skutečné šrouby

Nespoléhejte se na to, že se samozařezávací šroub v tenké příspěvku vydrží věčně.

Pro pouzdro, které bude rozebíráno, je lepší použít:

- mosazné teplosádací vložky;
- matice v kapsách;
- správné podpěry desek;
- šrouby standardní velikosti;
- podložky, kde se plast může zatlouct.

U tištěných podpěr je důležité:

- adekvátní průměr;
- zaoblená základna;
- žádné tenké stěny;
- správná orientace tisku;
- vůle materiálu kolem otvoru.

Pokud se kryt bude otevírat často, nové plastové závity se rychle opotřebí.

## Vodiče se nesmějí otlačovat

Vodiče v pouzdru musí být zajištěny.

Potřebujete:

- kabelové kanály;
- místa pro vazby;
- ochrana proti tahu na vstupu kabelu;
- poloměry místo ostrých hran;
- vůle od ventilátoru;
- vůle od topného prvku;
- ochrana před sevřením krytem.

Špatný scénář: uživatel zatáhne vnější kabel a síla jde přímo na svorku nebo pin desky.

Lepší je, aby byl kabel nejdříve upevněn pouzdrem, pak dosáhne konektoru nebo svorky.

## Nemíchejte síť s nižším napětím

Pokud má zařízení 110-230V AC, musí být pouzdro navrženo mnohem přísněji.

Minimální logika:

- vstup sítě oddělený;
- pojistka přístupná, ale chráněná;
- síťové svorky pokryty;
- vodiče nízkého napětí nejsou smíchány se síťovými vodiči;
- uživatel se nemůže dotknout části sítě;
- vodič se nemůže vytáhnout ze svorky pod napětím;
- plast se nedotýká horkých svorek a součástí napájení;
- uzemnění je přítomno tam, kde je vyžadováno.

Neznámejte bezpečnost sítě "podle obrázku". Pro část sítě potřebujete správné svorky, izolaci, ochranu proti tahu, pojistky a porozumění požadavkům na bezpečnost.

## Nechte přístup na servis

Zařízení bude potřebovat údržbu.

Nechte přístup k:

- pojistka;
- svorky;
- ovladač;
- USB nebo servisní konektor;
- teplotní senzor;
- ventilátor;
- filtr;
- topný prvek;
- montážní šrouby.

Pokud výměna ventilátoru vyžaduje odpájení drátů nebo odstranění topného prvku, design nebude dobře opravován.

## Ověřte při skutečné teplotě

Po montáži potřebujete víc než jen kontrolu, že se vše vejde.

Ověřte:

- teplota elektroniky po dlouhodobém provozu;
- teplota stěny blízko topného prvku;
- měkne se plast;
- zkroutí se vzduchový kanál;
- zahřívají se svorky;
- změnily se mezery k horkým součástkám;
- voní plast;
- dotýkají se vodiče horkých povrchů.

První test je nejlépe provést pod dohledem s možností rychle vypnout napájení.

## Kontrolní seznam před tiskem pouzdra

Před tiskem zkontrolujte:

1. Všechny skutečné komponenty jsou měřeny.
2. Kolem desek, konektorů a kabelů je vůle.
3. Horká zóna je oddělena od elektroniky.
4. Proudění vzduchu má jasnou cestu.
5. Ventilátor lze vyměnit.
6. Filtr lze vyměnit.
7. Teplotní senzor lze zkontrolovat a přeinstalovat.
8. Vodiče neprochází přes ostré hrany.
9. Existují místa pro vazby nebo klipy.
10. Síťové vodiče jsou odděleny od nízkého napětí.
11. Kryt nevšívá kabely.
12. Šrouby a vložky mají kolem sebe dostatek plastu.
13. Materiál vyhovuje pracovní teplotě.
14. Deformace součásti neučiní zařízení nebezpečným.

## Běžné chyby

- nejdříve navrhněte hezkou krabici, pak se pokuste přizpůsobit vodiče;
- nezanechání místa pro konektory;
- blokování ventilace napájecího zdroje;
- umístění ovladače v horkém rohu;
- vedení síťových a signálních vodičů dohromady;
- neposkytnutí ochrany proti tahovému namáhání kabelu;
- použití tenkých podpěr pro šrouby;
- zapomenutí, že filtry a ventilátory potřebují údržbu;
- tisk pouzdra z PLA pro horkou zónu;
- neověření pouzdra po dlouhém ohřívání.

## Klíčové poznatky

- Pouzdro je navrženo kolem skutečných komponent a vodičů.
- Horká zóna, elektronika, napájecí vedení a uživatelská zóna musí být odděleny.
- Vzduch musí proudit po užitečné cestě, ne jen "někde foukat".
- Vodiče musí být zajištěny a chráněny před ostrými hranami, teplem a napětím.
- Síť nelze míchat s logikou nízkého napětí.
- Údržba musí být plánována před tiskem, ne po montáži.

## Reference

- [Protolabs Network: Enclosure design for 3D printing](https://www.hubs.com/knowledge-base/enclosure-design-3d-printing-step-step-guide/) - practical rules for walls, gaps, bosses, ribs, and brackets.
- [Prusa Knowledge Base: Enclosure guidepost](https://help.prusa3d.com/article/enclosure-guidepost_366332) - why enclosure affects temperature, dust, smell, access to hot parts, and power supply placement outside warm chamber.
- [FRC Design: Design for 3D Printing](https://www.frcdesign.org/design-handbook/structure/design-for-3d-printing/) - tips for electronics enclosures, port access, ventilation, and heat-set inserts.
- [3D On Demand: 3D printed enclosures guide](https://www.3d-demand.com/blog/3d-printed-enclosures-electronics-guide) - design around internal components, wall thickness, clips, and heat dissipation.
- [3DSearch: Custom electronics enclosures](https://www.3dsearch.app/blog/3d-printing-electronics-enclosures) - ventilation, board standoffs, threaded inserts, gaps, and practical dimensions for FDM.
