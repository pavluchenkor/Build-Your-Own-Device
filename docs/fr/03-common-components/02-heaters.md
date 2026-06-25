---
title: "Chauffages pour sécheur de filament et chambre chauffée"
description: "Choisir un chauffage pour sécheur de filament ou chambre active d’imprimante 3D: 12V, 24V, secteur, puissance, commande et sécurité."
---

# Chauffages pour sécheur de filament et chambre chauffée

Le chauffage définit la vitesse de montée en température et les limites de sécurité du sécheur ou de la chambre chauffée. Cette page explique les types de chauffages, la puissance, la commande par MOSFET ou SSR et les erreurs pouvant provoquer une surchauffe.

Un radiateur est une charge qui convertit l'énergie électrique en chaleur. Dans un appareil DIY simple, c'est le composant le plus dangereux : une erreur de ventilateur entraîne généralement un faible flux d'air, mais une erreur de radiateur peut provoquer une surchauffe, une fusion du boîtier, des dommages au câblage ou un risque d'incendie.

Dans les imprimantes 3D et les appareils de type iDryer, on trouve des radiateurs dans la hotend, le lit, la chambre, le sécheur de filament, le conduit d'air ou un module de chauffage séparé.

## Où c'est utilisé

Tâches typiques :

- chauffer la hotend ;
- chauffer le lit ;
- préchauffer la chambre de l'imprimante ;
- sécher le filament ;
- préchauffer l'air avant un filtre ou un conduit ;
- maintenir la température dans un petit volume de processus.

Ce sont des tâches différentes. Un radiateur pour une hotend en métal, un coussin en silicone et un module PTC d'air ne sont pas interchangeables sans recalculer la puissance, le montage, le flux d'air et la protection.

## Types de radiateurs

Options courantes :

- radiateur cartouche ;
- coussin silicone ;
- radiateur PTC ;
- élément de chauffage en céramique ;
- module de ventilateur thermique prêt à l'emploi ;
- plaque chauffante ;
- lit de chauffage secteur ;
- assemblage nichrome ou résistif dans un boîtier fini.

Un radiateur cartouche est généralement inséré dans un bloc métallique. Il a besoin d'un bon contact thermique avec le métal et d'un montage fiable du capteur de température.

Un coussin silicone est généralement collé ou pressé contre une surface plane. Il a besoin d'une surface plane, d'une bonne adhérence, d'un capteur de température et d'une protection contre le pelage.

Un radiateur PTC limite partiellement la montée en température en raison de ses propriétés, mais cela ne remplace pas le contrôleur, le capteur, le fusible, le boîtier et la vérification du flux d'air. PTC ne rend pas automatiquement un appareil sûr.

Un module de ventilateur thermique prêt à l'emploi combine le radiateur et le flux d'air, mais il doit quand même être vérifié pour la tension, la puissance, la température, les matériaux du boîtier et la protection d'urgence.

## Tension, puissance et courant

Avant de connecter, vous devez trouver :

- tension de fonctionnement ;
- puissance ;
- courant ;
- type de courant : CC ou CA ;
- température maximale ;
- température de fonctionnement du câble ;
- méthode de montage ;
- exigences de flux d'air ;
- méthode de contrôle autorisée.

Le courant est calculé par la formule :

```text
courant = puissance / tension
```

Exemples :

```text
24V 120W -> 5A
24V 240W -> 10A
24V 300W -> 12,5A
230V 300W -> environ 1,3A
```

Un radiateur basse tension haute puissance est plus sûr pour la tension, mais nécessite de grands courants. Les grands courants nécessitent une alimentation appropriée, des câbles, des bornes, un MOSFET/SSR et un fusible.

Un radiateur secteur en `110-230V CA` peut fournir une puissance élevée avec un courant plus faible, mais le risque de choc est beaucoup plus élevé. Pour la partie secteur, vous avez besoin de connaissances en matière de sécurité électrique, d'un boîtier, de bornes, d'isolant, de mise à la terre si nécessaire, de fusibles et d'une isolation galvanique de la commande.

## Contrôle du radiateur

Le contrôleur ne doit pas alimenter directement le radiateur à partir de GPIO. GPIO ne fournit qu'un signal de contrôle.

Options de contrôle de puissance typiques :

