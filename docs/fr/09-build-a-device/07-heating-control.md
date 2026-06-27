---
title: "Contrôle du chauffage du cabinet : maintien de la température et ventilateur"
description: "Logique du cabinet chauffé sur idryer-core : maintien de la température cible par hystérésis, protection du radiateur par thermistance, ventilateur et commandes du portail."
---

# Contrôle du chauffage

Cette page vous montre comment connecter les capteurs, les paramètres et la partie puissance dans une logique opérationnelle. Le dispositif maintient une température définie dans le cabinet, protège le radiateur de la surchauffe et répond aux commandes du portail.

La logique s'exécute dans `loop()` à proximité de la maintenance du réseau. Tous les minuteurs et seuils sont non-bloquants, sans `delay()`.

## Ce qui doit se passer

Le comportement du cabinet repose sur trois règles simples :

1. **Maintien de la température.** Si l'air du cabinet est plus froid que la cible d'une quantité d'hystérésis — allumer le chauffage. Une fois la cible atteinte — éteindre.
2. **Protection du radiateur.** La thermistance contrôle le radiateur lui-même. S'il surchauffe au-delà du seuil autorisé — le chauffage s'éteint indépendamment de la température de l'air.
3. **Ventilateur.** Il s'allume pour distribuer la chaleur dans le cabinet, et s'éteint quand le chauffage n'est pas nécessaire.

## Commutateurs du radiateur et du ventilateur

Le contrôleur allume le radiateur et le ventilateur via un commutateur : module MOSFET (version A) ou SSR (version B) — voir [Schéma de câblage](03-wiring.md). Du point de vue du code, c'est simplement une broche GPIO : `HIGH` — allumée, `LOW` — éteinte.

Décrivons un tel commutateur avec une petite structure et créons deux instances — pour le radiateur et le ventilateur. Ajoutez ceci à `src/main.cpp` (avant `setup()`) :

```cpp
struct GpioOutput {
    int pin;
    void begin() { pinMode(pin, OUTPUT); digitalWrite(pin, LOW); }
    void on()    { digitalWrite(pin, HIGH); }
    void off()   { digitalWrite(pin, LOW); }
};

static GpioOutput myHeater{4};   // GPIO4 — contrôle du radiateur
static GpioOutput myFan{5};      // GPIO5 — contrôle du ventilateur
```

Les numéros de broches sont les mêmes que dans le [Schéma de câblage](03-wiring.md). Dans `setup()`, les deux commutateurs doivent être initialisés : `myHeater.begin();` et `myFan.begin();`.

!!! warning "État sûr au démarrage"
    `begin()` met immédiatement `LOW` — le radiateur et le ventilateur sont éteints jusqu'à ce que la logique décide autrement. C'est important : à la mise sous tension, le radiateur ne doit pas se retrouver accidentellement allumé.

## Maintien de la température par hystérésis

Pour un cabinet à `40–45 °C`, une hystérésis simple suffit : le chauffage s'allume et s'éteint autour de la cible. C'est plus simple qu'un PID complet et fonctionne de manière fiable pour un maintien doux de la chaleur.

La température cible et l'hystérésis proviennent du menu (`menu.target_temp`, `menu.hysteresis`) — il est déjà connecté dans le [chapitre 6](06-menu.md). Ajoutez un drapeau d'état et une fonction de décision :

```cpp
static bool s_heating = false;

static void controlLoop() {
    float air    = s_link.telemetry.airTempC[0];     // SHT31
    float target = (float)menu.target_temp;          // du menu
    float hyst   = (float)menu.hysteresis;           // du menu

    if (air < target - hyst) {
        s_heating = true;     // refroidi — chauffer
    } else if (air >= target) {
        s_heating = false;    // cible atteinte — arrêt
    }
}
```

La température cible et l'hystérésis sont obtenues à partir du [menu](06-menu.md) — l'utilisateur les modifie depuis le portail.

