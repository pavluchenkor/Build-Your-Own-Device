# Contrôleurs STM32

STM32 est une grande famille de microcontrôleurs 32 bits de STMicroelectronics basés sur les cœurs Arm Cortex-M. Ce n'est pas une seule carte ou une seule puce : sous le nom STM32 il y a des dizaines de séries et des centaines de modèles.

Dans le monde des imprimantes 3D, STM32 est très courant. De nombreuses cartes d'imprimante prêtes à l'emploi, cartes d'expansion, cartes CAN et contrôleurs utilisent STM32. Pour Klipper et les périphériques d'imprimante, c'est l'une des options les plus pratiques si vous êtes prêt à travailler avec une carte spécifique.

## Où STM32 est utile

STM32 est bon pour :

- carte d'imprimante 3D principale ;
- MCU supplémentaire dans Klipper ;
- carte de contrôle des ventilateurs, capteurs et sorties ;
- carte CAN ou carte de tête d'outil ;
- carte personnalisée plus sérieuse ;
- tâches nécessitant des minuteurs, PWM, ADC, UART, SPI, I2C, CAN ou USB ;
- projets nécessitant un écosystème industriel prêt à l'emploi et une documentation.

Si RP2040 est un départ simple et clair, STM32 est un vaste monde de contrôleurs où vous pouvez sélectionner une puce pour presque n'importe quelle tâche. Mais la flexibilité a un coût : la complexité.

## STM32 est une famille

Vous ne pouvez pas dire « j'ai un STM32 » et arrêter de choisir. Vous devez connaître le modèle exact.

Exemples de séries :

- **STM32F0 / STM32C0 / STM32G0** — séries budget et grand public ;
- **STM32F1** — ancienne série mais très bien connue, souvent trouvée dans Blue Pill et les anciennes cartes ;
- **STM32F4** — série plus puissante, populaire dans les contrôleurs ;
- **STM32G4** — intéressante pour les tâches de contrôle, minuteur et périphérique analogique ;
- **STM32H7** — contrôleurs puissants haut de gamme ;
- **STM32L / STM32U** — séries axées sur la consommation d'énergie faible.

Pour un utilisateur typique, ce qui compte n'est pas le marketing de la série, mais les choses spécifiques :

- y a-t-il un support dans le firmware que vous avez besoin ;
- combien de GPIO sont vraiment exposées sur la carte ;
- a-t-elle USB, CAN, UART, I2C, SPI ;
- combien de flash et RAM ;
- comment la flasher ;
- y a-t-il un pinout et un schéma corrects.

## La carte importe plus que le nom de la puce

La même STM32 peut être sur des cartes très différentes.

Variantes courantes :

- **Blue Pill / Black Pill** — cartes petites bon marché, souvent avec STM32F103 ou classe STM32F4, mais la qualité des clones varie ;
- **STM32 Nucleo** — cartes de développement officielles ST avec ST-LINK intégré ;
- **carte d'imprimante 3D prête à l'emploi** — a déjà des drivers, connecteurs, sorties MOSFET, entrées thermistance, fusibles et connecteurs de puissance ;
- **carte CAN/tête d'outil** — carte spécialisée pour une tête d'imprimante ou un module distant ;
- **carte personnalisée** — nécessite une conception complète de l'alimentation, USB, SWD, protection et routage.

Pour un premier projet pratique, il est généralement plus facile d'obtenir une carte prête à l'emploi avec une documentation qu'une STM32 nue ou un clone aléatoire sans schéma.

## STM32 et Klipper

STM32 est l'un des principaux chemins pour un MCU Klipper.

Architecture typique :

![Cartes Nucleo pour STM8 et STM32 de STMicroelectronics](../../img/02-controllers/04-stm32-nucleo-boards.jpg)

*Source : [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Nucleo-board.jpg), Avandalen, CC BY-SA 4.0*

