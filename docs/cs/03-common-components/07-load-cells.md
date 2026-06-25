# Snímače hmotnosti

Siloměr měří sílu prostřednictvím drobné deformace kovu. Vážení cívky, sledování zbývajícího vlákna a jednoduché zátěžové plošiny téměř vždy používají takové senzory.

Důležité k pochopení: siloměr sám o sobě „necítí váhu“. Při zatížení se mírně ohýbá nebo stlačuje a elektronika měří mikroskopickou změnu odporu na tenzometrech. Takže dvě věci jsou kritické: správná mechanika a normální zesilovač/ADC.

## Kde se používá

V projektech podobných iDryer lze snímač zatížení použít pro:

- odhad hmotnosti cívky s vláknem;
- hrubý výpočet zbývajícího plastu;
- kontrola, zda je cívka nainstalována;
- detecting sudden weight change;
- měření zatížení na malém mechanismu;
- experimental weight platform;
- řízení dávkování v systémech pro kutily.

Pro jednoduché "cívka přítomna/nepřítomna" někdy stačí koncový spínač nebo optický senzor. Siloměr je potřeba, když je důležité skutečně měřit hmotnost nebo změnu síly.

## Proč je potřeba HX711

Signál snímače zatížení je velmi slabý. Typický analogový vstup na ESP32, Arduinu nebo desce tiskárny obvykle nefunguje pro přímé připojení.

Takže snímač zatížení je obvykle připojen přes HX711 nebo podobný modul. HX711 dělá dvě věci:

- zesiluje slabý signál diferenciálního můstku;
- převádí je na digitální data pro regulátor.

Typický řetěz:

```text
load cell -> HX711 -> controller
```

Podrobné schéma zapojení je v praktické části: [Připojení siloměru](../06-practical-guides/04-connecting-load-cell.md).

## Jaké typy snímačů zatížení existují

U malých projektů jsou nejčastější:

- buňka nosníku - vhodná pro malé plošiny a držáky cívek;
- Buňka typu S - pracuje v tahu/kompresi, často se používá v závěsných sestavách;
- button cell - measures compression at one point;
- čtyři buňky na plošině - typické provedení podlahové váhy;
- jednotlivé tenzometrické prvky - vyžadují správný můstek a mechaniku, těžší pro začátečníky.

U systému závaží na cívku pro kutily je obvykle jednodušší začít s paprskovým siloměrem na `10 kg`, `10 kg` nebo blízkém dosahu. Dosah však závisí na hmotnosti cívky, držáku a případných trhnutích.

## Dráty a most

Most common four-wire load cells have a bridge circuit.

Na HX711 obvykle vidíte značky:

- `E+` or `VCC` - bridge power plus;
- `E-` or `GND` - bridge power minus;
- `A+`, `S+`, `O+` - positive measurement signal;
- `A-`, `S-`, `O-` - negative measurement signal.

Běžné barevné schéma:

- red - `E+`;
- black - `E-`;
- green or blue - `A+`;
- white - `A-`;
- yellow, foil or separate wire - shield.

Barvy nejsou zaručeny. Pokud existuje technický popis konkrétní buňky, je důležitější než jakákoli internetová tabulka. Pokud jdou odečty špatným směrem, často stačí jen prohození `A-` a `A-` nebo zaúčtování znaménka v programu.

## Mechanics Matter More Than Circuit

Siloměr se musí deformovat přesně tak, jak zamýšlel výrobce. Pokud se zátěž pohybuje kolem pracovní zóny, buňka bude ukazovat nestabilní hodnoty nebo téměř nic.

![Miniature S-beam load cell](../../img/03-common-components/07-miniature-load-cell.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Miniature_S-beam_load_cell.jpg), FUTEK Advanced Sensor Technology, CC BY-SA 4.0*

Pro paprskovou buňku je typická myšlenka:

- jedna strana je pevně připevněna k pevné základně;
- other side carries a platform or load;
- mezi pohyblivou částí a základnou je vůle;
- šrouby a pouzdro neblokují ohyb paprsku.

Poor mechanics gives such symptoms:

- drift hodnot bez zatížení;
- hmotnost závisí na tom, kam kladete cívku;
- buňka téměř nereaguje na zátěž;
- po odstranění zátěže se nula nevrátí;
- dotykem pouzdra se hodnoty prudce změní;
- různé sestavy vykazují různou hmotnost při stejném nastavení.

## Dosah a přetížení

Rozsah snímače zatížení není požadovaná pracovní hmotnost, je to limit, pro který je dimenzován.

Použití buňky `1 kg` pro cívku, držák a trhnutí nad `100 kg` může vést k nelinearitě nebo trvalé deformaci. Použití buňky `1 kg` pro cívku `1 kg` ztrácí citlivost a mechanici musí být mnohem opatrnější.

Při výběru rozsahu zvažte:

- maximální hmotnost plné cívky;
- hmotnost držáku a plošiny;
- misalignment forces;
- náhodné trhnutí při montáži;
- marže pro uživatele;
- desired accuracy.

