# Proud, napětí a výkon zátěže

Před připojením topidla, ventilátoru, LED pásu, servopohonu nebo jiného modulu musíte pochopit tři věci:

- napětí;
- proud;
- výkon.

Bez toho je snadné koupit nesprávný zdroj napětí, přehřát drát, rozpustit konektor, spálit modul MOSFET nebo připojit zátěž k řídícímu prvku tak, aby fungoval nestabilně.

## Kde najít parametry

Napětí, proud a výkon se obvykle nacházejí:

- na pouzdru součástky;
- na štítku zdroje napětí;
- na stránce produktu;
- v technické specifikaci;
- v manuálu;
- ve schématu desky nebo pinoutu.

Pokud parametr není uveden, není to malý problém. Je to důvod pro zastavení a zjištění, co přesně připojujete.

Pro součástky z periferie 3D tiskárny vypadají typické parametry takto:

- ventilátor: `24V 0.2A`;
- topidlo: `24V 100W`;
- LED pás: `24V 9.6W/m`;
- servopohon: `5V`, proud závisí na zátěži;
- řídící deska: maximální proud pro každý výstup je uveden zvlášť.

## Napětí se musí shodovat

Zátěž je navržena pro specifické napětí.

Příklady:

- ventilátor může být `5V`, `12V` nebo `24V`;
- LED pás může být `5V`, `12V` nebo `24V`;
- servopohon je často hodnocen na `5V` nebo `6V`;
- topidlo může být `12V`, `24V` nebo `110-230V AC`.

Pokud připojíte `24V` ventilátor na `12V`, nemusí se spustit nebo bude pracovat slabě. Pokud připojíte `12V` ventilátor na `24V`, může rychle selhat.

Hlavní pravidlo:

**napětí zdroje napětí se musí shodovat s napětím zátěže.**

Nepřipojujte zařízení k vyššímu napětí jen proto, že konektor pasuje fyzicky.

## Výkon ukazuje velikost zátěže

Výkon ukazuje, kolik energie zátěž spotřebuje nebo převede na práci, teplo, světlo nebo pohyb.

Výkon se měří ve wattech: `W`.

Příklady:

- `24V 5W` - malá zátěž;
- `24V 24W` - přibližně `1A`;
- `24V 120W` - už přibližně `5A`;
- `24V 240W` - přibližně `10A`.

Topidla obvykle spotřebují hodně energie. Ventilátory spotřebují méně, ale mohou mít vysoký startovní proud. LED pásy mohou být malá zátěž, pokud jsou krátké, nebo vážná zátěž, pokud jsou dlouhé a jasné.

## Proud zatěžuje vodiče a prvky výkonu

Proud ukazuje, kolik elektrické energie protéká vodiči, svorkami, konektory a prvky výkonu.

Proud často vytváří praktické problémy:

- vodiče se zahřívají;
- svorky ztmavnou;
- konektory se roztaví;
- MOSFET se přehřeje;
- zdroj napětí není dostatečný;
- zařízení se restartuje, když se zátěž zapne;
- pojistka se spálí, ne náhodou, ale kvůli skutečnému přetížení nebo chybě.

Proto není dost znát pouze napětí. Musíte vypočítat proud.

## Vzorec pro výpočet

Pro většinu jednoduchých výpočtů potřebujete vzorec pro výkon:

```text
P = U * I
```

Kde:

- `P` - výkon ve wattech `W`;
- `U` - napětí ve voltech `V`;
- `I` - proud v ampérech `A`.

K zjištění proudu:

```text
I = P / U
```

![Ohmův zákon: obvod se zdrojem napětí, proudem a odporem](../../img/01-electronics-basics/01-ohms-law-circuit.svg)

*Zdroj: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Ohm%27s_Law_with_Voltage_source_TeX.svg), GorillaWarfare, CC0 Public Domain*

Tento vzorec není pro zkoušku. Je potřebný k pochopení, zda to zdroj napětí, drát, svorka, modul MOSFET, relé, SSR nebo výstup desky zvládne.

## Rychlá tabulka pro 24V

V 3D tiskárnách a periférii je `24V` běžné. Pro rychlý odhad je užitečné si pamatovat:

