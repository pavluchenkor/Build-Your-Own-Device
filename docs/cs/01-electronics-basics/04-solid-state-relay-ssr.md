# Polovodičové relé

Polovodičové relé, neboli SSR, je relé bez mechanických kontaktů. Aplikujete slabý řídicí signál ze řídícího prvku na vstup SSR a výstup SSR zapne nebo vypne zátěž.

V jednoduchých zařízeních pro 3D tiskárny se SSR nejčastěji používá pro topidlo v síti: komoru, sušičku, stůl nebo samostatný modul vytápění. Je to pohodlný způsob, jak ovládat `110-230V AC` zátěž z nízkovoltážní elektroniky, ale ne způsob, jak učinit síť bezpečnou.

Pokud má projekt `110-230V AC`, silová část musí být sestavena v obalu s pojistkou, normálními svorkami, izolací, zpětným vedením kabelů a pochopením elektrické bezpečnosti.

## Jak se SSR liší od běžného relé

Běžné elektromagnetické relé klikne, protože se kontakty fyzicky pohybují uvnitř. Cívka relé potřebuje energii, často potřebuje tranzistorový ovladač, ochrannou diodu a kontakty mohou jiskřit, chvět se a opotřebovávat.

SSR přepíná zátěž pomocí polovodičů. Proto nemá klik, nemá mechanické opotřebení kontaktů a je lépe vhodné pro často se opakující zapínání/vypínání topidla.

Ale SSR není "relé bez nevýhod".

SSR má svá vlastní omezení:

- zahřívá se;
- často vyžaduje chladič;
- může mít malý únikový proud v otevřeném stavu;
- hůře snáší přetížení a skokové přepětí než správně vybrané kontaktory;
- může selhat v "zapnutém" stavu;
- musí být vybrán pro AC nebo DC zátěž;
- nenahrazuje pojistku, kryt a nouzovou tepelnou ochranu.

Pro zřídka se opakující přepínání zátěže může být vhodné běžné relé nebo kontaktor. Pro časté ovládání odporového topidla je SSR často praktičtější.

## Co je uvnitř AC SSR

AC SSR obvykle obsahuje:

- vstupní obvod řídicího signálu;
- optickou izolaci;
- spouštěcí obvod;
- výkonový TRIAC nebo pár tyristorů;
- obvod tlumení nebo jinou ochranu proti skokům;
- výkonové svorky pro zátěž.

Zjednodušeně řečeno, je to hotový TRIAC obvod v obalu. Proto je SSR pohodlný tam, kde nechcete sami počítat optoisolaci TRIAC, TRIAC, tlumení, rozestup desky a síťovou část.

Hotový kryt neodstraňuje potřebu ověření. Zvláště pokud je SSR levný, nemá technickou specifikaci nebo má podezřele vysoké proudové hodnocení na obalu.

## AC SSR a DC SSR

SSR musí být vybrán podle typu zátěže:

- **AC SSR** - pro střídavý proud, například topidlo v síti `110-230V AC`;
- **DC SSR** - pro stejnosměrný proud, například `12V` nebo `24V` DC zátěž.

Jsou to různá zařízení. AC SSR nelze automaticky umístit na `24V` DC topidlo: nemusí se vypnout. DC SSR nelze považovat za vhodné pro `230V AC`: může být nebezpečné a není pro takový obvod určeno.

Musíte zkontrolovat nejen `AC` nebo `DC` štítek, ale také rozsah výstupního napětí.

Příklady značení:

```text
Vstup: 3-32V DC
Výstup: 24-380V AC
```

To znamená:

- vstup je ovládán signálem nízkovoltážního DC;
- výstup přepíná AC zátěž v uvedeném rozsahu;
- nepotřebujete napájet zátěž ze vstupní strany přes SSR.

Před nákupem zkontrolujte řádky `Input`, `Output`, `Load voltage`, `Load current` a schéma zapojení výrobce.

## Typické schéma zapojení

SSR se obvykle umisťuje do rozříznuté линии napájení zátěže. Řídící prvek se připojuje pouze na vstup SSR, zatímco síť prochází výstupem SSR.

![Vnitřní struktura polovodičového relé SSR](../../img/01-electronics-basics/04-ssr-internal-structure.png)

