# Osciloskop

Osciloskop ukazuje, jak se signál mění v čase.

Multimetr může ukázat "asi 3.3V" nebo "je tam frekvence". Osciloskop ukazuje tvar signálu: pulsy, hrany, pokles, šum, odskok, pakety UART, PWM.

![Obrazovka digitálního osciloskopu](../../img/05-tools/07-digital-oscilloscope.jpg)

*Zdroj: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Digital_oscilloscope.jpg), premek.v, Public Domain*

Signál PWM na obrazovce osciloskopu vypadá takto:

![Animace PWM: změna duty cycle a průběh signálu](../../img/05-tools/07-pwm-signal-waveform.gif)

*Zdroj: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Pwm.gif), Mik81, CC0 Public Domain*

Nepotřebujete jej na každou jednoduchou stavbu. Ale když se zařízení chová nestabilně, osciloskop může v minutách odhalit, co multimetr nemůže vidět.

## Co můžete vidět

V zařízeních podobných iDryer-u je osciloskop užitečný pro prohlížení:

- PWM ventilátoru;
- PWM modulu MOSFET;
- UART `TX/RX`;
- pokles 5V nebo 3.3V při spuštění servomotoru;
- šum napájecího zdroje;
- odskok tlačítka;
- signál tachometru ventilátoru;
- krátké poruchy, které multimetr zprůměruje.

Osciloskop odpovídá nejen "je tam napětí", ale "co se děje se signálem v čase".

## Nejdůležitější varování

Většina stolních osciloskapů má zem sondy připojenou k ochrannému uzemnění sítě.

To znamená: clips zeme sondy není "jen další drát".

Pokud připojíte clips zeme sondy k bodu, který není `GND` nízkovoltážního obvodu, můžete vytvořit zkrat skrz osciloskop.

Je zvláště nebezpečné vstoupit do síťové části 110-230V AC, SSR, napájecího zdroje nebo vysokonapěťových sekcí s normálním osciloskapem.

Nemůžete:

- odpojit zem osciloskopu pro "plovoucí" měření;
- připojit clips zeme sondy k fázi nebo jinému napěťovému bodu;
- měřit síťové napětí s normální sondou bez pochopení obvodu;
- předpokládat, že dva kanály jsou zcela nezávislé: země kanálů jsou často propojeny.

Pro plovoucí měření, měření vysoké strany a měření vysokého napětí potřebujete správné metody: diferenciální sondu, izolované zařízení nebo jiný bezpečný přístup.

## Jak připojit sondu

Pro nízkovoltážní obvody:

1. Připojte sondu k osciloskopu.
2. Připojte zem sondy k `GND` zařízení.
3. Připojte špičku sondy k signálu.
4. Vyberte správné nastavení sondy: `1x` nebo `10x`.
5. Ujistěte se, že je osciloskop nastaven na stejný faktor.

Pro většinu digitálních signálů použijte `10x`: sonda méně zatěžuje obvod a obvykle lépe zobrazuje tvar signálu.

## PWM

PWM je pulzní signál.

Osciloskop ukazuje:

- frekvenci;
- duty cycle;
- úroveň logické jedničky;
- úroveň logické nuly;
- hrany;
- jitter;
- šum.

Pro ventilátor nebo MOSFET to pomáhá pochopit:

- zda výstup pinu vůbec signál vysílá;
- zda je úroveň 3.3V nebo 5V dostatečná;
- zda frekvence odpovídá nastavení;
- zda se duty cycle mění podle příkazu;
- zda signál nepadá, když je připojena zátěž.

## UART

UART na osciloskopu vypadá jako sekvence pulsů.

Osciloskop pomáhá vidět:

- zda je aktivita na `TX`;
- zda nejsou prohozeny logické úrovně;
- jaká je úroveň v klidu;
- zda je silný šum;
- zda se přibližně shoduje přenosová rychlost.

Pro dekódování textu je vhodněji logický analyzátor nebo USB-UART adaptér. Ale osciloskop rychle ukáže, zda je signál fyzicky živý.

## Pokles napájecího zdroje

Multimetr nemusí vidět krátký pokles.

Například když se servomotor spustí, linea 5V se může ponížit o několik milisekund. Multimetr ukazuje téměř normálních 5V, ale kontrolér se již restartoval.

Osciloskop vám umožňuje vidět:

- kolik napětí padá;
- jak dlouho pokles trvá;
- zda jsou špičky;
- zda kondenzátor pomáhá;
- zda se situace změní s jiným napájecím zdrojem nebo vodiči.

To je zvláště užitečné pro ESP32, servomotory, ventilátory a DC-DC.

