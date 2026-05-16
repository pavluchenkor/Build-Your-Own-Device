# Pourquoi le PLA est risqué

Le PLA est un excellent matériau pour commencer.

Il s'imprime facilement, est peu coûteux, produit des pièces soignées et est bien adapté aux prototypes. Beaucoup de premiers boîtiers, capots et supports sont imprimés en PLA.

Le problème commence quand le PLA est placé près de la chaleur et traité comme un matériau de travail complet.

## Le PLA n'a pas besoin de fondre pour devenir dangereux

L'erreur principale est de regarder la température de fusion.

Le PLA peut commencer à perdre sa rigidité bien avant de fondre.

Pour une pièce fonctionnelle, dangereux n'est pas seulement « il a fondu ». Dangereux est quand la pièce :

- se ramollit ;
- se déforme sous une vis ;
- perd sa forme ;
- libère un clip ;
- décale un capteur ;
- bloque un conduit d'air ;
- réduit l'écart avec une pièce chaude ;
- permet à un fil de toucher une zone chauffée.

Extérieurement, cela peut ressembler à une déformation mineure. Mais pour un appareil chauffé, un petit changement peut causer une lecture de température incorrecte ou un mauvais flux d'air.

## Où le PLA est particulièrement risqué

Le PLA ne doit mieux pas être utilisé pour :

- le support du chauffage ;
- le porte-capteur de température sur une pièce chaude ;
- le conduit d'air juste après le chauffage ;
- la pièce à l'intérieur d'une chambre chaude ;
- le support de terminal d'alimentation ;
- la pièce près d'un SSR, MOSFET ou dissipateur thermique ;
- la pièce sous charge constante dans la chaleur ;
- le boîtier où le courant alternatif 110-230V circule à proximité.

Même si la pièce ne touche pas le chauffage, elle peut s'asseoir dans l'air chaud pendant de longues périodes. Dans un boîtier fermé, la température augmente non seulement près du chauffage mais partout.

## Scénarios dangereux

Problèmes typiques :

- le support du chauffage s'est ramolli ;
- le porte-capteur s'est déplacé et la température lit mal ;
- le conduit d'air s'est déformé et le flux à travers le chauffage a diminué ;
- le capot électronique s'est déformé et a bloqué la ventilation ;
- la vis a écrasé le plastique après plusieurs heures de chauffage ;
- le fil a commencé à toucher une pièce chaude ;
- l'écart entre le plastique et la borne s'est réduit ;
- le boîtier a perdu sa forme mais l'appareil a continué à chauffer.

C'est pourquoi « il a imprimé joliment » ne signifie pas « fonctionnera en toute sécurité ».

## Où le PLA peut être utilisé

Le PLA n'est pas un mauvais matériau. Il a juste besoin d'être utilisé où il appartient.

Le PLA convient à :

- les prototypes froids ;
- les pièces d'ajustement ;
- les modèles ;
- les capots décoratifs loin de la chaleur ;
- les poignées et les coussinets dans les zones fraîches ;
- les pièces temporaires pour la vérification de la forme ;
- les modèles qui ne supportent pas la sécurité de l'appareil.

Le PLA est utile au début : vérifiez rapidement les dimensions, l'ajustement de la carte, la forme du capot, le placement des boutons ou la direction du conduit d'air. Mais après vérification, une pièce de travail près de la chaleur doit souvent être réimprimée dans un autre matériau ou remplacée par une pièce non imprimée.

## Le boîtier fermé aggrave la situation

Dans une pièce ouverte, une pièce en PLA peut sembler stable.

Dans un séchoir fermé ou une chambre d'imprimante, les conditions sont différentes :

- l'air se réchauffe ;
- le plastique reste dans la chaleur pendant longtemps ;
- un chauffage fonctionne à proximité ;
- le flux d'air peut ne pas refroidir la pièce ;
- il peut y avoir une alimentation électrique ou un module d'alimentation à l'intérieur ;
- la charge agit pendant des heures.

Par conséquent, vérifier « j'ai touché la pièce avec ma main, semble aller » n'est pas suffisant.

Vous devez vérifier l'appareil en fonctionnement réel : avec chauffage, ventilateur, boîtier et runtime similaire à l'utilisation réelle.

## PLA sous charge

Le PLA est rigide, mais cela ne signifie pas qu'il supporte bien la charge constante dans la chaleur.

