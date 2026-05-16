# PETG, ABS et ASA

Le PETG, l'ABS et l'ASA sont souvent considérés comme les matériaux suivants après le PLA, quand une pièce doit être non seulement jolie mais fonctionnelle.

Dans les appareils autour d'un séchoir, d'une chambre d'imprimante ou d'un chauffage, le choix du matériau affecte la sécurité. Une pièce peut avoir l'air normale après l'impression, mais après une heure dans un boîtier chaud, elle peut commencer à se ramollir, déformer le conduit d'air, desserrer les fixations ou décaler un capteur.

## PETG

Le PETG est souvent un bon premier matériau de travail après le PLA.

Il offre généralement :

- une impression plus facile que l'ABS et l'ASA ;
- moins d'odeur lors de l'impression ;
- moins de déformation ;
- une meilleure résistance à la température que le PLA ;
- un fonctionnement fiable pour de nombreux supports, capots, porte-pièces et conduits d'air dans des conditions modérées.

Pour les appareils semblables à iDryer, le PETG peut bien fonctionner pour :

- le support du ventilateur loin du chauffage ;
- le capot électronique ;
- le porte-capteur dans une zone à température modérée ;
- le conduit d'air pour l'air pas trop chaud ;
- le boîtier de prototype.

Mais le PETG ne devient pas automatiquement résistant à la chaleur pour n'importe quelle zone chaude.

Si une pièce se trouve près d'un chauffage, dans un flux d'air chaud ou sous une charge constante, le PETG peut progressivement perdre sa rigidité et se déformer.

## ABS

L'ABS est un matériau plus technique que le PLA et le PETG.

Il fonctionne généralement mieux pour :

- les pièces soumises à une charge mécanique ;
- les boîtiers dans un environnement plus chaud ;
- les supports où le PETG est déjà douteux ;
- les pièces nécessitant une meilleure résistance à la température.

Inconvénients de l'ABS :

- déformation plus importante ;
- nécessite une chambre fermée ou un environnement chaud stable lors de l'impression ;
- odeur notable ;
- peut émettre des fumées nocives lors de l'impression ;
- ne convient pas pour imprimer dans un espace de vie sans ventilation.

Ne choisissez pas l'ABS juste parce que « c'est plus résistant ». Vous devez savoir comment l'imprimer. Un ABS mal imprimé avec délamination et contrainte interne peut s'avérer pire qu'un PETG bien imprimé.

## ASA

L'ASA est similaire à l'ABS en purpose, mais souvent mieux adapté aux pièces extérieures et techniques.

Avantages de l'ASA :

- bonne résistance à la température ;
- résistance aux UV ;
- moins d'odeur par rapport à l'ABS, mais l'odeur et les fumées sont toujours présentes ;
- déformation généralement moins importante que l'ABS ;
- adapté aux pièces techniques fonctionnelles.

Inconvénients :

- nécessite également de bonnes conditions d'impression ;
- pour les grandes pièces, une chambre d'impression fermée est préférable ;
- les fumées nocives sont possibles lors de l'impression ;
- le matériau est plus coûteux et exigeant que le PETG.

L'ASA est souvent plus judicieux que l'ABS pour les pièces qui vivront longtemps dans un appareil ou près de fenêtres/lumière du soleil. Mais pour un petit capot électronique interne, l'ASA n'est pas toujours nécessaire.

## Où utiliser quel matériau

Un guide approximatif :

| Tâche | PETG | ABS/ASA |
| --- | --- | --- |
| Prototype froid | fonctionne | fonctionne, mais souvent excessif |
| Capot électronique loin de la chaleur | fonctionne | fonctionne |
| Support de ventilateur dans une zone modérée | fonctionne | fonctionne |
| Conduit d'air près d'un flux d'air chaud | parfois | souvent mieux |
| Pièce à l'intérieur d'une chambre chaude | vérifiez la température | souvent plus judicieux |
| Support près du chauffage | risqué | nécessite aussi une vérification, parfois du métal est nécessaire |
| Pièce sous charge constante dans la chaleur | avec prudence | mieux, mais pas automatiquement sûr |
| Pièce près du courant alternatif 110-230V | le matériau n'est pas la seule réponse | le matériau n'est pas la seule réponse |

Ce n'est pas un tableau de permission. C'est juste une logique de départ.

La solution réelle dépend de la température, la distance au chauffage, le flux d'air, la charge, le temps de fonctionnement et les conséquences de l'échec.

## La température de fusion n'est pas le paramètre principal

Pour les boîtiers et les supports, ce qui compte n'est pas la température à laquelle le matériau fond.

Plus important est le moment où il :

