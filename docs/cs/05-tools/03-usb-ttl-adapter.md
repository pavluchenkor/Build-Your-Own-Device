# USB-TTL

Adaptér USB-TTL nebo USB-UART umožňuje vašemu počítači komunikovat s mikrokontrolérem přes UART přes USB.

Potřebujete ho pro:

- flashování některých desek;
- čtení protokolů;
- ladění komunikace UART;
- konfiguraci modulů;
- obnovení desky, když normální USB nefunguje;
- připojení k zařízení bez vestavěného USB-UART.

Běžné adaptéry používají čipy jako CH340, CP2102, FT232 a podobně.

## USB-TTL nebo USB-UART

Popisy spotřebitelů často říkají USB-TTL.

Technicky to obvykle znamená USB-UART adaptér s logickými úrovněmi TTL.

Hlavní věc na pochopení:

- strana USB se připojuje k počítači;
- strana UART se připojuje k mikrokontroléru;
- adaptér není programátor pro všechny desky;
- adaptér nenahrazuje ST-Link, pokud potřebujete flashovat STM32 přes SWD.

## Hlavní spoje

Typicky jsou zde:

- `GND`;
- `TX`;
- `RX`;
- `VCC` nebo `3V3`/`5V`;
- někdy `DTR`;
- někdy `CTS`, `RTS`.

Minimum pro komunikaci:

- `GND`;
- `TX`;
- `RX`.

Napájení je připojeno pouze pokud si jste jistí, že by měl adaptér napájet desku.

## TX a RX jsou křížově připojeny

UART je připojen takto:

```text
adaptér TX -> deska RX
adaptér RX -> deska TX
adaptér GND -> deska GND
```

`TX` je přenos.

`RX` je příjem.

Vysílač jednoho zařízení musí být připojen k přijímači druhého.

Pokud připojíte `TX` na `TX`, komunikace obvykle nefunguje.

![Křížově připojené TX/RX v připojení UART](../../img/02-controllers/06-uart-tx-rx-crossover.png)