## Protection du radiateur par thermistance

L'air se réchauffe lentement, mais la spirale du radiateur se réchauffe rapidement. Sans contrôle séparé, le radiateur aura le temps de surchauffer avant que l'air n'atteigne la cible. C'est pourquoi la thermistance du radiateur définit une limite stricte.

```cpp
static const float HEATER_MAX_C = 80.0f;   // plafond de température du radiateur

static void applyHeater() {
    float heaterTemp = s_link.telemetry.heaterTempC[0];   // thermistance

    bool allow = s_heating && heaterTemp < HEATER_MAX_C;

    if (allow) {
        myHeater.on();
        s_link.telemetry.heaterPower01[0] = 1.0f;   // refléter dans la télémétrie
    } else {
        myHeater.off();
        s_link.telemetry.heaterPower01[0] = 0.0f;
    }
}
```

!!! warning "Le plafond du radiateur est une protection, pas un réglage climatique"
    `HEATER_MAX_C` limite la température du radiateur lui-même, pas l'air. La valeur dépend de la conception du radiateur et des matériaux du boîtier. Choisissez-la avec une marge en dessous de la température à laquelle les pièces imprimées se déforment — voir [Matériaux thermostables](../07-3d-printing/04-heat-resistant-materials.md).

Pour un chauffage plus fluide au lieu d'un mode tout ou rien, vous pouvez contrôler la puissance via PWM, et le champ `heaterPower01[0]` accepte des valeurs de `0.0` à `1.0`. Pour un cabinet avec maintien doux de la chaleur, la logique simple ci-dessus est généralement suffisante.

## Ventilateur

Le ventilateur distribue la chaleur dans le cabinet. La logique la plus simple consiste à l'allumer avec le chauffage :

```cpp
static void applyFan() {
    bool fanOn = s_heating;          // tourner pendant que nous chauffons
    if (fanOn) myFan.on(); else myFan.off();
    s_link.telemetry.fanOn[0] = fanOn;   // refléter dans la télémétrie
}
```

Dans le contrôleur en série, le ventilateur est contrôlé par la température avec des seuils d'allumage et d'extinction séparés (par exemple, allumage à `55 °C`, extinction à `35 °C`), pour qu'il ne vibre pas à la limite. Pour le cabinet, vous pouvez appliquer la même approche, en reliant les seuils aux paramètres du menu.

## Assemblage dans loop()

```cpp
void loop() {
    s_link.loop();          // réseau et publication automatique

    // capteurs (voir l'étape « Capteurs ») :
    s_climate.tick(millis());
    SensorReading c = s_climate.get();
    if (c.ok) {
        s_link.telemetry.airTempC[0]       = c.temperature;
        s_link.telemetry.airHumidityPct[0] = c.humidity;
    }
    s_link.telemetry.heaterTempC[0] = readHeaterTempC();

    controlLoop();   // décider de chauffer ou non
    applyHeater();   // appliquer au radiateur + protection
    applyFan();      // appliquer au ventilateur
}
```

Les champs de télémétrie (`heaterPower01`, `fanOn`) sont publiés par la façade elle-même — sur le portail, vous voyez si le dispositif chauffe actuellement et si le ventilateur fonctionne.

## Commandes du portail

Le démarrage et l'arrêt du maintien de la chaleur sont envoyés par le portail sous forme de commandes. Le gestionnaire est enregistré par la méthode `s_link.onCommand(nom, rappel)` — **après** `s_link.begin()`. Les commandes d'action arrivent avec le nom `invoke` et un champ `action` (rôle du menu, par exemple `storage.start` / `storage.stop`).

Pour analyser JSON, vous avez besoin des en-têtes `<ArduinoJson.h>` et `<string.h>` (pour `strcmp`) — ajoutez-les au reste des `#include` au début du fichier. Le gestionnaire lui-même est placé dans `setup()` :

