# Chyby zdroje napájení

Zdroj napájení je první věc, kterou je třeba zkontrolovat, když se zařízení chová podivně.

Slabý zdroj napájení, tenký drát nebo špatný terminál mohou vypadat jako problém s firmwarem, Wi-Fi, senzorem nebo řadičem.

## Příznaky

Typické příznaky problémů se zdrojem napájení:

- řadič se restartuje;
- obrazovka bliká;
- Wi-Fi na ESP32 vypadne;
- ventilátor se spustí a zastaví;
- servo se trhá;
- topidlo topí slabě;
- USB zmizí, když se zátěž zapne;
- MOSFET, terminál nebo drát se zahřívá;
- senzory zobrazují nestabilní hodnoty;
- zařízení funguje bez zátěže, ale selhává, když je připojeno topidlo nebo motor.

Pokud se příznak objeví přesně, když se zátěž zapne, téměř vždy je třeba zkontrolovat zdroj napájení a zapojení.

## Zdroj napájení bez rezervy

Zdroj napájení nemůžete vybrat přesně na výkon zátěže.

Pokud zátěž spotřebuje `100W`, zdroj napájení `100W` bude pracovat na svém limitu. Může se přehřát, poklesne napětí a špatně zpracovává impulzní proudy.

Praktické pravidlo pro tuto část:

**minimální energetická rezerva je 50%, pokud dokumentace konkrétní součásti neuvádí více.**

Příklad:

```text
topidlo: 24V 120W
proud: 120W / 24V = 5A
minimální 50% rezerva: 7,5A
```

Zdroj napájení je tedy lépe zvolit alespoň `24V 7,5A`, a v praxi často větší, pokud existují ventilátory, řadič, osvětlení a další zátěže.

## Celkový proud není vypočítán

Musíte vypočítat ne jednu součást, ale celé zařízení.

Například:

- topidlo;
- ventilátory;
- servo;
- LED pás;
- řadič;
- displej;
- senzory;
- DC-DC měnič.

Proudy se sčítají. Je také třeba zohlednit impulzní proudy a krátké špičky.

Servo nebo ventilátor mohou krátce odebírat více než v normálním režimu. Pokud je rezerva malá, právě v tomto okamžiku se řadič restartuje.

## Zmatení 12V a 24V

Nejjednoduší a nejnebezpečnější chyba:

- ventilátor 12V zapojen do 24V;
- modul 5V zapojen do 12V;
- topidlo 24V se očekává normální práce z 12V;
- modul 3,3V napájen z 5V bez kontroly.

Před připojením ověřte:

- hodnocení zátěže;
- hodnocení zdroje napájení;
- napětí pomocí multimetru;
- schéma zapojení;
- napěťové hodnoty řadiče a modulu.

Nespoléhejte se pouze na barvu drátů nebo podobný typ konektoru.

## Úbytek napětí na drátech

Drát má odpor.

Čím delší je drát a větší je proud, tím větší je úbytek napětí a vytápění.

Příznaky:

- zdroj napájení vydává 24V, ale zátěž dostane méně;
- topidlo topí slabě, než se očekávalo;
- ventilátor se spustí špatně;
- servo se trhá;
- drát je znatelně teplý;
- terminál se zahřívá.

Ověřte napětí nejen na výstupu zdroje napájení, ale také na samotné zátěži během provozu.

Pokud se napětí podstatně snižuje pod zátěží, problém může být v drátě, terminále, konektoru, zdroji napájení nebo příliš velké zátěži.

## Žádná společná zem

Pokud řadič řídí externí modul nebo zátěž, často je potřebná společná zem.

Například:

- řadič řídí modul MOSFET;
- řadič nastaví PWM na ventilátor se 4 piny;
- řadič řídí servo se samostatným napájením;
- modul HX711, RFID nebo jiný je napájen samostatně.

Bez společného `GND` nemusí mít signál správnou úroveň. Zařízení nemusí fungovat nebo funguje náhodně.

Společná zem neznamená, že celá zátěž musí být napájena řadičem. Je to pouze společná referenční úroveň signálu.

## Řadič napájen z hlučné linky

Motory, ventilátory, servomechanismy, topidla a LED pásy mohou vytvářet propady napětí a šum.

Pokud je řadič napájen ze stejné linky bez správného DC-DC, filtrování a rezervy, může se restartovat.

Běžná řešení:

- samostatný správný DC-DC pro řadič;
- krátké vodiče napájení řadiče;
- společný `GND` na jasném místě;
- kondenzátor poblíž zátěže, je-li to vhodné;
- oddělení napájecích a logických vodičů;
- správný zdroj napájení s rezervou.

## Co zkontrolovat pomocí multimetru

Minimálně:

1. Napětí zdroje napájení bez zátěže.
2. Napětí zdroje napájení pod zátěží.
3. Napětí na svorkách zátěže pod zátěží.
4. Polarita.
5. Přítomnost společné země.
6. Zahřívání drátů a terminálů po krátké zkoušce.

Pokud zařízení funguje pouze bez zátěže, změřte jej pod zátěží. Napětí bez zátěže může vypadat normálně.

## Co nedělat

Nemůžete:

- používat zdroj napájení „na limit";
- zvýšit hodnocení pojistky, protože se vypíchne;
- používat tenké vodiče Dupont pro napájecí zátěž;
- kroutit napájecí vodiče bez správného terminálu;
- napájet topidlo slabým konektorem;
- připojit zátěž přímo na GPIO;
- opakovaně zapínat zařízení, pokud se drát nebo terminál zahřívá.

Pokud se něco zahřívá, nejdříve vypněte napájení a zjistěte příčinu.

## Typické chyby

- nevypočítaný proud zátěže;
- vybrán zdroj napájení bez rezervy;
- zapomnut impulsní proud ventilátoru nebo servomechanismu;
- zmátnutí 12V a 24V;
- napájení řadiče 5V z nestabilní linky;
- žádné společné `GND`;
- drát příliš tenký;
- drát příliš dlouhý na proud;
- terminál není dobře utažen;
- zátěž funguje, ale napětí se výrazně snižuje.

## Klíčové body

- Zdroj napájení se kontroluje první.
- Vypočítejte proud pro všechny zátěže, nikoli jen jednu součást.
- Musíte mít alespoň 50% energetickou rezervu.
- Napětí musí být měřeno pod zátěží.
- Společný `GND` je často povinný pro řízení externích modulů.
- Tenký nebo dlouhý drát může způsobit úbytek napětí a zahřívání.

## Reference

- [SparkFun: How to Power a Project](https://learn.sparkfun.com/tutorials/how-to-power-a-project/voltagecurrent-considerations) - základní úvahy o napětí, proudu a výkonu pro projekty s mikrokontroléry.
- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - kontrola zdroje napájení, připojení a zahřívání při řešení problémů.
- [ProdataKey: How does wire gauge affect line loss?](https://support.pdk.io/hc/en-us/articles/360047588514-How-does-wire-gauge-affect-line-loss) - proč délka, průřez a proud ovlivňují úbytek napětí a ztráty.
- [WiringCalcs: Voltage Drop Explained](https://wiringcalcs.com/guides/voltage-drop-explained-guide/) - praktické vysvětlení úbytku napětí, odporu drátů a vlivu proudu.
- [SparkFun Qwiic Power Meter guide](https://docs.sparkfun.com/SparkFun_Qwiic_Power_Meter_ACS37800/hardware_assembly/) - příklad společného `GND` při měření/řízení externí zátěže.
