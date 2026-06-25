# Připojení servomotoru

Servomotor je malý motor se převodovkou a řídící elektronikou. Můžete mu sdělit, na jakou pozici natočit hřídel.

V zařízeních podobných iDryer-u může servomotor otevřít tlumič, posunout malou sponu, stisknout mechanický spínač nebo změnit směr proudu vzduchu.

Hlavní chyba se servomotorem: myšlení, že je to "malá věc" a můžete ji napájet z jakéhokoli 5V pinu kontroléru. Servomotor může odebrat významný proud, zejména při startu, náhlém pohybu nebo když se mechanismus zajednoté.

## Tři vodiče

Typický hobby servomotor má tři vodiče:

- napájení: obvykle `5V` nebo `6V`;
- zem: `GND`;
- signál: řídicí pulsy od kontroléru.

Běžné barvy:

- červená - napájení;
- černá nebo hnědá - zem;
- žlutá, oranžová nebo bílá - signál.

Ale nemůžete slepě důvěřovat barvám. Různí výrobci mohou používat různá barevná schémata. Před připojením zkontrolujte značení, stránku produktu nebo specifikace.

## Napájení oddělené, signál oddělený

Signální vodič nenaápájí servomotor. Pouze řídí servomotor, kam se má otočit.

Servomotor čerpá energii z napájecího vodiče.

Správná logika je:

- kontrolér poskytuje pouze řídicí signál;
- servomotor je napájen zdrojem 5V/6V, který zvládne jeho proud;
- zem kontroléru a zem napájení servomotoru jsou připojeny dohromady.

![Barevný kód vodiče servomotoru](../../img/03-common-components/06-servo-color-code.jpg)