*Zdroj: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:SSR.png), Thomas Verdyck, CC BY-SA 3.0*

Důležité body:

- vstup a výstup SSR jsou různé strany zařízení;
- nízkovoltážní strana nesmí být spojena se síťovou stranou;
- SSR se umisťuje do rozříznuté linky napájení zátěže, obvykle `Line`;
- ochranné uzemňění `PE` se nepřerušuje skrz SSR;
- pojistka musí chránit vedení a zátěž;
- topidlo potřebuje nezávislou tepelnou ochranu;
- celá síťová část musí být zavřena před dotykem.

SSR se nepovažuje za servisní odpojovač. Pro údržbu potřebujete fyzický způsob, jak odpojit energii: spínač, jistič, konektor nebo jiné standardní přerušení obvodu. V praxi mohou být různá schémata podle místních pravidel, typu výkonu, ochranného uzemňění a obalu. Pokud si nejste jisti, měla by schéma ověřit kvalifikovaná osoba.

## Nulový průchod, náhodné zapnutí a řízení

AC SSR existuje s různými metodami zapnutí.

**Nulový průchod SSR** zapíná zátěž blízko nulového průchodu síťového napětí. To je dobrá volba pro jednoduché zapnutí/vypnutí odporového topidla: méně hluku a měkčího přepínání.

**Náhodné zapnutí SSR** zapíná výstup téměř okamžitě po aplikaci řídicího signálu. Tento typ se používá tam, kde je potřeba jiná logika, fázové řízení nebo specifické požadavky na zatížení.

Pro komoru, sušičku nebo jednoduché topidlo obvykle není potřeba rychlé řízení dimeru. Často stačí pomalé řízení: například zapnout topidlo na několik sekund, ne tlačit ho stokrát za sekundu.

Ne všechna SSR jsou vhodná pro fázové řízení. Pokud konkrétně potřebujete regulátor fázové energie, to je samostatný typ zařízení a samostatné téma s šumem, teplem a požadavky na zátěž.

## Únikový proud

SSR může vést malý proud i když je "vypnuté". To se nazývá únikový proud.

Pro výkonné topidlo takový proud obvykle nevytváří znatelné topení, ale pro malou žárovku, LED ovladač, zdroj napětí nebo velmi malou zátěž to může být znatelné: indikátor může svítit slabě, vstup zdroje se může chovat podivně.

Proto by SSR neměl být považován za ideální odpojovač obvodu. Před prvním zapnutím topidla ověřte, že zátěž se nezahřívá, když je řídicí signál odstraněn. Je lépe nejdříve otestovat výstup SSR s bezpečnou malou zátěží, žárovkou nebo multimetrem, ne okamžitě s hlavním topidlem.

Pro údržbu, nouzové vypnutí a úplnou izolaci potřebujete spínač, jistič, pojistku, konektor nebo jiný fyzický způsob, jak odpojit energii.

## Ohřev a chladič

SSR se během provozu zahřívá. V zapnutém stavu je pokles napětí přes výkonný prvek, což znamená, že se generuje teplo.

Musíte zkontrolovat:

- proud zátěže;
- maximální proud SSR při skutečné teplotě;
- pokles napětí na výstupu;
- požadavky na chladič;
- teplotu uvnitř obalu;
- orientaci chladiče a proudění vzduchu;
- kvalitu tepelného kontaktu mezi SSR a chladičem;
- teplotu svorek a drátů po testu.

Štítek `25A` nebo `40A` neznamená, že SSR bude obsahovat takový proud bez chladiče v uzavřeném obalu vedle topidla. Výrobci obvykle specifikují proud za určitých chladicích podmínek.

Praktické pravidlo pro jednoduchý projekt: nevybírejte SSR přesně na proud zátěže. Plánujte rezervu, použijte chladič, čtěte technickou specifikaci a ověřte teplotu v reálném obalu. `50%` rezerva je dolní hranice pro počáteční odhad, ne záruka pro žádnou instalaci.

## SSR nechrání topidlo

SSR je výkonový spínač, ne bezpečnostní systém.

Topidlo potřebuje nezávislé vrstvy:

- pojistka nebo jistič pro vedení a zátěž;
- správný teplotní senzor;
- softwarové teplotní limity;
- kontrola topení v firmware;
- nezávislý termostat, tepelná pojistka nebo bimetalový spínač;
- kryt vyrobený z materiálu, který snese skutečné teploty;
- první test pod dohledem.