- MOSFET - pour les radiateurs CC `12V`/`24V` ;
- SSR CC - pour les radiateurs CC s'ils sont correctement évalués pour CC ;
- SSR CA - pour les radiateurs secteur CA ;
- relais mécanique - pour les arrêts rares, mais pas pour les PID/PWM fréquents ;
- sortie de puissance prête à l'emploi - uniquement si elle est évaluée pour le courant et la tension nécessaires.

SSR CA et SSR CC sont des appareils différents. Le mauvais type peut ne pas éteindre le radiateur ou fonctionner de manière non sécuritaire.

Un module MOSFET typique pour Arduino/ESP32 ne peut pas être utilisé comme commutateur `110-230V CA`. Si le module n'est pas conçu pour une charge secteur, il ne peut pas être connecté au secteur.

## Couches de sécurité

Un radiateur ne peut pas être conçu comme « le contrôleur l'allume - le contrôleur l'éteint ». Vous avez besoin de plusieurs couches de protection.

![Couches de commande de radiateur sûre](../../img/03-common-components/02-heater-safety-stack.svg)

Logique minimale :

- l'alimentation est évaluée pour le courant ;
- le fusible est sélectionné pour le câblage et la charge ;
- le commutateur de puissance correspond au type de charge ;
- le capteur de température est monté au bon endroit ;
- le micrologiciel a `min_temp`, `max_temp` et vérification du chauffage ;
- il y a une protection thermique matérielle indépendante : fusible thermique, thermostat ou commutateur bimétallique ;
- le boîtier et les matériaux résistent à la température réelle ;
- le premier test est effectué sous supervision.

La protection thermique matérielle doit fonctionner selon le contrôleur. Dans le cas simple, elle est placée en série dans le circuit d'alimentation du radiateur pour couper physiquement l'alimentation. Ce n'est pas seulement un autre capteur pour le micrologiciel.

Si le contrôleur se bloque, le capteur se détache, un MOSFET court-circuite ou un SSR colle, la protection doit couper l'alimentation du radiateur.

## Capteur de température

Un radiateur ne connaît pas sa propre température. Le contrôleur prend la décision en fonction du capteur.

Si le capteur :

- est mal appuyé ;
- est au mauvais endroit ;
- tombe ;
- est du mauvais type dans le micrologiciel ;
- a un mauvais contact thermique ;
- mesure l'air au lieu de la partie critique ;

le contrôleur peut continuer à chauffer même si la température réelle est déjà dangereuse.

Pour une hotend, le contact du capteur de température avec le bloc métallique est important. Pour un radiateur d'air, il est important de comprendre ce qui est mesuré : la température de l'élément, la température de l'air après l'élément, la température de la chambre ou la température près de la bobine. Ce sont des points différents et ils peuvent différer considérablement.

## Flux d'air et transfert de chaleur

Un radiateur libère de l'énergie, mais cette énergie doit aller en toute sécurité où elle est prévue.

Pour un radiateur à air, le flux d'air est critique :

- sans flux, l'élément peut localement surchauffer ;
- la ventilation faible ne supprime pas la chaleur ;
- un filtre obstrué change le mode de chauffage ;
- le conduit plastique peut ramollir ;
- un capteur de température peut ne pas voir ce qui se passe à l'élément.

Pour un radiateur de chambre, il est important de vérifier non seulement la température de l'air cible, mais aussi la température près du radiateur, des câbles, du SSR/MOSFET, des bornes et des pièces en plastique.

## Câbles, bornes et connecteurs

Un radiateur fonctionne souvent pendant de longues périodes et consomme un courant important. Un mauvais contact devient une source de chaleur.

Vérifiez :

- la section du câble ;
- la classe de température d'isolant ;
- l'évaluation de courant de la borne ;
- la qualité du sertissage ;
- le serrage des vis ;
- les viroles sur les câbles tressés ;
- la protection contre les tractions ;
- la distance des pièces chaudes ;
- l'absence de conducteurs exposés.

Si une borne noircit, sent, ramollit le plastique ou devient chaude, l'alimentation doit être coupée et la cause trouvée. Ne pas simplement augmenter le fusible ou le serrer plus tard.

## Quoi vérifier avant d'acheter

Avant d'acheter un radiateur, vérifiez :

