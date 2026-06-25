# Termistory

Termistore je teplotní senzor, jehož odpor se mění při zahřátí nebo ochlazení. V 3D tiskárnách, sušičkách a malých topných zařízeních se často používá jako zpětná vazba pro řízení topného tělesa.

Nejčastěji používaná možnost v komunita 3D tisku je NTC termistore `100K`. NTC znamená, že se zvyšující se teplotou se odpor snižuje. `100K` obvykle znamená přibližně `100 kOhm` při `25°C`.

## Kde se používá

Termistory se používají k měření teploty:

- hotend;
- heated bed;
- printer chamber;
- filament dryer;
- air duct;
- topný modul;
- oblast elektroniky, pokud je potřeba jednoduchá ochrana proti přehřátí.

V zařízení s ohřívačem není termistor dekorativním senzorem. Určuje, kdy regulátor sníží výkon, zakáže topení nebo se zastaví s chybou.

## NTC 100K, beta a vyhledávací tabulky

Různé termistory mohou vypadat stejně, ale mají různé vlastnosti.

Důležité parametry:

- odpor na `25°C`, například `100 kOhm`;
- type: NTC or PTC;
- Beta, například `3950K`;
- vyhledávací tabulka odporu/teploty;
- rozsah provozních teplot;
- accuracy;
- balení: skleněná kulička, kartuše, šroubový senzor, pouzdro;
- izolace drátu.

Pokud firmware vybere špatný typ čidla, teplota se zobrazí nesprávně. Chyba může být malá při pokojové teplotě a nebezpečná při provozní teplotě.

Takže fráze "100K termistor" není vždy dostačující. U firmwaru záleží na konkrétním modelu nebo alespoň na správné beta/tabulce.

## Jak regulátor měří teplotu

Termistor je obvykle připojen k analogovému vstupu přes napěťový dělič s pull-up rezistorem. Ovladač měří napětí, převádí ho na odpor a poté používá vyhledávací tabulku nebo vzorec k získání teploty.

![Voltage divider with thermistor for temperature measurement](../../img/03-common-components/04-thermistor-voltage-divider.svg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Thermistor_potential_divider.svg), Sjlegg, Public Domain*

V Klipperu se to nastavuje pomocí `sensor_pin`, `pullup_resistor`, někdy `[thermistor]` nebo vlastní sekce `[thermistor]`.

V Marlin se typ termistoru volí pomocí konfiguračních parametrů snímače a teplotních limitů.

Pro uživatele je klíč jednoduchý: firmware musí přesně znát typ senzoru, který je v zařízení nainstalován.

## Otevřený obvod a zkrat

Termistor a jeho kabeláž mohou selhat.

Typické příznaky:

- zlomený drát;
- poor connector contact;
- dráty jsou krátké;
- damaged insulation;
- senzor vyklouzl z pouzdra;
- drát odřený v pohyblivé části;
- čidlo ukazuje pokojovou teplotu, i když probíhá topení.

Firmware má obvykle ochrany jako `MINTEMP`, `MAXTEMP`, ověření zahřívání a ochrana proti tepelnému úniku. Tyto ochrany ale fungují pouze v případě, že senzor a firmware jsou správně nastaveny a výkonovou část lze skutečně vypnout.

Pokud senzor spadne z ohřívače, ale zůstane elektricky připojen, je to obzvláště nebezpečné: firmware může vidět „nízkou teplotu“ a nadále topit.

## Thermal Contact

Montáž termistoru je často důležitější, než se zdá.

Senzor by měl měřit teplotu místa, které skutečně potřebujete ovládat. U hotendu je to topný blok. U postele je to povrch nebo místo související s potřebou postele. U ohřívače vzduchu je to bod zvolený bezpečnostní a řídicí logikou.

Tepelný kontakt je ovlivněn:

- tlak snímače;
- thermal paste;
- mounting hole;
- sheath;
- screw mounting;
- gap;
- materiál kolem senzoru;
- stav drátu;
- contamination or dried paste;
- vibrace a volné upevnění.

Pokud se termistor jen dotkne části ze strany, může reagovat pomalu a ukazovat špatnou teplotu. PID regulátor pak dostane zpožděnou informaci a teplota může překročit nebo překročit cíl.

## Balíček senzorů

Termistory se dodávají v různých baleních.

Glass bead:

- cheap;
- tiny;
- requires careful mounting;
- snadno poškodit drát nebo izolaci.