*Zdroj: [SparkFun Electronics](https://learn.sparkfun.com/tutorials/serial-communication/all), CC BY-SA 4.0*

## Společný půdorys

Adaptér `GND` a deska `GND` musí být připojeny.

Bez společného půdorysu UART nemusí fungovat nebo bude fungovat nestabilně.

I když je deska napájena z oddělené zdroje, pro signálovou úroveň je stále potřeba půdorys.

## Logické úrovně 3,3V a 5V

Toto je jeden z nejdůležitějších bodů.

Adaptér může pracovat s logikou na:

- `3.3V`;
- `5V`;
- přepínatelný `3.3V/5V`.

Mnoho moderních desek a modulů používá logiku 3,3V: ESP32, RP2040, mnoho STM32.

Pokud použijete signál UART 5V na vstup 3,3V, můžete poškodit pin nebo celou desku.

Před připojením ověřte:

- jakou logickou úroveň deska používá;
- jakou logickou úroveň adaptér používá;
- co dělá přepínač 3,3V/5V;
- zda přepínač mění pouze napájení `VCC` nebo také úrovně `TX/RX`.

Některé adaptéry poskytují napájení 5V, ale signály logiky 3,3V. Ostatní mění jak napájení, tak úrovně. Zkontrolujte dokumentaci konkrétního adaptéru.

## Napájení z adaptéru

Nemusíte vždy připojovat `VCC`.

Často je bezpečnější připojit pouze:

- `GND`;
- `TX`;
- `RX`.

Napájejte desku z jejího normálního zdroje.

Můžete připojit `VCC` z adaptéru, pokud:

- deska je hodnocena na toto napětí;
- proud desky je v rozsahu možností adaptéru;
- není zde žádné jiné napájení ve stejné dobu;
- dokumentace desky umožňuje napájení přes tento pin.

Nebezpečná chyba je napájení z adaptéru USB-UART a zároveň ze samostatného zdroje, což způsobuje konflikt zdrojů.

## DTR a automatické resetování

Některé desky používají `DTR` pro automatické resetování během flashování.

Například Arduino Pro Mini a podobné desky mohou používat DTR přes kondenzátor pro automatické resetování.

Pokud flashování nezačíná automaticky, může to být proto, že:

- DTR není připojen;
- je potřeba ruční reset;
- je vybrán nesprávný adaptér;
- je vybrán nesprávný bootloader;
- je nesprávně vybrána rychlost nebo deska v IDE.

Pro jednoduché čtení protokolu DTR obvykle není potřeba.

## Jak zkontrolovat, zda je adaptér viditelný pro systém

Na macOS a Linuxu se adaptér obvykle zobrazuje jako zařízení v `/dev`.

Příklady:

```bash
ls /dev/tty.*
ls /dev/cu.*
ls /dev/ttyUSB*
ls /dev/ttyACM*
```

Na Windows se zobrazuje jako port `COM`.

Pokud se port neobjeví:

- zkontrolujte USB kabel;
- zkuste jiný port USB;
- zkontrolujte ovladač;
- ověřte, že to není jen nabíjecí kabel;
- podívejte se, jaký čip je na adaptéru: CH340, CP2102, FT232.

Levné adaptéry někdy vyžadují samostatný ovladač, zejména na Windows.

## Loopback test

Jednoduchý způsob, jak zkontrolovat adaptér:

1. Připojte spolu `TX` a `RX` adaptéru.
2. Otevřete sériový terminál.
3. Vyberte port a rychlost.
4. Zadejte text.

Pokud se znaky, které napíšete, vrátí, adaptér a port pravděpodobně fungují.

Po testu odeberte přemostění mezi `TX` a `RX`.

## Běžné chyby

- `TX` připojen na `TX` a `RX` na `RX`;
- zapomenut společný `GND`;
- vybrána úroveň 5V pro desku 3,3V;
- připojena `VCC` i když je deska již napájena odděleně;
- USB kabel se ukázal jako pouze nabíjecí;
- CH340/CP210x/FTDI ovladač není nainstalován;
- vybrán nesprávný port COM;
- rychlost UART se neshoduje;
- očekávání USB-UART pro flashování STM32 přes SWD;
- zmatek v režimu boot nebo resetování během flashování.

## Podstatné

- USB-UART adaptér je potřeba pro komunikaci UART mezi počítačem a deskou.
- Minimum pro komunikaci: `GND`, `TX`, `RX`.
- Adaptér `TX` jde na desku `RX`, adaptér `RX` jde na desku `TX`.
- Před připojením zkontrolujte logické úrovně 3,3V/5V.
- `VCC` je připojena pouze pokud si jste jistí, že potřebujete napájení z adaptéru.
- Pokud adaptér není viditelný, zkontrolujte kabel, ovladač a port USB.

## Referenční materiály

- [SparkFun: Serial Basic Hookup Guide](https://learn.sparkfun.com/tutorials/serial-basic-hookup-guide) - USB-to-serial adaptér, TX/RX/GND, VCC, DTR a přepínání 3,3V/5V.
- [SparkFun: Serial Basic CH340C Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide/serial-basic-overview) - moderní adaptér CH340C USB-UART, piny, LED a výběr napětí.
- [SparkFun: Serial Communication](https://learn.sparkfun.com/tutorials/serial-communication) - základy UART, TX/RX a sériová komunikace.
- [Silicon Labs: CP210x USB to UART Bridge VCP Drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) - oficiální ovladače Virtual COM Port CP210x.
- [Adafruit FTDI TTL-232 USB Type C Cable](https://www.adafruit.com/product/4364) - příklad kabelu s napájením 5V a logikou 3,3V, který ukazuje, proč je třeba napájení a signálové úrovně číst odděleně.
