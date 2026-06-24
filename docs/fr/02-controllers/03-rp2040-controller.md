```markdown
# Contrôleur RP2040

RP2040 est un microcontrôleur Raspberry Pi. La carte la plus connue basée sur celui-ci est le Raspberry Pi Pico.

Pour les périphériques DIY autour d'une imprimante 3D, RP2040 est l'une des options les plus pratiques : il est bon marché, bien documenté, fonctionne avec une logique `3.3V`, est pratique à flasher via USB, et convient bien comme MCU supplémentaire pour Klipper.

## Où RP2040 est utile

RP2040 convient pour :

- carte I/O supplémentaire pour Klipper ;
- contrôleur de ventilateur via MOSFET/pilotes ;
- lecture de thermistances et de capteurs analogiques simples ;
- connexion d'un OLED via I2C ;
- connexion de RFID/NFC via SPI ou UART ;
- contrôle de servo avec signal PWM ;
- carte autonome simple sans Wi-Fi ;
- banc de test pour capteurs et interfaces.

Si vous avez besoin de connectivité réseau dès le départ, il est plus simple de regarder du côté de l'ESP32 ou du Pico W. Si vous avez besoin d'un MCU câblé supplémentaire pour Klipper, RP2040 est souvent plus pratique.

## Pourquoi le Raspberry Pi Pico est pratique

Le Raspberry Pi Pico est une carte de développement prête à l'emploi basée sur RP2040. Elle dispose déjà d'un USB, d'une mémoire flash, d'un régulateur d'alimentation, d'un bouton `BOOTSEL` et de broches exposées.

Avantages du Pico :

- faible coût ;
- bonne documentation et brochage ;
- USB pour le flashage et la communication ;
- nombreux GPIO ;
- logique `3.3V` ;
- 2 UART, 2 SPI, 2 I2C ;
- 16 canaux PWM ;
- 3 entrées ADC sur les broches exposées du Pico ;
- PIO pour les interfaces non standard ;
- flashage UF2 pratique via stockage de masse USB.

Pour un premier projet, il est préférable d'obtenir un Pico ou Pico H avec des broches soudées plutôt qu'une puce RP2040 nue. Une puce nue nécessite une carte personnalisée, de la mémoire flash, une alimentation, un USB, du routage et des tests.

## BOOTSEL et UF2

L'un des points forts du Pico est un processus de flashage simple :

1. Maintenez le bouton `BOOTSEL` appuyé.
2. Connectez l'USB à votre ordinateur.
3. La carte apparaît comme un lecteur USB.
4. Copiez le fichier firmware `.uf2`.
5. La carte redémarre avec le nouveau firmware.

C'est pratique pour les projets MicroPython, CircuitPython, C/C++ et le firmware Klipper. Pour un débutant, cette méthode est généralement plus compréhensible que ST-Link, DFU ou un USB-UART séparé.

## RP2040 et Klipper

RP2040 est un bon candidat pour un MCU supplémentaire dans Klipper.

Schéma typique :

![Raspberry Pi Pico avec puce RP2040](../../img/02-controllers/03-rp2040-pico-photo.jpg)

*Source : [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Raspberry_Pi_Pico_oblique.jpg), Phiarc, CC BY-SA 4.0*

L'idée est :

- l'hôte Linux avec Klipper reste le contrôleur principal ;
- le Pico/RP2040 est flashé avec le firmware MCU de Klipper ;
- une section `[mcu]` principale ou supplémentaire est ajoutée à `printer.cfg` ;
- les broches RP2040 peuvent être utilisées pour les ventilateurs, capteurs, PWM et autres périphériques ;
- les charges de puissance sont toujours connectées via MOSFET, pilote, relais ou SSR.

C'est utile lorsque vous avez besoin de séparer une partie des périphériques en un bloc distinct : par exemple les ventilateurs, les capteurs de caméra, le filtre, l'éclairage, le bouton, le fin de course ou les sorties de service.

## GPIO et logique 3.3V

RP2040 fonctionne avec une logique `3.3V`. Cela signifie :

- ne pas appliquer `5V` aux GPIO ;
- pour les modules `5V`, un convertisseur de niveau peut être nécessaire ;
- les résistances de rappel I2C doivent être à `3.3V` ;
- les GPIO ne doivent pas alimenter directement une charge ;
- un ventilateur, une bande LED, un relais ou un élément chauffant nécessite un commutateur/pilote externe.

Si un module est « compatible Arduino », cela ne signifie pas qu'il est sûr pour RP2040. Vous devez vérifier les niveaux d'entrée et les résistances de rappel.

## Alimentation

Le Pico est généralement alimenté via USB ou via la broche `VSYS`. La carte dispose d'un régulateur pour alimenter le microcontrôleur.

Règles pratiques :

- ne pas alimenter les moteurs, servos et relais depuis la broche `3V3` du Pico ;
- utiliser une alimentation séparée pour les charges ;
- connecter la masse commune avec les pilotes basse tension ;
- vérifier d'où provient l'alimentation de `VSYS` et USB ;
- tenir compte du courant des modules externes, pas seulement du Pico lui-même.

Si le Pico se réinitialise au démarrage d'un servo ou d'un ventilateur, le problème est presque toujours lié à l'alimentation, à la masse ou aux parasites.

## ADC sur le Pico

Le Pico dispose d'entrées ADC que vous pouvez utiliser pour des tâches analogiques simples :

- thermistance via diviseur de tension ;
- potentiomètre ;
- capteur de lumière ;
- mesure de basse tension via diviseur de tension.

Limitations :

- la tension de l'entrée ADC ne doit pas dépasser la tension GPIO sûre ;
- pour mesurer `12V` ou `24V`, un diviseur et une protection sont nécessaires ;
- une thermistance nécessite une résistance correcte, un tableau/modèle et un contact mécanique ;
- l'ADC ne remplace pas un multimètre ou un appareil de mesure industriel.

Pour les éléments chauffants, rappellez-vous : l'ADC ne lit que le capteur. La sécurité du chauffage est assurée par le commutateur de puissance, les limites du firmware, le fusible et la protection thermique indépendante.

## PIO en termes simples

PIO est l'E/S Programmable. RP2040 possède de petits blocs programmables capables de générer ou de lire des signaux non standard sans charge constante sur le code principal.

Un débutant n'a pas besoin de commencer avec PIO. Mais c'est l'une des raisons pour lesquelles RP2040 est populaire pour les interfaces, la synchronisation et les périphériques non standard.

Pour un appareil simple de type iDryer, les GPIO, PWM, I2C, SPI, UART et ADC standard sont généralement suffisants.

## Pico, Pico W et Pico 2

Il est important de ne pas confondre les cartes :

- **Pico / Pico H** — carte RP2040 classique sans Wi-Fi ;
- **Pico W / Pico WH** — RP2040 avec module Wi-Fi/Bluetooth intégré ;
- **Pico 2 / Pico 2 W** — nouvelle génération basée sur RP2350, ce n'est pas RP2040.

Si un article ou un projet mentionne RP2040, il s'agit généralement du Pico de première génération ou d'une carte compatible. Le Pico 2 est similaire dans le concept, mais c'est un microcontrôleur différent, et la compatibilité du firmware/des broches doit être vérifiée séparément.

## Ce qu'il faut vérifier avant d'acheter

Avant d'acheter une carte basée sur RP2040, vérifiez :

- s'il s'agit d'un Pico original, d'un Pico W ou d'un clone ;
- si les broches sont soudées ;
- si elle dispose du connecteur USB dont vous avez besoin ;
- si un brochage correct est disponible ;
- quels GPIO sont disponibles ;
- si vous avez besoin du Wi-Fi ;
- si la carte convient au firmware Klipper ;
- comment la carte et les charges seront alimentées ;
- si vous avez suffisamment d'ADC/PWM/I2C/SPI/UART pour la tâche ;
- s'il y a de la place dans le boîtier pour le montage.

Si vous prévoyez un MCU Klipper, vérifiez à l'avance les instructions existantes pour votre carte spécifique et la méthode de flashage.

## Erreurs courantes

- appliquer `5V` aux GPIO du RP2040 ;
- alimenter un servo ou un relais depuis `3V3` ;
- oublier la masse commune avec MOSFET/pilote ;
- penser que le Pico W est un Pico ordinaire et ne pas tenir compte des ressources utilisées/de la puissance Wi-Fi ;
- acheter un Pico 2 en s'attendant à un comportement exact du RP2040 ;
- mesurer `12V`/`24V` sur l'ADC sans diviseur ;
- connecter un élément chauffant directement à une broche ;
- choisir RP2040 pour une tâche Wi-Fi alors qu'un Pico ordinaire n'a pas de Wi-Fi ;
- ne pas vérifier le brochage d'un clone spécifique.

## Points clés

RP2040 et Raspberry Pi Pico sont un excellent choix pour les périphériques DIY câblés et les MCU supplémentaires dans Klipper. La carte est bon marché, compréhensible, bien documentée et pratique à flasher.

Mais RP2040 est un microcontrôleur `3.3V`, pas un contrôleur de puissance. Les charges sont connectées via des pilotes, MOSFET, relais ou SSR. Pour les tâches Wi-Fi, vous avez besoin d'un Pico W ou d'un autre contrôleur en réseau.

## Ressources associées

- [Raspberry Pi : spécifications RP2040](https://www.raspberrypi.com/products/rp2040/specifications/) — spécifications officielles RP2040 : CPU, SRAM, UART/SPI/I2C, PWM, USB et PIO.
- [Documentation Raspberry Pi : microcontrôleurs série Pico](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html) — différences entre Pico, Pico W, Pico 2, GPIO, ADC, PWM et variantes de cartes.
- [Fiche technique RP2040](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf) — description technique détaillée du microcontrôleur, périphériques, PIO, GPIO et ADC.
- [Fiche technique Raspberry Pi Pico](https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf) — documentation pour la carte Pico elle-même : alimentation, USB, GPIO exposés et limitations de la carte.
- [Documentation Raspberry Pi : SDK C/C++ - Vos premiers binaires](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html#your-first-binaries) — exemple officiel de BOOTSEL, stockage de masse USB `RPI-RP2` et copie d'UF2 sur le Pico.
- [Référence de configuration Klipper](https://www.klipper3d.org/Config_Reference.html) — contexte du support RP2040 dans Klipper et paramètres pour les périphériques comme I2C.
```
