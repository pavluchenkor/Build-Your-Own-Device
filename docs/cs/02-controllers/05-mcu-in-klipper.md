# MCU v Klipperu

Klipper se skládá ze dvou hlavních částí:

- **host** — Linux počítač s Klipperem, například Raspberry Pi, Orange Pi, mini-PC nebo jiné zařízení;
- **MCU** — deska mikrokontroléru, která fyzicky ovládá piny.

Host dělá vysokoúrovňová rozhodnutí, čte konfiguraci, zpracovává G-code a plánuje akce. MCU provádí přesné příkazy na hardwaru: přepíná výstupy, čte vstupy, počítá čas, generuje PWM a hlášení stav zpět do hostu.

## Co je MCU v Klipperu

MCU je zkratka pro mikroprocesorovou jednotku.

V kontextu Klipperu je to konkrétní deska:

- hlavní deska 3D tiskárny;
- oddělená deska RP2040;
- oddělená deska STM32;
- deska CAN/hlava nástrojů;
- dodatečná deska I/O.

MCU "nemyslí jako celá tiskárna." Provádí nízkoúrovňové příkazy poslané hostem. Toto rozdělení činí Klipper flexibilním: můžete přidat druhý nebo třetí MCU a jeho piny použít v jedné sdílené konfiguraci.

## Jak to vypadá

Zjednodušené schéma:

![Host Klipperu a několik MCU](../../img/02-controllers/05-klipper-host-mcu-architecture.svg)

Host komunikuje s MCU přes USB, UART nebo CAN. V konfiguraci Klipperu dostane každý MCU svou sekci a piny tohoto MCU se pak používají v nastavení ventilátoru, sensoru, topidla, výstupu a dalších modulů.

## Co dělá host

Host:

- ukládá a čte `printer.cfg`;
- přijímá G-code a uživatelské příkazy;
- udržuje vysokoúrovňovou logiku;
- plánuje akce v čase;
- synchronizuje komunikaci s MCU;
- rozhoduje, kdy zapnout ventilátor, topidlo či jiný výstup;
- přijímá čtení a stav z MCU.

Host neaplikuje proud na ventilátor a nečte termistor přímo, pokud jsou tyto piny na externí desce. Říká MCU, co má dělat.

## Co dělá MCU

MCU:

- fyzicky ovládá GPIO;
- čte vstupy a sensory;
- generuje PWM;
- provádí příkazy ve správný čas;
- hlásí výsledky do hostu;
- vejde do shutdown na chyby, pokud je firmware a konfigurace nastavena tak.

Například pokud konfigurace má ventilátor na pinu `PA8`, je právě MCU s tímto pinem, který změní svůj stav. Host pouze posílá příkaz.

## Co znamená `[mcu]`

V `printer.cfg` sekce `[mcu]` popisuje mikrokontroleér, ke kterému se má Klipper připojit.

Příklad pro USB/sériový:

```ini
[mcu]
serial: /dev/serial/by-id/usb-Klipper_stm32f446xx_...
```

Pro dodatečný MCU se používá jméno:

```ini
[mcu chamber]
serial: /dev/serial/by-id/usb-Klipper_rp2040_...
```

Poté lze pinům dodatečného MCU zadat předponu:

```ini
[temperature_sensor chamber_air]
sensor_type: Generic 3950
sensor_pin: chamber:gpio26

[fan_generic chamber_fan]
pin: chamber:gpio15
```

Logika je jednoduchá: `chamber:gpio15` znamená "pin `gpio15` na MCU pojmenovaném `chamber`".

## Jména pinů a předpony

Klipper používá jména pinů hardwaru.

Příklady:

- pro STM32: `PA4`, `PB0`, `PC13`;
- pro RP2040: `gpio15`, `gpio26`;
- pro Arduino/AVR mohou být vlastní aliasy.

Před jménem pinu mohou být symboly:

- `!` — invertovat logiku;
- `^` — povolit pull-up, pokud MCU podporuje;
- `~` — povolit pull-down, pokud MCU podporuje.

Příklad:

```ini
[gcode_button chamber_door]
pin: ^chamber:gpio12
```

To není "Klipperova kouzla", ale konkrétní nastavení vstupního pinu na konkrétním MCU. Takže rozložení pinů desky musí být přesné.

## Proč je potřeba dodatečný MCU

Dodatečný MCU je užitečný, když potřebujete separovat periferie do samostatného bloku.

Příklady pro zařízení podobná iDryer:

- sensory teploty a vlhkosti komory;
- oběhový ventilátor;
- filtr ventilátor;
- podsvícení;
- tlačítko dveří;
- senzor víka;
- servo tlumidla;
- oddělený modul s měřítkem zátěže;
- dodatečný OLED nebo RFID;
- nouzový vstup, který je pohodlnější směrovat blízko zařízení.

Tento přístup je vhodný, když by mělo zařízení být součástí Klipperu, nikoli samostatná Wi-Fi krabička.

## MCU přístup nebo samostatný kontrolér

Existují dvě různé cesty.

**MCU v Klipperu**:

- zařízení je řízeno z `printer.cfg`;
- piny jsou viditelné Klipperu;
- můžete použít existující sekce jako `fan_generic`, `temperature_sensor`, `heater_generic`, `output_pin`;
- stav je viditelný v rozhraní Klipperu;
- komunikace s hostem je povinná.