Mauvaises places pour le PLA :

- les entretoises sous les vis ;
- les clips ;
- les charnières ;
- les supports de bobine ;
- les supports minces ;
- les pièces comprimées par une vis ;
- les pièces maintenant un ressort ou un levier.

Si une pièce en PLA est chauffée et chargée constamment, elle peut progressivement changer de forme. C'est appelé fluage du matériau.

Pour un boîtier, c'est particulièrement désagréable : aujourd'hui tout est assemblé correctement, mais après plusieurs cycles de chauffage l'écart est différent.

## Quoi utiliser au lieu du PLA

Selon la tâche, considérez :

- PETG - pour les zones modérément chaudes et les pièces fonctionnelles simples ;
- ABS ou ASA - pour les zones plus chaudes et les pièces techniques ;
- PC ou PA/nylon - pour les utilisateurs expérimentés et les conditions plus exigeantes ;
- métal, fibre de verre, céramique ou supports prêts à l'emploi - près du chauffage et de la section d'alimentation.

Si la question est support de chauffage, protection thermique, bornes secteur ou capteur critique, ne choisissez pas le matériau à partir d'une liste de filaments seule. Parfois, la bonne réponse n'est pas d'imprimer cette pièce en plastique du tout.

## Comment utiliser le PLA plus en toute sécurité

Si le PLA est utilisé malgré tout :

- gardez-le dans la zone froide ;
- ne le placez pas près du chauffage ;
- ne l'utilisez pas comme support de pièce d'alimentation ;
- ne le chargez pas avec une vis sans marge ;
- ne faites pas du PLA le seul élément de sécurité ;
- vérifiez après le chauffage prolongé ;
- gardez l'écart aux pièces chaudes ;
- faites un prototype, pas la dernière pièce chaude.

Pour les tests précoces, vous pouvez imprimer une pièce en PLA, assembler l'appareil sans chauffage ou à puissance réduite, vérifier la forme, l'ajustement et l'accès. Après cela, la pièce de travail doit être réimprimée dans un matériau approprié.

## Erreurs courantes

- ignorer le ramollissement du PLA et regarder seulement la température de fusion ;
- imprimer le support du chauffage en PLA ;
- placer le conduit d'air en PLA juste après le chauffage ;
- monter le thermisteur avec du PLA dans une zone chaude ;
- utiliser le PLA dans une chambre fermée chaude ;
- penser « si elle ne fond pas en 5 minutes, elle est sûre » ;
- ne pas vérifier la déformation après plusieurs heures d'opération ;
- laisser le PLA sous une vis et charge dans la chaleur ;
- ne pas réimprimer le prototype dans un matériau de travail.

## Points clés

- Le PLA est pratique pour les prototypes mais mauvais pour les zones chaudes.
- Une pièce peut devenir dangereuse bien avant la fusion.
- Le risque principal est la perte de forme, de rigidité et d'écarts.
- Le PLA peut être utilisé loin de la chaleur et de la section d'alimentation.
- Pour les pièces de travail près de la chaleur, considérez le PETG, l'ABS/ASA ou la solution non en plastique.
- Si l'échec d'une pièce en PLA peut affecter la sécurité, le matériau est mal choisi.

## Références

- [Base de connaissances Prusa : PLA](https://help.prusa3d.com/article/pla_2062) - PLA comme matériau simple pour les prototypes et les pièces sans charge mécanique, chimique ou thermique élevée.
- [Page produit Prusa PLA](https://www.prusa3d.com/en/product/pla-filament/) - avertissement pratique sur la faible résistance à la température et la perte de résistance à des températures supérieures à environ 60°C.
- [Bambu Lab : Guide du filament PLA](https://bambulab.com/en-us/filament/pla) - PLA comme matériau débutant pour les pièces décoratives et les modèles, mais pas pour les températures élevées et les applications exigeantes.
- [Bambu Lab : Guide de comparaison des filaments pour imprimante 3D](https://bambulab.com/en-us/filament-guide) - comparaison de la résistance à la chaleur et d'autres propriétés du PLA, PETG, ABS, ASA, PC et matériaux techniques.
- [Filwiz : Résistance à la chaleur du PLA expliquée](https://filwiz.com/guides/pla-heat-resistance-glass-transition-vs-melting-point) - explication de la différence entre température de fusion, transition vitrifiée et tolérance à la chaleur pratique du PLA.
