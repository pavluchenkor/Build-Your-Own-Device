# Connexion d'une Cellule de Charge

Une cellule de charge mesure la force ou le poids via minuscule déformation d'une poutre métallique, d'un bouton, ou d'une plateforme.

Dans les appareils de type iDryer, une cellule de charge peut estimer le poids de la bobine, le filament restant, ou la charge du mécanisme.

Point principal : une cellule de charge est presque jamais connectée directement à un contrôleur. Son signal est trop petit. Généralement, un module HX711 ou amplificateur/ADC similaire est placé entre le capteur et le contrôleur.

## Ce dont vous avez besoin

Ensemble minimum :

- cellule de charge de la plage de poids nécessaire ;
- module HX711 ;
- contrôleur : Arduino, ESP32, RP2040, STM32, ou autre carte ;
- montage mécanique rigide ;
- masse connue pour l'étalonnage ;
- fils courts et nets.

Si la mécanique est mauvaise, le circuit n'aidera pas. Une cellule de charge peut être câblée parfaitement mais donner des lectures sans sens en raison du mauvais alignement, du jeu, ou de la charge appliquée au mauvais point.

## Comment la connexion est arrangée

La cellule de charge se connecte à HX711 avec des fils analogues.

HX711 se connecte au contrôleur avec des fils numériques.

Chaîne typique :

```text
load cell -> HX711 -> controller
```

HX711 a généralement deux côtés :

- entrée de la cellule de charge : `E+`, `E-`, `A+`, `A-`, ou similaire ;
- connexion au contrôleur : `VCC`, `GND`, `DT`/`DOUT`, `SCK`/`CLK`.

![Diagramme de connexion HX711 et cellule de charge](../../img/06-practical-guides/04-hx711-load-cell-fritzing.jpg)

*Source: [SparkFun Electronics](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide/all), CC BY-SA 4.0*

## Fils de cellule de charge

Une cellule de charge quatre fils typique a généralement :

- `E+` - plus d'alimentation de pont ;
- `E-` - moins d'alimentation de pont ;
- `S+`, `A+`, ou `O+` - signal de mesure positif ;
- `S-`, `A-`, ou `O-` - signal de mesure négatif.

Schéma de couleur courant :

- rouge - `E+` ;
- noir - `E-` ;
- vert ou bleu - `A+` ;
- blanc - `A-`.

Mais les couleurs ne sont pas une loi. Différents capteurs peuvent différer. S'il y a une fiche technique pour la cellule de charge spécifique, suivez-la.

Si le capteur a un cinquième fil, du papier d'aluminium, ou un blindage, c'est souvent le blindage électromagnétique. Ne le confondez pas avec un fil de mesure de pont. Généralement, le blindage est connecté à `GND` ou au boîtier d'un côté si la documentation le dit, mais pas aux mesures `A+`/`A-`.

S'il n'y a pas de diagramme de câblage, ne connectez pas la cellule de charge « au hasard ». D'abord trouvez la fiche technique du capteur ou sonnez le pont par guide fabricant : les fils incorrects donnent facilement des lectures instables ou surcharger l'entrée HX711.

## Connexion HX711 au contrôleur

Du côté du contrôleur, vous avez généralement besoin de quatre lignes :

- `VCC` - alimentation du module ;
- `GND` - négatif commun ;
- `DT`, `DOUT`, ou `DATA` - données ;
- `SCK`, `CLK`, ou `PD_SCK` - horloge.

Pour de nombreux modules HX711, l'alimentation peut être `3.3V` ou `5V`, mais vérifiez le module spécifique. Si le contrôleur fonctionne à 3.3V, c'est pratique d'utiliser un module et une alimentation compatibles avec logique 3.3V.

Les broches `SCK` et `SCK` peuvent généralement se connecter à GPIO régulièrement. Ce n'est pas I2C ou SPI dans le sens habituel, mais une interface HX711 simple à deux fils.

## La mécanique importe plus que le circuit

Une cellule de charge doit déformer comme le fabricant l'a prévu.

Pour un capteur de poutre, un côté monte généralement à une base fixe, l'autre côté porte la charge. Si les deux côtés sont rigidement montés à une partie, le capteur ne fléchira pas normalement.

Vérifiez :

- où se trouve le côté de montage du capteur ;
- où la charge doit être appliquée ;
- quelle direction la force doit aller ;
- si des espaceurs sont nécessaires ;
- si la partie mobile dégage le boîtier ;
- pas de mauvais alignement ;
- pas de charge latérale ;
- les vis ne sont pas sur-serrées ;
- la bobine ou la plateforme n'atterrit pas au-delà de la zone de travail du capteur.

Pour le poids de la bobine, il est particulièrement important que toute la charge passe par le capteur, pas partiellement par le mur du boîtier, l'axe, le câble, ou le couvercle cosmétique.

## Ne pas surcharger le capteur

La plage d'une cellule de charge n'est pas une recommandation mais une limite de mesure.

Si un capteur de 1 kg est placé où une bobine et un support peuvent dépasser cela, le capteur fonctionnera mal ou se déformera en permanence.

Choisissez la plage avec marge :

- poids maximum de la bobine ;
- poids du support ;
- possible secousses ;
- mauvais alignement ;
- marge de sécurité pour erreur utilisateur.

Mais une plage trop grande n'est pas toujours bonne non plus. Un capteur de 100 kg sentira une petite bobine pire qu'un capteur de 5 kg ou 10 kg avec mécanique et électronique identiques.

