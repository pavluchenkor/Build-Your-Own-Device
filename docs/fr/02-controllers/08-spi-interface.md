# Interface SPI

SPI est une interface de communication série rapide entre un contrôleur et des périphériques. Signification : `Serial Peripheral Interface`.

SPI est souvent utilisé lorsque les données doivent être transmises plus rapidement qu'avec I2C, ou lorsque le périphérique est conçu pour SPI : écran, carte SD, module RFID, capteur, pilote ou puce mémoire.

## Domaines d'utilisation de SPI

Dans les imprimantes 3D et les appareils de type iDryer, SPI peut apparaître dans :

- les modules RFID/NFC comme le RC522 ;
- les écrans OLED/TFT ;
- les cartes SD ;
- les accéléromètres pour le correcteur de résonance ;
- les pilotes de moteur pas à pas, par exemple TMC2130/TMC5160 ;
- les puces mémoire ;
- les convertisseurs ADC/DAC et les cartes d'extension ;
- certains capteurs et modules spécialisés.

SPI est généralement plus rapide que I2C, mais nécessite plus de fils et une sélection de broches plus rigoureuse.

## Lignes de base

Un bus SPI typique utilise :

- `SCK` ou `CLK` — signal d'horloge ;
- `MOSI` — données du contrôleur vers le périphérique ;
- `MISO` — données du périphérique vers le contrôleur ;
- `CS`, `SS` ou `NSS` — sélection du périphérique spécifique ;
- `GND` — masse commune ;
- alimentation du module.

Schéma avec deux périphériques :

![SPI: basic exchange operation between master and slave device](../../../img/02-controllers/08-spi-basic-operation.png)

*Source : [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:SPI_basic_operation,_single_Main_%26_Sub.svg), Em3rgent0rdr, CC0 Public Domain*

`SCK`, `MOSI` et `MISO` peuvent être partagés par plusieurs périphériques. Mais chaque périphérique a généralement besoin de sa propre ligne `CS`.

## CS à la place des adresses

En I2C, les périphériques se distinguent par leurs adresses. En SPI, il n'y a généralement pas d'adresses. Le contrôleur sélectionne le périphérique via une ligne `CS` dédiée.

Exemple :

```text
SCK  -> common to all SPI devices
MOSI -> common
MISO -> common
CS1  -> RFID module
CS2  -> display
CS3  -> SD card
```

Lorsque le contrôleur souhaite communiquer avec le module RFID, il active `CS1`. Lorsqu'il souhaite communiquer avec l'écran, il active `CS2`.

Le plus souvent, `CS` est actif à l'état bas : au repos la ligne est à `HIGH`, pour sélectionner un périphérique — à `LOW`. Mais cela doit être vérifié dans la fiche technique.

## MOSI/MISO et nouveaux noms

Dans les anciens schémas très répandus, les noms sont :

- `MOSI` — Master Out Slave In ;
- `MISO` — Master In Slave Out ;
- `SS` — Slave Select.

Dans la documentation plus récente, on peut trouver des noms neutres :

- `PICO` — Peripheral In Controller Out, équivalent à MOSI ;
- `POCI` — Peripheral Out Controller In, équivalent à MISO ;
- `CS` — Chip Select.

Dans l'électronique pour imprimantes 3D, `MOSI`, `MISO`, `SCK`, `CS` restent très courants. L'essentiel est de comprendre la direction du signal et de vérifier le brochage du module spécifique.

## MISO peut ne pas être nécessaire

Tous les périphériques SPI n'envoient pas nécessairement des données en retour.

Par exemple, un écran simple peut uniquement recevoir des commandes et des pixels. Dans ce cas, la ligne `MISO` peut être absente ou inutilisée.

Mais pour les périphériques qui lisent des données, `MISO` est nécessaire :

- module RFID ;
- carte SD ;
- capteur ;
- pilote avec diagnostics ;
- puce mémoire.

Si le module est censé répondre et que `MISO` n'est pas connecté ou est inversé, l'initialisation peut échouer.

## Vitesse et mode SPI

SPI a une vitesse. Elle peut être bien supérieure à I2C, mais cela ne signifie pas qu'il faut immédiatement régler le maximum.

Le fonctionnement est influencé par :

- la longueur des fils ;
- la qualité de la masse ;
- le module et sa fiche technique ;
- le niveau de bruit ;
- la fréquence du contrôleur ;
- le mode SPI choisi.

Le mode SPI est défini par la polarité d'horloge et les paramètres de phase : `CPOL` et `CPHA`. Le mode 0 est souvent utilisé, mais pas toujours. Si le mode est incorrect, le périphérique peut ne pas répondre ou retourner des données incorrectes.

Dans la plupart des bibliothèques prêtes à l'emploi, le mode est déjà configuré. Mais si vous connectez un module inhabituel ou rédigez une configuration bas niveau, vous devez consulter la fiche technique.

## 3,3 V et 5 V

Comme d'autres interfaces, SPI ne garantit pas des niveaux de tension sûrs.

ESP32, RP2040, STM32 et de nombreux modules modernes fonctionnent en logique `3,3 V`. Arduino Uno/Nano utilise souvent `5 V`.

Avant de connecter, vérifiez :

- l'alimentation du module ;
- le niveau logique de `SCK`, `MOSI`, `MISO`, `CS` ;
- s'il y a une adaptation de niveaux ;
- si le module tolère `5 V` sur les entrées de signal ;
- si l'entrée du contrôleur tolère `5 V`.

