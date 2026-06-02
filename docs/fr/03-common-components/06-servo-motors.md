# Moteurs servo

Un moteur servo est un petit entraînement avec un moteur, une boîte de vitesses et de l'électronique interne. Vous lui donnez une position, et il essaie de faire tourner l'arbre vers cette position et de la maintenir.

Dans les appareils simples, un servo est pratique là où vous avez besoin non seulement d'allumer un moteur, mais de faire tourner un mécanisme à un angle compréhensible : ouvrir un amortisseur, décaler un verrou, appuyer sur un bouton, changer le flux d'air ou faire tourner un petit drapeau indicateur.

## Où c'est utilisé

Dans les appareils de type iDryer et les périphériques d'imprimante 3D, un servo peut être utilisé pour :

- amortisseur d'admission ou d'échappement d'air ;
- commutation de conduit d'air ;
- ouverture/fermeture d'un petit couvercle ;
- verrou mécanique ;
- appui sur un bouton physique ;
- déplacement d'un drapeau indicateur ;
- dosage simple ou crochet.

Un servo est bon pour la mécanique légère avec un déplacement limité. Pour la rotation continue d'un ventilateur, d'une vis ou d'une pompe, cela ne fonctionne généralement pas : vous avez besoin d'un moteur et d'un pilote différents.

## Trois fils

Un servo loisir typique a trois lignes :

- puissance : généralement `4,8-6V`, parfois `7,4V` ou autre valeur sur des modèles spéciaux ;
- masse : `GND` ;
- signal : impulsions de contrôle du contrôleur.

Couleurs de fil courantes :

- rouge - puissance ;
- noir ou marron - masse ;
- jaune, orange ou blanc - signal.

Vous ne pouvez pas faire confiance aveuglément aux couleurs. Différents fabricants utilisent des schémas de couleurs différents. Avant de connecter, vérifiez les marquages, la page produit ou la description technique.

