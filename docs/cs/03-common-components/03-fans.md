---
title: "Ventilátory a proudění vzduchu v sušičce filamentu"
description: "Proč je proudění vzduchu důležité v sušičce filamentu a vyhřívané komoře: výběr ventilátoru, průtok, statický tlak, hluk a rovnoměrný ohřev."
---

# Ventilátory a proudění vzduchu v sušičce filamentu

Ventilátor nejen pohybuje vzduchem: rozvádí teplo, omezuje lokální horká místa a pomáhá sušit filament rovnoměrně. Tato stránka pomáhá vybrat ventilátor a pochopit vliv proudění na skříň, topení a teplotní senzor.

Ventilátor je motor se spirálou, který pohybuje vzduchem. V zařízeních kolem 3D tiskárny jej potřebujete ne jen "aby foukal", ale aby tlačil vzduch do správné zóny: topného tělesa, cívky, filtru, chladiče, komory nebo elektronického prostoru.

Ventilátory stejné velikosti mohou fungovat velmi odlišně. Jeden dobře tlačí vzduch v otevřeném prostoru, druhý lépe tlačí vzduch přes filtr nebo potrubí, třetí je tichý, ale slabší při odporu.

## Kde se používá

V projektech podobných iDryer se ventilátory používají pro:

- oběh vzduchu uvnitř sušičky;
- přenos tepla z topného tělesa do komory;
- vyfukování vzduchu z komory tiskárny;
- filtrování přes HEPA/uhlíkový filtr;
- chlazení elektroniky;
- chlazení chladiče;
- vyrovnávání teploty v krytu.

Pro ohřev komory je ventilátor obzvlášť důležitý. Topné těleso uvolňuje teplo a proud vzduchu odstraňuje toto teplo z prvku a odnáší jej dál. Bez správného proudění vzduchu se topné těleso může místně přehřát, zatímco se komora ohřívá špatně.

## Průtok vzduchu a statický tlak

V technickém popisu ventilátoru obvykle vidíte dva důležité parametry:

- průtok vzduchu - často v `CFM` nebo `m3/h`;
- statický tlak - často v `mmH2O`, `Pa` nebo `inch H2O`.

Průtok vzduchu ukazuje, kolik vzduchu ventilátor může čerpat za ideálních podmínek s malým odporem.

Statický tlak ukazuje, jak dobře ventilátor může tlačit vzduch přes odpor: filtr, mřížku, chladič, úzké potrubí nebo dlouhou vzduchovou trubici.

Praktické pravidlo:

- pro otevřenou oběh je důležitější průtok vzduchu;
- pro filtry, chladiče, husté mřížky a potrubí je důležitější statický tlak;
- pro skutečný kryt, důležitý je pracovní bod, ne jen maximální číslo ve specifikaci.

Pokud umístíte tichý ventilátor krytu na hustý filtr, může sotva tlačit vzduch, i když se zdá průtok vzduchu silný v otevřeném prostoru.

## Axiální a radiální ventilátory

Axiální ventilátor tlačí vzduch podél osy rotace. To jsou typické čtvercové ventilátory `40x40`, `60x60`, `80x80`, `120x120 mm`.

Radiální ventilátor nasává vzduch ze strany a vyfukuje jej přes úzký výstup. Často funguje lépe pro potrubí, trysky, filtry a místa, kde potřebujete tlak.

Pro volnou oběh uvnitř komory je axiální ventilátor obvykle vhodný. Pro kompaktní potrubí, filtr nebo řízený průtok je někdy lepší radiální ventilátor.

## 2-pin, 3-pin a 4-pin

Ventilátory se často liší počtem vodičů.

![3-pin konektor na ventilátoru počítače](../../img/03-common-components/03-fan-3pin-connector.jpg)

*Zdroj: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Three-pin_connector_on_a_computer_fan.jpg), Dsimic, CC BY-SA 4.0*

2-pin:

- `+V`;
- `GND`.