```cpp
s_link.onCommand("invoke", [](JsonObjectConst data) {
    const char* action = data["action"] | "";
    if (strcmp(action, "storage.start") == 0) {
        s_heating = true;
        s_link.status.mode[0]        = iDryer::UnitMode::Storage;
        s_link.status.targetTempC[0] = (float)menu.target_temp;
        s_link.publishStatusNow();
    } else if (strcmp(action, "storage.stop") == 0) {
        s_heating = false;
        myHeater.off();
        s_link.status.mode[0] = iDryer::UnitMode::Idle;
        s_link.publishStatusNow();
    }
});
```

- `storage.start` / `storage.stop` — les mêmes rôles que vous avez définis dans le [menu](06-menu.md); le portail affiche les boutons correspondants.
- `iDryer::UnitMode::Storage` — mode de maintien doux de la chaleur. C'est le mode principal du cabinet.
- `s_link.status.mode[0]` et `targetTempC[0]` affichent l'état actuel de la chambre sur le portail.
- Appelez `publishStatusNow()` après chaque modification d'état pour que le portail le voie immédiatement, sans attendre le minuteur.

!!! warning "Pas de delay() dans le gestionnaire"
    Le gestionnaire `onCommand` est appelé depuis un rappel réseau. Tout blocage à l'intérieur brise la session MQTT. Modifiez les drapeaux et l'état, et effectuez le travail lui-même dans `loop()`.

## Fichier `src/main.cpp` complet après ce chapitre

C'est le fichier final et complété du dispositif. Les nouvelles lignes par rapport au chapitre précédent sont marquées `// ← chapitre 7`. Ce même fichier se trouve comme exemple prêt à l'emploi dans le dossier `example/09-cabinet/` du dépôt et est compilé par la commande `pio run -e cabinet`.

??? note "Ce qui était — `src/main.cpp` après le chapitre 6"

    ```cpp
    #include <iDryer.h>
    #include <Wire.h>
    #include <math.h>
    #include "Sht31ClimateSensor.h"
    #include <menu_state.h>

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

    static Sht31ClimateSensor s_climate(&Wire);
    static bool               s_climateOk = false;

    static const int   THERM_PIN  = 2;
    static const float SERIES_R   = 4700.0f;
    static const float NOMINAL_R  = 100000.0f;
    static const float NOMINAL_T  = 25.0f;
    static const float BETA       = 3950.0f;

    static float readHeaterTempC() {
        int   raw = analogRead(THERM_PIN);
        float v   = (float)raw / 4095.0f;
        float r   = SERIES_R * (1.0f - v) / v;
        float tK  = 1.0f / (1.0f / (NOMINAL_T + 273.15f) + logf(r / NOMINAL_R) / BETA);
        return tK - 273.15f;
    }

    void setup() {
        Serial.begin(115200);
        Wire.begin(8, 9);
        s_climateOk = s_climate.begin();
        menu.initDefaults();
        s_link.begin();
    }

    void loop() {
        s_link.loop();

        if (s_climateOk) {
            s_climate.tick(millis());
            SensorReading r = s_climate.get();
            if (r.ok) {
                s_link.telemetry.airTempC[0]       = r.temperature;
                s_link.telemetry.airHumidityPct[0] = r.humidity;
            }
        }
        s_link.telemetry.heaterTempC[0] = readHeaterTempC();
    }
    ```

