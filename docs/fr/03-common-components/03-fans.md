# Ventilateurs

Un ventilateur est un moteur avec une roue qui déplace l'air. Dans les appareils autour d'une imprimante 3D, vous en avez besoin non seulement pour « souffler », mais pour pousser l'air à travers la bonne zone : un radiateur, une bobine, un filtre, un radiateur, une chambre ou un compartiment d'électronique.

Les ventilateurs de même taille peuvent fonctionner très différemment. L'un pousse bien l'air en espace ouvert, un autre pousse mieux l'air à travers un filtre ou un conduit, un troisième est plus silencieux mais plus faible sous la résistance.

## Où c'est utilisé

Dans les projets de type iDryer, les ventilateurs sont utilisés pour :

- circulation d'air à l'intérieur du sécheur ;
- transfert de chaleur du radiateur vers la chambre ;
- expulsion d'air de la chambre de l'imprimante ;
- filtrage par filtre HEPA/charbon ;
- refroidissement d'électronique ;
- refroidissement d'un radiateur ;
- nivellement de température à l'intérieur de l'enceinte.

Pour le chauffage de la chambre, un ventilateur est particulièrement important. Le radiateur libère de la chaleur, et le flux d'air supprime cette chaleur de l'élément et l'emporte plus loin. Sans un flux d'air approprié, le radiateur peut localement surchauffer tandis que la chambre se réchauffe mal.

## Flux d'air et pression statique

Dans la description technique d'un ventilateur, vous voyez généralement deux paramètres importants :

- flux d'air - souvent en `CFM` ou `m3/h` ;
- pression statique - souvent en `mmH2O`, `Pa` ou `inch H2O`.

Le flux d'air indique la quantité d'air qu'un ventilateur peut pomper dans des conditions idéales avec peu de résistance.

La pression statique indique la force avec laquelle un ventilateur peut pousser l'air à travers la résistance : un filtre, une grille, un radiateur, un conduit étroit ou un long tube d'air.

Règle pratique :

- pour la circulation ouverte, le flux d'air est plus important ;
- pour les filtres, les radiateurs, les grilles denses et les conduits, la pression statique est plus importante ;
- pour un vrai boîtier, le point de fonctionnement est important, pas seulement le nombre maximum dans les spécifications.

Si vous placez un ventilateur de boîtier silencieux sur un filtre dense, il pourrait à peine pousser l'air, même si le flux d'air semble fort en espace ouvert.

## Ventilateurs axiaux et radiaux

Un ventilateur axial pousse l'air le long de l'axe de rotation. Ce sont des ventilateurs carrés typiques `40x40`, `60x60`, `80x80`, `120x120 mm`.

Un ventilateur radial prend de l'air sur le côté et le souffle par une sortie étroite. Il fonctionne souvent mieux pour les conduits, les buses, les filtres et les endroits où vous avez besoin de pression.

Pour la circulation libre à l'intérieur d'une chambre, un ventilateur axial est généralement pratique. Pour un conduit compact, un filtre ou un flux dirigé, un ventilateur radial est parfois préférable.

## 2 broches, 3 broches et 4 broches

Les ventilateurs diffèrent souvent par le nombre de fils.

![Connecteur 3 broches sur un ventilateur informatique](../../../img/03-common-components/03-fan-3pin-connector.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Three-pin_connector_on_a_computer_fan.jpg), Dsimic, CC BY-SA 4.0*

2 broches :

- `+V` ;
- `GND`.

Un tel ventilateur reçoit simplement de l'énergie. Vous pouvez contrôler la vitesse en changeant la tension d'alimentation ou PWM sur la ligne d'alimentation si la carte et le ventilateur le supportent.

3 broches :

- `+V` ;
- `GND` ;
- signal tachométrique (`tach`/`sense`).

Le troisième fil génère généralement un signal de vitesse. Il ne contrôle pas la vitesse en lui-même.

4 broches PWM :

- `GND` ;
- `+V` ;
- signal tachométrique (`tach`/`sense`) ;
- signal de contrôle PWM.

Sur un ventilateur PWM 4 broches, l'alimentation est généralement constante et la vitesse est définie par une ligne PWM séparée. Ce n'est pas la même chose que de basculer rapidement l'alimentation du ventilateur entre marche et arrêt.

## PWM et tachomètre

PWM est un signal de contrôle qui définit la vitesse souhaitée. Les ventilateurs PWM informatiques typiques 4 broches ont généralement une fréquence autour de `25 kHz`, et l'alimentation reste constante.

Si le fil PWM n'est pas connecté, de nombreux ventilateurs 4 broches fonctionnent à pleine vitesse.

Le signal tachométrique indique le nombre de tours par minute. Il est nécessaire si l'appareil doit comprendre :

- si le ventilateur tourne ou s'arrête ;
- si la vitesse correspond à la commande ;
- si un filtre ou un conduit crée trop de résistance ;
- si le ventilateur est coincé.

Le tachomètre ne remplace pas le contrôle de température. Dans un appareil avec un radiateur, vous devez surveiller à la fois la température et l'état du flux d'air si l'arrêt du ventilateur est dangereux.

## Tension et courant

Avant de connecter, vérifiez :

- tension du ventilateur : `5V`, `12V`, `24V` ;
- courant de fonctionnement ;
- courant de démarrage ;
- type de connecteur ;
- pinout ;
- s'il a PWM ;
- s'il a un tachomètre ;
- température de fonctionnement ;
- direction du flux d'air ;
- niveau de bruit ;
- durée de vie et type de roulement.

Vous ne pouvez pas alimenter un ventilateur à partir du GPIO du contrôleur. GPIO est un signal, pas une sortie de puissance. Le courant du ventilateur doit provenir de l'alimentation, d'une sortie de puissance de carte ou d'un module MOSFET.

