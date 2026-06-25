# Kontrolní seznam diagnostiky

Tento kontrolní seznam je potřeba když zařízení nefunguje nebo se chová podivně.

Myšlenka je jednoduchá: nejdříve odstraňte nebezpečí, pak zkontrolujte napájení a zapojení, a až poté se přesunout na firmware, senzory a zátěž.

## 1. Zastavit a vypnout napájení

Nejdříve vypněte zařízení.

Zvláště pokud je zde:

- vůně;
- drát se zahřívá;
- terminál se zahřívá;
- kouř;
- zvláštní zvuk;
- jiskření;
- topidlo se nechce vypnout;
- přerušovač nebo pojistka se vypíchne.

Neměňte vodiče pod napájením.

## 2. Odpojit napájecí zátěž

Před diagnostikou je lépe dočasně odpojit:

- topidlo;
- výkonný LED pás;
- servo;
- motor;
- externí napájecí zátěž.

Nejdříve ověřte, že řadič a logika fungují bez nebezpečné zátěže.

Pokud má zařízení 110-230V AC, nedržejte otevřenou síťovou část pod napájením na stole.

## 3. Kontrola zdroje napájení

S multimetrem zkontrolujte:

- je na výstupu zdroje napájení napětí;
- je napětí správné;
- je polarita správná;
- pokles napětí pod zátěží.

Například:

- 24V vedení by mělo být zhruba 24V;
- 12V vedení by mělo být zhruba 12V;
- 5V vedení by mělo být zhruba 5V;
- 3,3V vedení by mělo být zhruba 3,3V.

Přijatelná odchylka závisí na zdroji napájení a zařízení, ale zřejmá chyba jako 24V místo 12V by měla být nalezena před připojením zátěže.

## 4. Kontrola polarity

Zkontrolujte kde je plus a kde minus.

Nesdoléhejte se pouze na barvu vodiče.

Zkontrolujte:

- označení řadiče;
- označení zdroje napájení;
- pinout modulu;
- multimetr;
- schéma zapojení.

Obrácená polarita často okamžitě zabije modul.

## 5. Kontrola společné GND

Pokud je zde externí modul nebo samostatné napájení, zkontrolujte společný `GND`.

To je důležité pro:

- MOSFET modul;
- servo;
- PWM ventilátor;
- HX711;
- RFID;
- externí senzory;
- samostatný DC-DC.

Pokud signály jdou mezi zařízeními, musí mít společnou referenční úroveň, pokud obvod nepoužívá speciální izolaci.

## 6. Kontrola terminálů a konektorů

Prohlédněte si:

- drát je vložen až do konce;
- vodič je upnut, ne izolace;
- bez exponovaných vodičů;
- bez otmavlení;
- bez vůně;
- terminál se netřese;
- konektor nekupuje "na víře";
- kryt pouzdra nepřitíská drát.

Pohybujte vodiči s vypnutým napájením. Pokud kontakt jasně poklesne mechanicky, nejdříve opravte zapojení.

## 7. Kontrola řadiče bez zátěže

Připojte řadič bez napájecí zátěže.

Zkontrolujte:

- je detekován přes USB;
- spouští se firmware;
- je komunikace s hostitelem;
- mikrokontrolér se nezahřívá;
- napájení se nehoupe;
- jsou viditelné logy.

Pokud řadič není detekován ani bez zátěže, nepřipojujte topidlo a napájecí moduly, dokud nenajdete příčinu.

## 8. Kontrola firmwaru a konfigurace

Zkontrolujte:

- firmware je vytvořen pro správný řadič;
- je vybrána správná sériová/CAN/USB cesta;
- piny v konfiguraci odpovídají pinoutu;
- `sensor_type` je správný;
- `min_temp` a `max_temp` jsou rozumné;
- výstupy nejsou omylem invertované;
- žádné konflikty pinů.

Pokud se topidlo chová opačně po změně konfigurace, například "vypnut", ale teplota stoupá, vypněte napájení a zkontrolujte konfiguraci a napájecí obvod.

## 9. Kontrola senzorů

Před topením zkontrolujte senzory.

Pro termistor:

- teplota jako pokojová teplota;
- bez `MINTEMP`;
- bez `MAXTEMP`;
- odečty se neskáčou;
- odpor jak se očekávalo;
- když se senzor ohřeje rukou, odečty se změní správně.

Pro ostatní senzory:

- napájení správné;
- rozhraní vybrané správně;
- adresa nebo piny odpovídají konfiguraci;
- vodiče jsou krátké a nevisí.

## 10. Kontrola výstupu bez zátěže

Pokud je třeba zkontrolovat MOSFET, relé nebo výstup řadiče, udělajte to nejdříve bez nebezpečné zátěže.

