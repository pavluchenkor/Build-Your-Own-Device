# Conductivité thermique

La conductivité thermique indique à quel point un matériau transfère facilement la chaleur à travers lui-même.

Pour un sécheur, une chambre, un filtre, un conduit d'air ou un boîtier faits maison, ce n'est pas une physique abstraite. La conductivité thermique détermine si la chaleur s'échappera vers l'extérieur, si un hot spot apparaîtra près du radiateur, combien le mur extérieur se réchauffera et si une pièce imprimée ramollira.

## Idée simple

La chaleur a toujours tendance à s’échapper d’une zone plus chaude vers une zone plus froide. Plus la conductivité thermique d’un matériau est élevée, plus la chaleur le traverse facilement.

Le taux de transfert de chaleur est affecté par :

- material;
- wall thickness;
- contact area;
- temperature difference;
- qualité du contact entre les pièces ;
- présence d'air, de vides et d'isolation.

Une fine plaque d'aluminium peut rapidement diffuser la chaleur dans tout le boîtier. Au contraire, une épaisse couche de laine minérale ou de mousse isolante empêche la chaleur de s'échapper.

## Valeurs de référence matériau

Les valeurs ci-dessous servent uniquement à comprendre les ordres de grandeur. Pour une vraie construction, consultez la fiche technique du matériau spécifique.

| Material | Approximate Thermal Conductivity, `W/(m*K)` | What It Means in Practice |
| --- | ---: | --- |
| Copper | about `400` | excellent heat conductor, suitable for heat dissipation, but quickly transfers heat where it is not always needed |
| Aluminum | about `200-240` | distributes heat well, useful as a plate, radiator, or heat spreader |
| Steel | about `15-60` | conducts heat worse than aluminum, but screws and posts can still be thermal bridges |
| Glass | about `1` | conducts heat much worse than metal, but is not insulation in the conventional sense |
| Common plastics | about `0.1-0.5` | conduct heat poorly, but can soften and be flammable |
| Mineral wool, fiberglass | about `0.04` | effectively reduces heat loss, but requires protection from dust, moisture, and mechanical damage |
| Expanded polystyrene / polyurethane foam | about `0.03` | good insulation, but near heat, working temperature and fire properties are important |
| Air | about `0.026` | conducts heat poorly by itself, but transfers heat via convection when moving |

La conclusion principale : le métal et l'isolation diffèrent non pas d'un facteur deux, mais de plusieurs ordres de grandeur. Par conséquent, même une petite pièce métallique peut modifier considérablement l’image thermique.

## Pont thermique

Un pont thermique est un chemin par lequel la chaleur s’échappe plus facilement que par le reste de la structure.

![Classic thermal bridge through an enclosure](../../img/04-thermal-physics-and-materials/02-thermal-bridge-classic.png)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Pont_thermique_classique.png), AmisDeLaThermique, CC BY-SA 3.0*

Ponts thermiques typiques :

- metal screw through an insulated wall;
- plaque d'aluminium reliée au boîtier extérieur ;
- poteau métallique entre la chambre chaude et le panneau extérieur ;
- bornier ou fixation à proximité du radiateur ;
- conduit d'air qui touche directement une partie chaude.

Un pont thermique n'est pas toujours mauvais. Parfois, il est nécessaire de dissiper la chaleur d'un interrupteur d'alimentation, d'un radiateur ou d'un nœud chaud. Le problème commence lorsque le pont est accidentel : la chambre perd de la chaleur, la surface extérieure devient chaude et le plastique près du pont chauffe plus que prévu.

## Métal : Heat Sink or Accidental Heating

Le métal est pratique à utiliser dans les appareils chauffants :

- comme écran entre le radiateur et le plastique ;
- as a heat distribution plate;
- comme base pour le montage du radiateur ;
- comme radiateur pour l'électronique de puissance ;
- as a non-flammable inner surface.

Mais le métal ne garantit pas automatiquement la sécurité d’un appareil. Si une plaque métallique touche une zone chaude et le boîtier extérieur, elle peut conduire la chaleur vers l'extérieur. Si du plastique y est vissé, ce plastique peut chauffer à travers la fixation. Si des fils le traversent, près du bord, vous avez besoin de traversées, d'une protection contre les frottements et d'une marge de température pour l'isolation.

## Isolation : Lower Loss, More Responsibility

L’isolation réduit les pertes de chaleur, mais n’élimine pas le contrôle de la température.

Lorsque vous isolez une chambre :

