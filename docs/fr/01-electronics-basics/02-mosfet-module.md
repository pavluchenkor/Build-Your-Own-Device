# Module MOSFET

Un module MOSFET est une petite carte prête à l'emploi qui fonctionne comme un interrupteur d'alimentation contrôlé pour les charges CC. Le contrôleur fournit un signal de contrôle faible, et le module MOSFET active ou désactive le courant de l'alimentation vers la charge.

Dans les appareils de type iDryer et les périphériques d'imprimante 3D, un module MOSFET est utilisé pour les ventilateurs, les bandes LED, les radiateurs basse tension et autres charges `12V`/`24V`, lorsque la sortie standard du circuit est faible, occupée ou inconfortable.

## MOSFET et module MOSFET

Un MOSFET est un transistor à effet de champ. Il a trois broches principales:

- `Gate` - entrée de contrôle;
- `Drain` - sortie de puissance;
- `Source` - sortie de puissance.

La grille n'alimente pas la charge. Elle contrôle seulement. Le courant de charge principal s'écoule à travers la partie puissance du MOSFET entre `Drain` et `Source`.

Un module MOSFET n'est pas seulement un seul transistor. C'est généralement une carte avec un MOSFET, des terminaux, une entrée de contrôle et parfois des résistances supplémentaires, des indicateurs, un dissipateur thermique ou une diode de protection.

La carte est pratique pour un prototype, mais ses spécifications doivent être vérifiées aussi soigneusement que n'importe quel nœud d'alimentation.

## Pourquoi c'est nécessaire

GPIO du contrôleur ne doit pas alimenter une charge importante.

GPIO peut contrôler:

- l'entrée du module MOSFET;
- l'entrée du relais;
- l'entrée du SSR;
- l'entrée du pilote.

Mais GPIO ne doit pas alimenter directement:

- le ventilateur;
- la bande LED;
- le radiateur;
- le moteur;
- le solénoïde;
- l'entraînement servo.

Si vous connectez la charge directement à GPIO, vous risquez d'endommager le contrôleur, de provoquer des redémarrages, de surchauffer les pistes ou simplement d'obtenir une opération instable.

## Commutation du côté faible

La variante la plus courante pour un module MOSFET canal N est la commutation du côté faible, c'est-à-dire la commutation via la ligne négative.

![MOSFET canal N en mode de commutation du côté faible](../../../img/01-electronics-basics/02-nmos-switch-operation.png)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:NMOS_PWR_WHOLE.PNG), KjellElec, CC BY-SA 4.0*

Logique typique:

1. `+24V` de l'alimentation va directement au positif de la charge.
2. Le négatif de la charge va à la sortie de puissance du module MOSFET.
3. Le module MOSFET connecte ou rompt le chemin du négatif de la charge à `GND`.
4. `GND` de l'alimentation et `GND` du contrôleur sont connectés ensemble.
5. La broche de contrôle du contrôleur va à l'entrée `Signal`, `IN`, `Gate` ou similaire du module.

Le `GND` commun / le négatif commun est obligatoire. Sans cela, le contrôleur et le module MOSFET n'ont pas un niveau de référence commun pour le signal de contrôle.

La commutation du côté faible a une limitation: MOSFET rompt le négatif de la charge. Lorsque le commutateur est éteint, le négatif de la charge n'est pas égal au `GND` commun. Pour un simple ventilateur à 2 broches, une bande ou un radiateur, c'est généralement correct. Pour une charge avec un tachymètre, un fil de signal séparé, un capteur à l'intérieur ou une connexion supplémentaire à une autre carte, vous devez vérifier le schéma: parfois, il est préférable de contrôler l'entrée standard ou d'utiliser une méthode de commutation différente.

## Où l'utiliser

Le module MOSFET convient aux charges CC s'il est évalué pour sa tension et son courant:

- ventilateur `12V`/`24V`;
- bande LED monochrome;
- canal de bande RGB standard;
- radiateur `12V`/`24V`;
- petit moteur CC, s'il est protégé des pics;
- solénoïde, s'il y a une diode de rappel ou une autre protection.

Pour la bande LED adressable, MOSFET ne contrôle généralement pas les données. Il peut couper l'alimentation de toute la bande, mais les LED individuelles sont contrôlées via la ligne de données.

Pour un entraînement servo, un module MOSFET n'est généralement pas nécessaire pour contrôler la position: le servo a besoin d'un signal PWM de contrôle séparé et d'une alimentation normale.