Důležitý režim selhání: SSR se může porouchat a zůstat zapnutý. Proto musí nouzová tepelná ochrana moct odpojit energii topidla nezávisle na řídícím prvku a SSR.

## Jaké zátěže jsou vhodné

SSR je nejsnáze použitelné s odporovými zátěžemi CA:

- topidlo;
- silikónové topné polštáře;
- žárovka;
- jednoduchá tepelná zátěž bez vestavěné elektroniky.

Buďte opatrní s:

- motory;
- ventilátory CA;
- transformátory;
- solenoidy;
- zdroji napětí;
- elektronickými ovladači;
- zátěžemi s vysokým nárazovým proudem.

Induktivní a elektronické zátěže mohou vyžadovat jiný typ SSR, tlumení, varistor, kontaktor nebo samostatný obvod. SSR nemůžete vybrat pouze podle štítku `40A`.

## Co zkontrolovat před nákupem

Před nákupem SSR zkontrolujte:

- zátěž AC nebo DC;
- napětí zátěže;
- proud zátěže a výkon;
- vstupní napětí řízení;
- kompatibilita vstupu s řídícím prvkem: `3.3V`, `5V`, `12V` nebo jiná úroveň;
- typ zapnutí: nulový průchod nebo náhodné;
- maximální proud v potřebném chlazení;
- je potřeba chladič;
- existuje technická specifikace;
- existuje normální schéma zapojení;
- svorky a vzdálenosti izolace;
- kvalita výrobce;
- kde je pojistka umístěna;
- kde bude umístěna nezávislá tepelná ochrana.

Pokud není dokumentace a SSR má ovládat topidlo v síti, je to špatná volba.

## Běžné chyby

- zmatek vstupu a výstupu SSR;
- nákup DC SSR místo AC SSR nebo naopak;
- nezkontrolování rozsahu výstupního napětí;
- připojení AC SSR k DC topidlu a překvapení, že se nevypne;
- výběr SSR přesně na proud zátěže;
- instalace SSR bez chladiče;
- instalace SSR v zavřeném, horkém obalu;
- neúčtování únikového proudu;
- použití SSR jako jediného způsobu nouzového vypnutí;
- zapomenutá pojistka;
- neinstalace nezávislé tepelné ochrany topidla;
- ponechání přístupných síťových svorek;
- řízení SSR příliš rychlým PWM bez pochopení typu SSR a zátěže.

## Hlavní bod

SSR je pohodlné pro časté tiché ovládání zátěže, zvláště odporové topidlo v síti. Ale SSR musí být vybrán pro typ zátěže, napětí, proud, metodu zapnutí a tepelný provozní bod.

Pro `110-230V AC` zátěž SSR neodstraňuje elektrickou bezpečnost. Potřebujete kryt, pojistku, normální vedení, chladič je-li potřeba a nezávislou tepelnou ochranu topidla.

## Referenční materiály

- [Omron: Overview of Solid-state Relays](https://www.ia.omron.com/support/guide/18/introduction.html) - design SSR, optická izolace, typy a obecné principy aplikace.
- [Omron: SSR glossary and installation notes](https://www.ia.omron.com/support/guide/18/further_information.html) - definice `load voltage`, `leakage current`, `output ON voltage drop`, nulový průchod, tlumení a poznámky k disipaci tepla.
- [Panasonic: SSR Principle of Operation](https://industry.panasonic.com/global/en/products/control/relay/solid-state/principle_operation) - rozdíl mezi SSR s nulovým průchodem a náhodným, chování s odporovými a induktivními zátěžemi CA.
- [Sensata/Crydom: HS Series Heat Sinks](https://www.sensata.com/products/relays/solid-state-relays/ssr-accessories/hs-series-heat-sinks) - proč SSR generuje teplo a proč by se chladič měl shodovat s proudem a teplotou.
- [DigiKey: Solid State Relays - A Basic Overview](https://www.digikey.com/en/blog/solid-state-relays-a-basic-overview) - stručný přehled typů výstupů SSR, nulový průchod, náhodné zapnutí a omezení ve srovnání s mechanickými relé.
