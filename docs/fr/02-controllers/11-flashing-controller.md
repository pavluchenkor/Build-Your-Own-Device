# Flashage du contrôleur

Firmware (`firmware`) est un programme écrit dans la mémoire flash d'un microcontrôleur. Sans firmware, la carte ne sait pas quoi faire avec les broches, capteurs, ventilateurs et interfaces.

Important : ne confondez pas le firmware et la configuration. Le firmware est écrit sur le contrôleur. La configuration Klipper vit généralement sur l'hôte dans `printer.cfg` et dit au MCU déjà flashé quelles broches et paramètres utiliser.

## Firmware, bootloader, config

Trois concepts différents :

- **firmware** - programme principal du microcontrôleur ;
- **bootloader** - petit programme qui aide à écrire le firmware principal ;
- **config** - paramètres d'appareil, par exemple `printer.cfg` dans Klipper.

Le bootloader s'exécute en premier et peut accepter le nouveau firmware via USB, UART, DFU, carte SD, CAN ou autre mécanisme. Si le bootloader est accidentellement effacé, le flashage de la carte peut devenir difficile : parfois ST-LINK/SWD, USB-UART ou un autre programmeur est nécessaire.

## Itinéraire général

Avant le flashage, la procédure normale est :

1. Connaître le modèle exact de la carte.
2. Connaître le microcontrôleur exact.
3. Trouver le pinout, le schéma et les instructions du fabricant.
4. Comprendre si le firmware autonome ou le firmware MCU Klipper est nécessaire.
5. Trouver une configuration prête ou un exemple pour cette carte.
6. Choisir la méthode de flashage correcte.
7. Construire ou télécharger le bon fichier.
8. Mettre la carte en mode flashage.
9. Écrire le firmware.
10. Vérifier que la carte apparaît dans le système.
11. Vérifier la communication avec l'hôte et les broches de base sans charge.

Vous ne pouvez pas deviner les paramètres du firmware. Pour Klipper, le type de microcontrôleur, le décalage du bootloader, la référence d'horloge et l'interface de communication sont particulièrement importants.

## Méthodes de flashage typiques

Les différentes cartes flashent différemment :

![Chemins principaux pour flasher le contrôleur](../../img/02-controllers/11-controller-flashing-paths.svg)

Variantes courantes :

- **stockage de masse USB / UF2** - la carte apparaît en tant que disque, `.uf2` y est copié ;
- **USB DFU** - la carte entre en mode DFU, le firmware est écrit via USB ;
- **bootloader USB série / UART** - firmware via port série ;
- **ST-LINK / SWD** - le programmeur se connecte aux broches SWD ;
- **Carte SD** - certaines cartes d'imprimante 3D flashent avec un fichier sur la carte ;
- **CAN/Katapult/CanBoot** - firmware via bootloader CAN ;
- **Bootloader Arduino** - flashage de sketch via Arduino IDE ou avrdude.

Il n'y a pas une méthode universelle pour toutes les cartes. La méthode est déterminée par la carte spécifique, le bootloader et le firmware.

## RP2040 et UF2

Pour Raspberry Pi Pico et de nombreuses cartes RP2040, le moyen le plus simple est `BOOTSEL` et UF2.

Généralement :

1. Maintenez `BOOTSEL`.
2. Connectez USB.
3. La carte apparaît en tant que disque `RPI-RP2`.
4. Copiez le fichier `.uf2`.
5. Le disque disparaît, la carte redémarre.

Le BOOTSEL de Pico est dans la ROM du microcontrôleur, il ne peut donc pas être accidentellement effacé par le flashage normal. Cela rend RP2040 pratique pour les débutants.

## STM32 : DFU, ST-LINK, carte SD

Les cartes STM32 flashent de différentes manières.

Options possibles :

- bootloader USB DFU intégré ;
- bootloader UART ;
- ST-LINK/SWD ;
- Carte SD sur carte d'imprimante ;
- bootloader du fabricant de la carte ;
- bootloader CAN.

Pour STM32, le décalage du bootloader est souvent important. Par exemple, si le bootloader prend les premiers `8 KiB`, Klipper doit être construit avec le décalage correct. Si choisi mal, la carte peut ne pas démarrer après le flashage.

ST-LINK/SWD est utile comme option de plus bas niveau : il peut souvent récupérer une carte si le bootloader normal ne fonctionne pas. Mais cela nécessite les broches SWD, le programmeur et la compréhension de la connexion.

## Klipper : make menuconfig

Pour le firmware Klipper, vous faites généralement :

```bash
cd ~/klipper
make menuconfig
make
```

Dans `make menuconfig`, vous sélectionnez :

- architecture de microcontrôleur ;
- modèle de processeur ;
- décalage du bootloader ;
- référence d'horloge ;
- interface de communication : USB, série, CAN, etc. ;
- parfois les paramètres supplémentaires pour la carte spécifique.

Les valeurs correctes sont souvent écrites dans les commentaires en haut d'un fichier config prêt pour la carte. Si une telle configuration existe, lisez d'abord ses commentaires en haut.

Après la construction, le fichier firmware apparaît généralement dans `~/klipper/out/`. Ensuite, il est écrit en utilisant la méthode adaptée à la carte spécifique.

