# Modul MOSFET

Modul MOSFET je hotová malá deska, která funguje jako řízený výkonový spínač pro stejnosměrné zátěže. Řídící prvek poskytuje slabý řídicí signál a modul MOSFET zapíná nebo vypíná proud ze zdroje napětí k zátěži.

V zařízeních podobných iDryer a v periférii 3D tiskárny se modul MOSFET používá pro ventilátory, LED pásy, nízkovoltážní topidla a další zátěže `12V`/`24V`, když je standardní výstup desky slabý, obsazený nebo nepohodlný.

## MOSFET a modul MOSFET

MOSFET je tranzistor s efektem pole. Má tři hlavní vývody:

- `Gate` - řídicí vstup;
- `Drain` - výstup výkonu;
- `Source` - výstup výkonu.

Brána nepřipojuje zátěž. Pouze řídí. Hlavní proud zátěže protéká výkonnou částí MOSFET mezi `Drain` a `Source`.

Modul MOSFET není jen jeden tranzistor. Obvykle je to deska s MOSFET, svorkami, řídicím vstupem a někdy s dalšími rezistory, indikátory, chladičem nebo ochrannou diodou.

Deska je vhodná pro prototyp, ale její specifikace musí být kontrolovány stejně pečlivě jako jakýkoli výkonový uzel.

## Proč je to potřebné

GPIO řídícího prvku by neměl napájet těžkou zátěž.

GPIO může ovládat:

- vstup modulu MOSFET;
- vstup relé;
- vstup SSR;
- vstup ovladače.

Ale GPIO by neměl přímo napájet:

- ventilátor;
- LED pás;
- topidlo;
- motor;
- solenoid;
- servopohon.

Pokud připojíte zátěž přímo k GPIO, můžete poškodit řídící prvek, dostat restarty, přehřát stopy nebo jen dostat nestabilní provoz.

## Spínání na nižší straně

Nejběžnějším variantem pro modul N-kanálového MOSFET je spínání na nižší straně, to znamená spínání přes zápornou linku.

![N-kanálový MOSFET v režimu spínání na nižší straně](../../img/01-electronics-basics/02-nmos-switch-operation.png)

*Zdroj: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:NMOS_PWR_WHOLE.PNG), KjellElec, CC BY-SA 4.0*

Typická logika:

1. `+24V` ze zdroje napětí jde přímo na kladný pól zátěže.
2. Záporný pól zátěže jde na výstup výkonu modulu MOSFET.
3. Modul MOSFET připojuje nebo přerušuje cestu od záporného pólu zátěže k `GND`.
4. `GND` zdroje napětí a `GND` řídícího prvku jsou spojeny dohromady.
5. Kontrolní pin řídícího prvku jde na `Signal`, `IN`, `Gate` nebo podobný vstup modulu.

Společný `GND` / společný záporný pól je povinný. Bez něj řídící prvek a modul MOSFET nemají společnou referenční úroveň pro řídicí signál.

Spínání na nižší straně má omezení: MOSFET přerušuje záporný pól zátěže. Pokud je spínač vypnutý, záporný pól zátěže není roven společnému `GND`. Pro jednoduchý 2-pinový ventilátor, pás nebo topidlo je to obvykle v pořádku. Pro zátěž s tachometrem, samostatným signálním drátem, senzorem uvnitř nebo dalším připojením k další desce musíte zkontrolovat schéma: někdy je lépe ovládat standardní vstup nebo použít jinou metodu spínání.

## Kde se používá

Modul MOSFET je vhodný pro stejnosměrné zátěže, pokud je hodnocen na jejich napětí a proud:

- `12V`/`24V` ventilátor;
- jednobarevný LED pás;
- kanál standardního RGB pásu;
- `12V`/`24V` topidlo;
- malý stejnosměrný motor, pokud je chráněn před skokům;
- solenoid, pokud je tu zpětná dioda nebo jiná ochrana.

Pro adresovatelný LED pás obvykle MOSFET neřídí data. Může odpojit napájení na celý pás, ale jednotlivé LED jsou ovládány přes datový vodič.

Pro servopohon obvykle není potřebný modul MOSFET k řízení polohy: servo potřebuje samostatný řídicí PWM signál a normální napájení.

## Co kontrolovat při výběru

