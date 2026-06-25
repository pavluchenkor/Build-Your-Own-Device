# Co je STL

STL je soubor obsahující geometrii 3D modelu.

Jednoduše řečeno: STL řekne sliceru, jaký tvar se má tisknout. Ale STL téměř nic neříká o tom, jak dělat součást silnou, odolnou vůči teplu a bezpečnou v reálném zařízení.

Proto tvrzení "mám STL soubor pouzdra" neznamená, že máte úplný návod na stavbu zařízení.

## Co STL ukládá

STL popisuje povrch modelu jako sadu trojúhelníků.

Slicer vezme tuto geometrii a převede ji na cesty tisku.

STL je užitečný, protože:

- téměř všechny slicery jej rozumějí;
- lze jej exportovat z nejvíce CAD programů;
- je jednoduché vyměnit model;
- je dobře vhodný pro jednu hotovou součást s jednoduchou geometrií.

Ale jednoduchost STL je také jeho limitace.

## Co STL neukládá

Typický STL neukládá:

- materiál;
- barvu;
- orientaci tisku;
- výšku vrstvy;
- výplň;
- počet stěn;
- nastavení teploty;
- typ podpory;
- upevnění;
- pokyny na montáž;
- tolerance;
- účel součásti;
- tepelná varování;
- informace o tom, kde bude součást slabší.

To znamená, že dva lidé mohou tisknout stejný STL a získat různé součásti.

Jeden by mohl vytisknout CHKO rychle a hezky. Druhý by mohl vytisknout ASA s více stěnami a správnou orientací. Součásti vypadají podobně zvenčí, ale vedle tepla se budou chovat odlišně.

## Proč to záleží pro topená zařízení

Pro ozdobný kryt je STL často dostačující.

Pro součást blízko topidla není.

Potřebujete vědět:

- z jakého materiálu jej tisknout;
- jaká teplota bude v okolí;
- bude součást držet zátěž;
- budou vodiče v okolí;
- změní se senzor, pokud se součást deformuje;
- bude součást blokovat průtok vzduchu;
- bude plast příliš blízko svorce nebo topidla.

Pokud je STL stažený bez informací o materiálu a pracovních podmínkách, nelze jej považovat za připravené řešení pro sušičku, tiskárenské komoru nebo topný modul.

## Orientace tisku změní pevnost

FDM součásti jsou složeny z vrstev.

Kvůli tomu může být stejný model:

- silný v jedné orientaci;
- slabý v jiné;
- náchylný k oddělení mezi vrstvami pod zátěží;
- špatný pro šroubové upevnění;
- pouze vhodný pro dekorativní použití.

Například tenká konzola může dobře držet zátěž, pokud vrstvy běží podél směru síly. Ale stejná konzola se může zlomit mezi vrstvami, pokud je tištěna jinak.

STL sám o sobě neříká, jak správně orientovat součást.

## Nastavení sliceru také záleží

I se správným materiálem a orientací, nastavení tisku ovlivňují výsledek.

Pro funkční součást jsou důležité:

- počet perimetrů;
- tloušťka stěny;
- horní a spodní vrstvy;
- procento výplně;
- teplota tisku;
- chlazení;
- podpory;
- šířka čáry;
- kvalita mezivrstevní adheze.

Vyšší výplň ne vždy řeší problém. Často pro kryt, konzolu nebo vzduchochod jsou důležitější stěny, perimetry, tvar součásti a směr zátěže.

## Co potřebujete před tiskem pracovní součásti

Pokud bude součást součástí zařízení, potřebujete víc než jen STL. Potřebujete krátkou sadu požadavků:

- materiál;
- orientaci na tiskové desce;
- doporučenou tloušťku stěny a výplň;
- zda jsou potřebné podpory;
- jaké šrouby a vložky usar;
- kde součást nemůže být blízko tepla;
- maximální pracovní teplota zóny;
- jak zkontrolovat přesnost po tisku;
- co dělat, pokud se součást deformuje.

To je zvláště důležité pro:

- konzolu topidla;
- vzduchochod;
- montáž ventilátoru;
- držák senzoru teploty;
- kryt elektroniky;
- konzolu svorky;
- součásti blízko 110-230V AC.

## STL, 3MF a projektové soubory

STL je nejjednodušší a nejkompatibilnější formát, ale ne nejúplnější.

Formát 3MF byl vytvořen jako modernější formát pro 3D tisk. Může ukládat více dat: nejen geometrii, ale i některé informace o materiálech, barvách, objektech a výrobních nastaveních.

Mnoho slicerů může také uložit projektový soubor. Takový soubor je užitečný, protože ukládá nejen model, ale i orientaci, nastavení tisku, modifikátory a umístění na tiskové desce.

Praktické pravidlo:

- STL je dobré pro předání tvaru;
- 3MF nebo projektový soubor sliceru je lepší pro předání záměru tisku;
- textové pokyny jsou stále potřeba, pokud součást ovlivňuje bezpečnost.

## Jak vyhodnotit stažený STL

Před tiskem staženého dílu si položte otázku:

1. Je jasné, z jakého materiálu jej tisknout?
2. Jsou tam nějaká tepelná varování?
3. Můžete vidět, v jaké orientaci byl tištěn?
4. Jsou tam fotografie skutečné součásti v montáži?
5. Jsou určeny šrouby, matice, vložky a tolerance?
6. Je jasné, jakou zátěž bude součást držet?
7. Existuje riziko, že by deformace mohla vytvořit nebezpečnou situaci?

Pokud nemáte odpovědi, součást lze použít jako nápadu nebo prototyp, ale ne jako zaručené bezpečné pracovní součásti.

## Běžné chyby

- zacházení se STL jako s kompletním návodem;
- tisk pracovní součásti z PLA, jen proto, že je snazší;
- nezměnění orientace tisku pro zátěž;
- použití příliš málo stěn a doufání, že vysoká výplň to vyřeší;
- nezohlednění teploty v pouzdru;
- nezkontrolování mezer po tisku;
- zašroubování do tenkých sloupů bez rezervy;
- použití staženého pouzdra blízko tepla bez pochopení materiálu;
- neopuštění přístupu údržbě po montáži.

## Klíčové myšlenky

- STL ukládá tvar, ne bezpečný způsob výroby součásti.
- Pro zařízení záleží materiál, orientace, stěny, upevnění a pracovní podmínky.
- Jeden STL může vést k slabé nebo silné součásti.
- Pro součásti blízko tepla potřebujete informace o materiálu a mezích teploty.
- Soubory 3MF nebo sliceru lépe sdělují nastavení, ale nenahrazují inženýrskou kontrolu.

## Reference

- [3MF Consortium: Formát souboru pro 3D tisk](https://3mf.io/) - proč byl 3MF vytvořen a jaké limity starých formátů řeší.
- [3MF Consortium Časté otázky: 3MF vs STL](https://3mf.io/resources/faq/) - krátké srovnání STL a 3MF: materiály, vlastnosti, topologie a rozšiřitelnost.
- [Prusa Knowledge Base: Podporované formáty souborů](https://help.prusa3d.com/article/supported-file-formats_1772) - které formáty podporuje PrusaSlicer a proč je 3MF používán jako upřednostňovaný formát projektů.
- [Xometry: Formát souboru STL](https://www.xometry.com/resources/3d-printing/stl-file-format/) - praktický popis STL a data, která neukládá: materiál, barvu, profil tisku a historii CAD.
- [Xometry: Formát souboru 3MF](https://www.xometry.com/resources/3d-printing/3mf-file-format/) - přehled 3MF jako modernějšího kontejneru pro výrobní data.