*Zdroj: [SparkFun Electronics](https://learn.sparkfun.com/tutorials/hobby-servo-tutorial/all), CC BY-SA 4.0*

## Proč nemůžete napájet ze slabých 5V

Mnoho desek má 5V pin. To neznamená, že od něj lze bezpečně napájet servomotor.

Při pohybu servomotor odebrat mnohem více proudu, než naznačuje jeho velikost. Pokud napájení stačit, objeví se typické příznaky:

- kontrolér se restartuje;
- obrazovka zábleskuje;
- USB připojení padá;
- servomotor se trhá;
- Wi-Fi na ESP32 padá;
- servomotor bručí ale nepohybuje se;
- napájení klesá při startu pohybu.

U jednoho malého servomotoru board napájení někdy funguje, pokud jsou deska a zdroj výslovně hodnoceny pro tento proud. Ale pro skutečné zařízení s tlumičem, sponkou nebo mechanismem je lépe použít oddělený zdroj 5V/6V DC-DC nebo napájení s rezervou.

## Společná zem

Pokud je servomotor napájen samostatným zdrojem, je potřeba společná zem.

Bez společné zemi nemají kontrolér a servomotor společné úrovně signálu. Servomotor nemusí reagovat, může se trhát nebo se chovat náhodně.

Jednoduché připojení:

1. `+5V` nebo `+6V` ze zdroje napájení jde na napájení servomotoru.
2. `GND` ze zdroje napájení jde na zem servomotoru.
3. `GND` kontroléru je připojen ke stejné zemi.
4. PWM/GPIO pin kontroléru jde na signální vodič servomotoru.

Napájení servomotoru a kontroléru mohou být různé, ale zem musí být společná.

## Jaký signál je potřebný

Typický pozičný hobby servomotor je řízen pulsy.

Typický signál:

- puls zhruba každých `20 ms`;
- asi `1 ms` - jeden extrém rozsahu;
- asi `1.5 ms` - střed;
- asi `2 ms` - druhý extrém rozsahu.

Toto není typické PWM pro jasnost LED nebo rychlost ventilátoru. Zde záleží na šířce pulsu v mikrosekundách.

Skutečné limity konkrétního servomotoru se mohou lišit. Některé bezpečně fungují ne od 0 do 180 stupňů, ale méně. Takže extrémní pozice vyžadují pečlivé testování.

## Nezacpávejte servomotor proti mechanismu

Servomotor se snaží udržovat stanovenou pozici.

Pokud tlumič zasáhne kryt, rameno se uvázne nebo mechanismus dosáhne fyzického zastavení dříve, než příkaz skončí, servomotor pokračuje v tlačení. V tom okamžiku proud roste, motor se zahřívá, převodovka se opotřebovává.

To je zvláště kritické pro tlumače a spony.

Před trvalým provozem ověřte:

- mechanismus se volně pohybuje po celém rozsahu;
- bez chybného zarovnání;
- bez uváznutí vazeb;
- servomotor nebrouzí v krajní poloze;
- extrémní úhly ve firmwaru nevynucují mechanismus do zastavení;
- s vypnutým napájením zařízení zůstane bezpečné nebo se vrátí přes pružinu, jak je zamýšleno.

Pokud servomotor brouzí v klidu, často to signalizuje zátěž, zastavení nebo špatnou geometrii páky.

## Počáteční a blokující proud

Servomotor má normální provozní proud a proud, když je hřídel blokovaná. Druhý se často nazývá proud zastavení.

Proud zastavení se objeví, když se servomotor pokusí pohybovat, ale hřídel je blokovaná nebo mechanismus je příliš těžký.

Tento režim často způsobuje:

- pokles napájení;
- restart kontroléru;
- zahřívání vodiče;
- přehřívání DC-DC;
- lámání převodovky.

Pokud specifikace uvádí proud zastavení, vyberte zdroj napájení s ohledem na tuto hodnotu a bezpečnostní rezervu. Pokud není specifikace, nemůžete předpokládat, že je servomotor bezpečný "podle vzhledu".

## Kondenzátor vedle servomotoru

Někdy elektrolytický kondenzátor mezi `+5V` a `GND` vedle servomotoru pomáhá.

Nenahrazuje správné napájení, ale může hladlit krátké pokles při startu pohybu.

Pro malý servomotor: stovky mikrofaradů, jako `470 uF` nebo více, s hodnocením napětí nad napájecím napětím.

Polarita elektrolytického kondenzátoru záleží:

- plus kondenzátoru na `+5V`;
- minus kondenzátoru na `GND`.

Pokud musí být zařízení spolehlivé, nejdřív zvolte správné napájení a vodičů, pak použijte kondenzátor jako dodatečné opatření.

## Příklad konfigurace Klipperu

V Klipperu je servomotor popsán sekcí `[servo]`.

Příklad:

```ini
[servo chamber_damper]
pin: PA8
maximum_servo_angle: 180
minimum_pulse_width: 0.001
maximum_pulse_width: 0.002
initial_angle: 90
```

Příkazy:

```gcode
SET_SERVO SERVO=chamber_damper ANGLE=0
SET_SERVO SERVO=chamber_damper ANGLE=90
SET_SERVO SERVO=chamber_damper ANGLE=180
```

Názvy pinů jsou zde typické. V reálném zařízení zkontrolujte rozpis pinů vaší desky.

Pro mechaniku nezačínejte s `0` a `180` hned. Nejdřív testujte bezpečný rozsah jako `60`, `90`, `120`, pak rozšiřujte úhly.

## Příklad Arduino/ESP32 logiky

Přístup Arduino obvykle používá knihovnu Servo:

```cpp
#include <Servo.h>

Servo damper;

void setup() {
  damper.attach(9);
  damper.write(90);
}

void loop() {
}
```

Toto je jen příklad logiky signálu. Napájení servomotoru stále musí být navrženo zvlášť. I když je signální vodič připojen k Arduino nebo ESP32, servomotor nesmí přetěžovat napájení kontroléru.

## Co kontrolovat po připojení

Před montáží do pouzdra:

- servomotor dostává správné napětí;
- zdroj napájení zvládne proud servomotoru;
- zem kontroléru a zem servomotoru jsou společné;
- signální vodič je připojen na správný pin;
- servomotor se otáčí správným směrem;
- extrémní úhly nepoškodzují mechanismus;
- mechanismus se neuvázne;
- servomotor nebrouzí nepřetržitě;
- vodiče nechytají se páky nebo ozubů;
- napájení neslábne po pohybu;
- kontrolér se neresetuje.

Testujte mechaniku bez zátěže a pod skutečnou zátěží. Tlumič, který se lehce pohybuje ručně, se může po montáži v pouzdře uváznouttout.

## Běžné chyby

- napájení servomotoru z GPIO;
- napájení servomotoru ze slabého 5V pinu desky;
- zapomenutí společné zemi;
- důvěřování barevným kódům bez kontroly;
- připojení napájení pozpátku;
- použití příliš tenkých vodičů;
- nezohlednění počátečního a blokujícího proudu;
- vynucení servomotoru tlačit proti mechanickému zastavení;
- použití úhlu `0` nebo `180`, když skutečný mechanismus bezpečně běží pouze v menším rozsahu;
- montáž servomotoru blízko tepla bez kontroly pracovní teploty;
- zacházení se servomotorem nepřetržité rotace jako s běžným pozičním servomotorem.

## Klíčové body

- Servomotor má tři linky: napájení, zem a signál.
- Signál nenaápájí servomotor.
- Skutečná zařízení často potřebují oddělený zdroj 5V/6V.
- Zem servomotoru a zem kontroléru musí být společné.
- Nejnebezpečnější zátěž je uvíznutí nebo mechanické blokování.
- Extrémní úhly vyžadují pečlivý výběr, ne okamžité `0` a `180`.
- Pokud se kontrolér restartuje, když se servomotor pohybuje, nejdřív zkontrolujte napájení a společnou zem.

## Související čtení

- [Odkaz na konfiguraci Klipperu: Servo](https://www.klipper3d.org/Config_Reference.html#servo) - oficiální sekce `[servo]`, `SET_SERVO`, úhly a šířka pulsu.
- [SparkFun: Hobby Servo Tutoriál](https://learn.sparkfun.com/tutorials/hobby-servo-tutorial/introduction) - základní vysvětlení hobby servomotoru, tří vodičů a řízení pulsu.
- [SparkFun: Servo Trigger Hookup Guide](https://learn.sparkfun.com/tutorials/servo-trigger-hookup-guide/servo-motor-background) - rozpis elektrického připojení, typických barev vodičů a mechaniky hobby servomotoru.
- [Adafruit: Arduino Lekce 14. Servomotory](https://learn.adafruit.com/adafruit-arduino-lesson-14-servo-motors?view=all) - praktický příklad připojení, chování poklesu napájení a kondenzátor vedle servomotoru.
- [Odkaz na knihovnu Arduino Servo](https://www.arduino.cc/reference/en/libraries/servo/) - oficiální knihovna Servo pro přístup Arduino.
