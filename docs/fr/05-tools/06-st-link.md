# ST-Link

ST-Link est un programmeur et débogueur pour microcontrôleurs STM32.

Dans le contexte des appareils simples, il est utilisé pour :

- flasher une carte STM32 ;
- récupérer une carte après un flashage échoué ;
- se connecter à la puce via SWD ;
- effacer la mémoire ;
- vérifier que le microcontrôleur est visible ;
- parfois déboguer le programme.

ST-Link n'est pas nécessaire pour toutes les cartes. ESP32, RP2040 et Arduino flashent généralement d'une autre manière.

## Qu'est-ce que SWD

SWD est `Serial Wire Debug`.

C'est une interface de débogage et de flashage pour microcontrôleurs ARM, couramment utilisée avec STM32.

Pour la connexion de base, vous avez généralement besoin de :

- `SWDIO` ;
- `SWCLK` ;
- `GND` ;
- parfois `NRST` ;
- parfois `3.3V` ou `VTref` comme tension de référence cible.

Important : `3.3V` sur ST-Link ne signifie pas toujours « alimenter la carte d'ici ». Souvent, ST-Link a besoin de voir la tension de la carte cible pour comprendre les niveaux de signal.

## Connexion minimale

Généralement vous connectez :

```text
ST-Link SWDIO -> board SWDIO
ST-Link SWCLK -> board SWCLK
ST-Link GND   -> board GND
ST-Link NRST  -> board NRST si réinitialisation est nécessaire
ST-Link 3.3V/VTref -> 3.3V target si requis par ST-Link spécifique
```

La carte STM32 est souvent alimentée depuis son alimentation normale ou USB.

Avant de connecter, vérifiez la documentation pour votre ST-Link et carte spécifiques.

![Cartes Nucleo pour STM32 avec débogueur ST-Link intégré](../../img/02-controllers/04-stm32-nucleo-boards.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:STM32_Nucleo_boards.jpg), Avandalen, CC BY-SA 4.0*

## Alimentation de la carte

La confusion la plus courante : la carte est-elle alimentée par ST-Link ou séparément ?

Options :

1. La carte est alimentée séparément, ST-Link ne se connecte qu'au SWD et GND.
2. ST-Link fournit 3.3V à une petite carte cible, si elle est réellement conçue pour cela.
3. ST-Link lit seulement `VTref` mais ne doit pas alimenter la carte.

Vous ne pouvez pas aveuglément connecter plusieurs sources d'alimentation.

Si la carte est déjà alimentée par USB ou une alimentation, ne connectez pas l'alimentation depuis ST-Link jusqu'à ce que vous soyez sûr que le schéma le permet.

## Comment ST-Link diffère de DFU

DFU est un mode flashage via un bootloader USB, s'il est disponible.

ST-Link fonctionne via SWD directement avec le microcontrôleur.

ST-Link est utile quand :

- DFU n'est pas disponible ;
- le bootloader est corrompu ou non utilisé ;
- flashage désactivé USB ;
- la carte ne veut pas entrer en mode flashage normal ;
- vous avez besoin d'effacer la mémoire ;
- vous avez besoin de récupérer l'accès STM32.

Mais si une carte flashe normalement via USB/DFU ou carte SD, ST-Link peut ne pas être nécessaire.

## Connecter sous réinitialisation

Parfois, le firmware brise l'accès SWD.

Par exemple :

- Les broches SWD sont utilisées comme GPIO normales ;
- le firmware met rapidement la puce en veille ;
- le code se bloque juste après le démarrage ;
- les modes horloge/puissance sont définis incorrectement.

Dans ces cas, le mode `Connecter sous réinitialisation` aide.

L'idée : ST-Link tient la réinitialisation et essaie de se connecter avant l'exécution du mauvais firmware.

Cela nécessite souvent de connecter `NRST`.

## Comment savoir que ST-Link voit la carte

Dans STM32CubeProgrammer ou outil similaire, vous voyez généralement :

