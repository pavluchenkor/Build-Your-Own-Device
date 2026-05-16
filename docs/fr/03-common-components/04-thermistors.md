# Thermistances

Une thermistance est un capteur de température dont la résistance change lorsqu'elle est chauffée ou refroidie. Dans les imprimantes 3D, les sécheurs et les petits appareils de chauffage, elle est souvent utilisée comme rétroaction pour contrôler le radiateur.

L'option la plus courante dans la communauté de l'impression 3D est la thermistance NTC `100K`. NTC signifie qu'à mesure que la température augmente, la résistance diminue. `100K` signifie généralement environ `100 kOhm` à `25°C`.

## Où c'est utilisé

Les thermistances sont utilisées pour mesurer la température de :

- hotend ;
- lit chauffé ;
- chambre d'imprimante ;
- sécheur de filament ;
- conduit d'air ;
- module de chauffage ;
- zone d'électronique, si une simple protection contre la surchauffe est nécessaire.

Dans un appareil avec un radiateur, une thermistance n'est pas un capteur décoratif. Elle détermine le moment où le contrôleur réduit la puissance, désactive le chauffage ou s'arrête avec une erreur.

## NTC 100K, Beta et tables de consultation

Différentes thermistances peuvent se ressembler mais avoir des caractéristiques différentes.

Paramètres importants :

- résistance à `25°C`, par exemple `100 kOhm` ;
- type : NTC ou PTC ;
- Beta, par exemple `3950K` ;
- tableau de consultation résistance/température ;
- plage de température de fonctionnement ;
- précision ;
- boîtier : perle de verre, cartouche, capteur de vis, gaine ;
- isolation du câble.

Si le micrologiciel sélectionne le mauvais type de capteur, la température s'affichera incorrectement. L'erreur peut être faible à température ambiante et dangereuse à la température de fonctionnement.

Donc, l'expression « thermistance 100K » ne suffit pas toujours. Pour le micrologiciel, un modèle spécifique ou au moins le bon Beta/tableau est important.

## Comment le contrôleur mesure la température

Une thermistance est généralement connectée à une entrée analogique via un diviseur de tension avec une résistance de pull-up. Le contrôleur mesure la tension, la convertit en résistance, puis utilise un tableau de consultation ou une formule pour obtenir la température.

![Diviseur de tension avec thermistance pour la mesure de température](../../../img/03-common-components/04-thermistor-voltage-divider.svg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Thermistor_potential_divider.svg), Sjlegg, Public Domain*

Dans Klipper, ceci est défini via `sensor_type`, `sensor_pin`, parfois `pullup_resistor` ou une section `[thermistor]` personnalisée.

Dans Marlin, le type de thermistance est sélectionné via les paramètres de configuration du capteur et les limites de température.

Pour l'utilisateur, la conclusion clé est simple : le micrologiciel doit connaître exactement le type de capteur installé dans l'appareil.

## Circuit ouvert et court-circuit

Une thermistance et ses câbles peuvent échouer.

Symptômes typiques :

- fil cassé ;
- mauvais contact du connecteur ;
- les fils se courtent ;
- isolant endommagé ;
- le capteur a glissé hors de la gaine ;
- fil abrasé dans une pièce mobile ;
- le capteur indique la température ambiante même si le chauffage se produit.

Le micrologiciel a généralement des protections comme `MINTEMP`, `MAXTEMP`, vérification du chauffage et protection contre les emballements thermiques. Mais ces protections ne fonctionnent que si le capteur et le micrologiciel sont correctement configurés et que la partie électrique peut réellement être coupée.

Si un capteur tombe du radiateur mais reste électriquement connecté, c'est particulièrement dangereux : le micrologiciel peut voir « basse température » et continuer à chauffer.

## Contact thermique

Le montage de la thermistance est souvent plus important qu'il ne le semble.

Le capteur doit mesurer la température du lieu que vous avez réellement besoin de contrôler. Pour une hotend, c'est le bloc de chauffage. Pour un lit, c'est la surface ou un endroit lié à la température réelle du lit. Pour un radiateur d'air, c'est un point choisi par la logique de sécurité et de contrôle.

Le contact thermique est affecté par :

- la pression du capteur ;
- la pâte thermique ;
- le trou de montage ;
- la gaine ;
- le montage par vis ;
- l'écart ;
- le matériau autour du capteur ;
- l'état du câble ;
- la contamination ou la pâte séchée ;
- la vibration et le montage lâche.

Si une thermistance touche à peine une pièce latéralement, elle peut réagir lentement et afficher la mauvaise température. Le contrôleur PID reçoit alors des informations retardées et la température peut dépasser ou excéder la cible.

## Boîtier du capteur

Les thermistances sont disponibles dans différents boîtiers.

Perle de verre :

- bon marché ;
- minuscule ;
- nécessite un montage prudent ;
- facile à endommager le fil ou l'isolant.