## Que vérifier lors du choix

Avant d'acheter ou de connecter, vérifiez:

- l'évaluation de la tension de la charge;
- l'évaluation du courant maximal;
- le courant réel de votre charge;
- l'entrée fonctionne-t-elle à partir de `3.3V`;
- `Rds(on)` est-il dans la spécification technique à la tension de grille requise;
- a-t-il besoin d'une logique active `HIGH` ou `LOW`;
- y a-t-il un `GND` commun;
- y a-t-il une diode de rappel pour les moteurs/solénoïdes;
- taille du terminal et courant maximal du terminal;
- épaisseur de la piste du circuit et refroidissement;
- un dissipateur thermique est-il nécessaire;
- y a-t-il un schéma, une spécification technique ou une documentation normale.

Si la description dit seulement "module MOSFET pour Arduino" sans tension, courant, schéma et type MOSFET, vous ne pouvez pas choisir un tel module pour un radiateur ou une bande LED longue.

## MOSFET 3.3V et au niveau logique

De nombreux contrôleurs modernes fonctionnent avec la logique `3.3V`: ESP32, RP2040, de nombreux STM32.

Tous les MOSFET ne s'ouvrent pas complètement à partir de `3.3V`. S'il ne s'ouvre pas complètement, sa résistance reste élevée et il chauffe.

Termes importants:

- `Vgs(th)` - seuil où le MOSFET commence à s'ouvrir;
- `Rds(on)` - résistance du canal ouvert;
- MOSFET au niveau logique - MOSFET évalué pour le contrôle à partir des niveaux logiques.

Erreur courante: voir dans la spécification technique `Vgs(th) = 2V` et décider que le MOSFET fonctionne bien à partir de `3.3V`. Ce n'est pas le cas. `Vgs(th)` ne signifie pas "complètement ouvert". Vous devez vérifier `Rds(on)` à `2.5V`, `3.3V`, `4.5V` ou `5V`, selon le contrôleur.

Pour ESP32/RP2040, il est préférable de choisir un module qui indique explicitement la compatibilité de la commande `3.3V`, ou où le circuit d'entrée le fournit. Si le tableau ne contient `Rds(on)` qu'à `10V`, et qu'il n'y a pas de données à `2.5V`/`3.3V`/`4.5V`, un tel module est suspect pour un contrôleur `3.3V`.

## Courant et chauffage

Un MOSFET à l'état ouvert a toujours de la résistance. La chaleur est générée sur celui-ci.

Plus le courant est grand, plus c'est important:

- faible `Rds(on)`;
- zone de cuivre normale sur la carte;
- terminaux de taille appropriée;
- dissipateur thermique, si nécessaire;
- ventilation du boîtier;
- marge de courant;
- vérification de la température après une opération réelle.

Le marquage "100A MOSFET" sur le boîtier du transistor ne signifie pas qu'un petit module avec des pistes fines et des terminaux bon marché supportera `100A`. La limite réelle est souvent la carte, le bloc de terminaux, le fil, la connexion soudée et le refroidissement.

Si le module MOSFET est si chaud qu'il est difficile de le tenir à la main, c'est une raison de vous arrêter et de recalculer le courant, le refroidissement et la qualité de la connexion.

## Moteurs, ventilateurs et solénoïdes

Les charges inductives peuvent produire des pics de tension lors de la coupure.

Ces charges comprennent:

- moteurs CC;
- ventilateurs;
- solénoïdes;
- relais;
- électroaimants.

Ils ont souvent besoin de protection:

- diode de rappel;
- diode TVS;
- pilote prêt à l'emploi avec protection;
- module où la protection est déjà installée.

Si le module n'est évalué que pour une bande LED ou une charge résistive, vous ne pouvez pas automatiquement supposer qu'il est sûr pour un moteur ou un solénoïde.

Pour un radiateur, une diode de rappel n'est généralement pas nécessaire, car le radiateur est proche d'une charge résistive. Mais pour un radiateur, le courant, les terminaux, le fusible et la protection thermique indépendante sont plus importants.

## Contrôle PWM

Un module MOSFET peut être utilisé non seulement pour l'allumage/extinction, mais aussi pour la régulation de puissance PWM.

Exemples typiques:

- luminosité de la bande LED;
- vitesse d'un simple ventilateur CC;
- puissance d'un radiateur basse tension.

Mais PWM n'est pas toujours le même:

