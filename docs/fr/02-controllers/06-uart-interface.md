# Interface UART

UART est une interface simple de transmission de données en série entre deux appareils. Expansion : `Universal Asynchronous Receiver/Transmitter` (Récepteur/Transmetteur Asynchrone Universel).

Dans les projets pratiques, vous entendez généralement « UART », « série », « TX/RX » ou « port UART ». Pour les débutants, le point clé est : UART transmet les données sur la ligne `TX`, reçoit sur la ligne `RX`, et les deux appareils ont besoin d'une masse commune `GND` pour fonctionner correctement.

## Où UART est utilisé

UART se trouve presque partout :

- journaux de débogage des microcontrôleurs ;
- flashage des cartes via adaptateur USB-UART ;
- communication hôte-MCU dans certains scénarios Klipper ;
- modules GPS, RFID, empreinte digitale et capteur ;
- configuration du driver de moteur pas à pas TMC ;
- communication entre deux microcontrôleurs ;
- port de service sur la carte.

UART est pratique car il nécessite peu de fils et fonctionne bien pour l'échange de texte, commande et diagnostic simple.

## TX, RX et GND

Connexion minimale :

- `TX` - transmission ;
- `RX` - réception ;
- `GND` - masse commune.

TX d'un appareil se connecte à RX de l'autre :

![TX/RX entrecroisés et GND commun dans la connexion UART](../../../img/02-controllers/06-uart-tx-rx-crossover.png)

