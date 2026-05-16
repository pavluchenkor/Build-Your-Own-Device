# Bandes LED

Une bande LED est une carte flexible avec des LED et des pistes d'alimentation. Dans une imprimante, un sécheur ou un petit appareil DIY, elle est généralement utilisée pour l'éclairage de la chambre, l'indication d'état, l'éclairage de la zone de travail ou l'éclairage décoratif de l'enceinte.

L'erreur principale des débutants est de traiter une bande LED comme une petite LED. Même une courte bande peut consommer plus de courant qu'un ventilateur, et une longue bande devient une charge d'alimentation complète.

## Où c'est utilisé

Dans les appareils DIY autour d'une imprimante 3D, les bandes LED sont utiles pour :

- éclairer la chambre de l'imprimante ;
- éclairer le sécheur de filament ;
- indication d'état : chauffage, séchage, erreur, en attente ;
- éclairage de la zone de travail à l'intérieur de l'enceinte ;
- éclairage doux de nuit sans lumière principale ;
- signal visuel lorsque l'impression se termine ou qu'une erreur se produit.

Pour l'éclairage de service, une simple bande blanche est généralement préférable. Pour l'indication de mode, les bandes RGB ou adressables sont pratiques, mais elles sont plus complexes en termes d'alimentation et de contrôle.

## Tension : 5V, 12V ou 24V

Les bandes LED sont disponibles dans différentes tensions :

- `5V` - souvent des bandes adressables comme WS2812/NeoPixel ;
- `12V` - bandes blanches et RGB courantes ;
- `24V` - pratique pour les sections plus longues et les systèmes 24V.

La tension de la bande doit correspondre à la source d'alimentation. Vous ne pouvez pas connecter une bande `12V` à `24V`. Une bande `24V` sur `12V` peut s'assombrir ou ne pas fonctionner. Une bande `5V` sur `12V` ou `24V` sera presque certainement endommagée.

Si votre imprimante a déjà `24V`, cela ne signifie pas qu'une bande peut se connecter. Vous devez acheter exactement une bande `24V` ou mettre un convertisseur CC-CC pour la bonne tension.

## Bandes régulières et adressables

Il existe deux principaux types de bandes LED.

Une bande régulière s'allume tout à la fois. Cela pourrait être :

- blanc monocolor ;
- blanc chaud/froid ;
- bande RGB qui change de couleur le long de sa longueur ;
- bande RGBW avec canal blanc séparé.

Une telle bande n'a pas de microchip sur chaque LED. La luminosité est contrôlée par la commutation de l'alimentation ou le PWM via un MOSFET, un contrôleur LED ou une sortie de carte appropriée.

Une bande adressable a un microchip de contrôle pour les LED individuelles ou les groupes de LED. Elle vous permet d'éclairer différentes sections dans différentes couleurs. Exemples typiques : WS2812B, SK6812, bandes compatibles NeoPixel.

Les bandes adressables nécessitent :

- alimentation à la bonne tension ;
- `GND` commun avec le contrôleur ;
- fil de données `DIN` ;
- direction de données correcte selon la flèche sur la bande ;
- souvent - niveau de signal de données 5V ;
- alimentation soigneuse sans grosses chutes.

Pour un simple éclairage de chambre, une bande adressable est généralement excessive. Pour une indication et des effets sympathiques, c'est pratique, mais nécessite plus d'attention à l'alimentation.

## Courant et puissance

Choisissez une bande LED non seulement par sa couleur et sa longueur. Vous devez connaître sa puissance.

Les pages produits listent généralement :

- tension : par exemple `12V` ou `24V` ;
- puissance par mètre : par exemple `4,8 W/m`, `9,6 W/m`, `14,4 W/m` ;
- nombre de LED par mètre ;
- type de LED : par exemple `3528`, `5050`, `2835` ;
- largeur de bande ;
- degré de protection : nue, gaine silicone, IP65/IP67 ;
- longueur maximale par section.

Le courant est calculé simplement :

```text
courant = puissance / tension
```

Exemple : vous avez `2 m` de bande `24V` à une puissance de `9,6 W/m`.

```text
puissance totale = 2 m × 9,6 W/m = 19,2 W
courant = 19,2 W / 24 V = 0,8 A
```

Pour une telle bande, l'alimentation, le MOSFET, les câbles et le connecteur doivent confortablement gérer plus de `0,8 A`. Pratiquement, il est préférable d'ajouter au moins une marge de `30-50 %`, surtout si la bande fonctionne pendant de longues périodes.

Pour les bandes RGB, vous devez tenir compte du courant maximal de tous les canaux. Blanc sur RGB signifie généralement que les canaux rouge, vert et bleu sont allumés simultanément.