Pro zbývající vlákno je často užitečnější střední rezerva než velký rozsah. Například pro cívku s držákem o hmotnosti několika kilogramů je obvykle lepší buňka `10 kg` nebo `50 kg` než `50 kg`, pokud to mechanika dovolí.

## Tára a kalibrace

Siloměr bez kalibrace vydává hrubá čísla, nikoli gramy.

Typický proces:

1. Nainstalujte článek do skutečné mechaniky.
2. Put an empty platform or holder.
3. Vytárovat - přijmout aktuální hodnotu jako nulu.
4. Put a known weight.
5. Upravte kalibrační koeficient.
6. Zkontrolujte ještě jednu nebo dvě další hmotnosti.

U cívek je tu další problém: prázdná cívka také váží jinak. Pokud potřebujete odhadnout pouze plast, musíte znát hmotnost prázdné cívky nebo uložit profil pro tuto konkrétní cívku.

## Přesnost a stabilita

V praxi přesnost závisí na více než HX711 a buňce.

Čtení ovlivňuje:

- case rigidity;
- mounting play;
- side load;
- printer vibration or fan noise;
- délka drátu a stínění;
- measurement wires near power lines;
- temperature;
- tečení materiálu a plastická deformace;
- kabel nebo cívka dotýkající se pouzdra kolem článku.

Pokud je siloměr v potištěném plastovém pouzdře, neočekávejte laboratorní přesnost. Pro odhady zbývajícího filamentu často postačují stabilní hodnoty a opakovatelnost po kalibraci.

## Napájení a elektroinstalace

HX711 měří slabý signál, takže kabeláž by měla být opatrná.

Practical rules:

- držte HX711 blízko siloměru;
- neveďte kabely článků v blízkosti topných těles, motorů a elektrických vedení;
- zajistěte dráty, aby netáhly plošinu;
- použijte společný `GND` s ovladačem;
- napájejte modul napětím kompatibilním s regulátorem;
- nepoužívejte špatné kontakty Dupont při konečné montáži, pokud má zařízení pracovat dlouho.

Na straně ovladače se HX711 obvykle připojuje přes `DOUT`/`SCK` a `CLK`/`CLK`. Nejedná se o běžné I2C nebo SPI, ale o samostatné jednoduché rozhraní.

## Co zkontrolovat před nákupem

Před nákupem zkontrolujte:

- cell type: beam, S-type, button, platform;
- weight range;
- load application direction;
- rozměry a montážní otvory;
- dostupnost popisu nebo schématu zapojení;
- zda je potřeba jedna buňka nebo čtyři buňky;
- whether HX711 module fits your chosen cell;
- zda je zde prostor pro správnou vůli a montáž;
- zda můžete použít známou váhu pro kalibraci;
- zda zátěž neprojde pouzdrem kolem buňky.

Pokud mechanika ještě není promyšlená, je lepší nejprve načrtnout upevnění. Nákup „jakéhokoli siloměru“ často končí tím, že je fyzicky nemožné správně namontovat.

## Typické chyby

- připojení snímače zatížení přímo k analogovému vstupu;
- matoucí `E-`/`A+` a `A-`/`A-`;
- důvěřivé barvy drátu bez popisu;
- připevnění obou stran buňky nosníku k jedné tuhé části;
- blokování ohýbání buněk pomocí šroubů nebo pouzdra;
- přetížení buňky;
- volba příliš velkého rozsahu a ztráta citlivosti;
- zapomenutí táry a kalibrace;
- kalibrace na pracovním stole a následná instalace článku v různých mechanikách;
- routing wires near heater power lines;
- od pouzdra z měkkého plastu očekáváte gramovou přesnost.

## Hlavní bod

Siloměr je součást, kde na mechanice záleží stejně jako na elektronice. HX711 pomáhá číst slabý signál, ale neopraví křivou montáž, přetížení nebo zatížení kolem buňky.

Nejprve zvolte správný typ a rozsah, poté navrhněte upevnění, poté připojte HX711 a teprve poté proveďte tárování a kalibraci.

## Reference Materials

- [SparkFun: Load Cell Amplifier HX711 Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide) - practical connection of load cell to HX711, wires, library and calibration.
- [SparkFun HX711 product page](https://www.sparkfun.com/sparkfun-load-cell-amplifier-hx711.html) - description of HX711 role as bridge between load cell and microcontroller.
- [DigiKey: HX711 Datasheet by Avia Semiconductor](https://www.digikey.com/en/htmldatasheets/production/1836471/0/0/1/hx711.html) - technical description of HX711: 24-bit ADC, bridge sensor input and digital interface.
- [Phidgets: Load Cell Guide](https://cdn.phidgets.com/docs/Load_Cell_Guide) - practical examples of load cell types, load direction and mounting.
- [SparkFun retired HX711 guide: mechanical setup](https://learn.sparkfun.com/tutorials/retired---load-cell-amplifier-hx711-breakout-hookup-guide) - useful illustrations of beam, S-type and platform cell mounting.
