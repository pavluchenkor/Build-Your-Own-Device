---
title: "Démarrage du firmware sur idryer-core : premier lancement et connexion au portail"
description: "Création d'un projet PlatformIO basé sur idryer-core : platformio.ini, secrets.h, Config de l'appareil, premier flashage d'ESP32 et connexion au portail iDryer."
---

# Démarrage du firmware sur le cœur

Sur cette page, vous créez un projet de firmware, mettez l'ESP32 en état Online sur le portail et vérifiez que la partie réseau fonctionne. Les capteurs et la logique de chauffage seront ajoutés aux étapes suivantes.

L'approche est construite sur la façade `iDryer::Link`. Vous décrivez l'appareil avec une seule structure `iDryer::Config`, appelez `link.begin()` et `link.loop()` — le cœur gère automatiquement toute la connexion au réseau.

## 1. Préparez les outils

Vous aurez besoin de :

- VS Code avec l'extension PlatformIO ;
- Un câble USB ;
- Un réseau Wi-Fi `2.4 GHz` (ESP32 ne fonctionne pas avec les réseaux uniquement `5 GHz`).

Ce qu'est le firmware du contrôleur et comment il arrive sur la carte — [Flashage du contrôleur](../02-controllers/11-flashing-controller.md).

## 2. Créez un projet

Dans PlatformIO, un projet est un dossier avec une structure fixe. Créez un dossier de projet (par exemple `my-cabinet`) et ouvrez-le dans VS Code. À l'intérieur, vous devez avoir ces fichiers :

```text
my-cabinet/
├── platformio.ini        # paramètres de compilation (remplis à l'étape 4)
├── include/
│   └── secrets.h         # login et mot de passe Wi-Fi (étape 3)
├── lib/
│   └── idryer-core/      # bibliothèque du cœur (lien symbolique ou copie)
└── src/
    └── main.cpp          # code de l'appareil : Config + setup() + loop()
```

Tous les fragments de code ci-dessous vont exactement dans ces fichiers — chaque étape indique dans lequel. Créez manuellement les dossiers `include/`, `lib/` et `src/` s'ils n'existent pas.

Mettez la bibliothèque `idryer-core` dans `lib/` — PlatformIO trouve automatiquement les bibliothèques là. La façon la plus simple est de faire un lien symbolique vers la bibliothèque téléchargée :

```bash
ln -s /chemin/vers/idryer-core lib/idryer-core
```

Ceci est également requis pour la génération du menu (chapitre 6) — le hook cherche le générateur à l'intérieur de `lib/idryer-core/`.

## 3. Créez secrets.h

Copiez l'exemple `secrets.h.example` de la bibliothèque dans `include/secrets.h` de votre projet et entrez les données de votre réseau :

```cpp
#define WIFI_SSID      "your-ssid"
#define WIFI_PASSWORD  "your-password"
```

Ajoutez `include/secrets.h` à `.gitignore` pour que le mot de passe ne se retrouve pas dans le dépôt.

## 4. Configurez platformio.ini

Remplissez `platformio.ini` à la racine du projet :

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

Remplacez `board` par votre carte (par exemple, `esp32-s3-devkitc-1`). Pas besoin de spécifier `idryer-core` dans `lib_deps` — elle se trouve dans `lib/` (étape 2).

!!! note "Pourquoi toutes ces dépendances"
    `ArduinoJson`, `PubSubClient`, `base64`, `WebSockets` et `Improv-WiFi-Library` sont nécessaires pour la bibliothèque `idryer-core` elle-même (MQTT, accès WebSocket par LAN, provisionnement Wi-Fi). Sans aucune d'elles, la compilation échouera avec une erreur du type `... .h: No such file`. Les drapeaux `MQTT_BROKER` et `MQTT_PORT` sont également obligatoires — sans eux, le cœur ne se compilera pas (`'MQTT_BROKER' was not declared`).

## 5. Décrivez l'appareil dans Config

À partir de maintenant, tout se passe dans un seul fichier — `src/main.cpp`. Ouvrez-le et entrez le code de cette étape et des suivantes.