Thermistance cartouche :

- plus facile à insérer dans le trou du bloc de chauffage ;
- généralement mécaniquement plus stable ;
- important de faire correspondre le diamètre et la longueur.

Thermistance à vis :

- se monte facilement sur une surface métallique ;
- peut donner un bon contact s'il est installé correctement ;
- ne doit pas être trop serré ou endommagé le câble.

Capteur en gaine :

- pratique pour l'air, le liquide ou l'enceinte ;
- répond plus lentement si la gaine est massive ;
- le point d'installation approprié est important.

Le choix du boîtier dépend de ce qui est mesuré et de la façon dont le capteur sera entretenu.

## Vérification du multimètre

La vérification de base peut être effectuée avec un multimètre en mode résistance. La procédure détaillée se trouve dans l'article pratique : [Vérifier une thermistance](../05-practical-guides/02-checking-a-thermistor.md).

Pour une thermistance `100K` NTC typique à température ambiante autour de `25°C`, vous vous attendez à environ `100 kOhm`. La valeur exacte dépend de la température et de la tolérance.

Lorsqu'elle est chauffée avec les doigts, la résistance NTC devrait diminuer. Si le multimètre indique un circuit ouvert, un court-circuit ou la valeur saute lorsque vous bougez le fil, vérifiez d'abord le connecteur et le câblage.

La vérification au multimètre ne remplace pas l'étalonnage et ne prouve pas l'exactitude à `200°C`, mais elle montre rapidement un circuit ouvert, un court-circuit ou un mauvais type de capteur.

## Quoi vérifier avant d'acheter

Avant d'acheter une thermistance, vérifiez :

- résistance à `25°C` ;
- Beta ou modèle exact ;
- compatibilité avec le micrologiciel ;
- plage de température de fonctionnement ;
- boîtier du capteur ;
- longueur et matériau du câble ;
- type de connecteur ;
- méthode de montage ;
- si vous avez besoin d'une cartouche, d'une vis, d'une gaine ou d'une perle de verre ;
- si le capteur s'adapte à votre bloc de chauffage ou à la localisation d'installation ;
- disponibilité d'une description technique ou d'une information claire.

Pour une hotend, il est préférable d'obtenir un capteur qui s'adapte mécaniquement au bloc spécifique. Pour une chambre ou un sécheur, la localisation d'installation, la protection du câble et la stabilité de la mesure dans le flux d'air sont plus importantes.

## Erreurs typiques

- mauvais `sensor_type` sélectionné ;
- penser que n'importe quelle thermistance `100K` est la même ;
- le capteur est mal appuyé ;
- pas de contact thermique approprié ;
- le capteur a glissé hors de la gaine ;
- le fil a frotté ou s'est cassé au corps du capteur ;
- le contact du connecteur est mauvais ;
- le câblage à côté des lignes d'alimentation inutilement ;
- la thermistance mesure l'air mais le contrôleur pense qu'elle mesure le radiateur ;
- le micrologiciel défini sans `min_temp` et `max_temp` raisonnables ;
- radiateur allumé sans protection matérielle indépendante.

## Point principal

Une thermistance est la rétroaction d'un radiateur. Il est important non seulement d'acheter « 100K NTC », mais de sélectionner le bon type dans le micrologiciel, de monter le capteur au bon endroit et de vérifier le câblage.

Un mauvais contact thermique ou un mauvais `sensor_type` peuvent être plus dangereux qu'un capteur complètement mort, car le système continue à fonctionner mais prend des décisions basées sur une mauvaise température.

## Matériaux de référence

- [Klipper Configuration Reference: Temperature sensors](https://www.klipper3d.org/Config_Reference.html#temperature-sensors) - `sensor_type` officiel, `pullup_resistor`, `[thermistor]` personnalisé et capteurs de température dans Klipper.
- [Marlin Configuration: Temperature Ranges and Thermal Protection](https://marlinfw.org/docs/configuration/configuration.html#temperature-ranges) - limites de température, `MINTEMP`, `MAXTEMP` et protection thermique.
- [Vishay: NTC Thermistors](https://www.vishay.com/en/thermistors/ntc/) - paramètres de thermistance NTC : résistance à `25°C`, Beta, tolérance et plage de fonctionnement.
- [RepRap Europe: Thermistor NTC100K](https://www.reprap-3d-printer.com/product/335-thermistor-ntc100k) - exemple de thermistance NTC `100K` typique 3D imprimante avec Beta `3950` et `100 kOhm` à `25°C`.
- [RepRap Europe: Thermistor Cartridge 100k HT-NTC B3950](https://reprap.eu/produto/?id=1245&nome=Thermistor+Cartridge+100k+HT-NTC+B3950) - exemple de thermistance cartouche pour bloc de chauffage et montage mécanique.
