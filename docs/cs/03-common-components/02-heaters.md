---
title: "Topná tělesa pro sušičky filamentu a vyhřívané komory"
description: "Jak vybrat topné těleso pro sušičku filamentu nebo aktivní komoru 3D tiskárny: 12V, 24V, síťové napájení, výkon, řízení a bezpečnost."
---

# Topná tělesa pro sušičky filamentu a vyhřívané komory

Topení určuje rychlost ohřevu i bezpečnostní limity celé sušičky nebo komory. Tato stránka vysvětluje typy topných těles, volbu výkonu, řízení přes MOSFET nebo SSR a chyby vedoucí k přehřátí.

Topné těleso je elektrická zátěž, která mění elektrickou energii na teplo. V jednoduchém DIY zařízení je to nejnebezpečnější součást: chyba v ventilátoru obvykle vede na špatný průtok vzduchu, ale chyba topení může vést k přehřátí, roztavení krytu, poškození drátů nebo riziku požáru.

V 3D tiskárnách a zařízeních podobných iDryer se topná tělesa nacházejí v trysce, tiskové podložce, komoře, sušičce filamentu, vzduchovodu nebo v samostatném topném modulu.

## Kde se používá

Typické úkoly:

- ohřev trysky;
- ohřev tiskové podložky;
- předehřátí komory tiskárny;
- sušení filamentu;
- předehřátí vzduchu před filtrem nebo potrubím;
- udržování teploty v malém pracovním objemu.

To jsou různé úkoly. Topné těleso pro kovovou trysku, silikonový topný polštář a vzduchový PTC modul nejsou zaměnitelné bez přepočtu výkonu, montáže, proudění vzduchu a ochrany.

## Typy topných těles

Obvyklé možnosti:

- patronové topné těleso;
- silikonový polštář;
- PTC topné těleso;
- keramický topný prvek;
- hotový modul topného ventilátoru;
- topná deska;
- síťové topné lůžko;
- nichromový nebo odporový prvek v hotovém krytu.

Patronové topné těleso se obvykle vkládá do kovového bloku. Vyžaduje dobrý tepelný kontakt s kovem a spolehlivou montáž teplotního čidla.

Silikonový polštář se obvykle lepí nebo přitlačuje na rovný povrch. Vyžaduje rovný povrch, dobrou adhezi, teplotní čidlo a ochranu před odlupováním.

PTC topné těleso částečně omezuje vznik teplotního nárůstu díky svým vlastnostem, ale to nenahrazuje regulátor, čidlo, pojistku, kryt a kontrolu průtoku vzduchu. PTC automaticky nečiní zařízení bezpečným.

Hotový modul topného ventilátoru spojuje topné těleso a průtok vzduchu, ale přesto musí být kontrolován na napětí, výkon, teplotu, materiály pouzdra a nouzovou ochranu.

## Napětí, výkon a proud

Před připojením musíte zjistit:

- provozní napětí;
- výkon;
- proud;
- typ proudu: DC nebo AC;
- maximální teplota;
- provozní teplota drátů;
- způsob montáže;
- požadavky na průtok vzduchu;
- povolená metoda řízení.

Proud se vypočítá podle vzorce:

```text
proud = výkon / napětí
```

Příklady:

```text
24V 120W -> 5A
24V 240W -> 10A
24V 300W -> 12.5A
230V 300W -> přibližně 1.3A
```

Nízkoapěťové vysokovýkonné topné těleso je bezpečnější z hlediska napětí, ale vyžaduje velké proudy. Velké proudy vyžadují správný zdroj napájení, vodiče, konektory, MOSFET/SSR a pojistku.

Síťové topné těleso na `110-230V AC` může dodávat vysoký výkon s nižším proudem, ale riziko úrazu proudem je mnohem vyšší. Pro část se síťovým napájením potřebujete znalost elektrické bezpečnosti, kryt, konektory, izolaci, uzemnění v případě potřeby, pojistky a gal vanickou izolaci řízení.

## Řízení topného tělesa

Regulátor by neměl napájet topné těleso přímo z GPIO. GPIO poskytuje pouze řídicí signál.

Typické možnosti řízení výkonu:

