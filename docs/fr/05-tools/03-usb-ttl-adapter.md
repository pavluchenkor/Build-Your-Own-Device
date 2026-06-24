# USB-TTL

Un adaptateur USB-TTL, ou adaptateur USB-UART, laisse votre ordinateur communiquer avec un microcontrôleur sur UART via USB.

Vous en avez besoin pour :

- flasher certaines cartes ;
- lire les journaux ;
- déboguer la communication UART ;
- configurer des modules ;
- récupérer une carte quand l'USB normal ne fonctionne pas ;
- se connecter à un appareil sans USB-UART intégré.

Les adaptateurs courants utilisent des puces comme CH340, CP2102, FT232 et similaires.

## USB-TTL ou USB-UART

Les descriptions commerciales disent souvent USB-TTL.

Techniquement, cela signifie généralement un adaptateur USB-UART avec niveaux logiques TTL.

L'essentiel à comprendre :

- le côté USB se connecte à l'ordinateur ;
- le côté UART se connecte au microcontrôleur ;
- l'adaptateur n'est pas un programmeur pour toutes les cartes ;
- l'adaptateur ne remplace pas ST-Link si vous avez besoin de flasher STM32 via SWD.

## Broches principales

Il y a généralement :

- `GND` ;
- `TX` ;
- `RX` ;
- `VCC` ou `3V3`/`5V` ;
- parfois `DTR` ;
- parfois `CTS`, `RTS`.

Minimum pour la communication :

- `GND` ;
- `TX` ;
- `RX`.

L'alimentation n'est connectée que si vous êtes sûr que l'adaptateur devrait alimenter la carte.

## TX et RX sont interconnectés

UART est connecté comme ceci :

```text
adapter TX -> board RX
adapter RX -> board TX
adapter GND -> board GND
```

`TX` est transmission.

`RX` est réception.

Le transmetteur d'un appareil doit se connecter au récepteur de l'autre.

Si vous connectez `TX` à `TX`, la communication ne fonctionnera généralement pas.

![TX/RX interconnectés dans connexion UART](../../img/02-controllers/06-uart-tx-rx-crossover.png)

