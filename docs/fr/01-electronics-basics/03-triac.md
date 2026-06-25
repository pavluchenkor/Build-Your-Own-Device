# TRIAC

Un TRIAC, ou thyristor, est un interrupteur semi-conducteur de puissance pour le courant alternatif. Il est utilisé lorsque vous devez allumer ou contrôler une charge AC : par exemple un radiateur, une ampoule incandescente ou un autre appareil simple sur `110-230V AC`.

Pour les appareils faits maison, c'est un sujet à haut risque. Le TRIAC lui-même ne rend pas la tension réseau sûre. Il fournit simplement un moyen de contrôler une charge AC sans contacts mécaniques.

## Comment le TRIAC diffère du MOSFET

Le module MOSFET de l'article précédent est généralement utilisé pour les charges DC : `5V`, `12V`, `24V`.

Le TRIAC est utilisé pour les charges AC. Il est allumé par une impulsion de contrôle et conduit le courant jusqu'à ce que le courant qui le traverse tombe en dessous de la valeur de maintien. En réseau AC, cela se produit généralement près du passage à zéro de l'onde sinusoïdale.

En pratique :

- MOSFET - choix typique pour ventilateur `12V`/`24V`, bande LED ou chauffage DC ;
- TRIAC - élément typique dans les régulateurs de puissance AC et de nombreux SSR AC ;
- SSR - relais semi-conducteur prêt à l'emploi, qui peut contenir un optocoupleur, TRIAC/thyristor, boîtier, bornes et parfois radiateur.

Pour un débutant, pour une charge réseau, il est souvent plus sûr de considérer un SSR prêt à l'emploi ou un module certifié que d'assembler votre propre circuit TRIAC sur une breadboard.

## Pourquoi c'est utilisé pour les charges AC

Une charge basse tension puissante nécessite un courant élevé.

Par exemple :

```text
24V 240W -> 10A
24V 300W -> 12,5A
230V 300W -> environ 1,3A
```

À `24V`, vous avez besoin de fils épais, d'une alimentation électrique puissante, d'un MOSFET robuste, de bornes normales et de refroidissement. À `230V AC`, le courant est plus faible, mais il y a une tension réseau dangereuse et toutes les exigences de sécurité électrique.

L'approche TRIAC n'est pas "meilleure" et pas "plus simple". C'est un compromis différent : moins de courant dans le circuit électrique, mais des exigences beaucoup plus élevées pour l'isolation, le boîtier, le fusible, les distances et les qualifications.

## Architecture typique

Le contrôleur n'est généralement pas connecté directement au TRIAC.

Une architecture sûre typique ressemble à ceci :

![Circuit variateur AC avec TRIAC](../../img/01-electronics-basics/03-triac-dimmer-circuit.svg)

*Source : [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:TRIAC_based_dimmer_circuit.svg), Osbertjoel, CC BY-SA 4.0*

Il a :

- côté basse tension : contrôleur et résistance de contrôle ;
- TRIAC optoïsolateur : transmet la commande via l'isolement optique ;
- côté réseau : TRIAC de puissance, charge AC, fusible, bornes et boîtier ;
- parfois circuit d'amortissement et varistance/TVS pour le bruit et les pics.

Le TRIAC optoïsolateur est nécessaire pour l'isolement galvanique. Cela signifie qu'il n'y a pas de connexion électrique directe entre le microcontrôleur et la section réseau. La commande est transmise par la lumière à l'intérieur de l'optocoupleur.

L'isolement galvanique réduit le risque que la tension réseau atteigne le contrôleur, l'USB et l'ordinateur. Mais cela ne rend pas la section réseau sûre à toucher.

## Passage à zéro et contrôle de phase

Les TRIAC optoïsolateurs sont disponibles avec passage à zéro et sans.

Un optoïsolateur TRIAC avec passage à zéro allume la charge près du passage à zéro de la tension réseau. C'est pratique pour l'allumage/extinction simple d'un radiateur ou d'une autre charge résistive : moins de bruit et une commutation plus douce.

Un TRIAC optoïsolateur sans passage à zéro est utilisé lorsque le contrôle de phase de la puissance est nécessaire, par exemple un variateur. Un tel circuit est plus complexe : vous devez détecter le passage à zéro, compter le délai et tenir compte du bruit.