```cpp
#include <Wire.h>
#include <ArduinoJson.h>          // ← chapitre 7 (onCommand: JsonObjectConst)
#include <string.h>              // ← chapitre 7 (strcmp)
#include <math.h>
#include <iDryer.h>
#include "Sht31ClimateSensor.h"
#include <menu_state.h>

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

static Sht31ClimateSensor s_climate(&Wire);
static bool               s_climateOk = false;

static const int   THERM_PIN  = 2;
static const float SERIES_R   = 4700.0f;
static const float NOMINAL_R  = 100000.0f;
static const float NOMINAL_T  = 25.0f;
static const float BETA       = 3950.0f;

static float readHeaterTempC() {
    int   raw = analogRead(THERM_PIN);
    float v   = (float)raw / 4095.0f;
    float r   = SERIES_R * (1.0f - v) / v;
    float tK  = 1.0f / (1.0f / (NOMINAL_T + 273.15f) + logf(r / NOMINAL_R) / BETA);
    return tK - 273.15f;
}

// ← chapitre 7 : commutateurs du radiateur et du ventilateur
struct GpioOutput {
    int pin;
    void begin() { pinMode(pin, OUTPUT); digitalWrite(pin, LOW); }
    void on()    { digitalWrite(pin, HIGH); }
    void off()   { digitalWrite(pin, LOW); }
};
static GpioOutput myHeater{4};
static GpioOutput myFan{5};

// ← chapitre 7 : logique de maintien de la température
static bool        s_heating    = false;
static const float HEATER_MAX_C = 80.0f;

static void controlLoop() {
    float air    = s_link.telemetry.airTempC[0];
    float target = (float)menu.target_temp;
    float hyst   = (float)menu.hysteresis;
    if (air < target - hyst)  s_heating = true;
    else if (air >= target)   s_heating = false;
}

static void applyHeater() {
    float heaterTemp = s_link.telemetry.heaterTempC[0];
    bool  allow = s_heating && heaterTemp < HEATER_MAX_C;
    if (allow) myHeater.on(); else myHeater.off();
    s_link.telemetry.heaterPower01[0] = allow ? 1.0f : 0.0f;
}

static void applyFan() {
    if (s_heating) myFan.on(); else myFan.off();
    s_link.telemetry.fanOn[0] = s_heating;
}

void setup() {
    Serial.begin(115200);
    Wire.begin(8, 9);
    s_climateOk = s_climate.begin();
    myHeater.begin();              // ← chapitre 7
    myFan.begin();                 // ← chapitre 7
    menu.initDefaults();
    s_link.begin();

    s_link.onCommand("invoke", [](JsonObjectConst data) {   // ← chapitre 7
        const char* action = data["action"] | "";
        if (strcmp(action, "storage.start") == 0) {
            s_heating = true;
            s_link.status.mode[0]        = iDryer::UnitMode::Storage;
            s_link.status.targetTempC[0] = (float)menu.target_temp;
            s_link.publishStatusNow();
        } else if (strcmp(action, "storage.stop") == 0) {
            s_heating = false;
            myHeater.off();
            s_link.status.mode[0] = iDryer::UnitMode::Idle;
            s_link.publishStatusNow();
        }
    });
}

void loop() {
    s_link.loop();

    if (s_climateOk) {
        s_climate.tick(millis());
        SensorReading r = s_climate.get();
        if (r.ok) {
            s_link.telemetry.airTempC[0]       = r.temperature;
            s_link.telemetry.airHumidityPct[0] = r.humidity;
        }
    }
    s_link.telemetry.heaterTempC[0] = readHeaterTempC();

    controlLoop();   // ← chapitre 7
    applyHeater();   // ← chapitre 7
    applyFan();      // ← chapitre 7
}
```

## Vérification du résultat

Après cette étape :

- le démarrage depuis le portail met le cabinet en mode Storage, le dispositif commence à chauffer ;
- la température de l'air remonte jusqu'à la cible et se maintient dans les limites de l'hystérésis ;
- le radiateur ne dépasse pas `HEATER_MAX_C` ;
- le ventilateur et la puissance de chauffage sont visibles dans la télémétrie ;
- l'arrêt depuis le portail éteint le chauffage et bascule en Idle.

## Étape suivante

La logique est prête. Il reste à assembler le dispositif dans le boîtier et le tester sous tension — [Assemblage et vérification](08-assembly-and-check.md).