`iDryer::Config` est le passeport de l'appareil. Les drapeaux `has*` indiquent au portail ce que possède l'appareil et déterminent quels champs de télémétrie sont publiés.

Pour un armoire chauffée, au début de `src/main.cpp`

```cpp
#include <iDryer.h>

static const iDryer::Config CFG = {
    .deviceType        = iDryer::DeviceType::Dryer,
    .unitsCount        = 1,
    // Périphériques :
    .hasHeater         = true,    // chauffage contrôlable
    .hasFan            = true,    // ventilateur
    .hasAirTemp        = true,    // température de l'air (SHT31)
    .hasAirHumidity    = true,    // humidité de l'air (SHT31)
    .hasHeaterTemp     = true,    // température du chauffage (thermistance)
    // Périodes de publication automatique :
    .telemetryPeriodMs = 5000,
    .statusPeriodMs    = 10000,
    // Identification sur le portail :
    .hardwareVersion   = "1.0",
    .firmwareVersion   = "0.1.0",
    .model             = "DIY Storage Cabinet",
};

static iDryer::Link s_link(CFG);
```

!!! note "Les drapeaux has* — c'est un contrat avec le portail"
    Un champ de télémétrie dont le drapeau correspondant `has*` est `false` ne sera pas publié. Par exemple, sans `hasAirHumidity = true`, l'humidité ne sera pas envoyée au cloud, même si vous l'écrivez dans le code. N'activez que ce qui est physiquement présent sur l'appareil.

Liste des composants et drapeaux — [Composition du système](02-bom.md).

## 6. Fonction principale minimale

Dans le même fichier, après le bloc `Config`, ajoutez les fonctions `setup()` et `loop()`. Pour le premier lancement, il suffit d'initialiser le lien et de l'exécuter dans `loop()` :

```cpp
void setup() {
    Serial.begin(115200);
    s_link.begin();
}

void loop() {
    s_link.loop();
}
```

Cela suffit pour que l'appareil se connecte à Wi-Fi et se présente au portail. Les capteurs seront ajoutés à l'étape [Capteurs](05-sensors.md).

### `src/main.cpp` complet après ce chapitre

Prenez les deux blocs ci-dessus dans un seul fichier — c'est tout `src/main.cpp` à cette étape :

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

Le chapitre précédent montre **ce qu'il faut ajouter** et le **`src/main.cpp` complet après les modifications**, afin que vous voyiez toujours l'image complète, et non des fragments épars.

## 7. Flashez

```bash
pio run -e cabinet -t upload
```

## 8. Ouvrez Serial Monitor

```bash
pio device monitor -b 115200
```

Séquence attendue dans le journal :

```text
[CLOUD] Connecting to WiFi...
[CLOUD] WiFi connected, IP: 192.168.1.42
[CLOUD] Provisioning device...
[CLOUD] PIN: 1234567 (expires in 600s)
```

Si l'appareil s'est arrêté à la ligne `PIN: ...` — c'est normal. Procédez à la connexion.

## 9. Connectez l'appareil au portail

1. Ouvrez [portal.idryer.org](https://portal.idryer.org/).
2. Allez à la section **Add device**.
3. Entrez le PIN du Serial Monitor.

Après la connexion, l'appareil passera au statut `Online`. Le journal affichera :

```text
[CLOUD] Device claimed!
[CLOUD] MQTT connected!
```

## Vérification du résultat

À cette étape, l'appareil doit être Online sur le portail. Aucune donnée de capteur pour l'instant — c'est normal. Si l'appareil ne se connecte pas :

- vérifiez que le réseau `2.4 GHz` et le mot de passe dans `secrets.h` sont corrects ;
- vérifiez l'alimentation de l'ESP32 (les baisses de tension au démarrage du Wi-Fi sont une cause fréquente de redémarrages) ;
- consultez [Erreurs d'alimentation](../08-common-mistakes/02-power-mistakes.md) et [Erreurs de contrôleur](../08-common-mistakes/04-controller-mistakes.md).

## Prochaines étapes

La partie réseau fonctionne. Passez à [Capteurs](05-sensors.md) : nous allons brancher le SHT31 et la thermistance et voir leurs données sur le portail.