Un diagramme de connexion détaillé avec alimentation séparée se trouve dans la section pratique : [Connexion d'un moteur servo](../06-practical-guides/03-connecting-servo.md).

## Ce que « Moteur servo » signifie

À l'intérieur d'un servo de position loisir typique, il y a :

- moteur CC ;
- boîte de vitesses ;
- capteur de position, souvent un potentiomètre ;
- carte de contrôle ;
- arbre de sortie avec bras.

Le contrôleur externe ne gère pas le moteur directement. Il envoie un signal de position, et l'électronique interne du servo fait automatiquement tourner le moteur pour que l'arbre atteigne l'angle souhaité.

Un servo diffère donc d'un moteur CC régulier :

- le moteur CC tourne simplement lorsqu'il est alimenté ;
- le servo essaie d'atteindre une position définie ;
- le servo tire du courant même en maintenant une position s'il y a une charge sur l'arbre ;
- le servo peut augmenter rapidement le courant et devenir chaud s'il est bloqué.

## Servo positionnel et rotation continue

Le type le plus courant est un servo positionnel. Vous définissez un angle, par exemple `0`, `90` ou `180` degrés.

Le servo à rotation continue se ressemble mais fonctionne différemment : le signal de contrôle définit non pas l'angle, mais la direction et la vitesse de rotation. Il ne sait pas où est l'arbre. Pour un amortisseur ou un verrou, un tel servo est souvent inconvénient car sans capteurs supplémentaires, vous ne pouvez pas garantir la position.

Avant d'acheter, vérifiez ce que la description dit :

- `servo standard`, `servo positionnel`, `180°` - généralement positionnel ;
- `rotation continue`, `360°` - généralement tourne en continu, pas positionné à un angle.

La phrase `servo 360°` sur un marché est risquée : parfois c'est un servo à rotation continue, parfois c'est juste une plage étendue. Vous avez besoin de vérifier la description technique et les avis avec des mesures réelles.

## Signal de contrôle

Un servo loisir typique est contrôlé par des impulsions répétées.

Directives typiques :

- période environ `20 ms` ;
- impulsion environ `1 ms` - un bord de la plage ;
- impulsion environ `1,5 ms` - milieu ;
- impulsion environ `2 ms` - autre bord de la plage.

Différents servos ont des limites réelles différentes. Certains fonctionnent environ `500-2500 us`, d'autres ne fonctionnent en toute sécurité que dans une plage plus étroite.

Les positions extrêmes ne peuvent donc pas être définies aveuglément. Vérifiez d'abord le milieu, puis les petites déviations, seulement ensuite élargissez la plage.

## Puissance et courant

Le fil de signal n'alimente pas le servo. Il tire l'énergie du moteur de la ligne d'alimentation.

Même un petit servo peut brièvement tirer un grand courant au démarrage, mouvement rapide ou arrêt mécanique. Le courant moyen « en démo calme » ne montre pas le pire cas.

Paramètres importants :

- tension de fonctionnement ;
- courant sans charge ;
- courant chargé ;
- courant de blocage - courant avec arbre bloqué ;
- couple de maintien ou couple de blocage ;
- vitesse de rotation ;
- température de fonctionnement.

Si la description technique liste le courant de blocage, la source d'alimentation doit être choisie avec cette valeur et marge. Si le courant de blocage n'est pas listé, vous ne pouvez pas considérer la puissance « sûre à l'œil » : pour un appareil réel, il est préférable d'utiliser une source avec marge et vérifier la chute de tension sous charge.

Pour un petit servo, une sortie 5V de la carte fonctionne parfois. Mais pour un amortisseur, un verrou ou plusieurs servos, vous avez généralement besoin d'un convertisseur CC-CC 5V/6V séparé ou d'une alimentation. La masse doit être commune avec le contrôleur.

## Couple et mécanique

Un servo est choisi non pas seulement par la taille. Le paramètre mécanique principal est le couple, souvent en `kg·cm` ou `N·cm`.

Grossièrement :

- plus le levier est long, plus le couple nécessaire est grand ;
- plus l'amortisseur ou le mécanisme est lourd ou serré, plus le couple nécessaire est grand ;
- la friction, le désalignement et le joint augmentent considérablement la charge ;
- lorsqu'il est maintenu à un arrêt, le servo se réchauffe et tire du courant.

Exemple : un petit amortisseur léger peut fonctionner correctement avec un microservo. Un amortisseur sur un joint serré ou un couvercle avec un ressort peut nécessiter un plus grand servo avec des engrenages métalliques.

Pour une mécanique fiable :

- ne forcez pas le servo à constamment pousser contre un arrêt physique ;
- limiter les angles dans le micrologiciel ;
- laisser une petite marge de déplacement ;
- faire la liaison sans désalignement ;
- utiliser une longueur de bras appropriée ;
- tester le fonctionnement à la température réelle de l'enceinte.

Si le servo bourdonne à la position finale, cela signale généralement une charge, un arrêt ou une mauvaise géométrie.

## Boîte de vitesses : plastique ou métal

Les engrenages en plastique sont moins chers, plus silencieux et fonctionnent pour les tâches légères. Mais ils se cassent plus rapidement sur les impacts, les blocages et les charges lourdes.

Les engrenages métalliques sont plus forts, mais le servo peut être plus bruyant, plus lourd et plus cher. Pour les amortisseurs, les verrous et les mécanismes qu'un utilisateur peut accidentellement toucher, une boîte de vitesses métallique a souvent du sens.

Mais les engrenages métalliques ne remplacent pas la bonne mécanique. Si le mécanisme se bloque, il peut endommager le bras, le boîtier, le support ou l'arbre lui-même.

## Servo analogique et numérique

Dans les projets simples, les servos loisir analogiques sont plus courants. Les servos numériques maintiennent généralement la position plus fermement et réagissent plus rapidement, mais peuvent tirer plus de courant et être plus bruyants en maintenant.

Pour un amortisseur de sécheur ou un simple verrou, ce qui importe généralement plus est :

- assez de couple ;
- puissance normale ;
- mécanique fiable ;
- plage d'angles claire ;
- température de fonctionnement ;
- durée de vie de la boîte de vitesses.

Être « numérique » ne fait pas automatiquement d'un servo un bon pour l'appareil.

## Quoi vérifier avant d'acheter

Avant d'acheter un servo, vérifiez :

- positionnel ou rotation continue ;
- tension de fonctionnement ;
- courant requis et courant de blocage si listé ;
- couple ;
- vitesse de rotation ;
- plage d'angle ;
- matériau de la boîte de vitesses ;
- taille du boîtier ;
- type de connecteur ;
- longueur du fil ;
- température de fonctionnement ;
- disponibilité d'une description technique ou des spécifications raisonnables.

Pour un petit drapeau, vous pouvez utiliser un microservo. Pour un amortisseur avec un joint, un verrou ou un levier dans une chambre chaude, il est préférable de ne pas choisir le servo le moins cher sans spécifications.

## Erreurs typiques

- alimenter le servo depuis GPIO ;
- alimentation depuis une broche 5V de carte faible ;
- masse commune oubliée avec alimentation séparée ;
- fait confiance aux couleurs des fils sans vérifier ;
- confusion entre servo positionnel et servo à rotation continue ;
- n'a pas tenu compte du courant de blocage ;
- placé le servo contre un arrêt mécanique ;
- a utilisé l'angle `0` ou `180` alors que le mécanisme ne se déplace en toute sécurité que dans une plage étroite ;
- a choisi le servo uniquement par la taille, sans calculer le couple ;
- a mis des engrenages en plastique où l'impact ou le blocage est possible ;
- placé le servo près d'un radiateur sans vérifier la température.

## Point principal

Un servo est un composant pratique pour les amortisseurs, les verrous et les petits mécanismes, mais il a besoin d'une alimentation normale et d'une mécanique soigneuse. Un signal du contrôleur définit seulement la position, et tout le courant du moteur passe par la ligne d'alimentation.

Avant utilisation, vérifiez le type de servo, la tension, le couple, le courant, la plage d'angles et le comportement mécanique aux positions finales.

## Matériaux de référence

- [SparkFun: Hobby Servo Tutorial](https://learn.sparkfun.com/tutorials/hobby-servo-tutorial) - explication de base de la structure du servo loisir, du signal, de la puissance et des problèmes typiques.
- [SparkFun: Basic Servo Control for Beginners](https://learn.sparkfun.com/tutorials/basic-servo-control-for-beginners/servo-motor-basics) - tableau des couleurs de fil typiques, puissance, courant de blocage et plage de signal de contrôle.
- [Pololu: Electrical characteristics of servos](https://www.pololu.com/blog/16/electrical-characteristics-of-servos-and-introduction-to-the-servo-control-interface) - explication utile des courants du servo et pourquoi le courant de blocage est important pour la sélection de l'alimentation.
- [Adafruit: If the Servo Misbehaves](https://learn.adafruit.com/adafruit-arduino-lesson-14-servo-motors/if-the-servo-misbehaves) - description pratique de la chute de puissance et du condensateur près du servo.
- [Arduino Servo Library Reference](https://www.arduino.cc/reference/en/libraries/servo/) - référence officielle de la bibliothèque Servo pour l'approche Arduino et la description du servo standard/rotation continue.
