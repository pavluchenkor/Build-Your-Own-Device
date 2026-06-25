# Rozhraní CAN

CAN je komunikační rozhraní na více zařízení na společné diferenční lince. Rozšíření: `Controller Area Network`.

CAN pochází z automobilového a průmyslového hardware, ale v 3D tiskárnách se stal populárním na desky hlav nástrojů, vzdálené MCU a moduly, kde potřebujete delší a spolehlivější komunikaci než I2C/SPI.

## Kde je CAN užitečný

V tiskárnách a zařízeních podobných iDryer se CAN používá na:

- desky hlav nástrojů na hlavě tiskárny;
- dodatečný MCU ve vzdáleném bloku;
- snížení počtu vodičů v shluku kabelů;
- komunikace s CAN filtrem, kamerou či deskách sušičky;
- distribuovaný systém s více kontroléry;
- případy, kde je USB či dlouhý I2C/SPI nepohodlný.

CAN je obzvláště užitečný, když je uzel vzdálen od hostu či hlavní desky a v blízkosti jsou motory, topidla a jiné zdroje šumu.

## CANH, CANL a GND

Fyzická CAN sběrnice typicky používá:

- `CANH`;
- `CANL`;
- někdy `GND` či společný referenční vodič;
- napájení modulu odděleně, pokud je potřeba.

Signál se vysílá jako rozdíl mezi `CANH` a `CANL`. Proto CAN zvládá šum lépe než jednotlivé signálové linky.

Zjednodušené schéma:

![Vysokorychlostní CAN ISO 11898-2 sběrnice s více uzly a terminátory](../../img/02-controllers/09-can-iso11898-2-network.png)

*Zdroj: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:CAN_ISO11898-2_Network.png), EE JRW, CC BY-SA 4.0*

Na zapojení se často používá kroucený pár na `CANH`/`CANL`. `GND` závisí na konkrétním obvodu, deskách a dokumentaci, ale v malých DIY systémech je běžně potřeba společný referenční bod na stabilní provoz a bezpečnost rozhraní.

## CAN transceiver je potřebný

Důležité: podpora CAN v mikrokontroléru a přítomnost CAN na desce nejsou totéž.

Na CAN práci potřebujete:

- mikrokontroleér s CAN kontrolérem nebo vhodnou podporou firmwaru;
- CAN transceiver na desce;
- správné konektory `CANH`/`CANL`;
- napájení transceiveru;
- terminátory;
- firmware sestaven pro CAN.

Pokud datalist mikrokontroléru zmiňuje CAN, ale deska nemá transceiver, nemůžete se přímo připojit na CAN sběrnici.

## Topologie a terminátory

CAN je sběrnice. Dobrá topologie vypadá jako čára s uzly připojenými přes krátké větvení.

Obvykle jsou potřeba dva terminátory `120 Ohm`:

- jeden na jednom fyzickém konci sběrnice;
- druhý na druhém fyzickém konci.

Ne jeden, ne tři a ne "na každé desce". Přesně dva na koncích.

Pokud je vypnutá napájení, na správně terminované sběrnici multimetr mezi `CANH` a `CANL` často ukazuje kolem `60 Ohm`, protože dva rezistory `120 Ohm` jsou paralelně.

Mnoho desek má terminační jumper. Některé mají vestavěný terminátor bez pohodlného vypnutí. Takže před montáží zkontrolujte schémata všech desek na sběrnici.

## Bitrate

Rychlost CAN se musí shodovat na všech uzlech. V Klipperu CAN často používá `1000000`, což je `1 Mbit/s`, ale konkrétní hodnota závisí na firmware, nastavení a délce sběrnice.

Pokud se bitrate liší, uzly se nebudou moci normálně komunikovat.

Na dlouhé či problémové zapojení může být rychlost kritická. Čím vyšší je rychlost, tím náročnější je sběrnice na topologii, terminátory a kvalitu vodiče.

## CAN v Klipperu

V Klipperu se CAN používá jako způsob komunikace s MCU.

Zařízení na CAN se obvykle nezadává přes `serial:`. Místo toho konfigurace používá `canbus_uuid`:

```ini
[mcu toolhead]
canbus_uuid: 11aa22bb33cc
```

Na Linuxové straně obvykle potřebujete rozhraní `can0`. Host musí mít CAN adaptér:

- USB-CAN adaptér;
- deska v režimu USB-to-CAN mostu;
- HAT/adaptér pro SBC;
- jiný podporovaný obvod.

Klipper má nástroj na nalezení `canbus_uuid` nových neinicializovaných zařízení. Důležité pochopit: pokud je zařízení již konfigurováno Klipperem, nemusí se už v seznamu objevit jako "nové".

## USB-to-CAN most

Některé desky lze nahrát v režimu USB-to-CAN mostu. Pak se deska připojuje k hostu přes USB a objeví se Linuxu jako CAN adaptér.

