# Chyby řadiče

Řadič není univerzální box, kam můžete všechno přímo zapojit.

Čte senzory, produkuje řídící signály a komunikuje s hostitelem. Ale napájecí zátěž musí být napájena správnými výstupy, MOSFET, relé, SSR nebo ovladači.

## Příznaky

Typické příznaky problémů s řadičem nebo připojením:

- řadič není detekován přes USB;
- firmware se nespustí;
- piny nereagují;
- řadič se restartuje;
- řadič se výrazně zahřívá;
- řadič přestane fungovat po připojení modulu;
- ESP32 ztratí Wi-Fi když se zátěž zapne;
- senzor není viditelný přestože má napájení;
- Klipper se nepřipojí k MCU;
- příkazy pracují na špatném pinu.

## Vybrán špatný řadič

Před výběrem řadiče musíte pochopit úkol.

Pro jednoduché autonomní Wi-Fi zařízení může být ESP32 dobrá volba.

Pro dodatečný MCU v Klipperu je často praktičtější podívat se na:

- RP2040;
- STM32;
- hotový 3D tiskárenský řadič.

Arduino Uno/Nano jsou užitečné pro učení a jednoduché experimenty, ale pro nové vážné zařízení kolem tiskárny si rychle narazíte na omezení.

Chyba je vybrat řadič jen proto, že "je populární", bez kontroly:

- počet potřebných pinů;
- logické úrovně;
- napájení;
- podpora firmwaru;
- dostupnost USB/UART/CAN;
- podpora potřebných knihoven;
- výstupní proud;
- vývojové prostředí.

## ESP32 jako Klipperem MCU

ESP32 je užitečný jako samostatné IoT/Wi-Fi zařízení.

Ale neočekávejte automaticky, že ESP32 bude nejlepší volbou jako Klipperem MCU.

Pokud je cíl integrace s Klipperem jako dodatečný MCU, nejdříve se podívejte na oficiální a osvědčené možnosti pro Klipper. Pro nové hardwarové rozšíření je často jednodušší a spolehlivější používat RP2040 nebo STM32.

ESP32 je dobrý pokud by mělo zařízení:

- pracovat autonomně;
- mít Wi-Fi;
- poskytovat data přes MQTT nebo HTTP;
- mít webové rozhraní;
- komunikovat s Home Assistantem;
- pracovat samostatně od Klipperu.

## 3,3V a 5V logika

Mnoho moderních řadičů pracuje s logickou úrovní 3,3V.

Například:

- ESP32;
- RP2040;
- mnoho STM32.

Chyba je aplikovat 5V signál na vstup navržený pouze pro 3,3V.

Toto může:

- okamžitě poškodit pin;
- poškodit řadič později;
- způsobit nestabilní chod;
- rozbít modul, který se zdál být v pořádku.

Před připojením ověřte:

- napájecí napětí modulu;
- logickou úroveň vstupu/výstupu;
- je zde převodník úrovně;
- přijímá vstup 5V;
- co je napsáno v technickém popisu.

## GPIO není napájení zátěže

GPIO je signální pin.

Nesmí napájet:

- ventilátor;
- servo;
- topidlo;
- LED pás;
- relé bez ovladače;
- solenoid;
- motor.

GPIO může poslat příkaz. Proud zátěže musí jít správným výstupem, MOSFET, ovladačem, relé nebo samostatným modulem.

Pokud je zátěž připojena přímo na GPIO, můžete poškodit pin nebo celý řadič.

## Bez společné GND

Řadič může řídit externí modul pouze pokud mají společnou referenční úroveň.

Typická chyba:

- servo napájené ze samostatného 5V zdroje;
- signál pochází z řadiče;
- `GND` není připojena;
- servo se trhá nebo nereaguje.

Stejně tak s MOSFET moduly, PWM ventilátory, některými senzory a externími řadiči.

## Nesprávný firmware

Řadič může být v pořádku, ale firmware se nehodí.

Chyby:

- firmware nahrán pro špatný mikrokontrolér;
- vybrán špatný bootloader;
- zaměněno USB a UART firmware;
- vybrán špatný sériový port;
- Klipper nastavil špatnou cestu zařízení;
- piny v konfiguraci se neshodují s řadičem;
- firmware/host se nerestartoval po nahrání.

Před nahráním musíte přesně vědět model řadiče a mikrokontroléru.

## Pin existuje na schématu ale není vhodný

Není každý pin stejný.

Piny mohou mít omezení:

- jen vstup;
- používaný USB/UART/SPI;
- používaný během spuštění;
- související se spouštěcím režimem;
- nepodporuje potřebné PWM;
- vytažen nahoru nebo dolů;
- konflikty s jiným modulem.

Pokud se pin chová podivně, zkontrolujte dokumentaci řadiče, ne jen číslo GPIO.

## Co zkontrolovat

Mini seznam:

1. Je vybrán správný řadič pro daný úkol?
2. Jaké napájení potřebuje řadič?
3. Jaká logika: 3,3V nebo 5V?
4. Je zde společný `GND` s externími moduly?
5. Není zátěž napájena z GPIO?
6. Podporuje řadič potřebné rozhraní?
7. Není vybraný pin použitý?
8. Je firmware správný?
9. Je řadič viditelný přes USB?
10. Odpovídá konfigurace pinoutu řadiče?

## Co nedělat

Nemůžete:

- aplikovat 5V na 3,3V vstup bez kontroly;
- připojit zátěž přímo na GPIO;
- nahrát náhodný firmware "podobného" řadiče;
- měnit zapojení pod napájením;
- předpokládat, že libovolný GPIO vyhovuje jakémukoli úkolu;
- ignorovat zahřívání řadiče;
- připojit externí moduly bez společné země když je potřeba.

## Klíčové body

- Řadič řídí ale nenápájí přímo zátěž.
- Logika 3,3V a 5V musí být kompatibilní.
- GPIO je signál, ne napájení.
- Pro Klipperem MCU často hledáte RP2040/STM32, ESP32 je pohodlnější jako autonomní Wi-Fi zařízení.
- Firmware a pinout se musí shodovat se skutečným řadičem.
- Pokud se řadič zahřívá nebo přestane být detekován, vypněte napájení a najděte chybu v připojení.

## Reference

- [Klipper: Installation](https://www.klipper3d.org/Installation.html) - obecný proces přípravy a nahrání MCU pro Klipper.
- [Klipper: Config Reference, MCU](https://www.klipper3d.org/Config_Reference.html#mcu) - sekce `[mcu]`, sériové/CAN připojení a dodatečné MCU.
- [Arduino: Digital Pins](https://docs.arduino.cc/learn/microcontrollers/digital-pins/) - základní vysvětlení digitálních pinů jako vstupů/výstupů, ne napájení.
- [Espressif ESP32 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf) - oficiální elektrické specifikace ESP32.
- [Raspberry Pi Pico Datasheet](https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf) - oficiální data na RP2040/Pico, napájení a GPIO.
