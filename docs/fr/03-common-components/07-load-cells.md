# Capteurs de charge

Un capteur de charge mesure la force par une légère déformation du métal. Peser une bobine, surveiller le filament restant et les simples plateformes de poids utilisent presque toujours de tels capteurs.

Important à comprendre : un capteur de charge ne « ressent pas le poids » par lui-même. Il se plie ou se compresse légèrement sous la charge, et l'électronique mesure le changement de résistance microscopique dans les jauges de contrainte. Deux choses sont donc critiques : la mécanique correcte et un amplificateur/ADC normal.

## Où c'est utilisé

Dans les projets de type iDryer, un capteur de charge peut être utilisé pour :

- estimer le poids de la bobine avec filament ;
- calcul approximatif du plastique restant ;
- vérifier que la bobine est installée ;
- détecter un changement de poids soudain ;
- mesurer la charge sur un petit mécanisme ;
- plateforme de poids expérimentale ;
- contrôle du dosage dans les systèmes DIY.

Pour un simple « bobine présente/absente », parfois un commutateur limite ou un capteur optique suffit. Un capteur de charge est nécessaire lorsqu'il est important de mesurer réellement le poids ou le changement de force.

## Pourquoi HX711 est nécessaire

Un signal de capteur de charge est très faible. Une entrée analogique typique sur ESP32, Arduino ou une carte d'imprimante ne fonctionne généralement pas pour une connexion directe.

Un capteur de charge est donc généralement connecté via HX711 ou un module similaire. HX711 fait deux choses :

- amplifie le signal du pont différentiel faible ;
- le convertit en données numériques pour le contrôleur.

Chaîne typique :

```text
capteur de charge -> HX711 -> contrôleur
```