To je pohodlné, ale existuje důležité omezení: režim mostu je potřeba na komunikaci s reálnou CAN sběrnicí a ostatními CAN uzly. Pokud máte jen jednu desku blízko hostu a žádnou reálnou CAN sběrnici, je obvykle jednodušší používat normální režim USB/sériový.

Také USB-to-CAN most nebude viditelný jako `canbus_uuid`. Je nakonfigurován jako CAN rozhraní a používá `serial:`, nikoli `serial:`.

## Když je CAN oprávněný

CAN stojí za zvážení, pokud:

- potřebujete připojit desku hlavy nástrojů;
- potřebujete spustit komunikaci přes dlouhý svazek kabelů;
- potřebujete více vzdálených MCU;
- chcete snížit vodiče mezi pohyblivými a statickými částmi;
- již máte infrastrukturu CAN;
- je zvolená deska dobře zdokumentovaná pro CAN Klipperu.

CAN může být zbytečný, pokud:

- deska sedí blízko hostu;
- potřebujete jen jeden dodatečný MCU;
- USB funguje stabilně;
- nemáte zkušenosti s nahráváním, `can0`, terminátory a Linux sítí;
- zvolená deska je špatně zdokumentovaná.

Na první jednoduchý dodatečný kontrolér je USB často rychlejší a jasnější. CAN dává smysl, když řeší skutečný problém zapojení či distribuce desek.

## CAN nenapájí zátěž

CAN je jen komunikace.

Pokud CAN deska řídí ventilátor, topidlo, SSR nebo servo, stále potřebuje:

- napájení desky;
- napájení zátěže;
- MOSFET/driver/SSR;
- pojistky;
- správné svorky;
- tepelnou ochranu topidel;
- bezpečné pouzdro.

CAN nenahrazuje silovou elektroniku a neumožňuje topidlu bezpečnost.

## Co zkontrolovat před nákupem

Před nákupem desky CAN ověřte:

- který mikrokontroleér se používá;
- zda deska podporuje CAN Klipperu;
- zda je na desce CAN transceiver;
- kde jsou `CANH` a `CANL`;
- zda je terminátor a jak se povoluje;
- jaký konektor se používá;
- jak je deska napájena;
- jak se deska nahraje;
- zda existuje návod na `canbus_uuid`;
- zda se potřebuje oddělený USB-CAN adaptér;
- zda existuje schéma a rozložení pinů;
- jaké piny a silové výstupy jsou dostupné.

Pokud prodejce píše "CAN" jen protože čip teoreticky podporuje, ale deska nemá transceiver a dokumentaci, je to špatná volba.

## Typické chyby

- prohození `CANH` a `CANL`;
- zapomenutí, že CAN transceiver je potřebný;
- umístění jednoho terminátoru místo dvou;
- povolení terminátorů na každé desce;
- nekontrolování odporu mezi `CANH` a `CANL`;
- výběr různé bitrate na uzlech;
- očekávání `/dev/serial/by-id` z USB-to-CAN mostu;
- nahrání desky na USB, ale připojení jako CAN;
- nahrání na CAN, ale nekonfigurování `can0`;
- vytvoření hvězdy z dlouhých větví místo sběrnice;
- myšlenka, že CAN je způsob na napájení zátěže.

## Klíčové pozorování

CAN je dobrým rozhraním na vzdálené MCU, desky hlav nástrojů a distribuované systémy v tiskárně. Používá diferenční pár `CANH`/`CANL`, vyžaduje CAN transceivery, správnou topologii a dva terminátory na koncích sběrnice.

Pro Klipper je CAN užitečný, ale složitější než USB: musíte nahrát desku na CAN, nakonfigurovat adaptér/`can0`, najít `canbus_uuid` a ověřit fyzickou sběrnici. Používejte CAN tam, kde skutečně zjednodušuje zapojení nebo zlepšuje robustnost spojení.

## Related materials

- [Klipper: CANBUS](https://www.klipper3d.org/CANBUS.html) - oficiální dokumentace CAN Klipperu: hardware, adaptér hostu, `can0`, `canbus_uuid`, terminátory a USB-to-CAN most.
- [Klipper: CANBUS protocol](https://www.klipper3d.org/CANBUS_protocol.html) - jak Klipper přiřazuje CAN node id a používá `canbus_uuid`.
- [CAN Bus Debugger: CAN Bus Termination Explained](https://www.canbusdebugger.com/articles/can-bus-termination) - praktický výklad dvou terminátorů `120 Ohm`, měření `60 Ohm` a běžné chyby.
- [DigiKey: CAN Bus explained](https://www.digikey.com/en/blog/can-bus-explained) - obecný přehled CAN sběrnice, diferenční komunikace a aplikace v distribuovaných systémech.
- [Texas Instruments: Introduction to CAN](https://www.ti.com/lit/an/sloa101b/sloa101b.pdf) - základní popis fyzické vrstvy CAN, transceiversů a typické sítě.
