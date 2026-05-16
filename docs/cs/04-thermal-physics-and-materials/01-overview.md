# Termální fyzika a materiály

Tato sekce je potřebná pro zařízení s topidlem, komorou, sušičkou vláken, filtrem s teplým vzduchem, vzduchov­ými kanály, ventilátory, izolací nebo tištěnými díly blízko vysokých teplot.

Zde nenajdete akademický fyzikální kurz. Cíl je praktický: pochopit, kam jde teplo, proč se skříň zahřívá nerovnoměrně, proč jeden materiál vyhovuje zdi komory, zatímco jiný se může změkčit, kouřit nebo se stát rizikem požáru.

## Proč je to důležité

V jednoduchém vyhřávaném zařízení nemůžete myslet jen takto:

```text
umístit topidlo -> stalo se to horké
```

V praxi musíte odpovědět na další otázky:

- kam jde teplo od topidla;
- kde se objeví horké místa;
- co vidí teplotní senzor;
- vydrží materiál delší dobu ohřevu;
- co se stane, když selže ventilátor;
- co se stane, když se MOSFET/SSR zasekne;
- skončí drát, svorka nebo plast v přehřáté zóně;
- existuje nezávislá ochrana před přehřátím.

Zařízení může na obrazovce ukazovat `45°C`, ale vedle topidla, svorky nebo uvnitř vzduchového kanálu to může být mnohem teplejší. Proto nezáleží pouze na cílové teplotě komory, ale také na lokálních teplotách částí.

## Tři způsoby, jak se teplo šíří

Teplo se přenáší třemi hlavními způsoby:

![Tři mechanismy přenosu tepla: vedení, konvekce a záření](../../../img/04-thermal-physics-and-materials/01-heat-transfer-kettle.png)

*Zdroj: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Kettle-convection-conduction-radiation.png), P.wormer, CC BY-SA 3.0*

**Tepelné vedení** - teplo prochází materiálem. Například kovová konzola rychle přenáší teplo z horké zóny do skříně.

**Konvekce** - teplo je přenášeno proudem vzduchu. Například ventilátor odvádí teplo od topidla a šíří jej po celé komoře.

**Záření** - horký povrch vyzařuje teplo pomocí infračerveného záření. Například silně zahřátý prvek může zahřát blízký plast i bez přímého kontaktu.

V reálném zařízení téměř vždy všechny tři mechanismy fungují současně.

## Materiál je součástí tepelného systému

Materiál skříně, zdi, vzduchového kanálu nebo montáže ovlivňuje tepelný režim.

Kov:

- vede dobře teplo;
- může rozptylovat teplo z horké zóny;
- může zahřát vnější povrch;
- sám o sobě neřeší problém izolace a elektrické bezpečnosti.

Plast:

- vede teplo špatně;
- může být vhodný pro skříň;
- může se změkčit a ztratit pevnost;
- může být hořlavý nebo kouřit při přehřátí.

Izolace:

- snižuje ztrátu tepla;
- pomáhá udržovat teplotu komory;
- může zesílit lokální přehřátí;
- vyžaduje ochrannou vrstvu a ověření bezpečnosti v případě požáru.

Neexistuje univerzální "nejlepší materiál". Existuje materiál vhodný pro konkrétní umístění, teplotu, zatížení a scénář selhání.

## Pracovní teplota není teplota tání

Začátečníci se často dívají pouze na teplotu tání. To je chyba.

Materiál se může stát nevhodným dříve:

- změkčit se;
- ztratit tvar;
- smrštit se;
- ztratit pevnost;
- začít kouřit;
- uvolnit produkty rozkladu;
- stát se více hořlavým.

Pro skříň, montáž nebo vzduchový kanál je důležitější přípustná pracovní teplota, teplota měknutí, požární vlastnosti a doporučení výrobce.

## Vzduch se musí pohybovat správně

Ventilátor v ohřávaném zařízení není tam "pro oko". Určuje, jak se teplo bude uvolňovat z topidla.

Bez správného průtoku:

- topidlo se může lokálně přehřát;
- komora se bude zahřívat nerovnoměrně;
- senzor nemusí ukazovat správnou teplotu;
- blízké díly mohou být horší, než se očekávalo;
- regulace PID se bude chovat hůře.

Ale ventilátor musí být také správně vybrán a instalován: průtok, statický tlak, směr, filtr, síťka a vzduchový kanál mohou zcela změnit výsledek.

## Co kontrolovat v jakémkoliv ohřávaném zařízení

Před montáží a prvním testem zkontrolujte:

- výkon topidla;
- teplota vedle topidla;
- teplota vzduchu za topidlem;
- teplota svorek a vodičů;
- teplota skříně a tištěných dílů;
- zda materiál vydrží pracovní teplotu s rezervou;
- zda není hořlavý materiál poblíž horké zóny;
- je tam pojistka;
- existuje nezávislá ochrana před přehřátím;
- co se stane, když selže ventilátor;
- co se stane, když selže teplotní senzor.

První test se provádí pod dohledem a s možností rychle odpojit napájení.

## Jak číst tuto sekci

Sekce se skládá ze tří praktických témat:

- [Tepelná vodivost](02-thermal-conductivity.md) - proč se kov, plast, sklo a izolace chová jinak.
- [Materiály, hořlavost a škodlivé emise](03-material-safety.md) - jak vybrat materiál poblíž tepla a co číst v datalistech.
- [Konvekce a průtok vzduchu](04-convection-and-airflow.md) - proč stejné topidlo funguje jinak s různými průtoky vzduchu.

## Hlavní poselství

Ohřívané zařízení není jen topidlo a senzor. Jedná se o tepelný systém: topidlo, vzduch, skříň, materiály, vodiče, svorky, ventilátor, senzory a havarijní ochrana.

Pokud je materiál pohodlný, levný a snadno se řeže, neznamená to, že lze být umístěn vedle topidla. Nejprve zkontrolujte teplotu, přenos tepla, vlastnosti požáru, dokumentaci a scénáře selhání.

## Materiály k tématu

- [U.S. Department of Energy: Principles of Heating and Cooling](https://www.energy.gov/energysaver/principles-heating-and-cooling) - jednoduché vysvětlení tepelného vedení, konvekce a záření.
- [NASA Glenn Research Center: Heat Transfer](https://www1.grc.nasa.gov/beginners-guide-to-aeronautics/heat-transfer-3/) - základní vysvětlení přenosu tepla z horkého tělesa na chladnější.
- [Engineering ToolBox: Conductive Heat Transfer](https://www.engineeringtoolbox.com/conductive-heat-transfer-d_428.html) - tepelné vedení, teplotní gradient, tloušťka materiálu a vícevrstvé stěny.
- [UL Solutions: Combustion Fire Tests for Plastics](https://www.ul.com/services/combustion-fire-tests-plastics) - proč jsou plastové materiály porovnávány podle chování při spalování, nejen podle teploty tání.

## Viz také

- [iDryer docs: Topidla](../03-common-components/02-heaters.md) - lokální článek o výběru topidla, spínači napájení, senzoru a nezávislé ochraně před přehřátím.