- si ST-Link est connecté ;
- si la cible est trouvée ;
- quelle puce est détectée ;
- si vous pouvez lire la mémoire ;
- si vous pouvez effacer le flash.

Si ST-Link est visible comme un périphérique USB mais la cible n'est pas trouvée, le problème est souvent la connexion de la carte :

- la carte cible n'a pas d'alimentation ;
- pas de `GND` commun ;
- `SWDIO` et `SWCLK` sont permutés ;
- `VTref` n'est pas connecté si nécessaire ;
- la fréquence SWD est trop élevée ;
- la puce est verrouillée ;
- le firmware empêche la connexion ;
- `Connecter sous réinitialisation` est nécessaire.

## Fréquence SWD

Si la communication est instable, essayez de réduire la fréquence SWD.

Sur les longs fils, les mauvaises jumpers Dupont ou les cartes instables, la haute fréquence peut interférer avec la connexion.

Pour la récupération de la carte, lent et fiable bat rapide.

## Erreurs courantes

- oublié `GND` ;
- permutation de `SWDIO` et `SWCLK` ;
- connecté l'alimentation depuis ST-Link et USB en même temps sans comprendre le schéma ;
- n'a pas alimenté la carte cible ;
- n'a pas connecté `NRST` quand `Connecter sous réinitialisation` est nécessaire ;
- la fréquence SWD définie trop élevée ;
- essai de flasher ESP32 ou RP2040 avec ST-Link ;
- essai de connexion à une puce verrouillée sans comprendre la protection en lecture ;
- utilisation de longs fils de mauvaise qualité ;
- n'a pas mis à jour le firmware ST-Link ou n'a pas installé le pilote.

## Ce que vous ne pouvez pas faire

Vous ne pouvez pas :

- appliquer 5V à une carte STM32 3.3V sans vérification ;
- connecter plusieurs sources d'alimentation aveuglément ;
- connecter ST-Link à une carte sous tension secteur sans isolation sûre et enceinte ;
- changer les fils SWD avec l'alimentation activée s'il y a risque de court-circuit ;
- supposer qu'un clone ST-Link a le même pinout que l'original.

Les pinouts du clone ST-Link peuvent différer. Vérifiez toujours les marquages sur votre adaptateur spécifique.

## Les éléments essentiels

- ST-Link est nécessaire pour STM32 via SWD.
- Minimum : `SWDIO`, `SWCLK`, `GND`, parfois `NRST` et `VTref`.
- La carte devrait être alimentée correctement, mais pas nécessairement depuis ST-Link.
- DFU et ST-Link sont différentes méthodes de flashage.
- `Connecter sous réinitialisation` aide à récupérer l'accès après un mauvais firmware.
- Si la cible n'est pas trouvée, d'abord vérifiez l'alimentation, `GND`, `SWDIO/SWCLK`, `NRST` et fréquence SWD.

## Matériaux de référence

- [STMicroelectronics: UM1075 ST-LINK/V2 User Manual](https://www.st.com/resource/en/user_manual/dm00026748-st-link-v2-in-circuit-debugger-programmer-for-stm8-and-stm32-stmicroelectronics.pdf) - manuel officiel ST-LINK/V2, broches SWD/JTAG, VCC cible et GND.
- [STMicroelectronics: UM2237 STM32CubeProgrammer User Manual](https://www.st.com/resource/en/user_manual/um2237-stm32cubeprogrammer-software-description-stmicroelectronics.pdf) - modes de connexion ST-LINK, y compris Normal, Connecter sous réinitialisation et Hot plug.
- [ST Wiki: ST-LINK](https://wiki.st.com/stm32mpu/wiki/ST-LINK) - aperçu ST-LINK comme sonde matérielle pour STM32/STM8 et protocoles supportés.
- [Klipper: Installation](https://www.klipper3d.org/Installation.html) - processus général de préparation MCU pour Klipper.
- [STMicroelectronics: STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) - outil officiel ST pour flasher STM32 via ST-LINK/SWD, UART, USB DFU, SPI, I2C et bootloaders CAN.