Au démarrage, un ventilateur peut brièvement tirer plus de courant qu'en fonctionnement normal. Si plusieurs ventilateurs sont connectés à une sortie, leurs courants s'additionnent.

## Bruit, vibration et roulement

Le bruit dépend de plus que le seul RPM.

Le son est affecté par :

- la forme de la pale ;
- l'équilibrage ;
- le type de roulement ;
- le montage ;
- la grille ;
- le conduit ;
- le filtre ;
- la résonance du boîtier ;
- plusieurs ventilateurs à proximité.

Les descriptions techniques listent le bruit en `dB(A)`, mais dans un vrai boîtier, le ventilateur peut sonner différemment. Une grille avec une mauvaise géométrie, un mur à proximité ou un montage raide sur un panneau fin peut rendre un bon ventilateur bruyant.

Pour un appareil qui fonctionne pendant des heures, il est préférable de choisir un ventilateur non seulement par le prix et la taille, mais aussi par la durée de vie, le roulement et la température.

## Température et localisation d'installation

Un ventilateur qui fonctionne bien sur un établi peut se dégrader rapidement dans une chambre chaude.

Vérifiez :

- température de fonctionnement du ventilateur ;
- température de l'air près du radiateur ;
- distance de l'élément de chauffage ;
- si un flux chaud frappe directement le moteur ;
- si le montage ramollit ;
- si les fils se dessèchent ;
- si le ventilateur s'encrase de poussière ou de fibres.

Si le ventilateur est responsable du flux d'air du radiateur, son défaillance doit être considérée dans la logique de sécurité. Vous ne pouvez pas concevoir un radiateur de sorte qu'un ventilateur arrêté crée immédiatement une température dangereuse sans arrêt d'urgence.

## Filtres et conduits

Un filtre, une grille et un conduit peuvent réduire considérablement le flux d'air utile.

Signes typiques :

- le ventilateur est fort mais le flux d'air est faible ;
- le filtre n'obtient à peine de l'air ;
- l'air contourne le filtre par les lacunes ;
- la température près du radiateur augmente plus vite que la température de la chambre ;
- après le montage du couvercle, le flux d'air est pire que sur l'établi.

Pour filtrer une chambre efficacement, vous devez non seulement mettre un ventilateur, mais assurer un chemin d'air à travers le filtre. Si l'air trouve plus facile de passer par une lacune, il le fera.

## Quoi vérifier avant d'acheter

Avant d'acheter un ventilateur, vérifiez :

- taille et épaisseur ;
- tension ;
- courant ;
- type : axial ou radial ;
- flux d'air ;
- pression statique ;
- bruit ;
- RPM ;
- type de roulement ;
- 2 broches/3 broches/4 broches ;
- température de fonctionnement ;
- durée de vie ;
- direction du flux d'air ;
- connecteur et pinout ;
- s'il convient à un filtre, un conduit ou une circulation libre.

Pour un filtre et un conduit étroit, ne choisissez pas un ventilateur uniquement par CFM. Regardez la pression statique et testez dans un assemblage réel.

## Erreurs typiques

- connecté un ventilateur 12V à 24V ;
- connecté un ventilateur 24V à 12V et cru qu'il était cassé ;
- alimentation du ventilateur à partir de GPIO ;
- n'a pas établi la masse commune pour MOSFET/PWM externe ;
- n'a pas tenu compte du courant de démarrage ;
- connecté plusieurs ventilateurs à une sortie faible ;
- sélectionné un ventilateur uniquement par la taille ;
- installé un ventilateur à flux libre sur un filtre dense ;
- pense que le fil tach est un fil de contrôle ;
- pense que le PWM 4 broches est la même chose que 2 broches ;
- contrôle un ventilateur PWM 4 broches en basculant l'alimentation ;
- installé un ventilateur dans une zone chaude sans vérifier la température ;
- n'a pas vérifié le flux d'air après l'installation du couvercle, du filtre et du conduit.

## Point principal

Un ventilateur est choisi pour la tâche : circulation libre, filtre, conduit, radiateur, refroidissement de radiateur ou d'électronique. Pour l'espace ouvert, le flux d'air est important ; pour les filtres et les conduits, la pression est importante.

Vérifiez la tension, le courant, le type de fil, PWM/tachomètre, la température de fonctionnement et la résistance réelle du système. Dans un appareil avec un radiateur, le ventilateur doit faire partie d'un système thermique sûr, pas d'un composant décoratif.

## Matériaux de référence

- [Noctua: Microcontroller guide for PWM and RPM monitoring](https://www.noctua.at/en/support/faqs/microcontroller-guide-pwm-setup-and-rpm-monitoring) - explication pratique du PWM 4 broches, tachomètre, puissance et fréquence PWM autour de 25 kHz.
- [Noctua: Fan pin configuration](https://www.noctua.at/faq-redirects/en/support/solutions/articles/101000081757-what-pin-configuration-do-noctua-fans-use-) - pinout standard des ventilateurs 4 broches et comportement quand seule l'alimentation est connectée.
- [SANYO DENKI: Fan Airflow and Static Pressure](https://techcompass.sanyodenki.com/en/training/cooling/fan_basic/004/index.html) - explication du flux d'air, de la pression statique, du point de fonctionnement et de la résistance du système.
- [DigiKey: Selecting A Fan](https://www.digikey.ca/en/articles/selecting-a-fan) - sélection du type de ventilateur, courbe de ventilateur, résistance du système et différence entre ventilateurs axiaux et radiaux.
- [Klipper Configuration Reference: Fans](https://www.klipper3d.org/Config_Reference.html#fans) - sections Klipper officielles pour les ventilateurs : `fan`, `heater_fan`, `temperature_fan`, `controller_fan` et `fan_generic`.