Pour les bandes adressables 5V, une estimation approximative est jusqu'à `60 mA` par pixel RGB au blanc complet. Dans les effets réels, le courant peut être inférieur, mais vous ne pouvez pas dimensionner l'alimentation et le câblage pour « généralement pas à pleine luminosité ».

## Pourquoi vous ne pouvez pas alimenter une bande depuis GPIO

GPIO d'un contrôleur est une sortie de signal, pas une source d'alimentation.

Vous ne pouvez pas connecter une bande LED directement à une broche de microcontrôleur. GPIO n'est pas évaluée pour le courant de la bande. Cela peut endommager la carte, causer des redémarrages, un fonctionnement instable ou un surchauffage des pistes.

Logique correcte :

- le courant de la bande provient de l'alimentation ;
- le contrôleur ne gère que marche/arrêt, luminosité ou données ;
- un MOSFET, un pilote LED, un contrôleur LED ou une sortie de carte appropriée gère la commutation de puissance ;
- les masses du contrôleur et de l'alimentation sont connectées s'il y a un signal de contrôle.

## Connexion d'une bande simple monocolor

Pour une bande blanche `12V` ou `24V`, un MOSFET bas est souvent utilisé : le plus de la bande est connecté au plus d'alimentation, et le moins de la bande est commuté par le module MOSFET.

