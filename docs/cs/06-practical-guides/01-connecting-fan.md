# Připojení ventilátoru

Ventilátor se zdá být jednoduchou součástkou: aplikujte napájení a otáčí se.

V praxi vznikají problémy ze čtyř věcí:

- výběr ventilátoru s nesprávným napětím;
- připojení jej k slabému výstupu kontroléru;
- nepochopení rozdílu mezi ventilátory se 2, 3 a 4 piny;
- umístění ventilátoru tam, kde mu chybí tlak kvůli filtru, mřížce nebo potrubí.

V zařízeních podobných iDryer-u je ventilátor obvykle potřebný pro cirkulaci vzduchu, chlazení topidla, výfuk komory, filtraci nebo chlazení elektroniky.

## Co kontrolovat před připojením

Před připojením najděte parametry ventilátoru:

- napětí: `5V`, `12V` nebo `24V`;
- proud nebo výkon;
- typ konektoru: 2-pin, 3-pin nebo 4-pin;
- schopnost řízení PWM;
- přítomnost tachometrického signálu;
- průtok vzduchu;
- statický tlak;
- úroveň hluku;
- pracovní teplota.

Tato data se nacházejí na štítku, stránce produktu nebo v technickém listu.

Například list technických dat ventilátoru obvykle obsahuje nejen napětí a proud, ale také průtok vzduchu, statický tlak, hluk `SPL dB(A)`, pracovní teplotu a dobu údržby. Ty jsou užitečnější než výběr ventilátoru pouze podle velikosti.

## Nenapájejte ventilátor z GPIO

GPIO kontroléru je řídicí signál, ne výstup napájení.

Nikdy nenapájejte ventilátor přímo z GPIO. To může poškodit kontrolér nebo způsobit restartování při spuštění ventilátoru.

Správná logika je:

- ventilátor přijímá napájení ze zdroje napájení nebo výstupu napájení desky;
- kontrolér pouze spravuje zapnutí/vypnutí nebo rychlost;
- pokud je použit externí modul MOSFET, `GND` zdroje napájení a `GND` kontroléru musí být společné.

![N-kanálový MOSFET v režimu spínání (spodní strana) pro řízení zátěže](../../img/01-electronics-basics/02-nmos-switch-operation.png)

*Zdroj: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:NMOS_PWR_WHOLE.PNG), KjellElec, CC BY-SA 4.0*

## Nejjednodušší možnost: 2-pin ventilátor

2-pin ventilátor obvykle má pouze:

- `+` napájení;
- `-` napájení.

Pokud je to 24V ventilátor, jej na 24V. Pokud je to 12V ventilátor, jej na 12V.

Pro jednoduché řízení zapnutí/vypnutí můžete použít:

- vyhrazený výstup ventilátoru na desce, pokud je vhodný pro potřebné napětí a proud;
- externí modul MOSFET pro DC zátěže;
- samostatný regulátor ventilátoru.

Pokud by měl ventilátor běžet nepřetržitě, lze jej připojit přímo na příslušný zdroj napájení skrz pojistku nebo chráněnou linku napájení. Ale v zařízení s topidlem je často lepší, aby byl ventilátor řízen kontrolérem jako součást bezpečnostní logiky.

## 3-pin ventilátor

3-pin ventilátor obvykle má:

- napájení;
- zem;
- tachometrický signál.

Tachometrický signál vám umožňuje monitorovat otáčky RPM ventilátoru. Neřídí rychlost sám o sobě.

Rychlost 3-pin ventilátoru se obvykle změní snížením napájecího napětí nebo PWM na napájecí lince, pokud konkrétní deska a ventilátor to podporují. Ale tato metoda může fungovat hůře než správné 4-pin PWM: ventilátor může skřípat, selhat při nízké rychlosti nebo pracovat nestabilně.

Pokud řízení rychlosti není potřebné, lze 3-pin ventilátor používat jako běžný 2-pin: napájení a zem jsou připojeny, tachometrický vodič se nepoužívá.

## 4-pin PWM ventilátor

4-pin PWM ventilátor obvykle má:

- zem;
- napájení;
- tachometrický signál;
- signál řízení PWM.

Klíčový rozdíl: napájení ventilátoru je aplikováno nepřetržitě a rychlost se nastavuje odděleným PWM signálem.

To je správný způsob, jak řídit počítačové PWM ventilátory. Nepředpokládejte, že 4-pin ventilátor musí být řízen neustálým přepínáním napájení. Pro správný PWM ventilátor by měl řídicí signál jít na samostatný PWM pin.

