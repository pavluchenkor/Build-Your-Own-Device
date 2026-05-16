# Erreurs d'alimentation électrique

L'alimentation électrique est la première chose à vérifier quand l'appareil se comporte étrangement.

Une alimentation faible, un fil mince ou une mauvaise borne peuvent ressembler à un problème de firmware, Wi-Fi, capteur ou contrôleur.

## Symptômes

Les signes typiques de problèmes d'alimentation électrique :

- le contrôleur redémarre ;
- l'écran vacille ;
- le Wi-Fi sur ESP32 s'arrête ;
- le ventilateur démarre et s'arrête ;
- le servo saccade ;
- le chauffage chauffe faiblement ;
- l'USB disparaît quand la charge est activée ;
- le MOSFET, la borne ou le fil se réchauffe ;
- les capteurs affichent des valeurs instables ;
- l'appareil fonctionne sans charge mais s'arrête quand le chauffage ou le moteur est connecté.

Si un symptôme apparaît exactement quand la charge est activée, presque toujours l'alimentation et le câblage doivent être vérifiés.

## Alimentation sans marge

Vous ne pouvez pas sélectionner une alimentation exactement correspondant à la puissance de la charge.

Si la charge consomme `100W`, une alimentation de `100W` fonctionnera à sa limite. Elle peut surchauffer, affaisser la tension et mal gérer les courants d'appel.

Règle pratique pour cette section :

**La marge d'alimentation minimale est de 50%, sauf si la documentation d'un composant spécifique en exige plus.**

Exemple :

```text
chauffage : 24V 120W
courant : 120W / 24V = 5A
marge minimale de 50% : 7,5A
```

Donc l'alimentation est mieux choisir au moins `24V 7,5A`, et en pratique souvent plus, s'il y a des ventilateurs, contrôleur, éclairage et autres charges.

## Courant total non calculé

Vous devez calculer non seulement un composant, mais l'appareil entier.

Par exemple :

- chauffage ;
- ventilateurs ;
- servo ;
- bande LED ;
- contrôleur ;
- affichage ;
- capteurs ;
- convertisseur CC-CC.

Les courants s'ajoutent. Les courants d'appel et les pics brefs doivent également être comptabilisés.

Un servo ou un ventilateur peut brièvement consommer plus qu'en mode normal. Si la marge est petite, exactement ce moment causera le redémarrage du contrôleur.

## Confusion 12V et 24V

L'erreur la plus simple et la plus dangereuse :

- ventilateur 12V branché à 24V ;
- module 5V branché à 12V ;
- chauffage 24V censé fonctionner normalement à 12V ;
- module 3.3V alimenté de 5V sans vérification.

Avant de connecter, vérifiez :

- la tension nominale de la charge ;
- la tension nominale de l'alimentation électrique ;
- la tension avec un multimètre ;
- le diagramme de connexion ;
- les tensions nominales du contrôleur et du module.

Ne comptez pas seulement sur la couleur du fil ou le type de connecteur similaire.

## Chute de tension sur les fils

Le fil a une résistance.

Plus le fil est long et plus le courant est grand, plus la chute de tension et le chauffage sont importants.

Symptômes :

- l'alimentation produit 24V, mais la charge en reçoit moins ;
- le chauffage chauffe moins que prévu ;
- le ventilateur démarre mal ;
- le servo saccade ;
- le fil est noticement chaud ;
- la borne se réchauffe.

Vérifiez la tension non seulement à la sortie de l'alimentation, mais aussi sur la charge elle-même pendant le fonctionnement.

Si la tension baisse considérablement sous charge, le problème peut être dans le fil, la borne, le connecteur, l'alimentation ou une charge trop grande.

## Pas de masse commune

Si un contrôleur drive un module externe ou charge, souvent une masse commune est nécessaire.

Par exemple :

- contrôleur drive un module MOSFET ;
- contrôleur met PWM à un ventilateur 4 broches ;
- contrôleur drive un servo avec une alimentation séparée ;
- HX711, RFID ou autre module est alimenté séparément.