Pour un radiateur dans un sèche-linge ou une chambre, un contrôle de niveau de variateur n'est généralement pas nécessaire. Souvent, une approche d'allumage/extinction lente ou de contrôle par rafales suffit, si elle est supportée par le module choisi et sûre pour la charge.

## Quelles charges sont appropriées

Un TRIAC est le plus facile à utiliser avec des charges AC résistives :

- radiateur ;
- ampoule incandescente ;
- charge thermique simple sans électronique à l'intérieur.

Soyez prudent avec :

- moteurs ;
- ventilateurs AC ;
- transformateurs ;
- solénoïdes ;
- alimentations ;
- pilotes électroniques ;
- charges à courant d'appel élevé.

Une charge inductive déplace la phase du courant par rapport à la tension et peut interférer avec l'extinction normale du TRIAC. Elle peut nécessiter d'autres types de TRIAC, un circuit d'amortissement, une varistance ou une méthode de commutation différente.

Une alimentation électrique ou un pilote électronique ne doit pas être considéré comme une charge résistive normale. S'il contient sa propre électronique, le contrôle TRIAC peut fonctionner mal ou dangereusement.

## Circuit d'amortissement

L'amortisseur est un circuit RC (résistance + condensateur en parallèle avec TRIAC) qui amortit les changements de tension nets et prévient les déclenchements faux du TRIAC.

Cela peut aider :

- avec les charges inductives ;
- avec le bruit rapide dans le réseau ;
- avec les déclenchements faux du TRIAC ;
- avec les problèmes d'extinction.

Un point de départ typique pour une charge résistive de 200–400 W à 230 V : **100 nF + 100 Ω**. Le condensateur doit être de type X2 ou équivalent, évalué pour le fonctionnement en circuit réseau. Ce n'est pas une solution universelle, mais une valeur de départ. Pour une autre charge, les évaluations sont recalculées selon la fiche technique du TRIAC et les notes d'application du fabricant.

Si vous n'avez pas d'expérience avec les circuits AC, il est préférable d'utiliser un module prêt à l'emploi ou un SSR où l'amortisseur est déjà calculé par le fabricant.

## Chauffage et radiateur

Un TRIAC se réchauffe pendant le fonctionnement. Ce n'est pas un commutateur parfait : il y a une chute de tension à travers lui, ce qui signifie que la chaleur est générée.

Vous devez vérifier :

- courant de charge ;
- boîtier TRIAC ;
- chute de tension en état de conduction ;
- exigences de radiateur ;
- température ambiante ;
- température à l'intérieur du boîtier ;
- distance par rapport aux plastiques et fils ;
- marge de sécurité des paramètres.

Dans la spécification technique, il y a de nombreux paramètres. Pour le premier choix, trois suffisent :

- `IT(RMS)` — courant RMS maximal à travers le TRIAC. Doit être supérieur au courant de charge avec marge, au refroidissement réel.
- `VDRM`/`VRRM` — tension maximale en état d'extinction. Pour le réseau 230 V, choisissez TRIAC évalué à 600 V et plus.
- `IGT` — courant de grille. Doit correspondre aux capacités du TRIAC optoïsolateur.

D'autres paramètres (`IH`, `dV/dt`, `Tj`, `Rth`) sont importants pour un calcul précis ou en cas de problèmes dans le circuit réel.

L'évaluation du courant dans la spécification technique est donnée sous certaines conditions de refroidissement. Dans un boîtier fermé et chaud sans radiateur, le courant maximal réel est plus faible.

## TRIAC et SSR

Un SSR pour une charge AC utilise souvent un optocoupleur et un TRIAC ou un étage de puissance à thyristor à l'intérieur.

Avantages d'un SSR prêt à l'emploi :

- bornes pratiques ;
- entrée de contrôle claire ;
- boîtier ;
- paramètres déclarés ;
- souvent plus facile à monter et refroidir mécaniquement.

Inconvénients :

- SSR se réchauffe aussi ;
- le type correct est nécessaire : SSR à sortie AC pour charge AC ;
- de nombreux SSR nécessitent un radiateur ;
- le marché a de nombreuses contrefaçons et modules avec des spécifications exagérées ;
- SSR ne remplace pas le fusible, le boîtier et la sécurité électrique.

Si la tâche consiste à contrôler un radiateur réseau dans un appareil réel, un SSR de bonne qualité prêt à l'emploi est souvent plus pratique qu'un circuit fait maison sur un TRIAC séparé.