Počítačové 4-pin PWM ventilátory často mají řídicí vstup určený pro open-collector/open-drain signály s interním pull-upem, ne jakékoli napětí z GPIO. Neaplikujte `12V` nebo `24V` na PWM pin. Zkontrolujte dokumentaci ventilátoru; pokud je vyžadován open-drain/open-collector, použijte vhodný výstup tranzistoru nebo režim GPIO.

U mnoha 4-pin PWM ventilátorů je typická frekvence PWM kolem `25 kHz`. Některé ventilátory fungují v blízké oblasti, ale při příliš nízké nebo příliš vysoké frekvenci se mohou chovat nepředvídatelně: běh na plný výkon, zastavení nebo vydávání hluku.

Pokud není připojen PWM vodič, mnoho 4-pin ventilátorů běží na plný výkon.

## Společná GND / společná záporná

Pokud je ventilátor napájen samostatným zdrojem napájení a PWM signál pochází z kontroléru, je potřeba společná `GND` / společná záporná.

Bez společné `GND` nemají kontrolér a ventilátor společný referenční úroveň. Výsledkem je, že PWM nemusí fungovat nebo funguje přerušovaně.

Jednoduché pravidlo:

- kladné napájení ventilátoru pochází z příslušného zdroje napájení;
- záporné napájení ventilátoru je připojeno k zápornému zdroji napájení;
- `GND` kontroléru je připojen ke stejné záporné;
- řídicí signál funguje pouze se společným uzemněním.

## Výběr ventilátoru pro úkol

Pro otevřené chlazení záleží na průtoku vzduchu.

Pro filtr, chladič, těsnou mřížku, dlouhé potrubí nebo úzký kanál je důležitější statický tlak.

Takže pro tiskárenský filtr komory nemusí běžný tichý ventilátor pouzdra stačit. Bude dobře foukati ve volném vzduchu, ale sotva prohání vzduch skrz HEPA filtr, uhlíkovou vrstvu nebo úzký kanál.

Pokyny:

- pro volnou cirkulaci vzduchu se podívejte na `CFM` nebo `m³/h`;
- pro filtry, chladiče a potrubí je statický tlak nezbytný;
- pro tichý provoz se podívejte nejen na `dB(A)`, ale také na montáž, mřížku a vibrace;
- pro ohřevanou komoru se podívejte na pracovní teplotu ventilátoru.

## Počáteční proud a rezerva

Když se ventilátor spustí, může krátce odebrat více proudu než během normálního provozu.

Pokud je více ventilátorů připojeno na jeden výstup, jejich proudy se sčítají.

Zkontrolujte:

- maximální výstupní proud desky;
- proud jednoho ventilátoru;
- celkový proud všech ventilátorů;
- alespoň 50% rezerva;
- ohřev terminálů, vodičů a modulu MOSFET během dlouhodobého provozu.

Například pokud jeden ventilátor odebere `0.25A`, čtyři takové ventilátory odebírají přibližně `1A` bez zohlednění počátečního proudu.

## Příklad: připojení skrz modul MOSFET

Typický obvod pro 12V nebo 24V ventilátor:

1. Kladný zdroj napájení jde na kladný ventilátor.
2. Záporný ventilátor jde na výstup napájení modulu MOSFET.
3. Záporný zdroj napájení jde na modul MOSFET.
4. `GND` kontroléru je připojen k zápornému zdroji napájení.
5. Řídící pin kontroléru jde na vstup modulu MOSFET.

Toto se nazývá nízkostrannné spínání: MOSFET přerušuje záporný prvek zátěže.

Pro jednoduchý 2-pin ventilátor je to standardní a jasná možnost, pokud je modul MOSFET vhodný pro potřebné napětí a proud. U 3-pin/4-pin ventilátoru s tachometrem nebo samostatným PWM vstupem není "přerušení záporného prvku" vždy dobré: monitorování RPM a native PWM řízení obvykle vyžadují konstantní společnou `GND`.

## Příklad konfigurace Klipperu

Názvy pinů v příkladech nejsou univerzální. Před kopírováním zkontrolujte rozpis pinů vaší desky: nesprávný `pin` může aktivovat nesprávný výstup.

Pokud je ventilátor připojen k řízenému výstupu a měl by být ovládán ručně:

```ini
[fan_generic chamber_fan]
pin: PA8
max_power: 1.0
shutdown_speed: 0.0
kick_start_time: 0.5
off_below: 0.15
```

