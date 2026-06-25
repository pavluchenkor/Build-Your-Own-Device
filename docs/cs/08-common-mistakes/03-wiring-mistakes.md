# Chyby ve vedení

Zapojení často poškozuje zařízení více než samotná elektronika.

Špatný kontakt, obrácená polarita nebo slabý terminál mohou vypadat jako problém s firmwarem, senzorem nebo řadičem.

## Příznaky

Typické příznaky problémů se zapojením:

- zařízení někdy funguje, někdy ne;
- řadič je detekován pouze když je kabel pohnut;
- senzory zobrazují nesmysly;
- teplota se skáče;
- ventilátor se spustí přerušovaně;
- USB vypadne;
- terminál se zahřívá;
- drát tmavne nebo páchne;
- modul funguje na stole ale ne v pouzdru;
- po zavření krytu zařízení přestane fungovat.

Pokud se příznak změní když se drát pohne, nejdříve zkontrolujte zapojení.

## Obrácená plus a minus

Polarita se nedá zkontrolovat "podle barvy".

Červený drát je často plus, černý drát často minus, ale to není zárukou. V DIY zařízení si předchozí stavitel nebo vy sami mohli barvy zamíchat.

Před připojením:

- zkontrolujte označení řadiče;
- zkontrolujte pinout modulu;
- změřte napětí multimetrem;
- ověřte kde je `+` a kde `GND`;
- nepřipojujte modul pokud je pinout nejasný.

Obrácená polarita může okamžitě zničit řadič, senzor, ventilátor nebo DC-DC.

## Bez společné země

Společná zem je potřeba když je jeden modul napájen samostatně a signál pochází z řadiče.

Příklady:

- servo s samostatným napájením 5V;
- MOSFET modul pro ventilátor;
- 4-pinový PWM ventilátor;
- HX711;
- RFID modul;
- externí senzor.

Bez společné `GND` nemusí mít signál smysl. Zařízení nemusí reagovat, trhá se nebo funguje nestabilně.

## Špatný kontakt v terminálu

Terminál může vypadat jako upnutý, ale drát málo drží.

Důvody:

- drát není vložen až do konce;
- je upnut izolant místo vodiče;
- vinutý drát se třepí;
- je uvolněný šroub;
- terminál není hodnocen na proud;
- drát je příliš tenký nebo příliš tlustý pro terminál;
- chybí ferrule tam, kde je potřebná.

Špatný kontakt způsobuje zahřívání. Zahřívání zhoršuje kontakt. Toto je nebezpečný kruh.

Po krátké zkoušce pod zátěží zkontrolujte, zda se terminály a konektory zahřívají.

## Dupont ne pro napájecí zátěž

Vodiče Dupont jsou vhodné pro breadboardy a slabé signály.

Ale nemohou se považovat za normální napájecí vedení pro:

- topidla;
- výkonné ventilátory;
- LED pásy;
- servomechanismy s velkým proudem;
- napájení zařízení;
- 110-230V AC.

Dupont se může špatně držet, má malou kontaktní plochu a zahřívá se na proudech, na které není navržen.

Pro napájecí část potřebujete správné terminály, konektory, průřez drátů a protihlučnou ochranu.

## TX a RX

Pro UART je často potřeba křížové vedení:

- `TX` jednoho zařízení na `RX` druhého;
- `RX` jednoho zařízení na `TX` druhého;
- společný `GND`.

Typické chyby:

- připojeno `TX` na `TX`;
- připojeno `RX` na `RX`;
- zapomnut `GND`;
- vybraná špatná rychlost;
- logické úrovně se neshodují: 5V a 3,3V.

Pokud UART nefunguje, nejdříve zkontrolujte `TX/RX/GND`, pak rychlost a nastavení.

## I2C a SPI

Pro I2C:

- `SDA` musí jít na `SDA`;
- `SCL` musí jít na `SCL`;
- potřeba společný `GND`;
- adresa zařízení se nesmí konfliktovat;
- dráty musí být krátké.

Pro SPI:

- `MOSI`, `MISO`, `SCK`, `CS` se musí shodovat s pinoutem;
- každé zařízení má svůj vlastní `CS`;
- potřeba společný `GND`;
- dlouhé dráty mohou přerušit připojení.

RFID RC522 často matou lidi: pin `SDA` na řadiči může znamenat `SS/CS` pro SPI, ne I2C `SDA`.

## Sítě a signální vodiče

Vodiče 110-230V AC, napájecí DC zátěž a slabé signály se nesmí pokládat náhodně do jednoho svazku.

Problémy:

- rušení;
- zahřívání;
- poškození izolace;
- riziko dotknutí se síťové části;
- obtížná diagnostika;
- nebezpečí pro uživatele.

Část sítě musí být fyzicky oddělena. Nízkonapěťové senzory, UART/I2C/SPI a termistorové vodiče je lépe vést samostatně od napájecích vodičů topidla.

## Exponované vodiče

Exponovaný drát mimo terminál je špatný znak.

Může:

- dotknout sousedního terminálu;
- zkratovat pouzdro;
- dostat se pod kryt;
- zasáhnout ventilátor;
- vytvořit nebezpečí během údržby.

Po upnutí v terminálu by neměly vyčnívat dlouhé holé vodiče.

## Co zkontrolovat

Mini seznam:

1. Polarita zdroje napájení.
2. Společný `GND`.
3. Shoda pinoutu.
4. Kvalita terminálu.
5. Bez upnuté izolace místo vodiče.
6. Bez exponovaných vodičů.
7. Vodiče nejsou napnuté.
8. Kryt nepřitíská kabel.
9. Napájecí a signální vodiče odděleny.
10. Konektor hodnocen na proud.
11. Zařízení nemění chování když se drát pohne.

## Co nedělat

Nemůžete:

- měnit vodiče pod napájením;
- držet otevřenou síťovou část na stole;
- používat Dupont pro topidlo;
- upnout vinutý drát tak aby část vodiče trčela;
- kroutit napájecí vodiče bez správného spojení;
- ignorovat zahřívající se terminál;
- považovat "někdy funguje" za normální.

## Klíčové body

- Pokud zařízení reaguje na pohyb vodiče, jedná se o problém s vedením.
- Polarita se kontroluje multimetrem, ne podle barvy.
- Společný `GND` je potřeba pro většinu externích modulů se samostatným napájením.
- Dupont je vhodný pro breadboardy a signály, ale ne pro napájecí zátěž.
- Síťové a nízkonapěťové vodiče musí být odděleny.
- Zahřívající se terminál je důvod k zastavení, ne pokračování testu.

## Reference

- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - základní kontrola připojení, kontinuity, vypnutí-zapnutí a zahřívání.
- [SparkFun: Serial Communication](https://learn.sparkfun.com/tutorials/serial-communication) - UART, TX/RX a sériová komunikace.
- [SparkFun: I2C](https://learn.sparkfun.com/tutorials/i2c) - linky `SDA`, `SCL`, adresy a typické I2C chyby.
- [SparkFun: Serial Peripheral Interface](https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi) - linky SPI, `MOSI`, `MISO`, `SCK`, `SS/CS`.
- [FRC Design: Design for 3D Printing](https://www.frcdesign.org/design-handbook/structure/design-for-3d-printing/) - praktické rady pro elektronické pouzdra: otvory pro vodiče, ventilace, přístup k portům a odstranění komponent.
