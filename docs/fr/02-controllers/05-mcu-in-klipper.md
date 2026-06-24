# MCU dans Klipper

Klipper se compose de deux parties principales :

- **hôte** — un ordinateur Linux avec Klipper, tel qu'un Raspberry Pi, Orange Pi, mini-PC ou autre appareil ;
- **MCU** — une carte de microcontrôleur qui contrôle physiquement les broches.

L'hôte prend les décisions de haut niveau, lit la configuration, traite le G-code et planifie les actions. Le MCU exécute les commandes précises sur le matériel : bascule les sorties, lit les entrées, compte le temps, génère PWM et signale le statut à l'hôte.

## Qu'est-ce qu'un MCU dans Klipper

MCU signifie micro-controller unit (unité de microcontrôleur).

Dans le contexte de Klipper, c'est une carte spécifique :

- carte d'imprimante 3D principale ;
- carte RP2040 séparée ;
- carte STM32 séparée ;
- carte CAN/tête d'outil ;
- carte d'E/S supplémentaire.

Un MCU ne « pense pas comme l'imprimante entière ». Il exécute les commandes de bas niveau envoyées par l'hôte. Cette séparation rend Klipper flexible : vous pouvez ajouter un deuxième ou troisième MCU et utiliser ses broches dans une configuration partagée.

## Comment ça se présente

Schéma simplifié :

![Klipper hôte et plusieurs MCU](../../img/02-controllers/05-klipper-host-mcu-architecture.svg)

L'hôte communique avec le MCU via USB, UART ou CAN. Dans la configuration Klipper, chaque MCU obtient sa propre section, et les broches de ce MCU sont ensuite utilisées dans les paramètres de ventilateur, capteur, radiateur, sortie et autre module.

## Ce que l'hôte fait

L'hôte :

- stocke et lit `printer.cfg` ;
- accepte le G-code et les commandes de l'utilisateur ;
- maintient la logique de haut niveau ;
- planifie les actions au fil du temps ;
- synchronise la communication avec le MCU ;
- décide quand basculer un ventilateur, un radiateur ou une autre sortie ;
- reçoit les lectures et le statut du MCU.

L'hôte n'applique pas de courant à un ventilateur ou ne lit pas une thermistance directement si ces broches sont sur une carte externe. Il dit au MCU quoi faire.

## Ce que le MCU fait

Le MCU :

- contrôle physiquement GPIO ;
- lit les entrées et les capteurs ;
- génère PWM ;
- exécute les commandes au bon moment ;
- signale les résultats à l'hôte ;
- se met en arrêt à la suite d'erreurs si le firmware et la configuration le prévoient.

Par exemple, si la configuration a un ventilateur sur la broche `PA8`, c'est le MCU avec cette broche qui change son état. L'hôte envoie seulement la commande.

## Que signifie `[mcu]`

Dans `printer.cfg`, la section `[mcu]` décrit le microcontrôleur auquel Klipper doit se connecter.

Exemple pour USB/série :

```ini
[mcu]
serial: /dev/serial/by-id/usb-Klipper_stm32f446xx_...
```

Pour un MCU supplémentaire, vous utilisez un nom :

```ini
[mcu chamber]
serial: /dev/serial/by-id/usb-Klipper_rp2040_...
```

Après cela, les broches du MCU supplémentaire peuvent être spécifiées avec un préfixe :

```ini
[temperature_sensor chamber_air]
sensor_type: Generic 3950
sensor_pin: chamber:gpio26

[fan_generic chamber_fan]
pin: chamber:gpio15
```

La logique est simple : `chamber:gpio15` signifie « broche `gpio15` sur le MCU nommé `chamber` ».

## Noms de broches et préfixes

Klipper utilise des noms de broches matériels.

Exemples :

- pour STM32 : `PA4`, `PB0`, `PC13` ;
- pour RP2040 : `gpio15`, `gpio26` ;
- pour Arduino/AVR il peut y avoir ses propres alias.

Avant un nom de broche il peut y avoir des symboles :

- `!` — inverser la logique ;
- `^` — activer pull-up si le MCU le supporte ;
- `~` — activer pull-down si le MCU le supporte.

Exemple :

```ini
[gcode_button chamber_door]
pin: ^chamber:gpio12
```

Ce n'est pas « la magie de Klipper », mais un paramètre spécifique d'une broche d'entrée sur un MCU spécifique. Donc le pinout de la carte doit être exact.

## Pourquoi un MCU supplémentaire est-il nécessaire

Un MCU supplémentaire est utile quand vous devez séparer les périphériques dans un bloc séparé.

Exemples pour les appareils de type iDryer :

- capteurs de température et humidité de la chambre ;
- ventilateur de circulation ;
- ventilateur de filtre ;
- rétroéclairage ;
- bouton de porte ;
- capteur de couvercle ;
- servo d'amortisseur ;
- module séparé avec capteur de charge ;
- OLED ou RFID supplémentaire ;
- entrée d'urgence qui est plus pratique à router près de l'appareil.

Cette approche est pratique si l'appareil doit faire partie d'un système Klipper, pas une boîte Wi-Fi séparée.

## Approche MCU ou contrôleur autonome

Il y a deux chemins différents.

**MCU dans Klipper** :