- il est plus facile pour le radiateur d'augmenter la température ;
- le logement peut devenir plus froid à l'extérieur ;
- cooling time increases;
- la température locale à proximité du radiateur peut augmenter ;
- fan failure or stuck switch becomes more dangerous.

Par conséquent, l’isolation ne peut pas être ajoutée à titre d’« amélioration » sans être testée à nouveau. Après l'isolation, vous devez mesurer à nouveau les températures à l'intérieur de la chambre, au niveau du radiateur, des fils, des bornes et sur la surface extérieure.

## L'espace d'air fonctionne aussi

L'air stationnaire conduit mal la chaleur. Par conséquent, les entrefers, les doubles parois et les matériaux en mousse peuvent réduire le transfert de chaleur.

Mais si l’air commence à se déplacer, la convection entre en jeu. La chaleur est alors transférée par le flux d’air, et non seulement par conduction thermique. Par conséquent, un espace à travers lequel circule un flux chaud peut chauffer le boîtier plus qu'une paroi épaisse sans flux.

En pratique, cela signifie :

- ne laissez pas d'espaces accidentels à proximité du radiateur ;
- ne dirigez pas le flux chaud directement sur le plastique ;
- ne pas considérer les entrefers comme une protection si un courant les traverse ;
- vérifier la température en mode de fonctionnement réel, pas seulement sur un appareil froid.

## Quoi chercher dans la fiche technique du matériau

Pour les matériaux proches de la chaleur, la conductivité thermique n’est pas la seule chose qui compte.

Vérifiez :

- maximum continuous working temperature;
- softening temperature or thermal deformation temperature;
- classe d'inflammabilité et de comportement au feu ;
- possibilité de contact avec l'air chaud ;
- comportement de la couche de colle, du film, du revêtement ou du laminage ;
- recommandations d'utilisation du fabricant ;
- disponibilité d'une FDS/fiche de données de sécurité si le matériau peut chauffer ou être traité.

Si un matériau n'a pas de documentation claire, ne le placez pas à proximité du radiateur et ne l'utilisez pas comme seule protection.

## Vérification pratique Order

Pour le logement, l'enceinte ou le séchoir, il convient de procéder de la manière suivante :

1. Identifiez la zone chaude : chauffage, sortie d'air, bornes, interrupteur d'alimentation.
2. Séparez la zone chaude du plastique avec du métal, de la céramique ou un autre matériau approprié.
3. Vérifiez où le métal conduit la chaleur.
4. Ajoutez de l'isolant uniquement là où il ne couvre pas les nœuds chauds dangereux.
5. Mesurez la température en plusieurs points après l'échauffement.
6. Vérifiez le mode de panne du ventilateur si le chauffage dépend du débit d'air.
7. Ajoutez une protection indépendante contre la surchauffe là où la surchauffe est dangereuse.

Un capteur de température dans la chambre ne montre pas l'intégralité de l'image thermique. Vous avez besoin de mesures à proximité du radiateur, sur les fixations, sur les fils, sur le boîtier et sur les pièces imprimées.

## Conclusion principale

La conductivité thermique vous aide à comprendre où ira réellement la chaleur. Le métal peut être un dissipateur thermique utile ou un pont thermique accidentel. L’isolation peut améliorer l’efficacité, mais en même temps amplifier les conséquences d’une défaillance.

Toute modification du boîtier, de l'isolation, des fixations ou du conduit d'air doit être vérifiée par une mesure de température en mode de fonctionnement réel.

## Matériaux sur le Topic

- [Engineering ToolBox: Thermal Conductivity of Common Materials](https://www.engineeringtoolbox.com/thermal-conductivity-d_429.html) - reference values of thermal conductivity for metals, plastics, air, glass, and insulation.
- [Engineering ToolBox: Conductive Heat Transfer](https://www.engineeringtoolbox.com/conductive-heat-transfer-d_428.html) - relationship between heat flow, material, wall thickness, area, and temperature difference.
- [NASA Glenn Research Center: Heat Transfer](https://www1.grc.nasa.gov/beginners-guide-to-aeronautics/heat-transfer-3/) - basic explanation of heat transfer from hot body to cold.
- [U.S. Department of Energy: Principles of Heating and Cooling](https://www.energy.gov/energysaver/principles-heating-and-cooling) - simple explanation of thermal conduction, convection, radiation, and role of insulation.
- [Prusa Knowledge Base: Material table](https://help.prusa3d.com/materials) - practical reference for temperature behavior of popular 3D printing materials.
