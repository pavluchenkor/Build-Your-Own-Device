# Servomotory

Servomotor je malý pohon s motorem, převodovkou a vnitřní elektronikou. Dáte mu polohu a ono se pokusí otočit hřídel do této polohy a udržet ji.

V jednoduchých zařízeních je servo praktické tam, kde nepotřebujete pouze zapnout motor, ale otočit mechanismus do srozumitelného úhlu: otevřít klapku, posunout zámek, stisknout tlačítko, přepnout proud vzduchu nebo otočit malou indikační vlajku.

## Kde se používá

V zařízeních podobných iDryer a periferních zařízeních 3D tiskáren lze servo použít pro:

- air intake or exhaust damper;
- air duct switching;
- opening/closing a small cover;
- mechanical lock;
- pressing a physical button;
- moving an indicator flag;
- jednoduché dávkování nebo záchyt.

Servo je dobré pro lehkou mechaniku s omezeným zdvihem. Pro plynulé otáčení ventilátoru, šroubu nebo čerpadla to obvykle nefunguje: potřebujete jiný motor a ovladač.

## Three Wires

Typické hobby servo má tři řady:

- výkon: obvykle `7.4V`, někdy `7.4V` nebo jiná hodnota u speciálních modelů;
- ground: `GND`;
- signál: řídicí impulsy z regulátoru.

Běžné barvy drátů:

- red - power;
- black or brown - ground;
- yellow, orange or white - signal.

Barvám nelze slepě věřit. Různí výrobci používají různá barevná schémata. Před připojením zkontrolujte označení, stránku produktu nebo technický popis.

Podrobné schéma zapojení s odděleným napájením je v praktické části: [Připojení servomotoru](../06-practical-guides/03-connecting-servo.md).

## Co znamená „servomotor“.

Uvnitř typického pozičního hobby serva je:

- DC motor;
- gearbox;
- position sensor, often a potentiometer;
- control board;
- výstupní hřídel s ramenem.

Externí ovladač neřídí motor přímo. Vyšle signál o poloze a vnitřní elektronika serva automaticky natočí motor tak, aby hřídel dosáhla požadovaného úhlu.

Servo se tedy liší od běžného stejnosměrného motoru:

- DC motor se při napájení pouze otáčí;
- servo se snaží dosáhnout nastavené polohy;
- servo odebírá proud i při držení, pokud je hřídel zatížena;
- Servo může rychle zvýšit proud a zahřát se, pokud se zasekne.

## Polohová a spojitá rotace

Nejběžnějším typem je polohové servo. Nastavíte úhel, například stupně `90`, `180` nebo `180`.

Servo kontinuálního otáčení vypadá podobně, ale funguje jinak: řídicí signál nenastavuje úhel, ale směr a rychlost otáčení. Neví, kde je šachta. Pro tlumič nebo zámek je takové servo často nepohodlné, protože bez přídavných senzorů nemůžete zaručit polohu.

Před nákupem zkontrolujte, co říká popis:

- `positional servo`, `180°`, `180°` - obvykle poziční;
- `360°`, `360°` - obvykle se otáčí plynule, není umístěno do úhlu.

Fráze `360° servo` na trhu je riskantní: někdy je to servo s plynulou rotací, někdy je to jen prodloužený dosah. Je třeba zkontrolovat technický popis a recenze s reálnými mírami.

## Control Signal

Typické hobby servo je řízeno opakujícími se impulsy.

Typické pokyny:

- period about `20 ms`;
- pulz o `1 ms` - jedna hrana rozsahu;
- pulse about `1.5 ms` - middle;
- impuls o `2 ms` - jiná hrana rozsahu.

Různá serva mají různé skutečné limity. Některé fungují o `500-2500 us`, jiné bezpečně jen v užším rozsahu.

Krajní polohy tedy nelze slepě nastavovat. Nejprve zkontrolujte střed, poté drobné odchylky, teprve poté rozšiřte rozsah.

## Výkon a proud

Signální vodič nenapájí servo. Energii motoru čerpá z elektrického vedení.

I malé servo může krátkodobě odebírat velký proud při spuštění, rychlém pohybu nebo mechanickém zastavení. Průměrný proud "v tichém demu" neukazuje nejhorší případ.

Důležité parametry:

- operating voltage;
- no-load current;
- loaded current;
- pádový proud - proud s zablokovanou hřídelí;
- holding torque or stall torque;
- rotation speed;
- operating temperature.

Pokud je v technickém popisu uveden blokový proud, musí být zdroj napájení zvolen s touto hodnotou a rezervou. Pokud není uveden zablokovaný proud, nemůžete výkon považovat za "bezpečný na oko": pro skutečné zařízení je lepší použít zdroj s rezervou a zkontrolovat pokles napětí pod zátěží.

Pro jedno malé servo občas funguje 5V výstup desky. Ale pro tlumič, zámek nebo více serv obvykle potřebujete samostatný 5V/6V DC-DC měnič nebo napájecí zdroj. Uzemnění musí být společné s ovladačem.