- se ramolit ;
- se déforme sous la charge ;
- perd sa forme ;
- libère une vis ;
- se déforme ;
- change de taille.

Une pièce peut devenir dangereuse bien avant de fondre.

Par exemple, un porte-capteur peut se déplacer de quelques millimètres seulement. Extérieurement cela semble mineur, mais le contrôleur verra déjà la mauvaise température.

## L'impression d'ABS/ASA nécessite des conditions

L'ABS et l'ASA nécessitent souvent :

- une chambre fermée ;
- une température de plateau élevée ;
- une température stable autour de la pièce ;
- une bonne adhésion du plateau ;
- une protection contre les courants d'air ;
- une ventilation de la pièce ;
- un séchage soigneux du filament si nécessaire.

Si vous imprimez l'ABS/ASA sur une imprimante ouverte, une grande pièce peut se déformer, se fissurer ou se délaminier.

Pour les petites pièces, vous pouvez parfois vous passer d'une chambre fermée parfaite, mais pour un boîtier, un conduit d'air ou une longue pièce, prévoyez les bonnes conditions d'impression dès le départ.

## Ne choisissez pas le matériau séparément de la conception

Le matériau n'est qu'une partie de la solution.

Même un bon matériau ne sauvera pas une mauvaise géométrie :

- parois minces ;
- petits poteaux pour les vis ;
- coins internes aigus ;
- charge perpendiculaire aux couches ;
- mauvaise fixation au boîtier ;
- aucun écart avec les pièces chaudes ;
- ventilation bloquée.

Si une pièce maintient un chauffage, un connecteur d'alimentation ou un capteur de température, vous devez penser non seulement au plastique, mais aussi aux supports métalliques, aux écrans, aux écarts et à la protection de secours.

## Règle pratique

Pour un appareil simple, vous pouvez penser comme ceci :

- PLA - prototype, modèle, pièce décorative froide.
- PETG - minimum de base pour de nombreuses pièces fonctionnelles à température modérée.
- ABS/ASA - mieux pour les pièces plus chaudes et mécaniquement chargées, si vous pouvez les imprimer.
- Métal, fibre de verre, céramique ou pièces non inflammables prêtes à l'emploi - où le plastique près de la chaleur n'est plus approprié.

Si l'échec d'une pièce peut mener à une surchauffe, un court-circuit ou un contact entre un fil et une pièce chaude, le matériau doit être choisi avec une large marge de sécurité et testé dans un assemblage réel.

## Erreurs courantes

- penser que le PETG est entièrement résistant à la chaleur ;
- imprimer l'ABS/ASA sans une chambre fermée et obtenir une délamination ;
- choisir le matériau en fonction des conseils Internet sans connaître la température à l'intérieur du boîtier ;
- placer le conduit d'air PETG trop près du chauffage ;
- utiliser l'ABS/ASA dans un espace de vie sans ventilation ;
- penser que remplacer le PLA par l'ASA rend automatiquement la conception sûre ;
- ne pas vérifier la pièce après une heure de fonctionnement à température réelle ;
- oublier que les vis et la charge peuvent déformer le plastique au fil du temps.

## Points clés

- Le PETG est souvent un minimum acceptable pour les pièces fonctionnelles, mais pas pour n'importe quelle zone chaude.
- L'ABS et l'ASA gèrent mieux la température mais sont plus difficiles à imprimer et nécessitent une ventilation.
- L'ASA surpasse généralement l'ABS en résistance aux UV et sent souvent moins mauvais, mais nécessite toujours de la prudence.
- Le matériau est choisi en fonction de la température réelle, la charge et les conséquences de l'échec.
- Pour les pièces près d'un chauffage, la bonne réponse n'est parfois pas du plastique mais du métal ou un support prêt à l'emploi.

## Références

- [Base de connaissances Prusa : PETG](https://help.prusa3d.com/article/petg_2059) - description du PETG, impression, résistance, résistance à la température et limites.
- [Base de connaissances Prusa : ABS](https://cdn.help.prusa3d.com/article/abs_2058) - propriétés de l'ABS, exigences d'impression, déformation et avertissement de fumée.
- [Base de connaissances Prusa : ASA](https://help.prusa3d.com/article/asa_5078) - l'ASA comme matériau technique avec résistance à la température et aux UV, plus exigences de chambre fermée.
- [Bambu Lab : Guide de comparaison des filaments pour imprimante 3D](https://bambulab.com/en-us/filament-guide) - tableau comparatif des matériaux : PLA, PETG, ABS, ASA, PC, PA et composites.
- [Bambu Lab : Guide du filament ASA](https://bambulab.com/en-us/filament/asa) - brève description d'ASA, ses avantages, inconvénients et cas d'utilisation.
