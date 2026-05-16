# Matériaux résistants à la chaleur

Pour les pièces près de la chaleur, ce qui compte n'est pas l'étiquette « résistant à la chaleur » mais le comportement réel du matériau dans votre conception spécifique.

Une pièce peut ne pas fondre, mais elle peut déjà :

- se ramollir ;
- se plier ;
- se déformer sous une vis ;
- changer de taille ;
- perdre la rigidité ;
- desserrer les fixations ;
- décaler un capteur ;
- bloquer le flux d'air.

Par conséquent, la « température de fusion » n'est presque jamais le paramètre principal pour un boîtier, un support ou un conduit d'air.

## Ce qui compte comme une zone chaude

Une zone chaude n'est pas seulement l'endroit où s'assoit le chauffage.

Dans un appareil fait maison, les zones chaudes peuvent inclure :

- le flux d'air après le chauffage ;
- la paroi près du chauffage ;
- le point de montage du thermisteur ;
- le conduit d'air ;
- la zone au-dessus de l'alimentation électrique ;
- la zone près d'un SSR ou MOSFET avec dissipateur thermique ;
- la chambre fermée qui se réchauffe entièrement.

Si une pièce se trouve dans une telle zone, le matériau est choisi avec une marge et testé dans un assemblage réel.

## Température de travail, pas de fusion

La fusion est déjà un stade avancé du problème.

Pour une pièce imprimée, ce qui est plus important :

- à quelle température elle perd la rigidité ;
- s'il y a une charge ;
- combien d'heures elle fonctionnera ;
- y a-t-il un flux d'air chaud ;
- y a-t-il une vibration ;
- tient-elle une vis ou un clip ;
- que se passe-t-il si elle se déforme.

Un porte-capteur peut devenir dangereux même avant une défaillance visible. Si le capteur s'éloigne de la surface, le contrôleur peut continuer à chauffer car il lit la mauvaise température.

## Options de base

Une hiérarchie approximative des matériaux :

- PLA - pour les prototypes froids et les pièces décoratives loin de la chaleur.
- PETG - option de base pour les températures modérées et les pièces fonctionnelles simples.
- ABS/ASA - mieux pour les zones plus chaudes et les pièces mécaniquement chargées, si vous avez les bonnes conditions d'impression.
- PA/nylon - matériau technique résistant, mais fortement dépendant de l'humidité et des conditions d'impression.
- PC/polycarbonate - matériau plus résistant à la chaleur et plus robuste, mais difficile à imprimer.
- Composites avec charge de carbone ou de fibre de verre - peuvent être plus rigides et stables, mais nécessitent une buse appropriée et une compréhension des propriétés.
- Métal, fibre de verre, céramique ou pièces prêtes à l'emploi résistantes à la chaleur - où le plastique n'est plus approprié.

Ce n'est pas un classement « mieux-pire ». C'est une liste d'options avec une complexité, un coût et des risques différents.

## PETG

Le PETG fonctionne pour de nombreuses pièces dans une zone à température modérée :

- les capots électroniques ;
- les supports de ventilateurs ;
- les porte-capteurs de température loin du chauffage ;
- les conduits d'air pour un flux d'air modéré ;
- les éléments de boîtier ne portant pas une sécurité critique.

Mais le PETG peut se ramollir et se déformer sous charge. Si une pièce tient un chauffage, un terminal d'alimentation ou un capteur de sécurité, le PETG doit être utilisé très soigneusement.

## ABS et ASA

L'ABS et l'ASA fonctionnent généralement mieux dans les zones plus chaudes que le PETG.

Ils sont considérés pour :

- l'enclosure de chambre ;
- les conduits d'air ;
- les supports dans un environnement chaud ;
- les pièces techniques ;
- les pièces qui doivent conserver leur forme plus longtemps.

Mais ils ont un prix :

- plus difficiles à imprimer ;
- déformation ;
- odeur ;
- fumées potentiellement nocives ;
- de préférence imprimés dans une chambre fermée ;
- nécessite une ventilation.

L'ASA est souvent préféré pour les pièces où la résistance aux UV et la durabilité comptent. L'ABS peut être moins coûteux et plus disponible.

## PA / Nylon

Le PA, ou nylon, est utilisé pour les pièces techniques soumises à une charge mécanique.

Avantages :

- ténacité d'impact élevée ;
- bonne résistance à l'usure ;
- faible friction ;
- bonne ténacité mécanique ;
- certaines variantes ont une bonne résistance à la température.

Inconvénients :

- absorbe fortement l'humidité ;
- nécessite un séchage ;
- peut se déformer ;
- difficile à imprimer ;
- nécessite une surface correcte et des conditions appropriées.

Le nylon humide s'imprime mal : des bulles, un sifflement, une mauvaise surface et une faible résistance en résultent. Pour un simple capot de boîtier, le nylon est généralement excessif.

## PC / Polycarbonate

Le polycarbonate est considéré quand vous avez besoin d'une résistance élevée et d'une résistance à la température.

