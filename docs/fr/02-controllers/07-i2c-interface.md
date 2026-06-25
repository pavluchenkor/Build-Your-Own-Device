# Interface I2C

I2C est une interface de communication pour les petites puces et modules proches du contrôleur. Abréviation de : `bus I2C`. Dans la documentation, on parle souvent de `I2C bus`.

Principe de base : plusieurs appareils peuvent être connectés aux mêmes deux lignes de signal `SDA` et `SCL` s'ils ont des adresses différentes.

## Utilisations de l'I2C

Dans les dispositifs simples autour d'une imprimante 3D, I2C est souvent utilisé pour :

- les écrans OLED ;
- les capteurs de température, d'humidité, de pression et de luminosité ;
- les horloges temps réel ;
- les extensions GPIO ;
- certains encodeurs et modules de boutons ;
- les multiplexeurs I2C ;
- certains modules RFID/NFC ;
- les petites cartes auxiliaires.

I2C fonctionne bien pour les connexions courtes à l'intérieur d'un même boîtier. Pour de longs câbles traversant toute l'imprimante ou passant près des lignes d'alimentation, il devient plus risqué.

## SDA, SCL, alimentation et GND

Un module I2C dispose généralement de 4 contacts :

- `VCC` ou `VIN` - alimentation ;
- `GND` - masse commune ;
- `SDA` - données ;
- `SCL` - signal d'horloge.

Un circuit avec plusieurs appareils ressemble à ceci :

![Bus I2C : un maître et trois appareils sur SDA/SCL communs](../../img/02-controllers/07-i2c-bus-topology.svg)

*Source : [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:I2C.svg), Cburnett, CC BY-SA 3.0*

Tous les appareils sur le même bus I2C se connectent aux mêmes `SDA`, `SCL` et `GND`. L'alimentation peut être commune, mais sa tension et ses niveaux logiques doivent être vérifiés pour chaque module.

## Adresses des appareils

Chaque appareil I2C possède une adresse. Par exemple, les petits écrans OLED utilisent souvent `0x3C`, certains capteurs utilisent `0x76`, `0x77`, `0x68`, `0x69`, etc.

Si deux appareils sur le même bus ont la même adresse, le contrôleur ne peut pas les adresser correctement individuellement.

Que faire en cas de conflit d'adresses :

- modifier l'adresse via un cavalier ou un pont de soudure, si le module le permet ;
- choisir une variante de module différente ;
- utiliser un multiplexeur I2C ;
- répartir les appareils sur différents bus I2C, si le contrôleur et le firmware le permettent.

L'adresse est souvent donnée en format hexadécimal (`hex`) : `0x3C`. Mais certains firmwares ou configurations peuvent exiger le format décimal (`decimal`). Par exemple, `0x3C` en décimal vaut `60`. Il faut vérifier la documentation du système concerné.

## Résistances de rappel

Les lignes I2C fonctionnent via des résistances de rappel (pull-up). Les appareils sur le bus peuvent généralement mettre `SDA` ou `SCL` à l'état bas, et le niveau haut provient du rappel vers l'alimentation logique.

Sans résistances de rappel, le bus peut ne pas fonctionner. Mais trop de modules avec leurs propres résistances de rappel sur un même bus peut aussi poser problème : la résistance totale devient trop faible, les lignes sont davantage chargées, les fronts et niveaux du signal peuvent se dégrader.

En pratique :

- beaucoup d'écrans OLED et de cartes capteurs disposent déjà de résistances de rappel ;
- sur un bus court et simple, cela fonctionne généralement immédiatement ;
- en présence de nombreux appareils, il faut vérifier les schémas des modules et les résistances de rappel totales ;
- si le bus est instable, l'une des premières vérifications concerne les résistances de rappel.

Une résistance de départ courante pour un bus séparé est d'environ `4,7 kOhm`, mais les résistances de rappel dans les modules prêts à l'emploi peuvent être différentes.

## 3,3V et 5V

L2C est particulièrement sensible aux niveaux de tension, car `SDA` et `SCL` sont généralement rappelés vers une tension d'alimentation.

ESP32, RP2040 et STM32 fonctionnent généralement avec une logique `3,3V`. Arduino Uno/Nano fonctionne souvent avec une logique `5V`.

Situation dangereuse :

- contrôleur `3,3V` ;
- module I2C alimenté en `5V` ;
- les résistances de rappel du module tirent `SDA` et `SCL` vers `5V`.

Dans ce cas, `5V` peut apparaître sur le GPIO du contrôleur. Cela peut endommager le microcontrôleur.

Avant de connecter, vérifier :

- la tension d'alimentation du module ;
- vers quelle tension `SDA` et `SCL` sont rappelés ;
- si le module dispose d'un convertisseur de niveaux ;
- si le module est compatible avec un contrôleur `3,3V`.

En cas de doute, utiliser une alimentation `3,3V` pour les modules I2C ou un convertisseur de niveaux.

## Vitesse

Vitesses I2C typiques :

```text
100000   # standard mode, 100 kHz
400000   # fast mode, 400 kHz
```

Pour des câbles courts et des modules normaux, `400 kHz` fonctionne souvent. Mais pour des câbles longs, des résistances de rappel faibles, de nombreux appareils ou un environnement bruité, il vaut mieux commencer par `100 kHz`.

