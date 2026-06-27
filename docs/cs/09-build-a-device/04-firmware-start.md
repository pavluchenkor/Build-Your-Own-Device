---
title: "Spuštění firmwaru na idryer-core: první spuštění a vazba na portál"
description: "Vytvoření projektu PlatformIO na knihovně idryer-core: platformio.ini, secrets.h, Config zařízení, první firmware pro ESP32 a vazba na portál iDryer."
---

# Spuštění firmwaru na jádru

Na této stránce vytvoříte projekt firmwaru, uvedete ESP32 do stavu Online na portálu a ověříte, že síťová část funguje. Senzory a logiku ohřevu přidáme v dalších krocích.

Přístup je postaven na fasádě `iDryer::Link`. Popisujete zařízení jedinou strukturou `iDryer::Config`, voláte `link.begin()` a `link.loop()` — veškeré připojení k síti jádro provádí samo.

## 1. Připravte si nástroje

Budete potřebovat:

- VS Code s rozšířením PlatformIO;
- USB kabel;
- Wi-Fi síť `2.4 GHz` (ESP32 nefunguje se sítěmi pouze `5 GHz`).

Co je firmware kontroléru a jak se dostane do desky — [Firmware kontroléru](../02-controllers/11-flashing-controller.md).

## 2. Vytvořte projekt

V PlatformIO je projekt složka s pevnou strukturou. Vytvořte složku projektu (například `my-cabinet`) a otevřete ji ve VS Code. Uvnitř by měly být tyto soubory:

```text
my-cabinet/
├── platformio.ini        # nastavení sestavení (vyplníme v kroku 4)
├── include/
│   └── secrets.h         # přihlášení a heslo Wi-Fi (krok 3)
├── lib/
│   └── idryer-core/      # knihovna jádra (symlink nebo kopie)
└── src/
    └── main.cpp          # kód zařízení: Config + setup() + loop()
```

Všechny fragmenty kódu níže se umísťují právě do těchto souborů — v každém kroku je uvedeno, do kterého. Vytvořte složky `include/`, `lib/` a `src/` ručně, pokud neexistují.

Knihovnu `idryer-core` vložte do `lib/` — PlatformIO tam automaticky hledá knihovny. Nejjednodušší je vytvořit symlink na staženou knihovnu:

```bash
ln -s /cesta/k/idryer-core lib/idryer-core
```

To je také nutné pro generování menu (kapitola 6) — háček hledá generátor uvnitř `lib/idryer-core/`.

## 3. Vytvořte secrets.h

Zkopírujte příklad `secrets.h.example` z knihovny do `include/secrets.h` vašeho projektu a zadejte údaje vaší sítě:

```cpp
#define WIFI_SSID      "your-ssid"
#define WIFI_PASSWORD  "your-password"
```

Přidejte `include/secrets.h` do `.gitignore`, aby se heslo nedostalo do repozitáře.

## 4. Nakonfigurujte platformio.ini

Vyplňte `platformio.ini` v kořeni projektu:

```ini
[env:cabinet]
platform    = espressif32
framework   = arduino
board       = esp32-c3-devkitm-1

lib_deps =
    bblanchon/ArduinoJson @ ^6.21.0
    knolleary/PubSubClient
    densaugeo/base64 @ ^1.4.0
    links2004/WebSockets @ ^2.4.0
    https://github.com/jnthas/Improv-WiFi-Library.git

build_flags =
    -DIDRYER_API_BASE='"https://portal.idryer.org/api"'
    -DMQTT_BROKER='"mqtt.idryer.org"'
    -DMQTT_PORT=8883
    -DMQTT_USE_TLS=1
```

Nahraďte `board` svou deskou (například `esp32-s3-devkitc-1`). Samotnou `idryer-core` nemusíte zadávat v `lib_deps` — leží v `lib/` (krok 2).

!!! note "Proč všechny tyto závislosti"
    `ArduinoJson`, `PubSubClient`, `base64`, `WebSockets` a `Improv-WiFi-Library` potřebuje samotná knihovna `idryer-core` (MQTT, WebSocket přístup přes LAN, Wi-Fi provisioning). Bez kteréhokoli z nich se sestavení zhroutí s chybou jako `... .h: No such file`. Příznaky `MQTT_BROKER` a `MQTT_PORT` jsou také povinné — bez nich se jádro nemůže zkompilovat (`'MQTT_BROKER' was not declared`).

## 5. Popište zařízení v Config

Dále se vše odehrává v jednom souboru — `src/main.cpp`. Otevřete jej a zapište kód z tohoto a dalších kroků.