| Výkon | Proud na 24V |
|---:|---:|
| `12W` | `0.5A` |
| `24W` | `1A` |
| `48W` | `2A` |
| `96W` | `4A` |
| `120W` | `5A` |
| `240W` | `10A` |
| `300W` | `12.5A` |

Jedná se o přibližné hodnoty, ale pro první volbu zdroje napětí, drátu a výkonového spínače jsou velmi užitečné.

## Příklad: topidlo 24V 100W

Máte topidlo:

```text
24V 100W
```

Vypočítejte proud:

```text
I = 100W / 24V = 4.17A
```

To znamená, že následující musí vydržet více než `4.17A`:

- zdroj napětí;
- drát;
- svorky;
- konektor;
- MOSFET nebo SSR;
- pojistka a pouzdro pojistky;
- cesty na desce, pokud je topidlo připojeno k desce.

Pokud je zdroj napětí hodnocen na `24V 5A`, formálně se přibližuje k zátěži, ale téměř bez rezervy. Pro skutečné zařízení je lépe koupit větší.

## Příklad: více zátěží

Předpokládejme, že `24V` zařízení má:

- topidlo `100W`;
- ventilátor `24V 0.2A`;
- LED pás `24V 1A`;
- další ventilátor `24V 0.15A`.

Vypočítejte topidlo:

```text
100W / 24V = 4.17A
```

Sečtěte je:

```text
4.17A + 0.2A + 1A + 0.15A = 5.52A
```

Minimální zdroj napětí "těsné"] by byl kolem `24V 6A`, ale to je špatná volba pro dlouhodobý provoz. S `50%` rezervou:

```text
5.52A * 1.5 = 8.28A
```

Prakticky byste měli hledat `24V 9A`, `24V 10A` nebo větší zdroj napětí, pokud to umožňuje pouzdro, chlazení a bezpečnost.

## Rezerva je povinná

Zdroj napětí, vedení, svorky a výkonové moduly nelze vybrat přesně podle vypočteného proudu.

Pro tento průvodce je jednoduché pravidlo pro hrubý první odhad:

**plánujte alespoň 50% rezervu**, pokud dokumentace konkrétní součástky nevyžaduje více. Toto není univerzální záruka, ale počáteční odhad. Finální výběr je proveden podle technických specifikací, teploty uvnitř pouzdra, chlazení, deratingu a skutečného topení svorek/vodičů.

Rezerva je potřebná, protože:

- zdroj napětí se zahřívá;
- teplota uvnitř pouzdra může být vyšší než pokojová teplota;
- ventilátory a motory mají startovní proud;
- kontakty stárnou a uvolňují se;
- svorky mají omezení proudu a teploty;
- SSR a MOSFET generují teplo;
- zdroj napětí může mít deration - snížení maximálního výkonu při vysoké teplotě nebo špatné ventilaci.

Průmyslové zdroje napětí mají v technické specifikaci často deratovací křivku — křivku sníženého maximálního výkonu při zvýšení teploty. Deration znamená, že při vysoké teplotě nebo špatné ventilaci výrobce snižuje maximální přípustný výkon. Proto štítek `240W` na zdroji napětí vždy neznamená, že bude bezpečně dodávat `240W` v uzavřeném horkém pouzdru.

## Slabé místo nemusí být zdroj napětí

I když je zdroj napětí výkonný, obvod může být slabý jinde.

Musíte zkontrolovat celý obvod:

- výstup zdroje napětí;
- drát;
- svazkový blok;
- konektor;
- pojistka;
- modul MOSFET;
- relé nebo SSR;
- cesty na desce;
- samotná zátěž.

Například zdroj napětí může vydržet `10A`, ale malý konektor nebo špatná šroubová svorka se mohou zahřát již při nižším proudu. To je obzvláště důležité pro topidla a LED pásy.

## Co je výkonový spínač

Výkonový spínač je řízený spínač.

Řídící prvek nepřipojuje těžkou zátěž přímo. Dává slabý řídicí signál a výkonový spínač zapíná nebo vypíná proud zátěže.

Příklady:

- modul MOSFET pro `12V`/`24V` stejnosměrné zátěže;
- relé;
- SSR;
- hotový ovladač zátěže;
- standardní výstup výkonu desky, pokud je hodnocen pro potřebnou zátěž.

