# Multimètre

Un multimètre est le principal outil de diagnostic de première ligne.

Vous pouvez vérifier avec lui :

- si l'alimentation est présente ;
- si la tension est correcte ;
- où se trouvent plus et moins ;
- si un fil est cassé ;
- si un fusible est intact ;
- si une thermistance semble fonctionnelle ;
- s'il y a une chute de tension sous charge.

Mais il est facile de faire des erreurs avec un multimètre si vous confondez les modes. Les erreurs les plus dangereuses impliquent la mesure du courant et la tension secteur.

## Sondes et ports

Un multimètre a généralement :

- `COM` - port commun, où vous insérez presque toujours la sonde noire ;
- `V/Ohm/mA` ou similaire - pour tension, résistance, continuité et petits courants ;
- `10A` ou `A` - port séparé pour courant important.

Avant de mesurer, vérifiez toujours :

- dans quel port la sonde rouge est insérée ;
- quel mode est sélectionné ;
- exactement ce que vous êtes sur le point de mesurer.

Une erreur très courante : après mesure du courant, vous oubliez de déplacer la sonde de `A` vers `V/Ohm`, puis tentez de mesurer la tension. Cela peut causer un court-circuit.

## Mesure de la tension DC

DC est tension directe (constante). Dans nos appareils, cela est généralement :

- `3.3V` ;
- `5V` ;
- `12V` ;
- `24V`.

Procédure :

1. Sonde noire dans `COM`.
2. Sonde rouge dans le port `V`.
3. Sélectionnez le mode tension DC : généralement `V` avec une ligne droite.
4. Sonde noire sur négatif ou `GND`.
5. Sonde rouge sur positif.
6. Lisez l'affichage.

Si un signe moins apparaît avant le nombre sur l'affichage, les sondes sont inversées. C'est utile : vous pouvez déterminer la polarité de cette façon.

![Multimètre numérique avec sondes](../../../img/05-tools/02-digital-multimeter.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Aneng_AN870_multimeter_02.jpg), Retired electrician, CC0 Public Domain*

## Où mesurer la tension

Ne vous limitez pas à la sortie de l'alimentation.

Vérifiez :

- sur les bornes d'alimentation ;
- sur l'entrée de la carte ;
- sur les bornes de charge ;
- sur un module DC-DC ;
- sur le ventilateur ;
- sur un servo ;
- sur une bande LED.

Si l'alimentation affiche 24V mais la charge affiche notablement moins, cherchez un affaissement sur les fils, les terminaux ou les connecteurs.

Pour le diagnostic de l'alimentation, il est important de mesurer sous charge, pas seulement au repos.

## Mesure de la tension AC

AC est tension alternative, comme 110-230V du secteur.

La tension secteur est dangereuse.

Si vous ne comprenez pas ce que vous faites, ne mesurez pas les parties ouvertes du secteur avec un multimètre. Préférez utiliser des modules sûrs prêts à l'emploi, des terminaux fermés et l'aide d'un spécialiste.

Si vous mesurez, vous avez besoin de :

- un multimètre avec catégorie de sécurité **CAT II** ou **CAT III** — cela est écrit sur le boîtier de l'appareil à côté de la tension, par exemple `CAT II 600V`. CAT I n'est pas adapté au secteur domestique. CAT III et CAT IV offrent une marge supplémentaire pour les installations plus complexes ;
- des sondes en bon état de fonctionnement avec une catégorie pas inférieure au multimètre ;
- les mains sèches ;
- un assemblage fermé et stable ;
- compréhension de où se trouvent la phase et le neutre ;
- aucun point de contact accidentellement ouvert.

Pour la plupart des tâches impliquant l'électronique basse tension, les mesures DC sont suffisantes.

## Vérification de la continuité

La continuité montre si deux points sont électriquement connectés.

Il est utile de vérifier :

- si un fil est intact ;
- si `GND` est connecté ;
- si un câble n'est pas cassé ;
- si un bouton fonctionne ;
- si un fusible est intact ;
- si les contacts voisins sont court-circuités.

Procédure :

1. Éteignez l'alimentation.
2. Réglez le multimètre en mode continuité : généralement une icône de son ou un symbole de diode.
3. Touchez les sondes l'une contre l'autre - il devrait y avoir un bip.
4. Touchez les deux points que vous voulez vérifier.
5. Si cela bipe, il y a une connexion conductrice entre les points.

La vérification de la continuité est effectuée sur un circuit hors tension.

## Résistance

La résistance se mesure en ohms.

Pour nos tâches, c'est nécessaire pour :

- vérifier une thermistance ;
- vérifier les fils cassés ;
- vérifier un fusible ;
- déterminer s'il y a un court-circuit ;
- vérifier une résistance.