L'hôte Klipper fonctionne sur un appareil Linux, et la carte STM32 contrôle physiquement les broches : bascule les sorties MOSFET, lit les thermistances, contrôle les ventilateurs, reçoit les signaux des interrupteurs de limite et communique avec l'hôte via USB, UART ou CAN.

Pour les périphériques de type iDryer, STM32 a du sens si :

- l'appareil doit faire partie de la configuration Klipper ;
- vous avez besoin d'une carte d'imprimante prête à l'emploi avec sorties de puissance ;
- vous avez besoin de CAN ;
- vous avez besoin d'une approche de carte plus industrielle ;
- vous avez déjà une carte STM32 et une configuration connue.

Si vous avez besoin d'ajouter rapidement quelques broches et capteurs, RP2040 est souvent plus simple. Si vous avez besoin d'une carte puissante prêt à l'emploi avec connecteurs et drivers, une carte STM32 peut être meilleure.

## Flashage : USB, DFU, UART, SWD, ST-LINK

STM32 n'a pas une méthode de flashage universelle pour toutes les cartes.

Options :

- **bootloader USB / DFU** — flashage via bootloader USB intégré si la carte et la puce le supportent ;
- **bootloader UART** — flashage via broches série dans le bon mode BOOT ;
- **SWD via ST-LINK** — moyen fiable de flasher et déboguer via un programmeur ;
- **ST-LINK intégré sur Nucleo** — pratique pour le développement ;
- **bootloader sur carte d'imprimante** — parfois le flashage se fait via carte SD, USB ou bootloader spécial du fabricant.

Donc avant d'acheter une carte, vous devez chercher non seulement une fiche technique de puce, mais des instructions pour cette carte spécifique. Pour Klipper, il est particulièrement important de lire les commentaires dans une configuration de carte prête à l'emploi et les instructions du fabricant.

## Nucleo, Blue Pill et cartes d'imprimante

Les cartes **STM32 Nucleo** sont pratiques pour l'apprentissage et le prototypage. Elles ont généralement un ST-LINK intégré, des connecteurs Arduino Uno V3 et des broches morpho ST qui fournissent accès à plus de signaux. C'est une bonne option si vous voulez apprendre STM32 et avoir un outil de flashage officiel.

**Blue Pill / Black Pill** sont attrayants pour le prix et la taille, mais les clones ont souvent des problèmes : mauvaise puce, régulateur faible, mauvais USB, pas de schéma correct, bootloader bizarre. Pour les expériences ils sont utiles, pour un appareil fiable — seulement après vérification.

**Les cartes d'imprimante 3D prêtes à l'emploi** sont souvent plus pratiques pour les radiateurs, ventilateurs et capteurs car la section de puissance est déjà routée : il y a des terminaux, sorties MOSFET, entrées thermistance, alimentation, fusibles ou place pour eux. Mais même une carte prête à l'emploi nécessite de vérifier les courants, connecteurs, refroidissement et sécurité.

## Logique 3.3V et GPIO

La plupart des STM32 fonctionnent avec la logique `3.3V`.

Important :

- n'appliquez pas `5V` aux broches sauf si la fiche technique de la puce dit spécifiquement que cette broche accepte `5V` ;
- la compatibilité du shield Arduino sur Nucleo ne signifie pas que tous les signaux sont sûrs comme sur un Arduino Uno `5V` ;
- les pull-ups I2C sont généralement à `3.3V` ;
- GPIO ne devrait pas alimenter une charge directement ;
- les ventilateurs, bandes LED, radiateurs, relais et servos sont connectés via drivers et alimentation séparée.

Même si certaines broches STM32 acceptent `5V`, ce n'est pas la permission de tout connecter. Vous devez vérifier le tableau de pinout et les caractéristiques électriques pour la puce spécifique.

## Pourquoi STM32 est souvent choisi pour les imprimantes

STM32 est bon pour les cartes d'imprimante 3D car il a beaucoup de périphériques utiles :