Takový ventilátor jednoduše dostane napájení. Můžete řídit rychlost změnou napájecího napětí nebo PWM na přívodu napájení, pokud je to deska a ventilátor podporují.

3-pin:

- `+V`;
- `GND`;
- signál tachometru (`tach`/`sense`).

Třetí vodič obvykle vyvádí signál rychlosti. Sám o sobě neřídí rychlost.

4-pin PWM:

- `GND`;
- `+V`;
- signál tachometru (`tach`/`sense`);
- signál řízení PWM.

U 4-pin PWM ventilátoru je napájení obvykle dodáváno neustále a rychlost je nastavena na samostatné PWM řádce. To není totéž jako rychlé přepínání napájení ventilátoru zapnuto a vypnuto.

## PWM a tachometr

PWM je řídicí signál, který nastavuje požadovanou rychlost. Počítačové 4-pin PWM ventilátory mají typicky frekvenci kolem `25 kHz` a napájení zůstává konstantní.

Pokud je vodič PWM nepřipojen, mnohé 4-pin ventilátory běží plnou rychlostí.

Signál tachometru ukazuje otáčky za minutu. Je potřeba, pokud by zařízení mělo pochopit:

- zda se ventilátor otáčí nebo je zastaven;
- zda se rychlost shoduje s příkazem;
- zda filtr nebo potrubí vytváří příliš velký odpor;
- zda je ventilátor zaseknutý.

Tachometr nenahrazuje kontrolu teploty. V zařízení s topným tělesem musíte sledovat jak teplotu, tak stav proudění vzduchu, pokud je selhání ventilátoru nebezpečné.

## Napětí a proud

Před připojením zkontrolujte:

- napětí ventilátoru: `5V`, `12V`, `24V`;
- provozní proud;
- startovací proud;
- typ konektoru;
- rozložení pinů;
- zda má PWM;
- zda má tachometr;
- provozní teplota;
- směr průtoku vzduchu;
- úroveň hluku;
- životnost a typ ložiska.

Nemůžete napájet ventilátor z GPIO regulátoru. GPIO je signál, ne výstup napájení. Proud ventilátoru musí pocházet ze zdroje napájení, výstupu napájení desky nebo modulu MOSFET.

Při spuštění může ventilátor krátce odebrat více proudu než během normálního provozu. Pokud je ke jednomu výstupu připojeno více ventilátorů, jejich proudy se sčítají.

## Hluk, vibrace a ložisko

Hluk závisí na více než jen otáčkách.

Zvuk je ovlivněn:

- tvar lopatky;
- vyvažování;
- typ ložiska;
- montáž;
- mřížka;
- potrubí;
- filtr;
- rezonance krytu;
- více ventilátorů blízko sebe.

Technické popisy uvádějí hluk v `dB(A)`, ale v skutečném krytu může ventilátor znít jinak. Mřížka s špatnou geometrií, blízká stěna nebo tuhá montáž na tenký panel mohou udělat dobrý ventilátor hlučný.

Pro zařízení, které běží hodiny, je lepší vybrat si ventilátor ne jen podle ceny a velikosti, ale podle životnosti, ložiska a teploty.

## Teplota a místo instalace

Ventilátor, který dobře funguje na pracovní ploše, se může rychle zhoršit v horké komoře.

Zkontrolujte:

- provozní teplota ventilátoru;
- teplota vzduchu blízko topného tělesa;
- vzdálenost od topného prvku;
- zda horký proud přímo zasahuje motor;
- zda se montáž změkčuje;
- zda se vodiče vysušují;
- zda se ventilátor ucpává prachem nebo vlákny.

Pokud je ventilátor zodpovědný za průtok vzduchu topného tělesa, mělo by být selhání do bezpečné logiky zahrnuto. Nemůžete navrhnout topné těleso tak, aby zastavený ventilátor okamžitě vytvořil nebezpečnou teplotu bez nouzového vypnutí.

## Filtry a potrubí