Un diagramme de connexion détaillé se trouve dans la section pratique : [Connexion d'un capteur de charge](../06-practical-guides/04-connecting-load-cell.md).

## Quels types de capteurs de charge existent

Dans les petits projets, les plus courants sont :

- cellule de poutre - pratique pour les petites plateformes et les supports de bobine ;
- cellule de type S - fonctionne en traction/compression, souvent utilisée dans les configurations suspendues ;
- cellule de bouton - mesure la compression en un point ;
- quatre cellules sur une plateforme - conception typique de la balance de sol ;
- éléments de jauge de contrainte unique - nécessitent un pont approprié et une mécanique, plus difficile pour les débutants.

Pour un système simple de poids de bobine DIY, il est généralement plus facile de commencer par un capteur de charge de poutre sur `5 kg`, `10 kg` ou à proximité. Mais la plage dépend de la masse de la bobine, du support et des à-coups possibles.

## Fils et pont

La plupart des capteurs de charge à quatre fils courants ont un circuit pont.

Sur HX711, vous voyez généralement les marquages :

- `E+` ou `VCC` - plus d'alimentation du pont ;
- `E-` ou `GND` - moins d'alimentation du pont ;
- `A+`, `S+`, `O+` - signal de mesure positif ;
- `A-`, `S-`, `O-` - signal de mesure négatif.

Schéma de couleurs courant :

- rouge - `E+` ;
- noir - `E-` ;
- vert ou bleu - `A+` ;
- blanc - `A-` ;
- jaune, feuille ou fil séparé - blindage.

Les couleurs ne sont pas garanties. S'il y a une description technique de la cellule spécifique, c'est plus important que n'importe quelle table Internet. Si les lectures vont mal, souvent inverser `A+` et `A-` ou tenir compte du signe dans le programme suffit.

## La mécanique est plus importante que le circuit

Un capteur de charge doit se déformer exactement comme le fabricant l'a prévu. Si la charge contourne la zone de travail, la cellule affichera des lectures instables ou presque rien.

![Capteur de charge de type S miniature](../../../img/03-common-components/07-miniature-load-cell.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Miniature_S-beam_load_cell.jpg), FUTEK Advanced Sensor Technology, CC BY-SA 4.0*

Pour une cellule de poutre, l'idée typique est :

- un côté est fermement monté sur une base fixe ;
- l'autre côté porte une plateforme ou une charge ;
- il y a un espace entre la pièce mobile et la base ;
- les vis et le boîtier ne bloquent pas la flexion du poutre.

Une mauvaise mécanique donne de tels symptômes :

- les lectures dérivent sans charge ;
- le poids dépend de l'endroit où vous placez la bobine ;
- la cellule réagit à peine à la charge ;
- après suppression de la charge, zéro ne revient pas ;
- toucher le boîtier change les lectures fortement ;
- différents assemblages affichent un poids différent avec la même configuration.

## Plage et surcharge

La plage d'un capteur de charge n'est pas le poids de travail souhaité, c'est la limite pour laquelle il est évalué.

Utiliser une cellule `1 kg` pour une bobine, un support et des à-coups au-dessus de `1 kg` peut la pousser dans la non-linéarité ou la déformation permanente. Utiliser une cellule `100 kg` pour une bobine `1 kg` perd la sensibilité, et la mécanique doit être beaucoup plus soigneuse.

Lors du choix de la plage, considérez :

- poids maximal de la bobine pleine ;
- poids du support et de la plateforme ;
- forces de désalignement ;
- à-coups accidentels au montage ;
- marge pour l'utilisateur ;
- précision souhaitée.

Pour le filament restant, une marge modérée est souvent plus utile qu'une plage énorme. Par exemple, pour une bobine avec support pesant plusieurs kilos, une cellule `5 kg` ou `10 kg` est généralement meilleure que `50 kg` si la mécanique le permet.

## Tare et calibration

Un capteur de charge sans calibration produit des nombres bruts, pas des grammes.

Processus typique :

1. Installez la cellule en mécanique réelle.
2. Placez une plateforme ou un support vide.
3. Faites une tare - acceptez la valeur actuelle comme zéro.
4. Placez un poids connu.
5. Ajustez le coefficient d'étalonnage.
6. Vérifiez un ou deux poids de plus.

Pour les bobines, il y a un problème supplémentaire : une bobine vide pèse aussi différemment. Si vous devez estimer juste le plastique, vous devez connaître le poids de la bobine vide ou stocker un profil pour cette bobine spécifique.

## Précision et stabilité

En pratique, la précision dépend de plus que HX711 et la cellule.

Les lectures sont affectées par :

- la rigidité du boîtier ;
- le jeu de montage ;
- la charge latérale ;
- vibration ou bruit d'imprimante ;
- longueur du câble et blindage ;
- fils de mesure près des lignes d'alimentation ;
- température ;
- fluage du matériau et déformation plastique ;
- câble ou bobine touchant le boîtier autour de la cellule.

Si un capteur de charge est dans un boîtier en plastique imprimé, n'attendez pas une précision de laboratoire. Pour les estimations de filament restant, les lectures stables et la répétabilité après étalonnage suffisent généralement.

## Puissance et câblage

HX711 mesure un signal faible, le câblage doit donc être soigneux.

Règles pratiques :

- gardez HX711 près du capteur de charge ;
- ne routez pas les câbles de cellule près des radiateurs, des moteurs et des lignes d'alimentation ;
- fixez les câbles pour qu'ils ne tirent pas la plateforme ;
- utilisez `GND` commun avec le contrôleur ;
- alimentez le module avec une tension compatible au contrôleur ;
- n'utilisez pas de mauvais contacts Dupont dans l'assemblage final si l'appareil devrait fonctionner longtemps.

Du côté du contrôleur, HX711 se connecte généralement via `DT`/`DOUT` et `SCK`/`CLK`. Ce n'est pas régulier I2C ou SPI, mais une interface simple séparée.

## Quoi vérifier avant d'acheter

Avant d'acheter, vérifiez :

- type de cellule : poutre, type S, bouton, plateforme ;
- plage de poids ;
- direction d'application de charge ;
- dimensions et trous de montage ;
- disponibilité de description ou diagramme de câble ;
- si une cellule ou quatre cellules sont nécessaires ;
- si le module HX711 correspond à la cellule choisie ;
- s'il y a de la place pour un jeu et un montage appropriés ;
- si vous pouvez mettre un poids connu pour l'étalonnage ;
- si la charge ne passera pas par le boîtier autour de la cellule.

Si la mécanique n'est pas encore pensée, il est préférable d'esquisser d'abord le montage. Acheter « n'importe quel capteur de charge » finit souvent par être physiquement impossible à monter correctement.

## Erreurs typiques

- connexion directe du capteur de charge à l'entrée analogique ;
- confusion de `E+`/`E-` et `A+`/`A-` ;
- faire confiance aux couleurs de fil sans description ;
- montage des deux côtés de la cellule de poutre à une pièce rigide ;
- blocage de la flexion de cellule avec des vis ou un boîtier ;
- surcharge de la cellule ;
- choix d'une plage trop grande et perte de sensibilité ;
- oubli de tare et d'étalonnage ;
- étalonnage sur établi, puis installation de cellule en mécanique différente ;
- routage de câbles près des lignes de puissance du radiateur ;
- expectative de précision au niveau du gramme à partir d'un boîtier en plastique mou.

## Point principal

Un capteur de charge est un composant où la mécanique est aussi importante que l'électronique. HX711 aide à lire le signal faible, mais ne corrigera pas le montage déformé, la surcharge ou la charge contournant la cellule.

D'abord, choisissez le bon type et la bonne plage, puis concevez le montage, connectez HX711, et seulement alors faites tare et étalonnage.

## Matériaux de référence

- [SparkFun: Load Cell Amplifier HX711 Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide) - connexion pratique du capteur de charge à HX711, câbles, bibliothèque et étalonnage.
- [SparkFun HX711 product page](https://www.sparkfun.com/sparkfun-load-cell-amplifier-hx711.html) - description du rôle de HX711 comme pont entre capteur de charge et microcontrôleur.
- [DigiKey: HX711 Datasheet by Avia Semiconductor](https://www.digikey.com/en/htmldatasheets/production/1836471/0/0/1/hx711.html) - description technique de HX711 : ADC 24 bits, entrée capteur pont et interface numérique.
- [Phidgets: Load Cell Guide](https://cdn.phidgets.com/docs/Load_Cell_Guide) - exemples pratiques de types de capteurs de charge, direction de charge et montage.
- [SparkFun retired HX711 guide: mechanical setup](https://learn.sparkfun.com/tutorials/retired---load-cell-amplifier-hx711-breakout-hookup-guide) - illustrations utiles du montage de cellule de poutre, type S et plateforme.