Important : la résistance n'est mesurée que sur un circuit hors tension.

Si vous mesurez la résistance sur une carte sous tension, vous pouvez obtenir des lectures incorrectes ou endommager le multimètre.

## Test d'une thermistance

Pour une thermistance NTC `100K` typique à température ambiante, attendez-vous à des dizaines ou environ `100 kOhm`.

Si le multimètre affiche :

- `OL` ou infini - probable circuit ouvert ;
- presque `0 Ohm` - probable court-circuit ;
- une valeur fluctuant beaucoup quand vous bougez le fil - mauvais contact ;
- la résistance diminue quand vous la chauffez avec vos doigts - ressemble à une NTC active.

Les valeurs exactes dépendent du type de thermistance et de la température.

## Mesure du courant

Mesurer le courant est plus dangereux que mesurer la tension.

La tension se mesure en parallèle : les sondes touchent deux points.

Le courant se mesure en série : vous devez briser le circuit et connecter le multimètre en ligne pour que le courant circule à travers l'appareil.

Erreur - mettre le multimètre en mode courant et toucher les sondes au plus et au moins de l'alimentation. C'est presque un court-circuit à travers le multimètre.

Pour un débutant, il est préférable de :

- d'abord calculer le courant à partir de la puissance ;
- utiliser des wattmètres prêts à l'emploi / compteur de puissance USB / compteur de puissance DC ;
- mesurer le courant uniquement si vous comprenez comment connecter le multimètre en série ;
- commencer par la bonne plage et le bon port.

## Vérification d'un fusible

Vérifiez le fusible sur un circuit hors tension.

Méthodes :

- continuité ;
- mesure de résistance.

Un bon fusible affiche généralement une continuité et a une très faible résistance.

Un fusible grillé n'affiche généralement pas de continuité.

Si un fusible a grillé, vous ne pouvez pas simplement installer un fusible de calibre plus élevé. Trouvez d'abord la cause.

## Comment ne pas griller le multimètre

Règles minimales :

- vérifiez le mode avant de mesurer ;
- vérifiez le port de la sonde rouge avant de mesurer ;
- ne mesurez pas la résistance sur un circuit sous tension ;
- ne mesurez pas le courant comme la tension ;
- n'allez pas dans 110-230V AC sans comprendre la sécurité ;
- commencez par une plage plus élevée si le multimètre n'est pas auto-gamme ;
- utilisez des sondes en bon état de fonctionnement ;
- ne touchez pas les pointes en métal avec vos doigts.

## Scénarios pratiques

Vérifiez une alimentation 24V :

1. Mode tension DC.
2. Sonde noire sur négatif.
3. Sonde rouge sur positif.
4. Devrait afficher environ 24V.

Vérifiez un ventilateur :

1. Mesurez la tension sur le connecteur du ventilateur.
2. Vérifiez la polarité.
3. Vérifiez la tension au démarrage.

Vérifiez un fil cassé :

1. Débranchez l'alimentation.
2. Mode continuité.
3. Sondes aux deux extrémités du fil.
4. Pas de bip - probable circuit ouvert.

Vérifiez un court-circuit entre `+` et `GND` :

1. Débranchez l'alimentation.
2. Vérifiez la continuité entre `+` et `GND`.
3. S'il bipe où il ne devrait pas, cherchez un court-circuit.

## Les éléments essentiels

- Pour la tension DC, utilisez le mode `V` avec une ligne droite.
- La résistance et la continuité ne sont effectuées que sur les circuits hors tension.
- Le courant se mesure en série, pas en parallèle.
- Après mesure du courant, déplacez la sonde de `A` vers le port normal `V/Ohm`.
- La tension secteur est dangereuse ; ne mesurez pas les parties ouvertes 110-230V sans comprendre la sécurité.
- Un multimètre sous charge révèle souvent des problèmes invisibles au repos.

## Matériaux de référence

- [SparkFun: How to Use a Multimeter](https://learn.sparkfun.com/tutorials/how-to-use-a-multimeter/all) - guide pratique de tension, courant, résistance, continuité et ports multimètre.
- [Fluke: How to Measure Resistance](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-resistance) - mesure sûre de la résistance.
- [Fluke: How to Measure AC Voltage](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-ac-voltage) - mesure de la tension AC et ordre de connexion des sondes.
- [Fluke: How to Test for Continuity](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-test-for-continuity) - vérification de continuité et recherche de circuit ouvert.
- [Fluke: Choosing the correct fuse for your tester](https://www.fluke.com/en-us/learn/blog/digital-multimeters/choosing-the-correct-fuse-for-your-tester) - pourquoi les ports d'entrée de courant ont besoin de fusibles appropriés avec calibre de tension et de rupture corrects.