- MOSFET - pro DC topná tělesa `12V`/`24V`;
- DC SSR - pro DC topná tělesa, pokud je správně hodnoceno pro DC;
- AC SSR - pro síťová AC topná tělesa;
- elektromechanické relé - pro vzácné zapínání/vypínání, ne pro časté PID/PWM;
- hotový výstup výkonu - pouze pokud je hodnocen na potřebný proud a napětí.

AC SSR a DC SSR jsou různá zařízení. Nesprávný typ nemusí vypnout topné těleso nebo funguje nebezpečně.

Typický modul MOSFET pro Arduino/ESP32 nelze použít jako spínač `110-230V AC`. Pokud modul není navržen pro zátěž se síťovým napájením, nemůže být připojen do sítě.

## Vrstvy bezpečnosti

Topné těleso nelze navrhnout jako "regulátor ho zapne - regulátor ho vypne". Potřebujete více vrstev ochrany.

![Vrstvy bezpečného řízení topného tělesa](../../img/03-common-components/02-heater-safety-stack.svg)

Minimální logika:

- zdroj napájení je dimenzován na zadaný proud;
- pojistka je vybrána pro vodiče a zátěž;
- spínač výkonu odpovídá typu zátěže;
- teplotní čidlo je namontováno na správném místě;
- firmware má `min_temp`, `max_temp` a ověření topení;
- existuje nezávislá hardwarová tepelná ochrana: tepelná pojistka, termostat nebo bimetalový spínač;
- kryt a materiály vydrží skutečnou teplotu;
- první test se provádí pod dohledem.

Hardwarová tepelná ochrana musí fungovat nezávisle na regulátoru. V jednoduchém případě je umístěna v řadě v elektrickém obvodu topného tělesa, aby fyzicky přerušila napájení. To není jen další čidlo pro firmware.

Pokud se regulátor zaseká, čidlo se uvolní, MOSFET se zkratuje nebo SSR se zasekne, ochrana musí přerušit napájení topného tělesa.

## Teplotní čidlo

Topné těleso nezná svou vlastní teplotu. Regulátor dělá rozhodnutí na základě čidla.

Pokud čidlo:

- je špatně přitlačeno;
- je na špatném místě;
- se uvolní;
- je nesprávného typu v firmware;
- má špatný tepelný kontakt;
- měří vzduch namísto kritické součásti;

regulátor může pokračovat v topení, i když je skutečná teplota již nebezpečná.

U trysky je důležitý kontakt teplotního čidla s kovovým blokem. U vzduchového topného tělesa je důležité pochopit, co se měří: teplota prvku, teplota vzduchu za prvkem, teplota komory nebo teplota blízko cívky. Jedná se o různé body a mohou se výrazně lišit.

## Průtok vzduchu a přenos tepla

Topné těleso uvolňuje výkon, ale ten výkon musí bezpečně přejít na určené místo.

U vzduchového topného tělesa je průtok vzduchu kritický:

- bez průtoku se prvek může místně přehřát;
- slabá ventilace neodstraňuje teplo;
- ucpaný filtr mění režim topení;
- plastové potrubí se může změkčit;
- teplotní čidlo nemusí vidět, co se děje u prvku.

U topného tělesa komory je důležité kontrolovat nejen cílovou teplotu vzduchu, ale také teplotu v blízkosti topného tělesa, drátů, SSR/MOSFET, konektorů a plastových částí.

## Vodiče, konektory a pojistky

Topné těleso často běží po delší dobu a spotřebovává značný proud. Špatný kontakt se stává zdrojem tepla.

Zkontrolujte:

- průřez vodiče;
- třídu teploty izolace;
- jmenovitý proud konektoru;
- kvalitu krimpování;
- těsnost šroubů;
- ferrulové kroužky na měděném drátě;
- ochranu proti tahu;
- vzdálenost od horkých součástí;
- absenci exponovaných vodičů.

Pokud se konektor ztmavne, páchne, změkčí plast nebo se zahřeje, musíte vypnout napájení a zjistit příčinu. Nejen zvyšujte pojistku nebo ji později utahujte.

## Co zkontrolovat před nákupem

Před nákupem topného tělesa zkontrolujte:

- jaké médium by mělo být ohřáto: kov, vzduch, podložka, komora;
- napětí a typ proudu;
- výkon;
- proud;
- provozní teplota;
- maximální povrchová teplota;
- požadavky na průtok vzduchu;
- způsob montáže;
- materiál vodiče a izolace;
- kompatibilní spínač výkonu;
- místo pro teplotní čidlo;
- místo pro nezávislou tepelnou ochranu;
- kryt a okolní materiály;
- dostupnost technického popisu nebo jasné dokumentace.

Pokud stránka produktu postrádá informace o napětí, výkonu, teplotě a aplikaci, takové topné těleso není vhodné pro bezpečný první projekt.

## První test

První topení se provádí krátce a pod dohledem.

Postup:

1. Zkontrolujte odpor topného tělesa a porovnejte s výpočtem `R = U^2 / P`, pokud jsou známy napětí a výkon.
2. Zkontrolujte zkratování, pokud je to relevantní.
3. Pokud existuje kovový kryt nebo uzemnění `PE`, zkontrolujte, zda se topné těleso neshortuje na kryt.
4. Zkontrolujte napájecí napětí bez topného tělesa.
5. Zkontrolujte, zda spínač řízení vypne zátěž.
6. Zkontrolujte, zda teplotní čidlo čte rozumnou hodnotu.
7. Pro topné těleso `12V`/`24V`, pokud je to možné, spusťte přes laboratorní zdroj napájení s omezením proudu nebo dočasnou pojistkou.
8. Povolte topení při nízkém výkonu nebo krátce.
9. Sledujte, zda teplota stoupá na správném místě.
10. Zkontrolujte, že příkaz vypnutí skutečně zastaví topení.
11. Zkontrolujte zahřívání drátů, konektorů, MOSFET/SSR a krytu.
12. Zkontrolujte nouzovou ochranu scénářem, který můžete bezpečně simulovat.

Nenechávejte nové topné těleso bez dozoru při prvním spuštění.

## Typické chyby

- připojení topného tělesa na špatné napětí;
- nezapočítaný proud;
- napájení topného tělesa přes slabý konektor;
- použití MOSFET pro síťové AC topné těleso;
- záměna AC SSR a DC SSR;
- instalace SSR bez chladiče, když byl potřeba;
- zapomenutá pojistka;
- žádná nezávislá tepelná ochrana;
- špatná montáž teplotního čidla;
- kryt z PLA poblíž topného tělesa;
- nezapočítaný průtok vzduchu a ucpaný filtr;
- testování na pracovním stole, ale ne v krytu;
- vystavená část se síťovým napájením;
- zvýšení pojistky místo zjištění, proč se vypnula.

## Hlavní bod

Topné těleso se volí podle úkolu, napětí, výkonu, způsobu přenosu tepla a bezpečnosti. Nemůžete s tím zacházet jako s jednoduchou "dvouprvkovou zátěží".

Nejprve vypočítejte proud, vyberte spínač výkonu, vodiče a pojistku. Potom zajistěte teplotní čidlo, ochranu firmware, nezávislou hardwarovou tepelnou ochranu, správný kryt a testování v reálných podmínkách.

## Referenční materiály

- [Klipper Configuration Reference: heater_generic and verify_heater](https://www.klipper3d.org/Config_Reference.html#heater_generic) - nastavení topného tělesa, teplotní čidla, `min_temp`, `max_temp` a ověření topení v Klipper.
- [Marlin Configuration: Temperature Ranges and Thermal Protection](https://marlinfw.org/docs/configuration/configuration.html#temperature-ranges) - teplostní limity, `MINTEMP`, `MAXTEMP` a tepelná ochrana v Marlin.
- [Omron: Overview of Solid-state Relays](https://www.ia.omron.com/support/guide/18/introduction.html) - základní vysvětlení SSR, typy, aplikace a tepelná opatření.
- [Sensata/Crydom: SSR Heat Sink Reference](https://www.sensata.com/resources/brochure-solid-state-relays-heat-sink-reference) - proč SSR potřebuje chladič a jak se tepelný režim vztahuje k proudu zátěže.
- [Omega: Cartridge Heaters](https://www.omega.nl/prodinfo/cartridge-heaters.html) - praktické poznámky k aplikaci patronového topného tělesa, tepelný kontakt a výběr výkonu.
