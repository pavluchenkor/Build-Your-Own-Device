# Relais de semi-conducteurs

Un relais de semi-conducteurs ou SSR est un relais sans contacts mécaniques. Vous appliquez un faible signal de contrôle du contrôleur à l'entrée SSR, et la sortie SSR allume ou éteint une charge.

Dans les appareils simples pour les imprimantes 3D, SSR est le plus souvent utilisé pour un radiateur réseau : chambre, sèche-linge, table ou module de chauffage séparé. C'est un moyen pratique de contrôler une charge `110-230V AC` à partir d'électronique basse tension, mais pas un moyen de rendre le réseau sûr.

Si le projet a `110-230V AC`, la section électrique doit être montée dans un boîtier, avec un fusible, des terminales normales, une isolation, une protection contre la traction du câble et une compréhension de la sécurité électrique.

## Différence entre SSR et relais ordinaire

Un relais électromagnétique ordinaire clique car les contacts bougent physiquement à l'intérieur. La bobine du relais a besoin d'électricité, a souvent besoin d'un pilote de transistor, d'une diode de protection, et les contacts peuvent s'étinceler, vibrancer et s'user.

SSR bascule la charge en utilisant des semi-conducteurs. Par conséquent, il n'y a pas de clic, pas d'usure des contacts mécaniques et c'est mieux adapté au cycle fréquent d'allumage/extinction du radiateur.

Mais SSR ne "Relais sans inconvénients".

SSR a ses propres limitations :

- il se réchauffe ;
- nécessite souvent un radiateur ;
- peut avoir une petite fuite de courant en état d'extinction ;
- tolère moins bien les surcharges et les pics qu'un contacteur correctement choisi ;
- peut défaillir en état "marche" ;
- doit être choisi pour charge AC ou DC ;
- ne remplace pas le fusible, le boîtier et la protection thermique d'urgence.

Pour un cycle de commutation peu fréquent, un relais ordinaire ou un contacteur peut être plus approprié. Pour un contrôle fréquent d'un radiateur résistif, SSR est souvent plus pratique.

## Qu'y a-t-il à l'intérieur du SSR AC

Un SSR AC contient généralement :

- circuit d'entrée du signal de contrôle ;
- isolement optique ;
- circuit déclencheur ;
- TRIAC de puissance ou paire de thyristors ;
- circuit d'amortissement ou autre protection contre les pics ;
- bornes de puissance pour la charge.

En termes simples, c'est un circuit TRIAC prêt à l'emploi dans un boîtier. Par conséquent, SSR est pratique lorsque vous ne voulez pas calculer optoisolateur TRIAC, TRIAC, amortisseur, espacements de carte et section réseau vous-même.

Un boîtier prêt à l'emploi n'élimine pas la nécessité de vérification. Surtout si le SSR est bon marché, n'a pas de spécification technique ou a une évaluation de courant suspecte sur le boîtier.

## SSR AC et SSR DC

SSR doit être choisi selon le type de charge :

- **SSR AC** - pour courant alternatif, par exemple radiateur réseau `110-230V AC` ;
- **SSR DC** - pour courant continu, par exemple charge DC `12V` ou `24V`.

Ce sont des appareils différents. SSR AC ne peut pas être automatiquement mis sur un radiateur DC `24V` : il peut ne pas s'éteindre. SSR DC ne peut pas être considéré comme approprié pour `230V AC` : il peut être dangereux et non classé pour un tel circuit.

Vous devez vérifier non seulement l'étiquette `AC` ou `DC`, mais aussi la plage de tension de sortie.

Exemples de marquages :

```text
Entrée : 3-32V DC
Sortie : 24-380V AC
```

Cela signifie :

- l'entrée est contrôlée par un signal DC basse tension ;
- la sortie bascule la charge AC dans la plage spécifiée ;
- vous n'avez pas besoin d'alimenter la charge à partir du côté entrée via SSR.

Avant d'acheter, vérifiez les lignes `Input`, `Output`, `Load voltage`, `Load current` et le diagramme de connexion du fabricant.

## Schéma de connexion typique

SSR est généralement placé dans la rupture de la ligne de puissance de la charge. Le contrôleur se connecte uniquement à l'entrée SSR, tandis que le circuit de charge passe par la sortie SSR.

![Structure interne du relais de semi-conducteurs SSR](../../../img/01-electronics-basics/04-ssr-internal-structure.png)