## Premier démarrage

Avant l'installation dans l'appareil, testez le système sur le banc :

1. Connectez la cellule de charge à HX711.
2. Connectez HX711 au contrôleur.
3. Exécutez le code de test ou une bibliothèque.
4. Assurez-vous que les valeurs brutes changent quand vous appuyez sur le capteur.
5. Retirez la charge et vérifiez que la valeur est assez stable.
6. Placez une masse connue et vérifiez le changement.

À ce stade, ne demandez pas la précision en grammes. D'abord, vous devez voir que le capteur est vivant, la direction de la charge est correcte, et les lectures changent prévisiblement.

Si la valeur diminue à mesure que le poids augmente, généralement permutez simplement `A+` et `A-` ou comptabilisez le signe dans le code.

## Tare et étalonnage

Une cellule de charge sans étalonnage ne sait pas ce que sont les grammes.

Processus typique :

1. Placez la plateforme vide.
2. Tare : c'est zéro en comptant le poids de la plateforme.
3. Placez une masse connue.
4. Sélectionnez le facteur d'étalonnage.
5. Vérifiez plusieurs poids différents.

Pour les bobines de filament, décidez ce qui compte comme poids :

- bobine entière avec plastique ;
- seulement le plastique restant sans poids de bobine vide ;
- changement de poids de la valeur initiale.

Si les bobines vides de différents fabricants pèsent différemment, le calcul du reste exact nécessite de connaître le poids spécifique de la bobine vide ou de travailler avec des estimations approximatives.

## Bruit et lectures instables

HX711 mesure un signal très petit, donc le système est sensible au bruit et aux problèmes mécaniques.

Causes des lectures instables :

- longs fils du capteur à HX711 ;
- mauvais contacts ;
- fils d'alimentation du chauffage à côté des fils de signal ;
- vibration du ventilateur ou de l'imprimante ;
- base souple ;
- jeu de montage ;
- dérive de température ;
- charge touchant le boîtier contournant le capteur.

Mesures pratiques :

- gardez HX711 proche de la cellule de charge ;
- ne faites pas circuler les fils de signal à côté des fils d'alimentation du chauffage ;
- sécurisez les fils pour qu'ils ne tirent pas le capteur ;
- utilisez la moyenne de mesure ;
- étalonnez après le montage dans le boîtier ;
- tarifiez après échauffement de l'appareil si la température affecte notablement les lectures.

## Ce qu'il faut vérifier après l'assemblage

Avant utilisation :

- le capteur est évalué pour le poids nécessaire ;
- la charge traverse la partie de travail du capteur ;
- les fixations ne bloquent pas la déformation ;
- HX711 reçoit l'alimentation correcte ;
- `DT` et `SCK` sont connectés au GPIO correct ;
- la masse commune existe ;
- les valeurs brutes changent sous charge ;
- sans charge, les lectures ne dérivent pas trop rapidement ;
- la masse connue montre le poids attendu après l'étalonnage ;
- les fils ne tirent pas la plateforme ;
- la bobine ou le support ne touche pas le boîtier au-delà du capteur.

## Erreurs courantes

- connecter la cellule de charge directement à l'entrée analogique du contrôleur ;
- confondre `E+`/`E-` et `A+`/`A-` ;
- faire confiance aux couleurs des fils sans fiche technique ;
- oublier l'étalonnage ;
- tarification avant l'installation mécanique finale ;
- montage du capteur pour qu'il ne puisse pas fléchir ;
- surcharge du capteur ;
- choisir une plage trop grande et perdre la sensibilité ;
- instabilité à partir de longs fils et d'interférence ;
- attendre la précision en grammes d'un corps en plastique flexible sans mécanique rigide.

## Points clés

- La cellule de charge se connecte généralement via HX711, pas directement au contrôleur.
- Les fils du capteur vont à `E+`, `E-`, `A+`, `A-`.
- HX711 se connecte au contrôleur via l'alimentation, la masse, `DT` et `SCK`.
- La mécanique importe plus que le circuit : la charge doit passer par le capteur correctement.
- La tarification et l'étalonnage avec masse connue sont requis.
- Sans montage rigide et mécanique appropriée, les lectures précises ne se produiront pas.

## Lectures connexes

- [SparkFun: Load Cell Amplifier HX711 Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide/all) - connexion pratique HX711 et cellule de charge, couleurs de fil, `DT`/`SCK` et exemple d'étalonnage.
- [SparkFun: Load Cell Amplifier HX711 product page](https://www.sparkfun.com/sparkfun-load-cell-amplifier-hx711.html) - description du module HX711, objectif et interface du microcontrôleur.
- [DigiKey: HX711 Datasheet by Avia Semiconductor](https://www.digikey.com/en/htmldatasheets/production/1836471/0/0/1/hx711.html) - fiche technique technique HX711 : ADC 24-bit, entrée de pont différentiel, gain et interface numérique.
- [Phidgets: Load Cell Guide](https://cdn.phidgets.com/docs/Load_Cell_Guide) - exemples pratiques d'installation mécanique de cellule de charge et direction d'application de la charge.
- [SparkFun retired HX711 guide: load cell mechanical setup](https://learn.sparkfun.com/tutorials/retired---load-cell-amplifier-hx711-breakout-hookup-guide) - illustrations utiles des options de montage du capteur poutre, bouton et plateforme.
