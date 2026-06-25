# Chyby topidla a SSR

Topidlo je nejnebezpečnější zátěž v jednoduchém DIY zařízení.

Ventilátor se nemusí spustit. Senzor může dávat špatné odečty. Ale topidlo s chybou může přehřát pouzdro, rozpustit plast, poškodit zapojení nebo vytvořit riziko požáru.

Pokud má zařízení 110-230V AC a nerozumíte elektrobezpečnosti, správná akce je zastavit a zeptat se specialisty na pomoc.

## Příznaky

Nebezpečné příznaky:

- SSR se výrazně zahřívá;
- topidlo se nechce vypnout;
- teplota stoupá přestože je příkaz vypnut;
- teplota stoupá příliš rychle nebo nerozsáhlou;
- teplotní senzor zobrazuje špatnou hodnotu;
- terminál se otmavil;
- drát nebo konektor se zahřívá;
- přerušovač nebo pojistka se vypíchne;
- pouzdro páchne na plast nebo spalování;
- zařízení je nebezpečné se dotýkat;
- topidlo pokračuje po chybě řadiče.

Pokud se topidlo nechová podle očekávání, vypněte napájení.

## AC SSR a DC SSR zaměněno

SSR přichází pro různé typy zatížení.

AC SSR je pro střídavý proud. DC SSR je pro stejnosměrný proud.

Chyba:

- AC SSR umístěn na DC topidlo;
- DC SSR umístěn na 230V AC;
- koupen "SSR 40A" bez pochopení co je napsáno na pouzdru.

Špatný typ SSR nemusí vypnout zátěž nebo pracovat nebezpečně.

Před připojením ověřte:

- typ výstupu: AC nebo DC;
- povolené napětí zátěže;
- povolený proud;
- napětí řídícího vstupu;
- schéma zapojení výrobce;
- je potřeba chladič.

## SSR bez chladiče

SSR se zahřívá během provozu.

I když pouzdro říká velký proud, neznamená to, že relé to zvládne bez chladiče v uzavřeném pouzdru.

Kontrola:

- proud zátěže;
- úbytek napětí přes SSR;
- rozptýlený výkon;
- požadavky chladiče;
- teplota SSR pouzdra po provozu;
- je tam proudění vzduchu.

Pokud je SSR tak horký, že je těžko se ho dotýkat rukou, je to důvod zastavit a zjistit.

## MOSFET pro 110-230V AC

Běžné MOSFET moduly pro Arduino/ESP32 jsou obvykle pro DC zátěž: 12V nebo 24V.

Nemohou se používat jako jednoduchý spínač pro střídavou síť 110-230V.

Pro síťovou zátěž potřebujete jiné součásti, jinou izolaci, jiné terminály, uzemnění, pojistky a pochopení elektrobezpečnosti.

Pokud si nejste jisti, že vybraný modul je určen pro síťovou zátěž, nepřipojujte ho k síti.

## Bez pojistky

Pojistka nezjistí zařízení zcela bezpečné, ale omezuje důsledky některých selhání.

Špatné myšlenky:

- "Přidám to později";
- "zdroj napájení se bude chránit";
- "moje topidlo je malé";
- "pokud se pojistka vypíchne, dám větší".

Pojistka se volí pro obvod, zapojení a zátěž. Nemůže být zvýšena jen proto, že se vypíchne.

Pokud se pojistka vypíchne, najděte příčinu.

## Bez nezávislé tepelné ochrany

Firmware a teplotní senzor nejsou jedinou ochranou.

Pro topidlo je nezávislá ochrana hardwaru užitečná:

- termostat;
- tepelná pojistka;
- bimetalový spínač;
- samostatný nouzový vypínač napájení topidla.

Taková ochrana musí pracovat nezávisle na řadiči a firmwaru.

Pokud se řadič zaseká, pin zůstane v zapnutém stavu, SSR selže nebo senzor se odpojí, hardwarová ochrana může být poslední linií obrany.

## Teplotní senzor špatně upevněn

Topidlo je řízeno zpětnou vazbou ze senzoru.

Pokud senzor:

- je odpojen;
- špatně přidrženě;
- na špatném místě;
- nemá tepelný kontakt;
- ukazuje teplotu vzduchu místo topidla;
- je ve firmwaru vybrán špatný typ;

řadič může pokračovat v topení protože vidí špatnou teplotu.

Špatný tepelný kontakt je jedna z nejnebezpečnějších chyb v tepelných systémech.

## Špatný výkon topidla

Výkon topidla musí být vypočítán před připojením.

Příklad:

```text
24V 120W -> 5A
24V 240W -> 10A
230V 300W -> zhruba 1,3A
```

Pro nízkonapěťová výkonná topidla se proud rychle zvětší. To vyžaduje správné dráty, terminály, MOSFET/SSR a zdroj napájení.

Pro topidla na síti je proud menší ale nebezpečí úrazu je mnohem větší.

## Slabé terminály a vodiče

Terminál, který "nějak drží" se může zahřát pod proudem.

Důvody:

- špatný kontakt;
- upnutá izolace;
- drát příliš tenký;
- terminál není hodnocen na proud;
- vinutý drát bez ferrule se třepí;
- šroub uvolněn teplem a vibracemi.

Otmavlý terminál, vůně, zahřívání nebo měknutí plastu je důvod vypnout zařízení.

## Co nedělat

Nemůžete:

- držet otevřenou síťovou část pod napájením;
- měnit vodiče pod napájením;
- používat Arduino MOSFET modul pro 230V AC;
- používat SSR bez chladiče pokud je potřeba;
- vypnout tepelnou ochranu;
- zkratovat nouzový termostat;
- zvýšit pojistku "aby se nevypíchla";
- nechat topidlo bez dozoru při prvním testu;
- používat PLA montáž blízko topidla.

## Co zkontrolovat

Před prvním topením:

1. Napětí topidla.
2. Výkon a proud.
3. Typ spínače: MOSFET, AC SSR, DC SSR, relé.
4. Proudová rezerva.
5. Chladič SSR nebo MOSFET, pokud je potřeba.
6. Pojistka.
7. Uzemnění, pokud je potřeba.
8. Terminály a vodiče.
9. Montáž teplotního senzoru.
10. Správný `sensor_type` v firmwaru.
11. `min_temp` a `max_temp`.
12. Nezávislá tepelná ochrana.
13. Chování když je řadič vypnut.
14. Teplota terminálu a SSR po krátké zkoušce.

## Klíčové body

- Topidlo se nemůže testovat jako běžná malá zátěž.
- AC SSR a DC SSR jsou různá zařízení.
- SSR často vyžaduje chladič.
- MOSFET modul pro DC zátěž nefunguje pro 110-230V AC.
- Teplotní senzor musí být pevně upevněn na správném místě.
- Hardwarová tepelná ochrana musí být nezávislá na firmwaru.
- Pokud je vůně, zahřívání terminálu nebo neobvyklé chování topidla, vypněte napájení.

## Reference

- [Klipper Configuration Reference: verify_heater](https://www.klipper3d.org/Config_Reference.html#verify_heater) - oficiální ověřování topidla a kontrola teplotního senzoru podle míry nárůstu a akumulované chyby.
- [Tom's Hardware: How to Fix 3D Printer Thermal Runaway](https://www.tomshardware.com/3d-printing/how-to-fix-3d-printer-thermal-runaway) - kontrola termistoru, topného kartridže, ventilátoru, napájení a zapojení během tepelného úniku.
- [Marlin Configuration: Temperature Ranges and Thermal Protection](https://marlinfw.org/docs/configuration/configuration.html#temperature-ranges) - `MINTEMP`, `MAXTEMP` a tepelná ochrana jako součást bezpečnosti.
- [Sensata/Crydom SSR Heat Sink Selection](https://www.sensata.com/sites/default/files/a/sensata-ssr-heat-sink-selection-white-paper.pdf) - proč SSR vyžaduje tepelný výpočet a chladič při významných proudech.
- [Omron: Solid State Relay Basics](https://components.omron.com/us-en/products/basic-knowledge/relays/solid-state-relays) - základní informace o SSR, aplikaci, zahřívání a rozdílech od mechanických relé.