Možnosti:

- malý testovací ventilátor;
- LED s odporem;
- multimetr;
- slabá bezpečná zátěž.

Nezačínejte diagnostiku s výkonným topidlem.

Pro topidlo, před prvním zapnutím, je užitečná číselná kontrola: změřte odpor a porovnejte s očekávaným `R = U^2 / P`. Pokud je kovové pouzdro nebo `PE`, zkontrolujte žádný zkrat na pouzdro. Pro topidlo `12V`/`24V` je první běh lepší přes laboratorní zdroj napájení s omezením proudu nebo dočasnou pojistkou.

## 11. Kontrola spínače napájení samostatně

Pro MOSFET/SSR/relé zkontrolujte:

- správný typ zatížení: AC nebo DC;
- správné napětí;
- správné terminály;
- řídící vstup;
- společný `GND` pokud je potřeba;
- chladič pokud je potřeba;
- vstup a výstup nejsou zaměněny.

AC SSR a DC SSR nemohou být zaměněny.

Pro SSR samostatně zkontrolujte stav "vypnut": když je řídící signál odstraněn, zátěž se nesmí zahřívat. Nejdříve lépe použijte bezpečnou malou zátěž, lampu nebo multimetr, ne hlavní topidlo.

## 12. Připojit zátěž s krátkou zkouškou

Když základní kontroly prošly, připojte zátěž krátce a pod dohledem.

Zkontrolujte:

- zátěž se zapne;
- zátěž se vypne;
- terminály se nezahřívají;
- vodiče se nezahřívají;
- MOSFET/SSR se nepřehřívá;
- senzor ukazuje realistickou teplotu;
- řadič se nerestartuje;
- pojistka se nevypíchne.

První test topidla by neměl být dlouhý a bez dozoru.

## 13. Kontrola po několika minutách provozu

Po několika minutách zkontrolujte:

- terminály;
- vodiče;
- zdroj napájení;
- MOSFET;
- SSR;
- pouzdro blízko topidla;
- odečty senzoru;
- stabilitu řadiče.

Pokud se něco nečekaně zahřálo, vypněte napájení a vraťte se k kontrole napájení, zapojení a spínače napájení.

## Co nedělat

Nemůžete:

- opakovaně zapínat zařízení pokud se něco zahřívá nebo páchne;
- držet 110-230V AC otevřeno na stole;
- měnit vodiče pod napájením;
- zvýšit pojistku "aby se nevypíchla";
- vypnout tepelnou ochranu k testování;
- zkratovat nouzový termostat;
- testovat výkonné topidlo bez teplotního senzoru;
- nechat první test bez dozoru.

## Krátké pořadí

Pokud potřebujete velmi krátké pořadí:

1. Vypněte napájení.
2. Odpojte napájecí zátěž.
3. Zkontrolujte napětí zdroje napájení.
4. Zkontrolujte polaritu.
5. Zkontrolujte společný `GND`.
6. Zkontrolujte terminály a vodiče.
7. Zkontrolujte řadič bez zátěže.
8. Zkontrolujte firmware a pinout.
9. Zkontrolujte senzory.
10. Zkontrolujte výstup bez nebezpečné zátěže.
11. Zkontrolujte MOSFET/SSR/relé.
12. Připojte zátěž s krátkou zkouškou.
13. Zkontrolujte zahřívání vodičů, terminálů a napájecích částí.

## Klíčové body

- Diagnostika začíná vypnutím napájení a snížením rizika.
- Napájecí zátěž je lépe odpojena pro základní kontroly.
- Napájení, polarita, `GND` a terminály se kontrolují před firmwarem.
- Topidlo se nemůže používat jako první indikátor testu.
- Pokud se ochrana aktivuje, najděte příčinu, ne vypínání ochrany.

## Reference

- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - základní sekvence kontroly připojení, napájení a hardwarových problémů.
- [SparkFun: How to Power a Project](https://learn.sparkfun.com/tutorials/how-to-power-a-project/voltagecurrent-considerations) - jak přemýšlet o napětí, proudu a napájení projektu.
- [Fluke: How to Measure Resistance with a Digital Multimeter](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-resistance) - bezpečné měření odporu na de-energizovaném obvodu.
- [Tom's Hardware: How to Fix 3D Printer Thermal Runaway](https://www.tomshardware.com/3d-printing/how-to-fix-3d-printer-thermal-runaway) - praktické kontroly termistoru, topidla, ventilátoru, napájení a zapojení.
- [Klipper Configuration Reference: min_temp, max_temp and verify_heater](https://www.klipper3d.org/Config_Reference.html#verify_heater) - softwarové kontroly teploty, senzoru a očekávaného nárůstu teploty topidla.