Před nákupem nebo připojením zkontrolujte:

- hodnocení napětí zátěže;
- maximální hodnocení proudu;
- skutečný proud vaší zátěže;
- funguje vstup od `3.3V`;
- je `Rds(on)` v technické specifikaci na potřebném napětí brány;
- potřebuje aktivní logiku `HIGH` nebo `LOW`;
- je tam společný `GND`;
- je tam zpětná dioda pro motory/solenoidy;
- velikost svorek a maximální proud svorek;
- tloušťka cesty desky a chlazení;
- je potřeba chladič;
- je tam schéma, technická specifikace nebo normální dokumentace.

Pokud popis říká jen "MOSFET modul pro Arduino" bez napětí, proudu, schématu a typu MOSFET, nemůžete zvolit takový modul pro topidlo nebo dlouhý LED pás.

## 3.3V a MOSFET na úrovni logiky

Mnoho moderních řídících prvků pracuje s logikou `3.3V`: ESP32, RP2040, mnoho STM32.

Ne všechny MOSFET se plně otevírají od `3.3V`. Pokud se plně neotevřou, jejich odpor zůstane vysoký a přehřívají se.

Důležité termíny:

- `Vgs(th)` - prahová hodnota, kde se MOSFET začíná otevírat;
- `Rds(on)` - odpor otevřeného kanálu;
- MOSFET na úrovni logiky - MOSFET hodnocený pro řízení z logických úrovní.

Běžná chyba: vidět v technické specifikaci `Vgs(th) = 2V` a rozhodnout, že MOSFET funguje dobře od `3.3V`. To není pravda. `Vgs(th)` neznamená "plně otevřeno". Musíte zkontrolovat `Rds(on)` na `2.5V`, `3.3V`, `4.5V` nebo `5V`, v závislosti na řídícím prvku.

Pro ESP32/RP2040 je lépe zvolit modul, který výslovně uvádí kompatibilitu s řízením `3.3V`, nebo kde to poskytuje vstupní obvod. Pokud tabulka obsahuje `Rds(on)` pouze na `10V` a není data na `2.5V`/`3.3V`/`4.5V`, je takový modul podezřelý pro řídící prvek `3.3V`.

## Proud a ohřev

MOSFET v otevřeném stavu má stále odpor. Na něm se generuje teplo.

Čím větší proud, tím důležitější:

- nízké `Rds(on)`;
- normální měděná plocha na desce;
- vhodně dimenzované svorky;
- chladič, je-li potřeba;
- ventilace pouzdra;
- rezerva proudu;
- kontrola teploty po skutečném provozu.

Značka "100A MOSFET" na pouzdru tranzistoru neznamená, že malý modul s tenkými stopami a levnými svorkami bude vydržet `100A`. Skutečný limit je často deska, svázkový blok, drát, svařovací spoj a chlazení.

Pokud se modul MOSFET tak zahřívá, že je těžké ho držet v ruce, je to důvod zastavit se a přepočítat proud, chlazení a kvalitu připojení.

## Motory, ventilátory a solenoidy

Induktivní zátěže mohou vytvářet přepěťové špičky, když se vypnou.

Takové zátěže zahrnují:

- stejnosměrné motory;
- ventilátory;
- solenoidy;
- relé;
- elektromagnety.

Často potřebují ochranu:

- zpětná dioda;
- TVS dioda;
- hotový ovladač s ochranou;
- modul, kde je ochrana již nainstalována.

Pokud je modul hodnocen pouze pro LED pás nebo odporovou zátěž, nemůžete automaticky předpokládat, že je bezpečný pro motor nebo solenoid.

Pro topidlo obvykle není potřebná zpětná dioda, protože topidlo je blízko odporové zátěži. Ale pro topidlo je důležitější proud, svorky, pojistka a nezávislá tepelná ochrana.

## Řízení PWM

Modul MOSFET lze použít nejen pro zapnutí/vypnutí, ale také pro regulaci výkonu PWM.

Typické příklady:

- jas LED pásu;
- rychlost jednoduchého stejnosměrného ventilátoru;
- výkon nízkovoltážního topidla.

Ale PWM není vždy stejný:

- 4-pinový PWM ventilátor je lépe ovládán samostatným PWM pinem ventilátoru, ne řezáním výkonu;
- topidlo obvykle nevyžaduje vysokou frekvenci PWM;
- příliš vysoká frekvence může zvýšit ohřev MOSFET;
- příliš nízká frekvence může způsobit blikání LED nebo šum motoru.

Volba frekvence závisí na zátěži, modulu a firmwaru.

## Modul MOSFET není pro 110-230V AC

Standardní moduly MOSFET pro Arduino/ESP32 jsou navrženy pro stejnosměrné zátěže: `5V`, `12V`, `24V`, někdy více, pokud je výslovně uvedeno.

Nelze je použít jako spínač pro síťové napětí `110-230V AC`.

Pro síťovou zátěž potřebujete jiná řešení:

- relé nebo SSR speciálně hodnocené pro AC zátěž;
- normální svorky;
- pojistka;
- pouzdro;
- izolace;
- uzemňování, kde je vyžadováno;
- pochopení elektrické bezpečnosti.

Pokud si nejste jisti, že je modul určen pro síťové napětí, nepřipojujte jej k síti.

## Co kontrolovat po připojení

Před dlouhodobým provozem zkontrolujte:

- zátěž má správné napětí;
- řídící prvek a zdroj napětí mají společný `GND`;
- řídicí signál skutečně zapíná a vypíná zátěž;
- modul MOSFET se neohřívá nadměrně;
- svorky se neohřívají;
- vodiče jsou vhodné pro proud;
- PWM funguje bez podivného šumu, blikání nebo restartů;
- zátěž je skutečně vypnuta, když je příkaz vypnutý;
- pro motor/solenoid je ochrana proti skokům;
- pro topidlo je pojistka a nezávislá tepelná ochrana.

Proveďte první test těžké zátěže stručně a pod dohledem.

## Běžné chyby

- napájení zátěže z GPIO;
- zapomenutí společné země;
- výběr modulu pouze podle pěkného čísla proudu v názvu;
- nezkontrolování provozu od logiky `3.3V`;
- používání MOSFET, který se plně neotvírá;
- připojení motoru nebo solenoidu bez zpětné ochrany;
- připojení dlouhého LED pásu přes slabé svorky;
- používání stejnosměrného modulu MOSFET pro `110-230V AC`;
- nezkontrolování ohřevu modulu v uzavřeném pouzdru;
- myšlenka, že samotný modul MOSFET omezuje proud zátěže.

## Hlavní bod

Modul MOSFET je řízený výkonový spínač pro stejnosměrné zátěže. Nevytváří výkon a nepřipojuje zátěž z řídícího prvku. Pouze otevírá nebo zavírá cestu pro proud ze zdroje napětí.

Zkontrolujte napětí, proud, kompatibilitu s logikou `3.3V`/`5V`, společný `GND`, ohřev, svorky a ochranu pro induktivní zátěže. Pro síťové napětí není standardní modul Arduino/ESP32 MOSFET vhodný.

## Referenční materiály

- [SparkFun MOSFET Power Switch and Buck Regulator Hookup Guide](https://docs.sparkfun.com/SparkFun_MOSFET_Power_Switch_and_Buck_Regulator_Low-Side/single_page/) - příklad hotového modulu MOSFET na nižší straně, připojení zátěže, tepelné limity desky a zpětná dioda.
- [SparkFun MOSFET Power Switch product page](https://www.sparkfun.com/products/23979) - příklad toho, jak výrobce specifikuje napětí, proud, obvod na nižší straně, MOSFET a omezení desky.
- [Adafruit MOSFET Driver](https://learn.adafruit.com/adafruit-mosfet-driver) - praktické vysvětlení, proč nemohou být motory, solenoidy a výkonné LED připojeny přímo k GPIO a proč je potřebná ochrana proti skokům.
- [DigiKey: How to Select a MOSFET](https://www.digikey.com/en/blog/how-to-select-a-mosfet-for-logic-circuits-or-gate-design) - výběr MOSFET podle `Vgs`, `Rds(on)` a úrovně logického řízení.
- [Infineon: Logic level MOSFETs](https://www.infineon.com/products/power/mosfet/n-channel/optimos-strongirfet/optimos-ir-mosfet-logic-level) - vysvětlení MOSFET na úrovni logiky a řízení z mikrokontroléru.