Řízení:

```gcode
SET_FAN_SPEED FAN=chamber_fan SPEED=1.0
SET_FAN_SPEED FAN=chamber_fan SPEED=0.4
SET_FAN_SPEED FAN=chamber_fan SPEED=0
```

Pokud by se měl ventilátor vypnout na základě teploty komory:

```ini
[temperature_fan chamber_exhaust]
pin: PA8
max_power: 1.0
shutdown_speed: 0.0
kick_start_time: 2.0
off_below: 0.15
sensor_type: NTC 100K beta 3950
sensor_pin: PA0
min_temp: 0
max_temp: 80
target_temp: 45
control: watermark
```

Názvy pinů jsou zde typické. V reálném zařízení zkontrolujte rozpis pinů vaší desky.

## Co kontrolovat po připojení

Před dlouhodobým provozem ověřte:

- ventilátor se otáčí správným směrem;
- napětí odpovídá ventilátoru;
- modul MOSFET se nepřehřívá;
- terminálu se nepřehřívají;
- vodiče nejsou příliš tenké pro vybraný proud;
- ventilátor se spustí po úplném zastavení;
- bez skřípání nebo zasekávání při nízké rychlosti;
- průtok vzduchu prochází potřebnou oblastí, ne kolem ní;
- mřížka, filtr nebo kryt neznečišťuje průtok více, než bylo očekáváno.

Pokud je ventilátor blízko topidla, testujte jej při skutečné teplotě komory. Ventilátor, který funguje dobře na lavici, se může rychle degradovat v horkém pouzdře.

## Běžné chyby

- připojení 12V ventilátoru na 24V;
- připojení 24V ventilátoru na 12V a rozhodnutí, že je rozbité;
- napájení ventilátoru z GPIO;
- zapomenutí společné zemi mezi kontrolérem a Externí napájením;
- očekávání PWM řízení od 3-pin ventilátoru;
- řízení 4-pin PWM ventilátoru přerušením napájení místo použití PWM pinu;
- nezohlednění celkového proudu více ventilátorů;
- výběr ventilátoru podle velikosti bez kontroly statického tlaku;
- umístění tichého ventilátoru na hustý filtr a získání téměř nulového průtoku;
- nekontrolování směru průtoku po instalaci;
- opuštění vodičů bez zajištění a získání oděru proti rotoru nebo pouzdru.

## Klíčové body

- Napětí ventilátoru musí odpovídat zdroji napájení.
- GPIO nenaápájí ventilátor, pouze jej řídí.
- Pro externí napájení je vyžadována společná zem s kontrolérem.
- 2-pin ventilátor se nejsnáze řídí přes výstup napájení nebo MOSFET.
- 3-pin přidávají tachometr, ale ne samostatný PWM vstup.
- 4-pin PWM se nejlépe řídí pomocí samostatného PWM signálu, ne přepínání napájení.
- Pro filtry a potrubí záleží statický tlak víc než krásné číslo `CFM`.
- Po montáži zkontrolujte nejen otáčení, ale skutečný průtok skrz konstrukci.

## Související čtení

- [Noctua: Nastavení PWM a monitorování RPM ventilátoru s mikrokontroléry](https://www.noctua.at/en/support/faqs/microcontroller-guide-pwm-setup-and-rpm-monitoring) - praktické vysvětlení 4-pin PWM, signálu RPM, společné zemi a typické frekvence PWM.
- [Odkaz na konfiguraci Klipperu: Ventilátory](https://www.klipper3d.org/Config_Reference.html#fans) - oficiální sekce `fan`, `heater_fan`, `controller_fan`, `temperature_fan` a `fan_generic`.
- [Dokumentace Voron: Teplota komory a výfukový ventilátor](https://docs.vorondesign.com/community/howto/alchemyEngine/chamber_temperature_exhaust_fan.html) - příklad řízení výfukového ventilátoru komory podle teploty v Klipperu.
- [DigiKey: Výběr ventilátoru](https://www.digikey.com/en/articles/selecting-a-fan) - výběr ventilátoru s ohledem na průtok vzduchu, statický tlak, odpor pouzdra a filtry.
- [SANYO DENKI: Příklad listu technických dat DC ventilátoru](https://products.sanyodenki.com/en/sanace/dc/dc-fan/109P0405F601/) - příklad skutečných parametrů: napětí, proud, průtok vzduchu, statický tlak, hluk, pracovní teplota a doba služby.
