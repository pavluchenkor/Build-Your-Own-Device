# Kontrola termistoru

Termistor je teplotní senzor, který mění odpor při ohřátí nebo ochlazení.

V 3D tiskárnách, sušičkách a komornch s topidlem je nejběžnějším typem NTC termistor s hodnocením `100K`. NTC znamená, že odpor se snižuje s rostoucí teplotou.

Musíte zkontrolovat termistor, pokud:

- teplotní údaje jsou nerealistické;
- teplota se skáče kolem;
- topidlo vstoupí do chybového stavu;
- firmware hlásí `MINTEMP`, `MAXTEMP`, `Thermal runaway` nebo podobné;
- termistor byl vyměněn, přemístěn nebo znovu usazený;
- zařízení bylo poprvé složeno.

## Nejdřív vypněte napájení

Odpor se měří pouze na de-energizované obvody.

Před kontrolou:

1. Vypněte zařízení.
2. Odpojte napájení od sítě nebo zdroje napájení.
3. Čekejte, až topidlo vychladne.
4. Odpojte termistor z desky, pokud potřebujete měřit senzor sám.

Pokud měříte odpor, když je termistor připojen k desce, mohou být údaje zkresleny ostatními součástmi obvodu. Pokud měříte odpor s zapnutým napájením, můžete poškodit multimetr nebo desku.

## Co by měl mít NTC 100K

Typický NTC `100K` má odpor přibližně `100 kOhm` při `25°C`.

To neznamená, že multimetr bude vždy ukazovat přesně `100.0 kOhm`.

Je normální, aby se údaj při pokojové teplotě mírně lišil:

- v chladné místnosti bude odpor vyšší;
- v teplé místnosti bude odpor nižší;
- různé typy termistorů mají různé tabulky;
- dlouhé vodiče a špatné kontakty mohou ovlivnit měření.

Hlavní kontrola je jednoduchá: 100K NTC při pokojové teplotě by měla ukazovat desítky nebo kolem sta kiloomů, ne `0 Ohm` nebo `OL`.

## Měření s multimetrem

Nastavte multimetr do režimu odporu `Ohm`.

Pokud váš multimetr není automaticky měřítko, vyberte rozsah nad `100 kOhm`, například `200 kOhm` nebo `2 MOhm`.

Pak:

1. Odpojte termistor z desky.
2. Dotčete se měřicích hrotů multimetru na dva termistor vodiče.
3. Nepodržujte současně kovové konce hrotů a vodičů: vaše tělo může přidat paralelní odpor.
4. Čekejte, až se údaj stabilizuje.
5. Zaznamenejte hodnotu.

![Digitální multimetr pro měření odporu termistoru](../../img/05-tools/02-digital-multimeter.jpg)

*Zdroj: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Aneng_AN870_multimeter_02.jpg), Retired electrician, CC0 Public Domain*

## Rychlý test tepla s prstem

Po měření při pokojové teplotě můžete senzor opatrně ohřát prsty.

U NTC termistoru by měl odpor začít klesat.

Například:

- byl kolem `100 kOhm` při pokojové teplotě;
- po ohřátí prstem se snížil.

Přesná čísla zde nezáleží. Záleží na směru změny.

Pokud se odpor vůbec nemění, skáče náhodně nebo zmizí, když se vodič pohne, problém může být v senzoru, vodiči, usazení nebo konektoru.

## Rozbitum a zkrat

Multimetr pomáhá rychle rozlišit normální senzor od zřejmého selhání.

Typické znaky:

- `OL`, `over limit`, `1` na levé straně displeje nebo nekonečný odpor - otevřený obvod;
- téměř `0 Ohm` - zkrat;
- hodnota se výrazně změní, když se vodič pohne - špatný kontakt nebo přerušený vodič;
- hodnota kolem `100 kOhm` při pokojové teplotě a snižuje se při ohřátí - vypadá jako zdravý NTC 100K.

Různé multimetry používají různá označení pro otevřený obvod. Obvykle je to `OL` nebo hodnota mimo vybraný rozsah.

## Kontrola vodičů

Termistor může být v pořádku, zatímco problém je v vodičích.

Zkontrolujte:

- konektor je plně vsunut;
- piny nevyšly z pouzdra konektoru;
- vodiče nejsou rozevlátané;
- bez poškození izolace blízko topidla;
- bez napětí vodiče, když se osy nebo kryt pohybují;
- kabel neběží přímo vedle napájecích vodičů topidla bez důvodu;
- umístění usazení je bezpečné.

Pokud se údaje změní, když se vodič pohne, toto není "vlastnost senzoru". To je kontaktní problém, který musí být opraven dříve, než zapnete topidlo.

## Kontrola v Klipperu

V Klipperu je typ senzoru nastaven v konfiguraci.

Příklad pro typický senzor teploty komory:

```ini
[temperature_sensor chamber]
sensor_type: Generic 3950
sensor_pin: PA0
min_temp: 0
max_temp: 100
```

Příklad pro topidlo v komoře:

```ini
[heater_generic chamber_heater]
gcode_id: C
heater_pin: PA8
sensor_type: Generic 3950
sensor_pin: PA0
control: watermark
min_temp: 0
max_temp: 90
```

Názvy pinů jsou zde typické. V reálném zařízení zkontrolujte rozpis pinů vaší desky.

