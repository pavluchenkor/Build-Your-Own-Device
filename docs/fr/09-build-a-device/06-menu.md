---
title: "Menu de l'appareil à partir du YAML : paramètres dans NVS et sur le portail"
description: "Comment décrire le menu de l'appareil dans idryer-core en menu.yaml : température cible et hystérésis sont sauvegardées dans NVS et affichées par des widgets sur le portail iDryer."
---

# Menu à partir du YAML

Le menu est un ensemble de paramètres de l'appareil : température cible, hystérésis, seuils du ventilateur. Sur `idryer-core`, le menu est décrit par un seul fichier `menu.yaml`, et tout le reste — structures C++, sauvegarde en mémoire non volatile (NVS) et publication sur le portail — est généré automatiquement.

C'est l'un des blocs clés du noyau. Vous n'écrivez pas de code de stockage des paramètres et n'imaginez pas de format pour le portail — vous énumérez simplement les paramètres en YAML.

## Pourquoi un menu

Après les étapes précédentes, l'appareil lit les capteurs, mais tous les seuils sont « codés en dur » dans le code. Le menu résout trois problèmes à la fois :

- **stockage** : les valeurs survivent au redémarrage (NVS) ;
- **gestion à partir du portail** : chaque paramètre devient un widget (curseur, interrupteur) ;
- **source unique de vérité** : un seul fichier décrit à la fois la mémoire et l'interface.

## Comment cela fonctionne

Un seul fichier `menu.yaml` est traité par un générateur lors de la compilation :

```text
menu.yaml → (compilation pio run) → fichiers C++ dans src/menu/ + NVS + JSON pour le portail
```

Un élément avec un champ `role:` est visible du portail et s'affiche avec un widget. Un élément sans `role:` — est privé, uniquement pour la logique interne de l'appareil.

!!! warning "Ne modifiez pas les fichiers générés"
    Les fichiers `menu_state.*`, `menu_bindings.*`, `menu_ids.h` et autres sont créés par le générateur. Ne modifiez que `menu.yaml` et recompilez — sinon vos modifications seront écrasées.

## Étape 1. Copiez le modèle

La bibliothèque contient un modèle de menu. Copiez-le dans votre projet :

```bash
mkdir -p src/menu
cp path/to/idryer-core/menu/menu.template.yaml src/menu/menu.yaml
```

## Étape 2. Activez la génération lors de la compilation

Copiez l'exemple du hook du projet `iDryer-Storage` (vous pouvez le prendre tel quel, il n'y a rien à configurer) :

```bash
mkdir -p extra_scripts
cp path/to/iDryer-Storage/extra_scripts/pre_gen_menu.py extra_scripts/pre_gen_menu.py
```

Puis dans `platformio.ini`, ajoutez à la section `[env:cabinet]` la ligne `-Isrc/menu` (pour que le code voit `#include <menu_state.h>`) et connectez le hook via `extra_scripts` :

```ini
[env:cabinet]
; ... platform / board / lib_deps du chapitre 4 — sans modifications ...

build_flags =
    -Isrc/menu                      ; ← ajouté : chemin vers le menu généré
    -DIDRYER_API_BASE='"https://portal.idryer.org/api"'
    -DMQTT_BROKER='"mqtt.idryer.org"'
    -DMQTT_PORT=8883
    -DMQTT_USE_TLS=1

extra_scripts =                     ; ← ajouté
    pre:extra_scripts/pre_gen_menu.py
```

Le hook trouvera automatiquement le générateur au chemin `lib/idryer-core/menu/menu_gen.py`, donc la bibliothèque doit être connectée via `lib/` (symlink ou copie), comme décrit au chapitre 4.

## Étape 3. Décrivez les paramètres du cabinet

Ouvrez `src/menu/menu.yaml`. Le modèle contient déjà un élément racine `root` avec un tableau `children` et des exemples de paramètres. Supprimez les exemples (`my_param`, `my_flag`, `my_mode_group`) et ajoutez les vôtres dans `children`. Les deux derniers éléments — `units_count` et `language` — conservez-les en place : c'est un contrat fixe avec le portail.

Pour un cabinet de base, quelques paramètres suffisent.

Température cible de stockage :

```yaml
- id: target_temp
  type: value
  role: storage.target_temperature   # rend le paramètre visible comme widget sur le portail
  title: { ru: "ТЕМПЕРАТУРА", en: "TARGET TEMP" }
  unit:  { ru: "°C", en: "°C" }
  vtype: uint16
  min: 30
  max: 50
  step: 1
  bind: target_temp            # clé NVS (≤ 15 caractères)
  persist: true
  scope: global
  default: 45
```

Hystérésis (nombre de degrés que la température peut descendre en dessous de la cible avant que le chauffage se réactive) :