- quel milieu il doit chauffer : métal, air, lit, chambre ;
- tension et type de courant ;
- puissance ;
- courant ;
- température de fonctionnement ;
- température de surface maximale ;
- exigences de flux d'air ;
- méthode de montage ;
- matériau du câble et isolant ;
- commutateur de puissance compatible ;
- endroit pour le capteur de température ;
- place pour la protection thermique indépendante ;
- boîtier et matériaux environnants ;
- disponibilité d'une description technique ou d'une documentation claire.

Si la page produit manque d'informations sur la tension, la puissance, la température et l'application, un tel radiateur ne convient pas à un premier projet sûr.

## Premier test

Le premier chauffage est effectué brièvement et sous supervision.

Procédure :

1. Vérifiez la résistance du radiateur et comparez avec le calcul `R = U^2 / P` si la tension et la puissance sont connues.
2. Vérifiez les courts-circuits le cas échéant.
3. S'il y a un boîtier métallique ou une terre de protection `PE`, vérifiez que le radiateur ne court-circuite pas au boîtier.
4. Vérifiez la tension d'alimentation sans le radiateur.
5. Vérifiez que le commutateur de contrôle éteint la charge.
6. Vérifiez que le capteur de température lit une valeur raisonnable.
7. Pour un radiateur `12V`/`24V`, si possible, démarrez via une alimentation de labo avec limitation de courant ou un fusible temporaire.
8. Activez le chauffage à faible puissance ou brièvement.
9. Observez si la température augmente au bon endroit.
10. Vérifiez que la commande d'arrêt arrête réellement le chauffage.
11. Vérifiez le chauffage des câbles, des bornes, du MOSFET/SSR et du boîtier.
12. Vérifiez la protection d'urgence par un scénario que vous pouvez simuler en toute sécurité.

N'abandonnez pas un nouveau radiateur au premier démarrage.

## Erreurs typiques

- radiateur connecté à la mauvaise tension ;
- n'a pas calculé le courant ;
- alimentation du radiateur via un faible connecteur ;
- utilisation de MOSFET pour un radiateur secteur CA ;
- confusion entre SSR CA et SSR CC ;
- SSR installé sans dissipateur thermique alors qu'il était nécessaire ;
- fusible oublié ;
- pas de protection thermique indépendante ;
- mauvais montage du capteur de température ;
- boîtier fait de PLA près du radiateur ;
- n'a pas tenu compte du flux d'air et du filtre obstrué ;
- testé sur établi mais pas en boîtier ;
- partie secteur exposée ;
- augmentation du fusible au lieu de trouver pourquoi il a fondu.

## Point principal

Un radiateur est choisi par la tâche, la tension, la puissance, la méthode de transfert de chaleur et la sécurité. Vous ne pouvez pas le traiter comme une simple « charge à deux fils ».

D'abord, calculez le courant, sélectionnez le commutateur de puissance, le câblage et le fusible. Ensuite, assurez-vous qu'il y a un capteur de température, une protection du micrologiciel, une protection thermique matérielle indépendante, un boîtier approprié et des tests dans le monde réel.

## Matériaux de référence

- [Klipper Configuration Reference: heater_generic and verify_heater](https://www.klipper3d.org/Config_Reference.html#heater_generic) - paramètres de radiateur, capteurs de température, `min_temp`, `max_temp` et vérification du chauffage dans Klipper.
- [Marlin Configuration: Temperature Ranges and Thermal Protection](https://marlinfw.org/docs/configuration/configuration.html#temperature-ranges) - limites de température, `MINTEMP`, `MAXTEMP` et protection thermique dans Marlin.
- [Omron: Overview of Solid-state Relays](https://www.ia.omron.com/support/guide/18/introduction.html) - explication de base du SSR, types, application et mesures thermiques.
- [Sensata/Crydom: SSR Heat Sink Reference](https://www.sensata.com/resources/brochure-solid-state-relays-heat-sink-reference) - pourquoi SSR a besoin d'un dissipateur thermique et comment le régime thermique se rapporte au courant de charge.
- [Omega: Cartridge Heaters](https://www.omega.nl/prodinfo/cartridge-heaters.html) - notes pratiques sur l'application du radiateur cartouche, le contact thermique et la sélection de puissance.