Cartridge thermistor:

- snadnější vložení do otvoru topného bloku;
- obvykle mechanicky stabilnější;
- Důležité je sladit průměr a délku.

Screw thermistor:

- snadno se montuje na kovový povrch;
- může poskytnout dobrý kontakt, pokud je správně nainstalován;
- nesmí drát příliš utáhnout nebo poškodit.

Senzor v plášti:

- vhodné pro vzduch, kapalinu nebo uzavřený prostor;
- reaguje pomaleji, pokud je pouzdro masivní;
- správný bod instalace je důležitý.

Volba balení závisí na tom, co se měří a jak bude senzor servisován.

## Kontrola multimetru

Základní kontrolu lze provést multimetrem v odporovém režimu. Podrobný postup je v praktickém článku: [Kontrola termistoru](../06-practical-guides/02-checking-thermistor.md).

Pro typický NTC `100K` při pokojové teplotě kolem `25°C` očekáváte přibližně `100 kOhm`. Přesná hodnota závisí na teplotě a toleranci.

Při zahřátí prsty by se měl odpor NTC snížit. Pokud multimetr ukazuje přerušený obvod, zkrat nebo hodnota při pohybu vodiče vyskočí, nejprve zkontrolujte konektor a kabeláž.

Kontrola multimetru nenahrazuje kalibraci a neprokazuje přesnost na `200°C`, ale rychle ukazuje zjevný otevřený, krátký nebo nesprávný typ senzoru.

## Co zkontrolovat před nákupem

Před nákupem termistoru zkontrolujte:

- resistance at `25°C`;
- Beta or exact model;
- kompatibilita s firmwarem;
- rozsah provozních teplot;
- senzorový balíček;
- délka a materiál drátu;
- connector type;
- mounting method;
- whether you need a cartridge, screw, sheath or glass bead;
- zda se čidlo hodí k vašemu topnému bloku nebo místu instalace;
- dostupnost technického popisu nebo jasných informací.

Pro hotend je lepší pořídit snímač, který mechanicky pasuje na konkrétní blok. U komory nebo sušičky záleží více na místě instalace, ochraně vodičů a stabilitě měření v proudění vzduchu.

## Typické chyby

- špatně vybrán `sensor_type`;
- myslet si, že jakýkoli `100K` termistor je stejný;
- snímač je špatně stlačen;
- no proper thermal contact;
- senzor vyklouzl z pouzdra;
- drát odřený nebo zlomený na těle snímače;
- kontakt konektoru je špatný;
- vedení vedle elektrického vedení zbytečně;
- termistor měří vzduch, ale regulátor si myslí, že měří ohřívač;
- firmware nastavený bez rozumných `min_temp` a `max_temp`;
- ohřívač zapnutý bez nezávislé hardwarové ochrany.

## Hlavní bod

Termistor je zpětná vazba pro ohřívač. Je důležité nejen koupit "100K NTC", ale vybrat správný typ ve firmwaru, namontovat snímač na správné místo a zkontrolovat kabeláž.

Špatný tepelný kontakt nebo nesprávný `sensor_type` může být nebezpečnější než zcela mrtvý senzor, protože systém stále funguje, ale rozhoduje o nesprávné teplotě.

## Reference Materials

- [Klipper Configuration Reference: Temperature sensors](https://www.klipper3d.org/Config_Reference.html#temperature-sensors) - oficiální `sensor_type`, `pullup_resistor`, vlastní `[thermistor]` a teplotní senzory v Klipperu.
- [Marlin Configuration: Temperature Ranges and Thermal Protection](https://marlinfw.org/docs/configuration/configuration.html#temperature-ranges) - teplotní limity, `MINTEMP`, `MAXTEMP` a tepelná ochrana.
- [Vishay: NTC Thermistors](https://www.vishay.com/en/thermistors/ntc/) - Parametry NTC termistoru: odpor při `25°C`, Beta, tolerance a provozní rozsah.
- [RepRap Europe: Thermistor NTC100K](https://www.reprap-3d-printer.com/product/335-thermistor-ntc100k) - příklad typické 3D tiskárny NTC `100K` s Beta `3950` a `100 kOhm` na `25°C`.
- [RepRap Europe: Thermistor Cartridge 100k HT-NTC B3950](https://reprap.eu/produto/?id=1245&nome=Thermistor+Cartridge+100k+HT-NTC+B3950) - příklad kartušového termistoru pro topný blok a mechanickou montáž.