Dans Klipper, le paramètre `100000` n'est pas pris en charge de manière uniforme sur tous les MCU. La documentation indique que de nombreux microcontrôleurs utilisent `400000`, tandis que certaines plateformes supportent `400000`. On ne peut donc pas simplement écrire une vitesse élevée et supposer qu'elle est réellement appliquée.

## Scanner I2C

Un scanner I2C est un petit programme ou commande qui parcourt les adresses et indique quels appareils répondent sur le bus.

Il aide à comprendre :

- si le contrôleur voit le module ;
- quelle est l'adresse de l'appareil ;
- si `SDA` et `SCL` sont inversés ;
- s'il y a une alimentation et un `GND` commun ;
- s'il y a un conflit d'adresses.

Mais le scanner ne prouve pas que l'appareil fonctionne complètement. Il indique seulement que quelqu'un répond à cette adresse.

## I2C dans Klipper

Dans Klipper, un appareil I2C est connecté à un MCU spécifique.

La configuration peut inclure les paramètres suivants :

- `i2c_mcu` - à quel MCU l'appareil est connecté ;
- `i2c_bus` - bus I2C matériel, s'il en existe plusieurs ;
- `i2c_software_scl_pin` et `i2c_software_sda_pin` - I2C logiciel sur les broches sélectionnées ;
- `i2c_address` - adresse de l'appareil ;
- `i2c_speed` - vitesse, si prise en charge.

Important : `0x3C` dans Klipper est souvent spécifié en nombre décimal, et non en format hexadécimal. Si la fiche technique indique `60`, la configuration peut exiger `60`.

Si l'appareil est connecté à un MCU supplémentaire, cela doit également être spécifié. Sinon, Klipper le cherchera sur la carte principale.

## Longueur des câbles et interférences

I2C est conçu pour les connexions courtes. À l'intérieur d'un petit boîtier ou sur une seule carte, c'est pratique. Dans une imprimante 3D, les conditions sont moins favorables :

- moteurs à proximité ;
- éléments chauffants à proximité ;
- longs câbles ;
- connecteurs sur les portes ;
- lignes d'alimentation des ventilateurs et des éléments chauffants ;
- interférences électromagnétiques.

Règles pratiques :

- garder `SDA` et `SCL` courts ;
- les router près du `GND` ;
- ne pas les router parallèlement aux câbles d'alimentation des éléments chauffants ;
- ne pas faire de longs câbles plats vers les parties mobiles sans raison ;
- réduire la vitesse à `100 kHz` en cas d'erreurs ;
- utiliser des connecteurs appropriés et un soulagement de tension ;
- pour les connexions longues, choisir une autre interface : UART, CAN, RS-485 ou un MCU local près du capteur.

## Ce qu'il faut vérifier avant de connecter

Avant de connecter un module I2C, vérifier :

- l'alimentation du module ;
- le niveau logique ;
- vers quelle tension `SDA` et `SCL` sont rappelés ;
- l'adresse de l'appareil ;
- si l'adresse peut être modifiée ;
- s'il y a un conflit avec d'autres appareils ;
- la longueur des câbles ;
- si le firmware le supporte ;
- à quel MCU et quel bus l'appareil se connecte ;
- si un I2C matériel ou logiciel est nécessaire.

## Erreurs typiques

- `SDA` et `SCL` inversés ;
- `GND` commun oublié ;
- résistances de rappel `5V` appliquées à un contrôleur `3,3V` ;
- deux appareils avec la même adresse ;
- adresse hexadécimale spécifiée là où une adresse décimale était requise ;
- câbles trop longs utilisés ;
- de nombreux modules avec résistances de rappel connectés ;
- module non pris en charge par le firmware choisi ;
- appareil connecté à un MCU supplémentaire sans spécifier `i2c_mcu` ;
- confusion entre I2C et I2S.

## Conclusion

I2C est pratique pour les petits écrans, capteurs et modules auxiliaires proches du contrôleur. Il nécessite `SDA`, `SCL`, une alimentation et un `GND` commun.

Principales vérifications avant la connexion : adresse, niveaux `3,3V/5V`, résistances de rappel, longueur des câbles et support firmware. Dans l'environnement bruité d'une imprimante, garder I2C court.

## Ressources associées

- [SparkFun : I2C au niveau matériel](https://learn.sparkfun.com/tutorials/i2c/i2c-at-the-hardware-level) - explication pratique de `SDA`, `SCL`, des lignes open-drain et des résistances de rappel.
- [SparkFun : tutoriel I2C](https://learn.sparkfun.com/tutorials/i2c/all) - guide I2C général, adresses, plusieurs appareils sur un bus et caractéristiques matérielles.
- [Adafruit : spécifications techniques STEMMA QT](https://learn.adafruit.com/introducing-adafruit-stemma-qt/technical-specs) - exemple de connecteur I2C standardisé, brochage, alimentation et `GND`.
- [Adafruit : multiplexeur I2C PCA9548](https://learn.adafruit.com/adafruit-pca9548-8-channel-stemma-qt-qwiic-i2c-multiplexer/pinouts) - exemple de résolution des conflits d'adresses I2C en double via un multiplexeur.
- [Référence de configuration Klipper : paramètres I2C communs](https://www.klipper3d.org/Config_Reference.html) - paramètres `i2c_address`, `i2c_mcu`, `i2c_bus`, I2C logiciel et `i2c_speed`.