Sans la « GND » commune, le signal peut ne pas avoir le bon niveau. L'appareil peut ne pas fonctionner ou fonctionner aléatoirement.

La masse commune ne signifie pas que l'ensemble de la charge doit être alimenté par le contrôleur. C'est seulement le niveau de référence commun pour le signal.

## Contrôleur alimenté à partir de la ligne bruyante

Les moteurs, ventilateurs, servos, chauffages et bandes LED peuvent créer des affaissements de tension et du bruit.

Si le contrôleur est alimenté à partir de la même ligne sans CC-CC approprié, filtrage et marge, il peut redémarrer.

Solutions courantes :

- CC-CC approprié séparé pour le contrôleur ;
- fils d'alimentation du contrôleur courts ;
- masse commune à un point clair ;
- condensateur près de la charge, si approprié ;
- séparation du câblage d'alimentation et logique ;
- alimentation électrique appropriée avec marge.

## Ce à vérifier avec un multimètre

Au minimum :

1. Tension de l'alimentation sans charge.
2. Tension de l'alimentation sous charge.
3. Tension aux bornes de la charge sous charge.
4. Polarité.
5. Présence de masse commune.
6. Chauffage du fil et de la borne après un test bref.

Si l'appareil fonctionne seulement sans charge, mesurez-le sous charge. La tension sans charge peut sembler normale.

## Ce à ne pas faire

Vous ne pouvez pas :

- utiliser une alimentation « à la limite » ;
- augmenter la tension du fusible parce qu'il saute ;
- utiliser des fils Dupont minces pour la charge d'alimentation ;
- tordre les fils d'alimentation sans borne appropriée ;
- alimenter le chauffage par un connecteur faible ;
- connecter la charge directement à la GPIO ;
- allumer à plusieurs reprises l'appareil si le fil ou la borne se réchauffe.

Si quelque chose se réchauffe, éteignez d'abord l'alimentation et trouvez la cause.

## Erreurs typiques

- n'a pas calculé le courant de charge ;
- a choisi une alimentation sans marge ;
- a oublié le courant d'appel du ventilateur ou du servo ;
- a confusé 12V et 24V ;
- alimente le contrôleur 5V à partir d'une ligne instable ;
- pas de « GND » commune ;
- fil trop mince ;
- fil trop long pour le courant ;
- borne non bien serrée ;
- la charge fonctionne mais la tension baisse considérablement.

## Points clés

- L'alimentation est vérifiée en premier.
- Calculez le courant pour toutes les charges, pas seulement une pièce.
- A besoin d'au moins 50% de marge d'alimentation.
- La tension doit être mesurée sous charge.
- La « GND » commune est souvent obligatoire pour contrôler les modules externes.
- Un fil mince ou long peut causer une chute de tension et un chauffage.

## Références

- [SparkFun : Comment alimenter un projet](https://learn.sparkfun.com/tutorials/how-to-power-a-project/voltagecurrent-considerations) - considérations élémentaires sur la tension, le courant et l'alimentation des projets microcontrôleur.
- [SparkFun : Conseils de dépannage](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - vérification de l'alimentation, des connexions et du chauffage lors du dépannage.
- [ProdataKey : Comment la jauge de fil affecte-t-elle la perte de ligne ?](https://support.pdk.io/hc/en-us/articles/360047588514-How-does-wire-gauge-affect-line-loss?) - pourquoi la longueur, la section transversale et le courant affectent la chute de tension et les pertes.
- [WiringCalcs : Chute de tension expliquée](https://wiringcalcs.com/guides/voltage-drop-explained-guide/) - explication pratique de la chute de tension, de la résistance du fil et de l'effet du courant.
- [Guide SparkFun Qwiic Power Meter](https://docs.sparkfun.com/SparkFun_Qwiic_Power_Meter_ACS37800/hardware_assembly/) - exemple de « GND » commune lors de la mesure/contrôle de la charge externe.
