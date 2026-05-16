# Conception de boîtier

Un boîtier d'appareil n'est pas juste une boîte autour des composants.

Il doit maintenir en toute sécurité :

- le chauffage ;
- le ventilateur ;
- les capteurs ;
- l'alimentation électrique ;
- le contrôleur ;
- les bornes ;
- les fils ;
- les connecteurs ;
- l'affichage ou les boutons ;
- les pièces mécaniques.

Pour un appareil chauffé, un mauvais boîtier peut créer un problème même avec une bonne électronique : bloquer le flux d'air, surchauffer le contrôleur, abraser un fil ou rapprocher le plastique trop près d'une pièce chaude.

## Commencez par la disposition des composants

Avant de modéliser le boîtier, disposez les composants réels :

- carte de contrôleur ;
- alimentation électrique ou convertisseur CC-CC ;
- ventilateur ;
- chauffage ;
- capteur de température ;
- bornes ;
- fusible ;
- fils ;
- connecteurs ;
- boutons, affichage, RFID ou autres modules.

Le boîtier est conçu autour des dimensions réelles de la pièce, pas « à peu près cette taille ».

Vérifiez :

- où les connecteurs sont situés ;
- où l'USB sort ;
- où le bouton de réinitialisation est enfoncé ;
- comment le capot sortira ;
- comment le ventilateur sera remplacé ;
- où le fil d'alimentation s'exécutera ;
- comment la carte sera montée.

## Séparez les zones

Dans un appareil chauffé, il est utile de penser par zones :

- zone chaude ;
- zone électronique ;
- zone de câblage d'alimentation ;
- zone utilisateur ;
- zone de service.

La zone chaude est le chauffage, le flux d'air chaud, le capteur de température et les pièces à proximité.

La zone électronique est le contrôleur, l'affichage, les capteurs de faible tension, les fils logiques.

La zone de câblage d'alimentation est l'alimentation électrique, le SSR, le MOSFET, les bornes, les fusibles, l'entrée secteur si présente.

La zone utilisateur est tout ce qui est touché par les mains : boutons, poignées, capots, affichage, emplacement du lecteur RFID.

Ces zones ne doivent pas se croiser au hasard.

## Ne placez pas l'électronique juste à côté du chauffage

Le contrôleur, l'affichage, le CC-CC et les fils n'aiment pas la surchauffe.

Laissez :

- une distance du chauffage ;
- un écart d'air ;
- un écran ou une partition si nécessaire ;
- une ventilation pour l'électronique ;
- l'accès pour vérifier la température après l'assemblage.

Si l'électronique s'assoit dans une poche fermée sans ventilation, elle peut surchauffer même sans contact direct avec le chauffage.

## L'air doit circuler où il est nécessaire

Un ventilateur seul ne garantit pas le flux d'air.

Le boîtier doit diriger l'air :

- à travers le chauffage ;
- à travers la bobine ou la zone de travail ;
- à travers un filtre si présent ;
- passé le capteur au bon point ;
- dehors ou en boucle comme prévu.

Un mauvais design peut aboutir à un ventilateur sympa et un flux utile presque zéro. L'air suivra le chemin de la moindre résistance, à travers les écarts, autour des filtres ou passé le chauffage.

Pour les conduits d'air, évitez :

- rétrécissement aigu ;
- virages inutiles ;
- les canaux longs et minces ;
- les grilles avec une petite surface ouverte ;
- les filtres sans un ventilateur avec une pression statique suffisante.

## Faites des montages pour les vraies vis

Ne comptez pas sur une vis auto-taraudeuse dans un poteau mince pendant longtemps.

Pour un boîtier qui sera démonté, mieux utiliser :

- des inserts thermiques en laiton ;
- des écrous dans les poches ;
- des entretoises de carte appropriées ;
- des vis de taille standard ;
- des rondelles où le plastique peut s'enfoncer.

Pour les entretoises imprimées, important :

- un diamètre adéquat ;
- une base arrondie ;
- pas de parois minces ;
- l'orientation correcte de l'impression ;
- l'espace du matériau autour du trou.

Si le capot s'ouvre souvent, les filets en plastique nus s'usent rapidement.

## Les fils ne doivent pas s'abraser

Les fils dans le boîtier doivent être sécurisés.

Vous avez besoin :

- des canaux de câble ;
- des espaces pour les attaches ;
- le soulagement de contrainte à l'entrée du câble ;
- les rayons au lieu des arêtes vives ;
- l'espace libre du ventilateur ;
- l'espace libre du chauffage ;
- la protection contre le pincement par le capot.

Un mauvais scénario : l'utilisateur tire un câble externe et la force va directement à une borne ou une broche de carte.

Mieux vaut que le câble soit d'abord fixé par le boîtier, puis atteigne le connecteur ou la borne.

## Ne mélangez pas le secteur avec la basse tension

Si l'appareil a du courant alternatif 110-230V, le boîtier doit être conçu beaucoup plus strictement.

Logique minimale :

