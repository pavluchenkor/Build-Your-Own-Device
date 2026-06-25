# Liste de contrôle de diagnostic

Cette liste de contrôle est nécessaire quand l'appareil ne fonctionne pas ou se comporte étrangement.

L'idée est simple : d'abord éliminer le danger, puis vérifier l'alimentation et le câblage, et seulement après passer au firmware, capteurs et charges.

## 1. Arrêtez et éteignez l'alimentation

D'abord, éteignez l'appareil.

Surtout s'il y a :

- une odeur ;
- un fil qui se réchauffe ;
- une borne qui se réchauffe ;
- de la fumée ;
- un son étrange ;
- des étincelles ;
- le chauffage ne s'éteint pas ;
- le disjoncteur ou le fusible saute.

Ne changez pas les fils sous tension.

## 2. Déconnectez la charge d'alimentation

Avant le diagnostic, il est mieux de déconnecter temporairement :

- le chauffage ;
- la bande LED puissante ;
- le servo ;
- le moteur ;
- la charge d'alimentation externe.

D'abord, vérifiez que le contrôleur et la logique fonctionnent sans charge dangereuse.

Si l'appareil a du courant alternatif 110-230V, ne tenez pas ouverte la partie secteur sous tension sur le banc.

## 3. Vérifiez l'alimentation électrique

Avec un multimètre, vérifiez :

- s'il y a de la tension à la sortie de l'alimentation ;
- si la tension est correcte ;
- si la polarité est correcte ;
- si la tension s'affaisse sous charge.

Par exemple :

- la ligne 24V doit être environ 24V ;
- la ligne 12V doit être environ 12V ;
- la ligne 5V doit être environ 5V ;
- la ligne 3.3V doit être environ 3.3V.

L'écart acceptable dépend de l'alimentation et de l'appareil, mais une erreur évidente comme 24V au lieu de 12V doit être trouvée avant de connecter la charge.

## 4. Vérifiez la polarité

Vérifiez où sont plus et moins.

Ne comptez pas seulement sur la couleur du fil.

Vérifiez :

- les marquages de la carte ;
- les marquages de l'alimentation ;
- le pinout du module ;
- le multimètre ;
- le diagramme de connexion.

La polarité inversée tue souvent le module instantanément.

## 5. Vérifiez la « GND » commune

S'il y a un module externe ou alimentation séparée, vérifiez la « GND » commune.

C'est important pour :

- le module MOSFET ;
- le servo ;
- le ventilateur PWM ;
- le HX711 ;
- le RFID ;
- les capteurs externes ;
- le CC-CC séparé.

Si les signaux vont entre les appareils, ils doivent avoir un niveau de référence commun, sauf si le circuit utilise une isolation spéciale.

## 6. Vérifiez les bornes et connecteurs

Inspectez :

- le fil inséré complètement ;
- le conducteur serré, pas l'isolant ;
- pas de brins exposés ;
- pas de noircissement ;
- pas d'odeur ;
- la borne ne bouge pas ;
- le connecteur ne tient pas « sur la foi » ;
- le capot du boîtier ne pince pas le fil.

Bougez les fils sans alimentation. Si le contact chute clairement mécaniquement, d'abord réparez le câblage.

## 7. Vérifiez le contrôleur sans charge

Connectez le contrôleur sans charge d'alimentation.

Vérifiez :

- s'il est détecté via USB ;
- si le firmware démarre ;
- s'il y a communication avec l'hôte ;
- si le microcontrôleur ne se réchauffe pas ;
- si l'alimentation ne vacille pas ;
- si les logs sont visibles.

Si le contrôleur n'est pas détecté même sans charge, ne reconnectez pas le chauffage et les modules d'alimentation jusqu'à ce que vous trouviez la cause.

## 8. Vérifiez le firmware et la configuration

Vérifiez :

- le firmware est construit pour la bonne carte ;
- le bon chemin série/CAN/USB est sélectionné ;
- les broches dans la configuration correspondent au pinout ;
- « sensor_type » est correct ;
- « min_temp » et « max_temp » sont raisonnables ;
- les sorties ne sont pas accidentellement inversées ;
- pas de conflits de broches.

Si le chauffage se comporte à l'opposé après le changement de configuration, par exemple « éteint » mais la température monte, éteignez l'alimentation et vérifiez la configuration et le circuit d'alimentation.

## 9. Vérifiez les capteurs

Avant le chauffage, vérifiez les capteurs.

Pour le thermisteur :

- la température comme température ambiante ;
- pas de « MINTEMP » ;
- pas de « MAXTEMP » ;
- les lectures ne sautent pas ;
- la résistance comme attendue ;
- Quand chauffée par la main, les lectures changent correctement.

Pour les autres capteurs :

- l'alimentation correcte ;
- l'interface sélectionnée correctement ;
- l'adresse ou les broches correspondent à la configuration ;
- les fils courts et ne pendent pas.

## 10. Vérifiez la sortie sans charge

Si vous devez vérifier MOSFET, relais ou sortie de carte, faites-le d'abord sans charge dangereuse.