## Ce que vous ne pouvez pas faire

Vous ne pouvez pas :

- assembler un circuit TRIAC réseau sur une breadboard sans soudure ;
- laisser la section réseau ouverte sous tension ;
- connecter le contrôleur directement à la section réseau sans isolement ;
- utiliser un module MOSFET basse tension à la place de TRIAC/SSR pour `230V AC` ;
- mettre un condensateur aléatoire dans le circuit d'amortissement réseau ;
- considérer l'étiquette "40A" sur un module bon marché comme une vérification suffisante ;
- fonctionner sans fusible ;
- placer les bornes réseau à côté de l'USB, des boutons et des contacts basse tension ouverts ;
- tester un tel circuit sans comprendre la sécurité électrique.

Travailler avec `110-230V AC` nécessite des connaissances, des outils appropriés, un boîtier, une vérification d'isolement et la compréhension des règles locales. En cas de doute, une personne qualifiée doit assembler ou inspecter la section électrique.

## Ce qu'il faut vérifier avant d'acheter

Avant d'acheter un TRIAC, un module ou un SSR, vérifiez :

- s'il s'agit d'une charge AC ou DC ;
- tension réseau ;
- courant et puissance de charge ;
- s'il s'agit d'une charge résistive ou inductive ;
- si le passage à zéro est nécessaire ;
- si l'amortissement est nécessaire ;
- courant maximal au refroidissement réel ;
- si un radiateur est nécessaire ;
- s'il y a isolement optique ;
- bornes et espacement pour le réseau ;
- fusible et boîtier ;
- s'il y a spécification technique ou documentation du fabricant.

S'il n'y a pas de documentation et que le module doit contrôler un radiateur réseau, c'est un mauvais choix.

## Erreurs courantes

- utiliser le TRIAC pour une charge DC ;
- confondre MOSFET, TRIAC et SSR ;
- connecter la charge réseau sans isolement optique ;
- utiliser le TRIAC optoïsolateur à passage à zéro et s'attendre à un gradateur lisse ;
- utiliser le TRIAC avec moteur sans amortissement et vérification du type de charge ;
- ne pas installer de radiateur ;
- ne pas tenir compte de la température à l'intérieur du boîtier ;
- utiliser des bornes aléatoires et des fils fins ;
- penser que SSR ou TRIAC remplace le fusible ;
- laisser la section réseau ouverte à côté du contrôleur et de l'USB.

## Le point principal

Le TRIAC est un commutateur de puissance pour les charges AC. Il est utile pour les charges réseau résistives, telles que les radiateurs, mais nécessite un design correct de la section réseau.

Pour un microcontrôleur, l'isolement optique est nécessaire. Pour la charge, le bon TRIAC/SSR, le fusible, les bornes, le boîtier, le radiateur si nécessaire et la vérification de la sécurité sont nécessaires. Si vous n'avez pas d'expérience avec `110-230V AC`, ne montez pas la section électrique vous-même.

## Matériaux de référence

- [STMicroelectronics : Documentation des TRIAC standard et sans amortissement](https://www.st.com/en/thyristors-scr-and-ac-switches/standard-and-snubberless-triacs/documentation.html) - sélection TRIAC, paramètres et notes d'application sur TRIAC sans amortissement/standard.
- [ST AN437 : Conception du circuit d'amortissement RC pour les TRIAC](https://www.alldatasheet.com/datasheet-pdf/pdf/696239/STMICROELECTRONICS/AN437.html) - explication détaillée de la raison pour laquelle le circuit RC d'amortissement est nécessaire et comment il affecte l'extinction du TRIAC.
- [Fiche technique MOC3063 : Pilote TRIAC optoïsolateur à passage à zéro](https://www.alldatasheet.com/html-pdf/5043/MOTOROLA/MOC3063/258/1/MOC3063.html) - exemple de TRIAC optoïsolateur pour l'interface logique avec charges `115/240 VAC`.
- [Omron : Aperçu des relais à semi-conducteurs](https://www.ia.omron.com/support/guide/18/introduction.html) - explication fondamentale du SSR en tant que relais à semi-conducteurs sans contacts mécaniques.
- [Glossaire SSR Omron : phototriac, passage à zéro, amortissement](https://www.ia.omron.com/support/guide/31/further_information.html) - brèves définitions de phototriac, passage à zéro et circuit d'amortissement.