- entrée secteur séparée ;
- fusible accessible mais protégé ;
- bornes secteur couvertes ;
- fils basse tension non mélangés avec fils secteur ;
- l'utilisateur ne peut pas toucher la partie secteur ;
- le fil ne peut pas sortir du terminal sous tension ;
- le plastique ne touche pas les terminaux chauds et les composants d'alimentation ;
- la mise à la terre est présente si nécessaire.

N'inventez pas la sécurité secteur « par image ». Pour la partie secteur, vous avez besoin des bonnes bornes, l'isolation, le soulagement de contrainte, les fusibles et la compréhension des exigences de sécurité.

## Laissez l'accès pour le service

L'appareil aura besoin de maintenance.

Laissez l'accès à :

- le fusible ;
- les bornes ;
- le contrôleur ;
- le connecteur USB ou de service ;
- le capteur de température ;
- le ventilateur ;
- le filtre ;
- le chauffage ;
- les vis de montage.

Si le remplacement d'un ventilateur nécessite le dessoudage de fils ou le retrait du chauffage, la conception ne sera pas bien entretenue.

## Vérifiez à température réelle

Après l'assemblage, vous devez faire plus que vérifier que tout s'adapte.

Vérifiez :

- la température de l'électronique après une opération prolongée ;
- la température de la paroi près du chauffage ;
- le plastique se ramollit-il ;
- le conduit d'air se déforme-t-il ;
- les terminaux deviennent-ils chauds ;
- les écarts aux pièces chaudes ont-ils changé ;
- le plastique sent-il ;
- les fils touchent-ils les surfaces chaudes.

Le premier test est mieux fait sous supervision avec la capacité à couper l'alimentation rapidement.

## Liste de contrôle avant d'imprimer le boîtier

Avant d'imprimer, vérifiez :

1. Tous les composants réels sont mesurés.
2. Il y a du dégagement autour des cartes, connecteurs et câbles.
3. La zone chaude est séparée de l'électronique.
4. Le flux d'air a un chemin clair.
5. Le ventilateur peut être remplacé.
6. Le filtre peut être remplacé.
7. Le capteur de température peut être vérié et réinstallé.
8. Les fils ne passent pas par les arêtes vives.
9. Il y a des endroits pour les attaches ou les clips.
10. Les fils secteur sont séparés de la basse tension.
11. Le capot ne pince pas les câbles.
12. Les vis et les inserts ont assez de plastique autour d'eux.
13. Le matériau convient à la température de travail.
14. La déformation de la pièce ne rend pas l'appareil dangereux.

## Erreurs courantes

- concevoir une jolie boîte d'abord, puis essayer d'adapter les fils ;
- ne pas laisser d'espace pour les connecteurs ;
- bloquer la ventilation de l'alimentation électrique ;
- mettre le contrôleur dans un coin chaud ;
- exécuter les fils secteur et signal ensemble ;
- ne pas fournir le soulagement de contrainte du câble ;
- utiliser des entretoises minces pour les vis ;
- oublier que les filtres et ventilateurs nécessitent la maintenance ;
- imprimer le boîtier en PLA pour une zone chaude ;
- ne pas vérifier le boîtier après un chauffage prolongé.

## Points clés

- Le boîtier est conçu autour des composants réels et des fils.
- La zone chaude, l'électronique, le câblage d'alimentation et la zone utilisateur doivent être séparés.
- L'air doit circuler le long d'un chemin utile, pas juste « quelque part de soufflant ».
- Les fils doivent être sécurisés et protégés des arêtes vives, de la chaleur et de la tension.
- Le secteur ne peut pas être mélangé avec la logique basse tension.
- La maintenance doit être planifiée avant l'impression, pas après l'assemblage.

## Références

- [Protolabs Network : Conception de boîtier pour l'impression 3D](https://www.hubs.com/knowledge-base/enclosure-design-3d-printing-step-step-guide/) - règles pratiques pour les parois, les écarts, les bossages, les nervures et les supports.
- [Base de connaissances Prusa : Poteau de guide du boîtier](https://help.prusa3d.com/article/enclosure-guidepost_366332) - pourquoi le boîtier affecte la température, la poussière, l'odeur, l'accès aux pièces chaudes et le placement de l'alimentation en dehors de la chambre chaude.
- [FRC Design : Design for 3D Printing](https://www.frcdesign.org/design-handbook/structure/design-for-3d-printing/) - conseils pour les boîtiers électroniques, l'accès aux ports, la ventilation et les inserts thermiques.
- [3D On Demand : Guide des boîtiers imprimés en 3D](https://www.3d-demand.com/blog/3d-printed-enclosures-electronics-guide) - la conception autour des composants internes, l'épaisseur de paroi, les clips et la dissipation thermique.
- [3DSearch : Boîtiers électroniques personnalisés](https://www.3dsearch.app/blog/3d-printing-electronics-enclosures) - ventilation, entretoises de carte, inserts filetés, écarts et dimensions pratiques pour FDM.