**Samostatný kontrolér**:

- zařízení si dělá vlastní rozhodnutí;
- může mít Wi-Fi, webové rozhraní, MQTT;
- nemusí záviset na tiskárně;
- vyžaduje vlastní firmware a bezpečnostní logiku;
- se nepřipojuje jako normální `[mcu]` v Klipperu.

ESP32 je často dobrý na samostatné Wi-Fi zařízení. RP2040 a STM32 jsou často pohodlnější jako drátový MCU v Klipperu.

## USB, UART a CAN

Komunikace mezi hostem a MCU může být různá.

**USB** — nejběžnější a jednoduchý na jednu nebo dvě desky blízko hostu. Pohodlný na Pico, desky STM32 a mnoho desek tiskáren.

**UART** — sériová komunikace přes oddělené piny TX/RX. Může být užitečný na některých deskách, ale vyžaduje opatrné připojení úrovně, zem a rychlosti.

**CAN** — pohodlný pro vzdálené moduly, desky hlav nástrojů a stabilnější drátovou architekturu. Ale CAN vyžaduje podporovaný mikrokontroleér, CAN transceiver, správnou sběrnici, terminátory a nastavení rozhraní Linuxu.

Na první dodatečný kontrolér je USB obvykle jednodušší. CAN má smysl, když je skutečný důvod: delší zapojení, více uzlů, deska hlavy nástrojů nebo existující infrastruktura CAN.

## MCU nechrání sekci napájení

Důležité: přidání MCU neučiní zátěž bezpečnou.

Pokud MCU řídí ventilátor, topidlo nebo SSR, stále potřebujete:

- správný spínač napájení;
- správné napájení;
- vodiče a svorky na proud;
- pojistku;
- nezávislou tepelnou ochranu topidla;
- bezpečné pouzdro;
- ověření chování, pokud komunikace bude ztracena nebo je host vypnut.

Pokud hostitel ztratí komunikaci s MCU, Klipper může systém vypnout, ale nenahrazuje hardwarovou ochranu. Topidlo by mělo být navrženo tak, aby selhání firmwaru, senzoru, SSR nebo komunikace nevedlo k nebezpečnému režimu.

## Co zkontrolovat před výběrem MCU

Před nákupem desky na MCU Klipperu zkontrolujte:

- zda je mikrokontroleér podporován Klipperem;
- zda existuje hotová konfigurace nebo pokyny pro desku;
- která metoda komunikace je potřebná: USB, UART nebo CAN;
- jak se deska nahraje;
- zda máte dost GPIO, ADC, PWM, I2C, SPI, UART;
- které piny jsou skutečně exponované;
- jaká logika GPIO: obvykle `3.3V`;
- zda jsou potřebné drivery/MOSFET/SSR na zátěž;
- zda je dokumentace na napájení a rozložení pinů;
- co se stane, pokud komunikace s MCU bude ztracena.

Na první dodatečný MCU je obvykle jednodušší vybrat RP2040/Pico nebo známou desku STM32 s jasnými pokyny.

## Běžné chyby

- myšlenka, že MCU obsahuje veškerou logiku Klipperu;
- plení si host a MCU;
- přidání `[mcu chamber]`, ale pak zadání pinů bez předpony `chamber:`;
- převzetí pinu z něčího rozložení pinů;
- nahrání špatného typu mikrokontroléru v `make menuconfig`;
- nekontrolování offsetu bootloaderu a metody nahrávání desky;
- používání nestabilního USB kabelu;
- připojení `5V` na `3.3V` vstup;
- napájení zátěže z GPIO;
- myšlenka, že softwarové vypnutí nahrazuje pojistku a tepelnou pojistku.

## Klíčové body

V Klipperu je MCU deska, která fyzicky ovládá piny, a host plánuje a koordinuje práci. Dodatečný MCU vám umožní rozšířit systém a přesunout periferie blíž k zařízení.

Na úlohy podobné iDryer je to pohodlné na ventilátory, sensory, filtry, podsvícení, tlačítka a některé pohony. Ale sekce napájení a bezpečnost topidla zůstávají samostatným hardwarovým úkolem.

## Související materiály

- [Klipper: Code overview](https://www.klipper3d.org/Code_Overview.html) — architektura Klipperu, dělení kódu hostu a mikrokontroléru, model timingu a GPIO.
- [Klipper: Configuration reference - Micro-controller configuration](https://www.klipper3d.org/Config_Reference.html#micro-controller-configuration) — `[mcu]`, dodatečný `[mcu name]`, formát jména pinu a předpony.
- [Klipper: Installation - Building and flashing the micro-controller](https://www.klipper3d.org/Installation.html#building-and-flashing-the-micro-controller) — obecný postup `make menuconfig`, stavby a nahrávání MCU.
- [Klipper: Bootloaders](https://www.klipper3d.org/Bootloaders.html) — proč se bootloadery liší mezi deskami a proč bootloader záleží.
- [Klipper: CANBUS](https://www.klipper3d.org/CANBUS.html) — komunikace CAN, `canbus_uuid`, USB-to-CAN most a hardwarové požadavky.
