# Multimetr

Multimetr je hlavním diagnostickým nástrojem první linie.

Můžete to zkontrolovat:

- zda je přítomna síla;
- pokud je napětí správné;
- kde plus a mínus jsou;
- pokud je přerušený drát;
- pokud je pojistka neporušená;
- pokud se termistor jeví jako funkční;
- zda nedochází k poklesu napětí při zátěži.

Ale je snadné dělat chyby s multimetrem, pokud si pletete režimy. Mezi nejnebezpečnější chyby patří měření proudu a síťového napětí.

## Sondy a porty

Multimetr má obvykle:

- `COM` - společný port, kam téměř vždy vkládáte černou sondu;
- `V/Ohm/mA` nebo podobný port - pro napětí, odpor, spojitost a malé proudy;
- `A` nebo `A` - samostatný port pro velký proud.

Před měřením vždy zkontrolujte:

- do kterého portu je vložena červená sonda;
- jaký režim je zvolen;
- co přesně se chystáte měřit.

Velmi častá chyba: po změření proudu zapomenete přesunout sondu z `V/Ohm` zpět do `V/Ohm` a poté zkusíte změřit napětí. To může způsobit zkrat.

## Measuring DC voltage

DC je stejnosměrné (konstantní) napětí. V našich zařízeních je to obvykle:

- `3.3V`;
- `5V`;
- `12V`;
- `24V`.

Procedure:

1. Černá sonda do `COM`.
2. Červená sonda do portu `V`.
3. Zvolte režim stejnosměrného napětí: obvykle `V` s rovnou čárou.
4. Černá sonda na negativu nebo `GND`.
5. Red probe on positive.
6. Přečtěte si displej.

Pokud se před číslem na displeji objeví znaménko mínus, jsou sondy prohozeny. To je užitečné: tímto způsobem můžete určit polaritu.

![Digital multimeter with probes](../../img/05-tools/02-digital-multimeter.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Aneng_AN870_multimeter_02.jpg), Retired electrician, CC0 Public Domain*

## Kde měřit napětí

Neomezujte se na výstup napájecího zdroje.

Zkontrolujte:

- na napájecích svorkách;
- na vstupu desky;
- na zátěžových svorkách;
- on a DC-DC module;
- na ventilátoru;
- on a servo;
- on an LED strip.

Pokud napájecí zdroj ukazuje 24 V, ale zátěž ukazuje znatelně méně, hledejte průhyb na vodičích, svorkách nebo konektorech.

Pro diagnostiku napájecího zdroje je důležité měřit při zátěži, ne pouze v klidu.

## Measuring AC voltage

AC je střídavé napětí, např. 110-230V ze sítě.

Síťové napětí je nebezpečné.

Pokud nerozumíte tomu, co děláte, neměřte otevřené části sítě multimetrem. Je lepší používat hotové bezpečné moduly, přiložené terminály a odbornou pomoc.

Pokud měříte, potřebujete:

- multimetr s bezpečnostní kategorií **CAT II** nebo **CAT III** — toto je napsáno na těle přístroje vedle napětí, například `CAT II 600V`. CAT I není vhodný pro domácí sítě. CAT III a CAT IV poskytují extra rezervu pro složitější instalace;
- správně fungující sondy s kategorií ne nižší než multimetr;
- dry hands;
- uzavřená a stabilní sestava;
- pochopení toho, kde jsou fáze a neutrál;
- no accidental open contact points.

Pro většinu úloh týkajících se nízkonapěťové elektroniky postačují DC měření.

## Continuity check

Spojitost ukazuje, zda jsou dva body elektricky spojeny.

Je užitečné zkontrolovat:

- pokud je drát neporušený;
- pokud je připojen `GND`;
- pokud kabel není přerušený;
- pokud tlačítko funguje;
- pokud je pojistka neporušená;
- pokud jsou sousední kontakty zkratovány.

Procedure:

1. Turn off power.
2. Nastavte multimetr do režimu spojitosti: obvykle ikona zvuku nebo symbol diody.
3. Dotkněte se sond navzájem – mělo by se ozvat pípnutí.
4. Dotkněte se dvou bodů, které chcete zkontrolovat.
5. Pokud pípne, je mezi body vodivé spojení.

Kontrola kontinuity se provádí na obvodu bez napětí.

## Resistance

Odpor se měří v ohmech.

Pro naše úkoly je potřeba:

