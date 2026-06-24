# Adaptateurs USB-UART

Un adaptateur USB-UART est nécessaire pour permettre à un ordinateur ou à un hôte Linux de communiquer avec un périphérique UART via USB. Il convertit l'USB en lignes série standard `TX`, `RX` et `GND`.

Un tel adaptateur est souvent nécessaire pour le flashage, les journaux, les diagnostics et la récupération de cartes sans connecteur USB approprié.

## Où il est nécessaire

L'adaptateur USB-UART est utile pour :

- flasher certaines cartes microcontrôleurs ;
- lire les journaux série ;
- accéder à la console du périphérique ;
- les diagnostics en mode bootloader ;
- connecter l'Arduino Pro Mini et certains clones Nano ;
- travailler avec des cartes sans USB intégré ;
- la récupération après un flashage échoué ;
- la connexion temporaire d'un MCU à l'hôte via série.

Si une carte dispose déjà d'un USB approprié et apparaît comme un périphérique série, un adaptateur USB-UART séparé n'est peut-être pas nécessaire.

## Ce qu'il contient

Contacts typiques :

- `TX` ou `TXO` - transmission de l'adaptateur vers le périphérique ;
- `RX` ou `RXI` - réception depuis le périphérique ;
- `GND` - masse commune ;
- `VCC`, `3V3` ou `5V` - alimentation, si nécessaire ;
- `DTR` - souvent utilisé pour la réinitialisation automatique/le flashage ;
- `RTS`, `CTS` - lignes de contrôle de flux ou scénarios de démarrage/réinitialisation.

Schéma de connexion :

![Adaptateur USB-UART sur puce CH340T](../../img/02-controllers/10-usb-uart-ch340-adapter.jpg)

*Source : [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:15938_-_USBtoSerial_1.jpg), SparkFun Electronics, CC BY 2.0*

Pour une simple lecture de journaux, `TX`, `RX` et `GND` sont souvent suffisants. L'alimentation n'est connectée que s'il est clair que la carte doit être alimentée par l'adaptateur.

## Comment connecter TX et RX

La connexion est croisée :

```text
TX adapter -> RX device
RX adapter <- TX device
GND adapter -> GND device
```

En l'absence de connexion, la première vérification consiste à s'assurer que `TX` et `RX` ne sont pas inversés, qu'il y a une `GND` commune, que la vitesse correspond et que le bon port COM/tty est sélectionné.

## 3.3V et 5V

Les adaptateurs USB-UART existent en :

- `3.3V` uniquement ;
- `5V` uniquement ;
- avec commutateur `3.3V/5V` ;
- avec cavalier ou cavalier à souder ;
- avec `VCC` d'une tension, mais signaux d'un autre niveau.

Cela a son importance : le niveau de `VCC` et le niveau de `TX/RX` ne sont pas toujours évidents d'après les étiquettes.

ESP32, RP2040 et STM32 utilisent généralement la logique `3.3V`. Arduino Uno/Nano utilise souvent la logique `5V`. Si vous appliquez un signal `5V` à une entrée `3.3V`, vous pouvez endommager la carte.

Avant de connecter, vérifiez la documentation de l'adaptateur et de la carte. Ne vous fiez pas uniquement à la couleur du cavalier ou à l'étiquette sur le boîtier.

## TTL UART et RS-232

Un adaptateur USB-UART pour microcontrôleurs génère habituellement du UART TTL/CMOS : `3.3V` ou `5V`.

Ce n'est pas la même chose que le vrai RS-232.

Le RS-232 a des niveaux de tension différents et ne peut pas être connecté directement au GPIO d'un microcontrôleur. Si vous devez travailler avec un vrai port RS-232, vous avez besoin d'un adaptateur USB-RS232 ou d'un convertisseur de niveau, et non d'un USB-UART TTL ordinaire.

## Alimentation depuis l'adaptateur

La broche `VCC` de l'adaptateur peut être utile, mais elle est souvent mal utilisée.

Approche sûre :

- pour les journaux et les diagnostics, connectez d'abord uniquement `TX`, `RX`, `GND` ;
- ne connectez pas `VCC` si la carte est déjà alimentée par USB, par une alimentation ou par un autre circuit ;
- n'alimentez pas de moteurs, servos, relais, radiateurs et bandeaux LED via USB-UART ;
- vérifiez le courant que l'adaptateur peut réellement fournir ;
- gardez à l'esprit que `VCC` peut être `3.3V` ou `5V`.

Si vous connectez deux sources d'alimentation sans comprendre le circuit, vous risquez d'obtenir une alimentation inverse, une instabilité ou des dommages à la carte.

## DTR et RTS

Certaines cartes utilisent `DTR` et `RTS` pour la réinitialisation automatique ou l'entrée en mode bootloader.

Exemples :