Důležitě: `sensor_type` musí odpovídat skutečnému senzoru. Dva termistory mohou vypadat shodně, ale mají různé tabulky. Pokud zvolíte nesprávný typ, teplota může být notně nepřesná, zejména v pracovním rozsahu vytápění.

## Co sledovat v rozhraní

Po připojení zkontrolujte teplotu v rozhraní Klipperu, Mainsail, Fluidd nebo jiném uživatelském rozhraní.

Při pokojové teplotě by měl údaj být blízko skutečné pokojové teploty.

Podezřelé znaky:

- čte výrazně nižší, než je skutečnost;
- čte výrazně vyšší, než je skutečnost;
- teplota skáče o desítky stupňů;
- teplota se změní, když pohybujete vodičem;
- teplota nestoupá, když je topidlo zapnuto;
- teplota roste velmi pomalu;
- teplota stoupá, i když je topidlo vypnuté.

Pokud je senzor na topidlu, nezačínejte dlouhé vytápění, dokud údaje nevypadají rozumně.

## Chyby firmwaru

Ve firmwaru 3D tiskárny nejsou teplotní chyby malou záležitostí, ale součást bezpečnosti.

Pro typický obvod s NTC a palubní pull-up:

- selhání senzoru se často jeví jako příliš nízká teplota nebo `MINTEMP`;
- zkrat se často jeví jako příliš vysoká teplota nebo `MAXTEMP`;
- špatný tepelný kontakt může způsobit `Heating failed` nebo `Thermal runaway`;
- silné chladícího topného bloku může způsobit chybu, protože teplota roste příliš pomalu nebo se nedrží.

Názvy chyb závisí na firmwaru, ale smysl je stejný: kontrolér už důvěřuje teplotě nebo vidí, že topidlo nefunguje podle očekávání.

Nezakazujte tepelnou ochranu jen proto, abyste "zkontrolovali". Pokud se ochrana aktivuje, nejdřív hledejte příčinu v senzoru, vodičích, montáži, topidlu, nastavení PID a chladění.

## Tepelný kontakt

Elektricky fungující termistor negarantuje správnou teplotu.

Senzor musí dobře přenášet teplo z části, kterou měří.

Zkontrolujte:

- senzor je plně v pouzdře nebo otvoru;
- je normální svěrka;
- bez mezery mezi senzorem a povrchem;
- tepelná pasta se nevysušila ani neodsypala, je-li použita;
- upevnění není volné;
- senzor nevyšel z místa;
- vodiče netahají senzor ven.

Špatný kontakt je nebezpečný, protože senzor čte teplotu nižší, než je skutečnost. Kontrolér pokračuje v topidla, zatímco skutečná součást už může být přehřátá.

## Mini-checklist

Před prvním topidlem:

- odpor termistoru vypadá podle očekávání;
- odpor NTC klesá s ohřátím prstem;
- bez otevřeného obvodu nebo zkratu;
- vodiče nereagují skoky na pohyb;
- konektor je správně vsunut;
- správný `sensor_type` je zvolen ve firmwaru;
- teplota v rozhraní vypadá na pokojovou teplotu;
- senzor je bezpečně namontován na správné místo;
- `min_temp` a `max_temp` jsou nastaveny rozumně pro zařízení.

## Běžné chyby

- měření odporu se zapnutou deskou;
- neodpojení senzoru z desky a získání zvláštních hodnot;
- záměna `100K` termistoru s jiným typem senzoru;
- výběr nesprávného `sensor_type`;
- vidění `OL` a myšlení, že to znamená "100K";
- předpoklad, že jakýkoli 100K NTC je stejný;
- opuštění termistoru volně vedle topidla;
- přetažení skleněného termistoru skrutkou;
- natažení vodiče, aby senzor vyšel z pouzdra;
- zakázání tepelné ochrany místo opravy příčiny chyby.

## Klíčové body

- Odpor se měří pouze na de-energizované obvody.
- Typický NTC 100K je přibližně `100 kOhm` při `25°C`.
- Když je ohřátý, NTC odpor klesá.
- `OL` obvykle znamená otevřený obvod, téměř `0 Ohm` znamená zkrat.
- Firmware musí mít zvolen správný typ senzoru.
- Dobrý tepelný kontakt je stejně důležitý jako funkční vodičů.
- Nezačínejte topidlo, pokud teplotní údaje vypadají špatně.

## Související čtení

- [Odkaz na konfiguraci Klipperu: Teplotní senzory](https://www.klipper3d.org/Config_Reference.html#temperature-sensors) - oficiální `sensor_type`, `sensor_pin`, `pullup_resistor` parametry a seznam běžných termistorů.
- [Konfigurace Marlinu: Rozsahy teplot a tepelná ochrana](https://marlinfw.org/docs/configuration/configuration.html#temperature-ranges) - vysvětlení `MINTEMP`, `MAXTEMP` a ochrany před tepelným únikem.
- [Poradce při potížích s Marlinem: Topidlo selhalo](https://marlinfw.org/docs/basics/troubleshooting.html#heating-failed) - typické příčiny chyb topidla: termistor, pomalý nárůst teploty, tepelný únik.
- [RepRap Wiki: Termistor](https://reprap.org/wiki/Thermistor) - základní popis NTC/PTC termistorů a kontroly odporu v pokojové teplotě.
- [Fluke: Jak měřit odpor s digitálním multimetrem](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-resistance) - bezpečný postup pro měření odporu s digitálním multimetrem.