- le ventilateur PWM 4 broches est mieux contrôlé par une broche PWM séparée du ventilateur, pas en coupant l'alimentation;
- le radiateur ne nécessite généralement pas une fréquence PWM élevée;
- une fréquence trop élevée peut augmenter le chauffage du MOSFET;
- une fréquence trop faible peut causer du scintillement LED ou du bruit moteur.

Le choix de la fréquence dépend de la charge, du module et du micrologiciel.

## Le module MOSFET n'est pas pour 110-230V AC

Les modules MOSFET standard pour Arduino/ESP32 sont conçus pour les charges CC: `5V`, `12V`, `24V`, parfois plus s'ils sont explicitement spécifiés.

Ils ne peuvent pas être utilisés comme commutateur pour la tension secteur `110-230V AC`.

Pour la charge secteur, vous avez besoin de solutions différentes:

- relais ou SSR évalué spécifiquement pour charge AC;
- terminaux normaux;
- fusible;
- boîtier;
- isolation;
- mise à la terre où requise;
- compréhension de la sécurité électrique.

Si vous n'êtes pas sûr que le module est destiné à la tension secteur, ne le connectez pas au secteur.

## Que vérifier après la connexion

Avant le fonctionnement à long terme, vérifiez:

- la charge obtient la bonne tension;
- le contrôleur et l'alimentation ont un `GND` commun;
- le signal de contrôle active et désactive réellement la charge;
- le module MOSFET ne chauffe pas excessivement;
- les terminaux ne chauffent pas;
- les fils sont adaptés au courant;
- PWM fonctionne sans bruit étrange, scintillement ou redémarrages;
- la charge est réellement désactivée lorsque la commande est désactivée;
- pour le moteur/solénoïde, il y a une protection contre les pics;
- pour le radiateur, il y a un fusible et une protection thermique indépendante.

Effectuez le premier test de charge importante brièvement et sous surveillance.

## Erreurs courantes

- alimentation de la charge par GPIO;
- oubli de la mise à la terre commune;
- choix du module uniquement selon le joli chiffre de courant dans le nom;
- non-vérification du fonctionnement à partir de la logique `3.3V`;
- utilisation d'un MOSFET qui ne s'ouvre pas complètement;
- connexion d'un moteur ou d'un solénoïde sans protection de rappel;
- connexion d'une bande LED longue via des terminaux faibles;
- utilisation du module MOSFET CC pour `110-230V AC`;
- non-vérification du chauffage du module dans un boîtier fermé;
- pensant que le module MOSFET lui-même limite le courant de charge.

## L'idée principale

Un module MOSFET est un interrupteur d'alimentation contrôlé pour les charges CC. Il ne crée pas de puissance et n'alimente pas la charge depuis le contrôleur. Il ouvre ou ferme seulement le chemin du courant provenant de l'alimentation.

Vérifiez la tension, le courant, la compatibilité avec la logique `3.3V`/`5V`, le `GND` commun, le chauffage, les terminaux et la protection des charges inductives. Pour la tension secteur, le module MOSFET standard Arduino/ESP32 ne convient pas.

## Matériaux de référence

- [SparkFun MOSFET Power Switch and Buck Regulator Hookup Guide](https://docs.sparkfun.com/SparkFun_MOSFET_Power_Switch_and_Buck_Regulator_Low-Side/single_page/) - exemple de module MOSFET côté faible prêt à l'emploi, connexion de charge, limites thermiques du circuit et diode de rappel.
- [SparkFun MOSFET Power Switch product page](https://www.sparkfun.com/products/23979) - exemple de la façon dont le fabricant spécifie la tension, le courant, le circuit côté faible, le MOSFET et les limitations du circuit.
- [Adafruit MOSFET Driver](https://learn.adafruit.com/adafruit-mosfet-driver) - explication pratique de la raison pour laquelle les moteurs, les solénoïdes et les LED puissantes ne peuvent pas être connectés directement à GPIO et pourquoi la protection contre les pics est nécessaire.
- [DigiKey: How to Select a MOSFET](https://www.digikey.com/en/blog/how-to-select-a-mosfet-for-logic-circuits-or-gate-design) - sélection de MOSFET par `Vgs`, `Rds(on)` et niveau de commande logique.
- [Infineon: Logic level MOSFETs](https://www.infineon.com/products/power/mosfet/n-channel/optimos-strongirfet/optimos-ir-mosfet-logic-level) - explication du MOSFET au niveau logique et contrôle du microcontrôleur.