*Source : [SparkFun Electronics](https://learn.sparkfun.com/tutorials/serial-communication/all), CC BY-SA 4.0*

Règle :

```text
Appareil A TX -> Appareil B RX
Appareil A RX <- Appareil B TX
Appareil A GND -> Appareil B GND
```

L'erreur la plus courante est de connecter `TX` à `TX` et `RX` à `RX`. Parfois, les marquages des modules sont confus, donc s'il n'y a pas de connexion, vérifiez d'abord le pinout et la documentation plutôt que de changer aléatoirement tous les fils.

## UART, USB et USB-UART

UART n'est pas USB.

Un ordinateur n'a généralement pas de broches UART nues. C'est pourquoi un adaptateur USB-UART est nécessaire : il se connecte à l'USB de l'ordinateur d'un côté et fournit les lignes `TX`, `RX`, `GND` et parfois `VCC`, `DTR`, `CTS` de l'autre.

Exemples :

- ordinateur lisant des journaux depuis une carte via USB-UART ;
- flashage USB-UART d'une carte sans USB intégré ;
- hôte se connectant à MCU via série ;
- adaptateur aidant à récupérer une carte après un flashage échoué.

Ne confondez pas un connecteur USB sur une carte avec les broches UART sur l'en-tête. Sur certaines cartes, l'USB est déjà connecté à une puce USB-UART intégrée, tandis que sur d'autres, l'USB va directement au microcontrôleur.

## Niveaux logiques : 3.3V, 5V, RS-232

UART décrit la méthode de transmission de données, mais ne garantit pas des niveaux de tension sûrs.

En électronique DIY, TTL/CMOS UART est le plus courant :

- UART `3.3V` - ESP32, RP2040, STM32 et de nombreuses cartes modernes ;
- UART `5V` - Arduino Uno/Nano et certains modules plus anciens.

Appliquer un signal `5V` à une entrée de microcontrôleur `3.3V` peut endommager la carte. Pour les niveaux incompatibles, un convertisseur de niveau ou un autre circuit d'adaptation est nécessaire.

Il y a aussi RS-232, qui est séparé. Ce n'est pas « juste UART sur un connecteur DB9 ». RS-232 a des niveaux de tension différents et une logique électrique différente. Vous ne pouvez pas connecter un vrai port RS-232 directement à une GPIO de microcontrôleur. Un convertisseur de niveau est nécessaire, tel qu'un circuit de type MAX232 ou un adaptateur prêt à l'emploi.

## Vitesse et format

La vitesse UART doit correspondre. Valeurs courantes :

```text
9600
57600
115200
250000
1000000
```

Si la vitesse ne correspond pas, le terminal affichera du charabia ou du silence.

Il y a aussi le format de transmission. `8N1` est souvent utilisé :

- `8` - 8 bits de données ;
- `N` - pas de parité ;
- `1` - un bit d'arrêt.

Pour la plupart des tâches simples, définir la même vitesse et le `8N1` standard est suffisant, sauf si la documentation du module l'exige autrement.

## UART dans les imprimantes 3D

Dans les imprimantes 3D, UART sert souvent trois rôles différents.

**Communication entre l'hôte et la carte**

Certaines cartes peuvent communiquer avec l'hôte via série/UART. Dans Klipper, ceci est décrit dans la section `[mcu]` via `serial`.

**Configuration du driver TMC**

Certains drivers de moteur pas à pas utilisent UART pour configurer le courant, stealthChop/spreadCycle, diagnostics et lecture du statut. Le moteur lui-même est généralement contrôlé non pas par UART, mais par les signaux `STEP` et `DIR`.

**Débogage et flashage**

UART peut être utilisé pour les journaux, le mode bootloader et la récupération de carte via un adaptateur USB-UART.

## Un UART - généralement deux appareils actifs

L'UART classique est une connexion entre deux appareils. Vous ne pouvez pas aveuglément connecter plusieurs transmetteurs à une seule ligne `RX`.

Problèmes :

- deux appareils tirent simultanément la ligne `TX` ;
- les données se mélangent ;
- un module reçoit les commandes destinées à un autre ;
- possible conflit électrique.

Parfois, un `TX` peut être écouté par plusieurs récepteurs, mais c'est une décision consciente et ne convient pas comme règle universelle. Pour les débutants, c'est plus sûr de supposer : un port UART - une paire d'appareils.

## Quoi vérifier avant de connecter

Avant de connecter UART, vérifiez :

- où se trouvent `TX` et `RX` ;
- une masse commune `GND` est-elle nécessaire ;
- niveau logique : `3.3V` ou `5V` ;
- c'est UART TTL ou RS-232 ;
- vitesse de transmission ;
- format, s'il est spécifié ;
- c'est UART non occupé par les journaux USB ou le flashage ;
- y a-t-il un autre transmetteur connecté à cette ligne ;
- la puissance ou seulement `TX`/`RX`/`GND` doivent-elles être connectées.

La puissance de l'adaptateur USB-UART ne se connecte que s'il est clair que la carte doit être alimentée par elle. Souvent pour le diagnostic, seuls `TX`, `RX` et `GND` sont nécessaires.

## Erreurs typiques

- connecter `TX` avec `TX`, `RX` avec `RX` ;
- oublier la masse commune `GND` ;
- appliquer UART `5V` à une entrée `3.3V` ;
- confondre UART TTL et RS-232 ;
- sélectionner le mauvais débit en bauds ;
- connecter l'alimentation d'un adaptateur USB-UART à une carte déjà alimentée ;
- utiliser les broches UART occupées par les journaux USB ou le bootloader ;
- connecter plusieurs transmetteurs à une ligne ;
- penser que UART peut entraîner une charge puissante directement.

## Conclusion clé

UART est une interface simple pour l'échange de données entre deux appareils. Vous avez besoin de `TX`/`RX` entrecroisés, masse commune `GND`, vitesse correspondante et niveaux logiques compatibles.

UART n'est pas une alimentation électrique et ne fonctionne pas comme une sortie de puissance. Il transmet des données, pas faire tourner les moteurs ou activer les radiateurs directement.

## Matériaux connexes

- [SparkFun: Serial Communication](https://learn.sparkfun.com/tutorials/serial-communication/all) - bonne explication pratique d'UART, TX/RX, débit en bauds, série TTL, RS-232 et erreurs courantes.
- [SparkFun: Serial Communication - UARTs](https://learn.sparkfun.com/tutorials/serial-communication/uarts) - ce que fait UART à l'intérieur d'un microcontrôleur et pourquoi TX/RX sont nécessaires.
- [Adafruit: Serial UART on FT232H](https://learn.adafruit.com/adafruit-ft232h-breakout/serial-uart) - exemple d'un adaptateur USB-UART et connexion de TX/RX/GND à un appareil série.
- [SparkFun: Serial Basic CH340C Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide) - exemple d'un adaptateur USB-UART, broches RX/TX/VCC/GND et test de boucle.
- [Klipper: Configuration reference - `[mcu]`](https://www.klipper3d.org/Config_Reference.html#mcu) - comment la connexion MCU série est décrite dans la configuration Klipper.