- Arduino Pro Mini utilise souvent `DTR` via un condensateur pour la réinitialisation pendant le flashage ;
- les cartes ESP32 peuvent utiliser `DTR`/`RTS` pour contrôler automatiquement `EN` et `BOOT` ;
- certains scénarios de bootloader nécessitent d'appuyer manuellement sur un bouton si ces lignes ne sont pas connectées.

Si le flashage ne démarre pas automatiquement, ce n'est pas toujours un problème de `TX/RX`. Il se peut que `DTR`/`RTS` ne soient pas connectés, qu'un mauvais bootloader soit sélectionné, ou que `BOOT`/`RESET` doive être pressé manuellement.

## CH340, CP2102, FTDI

Puces USB-UART populaires :

- **CH340/CH341** - adaptateurs bon marché et très répandus ;
- **CP2102/CP210x** - USB-UART Silicon Labs courant ;
- **FT232/FTDI** - option classique, souvent plus coûteuse ;
- **PL2303** - présent dans les anciens adaptateurs et câbles.

Sur les systèmes modernes, le pilote est souvent installé automatiquement, mais pas toujours. Si le port n'apparaît pas, vérifiez :

- que le câble USB n'est pas uniquement pour la charge ;
- que le périphérique est détecté par le système ;
- si un pilote est nécessaire ;
- si un ancien pilote ne crée pas de conflit ;
- si le port n'est pas occupé par un autre programme.

## Comment tester l'adaptateur

Test de bouclage simple :

1. Connectez l'adaptateur à l'ordinateur.
2. Connectez `TX` de l'adaptateur à `RX` de l'adaptateur.
3. Ouvrez un terminal série.
4. Sélectionnez le port et la vitesse, par exemple `115200`.
5. Tapez des caractères.
6. Si cela fonctionne, les caractères sont renvoyés en écho.

Cela teste l'adaptateur lui-même, le pilote, le câble et le programme terminal sans carte externe.

## Ce qu'il faut vérifier avant d'acheter

Avant d'acheter un adaptateur USB-UART, vérifiez :

- quels niveaux `TX/RX` : `3.3V`, `5V` ou commutable ;
- comment le niveau est sélectionné ;
- quelle puce est utilisée : CH340, CP2102, FTDI ou autre ;
- s'il existe des pilotes pour votre système ;
- si `DTR` et `RTS` sont présents, si le flashage automatique est nécessaire ;
- quel connecteur USB ;
- si les broches `GND`, `TX`, `RX`, `VCC` sont dans un ordre pratique ;
- s'il existe un schéma ou une bonne documentation ;
- quel courant peut être tiré de `VCC`, si nécessaire.

Pour les diagnostics ESP32/RP2040/STM32, un adaptateur avec signaux `3.3V` et marquage clair est plus pratique.

## Erreurs typiques

- connecter `TX` avec `TX`, `RX` avec `RX` ;
- oublier la `GND` commune ;
- sélectionner le niveau `5V` pour une carte `3.3V` ;
- connecter `VCC` à une carte déjà alimentée ;
- alimenter une charge via un adaptateur USB-UART ;
- confondre USB-UART TTL avec USB-RS232 ;
- utiliser un câble USB uniquement pour la charge ;
- ne pas installer le pilote CH340/CP2102/FTDI ;
- sélectionner le mauvais port COM/tty ;
- ne pas connecter `DTR`/`RTS` lorsque nécessaire pour le flashage automatique ;
- laisser le terminal série ouvert, puis se demander pourquoi le flasheur ne peut pas ouvrir le port.

## Point clé

Un adaptateur USB-UART est un pont entre l'USB de l'ordinateur et les broches UART d'un périphérique. Pour une connexion minimale, vous avez besoin de `TX/RX` croisés et d'une `GND` commune.

Principaux risques : mauvais niveau `3.3V/5V`, connexion d'alimentation inutile, confusion entre TTL UART et RS-232, et lignes `DTR`/`RTS` manquantes pour le flashage.

## Ressources associées

- [SparkFun : Serial Basic CH340C Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide) - guide pratique de l'USB-UART CH340C, broches `DTR/RX/TX/VCC/CTS/GND`, sélection de tension et test de bouclage.
- [SparkFun : Serial Basic Overview](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide/serial-basic-overview) - description du brochage et commutation `3.3V/5V` sur adaptateur.
- [Adafruit : FT232H Serial UART](https://learn.adafruit.com/adafruit-ft232h-breakout/serial-uart) - exemple d'adaptateur USB-série, `TX`/`RX`, lignes de contrôle de flux et connexion au périphérique.
- [Silicon Labs : CP2102 USB to UART Bridge](https://www.silabs.com/interface/usb-bridges/classic/device.cp2102) - exemple officiel de puce pont USB-UART et pilotes Virtual COM Port.
- [Référence de configuration Klipper : `[mcu]`](https://www.klipper3d.org/Config_Reference.html#mcu) - comment la connexion série MCU est décrite dans Klipper via `serial`.
