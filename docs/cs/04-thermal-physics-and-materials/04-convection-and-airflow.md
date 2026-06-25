# Konvekce a proudění vzduchu

Konvekce je přenos tepla pomocí proudu vzduchu. V sušičce, tiskárně komory, ohřívaném filtru nebo zařízení podobném iHeater-u vzduch často určuje, zda teplo dosáhne tam, kam je potřeba.

Topidlo samo o sobě pouze mění elektrickou energii na teplo. Ventilátor a vzduchochod určují, zda se toto teplo rovnoměrně rozloží po celé komoře, nebo zůstane na malém nebezpečném horkém místě.

## Tři režimy jednoho topidla

Stejné topidlo s výkonem `100 W` může pracovat zcela odlišně.

![Konvekční buňky: teplý vzduch stoupá, studený padá](../../img/04-thermal-physics-and-materials/04-convection-cells.svg)

*Zdroj: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Convection_cells.svg), McSush, CC BY-SA 3.0*

Bez proudu vzduchu:

- topidlo se silně zahřívá v místní zóně;
- vzduch v okolí se zahřívá, ale slabě se mísí;
- vzdálená část komory může zůstat chladná;
- plast, svorky nebo izolace v okolí se mohou přehřívat;
- teplotní senzor nemusí ukazovat, co se děje u topidla.

Se slabým nebo nesprávným proudem vzduchu:

- část tepla jde do komory;
- dochází k míšení;
- ale proud může obejít topidlo;
- filtr, síť nebo úzký kanál mohou výrazně snížit průtok vzduchu;
- horká místa zůstávají.

Se normálním průtokem:

- vzduch projde horkou zónou;
- teplo uniká z topidla do komory;
- teplota se stává více rovnoměrná;
- PID ovládání funguje více předvídatelně;
- okolní části se přehřívají méně místně.

Průtok vzduchu nevytváří dodatečnou energii. Pomáhá odejmout již vytvořené teplo a přenést jej na správné místo.

## Přirozená a vynucená konvekce

Existují dva užitečné režimy:

- přirozená konvekce - teplý vzduch stoupá sám;
- vynucená konvekce - proud je vytvořen ventilátorem, dmychadlem nebo odstředivým ventilátorem.

U malých topených zařízení je přirozená konvekce často nedostatečná. Je pomalá, závisí na tvaru krytu a snadno vytváří zóny teploty.

Vynucená konvekce je obvykle lepší, pokud potřebujete:

- rychle odvést teplo z topidla;
- rovnoměrně ohřát komoru;
- vést vzduch skrz filtr;
- sušit filament;
- chladit elektroniku;
- udržet teplotní senzor v smysluplném proudu vzduchu.

## Ventilátor není jen velikost

Fráze „dám si ventilátor 40 mm" vám řekne téměř nic o výsledku.

Pro skutečné zařízení jsou důležité:

- průtok vzduchu;
- statický tlak;
- pracovní bod po instalaci v krytu;
- směr proudu;
- odpor sítí, filtrů a vzduchochlodů;
- teplota vzduchu u ventilátoru;
- hluk a vibrace;
- zdrojový výkon pod zátěží;
- počáteční proud;
- tachometr nebo řízení otáček.

Katalog často uvádí maximální průtok a maximální statický tlak. V reálném zařízení ventilátor nepracuje v těchto ideálních bodech. Filtr, síť, úzký kanál, zatáčka vzduchochlodu a hustý topič vytvářejí odpor, takže skutečný průtok může být mnohem nižší.

Pokud má vzduch procházet filtrem, radiátorem, voštinou nebo úzkým kanálem, obvykle nepotřebujete jen „více CFM", ale ventilátor nebo odstředivé dmychadlo s odpovídajícím statickým tlakem.

## Cesta vzduchu

Dobrý návrh odpovídá čtyřem otázkám:

1. Odkud se vzduch nasává?
2. Čím projde?
3. Kde uvolní teplo?
4. Kam se vrací?

Pro komoru nebo sušičku je užitečná cirkulace v uzavřené smyčce:

```text
komora -> ventilátor -> topidlo -> horký proud -> komora -> návrat
```

Pro filtr se může uplatnit jiná logika:

```text
komora -> filtr -> ventilátor -> výfuk nebo návrat
```

Hlavní je, aby proud nechodil nejjednodušší zbytečnou cestou kolem topidla nebo filtru. Vzduch si vždy vybere cestu s nejmenším odporem.

## Teplotní senzor musí vidět správné místo

Špatné možnosti:

- senzor je přímo u topidla a vidí místní přehřátí;
- senzor je v mrtvé zóně a vidí chladný kout;
- senzor se dotýká kovové stěny a měří stěnu, ne vzduch;
- senzor je umístěn před topidlem, přestože teplota za ním záleží;
- senzor je foukán proudem, který neodráží teplotu v komoře.