Filtr, mřížka a potrubí mohou výrazně snížit užitečný průtok vzduchu.

Typické příznaky:

- ventilátor je hlučný, ale průtok vzduchu je slabý;
- filtr sotva propouští vzduch;
- vzduch obchází filtr přes mezery;
- teplota blízko topného tělesa stoupá rychleji než teplota komory;
- po namontování krytu je průtok vzduchu horší než na pracovní ploše.

Aby se efektivně filtrovala komora, nemusíte jen umístit ventilátor, musíte zajistit cestu vzduchu přes filtr. Pokud si vzduch najde cestu přes mezeru, půjde jí.

## Co zkontrolovat před nákupem

Před nákupem ventilátoru zkontrolujte:

- velikost a tloušťku;
- napětí;
- proud;
- typ: axiální nebo radiální;
- průtok vzduchu;
- statický tlak;
- hluk;
- otáčky;
- typ ložiska;
- 2-pin/3-pin/4-pin;
- provozní teplota;
- životnost;
- směr průtoku vzduchu;
- konektor a rozložení pinů;
- zda se hodí pro filtr, potrubí nebo volnou oběh.

Pro filtr a úzké potrubí si nevybírejte ventilátor pouze podle CFM. Podívejte se na statický tlak a testujte v reálné montáži.

## Typické chyby

- připojení 12V ventilátoru k 24V;
- připojení 24V ventilátoru na 12V a myšlenka, že je rozbitý;
- napájení ventilátoru z GPIO;
- nezřízením společného uzemnění pro externí MOSFET/PWM;
- nezapočítaný startovací proud;
- připojení více ventilátorů k slabému výstupu;
- výběr ventilátoru pouze podle velikosti;
- instalace ventilátoru s volným průtokem na hustý filtr;
- myšlení, že drát tach je řídící drát;
- myšlení, že 4-pin PWM je totéž jako 2-pin;
- řízení 4-pin PWM ventilátoru přepínáním napájení zapnuto/vypnuto;
- instalace ventilátoru v horké zóně bez kontroly teploty;
- nekontrolování průtoku vzduchu po instalaci krytu, filtru a potrubí.

## Hlavní bod

Ventilátor se vybírá pro úkol: volná oběh, filtr, potrubí, chladič, chlazení topného tělesa nebo elektroniky. Pro otevřený prostor je důležitý průtok; pro filtry a potrubí je důležitý tlak.

Zkontrolujte napětí, proud, typ vodiče, PWM/tachometr, provozní teplotu a skutečný odpor systému. V zařízení s topným tělesem by měl být ventilátor součástí bezpečného tepelného systému, ne dekorativní součásti.

## Referenční materiály

- [Noctua: Microcontroller guide for PWM and RPM monitoring](https://www.noctua.at/en/support/faqs/microcontroller-guide-pwm-setup-and-rpm-monitoring) - praktické vysvětlení 4-pin PWM, tachometru, napájení a PWM frekvence kolem 25 kHz.
- [Noctua: Fan pin configuration](https://www.noctua.at/faq-redirects/en/support/solutions/articles/101000081757-what-pin-configuration-do-noctua-fans-use-) - standardní rozložení 4-pin fanouška a chování při připojení pouze napájení.
- [SANYO DENKI: Fan Airflow and Static Pressure](https://techcompass.sanyodenki.com/en/training/cooling/fan_basic/004/index.html) - vysvětlení průtoku vzduchu, statického tlaku, pracovního bodu a odporu systému.
- [DigiKey: Selecting A Fan](https://www.digikey.ca/en/articles/selecting-a-fan) - výběr typu ventilátoru, křivka ventilátoru, odpor systému a rozdíl mezi axiálními a radiálními ventilátory.
- [Klipper Configuration Reference: Fans](https://www.klipper3d.org/Config_Reference.html#fans) - oficiální sekce Klipper pro ventilátory: `fan`, `heater_fan`, `temperature_fan`, `controller_fan` a `fan_generic`.