Options :

- petit ventilateur de test ;
- LED avec résistance ;
- multimètre ;
- charge sûre et faible.

Ne commencez pas le diagnostic avec un chauffage puissant.

Pour le chauffage, avant le premier allumage, la vérification numérique est utile : mesurez la résistance et comparez à la « R = U^2 / P » attendue. S'il y a un boîtier métallique ou « PE », vérifiez aucun court-circuit au boîtier. Pour le chauffage « 12V »/« 24V », le premier fonctionnement est mieux via une alimentation de laboratoire avec limite de courant ou fusible temporaire.

## 11. Vérifiez le commutateur d'alimentation séparément

Pour MOSFET/SSR/relais, vérifiez :

- le type de charge correct : AC ou DC ;
- la tension correcte ;
- les bornes correctes ;
- l'entrée de contrôle ;
- la « GND » commune si nécessaire ;
- le dissipateur thermique si nécessaire ;
- l'entrée et la sortie ne sont pas mélangées.

Le SSR AC et le SSR DC ne peuvent pas être échangés.

Pour le SSR, vérifiez séparément l'état « éteint » : avec le signal de contrôle supprimé, la charge ne doit pas se réchauffer. Le premier test est mieux utiliser la petite charge sûre, lampe ou multimètre, pas le chauffage principal.

## 12. Connectez la charge avec un test bref

Quand les vérifications élémentaires sont passées, connectez la charge brièvement et sous supervision.

Vérifiez :

- la charge s'active ;
- la charge s'éteint ;
- les bornes ne se réchauffent pas ;
- les fils ne se réchauffent pas ;
- le MOSFET/SSR ne surchauffe pas ;
- le capteur affiche la température réaliste ;
- le contrôleur ne redémarre pas ;
- le fusible ne saute pas.

Le premier test de chauffage ne doit pas être long et sans surveillance.

## 13. Vérifiez après quelques minutes d'opération

Après quelques minutes, vérifiez :

- les bornes ;
- les fils ;
- l'alimentation ;
- le MOSFET ;
- le SSR ;
- le boîtier près du chauffage ;
- les lectures des capteurs ;
- la stabilité du contrôleur.

Si quelque chose s'est inopinément réchauffé, éteignez l'alimentation et retournez à la vérification de l'alimentation, du câblage et du commutateur d'alimentation.

## Ce à ne pas faire

Vous ne pouvez pas :

- allumer à plusieurs reprises l'appareil si quelque chose se réchauffe ou sent ;
- tenir ouverte du courant alternatif 110-230V sur le banc ;
- changer les fils sous tension ;
- augmenter le fusible « pour qu'il ne saute pas » ;
- désactiver la protection thermique pour le test ;
- court-circuiter le thermostat d'urgence ;
- tester un chauffage puissant sans capteur de température ;
- laisser le premier test sans surveillance.

## Ordre court

Si vous avez besoin d'un ordre très court :

1. Éteignez l'alimentation.
2. Déconnectez la charge d'alimentation.
3. Vérifiez la tension de l'alimentation.
4. Vérifiez la polarité.
5. Vérifiez la « GND » commune.
6. Vérifiez les bornes et les fils.
7. Vérifiez le contrôleur sans charge.
8. Vérifiez le firmware et le pinout.
9. Vérifiez les capteurs.
10. Vérifiez la sortie sans charge dangereuse.
11. Vérifiez MOSFET/SSR/relais.
12. Connectez la charge avec un test bref.
13. Vérifiez le chauffage des fils, bornes et pièces d'alimentation.

## Points clés

- Le diagnostic commence par éteindre l'alimentation et réduire le risque.
- La charge d'alimentation est mieux déconnectée pour les vérifications élémentaires.
- L'alimentation, la polarité, « GND » et les bornes sont vérifiées avant le firmware.
- Le chauffage ne peut pas être utilisé comme premier indicateur de test.
- Si la protection s'est déclenchée, trouvez la cause, ne désactivez pas la protection.

## Références

- [SparkFun : Conseils de dépannage](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - séquence de base de vérification des connexions, de l'alimentation et des problèmes matériels.
- [SparkFun : Comment alimenter un projet](https://learn.sparkfun.com/tutorials/how-to-power-a-project/voltagecurrent-considerations) - comment penser à la tension, le courant et l'alimentation du projet.
- [Fluke : Comment mesurer la résistance avec un multimètre numérique](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-resistance) - mesure de résistance sûre sur circuit désénergisé.
- [Tom's Hardware : Comment corriger la fuite thermique de l'imprimante 3D](https://www.tomshardware.com/3d-printing/how-to-fix-3d-printer-thermal-runaway) - vérifications pratiques du thermisteur, chauffage, ventilateur, alimentation et câblage.
- [Klipper Configuration Reference : min_temp, max_temp et verify_heater](https://www.klipper3d.org/Config_Reference.html#verify_heater) - vérifications logicielles de la température, du capteur et de la hausse de température attendue du chauffage.