- minuteurs et PWM pour ventilateurs, radiateurs et signaux ;
- ADC pour thermistances et capteurs ;
- UART/SPI pour drivers de moteurs pas à pas et modules ;
- I2C pour écrans et capteurs ;
- USB pour communiquer avec l'hôte ;
- CAN dans certaines séries et cartes ;
- assez de performance pour les tâches MCU en temps réel.

Mais le microcontrôleur lui-même ne rend pas une carte sûre. Les radiateurs, MOSFET de puissance, SSR, fusibles, connecteurs et protection thermique restent une tâche d'ingénierie séparée.

## Quoi vérifier avant d'acheter

Avant d'acheter une carte STM32, vérifiez :

- modèle de microcontrôleur exact ;
- s'il y a un support dans Klipper ou le firmware que vous avez besoin ;
- combien de flash et RAM ;
- comment la carte est flashée ;
- si elle a USB, CAN, UART ou une autre interface nécessaire ;
- s'il y a un pinout et un schéma officiels ;
- quelles broches sont occupées par LED, USB, oscillateur, mode d'amorçage ou SWD ;
- quelles broches sont tolérantes 5V et lesquelles ne le sont pas ;
- quelles sorties de puissance sont sur la carte et quel courant elles sont évaluées pour ;
- s'il y a des fusibles, des terminaux et une bonne alimentation ;
- à quel point la documentation du fabricant est compréhensible.

Si une carte est vendue avec seulement une belle photo et pas de schéma, ce n'est pas une bonne base pour un appareil avec un radiateur.

## Erreurs courantes

- penser que STM32 est une carte spécifique ;
- acheter un clone Blue Pill et s'attendre au comportement d'une carte officielle ;
- ne pas vérifier le modèle exact de la puce ;
- ne pas comprendre comment flasher la carte ;
- confondre DFU, BOOT0, UART et ST-LINK ;
- connecter un module `5V` à une broche non tolérante `5V` ;
- utiliser les broches SWD comme GPIO ordinaire et perdre la capacité à flasher/déboguer ;
- penser que GPIO est une sortie de puissance ;
- choisir une carte sans schéma pour un radiateur ;
- ne pas vérifier la configuration Klipper prête avant d'acheter.

## Points clés

STM32 est une famille puissante et pratique de microcontrôleurs, en particulier pour les cartes d'imprimante 3D et Klipper MCU. Mais vous devez choisir non pas « STM32 en général » mais une carte spécifique avec une puce spécifique, pinout, méthode de flashage et documentation.

Pour un premier contrôleur simple, RP2040 est souvent plus facile. Pour l'électronique d'imprimante prête à l'emploi, les cartes CAN et les périphériques plus sérieux, STM32 est souvent le bon choix.

## Matériaux connexes

- [STMicroelectronics: STM32 32-bit Arm Cortex MCUs](https://www.st.com/en/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-mcus.html) — aperçu officiel de la famille STM32, séries, performance et outils.
- [STMicroelectronics: STM32 Mainstream MCUs](https://www.st.com/en/microcontrollers-microprocessors/stm32-mainstream-mcus.html) — aperçu des séries grand public STM32C0, G0, F0, F1, G4 et leur positionnement.
- [STMicroelectronics: STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) — outil de flashage STM32 officiel via ST-LINK/SWD, UART, USB DFU, I2C, SPI et bootloader CAN.
- [STMicroelectronics: NUCLEO-F103RB](https://www.st.com/en/product/nucleo-f103rb) — exemple d'une carte Nucleo officielle avec ST-LINK intégré, connecteurs Arduino Uno V3 et broches morpho ST.
- [ST UM1724: STM32 Nucleo-64 boards user manual](https://www.st.com/resource/en/user_manual/dm00105823-stlink-v2-in-circuit-debugger-programmer-for-stm8-and-stm32-stmicroelectronics.pdf) — documentation pour Nucleo-64, connecteurs, ST-LINK et avertissement sur E/S `3.3V`.
- [Klipper: Code overview](https://www.klipper3d.org/Code_Overview.html) — architecture de Klipper et contexte de backend MCU, y compris STM32 dans l'arborescence source.