U komory je obvykle užitečné měřit vzduch tam, kde by měla být teplota ovladatelná, ale ne přímo u topidla. Na ochranu před přehřátím u topidla je potřebný samostatný senzor nebo nezávislý termostat/tepelná pojistka.

Jeden senzor pro ovládání a jeden nezávislý nouzový prvek je mnohem lepší než jeden senzor zodpovědný za všechno.

## Filtry a sítě mohou zabít průtok

Filtr, síť, dekorativní mříž nebo úzká mezera přidávají odpor.

Typické chyby:

- husty filtr na slabém axiálním ventilátoru;
- částečné zablokování vstupu dekorativní síti;
- ostrá zatáčka hned za ventilátorem;
- umístění topidla tak, aby kolem něj vzduch procházel;
- zapomenutí, že filtr se ucpává prachem a odpor roste;
- zanechání přístupu pro údržbu filtru.

Pokud zařízení závisí na průtoku, zkontrolujte nejen „ventilátor se otáčí", ale i to, že vzduch skutečně procházejícího správnou cestou.

## Co se stane, když ventilátor selže

Nejnebezpečnější scénář pro topidlo s proudem vzduchu:

```text
ventilátor zastavil -> topidlo pokračuje -> místní teplota rychle stoupá
```

Proto topidlo, které se opírá o proud vzduchu, potřebuje opatření:

- nezávislou ochranu před přehřátím blízko horké zóny;
- omezení výkonu;
- materiál s teplotní rezervou;
- vzdálenost od topidla k plastu a izolaci;
- řízení tachometru ventilátoru, pokud je ventilátor kritický;
- kontrola topidla v firmwaru, pokud používáte Klipper nebo podobné;
- první test pod dohledem.

Firmware pomáhá, ale nenahrazuje fyzickou ochranu. MOSFET, SSR nebo relé mohou selhat v zapnutém stavu.

## Minimální kontrola po montáži

Po stavbě topného zařízení zkontrolujte:

- směr proudu;
- je tam průtok na výstupě, ne jen otáčení ventilátoru;
- teplota u topidla;
- teplota po topidlu;
- teplota ve vzdálené části komory;
- teplota vodičů, svorek a tištěných dílů;
- teplota ventilátoru;
- chování s částečně zablokovaným filtrem;
- vypne se topidlo, pokud senzor selže;
- aktivuje se nezávislá ochrana proti přehřátí v nebezpečném scénáři.

První zahřátí proveďte pod dohledem. Měření je lépe provádět po stabilizaci a po delší dobu provozu, protože kryt, upevnění a izolace se zahřívají pomaleji než vzduch.

## Připojení ke Klipperu

V Klipperu je několik užitečných mechanismů:

- `heater_fan` - ventilátor se zapne s topidlem nebo když je dosažena teplota;
- `temperature_fan` - ventilátor je řízen samostatným teplotním senzorem;
- `verify_heater` - kontroluje, že topidlo se chová očekávaně;
- `tachometer_pin` pro ventilátor - umožňuje vidět otáčky, pokud ventilátor podporuje signál tachometru.

Toto není úplné bezpečnostní schéma, ale dobrá úroveň kontroly pro zařízení, kde jsou teplota a průtok důležité.

## Hlavní poznámka

V topném zařízení nezáleží pouze na výkonu topidla, ale i na cestě vzduchu. Dobrý průtok odebírá teplo z topidla a přenáší jej do komory. Špatný průtok zanechává horké místo, klamá senzor a zvyšuje riziko přehřátí materiálu.

Pokud topidlo závisí na ventilátoru, selhání ventilátoru musí být samostatný nouzový scénář, ne překvapení.

## Zdroje na téma

- [Engineering ToolBox: Konvektivní přenos tepla](https://www.engineeringtoolbox.com/amp/convective-heat-transfer-d_430.html) - vysvětlení přirozené a vynucené konvekce.
- [SANYO DENKI: Průtok ventilátoru a statický tlak](https://techcompass.sanyodenki.com/en/training/cooling/fan_basic/004/index.html) - proč maximální průtok a maximální tlak z katalogu se nerovnají skutečnému provozu zařízení.
- [SANYO DENKI: Pokyn pro výběr ventilátoru](https://products.sanyodenki.com/info/sanace/en/technical_material/select.html) - praktický přístup k volbě ventilátoru podle tepelného výkonu, nárůstu teploty a skutečných testů.
- [DigiKey: Výběr ventilátoru](https://www.digikey.com/en/articles/selecting-a-fan) - rozdíl mezi axiálními a odstředivými ventilátory, vliv krytu a odporu toku.
- [Dokumentace Klipperu: Odkaz na konfiguraci](https://www.klipper3d.org/Config_Reference.html) - parametry pro `heater_fan`, `temperature_fan`, `verify_heater` a tachometr ventilátoru.

## Viz také

- [iDryer dokumenty: Připojení ventilátoru](../06-practical-guides/01-connecting-fan.md) - místní pokyn o napájení ventilátoru, MOSFET, společné GND a příklady Klipperu.
