# Physique thermique et matériaux

Cette section est nécessaire pour les appareils avec un radiateur, une chambre, un sécheur de filament, un filtre avec air chaud, des conduits d'air, des ventilateurs, une isolation ou des pièces imprimées près de hautes températures.

Vous ne trouverez pas un cours de physique académique ici. L'objectif est pratique : comprendre où va la chaleur, pourquoi le boîtier se réchauffe de manière inégale, pourquoi un matériau convient pour une paroi de chambre alors qu'un autre peut ramollir, fumer ou devenir un risque d'incendie.

## Pourquoi c'est important

Dans un simple appareil chauffé, vous ne pouvez pas penser que c'est la seule façon :

```text
placé un radiateur -> il s'est réchauffé
```

En pratique, vous devez répondre à d'autres questions :

- où va la chaleur du radiateur ;
- où apparaîtront les hot spots ;
- ce que le capteur de température voit ;
- le matériau résistera-t-il au chauffage prolongé ;
- que se passe-t-il si le ventilateur échoue ;
- que se passe-t-il si un MOSFET/SSR colle ;
- les câbles, les bornes ou le plastique finiront-ils dans la zone de surchauffe ;
- y a-t-il une protection indépendante contre la surchauffe.

Un appareil peut afficher `45°C` sur l'écran, mais à côté du radiateur, de la borne ou à l'intérieur du conduit d'air, il peut être beaucoup plus chaud. Par conséquent, non seulement la température de la chambre cible est importante, mais aussi les températures locales des pièces.

## Trois façons dont la chaleur se propage

La chaleur se transfère de trois façons principales :

![Trois mécanismes de transfert de chaleur : conduction, convection et rayonnement](../../../img/04-thermal-physics-and-materials/01-heat-transfer-kettle.png)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Kettle-convection-conduction-radiation.png), P.wormer, CC BY-SA 3.0*

**Conduction thermique** - la chaleur passe à travers un matériau. Par exemple, un support métallique transfère rapidement la chaleur d'une zone chaude au boîtier.

**Convection** - la chaleur est transportée par un courant d'air. Par exemple, un ventilateur prend la chaleur du radiateur et la propage dans toute la chambre.

**Rayonnement** - une surface chaude transfère la chaleur via le rayonnement infrarouge. Par exemple, un élément fortement chauffé peut chauffer le plastique à proximité même sans contact direct.

Dans un appareil réel, les trois mécanismes fonctionnent presque toujours simultanément.

## Le matériau fait partie du système thermique

Le matériau du boîtier, du mur, du conduit d'air ou du support affecte le régime thermique.

Métal :

- conduit bien la chaleur ;
- peut dissiper la chaleur de la zone chaude ;
- peut rendre la surface externe chaude ;
- ne résout pas le problème d'isolant et de sécurité électrique par lui-même.

Plastique :

- conduit mal la chaleur ;
- peut être pratique pour un boîtier ;
- peut ramollir et perdre de la résistance ;
- peut être inflammable ou fumer lorsqu'il surchauffe.

Isolation :

- réduit les pertes de chaleur ;
- aide à maintenir la température de la chambre ;
- peut amplifier la surchauffe locale ;
- nécessite une couche protectrice et une vérification de la sécurité incendie.

Il n'y a pas de matériau universel « meilleur ». Il y a un matériau approprié pour un emplacement spécifique, une température, une charge et un scénario de défaillance.

## La température de fonctionnement n'est pas la température de fusion

Les débutants regardent souvent uniquement la température de fusion. C'est une erreur.

Le matériau peut devenir inadapté plus tôt :

- ramollir ;
- perdre de forme ;
- rétrécir ;
- perdre de résistance ;
- commencer à sentir ;
- libérer des produits de décomposition ;
- devenir plus inflammable.

Pour le boîtier, le montage ou le conduit d'air, la température de travail permissible, la température de ramollissement, les propriétés de feu et les recommandations du fabricant sont plus importantes.

## L'air doit se déplacer correctement

Un ventilateur dans un appareil chauffé n'est pas là « pour montrer ». Elle détermine comment la chaleur s'échappe du radiateur.

Sans flux approprié :

- le radiateur peut localement surchauffer ;
- la chambre se réchauffera de manière inégale ;
- le capteur peut ne pas montrer la bonne température ;
- les pièces à proximité peuvent devenir plus chaudes que prévu ;
- le contrôle PID se comportera pire.

Mais le ventilateur doit également être sélectionné et installé correctement : flux, pression statique, direction, filtre, écran et conduit d'air peuvent complètement changer le résultat.

## Quoi vérifier dans n'importe quel appareil chauffé

Avant l'assemblage et le premier test, vérifiez :

- puissance du radiateur ;
- température à côté du radiateur ;
- température de l'air après le radiateur ;
- température des bornes et des câbles ;
- température du boîtier et des pièces imprimées ;
- si le matériau résiste à la température de travail avec marge ;
- si le matériau inflammable est près de la zone chaude ;
- existe-t-il un fusible ;
- existe-t-il une protection indépendante contre la surchauffe ;
- que se passe-t-il si le ventilateur échoue ;
- que se passe-t-il si le capteur de température échoue.

Le premier test est effectué sous observation et avec la capacité de couper rapidement l'alimentation.

## Comment lire cette section

La section se compose de trois sujets pratiques :

- [Conductivité thermique](02-thermal-conductivity.md) - pourquoi le métal, le plastique, le verre et l'isolation se comportent différemment.
- [Matériaux, inflammabilité et émissions nuisibles](03-material-safety.md) - comment choisir le matériau près de la chaleur et quoi lire dans la fiche technique.
- [Convection et flux d'air](04-convection-and-airflow.md) - pourquoi le même radiateur fonctionne différemment avec différents flux d'air.

## Conclusion principale

Un appareil chauffé n'est pas seulement un radiateur et un capteur. C'est un système thermique : radiateur, air, boîtier, matériaux, câbles, bornes, ventilateur, capteurs et protection d'urgence.

Si un matériau est pratique, bon marché et facile à couper, cela ne signifie pas qu'il peut être placé à côté d'un radiateur. Vérifiez d'abord la température, le transfert de chaleur, les propriétés de feu, la documentation et les scénarios de défaillance.

## Matériaux sur le sujet

- [U.S. Department of Energy: Principles of Heating and Cooling](https://www.energy.gov/energysaver/principles-heating-and-cooling) - explication simple de la conduction thermique, convection et rayonnement.
- [NASA Glenn Research Center: Heat Transfer](https://www1.grc.nasa.gov/beginners-guide-to-aeronautics/heat-transfer-3/) - explication de base du transfert de chaleur d'un corps plus chaud à un corps plus froid.
- [Engineering ToolBox: Conductive Heat Transfer](https://www.engineeringtoolbox.com/conductive-heat-transfer-d_428.html) - conduction thermique, gradient de température, épaisseur du matériau et murs multicouches.
- [UL Solutions: Combustion Fire Tests for Plastics](https://www.ul.com/services/combustion-fire-tests-plastics) - pourquoi les matériaux plastiques sont comparés par le comportement en cas d'incendie, pas seulement par la température de fusion.

## Voir aussi

- [iDryer docs: Radiateurs](../03-common-components/02-heaters.md) - article local sur la sélection du radiateur, le commutateur de puissance, le capteur et la protection indépendante contre la surchauffe.