Avantages :

- résistance à l'impact élevée ;
- résistance à la température élevée ;
- bonne rigidité ;
- adapté aux pièces fonctionnelles.

Inconvénients :

- difficile à imprimer ;
- température élevée de la buse et du plateau ;
- sujet à la déformation ;
- a besoin d'un environnement chaud stable ;
- pas toutes les imprimantes conviennent.

Le PC n'est pas un matériau « débutant ». Si l'impression est instable, une pièce peut avoir l'air normale mais avoir une mauvaise résistance entre les couches.

## Composites

Les filaments composites contiennent des charges : fibre de carbone, fibre de verre, Kevlar ou autre matériau.

Ils peuvent fournir :

- une plus grande rigidité ;
- moins de déformation ;
- une meilleure stabilité dimensionnelle ;
- une belle surface technique.

Mais ils ne rendent pas le plastique de base magiquement non inflammable ou entièrement résistant à la chaleur.

Important :

- la charge de carbone use les buses en laiton ;
- une buse durcie ou appropriée est nécessaire ;
- le composite peut être plus fragile ;
- les propriétés dépendent du matériau spécifique, pas juste des lettres « CF » dans le nom.

## Quand le plastique ne fonctionne pas

Pour certains endroits, le matériau approprié n'est pas du plastique imprimé.

Mieux à considérer métal, fibre de verre, céramique ou pièces industrielles prêtes à l'emploi pour :

- le support du chauffage ;
- la zone de chaleur directe ;
- le contact avec le terminal d'alimentation ;
- le montage du fil secteur ;
- la barrière mécanique entre le courant alternatif 110-230V et l'utilisateur ;
- l'endroit où la déformation de la pièce pourrait mener à un incendie ou un choc électrique.

Une pièce imprimée peut maintenir la forme du boîtier, mais ne doit pas être la seule protection contre une défaillance dangereuse.

## Comment choisir le matériau

Avant de choisir un matériau, répondez :

1. Quelle est la température maximale au lieu d'installation ?
2. Combien de temps la pièce fonctionnera-t-elle à cette température ?
3. Y a-t-il une charge mécanique ?
4. Y a-t-il des vis, des clips ou une compression constante ?
5. Y a-t-il un chauffage, un SSR, un MOSFET, une alimentation électrique ou du courant alternatif 110-230V à proximité ?
6. Que se passe-t-il si la pièce se déforme ?
7. Pouvez-vous remplacer le plastique par du métal ou un support prêt à l'emploi ?

Si la conséquence d'une défaillance est grave, vous ne voulez pas « le plastique le plus pratique » mais une conception avec marge et une protection indépendante.

## Erreurs courantes

- regarder seulement la température de fusion ;
- penser que le PETG est sûr à côté de n'importe quel chauffage ;
- utiliser le PLA dans une chambre fermée chaude ;
- imprimer du PC/nylon sans une imprimante appropriée et obtenir une pièce faible ;
- choisir un composite seulement pour le marquage cool « CF » ;
- placer une pièce en plastique juste à côté d'un terminal d'alimentation ;
- ne pas vérifier la pièce après un chauffage prolongé ;
- oublier la charge de vis et la déformation du matériau ;
- ne pas tenir compte du fait qu'un boîtier fermé se réchauffe entièrement.

## Points clés

- La température de travail est plus importante que la température de fusion.
- Une pièce peut devenir dangereuse avant une fusion visible.
- Le PETG est une option de base pour une zone modérée, pas une protection thermique universelle.
- L'ABS/ASA gère mieux la chaleur mais nécessite les bonnes conditions d'impression et une ventilation.
- Le nylon et le PC sont des matériaux techniques pour les utilisateurs expérimentés et un équipement approprié.
- Dans les endroits chauds et soumis à des charges, le métal ou un support prêt à l'emploi est souvent mieux.

## Références

- [Base de connaissances Prusa : Guide des matériaux](https://help.prusa3d.com/category/material-guide_220) - catalogue Prusa complet des matériaux avec PLA, PETG, ABS, ASA, PC, Nylon et composites.
- [Base de connaissances Prusa : Polycarbonate](https://help.prusa3d.com/article/polycarbonate-pc_165812) - propriétés du PC, résistance à la température élevée et difficulté d'impression.
- [Base de connaissances Prusa : Polyamide / Nylon](https://help.prusa3d.com/article/polyamide-nylon_167188) - nylon comme matériau technique, absorption d'humidité, séchage et exigences d'impression.
- [Bambu Lab : Guide de comparaison des filaments pour imprimante 3D](https://bambulab.com/en-us/filament-guide) - comparaison des matériaux par résistance à la chaleur, résistance, absorption d'humidité et besoins de séchage.
- [Base de connaissances Prusa : Poteau de guide du boîtier](https://cdn.help.prusa3d.com/article/enclosure-guidepost_366332) - pourquoi une chambre fermée est importante pour les matériaux qui se déforment lors du refroidissement.