Pro topidla, ventilátory, LED pásy a motory se pravidlo téměř vždy použije:

**GPIO řídícího prvku nepřipojuje zátěž. GPIO pouze řídí.**

## Trochu o Ohmově zákonu

Ohmův zákon souvisí s napětím, proudem a odporem:

```text
U = I * R
```

Pro tento článek je důležitá jednoduchá myšlenka: pokud aplikujete napětí na zátěž, proud přes ni bude procházet. Kolik proudu prochází, závisí na samotné zátěži.

Ale ne všechny zátěže se chovají stejně:

- topidlo je blízko odporové zátěži;
- ventilátor a motor mají startovní proud;
- servopohon prudce zvýší proud, když je zablokován;
- LED pás spotřebuje proud podle délky a jasnosti;
- elektronický modul může mít přechodný proud při zapnutí.

Proto je pro skutečné zařízení lépe brát data z technických specifikací nebo měřit proud multimetrem / laboratorním zdrojem napětí, pokud je to bezpečné.

## Co zkontrolovat před připojením

Před připojením zátěže odpovězte:

1. Na jaké napětí je zátěž hodnocena?
2. Je to stejnosměrná nebo střídavá zátěž?
3. Jaký výkon nebo proud je uveden?
4. Jaký proud dostanete ze vzorce `I = P / U`?
5. Jaké další zátěže jsou na stejném zdroji napětí?
6. Je zde alespoň `50%` rezerva?
7. Vydržují to vodiče, svorky, konektory a deska?
8. Co bude ovládat zátěž: MOSFET, relé, SSR nebo standardní výstup?
9. Je potřebná pojistka?
10. Co se stane, pokud dojde ke zkratu, zaseknutí motoru nebo selhání ventilátoru?

Pokud se jedná o topidlo nebo síťové napětí `110-230V AC`, jsou bezpečnostní požadavky vyšší. Síťová část nemůže být sestavena hádam: potřebujete vhodné pouzdro, pojistku, izolaci, ochranné uzemňování `PE`, nárazník pro vodiče a ověření kvalifikovanou osobou.

## Hlavní bod

- Napětí zdroje napětí se musí shodovat s napětím zátěže.
- Výkon ukazuje velikost zátěže.
- Proud ukazuje zatížení vodičů, svorek, konektorů a prvků výkonu.
- Základní vzorec: `I = P / U`.
- V systému `24V` je `24W` přibližně `1A`, `120W` je přibližně `5A`, `240W` je přibližně `10A`.
- Proudy všech zátěží na jednom zdroji napětí se sčítají.
- Pro hrubý první odhad potřebujete alespoň `50%` rezervu; přesný výběr se provádí podle technických specifikací, teploty, chlazení a deratingu.
- Slabé místo nemusí být zdroj napětí, ale svorka, konektor, drát, MOSFET nebo cesta na desce.
- GPIO řídícího prvku nepřipojuje těžkou zátěž, pouze řídí výkonový spínač.

## Referenční materiály

- [SparkFun: Voltage, Current, Resistance, and Ohm's Law](https://learn.sparkfun.com/tutorials/voltage-current-resistance-and-ohms-law) - jasné základní vysvětlení napětí, proudu, odporu a Ohmova zákona.
- [DigiKey: Ohm's Law Calculator](https://www.digikey.com/en/resources/conversion-calculators/conversion-calculator-ohms) - kalkulačka pro výpočet vztahu mezi napětím, proudem, odporem a výkonem.
- [Mean Well: How to read a derating curve](https://meanwellpowersupplies.com/technical-articles/faq/how-to-read-a-derating-curve/) - proč maximální výkon zdroje napětí závisí na teplotě, ventilaci a vstupním napětí.
- [DigiKey: Selecting and Applying AC/DC Power Supplies](https://www.digikey.com/en/articles/selecting-and-applying-ac-dc-power-supplies) - výběr zdroje napětí s ohledem na teplotu, deration, kabely a typ zátěže.
- [Weidmuller: Derating curve / current-carrying capacity](https://www.weidmuller.com/en/products/connectivity/pcb_terminals_and_connectors/derating_curve.jsp) - proč maximální proud svorek a konektorů závisí na teplotě a designu.
