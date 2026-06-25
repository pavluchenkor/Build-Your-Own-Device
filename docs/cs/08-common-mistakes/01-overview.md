# Časté chyby

Tato část není určena k posouzení vás.

Pomáhá vám rychle identifikovat běžné chyby v DIY zařízení: padající zdroj napájení, volný drát, senzor, který ukazuje nesmysly, řadič se restartuje, topidlo se chová podivně.

Formát sekce je přímočarý:

- příznak;
- pravděpodobná příčina;
- co zkontrolovat;
- co nedělat;
- jak bezpečně opravit.

## Hlavní pravidlo diagnostiky

Pokud se zařízení chová podivně, okamžitě neměňte firmware, neresoldujte vše a nezvyšujte výkon.

Nejdříve ověřte základy:

1. zdroj napájení;
2. polarita;
3. společná `GND`;
4. terminály a konektory;
5. senzory;
6. spínače výkonu;
7. firmware a konfigurace.

Většina problémů v jednoduchých zařízeních se ukazuje jako ne "komplexní elektronika", ale zdroj napájení, zapojení nebo nesprávná připojení.

## Kdy zastavit

Okamžitě vypněte napájení, pokud:

- se objeví vůně pálení;
- drát se zahřívá;
- terminál se zahřívá;
- konektor tmavne;
- kryt se stal horký na neočekávaném místě;
- topidlo se nechce vypnout;
- přerušovač nebo pojistka se vypíchne;
- teplotní senzor zobrazuje nesmysly;
- zařízení funguje pouze když pohybujete drát.

Nedělejte "zapálit znovu, abychom se podívali". Pokud se něco zahřívá, páchne nebo jiskří, najděte nejdříve příčinu bez napájení.

## Hlavní skupiny chyb

V této sekci jsou chyby rozděleny do skupin:

- `02-power-mistakes.md` - slabý zdroj napájení, nesprávné napětí, pokles, tenké dráty, bez rezervy.
- `03-wiring-mistakes.md` - obrácená polarita, špatné terminály, bez společné země, špatné konektory.
- `04-controller-mistakes.md` - nevhodný řadič, logika 3,3V/5V, GPIO místo výstupu výkonu, nesprávný firmware.
- `05-heater-ssr-mistakes.md` - topidla, SSR, MOSFET, 110-230V AC, teplotní senzor, chladiče a ochrana.
- `06-diagnostic-checklist.md` - obecné pořadí ověřování, když zařízení nefunguje.

## Proč se nejdřív kontroluje zdroj napájení

Zdroj napájení ovlivňuje téměř vše.

Pokud je zdroj napájení slabý nebo dráty tenké, příznaky mohou vypadat jako problém s firmwarem:

- řadič se restartuje;
- Wi-Fi vypadne;
- obrazovka bliká;
- servo se trhá;
- ventilátor se nespustí;
- senzory zobrazují náhodné hodnoty;
- topidlo topí slabě.

Dokud se zdroj napájení nezkontroluje s multimetrem pod zátěží, je obtížné se sebou diagnostikovat vše ostatní.

## Proč je zapojení důležitější, než se zdá

Špatné spojení může pracovat "téměř normálně".

To je přesně to, co je nebezpečné:

- dnes funguje;
- při vibracích se odpojí;
- když se zahřeje, kontakt se zhorší;
- terminál postupně tmavne;
- drát začíná se zahřívat;
- senzor se objevuje a mizí.

Pokud se zařízení změní chování, když pohybujete drát, nejedná se o chybu softwaru. Jedná se o problém s připojením.

## Proč se ochrana nesmí vypínat

Tepelný únik, `MINTEMP`, `MAXTEMP`, `topidlo se neohřívá` a podobné chyby existují ne proto, aby se obtěžovalo uživatele.

Jsou to znamení, že řadič již nedůvěřuje odečtu teploty nebo vidí nebezpečné chování vytápění.

Špatná myšlenka:

- vypnout tepelnou ochranu;
- rozšířit teplotní limity bez pochopení důvodu;
- nahradit pojistku větší;
- zkratovat termostat přímo;
- zkratovat ochranu "k testování".

Správná myšlenka: najít důvod, proč se ochrana aktivuje.

## Jak číst tuto sekci

Pokud zařízení vůbec nefunguje, začněte se seznamem diagnostiky.

Pokud je příznak jasný, přejděte na relevantní článek:

- restartování, blikání, slabé topidlo - zdroj napájení;
- funguje, když pohybujete drát - zapojení;
- řadič není detekován nebo piny nereagují - řadič;
- topidlo se nechce vypnout nebo SSR se zahřívá - topidlo a SSR;
- vše je nejasné - obecný seznam.

## Klíčové body

- Většina chyb začíná napájením, zapojením a nesprávnými připojeními.
- Pokud se něco zahřívá, páchne nebo tmavne, vypněte napájení.
- Diagnostika probíhá od jednoduchého ke složitému.
- Ochrana firmwaru a hardwaru se nesmí vypínat pro pohodlí.
- Sítě střídavého proudu 110-230V se nemohou diagnostikovat "na stole" bez pochopení elektrobezpečnosti.

## Reference

- [SparkFun: Tipy pro řešení problémů](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - základní přístup ke kontrole připojení, napájení, vytápění a hardwarových problémů.
- [SparkFun: Jak napájet projekt](https://learn.sparkfun.com/tutorials/how-to-power-a-project/voltagecurrent-considerations) - napětí, proud a výběr napájení pro elektronický projekt.
- [Tom's Hardware: Jak opravit tepelný únik 3D tiskárny](https://www.tomshardware.com/3d-printing/how-to-fix-3d-printer-thermal-runaway) - praktická analýza teplotního senzoru, topidla, ventilátoru, zdroje napájení a zapojení během tepelného úniku.
- [Klipper Configuration Reference: verify_heater](https://www.klipper3d.org/Config_Reference.html#verify_heater) - oficiální ověření topidla a kontrola teplotního senzoru podle očekávaného nárůstu teploty a akumulované chyby.
- [Průvodce měřičem napájení SparkFun Qwiic](https://docs.sparkfun.com/SparkFun_Qwiic_Power_Meter_ACS37800/hardware_assembly/) - příklad potřeby společné `GND` při měření/řízení externí zátěže.