## Vérification après le flashage

Après le flashage, vous devez vérifier plus que juste « le flasheur a écrit succès ».

Vérifiez :

- l'appareil apparaît-il dans le système ;
- `/dev/serial/by-id/...` est-il présent, si vous utilisez USB/série ;
- `canbus_uuid` est-il visible, si vous utilisez CAN ;
- le chemin correspond-il à `printer.cfg` ;
- n'y a-t-il pas d'erreurs de communication dans Klipper ;
- les broches correspondent-elles au pinout de cette carte spécifique ;
- les entrées/sorties de base fonctionnent-elles sans charge de puissance ;
- le ventilateur/MOSFET/SSR est-il désactivé dans l'état sûr.

Pour la première vérification, ne connectez pas le radiateur comme charge finale. Vérifiez d'abord la communication, les capteurs et la logique dans des conditions sûres.

## Ce qu'il faut sauvegarder avant le flashage

Avant de changer le firmware, il est utile de sauvegarder :

- `printer.cfg` actuelle ;
- ancienne version du firmware, si disponible ;
- modèle de carte et microcontrôleur ;
- chemin série trouvé ou UUID CAN ;
- photo des connexions ;
- pinout ;
- paramètres `make menuconfig` ;
- lien vers les instructions du fabricant.

Si quelque chose se passe mal, ces données aideront à une récupération rapide.

## Ce qui peut mal se passer

Problèmes courants :

- le câble USB est charge uniquement ;
- la carte n'est pas entrée en bootloader ;
- mauvais microcontrôleur sélectionné ;
- mauvais décalage du bootloader sélectionné ;
- mauvaise interface de communication sélectionnée ;
- firmware écrit, mais la carte est cherchée au mauvais endroit ;
- le chemin série a changé après la reconnexion ;
- la carte SD n'est pas lue par la carte ;
- fichier firmware nommé incorrectement pour le bootloader de la carte ;
- pilote DFU/USB-UART non installé ;
- la carte alimentée de deux côtés ;
- après le flashage, la config référence les anciennes broches.

Ne changez pas tout en réponse à la première erreur. Mieux vaut procéder étape par étape : câble, mode bootloader, modèle MCU, paramètres de build, méthode d'écriture, apparence du périphérique système, configuration.

## Flashage et sécurité

Le firmware peut activer et désactiver les sorties, mais il ne remplace pas la sécurité matérielle.

Pour les radiateurs vous avez besoin de :

- commutateur de puissance correct ;
- fusible ;
- protection thermique indépendante ;
- capteur de température correct ;
- boîtier sécurisé ;
- vérifier le comportement en cas d'erreur de firmware, accrochage MCU ou perte de communication.

Après le flashage du contrôleur, ne connectez pas le radiateur sans vérifier que la broche est choisie correctement, la logique d'activation n'est pas inversée et les limites de sécurité fonctionnent.

## Erreurs typiques

- confondre le firmware et `printer.cfg` ;
- flasher un fichier d'une carte similaire mais différente ;
- ne pas lire les commentaires en haut de la configuration Klipper prête ;
- sélectionner le mauvais décalage du bootloader ;
- effacer le bootloader sans comprendre les conséquences ;
- utiliser un câble USB charge uniquement ;
- ne pas mettre la carte en mode flashage ;
- chercher la carte CAN dans `/dev/serial/by-id` ;
- chercher la carte USB-série via `canbus_uuid` ;
- connecter la charge de puissance avant de vérifier les broches ;
- ne pas sauvegarder l'ancienne configuration.

## Conclusion clé

Le firmware est le programme à l'intérieur du contrôleur, la configuration est ses paramètres d'exploitation. Pour chaque carte, vous devez connaître le modèle exact, le microcontrôleur, le bootloader, la méthode de flashage et les paramètres de construction.

Pour RP2040, UF2/BOOTSEL est généralement le plus simple. Pour STM32, vérifiez la carte spécifique : bootloader DFU, ST-LINK, carte SD, UART ou CAN. Pour Klipper, trouvez d'abord une configuration prête et les commentaires pour `make menuconfig`.

## Matériaux connexes

- [Klipper: Installation - Building and flashing the micro-controller](https://www.klipper3d.org/Installation.html#building-and-flashing-the-micro-controller) - itinéraire officiel pour `make menuconfig`, `make` et vérification du chemin série.
- [Klipper: Bootloaders](https://www.klipper3d.org/Bootloaders.html) - pourquoi les bootloaders diffèrent entre les cartes, pourquoi le décalage du bootloader est nécessaire et comment les différents MCU sont flashés.
- [Raspberry Pi Documentation: Pico-series microcontrollers](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html) - BOOTSEL, UF2 et spécificités Pico/RP2040/RP2350.
- [Raspberry Pi Documentation: C/C++ SDK - Your First Binaries](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html#your-first-binaries) - exemple officiel de BOOTSEL, stockage de masse USB `RPI-RP2` et flashage de Pico via UF2.
- [STMicroelectronics: STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) - outil STM32 officiel pour flasher via ST-LINK/SWD, UART, USB DFU, SPI, I2C et bootloader CAN.