```yaml
- id: hysteresis
  type: value
  title: { ru: "ГИСТЕРЕЗИС", en: "HYSTERESIS" }
  unit:  { ru: "°C", en: "°C" }
  vtype: uint8
  min: 1
  max: 5
  step: 1
  bind: hysteresis
  persist: true
  scope: global
  default: 2
```

!!! note "role: — c'est une liste fermée"
    La valeur `role:` ne peut pas être inventée arbitrairement — elle doit provenir de la liste `canonical_roles` du contrat du noyau. Si aucun rôle approprié n'existe, la compilation s'arrêtera et affichera la liste des rôles autorisés. Pour un cabinet de stockage, les rôles de la famille `storage.*` sont appropriés : `storage.target_temperature`, `storage.target_humidity`, `storage.start`, `storage.stop`. La liste complète se trouve dans l'en-tête `menu.template.yaml`. Les paramètres sans `role:` (comme l'hystérésis ci-dessus) fonctionnent comme des paramètres internes : ils sont sauvegardés dans NVS, mais ne sont pas affichés sur le portail.

Limitations qui ne peuvent pas être violées :

- `bind` — pas plus de 15 caractères (limite de la clé NVS) ;
- n'ajoutez pas le champ `widget:` dans `menu.yaml` — le type de widget est déterminé par le contrat selon `role:`.

!!! warning "Vérifiez l'élément ignore_external_cmd du modèle"
    Le modèle contient un élément `ignore_external_cmd`, et son `bind` comporte 19 caractères, ce qui dépasse la limite de 15. Si vous le laissez tel quel, la génération échouera : `bind 'ignore_external_cmd' ... a 19 caractères, limite 15`. Soit supprimez cet élément, soit raccourcissez `bind` à `ign_ext_cmd` (comme dans les produits réels). Pour un cabinet de base, vous pouvez simplement le supprimer.

## Étape 4. Compilez le projet et vérifiez la génération

```bash
pio run -e cabinet
```

Lors de la compilation, le pre-hook installera automatiquement les dépendances (une seule fois) et générera les fichiers C++ du menu. Si `menu.yaml` n'a pas changé — la génération est omise (`up-to-date`).

Vérifiez que la génération s'est bien déroulée. Le journal de compilation affiche une ligne sur la génération du menu, et dans le dossier `src/menu/` — les fichiers générés :

```text
src/menu/
├── menu.yaml          # votre fichier (source)
├── menu_state.h/.cpp  # objet menu avec tous les paramètres
├── menu_bindings.*    # accès par bind + écriture dans NVS
├── menu_ids.h
└── menu_meta.h        # et autres
```

Si la compilation échoue avec un message sur une `role:` inconnue — cela signifie que le rôle n'est pas dans la liste `canonical_roles`. Corrigez-le et recompilez. Les fichiers marqués comme autogen ne doivent pas être modifiés manuellement.

## Étape 5. Connectez le menu au fichier principal

Pour utiliser le code du menu, connectez deux choses dans `src/main.cpp` :

1. L'en-tête du menu généré :

    ```cpp
    #include <menu_state.h>      // objet menu avec tous les paramètres
    ```

2. Le chargement des valeurs par défaut dans `setup()` — **avant** `s_link.begin()` :

    ```cpp
    menu.initDefaults();         // définir les valeurs par défaut du YAML
    ```

Après cela, les paramètres sont accessibles via l'objet global `menu` :

```cpp
uint16_t target = menu.target_temp;   // accès direct à la valeur
```

Vous utilisez ces valeurs dans la logique de chauffage à l'étape suivante. Lorsque l'utilisateur change un paramètre sur le portail, le noyau applique automatiquement la nouvelle valeur et la sauvegarde dans NVS.

## Fichier complet `src/main.cpp` après ce chapitre

Par rapport au chapitre précédent, seules deux lignes ont été ajoutées (marquées `// ← chapitre 6`) : la connexion du menu et `menu.initDefaults()`.

??? примечание «Avant — `src/main.cpp` après le chapitre 5»

    ```cpp
    #include <iDryer.h>
    #include <Wire.h>
    #include <math.h>
    #include "Sht31ClimateSensor.h"

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
#include <iDryer.h>
#include <Wire.h>
#include <math.h>
#include "Sht31ClimateSensor.h"
#include <menu_state.h>           // ← chapitre 6

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
    menu.initDefaults();           // ← chapitre 6
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

## Vérification du résultat

Après le flashage :

- sur le portail dans la fiche de l'appareil, le paramètre de température cible apparaît ;
- le changement de valeur sur le portail est sauvegardé et survit au redémarrage ;
- les paramètres internes (hystérésis) sont accessibles dans le code via `menu`.

## Étape suivante

Les paramètres sont décrits et stockés. Connectons-les au matériel dans [Gestion du chauffage](07-heating-control.md) : le chauffeur maintient la température cible, le ventilateur s'active selon le seuil.