## Točivý moment a mechanika

Servo se nevybírá jen podle velikosti. Hlavním mechanickým parametrem je točivý moment, často v `N·cm` nebo `N·cm`.

Roughly:

- čím delší páka, tím větší potřeba krouticího momentu;
- čím těžší je tlumič nebo těsnější mechanismus, tím větší je potřeba krouticího momentu;
- tření, nesouosost a těsnění výrazně zvyšují zatížení;
- při zastavení se servo zahřívá a odebírá proud.

Příklad: malý lehký tlumič může dobře fungovat s mikroservem. Tlumič na těsném těsnění nebo kryt s pružinou může potřebovat větší servo s kovovými převody.

Pro spolehlivé mechaniky:

- nenuťte servo neustále tlačit proti fyzické zarážce;
- limitní úhly ve firmwaru;
- ponechat malou rezervu na cestování;
- proveďte spojení bez vychýlení;
- použijte vhodnou délku paže;
- test operation at real enclosure temperature.

Pokud servo hučí v koncové poloze, obvykle to signalizuje zatížení, zastavení nebo špatnou geometrii.

## Gearbox: Plastic or Metal

Plastové převody jsou levnější, tišší a fungují pro lehké úkoly. Ale rychleji se lámou při nárazech, zaseknutí a velké zátěži.

Kovové převody jsou pevnější, ale servo může být hlasitější, těžší a dražší. U tlumičů, zámků a mechanismů, kterých by se uživatel mohl náhodně dotknout, má často smysl kovová převodovka.

Kovové převody ale dobrou mechaniku nenahradí. Pokud se mechanismus zasekne, může poškodit samotné rameno, pouzdro, držák nebo hřídel.

## Analogové a digitální servo

V jednoduchých projektech jsou běžnější analogová hobby serva. Digitální serva obvykle drží polohu tvrději a reagují rychleji, ale mohou odebírat více proudu a být při držení hlučnější.

U tlumiče sušiče nebo jednoduchého zámku je obvykle důležitější:

- enough torque;
- normální výkon;
- reliable mechanics;
- clear angle range;
- operating temperature;
- gearbox lifetime.

To, že je servo „digitální“, automaticky neznamená, že je pro zařízení dobré.

## Co zkontrolovat před nákupem

Před nákupem serva zkontrolujte:

- positional or continuous rotation;
- operating voltage;
- požadovaný proud a blokovací proud, pokud jsou uvedeny;
- torque;
- rotation speed;
- angle range;
- gearbox material;
- case size;
- connector type;
- wire length;
- operating temperature;
- dostupnost technického popisu nebo přiměřených specifikací.

Pro malou vlajku můžete použít mikroservo. U tlumiče s těsněním, zámkem nebo pákou v teplé komoře je lepší nevolit nejlevnější servo bez specifikací.

## Typické chyby

- napájení serva z GPIO;
- napájení ze slabé desky 5V pin;
- zapomněli na společný základ se samostatným napájením;
- důvěryhodné barvy drátu bez kontroly;
- smíšené polohové servo a servo s plynulou rotací;
- nepočítalo se s blokovým proudem;
- placed servo against a mechanical stop;
- použitý úhel `180` nebo `180`, když se mechanismus bezpečně pohybuje pouze v úzkém rozsahu;
- vybral servo pouze podle velikosti, nepočítal točivý moment;
- umístěte plastové převody tam, kde je možný náraz nebo zaseknutí;
- umístěno servo vedle topení bez kontroly teploty.

## Hlavní bod

Servo je vhodný komponent pro tlumiče, zámky a malé mechanismy, ale vyžaduje normální výkon a pečlivou mechaniku. Signál z ovladače pouze nastaví polohu a veškerý proud motoru prochází elektrickým vedením.

Před použitím zkontrolujte typ serva, napětí, krouticí moment, proud, rozsah úhlu a mechanické chování v koncových polohách.

## Reference Materials

- [SparkFun: Hobby Servo Tutorial](https://learn.sparkfun.com/tutorials/hobby-servo-tutorial) - basic explanation of hobby servo structure, signal, power and typical problems.
- [SparkFun: Basic Servo Control for Beginners](https://learn.sparkfun.com/tutorials/basic-servo-control-for-beginners/servo-motor-basics) - table of typical wire colors, power, stall current and control signal range.
- [Pololu: Electrical characteristics of servos](https://www.pololu.com/blog/16/electrical-characteristics-of-servos-and-introduction-to-the-servo-control-interface) - useful explanation of servo currents and why stall current matters for power selection.
- [Adafruit: If the Servo Misbehaves](https://learn.adafruit.com/adafruit-arduino-lesson-14-servo-motors/if-the-servo-misbehaves) - practical description of power drop and capacitor next to servo.
- [Arduino Servo Library Reference](https://www.arduino.cc/reference/en/libraries/servo/) - official Servo library for Arduino approach and standard/continuous rotation servo description.