![Gros plan d'une bande LED avec des diodes SMD](../../../img/03-common-components/05-led-strip-closeup.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:LED_strip_closeup.jpg), Akbermamps, CC BY 4.0*

Circuit typique :

1. L'alimentation `+V` va à la bande LED `+`.
2. La bande LED `-` va à la sortie d'alimentation du module MOSFET.
3. L'alimentation `GND` va au module MOSFET.
4. Le `GND` du contrôleur est connecté à l'alimentation `GND`.
5. La broche de contrôle du contrôleur va à l'entrée du module MOSFET.

Si la carte de l'imprimante a déjà une sortie gérée pour les ventilateurs ou les LED, vous pouvez l'utiliser uniquement si elle est évaluée pour la tension et le courant nécessaires. Vous ne pouvez pas connecter une longue bande à un connecteur aléatoire sans vérifier la limite de sortie.

## Bande RGB

Une bande RGB typique a généralement un plus commun et trois moins gérés :

- `+V` ;
- `R` ;
- `G` ;
- `B`.

Chaque canal de couleur nécessite un canal MOSFET séparé ou un contrôleur RGB prêt à l'emploi. Un MOSFET pour la bande RGB entière ne peut que l'allumer et l'éteindre, pas changer la couleur.

Lors de la sélection d'un module MOSFET pour une bande RGB, regardez le courant par canal et le courant total. Le connecteur, la borne et le fil doivent également gérer la charge.

## Bande adressable

Une bande adressable a généralement :

- `+5V` ou une autre alimentation si ce n'est pas un modèle 5V ;
- `GND` ;
- `DIN` - entrée de données ;
- parfois `DOUT` - sortie de données vers la section suivante.

Règles importantes :

- connectez les données vers la flèche sur la bande ;
- le contrôleur et la bande doivent avoir une masse commune ;
- pour les bandes adressables 5V sur un contrôleur 3,3V, vous avez souvent besoin d'un convertisseur de niveau ;
- avant une longue bande, un condensateur électrolytique à travers l'alimentation est utile ;
- une résistance autour de `300-500 Ohm` est souvent placée dans la ligne de données près de l'entrée de la bande ;
- pour une longue bande, il est préférable d'alimenter non seulement au départ mais à des points supplémentaires.

Si une bande adressable est alimentée depuis une alimentation séparée, vous ne pouvez pas appliquer uniquement `DIN` sans `GND` commun. Le signal de données n'a alors pas de bon niveau de référence et la bande scintille aléatoirement ou ne fonctionne pas.

## Chute de tension et alimentation multi-points

Une longue bande LED peut être brillante au départ et notablement plus sombre à la fin. Ce n'est pas un « mauvais contrôleur », c'est la chute de tension sur les câbles et les pistes de cuivre de la bande.

Plus la tension est basse et le courant est élevé, pire est le problème. Donc, les bandes `5V` et `12V` ont souvent plus besoin d'alimentation à partir de plusieurs points que les bandes `24V` de la même puissance.

Signes de chute de tension :

- la fin de la bande est plus sombre ;
- blanc sur RGB change en jaune ou rouge ;
- la bande adressable scintille pendant les effets lumineux ;
- le contrôleur redémarre lorsque la luminosité augmente ;
- les câbles, le connecteur ou le début de la bande deviennent chauds.

Solution :

- utiliser la bande à la tension appropriée ;
- utiliser un câble avec une jauge suffisante ;
- appliquer l'alimentation au début et à la fin de longues sections ;
- diviser la longue bande en sections ;
- utiliser un fusible sur la ligne d'alimentation ;
- ne pas router tout le courant à travers un connecteur faible ou des pistes fines.

## Chaleur et montage

Une bande LED elle-même produit de la chaleur. C'est particulièrement notable pour les bandes brillantes dans une gaine silicone et les bandes montées à l'intérieur d'une enceinte fermée.

Mauvais emplacements de montage :

- à côté d'un radiateur ;
- sur PLA mou à l'intérieur d'une chambre chaude ;
- sur une surface qui ne dissipe pas la chaleur ;
- où la bande touche des pièces mobiles ;
- sur un couvercle qui est souvent retiré sans connecteur.

Pour une longue durée de vie, il est préférable de monter la bande sur un profil en aluminium ou une autre surface qui dissipe la chaleur. Si la bande est à l'intérieur de la chambre de l'imprimante, tenez compte de la température de la chambre et de la température de la couche adhésive.

## Quoi vérifier avant d'acheter

Avant d'acheter une bande LED, vérifiez :

- tension de la bande ;
- puissance par mètre ;
- longueur totale ;
- couleur : blanc, RGB, RGBW, adressable ;
- type de contrôle ;
- largeur de la bande et emplacement de montage ;
- température du lieu d'installation ;
- si vous avez besoin d'un profil en aluminium ;
- si vous avez besoin d'un module MOSFET ou d'un contrôleur LED ;
- si l'alimentation peut gérer la charge supplémentaire ;
- s'il y a un connecteur approprié pour la maintenance.

Pour une chambre d'imprimante, une bande blanche `24V` est généralement plus pratique si tout le système est déjà `24V`. Pour un petit indicateur ESP32, une courte bande adressable `5V` pourrait être pratique. Pour un long éclairage RGB décoratif, il est préférable de calculer le courant à l'avance et de penser à l'alimentation multi-points.

## Erreurs typiques

- bande connectée à la mauvaise tension ;
- alimentation de la bande depuis GPIO ;
- n'a pas calculé le courant pour la longueur entière ;
- sélection du module MOSFET sans marge ;
- connexion de la bande longue avec un câble fin ;
- masse commune oubliée entre le contrôleur et la bande ;
- bande adressable connectée aux données à `DOUT` au lieu de `DIN` ;
- n'a pas installé de convertisseur de niveau pour la bande adressable 5V depuis le contrôleur 3,3V si nécessaire ;
- alimentation d'une seule extrémité d'une longue bande ;
- installation de la bande dans une zone chaude sans vérifier la température ;
- bande abandonnée sans connecteur sur un couvercle amovible.

## Point principal

Une bande LED n'est pas une LED de signal, c'est une charge. D'abord vérifiez la tension et la puissance, puis calculez le courant, sélectionnez le fil, le MOSFET ou le contrôleur, et seulement ensuite connectez à la carte.

Pour un éclairage simple, choisissez une bande blanche régulière à la tension du système. Pour les effets et l'indication, vous pouvez utiliser une bande adressable, mais l'alimentation, la masse commune, le niveau de signal et la protection contre la chute de tension sont particulièrement importants.

## Matériaux de référence

- [Adafruit NeoPixel Überguide: Best Practices](https://learn.adafruit.com/adafruit-neopixel-uberguide/best-practices) - règles pratiques pour les bandes adressables : masse commune, résistance de ligne de données, condensateur et niveau de signal.
- [Adafruit NeoPixel Überguide: Powering NeoPixels](https://learn.adafruit.com/adafruit-neopixel-uberguide/powering-neopixels) - explication détaillée de l'alimentation de la bande adressable, chute de tension et alimentation multi-points.
- [Adafruit RGB LED Strips: Usage](https://learn.adafruit.com/rgb-led-strips/usage) - exemple de gestion des bandes RGB régulières via des transistors de puissance/MOSFET, pas directement depuis le microcontrôleur.
- [SparkFun WS2812 Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/ws2812-breakout-hookup-guide/addressable-led-strips) - introduction aux bandes adressables WS2812 et leurs variantes.
- [QuinLED: 12V vs 24V LED strip and voltage drop](https://quinled.info/2018/08/24/12v-vs-24v-led-strip-or-voltage-drop/) - explication pratique de pourquoi les bandes longues souffrent de chute de tension et pourquoi 24V est souvent mieux pour les longues sections.