Par exemple, le RC522 nécessite généralement une alimentation et une logique en `3,3 V`. Le connecter à un Arduino `5 V` sans adaptation de niveaux est une mauvaise idée.

## SPI dans Klipper

Dans Klipper, SPI est utilisé pour divers périphériques : pilotes TMC, accéléromètres, certains écrans et capteurs.

La configuration peut inclure :

- `cs_pin` — broche de sélection du périphérique ;
- `spi_bus` — bus SPI matériel ;
- `spi_speed` — vitesse en Hz ;
- `spi_software_sclk_pin` ;
- `spi_software_mosi_pin` ;
- `spi_software_miso_pin`.

Si le périphérique est connecté à un MCU supplémentaire, les broches doivent appartenir à ce MCU. Comme pour les autres sections Klipper, le brochage de la carte spécifique est plus important que les suppositions.

Exemple approximatif :

```ini
[some_spi_device]
cs_pin: chamber:gpio9
spi_software_sclk_pin: chamber:gpio10
spi_software_mosi_pin: chamber:gpio11
spi_software_miso_pin: chamber:gpio12
```

Ce n'est pas une configuration prête à l'emploi pour un périphérique spécifique, mais une illustration : toutes les broches SPI doivent se trouver sur le MCU auquel le module est réellement connecté.

## Longueur des fils et interférences

SPI peut fonctionner rapidement, mais n'apprécie pas un câblage long et négligé.

Règles pratiques :

- garder `SCK`, `MOSI`, `MISO`, `CS` courts ;
- faire passer près de `GND` ;
- ne pas faire passer parallèlement aux fils de chauffe et de moteur ;
- réduire `spi_speed` en cas d'erreurs ;
- utiliser des connecteurs appropriés ;
- ne pas étirer SPI sur toute l'imprimante sans raison ;
- pour les nœuds distants, privilégier plutôt CAN, UART/RS-485, ou un MCU séparé près du module.

La ligne `SCK` est particulièrement sensible : c'est le signal d'horloge. Si elle est perturbée, toute la communication peut devenir instable.

## SPI et RC522

Le RC522 est un bon exemple de module SPI avec une confusion de nommage.

Sur de nombreuses cartes RC522, la broche `SDA` est en réalité utilisée comme `SS`/`CS` pour SPI. Ce n'est pas le `SDA` de I2C.

Pour le RC522, vous avez généralement besoin de :

- `3,3 V` ;
- `GND` ;
- `SCK` ;
- `MOSI` ;
- `MISO` ;
- `SDA`/`SS`/`CS` ;
- `RST` ;
- parfois `IRQ`, mais dans les projets simples il est souvent inutilisé.

Un schéma détaillé se trouve dans l'article pratique : [Connexion d'un lecteur RFID](../05-practical-guides/05-connecting-rfid-reader.md).

## Ce qu'il faut vérifier avant de connecter

Avant de connecter un module SPI, vérifiez :

- l'alimentation du module ;
- le niveau logique ;
- le brochage de la carte spécifique ;
- où se trouvent `SCK`, `MOSI`, `MISO`, `CS` ;
- si `RST`, `DC`, `IRQ` ou d'autres broches sont nécessaires ;
- quel `CS` est assigné au périphérique ;
- si `CS` n'entre pas en conflit avec un autre module ;
- si SPI matériel ou logiciel est nécessaire ;
- quelle vitesse la documentation recommande ;
- si le firmware prend en charge ce module.

## Erreurs typiques

- `MOSI` et `MISO` inversés ;
- `CS` oublié ;
- deux périphériques connectés sur un même `CS` ;
- masse commune `GND` non connectée ;
- alimentation en `5 V` d'un module SPI en `3,3 V` ;
- confusion entre `SDA` sur RC522 et `SDA` de I2C ;
- vitesse trop élevée sélectionnée ;
- fils trop longs ;
- module connecté à un MCU, mais broches spécifiées depuis un autre ;
- croire que SPI est une interface d'alimentation pour piloter une charge.

## Conclusion clé

SPI est une interface rapide pour les modules proches du contrôleur. En général, il faut `SCK`, `MOSI`, `MISO`, `CS`, une alimentation et `GND`.

La principale différence avec I2C : SPI n'a généralement pas d'adresses, et chaque périphérique est sélectionné par une ligne `CS` dédiée. Avant de connecter, vérifiez le brochage, les niveaux logiques, la vitesse, la longueur des fils et la prise en charge par le firmware.

## Ressources associées

- [SparkFun: Serial Peripheral Interface](https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi) — explication pratique de SPI, lignes de données, nouveaux noms PICO/POCI et logique d'échange de base.
- [SparkFun: SPI Chip Select](https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi/chip-select-cs) — pourquoi `CS` est nécessaire et comment connecter plusieurs périphériques SPI.
- [Adafruit: SPI Devices](https://learn.adafruit.com/circuitpython-basics-i2c-and-spi/spi-devices) — comparaison SPI vs I2C, `CS` séparé, vitesse, polarité/phase et limitations.
- [DigiKey: SPI Simplifies Device Communication](https://www.digikey.com/en/articles/why-how-to-use-serial-peripheral-interface-simplify-connections-between-multiple-devices) — options de connexion de plusieurs périphériques SPI et rôle de `CS`.
- [Klipper Configuration Reference: Common SPI settings](https://www.klipper3d.org/Config_Reference.html) — paramètres `spi_speed`, `spi_bus`, SPI logiciel et `cs_pin` dans Klipper.