`iDryer::Config` — to je pas zařízení. Příznaky `has*` informují portál, co zařízení má, a určují, která telemetrická pole se publikují.

Pro vytápěnou skříň na začátek `src/main.cpp`

```cpp
#include <iDryer.h>

static const iDryer::Config CFG = {
    .deviceType        = iDryer::DeviceType::Dryer,
    .unitsCount        = 1,
    // Periférie:
    .hasHeater         = true,    // řízený ohřívač
    .hasFan            = true,    // ventilátor
    .hasAirTemp        = true,    // teplota vzduchu (SHT31)
    .hasAirHumidity    = true,    // vlhkost vzduchu (SHT31)
    .hasHeaterTemp     = true,    // teplota ohřívače (termistor)
    // Období autopublikace:
    .telemetryPeriodMs = 5000,
    .statusPeriodMs    = 10000,
    // Identifikace na portálu:
    .hardwareVersion   = "1.0",
    .firmwareVersion   = "0.1.0",
    .model             = "DIY Storage Cabinet",
};

static iDryer::Link s_link(CFG);
```

!!! note "Příznaky has* — to je kontrakt s portálem"
    Pole telemetrie, které má odpovídající příznak `false`, se nepublikuje. Například bez `hasAirHumidity = true` se vlhkost nedostane do cloudu, i když ji napíšete do kódu. Zapínejte pouze to, co je fyzicky v zařízení.

Výčet součástek a příznaků — [Součásti systému](02-bom.md).

## 6. Minimální hlavní

Ve stejném souboru za blokem `Config` přidejte funkce `setup()` a `loop()`. Pro první spuštění stačí inicializovat odkaz a točit jej v `loop()`:

```cpp
void setup() {
    Serial.begin(115200);
    s_link.begin();
}

void loop() {
    s_link.loop();
}
```

To stačí na to, aby se zařízení připojilo k Wi-Fi a vyšlo na portál. Senzory přidáme v kroku [Senzory](05-sensors.md).

### Úplný `src/main.cpp` po této kapitole

Vezměte oba bloky výše do jednoho souboru — to je celý `src/main.cpp` v tomto kroku:

```cpp
#include <iDryer.h>

static const iDryer::Config CFG = {
    .deviceType        = iDryer::DeviceType::Dryer,
    .unitsCount        = 1,
    .hasHeater         = true,
    .hasFan            = true,
    .hasAirTemp        = true,
    .hasAirHumidity    = true,
    .hasHeaterTemp     = true,
    .telemetryPeriodMs = 5000,
    .statusPeriodMs    = 10000,
    .hardwareVersion   = "1.0",
    .firmwareVersion   = "0.1.0",
    .model             = "DIY Storage Cabinet",
};
static iDryer::Link s_link(CFG);

void setup() {
    Serial.begin(115200);
    s_link.begin();
}

void loop() {
    s_link.loop();
}
```

Předchozí kapitola ukazuje, **co přidat** a **úplný `src/main.cpp` po změnách**, aby jste vždy viděli celý obrázek, ne rozprostřené kusy.

## 7. Prošijte

```bash
pio run -e cabinet -t upload
```

## 8. Otevřete Serial Monitor

```bash
pio device monitor -b 115200
```

Očekávaná posloupnost v logu:

```text
[CLOUD] Connecting to WiFi...
[CLOUD] WiFi connected, IP: 192.168.1.42
[CLOUD] Provisioning device...
[CLOUD] PIN: 1234567 (expires in 600s)
```

Pokud se zařízení zastavilo na řádku `PIN: ...` — to je normální. Přejděte na vazbu.

## 9. Navažte zařízení na portál

1. Otevřete [portal.idryer.org](https://portal.idryer.org/).
2. Přejděte do sekce **Add device**.
3. Zadejte PIN ze Serial Monitor.

Po vazbě se zařízení přepne do stavu `Online`. V logu se objeví:

```text
[CLOUD] Device claimed!
[CLOUD] MQTT connected!
```

## Ověření výsledku

V tomto kroku by mělo být zařízení Online na portálu. Data ze senzorů zatím nejsou — to je očekávané. Pokud se zařízení nepřipojuje:

- ověřte, že síť `2.4 GHz` a heslo v `secrets.h` jsou správné;
- ověřte napájení ESP32 (pokles napětí při startu Wi-Fi — časté ústí do restartů);
- podívejte se na [Chyby napájení](../08-common-mistakes/02-power-mistakes.md) a [Chyby kontrolérů](../08-common-mistakes/04-controller-mistakes.md).

## Co dál

Síťová část funguje. Přejděte na [Senzory](05-sensors.md): připojíme SHT31 a termistor a uvidíme jejich data na portálu.
