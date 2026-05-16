# Erreurs courantes

Cette section ne sert pas à vous critiquer.

Elle sert à vous aider à identifier rapidement les erreurs courantes dans un appareil DIY : alimentation affaissée, fil lâche, capteur affichant des ordures, contrôleur redémarrant, chauffage se comportant étrangement.

Le format de la section est simple :

- le symptôme ;
- la cause probable ;
- ce à vérifier ;
- ce à ne pas faire ;
- comment réparer en toute sécurité.

## La règle principale du diagnostic

Si l'appareil se comporte étrangement, vous ne changez pas immédiatement le firmware, ne ressoudez pas tout ou n'augmentez pas la puissance.

D'abord, vérifiez les bases :

1. l'alimentation électrique ;
2. la polarité ;
3. la masse commune « GND » ;
4. les bornes et connecteurs ;
5. les capteurs ;
6. les commutateurs d'alimentation ;
7. le firmware et la configuration.

La plupart des problèmes dans les appareils simples s'avèrent être non « l'électronique complexe » mais l'alimentation électrique, le câblage ou les connexions incorrectes.

## Quand arrêter

Éteignez immédiatement l'alimentation si :

- une odeur de brûlure apparaît ;
- un fil se réchauffe ;
- une borne se réchauffe ;
- un connecteur noircit ;
- le boîtier devient chaud dans un endroit inattendu ;
- le chauffage ne s'éteint pas ;
- le disjoncteur ou le fusible saute ;
- le capteur de température affiche des ordures ;
- l'appareil fonctionne seulement quand vous bougez le fil.

Ne « l'allumez pas une fois de plus pour regarder ». Si quelque chose se réchauffe, sent ou scintille, trouvez d'abord la cause sans alimentation.

## Principaux groupes d'erreurs

Dans cette section, les erreurs sont divisées en groupes :

- `02-power-mistakes.md` - alimentation faible, tension incorrecte, affaissement, fils minces, pas de marge.
- `03-wiring-mistakes.md` - polarité inversée, mauvaises bornes, pas de masse commune, mauvais connecteurs.
- `04-controller-mistakes.md` - carte inappropriée, logique 3.3V/5V, GPIO au lieu de sortie d'alimentation, firmware incorrect.
- `05-heater-ssr-mistakes.md` - chauffages, SSR, MOSFET, courant alternatif 110-230V, capteur de température, dissipateurs thermiques et protection.
- `06-diagnostic-checklist.md` - ordre de vérification général quand l'appareil ne fonctionne pas.

## Pourquoi l'alimentation électrique est vérifiée en premier

L'alimentation électrique affecte presque tout.

Si l'alimentation est faible ou les fils minces, les symptômes peuvent ressembler à un problème de firmware :

- le contrôleur redémarre ;
- le Wi-Fi s'arrête ;
- l'écran vacille ;
- le servo saccade ;
- le ventilateur ne démarre pas ;
- les capteurs affichent des valeurs aléatoires ;
- le chauffage chauffe mal.

Jusqu'à ce que l'alimentation soit vérifiée avec un multimètre sous charge, il est difficile de diagnostiquer en toute confiance tout le reste.

## Pourquoi le câblage est plus important qu'il n'y paraît

Une mauvaise connexion peut fonctionner « presque normalement ».

C'est précisément ce qui est dangereux :

- aujourd'hui ça fonctionne ;
- quand on la secoue, elle se déconnecte ;
- quand chauffée, le contact s'aggrave ;
- la borne noircit progressivement ;
- le fil commence à se réchauffer ;
- le capteur apparaît et disparaît.

Si l'appareil change de comportement quand vous bougez le fil, ce n'est pas une erreur logicielle. C'est un problème de connexion.

## Pourquoi la protection ne doit pas être désactivée

La fuite thermique, `MINTEMP`, `MAXTEMP`, « le chauffage ne chauffe pas » et les erreurs similaires existent non pour embêter l'utilisateur.

Ce sont des signes que le contrôleur ne fait plus confiance à la lecture de température ou voit un comportement de chauffage dangereux.

Mauvaise idée :

- désactiver la protection thermique ;
- étendre les limites de température sans comprendre la raison ;
- remplacer le fusible par un plus gros ;
- court-circuiter le thermostat directement ;
- court-circuiter la protection « pour tester ».

Bonne idée : trouver la raison pour laquelle la protection se déclenche.

## Comment lire cette section

Si l'appareil ne fonctionne pas du tout, commencez par la liste de contrôle de diagnostic.

Si le symptôme est clair, allez à l'article pertinent :

- redémarrages, scintillement, chaleur faible - alimentation électrique ;
- fonctionne quand vous bougez le fil - câblage ;
- carte non détectée ou les broches ne répondent pas - contrôleur ;
- le chauffage ne s'éteint pas ou le SSR se réchauffe - chauffage et SSR ;
- tout est flou - liste de contrôle générale.

## Points clés

- La plupart des erreurs commencent par l'alimentation, le câblage et les connexions incorrectes.
- Si quelque chose se réchauffe, sent ou noircit, éteignez l'alimentation.
- Le diagnostic procède du simple au complexe.
- La protection du firmware et la protection du matériel ne doivent pas être désactivées pour la commodité.
- Le secteur alternatif 110-230V ne peut pas être diagnostiqué « sur le banc » sans comprendre la sécurité électrique.

## Références

- [SparkFun : Conseils de dépannage](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - approche de base pour vérifier les connexions, l'alimentation, le chauffage et les problèmes matériels.
- [SparkFun : Comment alimenter un projet](https://learn.sparkfun.com/tutorials/how-to-power-a-project/voltagecurrent-considerations) - tension, courant et sélection d'alimentation pour un projet électronique.
- [Tom's Hardware : Comment corriger la fuite thermique de l'imprimante 3D](https://www.tomshardware.com/3d-printing/how-to-fix-3d-printer-thermal-runaway) - analyse pratique du capteur de température, du chauffage, du ventilateur, de l'alimentation et du câblage lors d'une fuite thermique.
- [Klipper Configuration Reference : verify_heater](https://www.klipper3d.org/Config_Reference.html#verify_heater) - vérification officielle du chauffage et vérification du capteur de température par taux de hausse attendu et erreur accumulée.
- [Guide SparkFun Qwiic Power Meter](https://docs.sparkfun.com/SparkFun_Qwiic_Power_Meter_ACS37800/hardware_assembly/) - exemple du besoin d'une « GND » commune lors de la mesure/contrôle de la charge externe.