## Šum a interference

Šum na napájecích nebo signálních vodičích může prolomit senzory a komunikaci.

Osciloskop pomáhá vidět:

- zvlnění DC-DC;
- motorové špičky;
- šum blízko topidla;
- odskok tlačítka;
- interference na dlouhém vodiči.

Ale rozumějte omezením: špatné připojení zeme sondy může přidat šum na samotný displej. Krátká pružina zeme sondy nebo krátký vodič zeme často dávají poctivější obraz než dlouhý clips.

## Multimetr s měřením frekvence

Někdy osciloskop není na počáteční kontroly potřebný.

Některé multimetry mohou měřit frekvenci signálu. Ve specifikacích se to mohou nazývat `Hz`, `frekvence` nebo `čítač frekvence`.

To je užitečné, pokud potřebujete rychle pochopit:

- zda existuje PWM signál vůbec;
- zda se frekvence mění s úpravou;
- zda výstup kontroléru funguje;
- zda je aktivita na jednoduchém digitálním vodiči.

Například pokud by kontrolér měl výstup PWM ventilátoru nebo modulu MOSFET, multimetr měřící frekvenci může ukázat, že signál existuje a jeho frekvence se přibližně shoduje s očekávanou hodnotou.

Ale multimetr neukazuje tvar signálu. Neukazuje:

- úroveň logické jedničky;
- šířka pulsu;
- duty cycle PWM;
- hrany signálu;
- krátké poklesy;
- šum a interference;
- zkreslení vedení.

Takže multimetr měřící frekvenci je dobrý nástroj pro rychlé kontroly, ale není úplnou náhradou za osciloskop.

## Co kontrolovat před měřením

Před připojením sondy:

1. Co je `GND` v obvodu?
2. Je tento bod připojen k ochrannému uzemnění sítě?
3. Není tam síťové napětí?
4. Je sonda hodnocena na napětí?
5. Je vybrán `10x`, pokud je to potřeba?
6. Jsou sonda a kanál nastaveny stejně?
7. Nejsou země kanálů připojeny k různým bodům obvodu?
8. Můžete nejdřív zkontrolovat signál na straně nízkého napětí?

Pokud máte pochyby o 110-230V AC, nepřipojujte osciloskop.

## Běžné chyby

- clips zeme připojen k napěťovému bodu, ne `GND`;
- pokus "odpojit" zem osciloskopu od sítě;
- měření síťového napětí s normální sondou bez diferenciálu;
- zapomenutí, že země kanálů jsou připojeny;
- sonda nastavena na `10x`, osciloskop nastaven na `1x`;
- použití dlouhé zeme sondy a vidění extra šumu;
- pouze pohled s multimetrem a chybění krátkého poklesu;
- myšlení, že problém UART je softwarový, když na vodiči není fyzický signál.

## Podstata

- Osciloskop ukazuje tvar signálu v čase.
- Je užitečný pro PWM, UART, pokles napájecího zdroje, šum a krátké poruchy.
- Běžná stolní zem osciloskopu je připojena k ochrannému uzemnění sítě.
- Nemůžete připojit zem sondy k libovolnému bodu obvodu.
- Pro síťová a plovoucí měření jsou potřeba speciální bezpečné metody.
- Multimetr měřící frekvenci je užitečný, ale není úplnou náhradou za osciloskop.

## Referenční materiály

- [SparkFun: Jak používat osciloskop](https://learn.sparkfun.com/tutorials/how-to-use-an-oscilloscope/introduction) - základní praktický úvod do osciloskapů, signálů a ovládačů.
- [Tektronix: Jak používat osciloskop](https://www.tek.com.cn/documents/primer/how-to-use-an-oscilloscope) - uzemňování, nastavení, ovládání a základní použití osciloskopu.
- [Tektronix: Abeceda sond Primer](https://www.tek.com/en/documents/whitepaper/abcs-probes-primer) - varování o zemi sondy, síťové zemi a nebezpečí plovoucích měření s normálním osciloskapem.
- [Tektronix: Plovoucí měření osciloskopu a ochrana operátora](https://www.tek.com/en/documents/technical-brief/floating-oscilloscope-measurements-and-operator-protection) - proč je odpojení sítě osciloskopu nebezpečné a jaké bezpečné alternativy existují.
- [Keysight: Plavání osciloskopu](https://docs.keysight.com/kkbopen/how-can-i-float-an-infiniium-or-infiniivision-x-oscilloscope-isolating-it-from-mains-power-607258715.html) - Keysight nedoporučuje obcházení uzemňování a naznačuje diferenciální sondy.
