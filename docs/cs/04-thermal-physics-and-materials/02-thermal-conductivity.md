# Tepelná vodivost

Tepelná vodivost určuje, jak snadno se teplo šíří materiálem.

V homemade sušičce, komoře, filtru, vzduchochladu nebo krytu není jde o abstraktní fyziku. Tepelná vodivost určuje, zda teplo unikne ven, zda se objeví horká místa u topidla, jak moc se zahřeje vnější stěna a zda se vytisknutá součást nezmění.

## Jednoduché vysvětlení

Teplo vždy tenduje unikat z teplejší zóny do chladnější. Čím vyšší je tepelná vodivost materiálu, tím snadněji jím teplo prochází.

Rychlost přenosu tepla je ovlivněna:

- materiálem;
- tloušťkou stěny;
- plochou kontaktu;
- rozdílem teplot;
- kvalitou kontaktu mezi díly;
- přítomností vzduchu, mezer a izolace.

Tenká hliníková deska může rychle rozšířit teplo po celém krytu. Silná vrstva minerální vlny nebo pěnové izolace naopak brání úniku tepla.

## Referenční hodnoty materiálů

Hodnoty níže slouží jen k pochopení řádů velikosti. Pro skutečnou stavbu si ověřte parametry konkrétního materiálu v jeho specifikaci.

| Materiál | Přibližná tepelná vodivost, `W/(m*K)` | Co to znamená v praxi |
| --- | ---: | --- |
| Měď | cca `400` | vynikající tepelný vodič, vhodný pro odvod tepla, ale rychle vede teplo tam, kde není potřeba |
| Hliník | cca `200-240` | dobře šíří teplo, vhodný jako deska, radiátor nebo tepelný rozvaděč |
| Ocel | cca `15-60` | vede teplo hůře než hliník, ale šrouby a nosné prvky mohou být tepelnými mosty |
| Sklo | cca `1` | vede teplo mnohem hůře než kov, ale není to izolace v klasickém slova smyslu |
| Běžné plasty | cca `0.1-0.5` | vedou teplo špatně, ale mohou měknuty a hořet |
| Minerální vlna, sklovlákno | cca `0.04` | efektivně snižuje tepelné ztráty, ale vyžaduje ochranu před prachem, vlhkostí a mechanickým poškozením |
| Expandovaný polystyrén / polyuretanová pěna | cca `0.03` | dobrá izolace, ale blízko tepla jsou důležité pracovní teplota a požární vlastnosti |
| Vzduch | cca `0.026` | sám o sobě vede teplo špatně, ale přenáší ho konvekcí při pohybu |

Hlavní závěr: kov a izolace se liší ne o faktor dva, ale o řády. Proto i malý kovový prvek může výrazně změnit tepelný obraz.

## Tepelný most

Tepelný most je cesta, kudy teplo uniká lépe než zbytkem konstrukce.

![Klasický tepelný most skrz obálkou](../../img/04-thermal-physics-and-materials/02-thermal-bridge-classic.png)

*Zdroj: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Pont_thermique_classique.png), AmisDeLaThermique, CC BY-SA 3.0*

Typické tepelné mosty:

- kovový šroub skrz izolovanou stěnu;
- hliníková deska připojená k vnějšímu krytu;
- kovový nosný prvek mezi horkou komorou a vnějším panelem;
- svorkovnice nebo upevnění blízko topidla;
- vzduchochod, který přímo dotýká horké části.

Tepelný most není vždy špatný. Někdy je potřebný k odvodu tepla z vypínače, radiátoru nebo horkého uzlu. Problém začíná, když je most neúmyslný: komora ztrácí teplo, vnější povrch se zahřívá a plast blízko mostu se zahřívá více než očekáváno.

## Kov: Chladič nebo náhodné zahřívání

Kov se hodí k použití v topených zařízeních:

- jako clona mezi topidlem a plastem;
- jako deska pro rozložení tepla;
- jako podklad pro upevnění topidla;
- jako chladič elektroniky;
- jako nehořlavý vnitřní povrch.

Ale kov nezaručuje bezpečnost zařízení automaticky. Pokud kovová deska dotýká horké zóny i vnějšího krytu, může vést teplo ven. Pokud je k ní přišroubován plast, tento plast se může zahřát přes upevnění. Pokud skrz ní procházejí vodiče, u okrajů potřebujete průchodky, ochranu před otěrem a teplotní rezervu pro izolaci.

## Izolace: Nižší ztráty, větší zodpovědnost