*Source : [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:SSR.png), Thomas Verdyck, CC BY-SA 3.0*

Points importants :

- l'entrée SSR et la sortie SSR sont des côtés différents de l'appareil ;
- le côté basse tension ne doit pas être connecté au côté réseau ;
- SSR est placé dans la rupture de la ligne de puissance de charge, généralement `Line` ;
- la mise à la terre de protection `PE` n'est pas interrompue via SSR ;
- le fusible doit protéger le câblage et la charge ;
- le radiateur a besoin d'une protection thermique indépendante ;
- toute la section réseau doit être fermée au toucher.

SSR n'est pas considéré comme un disjoncteur de service. Pour la maintenance, vous avez besoin d'un moyen physique de couper le courant : interrupteur, disjoncteur, connecteur ou autre interruption de circuit standard. En pratique, il peut y avoir différents schémas selon les règles locales, le type d'électricité, la mise à la terre de protection et le boîtier. Si vous ne êtes pas sûr, une personne qualifiée doit vérifier le circuit.

## Passage à zéro, allumage aléatoire et contrôle

SSR AC est disponible avec différentes méthodes d'allumage.

**SSR à passage à zéro** allume la charge près du passage à zéro de la tension réseau. C'est une bonne option pour l'allumage/extinction simple d'un radiateur résistif : moins de bruit et une commutation plus douce.

**SSR à allumage aléatoire** allume la sortie presque immédiatement après l'application du signal de contrôle. Ce type est utilisé lorsqu'une logique différente est nécessaire, le contrôle de phase ou des exigences de charge spécifiques.

Pour une chambre, un sèche-linge ou un radiateur simple, le contrôle rapide du variateur n'est généralement pas nécessaire. Souvent, le contrôle lent suffit : par exemple, activer le radiateur pendant quelques secondes, pas cent fois par seconde.

Tous les SSR ne conviennent pas au contrôle de phase. Si vous avez spécifiquement besoin d'un régulateur de puissance de phase, c'est un type d'appareil séparé et un sujet séparé avec bruit, chauffage et exigences de charge.

## Fuite de courant

SSR peut passer un petit courant même lorsqu'il est "éteint". C'est ce qu'on appelle le courant de fuite.

Pour un radiateur puissant, un tel courant ne crée généralement pas de chauffage perceptible, mais pour une petite lampe, un pilote LED, une alimentation ou une très petite charge, cela peut être perceptible : l'indicateur peut briller faiblement, l'entrée d'alimentation peut se comporter étrangement.

Par conséquent, SSR ne doit pas être considéré comme un disjoncteur de circuit idéal. Avant le premier allumage du radiateur, vérifiez que la charge ne chauffe pas lorsque le signal de contrôle est retiré. Il est préférable de d'abord tester la sortie SSR avec une petite charge sûre, une lampe ou un multimètre, pas immédiatement avec le radiateur principal.

Pour la maintenance, l'arrêt d'urgence et l'isolation complète, vous avez besoin d'un interrupteur, d'un disjoncteur, d'un fusible, d'un connecteur ou d'un autre moyen physique de coupure de courant.

## Chauffage et radiateur

SSR se réchauffe pendant la fonctionnement. En état de conduction, il y a une chute de tension sur l'élément de puissance, ce qui signifie que la chaleur est générée.

Vous devez vérifier :

- courant de charge ;
- courant SSR maximal à température réelle ;
- chute de tension en sortie ;
- exigences de radiateur ;
- température à l'intérieur du boîtier ;
- orientation du radiateur et circulation d'air ;
- qualité du contact thermique entre SSR et radiateur ;
- température des terminales et des fils après test.

L'étiquette `25A` ou `40A` ne signifie pas que le SSR supportera ce courant sans radiateur dans un boîtier fermé et chaud à côté d'un radiateur. Les fabricants spécifient généralement le courant dans des conditions de refroidissement spécifiques.

Règle pratique pour un projet simple : ne choisissez pas SSR exactement pour le courant de charge. Plan marge, utilisez le radiateur, lisez la spécification technique et vérifiez la température dans le boîtier réel. `50%` de marge est la limite inférieure pour une estimation initiale, pas une garantie pour toute installation.

## SSR ne protège pas le radiateur

SSR est un interrupteur de puissance, pas un système de sécurité.

Un radiateur a besoin de couches indépendantes :