- l'appareil est contrôlé à partir de `printer.cfg` ;
- les broches sont visibles pour Klipper ;
- vous pouvez utiliser les sections existantes comme `fan_generic`, `temperature_sensor`, `heater_generic`, `output_pin` ;
- l'état est visible dans l'interface de Klipper ;
- la communication avec l'hôte est requise.

**Contrôleur autonome** :

- l'appareil prend ses propres décisions ;
- peut avoir Wi-Fi, interface web, MQTT ;
- n'a pas besoin de dépendre de l'imprimante ;
- nécessite son propre firmware et logique de sécurité ;
- ne se connecte pas comme un `[mcu]` normal dans Klipper.

L'ESP32 est souvent bon pour un appareil Wi-Fi autonome. RP2040 et STM32 sont souvent plus pratiques comme MCU filaire dans Klipper.

## USB, UART et CAN

La communication entre l'hôte et le MCU peut être différente.

**USB** — l'option la plus courante et simple pour une ou deux cartes près de l'hôte. Pratique pour Pico, cartes STM32 et de nombreuses cartes d'imprimante.

**UART** — communication série via broches TX/RX séparées. Peut être utile sur certaines cartes, mais nécessite une connexion attentive du niveau, de la masse et de la vitesse.

**CAN** — pratique pour les modules distants, cartes de tête d'outil et une architecture filaire plus stable. Mais CAN nécessite un microcontrôleur supporté, un transcepteur CAN, un bus correct, des terminateurs et une configuration d'interface Linux.

Pour un premier contrôleur supplémentaire, USB est généralement plus simple. CAN a du sens quand il y a une vraie raison : câblage plus long, nœuds multiples, carte de tête d'outil ou infrastructure CAN existante.

## MCU ne protège pas la section puissance

Important : ajouter un MCU ne rend pas une charge sûre.

Si un MCU contrôle un ventilateur, un radiateur ou un SSR, vous avez toujours besoin de :

- commutateur de puissance correct ;
- alimentation appropriée ;
- fils et terminaux pour le courant ;
- fusible ;
- protection thermique indépendante pour le radiateur ;
- boîtier sécurisé ;
- vérification du comportement si la communication est perdue ou l'hôte est arrêté.

Si l'hôte perd la communication avec le MCU, Klipper peut arrêter le système, mais cela ne remplace pas la protection matérielle. Un radiateur doit être conçu pour qu'une défaillance unique du firmware, du capteur, SSR ou de la communication ne conduise pas à un mode non sécurisé.

## Quoi vérifier avant de choisir un MCU

Avant d'acheter une carte pour Klipper MCU, vérifiez :

- si le microcontrôleur est supporté par Klipper ;
- s'il y a une configuration prête ou des instructions pour la carte ;
- quelle méthode de communication est nécessaire : USB, UART ou CAN ;
- comment la carte est flashée ;
- si vous avez assez de GPIO, ADC, PWM, I2C, SPI, UART ;
- quelles broches sont vraiment exposées ;
- quelle tension GPIO : généralement `3.3V` ;
- si des drivers/MOSFET/SSR sont nécessaires pour les charges ;
- s'il y a une documentation pour la puissance et le pinout ;
- ce qui se passe si la communication avec le MCU est perdue.

Pour un premier MCU supplémentaire, il est généralement plus facile de choisir RP2040/Pico ou une carte STM32 bien connue avec des instructions claires.

## Erreurs courantes

- penser que le MCU contient toute la logique de Klipper ;
- confondre l'hôte et le MCU ;
- ajouter `[mcu chamber]` mais ensuite spécifier les broches sans le préfixe `chamber:` ;
- prendre une broche du pinout de quelqu'un d'autre ;
- flasher le mauvais type de microcontrôleur dans `make menuconfig` ;
- ne pas vérifier le décalage du bootloader et la méthode de flashage de la carte ;
- utiliser un câble USB instable ;
- connecter `5V` à l'entrée `3.3V` ;
- alimenter une charge à partir de GPIO ;
- penser que l'arrêt logiciel remplace un fusible et un fusible thermique.

## Points clés

Dans Klipper, un MCU est une carte qui contrôle physiquement les broches, et l'hôte planifie et coordonne le travail. MCU supplémentaire vous permet d'étendre le système et de rapprocher les périphériques de l'appareil.

Pour les tâches de type iDryer, c'est pratique pour les ventilateurs, capteurs, filtres, rétroéclairage, boutons et certains actionneurs. Mais la section de puissance et la sécurité du radiateur restent une tâche matérielle séparée.

## Matériaux connexes

- [Klipper: Code overview](https://www.klipper3d.org/Code_Overview.html) — architecture de Klipper, division du code hôte et code micro-contrôleur, modèle de synchronisation et GPIO.
- [Klipper: Configuration reference - Micro-controller configuration](https://www.klipper3d.org/Config_Reference.html#micro-controller-configuration) — `[mcu]`, `[mcu name]` supplémentaire, format du nom de la broche et préfixes.
- [Klipper: Installation - Building and flashing the micro-controller](https://www.klipper3d.org/Installation.html#building-and-flashing-the-micro-controller) — processus général de `make menuconfig`, construction et flashage du MCU.
- [Klipper: Bootloaders](https://www.klipper3d.org/Bootloaders.html) — pourquoi les différentes cartes ont des méthodes de flashage différentes et pourquoi le bootloader importe.
- [Klipper: CANBUS](https://www.klipper3d.org/CANBUS.html) — communication CAN, `canbus_uuid`, pont USB-CAN et exigences matérielles.