Izolace snižuje tepelné ztráty, ale neodstraňuje kontrolu teploty.

Když izolujete komoru:

- je pro topidlo snazší zvýšit teplotu;
- vnější stěna se může stát chladnější;
- zvyšuje se doba chladnutí;
- místní teplota u topidla může vzrůst;
- porucha ventilátoru nebo uvíznutý spínač se stává nebezpečnější.

Proto izolaci nelze přidávat jako „vylepšení" bez opětovného testování. Po izolaci musíte znovu měřit teploty uvnitř komory, u topidla, u vodičů, u svorek a na vnějším povrchu.

## Vzduchová mezera také funguje

Stojatý vzduch vede teplo špatně. Proto vzduchové mezery, dvojité stěny a pěnové materiály mohou snížit přenos tepla.

Ale pokud se vzduch začne pohybovat, vejde v platnost konvekce. Pak je teplo přenášeno proudem vzduchu, ne jen vedením. Proto mezera, kudy prochází horký proud, může zahřívat kryt více než silná stěna bez proudu.

V praxi to znamená:

- nenechávejte náhodné mezery blízko topidla;
- nevedete horký proud přímo na plast;
- nezpracovávejte vzduchové mezery jako ochranu, pokud jimi prochází proud;
- kontrolujte teplotu při skutečném provozu, ne jen na chladném zařízení.

## Co hledat v listu technických dat materiálu

Pro materiál blízko tepla není tepelná vodivost jedinou důležitou věcí.

Zkontrolujte:

- maximální kontinuální pracovní teplotu;
- teplotu měknutí nebo tepelné deformace;
- třída hořlavosti a chování v ohni;
- dovolení kontaktu s horkým vzduchem;
- chování lepidla, fólie, nátěru nebo laminace;
- doporučení výrobce k použití;
- dostupnost SDS/bezpečnostního listu, pokud se materiál může zahřívat nebo zpracovávat.

Pokud materiál nemá jasnou dokumentaci, neumisťujte jej blízko topidla a nepoužívejte jej jako jedinou ochranu.

## Praktický pořadí ověřování

Pro kryt, komoru nebo sušičku je vhodné postupovat takto:

1. Identifikujte horkou zónu: topidlo, výstup vzduchu, svorky, vypínač.
2. Oddělte horkou zónu od plastu kovem, keramikou nebo jiným vhodným materiálem.
3. Zkontrolujte, kam kov vede teplo.
4. Přidejte izolaci pouze tam, kde nepokrývá nebezpečné horké uzly.
5. Měřte teplotu na několika místech po zahřátí.
6. Zkontrolujte režim selhání ventilátoru, pokud topidlo závisí na proudu vzduchu.
7. Přidejte nezávislou ochranu před přehřátím tam, kde je to nebezpečné.

Jeden teplotní senzor v komoře neukazuje úplný obraz tepla. Potřebujete měření blízko topidla, na upevnění, na vodičích, na krytu a na tištěných dílech.

## Hlavní poznámka

Tepelná vodivost vám pomáhá pochopit, kam teplo skutečně jde. Kov může být užitečný chladič nebo náhodný tepelný most. Izolace může zlepšit účinnost, ale zároveň zesílí důsledky selhání.

Jakékoli změny krytu, izolace, upevnění nebo vzduchochladu musí být ověřeny měřením teploty při skutečném provozu.

## Zdroje na téma

- [Engineering ToolBox: Tepelná vodivost běžných materiálů](https://www.engineeringtoolbox.com/thermal-conductivity-d_429.html) - referenční hodnoty tepelné vodivosti kovů, plastů, vzduchu, skla a izolace.
- [Engineering ToolBox: Vedení tepla](https://www.engineeringtoolbox.com/conductive-heat-transfer-d_428.html) - vztah mezi průtokem tepla, materiálem, tloušťkou stěny, plochou a rozdílem teplot.
- [NASA Glenn Research Center: Přenos tepla](https://www1.grc.nasa.gov/beginners-guide-to-aeronautics/heat-transfer-3/) - základní vysvětlení přenosu tepla z horkého tělesa na studené.
- [U.S. Department of Energy: Principy vytápění a chlazení](https://www.energy.gov/energysaver/principles-heating-and-cooling) - jednoduché vysvětlení vedení tepla, konvekce, radiace a role izolace.
- [Prusa Knowledge Base: Tabulka materiálů](https://help.prusa3d.com/materials) - praktický odkaz na chování teploty populárních materiálů pro 3D tisk.