- fusible ou disjoncteur pour le câblage et la charge ;
- capteur de température correct ;
- limites de température du logiciel ;
- vérification du chauffage en microprogramme ;
- thermostat indépendant, fusible thermique ou commutateur bimétallique ;
- boîtier fait de matériau capable de supporter les températures réelles ;
- premier test sous observation.

Mode de défaillance important : SSR peut se dégrader et rester allumé. Par conséquent, la protection thermale d'urgence doit être capable de couper l'alimentation du radiateur indépendamment du contrôleur et du SSR.

## Quelles charges sont appropriées

SSR est le plus facile à utiliser avec des charges AC résistives :

- radiateur ;
- coussin chauffant silicone ;
- ampoule incandescente ;
- charge thermique simple sans électronique intégrée.

Soyez prudent avec :

- moteurs ;
- ventilateurs AC ;
- transformateurs ;
- solénoïdes ;
- alimentations ;
- pilotes électroniques ;
- charges à courant d'appel élevé.

Les charges inductives et électroniques peuvent nécessiter un type SSR différent, un amortisseur, un varistor, un contacteur ou un circuit séparé. Vous ne pouvez pas choisir SSR uniquement selon l'étiquette "40A".

## Ce qu'il faut vérifier avant d'acheter

Avant d'acheter SSR, vérifiez :

- charge AC ou DC ;
- tension de charge ;
- courant et puissance de charge ;
- tension d'entrée de contrôle ;
- compatibilité d'entrée avec contrôleur : `3.3V`, `5V`, `12V` ou autre niveau ;
- type d'allumage : passage à zéro ou aléatoire ;
- courant maximal avec refroidissement nécessaire ;
- le radiateur est-il nécessaire ;
- y a-t-il spécification technique ;
- y a-t-il diagramme de connexion normal ;
- terminales et distances d'isolement ;
- qualité du fabricant ;
- où le fusible est placé ;
- où la protection thermique indépendante sera.

S'il n'y a pas de documentation et que le SSR doit contrôler un radiateur réseau, c'est un mauvais choix.

## Erreurs courantes

- confus entrée et sortie SSR ;
- acheté SSR DC au lieu de SSR AC ou inversement ;
- ne pas vérifiée plage de tension de sortie ;
- connecté SSR AC à radiateur DC et ont été surpris qu'il ne s'éteint pas ;
- choisir SSR exactement pour courant de charge ;
- installé SSR sans radiateur ;
- installé SSR dans boîtier fermé et chaud ;
- ne pas tenu compte de courant de fuite ;
- utiliser SSR comme seule façon pour arrêt d'urgence ;
- oublié fusible ;
- ne pas installé protection thermique indépendante ;
- laissé terminales de réseau accessibles ;
- contrôler SSR avec PWM trop rapide sans comprendre type SSR et charge.

## Le point principal

SSR est pratique pour le contrôle de charge fréquente et silencieuse, en particulier radiateur réseau. Mais SSR doit être choisi pour type de charge, tension, courant, méthode d'allumage et point de fonctionnement thermique.

Pour charge `110-230V AC`, SSR n'élimine pas la sécurité électrique. Vous avez besoin d'un boîtier, d'un fusible, d'un câblage normal, d'un radiateur si nécessaire et d'une protection thermale indépendante du radiateur.

## Matériaux de référence

- [Omron : Aperçu des relais de semi-conducteurs](https://www.ia.omron.com/support/guide/18/introduction.html) - conception SSR, isolement optique, types et principes d'application générale.
- [Omron : Notes d'installation et glossaire SSR](https://www.ia.omron.com/support/guide/18/further_information.html) - définitions de `load voltage`, `leakage current`, `output ON voltage drop`, passage à zéro, amortissement et notes sur la dissipation thermique.
- [Panasonic : Principe de fonctionnement SSR](https://industry.panasonic.com/global/en/products/control/relay/solid-state/principle_operation) - différence entre SSR passage à zéro et aléatoire, comportement avec charges AC résistives et inductives.
- [Sensata/Crydom : Radiateurs série HS](https://www.sensata.com/products/relays/solid-state-relays/ssr-accessories/hs-series-heat-sinks) - pourquoi SSR génère de la chaleur et pourquoi le radiateur doit correspondre au courant et à la température.
- [DigiKey : Relais de semi-conducteurs - Un aperçu de base](https://www.digikey.com/en/blog/solid-state-relays-a-basic-overview) - bref aperçu des types de sortie SSR, passage à zéro, allumage aléatoire et limitations par rapport aux relais mécaniques.