*Source: [SparkFun Electronics](https://learn.sparkfun.com/tutorials/serial-communication/all), CC BY-SA 4.0*

## Masse commune

L'adaptateur `GND` et la carte `GND` doivent être connectés.

Sans masse commune, UART peut ne pas fonctionner ou fonctionner de manière instable.

Même si la carte est alimentée par une alimentation séparée, la masse est toujours nécessaire comme niveau de signal commun.

## Niveaux logiques 3.3V et 5V

C'est l'un des points les plus importants.

L'adaptateur peut fonctionner avec logique à :

- `3.3V` ;
- `5V` ;
- `3.3V/5V` commutable.

De nombreuses cartes et modules modernes utilisent logique 3.3V : ESP32, RP2040, de nombreux STM32.

Si vous appliquez un signal UART 5V à une entrée 3.3V, vous pouvez endommager la broche ou toute la carte.

Avant de connecter, vérifiez :

- quel niveau logique la carte utilise ;
- quel niveau logique l'adaptateur utilise ;
- ce que le cavalier 3.3V/5V fait ;
- si le cavalier change seulement l'alimentation `VCC` ou aussi les niveaux `TX/RX`.

Certains adaptateurs offrent alimentation 5V mais signaux logiques 3.3V. D'autres changent puissance et niveaux. Vérifiez la documentation de l'adaptateur spécifique.

## Alimentation depuis l'adaptateur

Vous n'avez pas toujours besoin de connecter `VCC`.

Souvent c'est plus sûr de connecter seulement :

- `GND` ;
- `TX` ;
- `RX`.

Alimentez la carte depuis sa source normale.

Vous pouvez connecter `VCC` depuis l'adaptateur si :

- la carte est évaluée pour cette tension ;
- le courant de la carte est dans la capacité de l'adaptateur ;
- il n'y a pas d'autre alimentation en même temps ;
- la documentation de la carte permet l'alimentation via cette broche.

Une erreur dangereuse est de fournir l'alimentation à la fois depuis l'adaptateur USB-UART et une alimentation séparée en même temps, ce qui cause un conflit des sources.

## DTR et réinitialisation automatique

Certaines cartes utilisent `DTR` pour réinitialisation automatique pendant le flashage.

Par exemple, Arduino Pro Mini et cartes similaires peuvent utiliser DTR via un condensateur pour réinitialisation automatique.

Si le flashage ne démarre pas automatiquement, cela peut être parce que :

- DTR n'est pas connecté ;
- réinitialisation manuelle est nécessaire ;
- le mauvais adaptateur est sélectionné ;
- le mauvais bootloader est sélectionné ;
- la vitesse ou la carte dans l'IDE est sélectionnée incorrectement.

Pour simple lecture de journal, DTR n'est généralement pas nécessaire.

## Comment vérifier si l'adaptateur est visible au système

Sur macOS et Linux, l'adaptateur apparaît généralement comme un appareil dans `/dev`.

Exemples :

```bash
ls /dev/tty.*
ls /dev/cu.*
ls /dev/ttyUSB*
ls /dev/ttyACM*
```

Sur Windows, il apparaît comme un port `COM`.

Si le port n'apparaît pas :

- vérifiez le câble USB ;
- essayez un port USB différent ;
- vérifiez le pilote ;
- vérifiez que ce n'est pas juste un câble de charge ;
- voyez quelle puce est sur l'adaptateur : CH340, CP2102, FT232.

Les adaptateurs bon marché nécessitent parfois un pilote séparé, notamment sur Windows.

## Test de boucle

Moyen simple de vérifier l'adaptateur :

1. Connectez `TX` et `RX` de l'adaptateur ensemble.
2. Ouvrez un terminal série.
3. Sélectionnez le port et la vitesse.
4. Tapez du texte.

Si les caractères que vous tapez reviennent, l'adaptateur et le port fonctionnent probablement.

Après le test, retirez le cavalier entre `TX` et `RX`.

## Erreurs courantes

- `TX` connecté à `TX` et `RX` à `RX` ;
- oublié `GND` commun ;
- niveau 5V sélectionné pour une carte 3.3V ;
- connecté `VCC` bien que la carte soit déjà alimentée séparément ;
- le câble USB s'est avéré être de charge seulement ;
- pilote CH340/CP210x/FTDI non installé ;
- mauvais port COM sélectionné ;
- la vitesse UART ne correspond pas ;
- s'attendre à ce que USB-UART flashe STM32 via SWD ;
- confondu mode de démarrage ou réinitialisation pendant le flashage.

## Les éléments essentiels

- L'adaptateur USB-UART est nécessaire pour la communication UART entre ordinateur et carte.
- Minimum pour la communication : `GND`, `TX`, `RX`.
- L'adaptateur `TX` va à la carte `RX`, l'adaptateur `RX` va à la carte `TX`.
- Vérifiez les niveaux logiques 3.3V/5V avant de connecter.
- `VCC` n'est connecté que si vous avez définitivement besoin d'alimentation depuis l'adaptateur.
- Si l'adaptateur n'est pas visible, vérifiez le câble, le pilote et le port USB.

## Matériaux de référence

- [SparkFun: Serial Basic Hookup Guide](https://learn.sparkfun.com/tutorials/serial-basic-hookup-guide) - adaptateur USB-série, TX/RX/GND, VCC, DTR et commutation 3.3V/5V.
- [SparkFun: Serial Basic CH340C Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide/serial-basic-overview) - adaptateur USB-UART CH340C moderne, broches, LEDs et sélection de tension.
- [SparkFun: Serial Communication](https://learn.sparkfun.com/tutorials/serial-communication) - base UART, TX/RX et communication série.
- [Silicon Labs: CP210x USB to UART Bridge VCP Drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) - pilotes officiels CP210x Virtual COM Port.
- [Adafruit FTDI TTL-232 USB Type C Cable](https://www.adafruit.com/product/4364) - exemple de câble avec alimentation 5V et logique 3.3V, montrant pourquoi l'alimentation et les niveaux de signal doivent être lus séparément.