- check a thermistor;
- check for broken wire;
- check a fuse;
- určit, zda nedošlo ke zkratu;
- check a resistor.

Důležité: odpor se měří pouze na beznapěťovém obvodu.

Pokud měříte odpor na desce pod napětím, můžete získat nesprávné údaje nebo poškodit multimetr.

## Testing a thermistor

U typického NTC `100 kOhm` při pokojové teplotě počítejte s desítkami nebo kolem `100 kOhm`.

Pokud multimetr ukazuje:

- `OL` or infinity - likely open circuit;
- almost `0 Ohm` - likely short circuit;
- hodnota hodně kolísá při pohybu drátu - špatný kontakt;
- odpor klesá při zahřátí prsty - vypadá jako živé NTC.

Přesné hodnoty závisí na typu termistoru a teplotě.

## Measuring current

Měření proudu je nebezpečnější než měření napětí.

Napětí se měří paralelně: sondy se dotýkají dvou bodů.

Proud se měří v sérii: musíte přerušit obvod a zapojit multimetr do řady, aby proud procházel zařízením.

Chyba - uveďte multimetr do aktuálního režimu a dotkněte se sond na plus a mínus napájení. To je téměř zkrat přes multimetr.

Pro začátečníka je lepší:

- nejprve vypočítat proud z výkonu;
- použijte hotové wattmetry/USB elektroměr/DC elektroměr;
- měřte proud pouze v případě, že rozumíte tomu, jak zapojit multimetr do série;
- začněte se správným rozsahem a správným portem.

## Checking a fuse

Zkontrolujte pojistku v obvodu bez napětí.

Methods:

- continuity;
- resistance measurement.

Dobrá pojistka obvykle vykazuje spojitost a má velmi nízký odpor.

Spálená pojistka obvykle nevykazuje spojitost.

Pokud se spálila pojistka, nemůžete jen nainstalovat pojistku vyšší třídy. Nejprve najděte příčinu.

## Jak nespálit multimetr

Minimum rules:

- před měřením zkontrolujte režim;
- před měřením zkontrolujte červený port sondy;
- neměřte odpor v obvodu pod napětím;
- don't measure current like voltage;
- nechoďte do 110-230V AC bez pochopení bezpečnosti;
- začněte s vyšším rozsahem, pokud multimetr není automatický;
- používat funkční sondy;
- nedotýkejte se prsty kovových hrotů.

## Practical scenarios

Zkontrolujte 24V napájecí zdroj:

1. DC voltage mode.
2. Černá sonda na negativu.
3. Red probe on positive.
4. Mělo by číst o 24V.

Zkontrolujte ventilátor:

1. Změřte napětí na konektoru ventilátoru.
2. Zkontrolujte polaritu.
3. Zkontrolujte napětí při startu.

Zkontrolujte přerušený vodič:

1. Disconnect power.
2. Continuity mode.
3. Sondy na obou koncích drátu.
4. No beep - possible open circuit.

Zkontrolujte zkrat mezi `GND` a `GND`:

1. Disconnect power.
2. Zkontrolujte kontinuitu mezi `GND` a `GND`.
3. Pokud pípá tam, kde nemá, hledejte zkrat.

## To podstatné

- Pro stejnosměrné napětí použijte režim `V` s přímkou.
- Odpor a kontinuita se provádí pouze na obvodech bez napětí.
- Proud se měří v sérii, ne paralelně.
- Po změření proudu přesuňte sondu z `V/Ohm` zpět do normálního portu `V/Ohm`.
- Síťové napětí je nebezpečné; neměřte otevřené části 110-230V bez pochopení bezpečnosti.
- Multimetr pod zatížením často odhalí problémy, které nejsou viditelné při nečinnosti.

## Reference materials

- [SparkFun: How to Use a Multimeter](https://learn.sparkfun.com/tutorials/how-to-use-a-multimeter/all) - practical guide to voltage, current, resistance, continuity and multimeter ports.
- [Fluke: How to Measure Resistance](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-resistance) - safe resistance measurement.
- [Fluke: How to Measure AC Voltage](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-ac-voltage) - measuring AC voltage and probe connection order.
- [Fluke: How to Test for Continuity](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-test-for-continuity) - continuity check and open-circuit search.
- [Fluke: Choosing the correct fuse for your tester](https://www.fluke.com/en-us/learn/blog/digital-multimeters/choosing-the-correct-fuse-for-your-tester) - why current input ports need proper fuses with correct voltage and interrupt rating.
