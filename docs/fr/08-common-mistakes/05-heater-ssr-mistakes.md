# Erreurs du chauffage et du SSR

Le chauffage est la charge la plus dangereuse dans un appareil DIY simple.

Un ventilateur peut ne pas démarrer. Un capteur peut donner des lectures fausses. Mais un chauffage avec une erreur peut surchauffer le boîtier, faire fondre le plastique, endommager le câblage ou créer un risque d'incendie.

Si l'appareil a du courant alternatif 110-230V et vous ne comprenez pas la sécurité électrique, la bonne action est d'arrêter et demander à un spécialiste de l'aide.

## Symptômes

Les signes dangereux :

- le SSR se réchauffe considérablement ;
- le chauffage ne s'éteint pas ;
- la température monte bien que la commande soit éteinte ;
- la température monte trop vite ou sans raison ;
- le capteur de température affiche la mauvaise valeur ;
- la borne a noirci ;
- le fil ou le connecteur se réchauffe ;
- le disjoncteur ou le fusible saute ;
- le boîtier sent le plastique ou la brûlure ;
- l'appareil est dangereux à toucher ;
- le chauffage continue après l'erreur du contrôleur.

Si le chauffage ne se comporte pas comme prévu, éteignez l'alimentation.

## SSR AC et DC mélangés

Les SSRs viennent pour différents types de charge.

SSR AC est pour le courant alternatif. SSR DC est pour le courant continu.

Erreur :

- SSR AC mis sur chauffage DC ;
- SSR DC mis sur courant alternatif 230V ;
- a acheté « SSR 40A » sans comprendre ce qui est écrit sur le boîtier.

Le mauvais type de SSR peut ne pas éteindre la charge ou fonctionner dangereusement.

Avant de connecter, vérifiez :

- type de sortie : AC ou DC ;
- tension de charge autorisée ;
- courant autorisé ;
- tension d'entrée de contrôle ;
- diagramme de connexion du fabricant ;
- le dissipateur thermique est-il nécessaire.

## SSR sans dissipateur thermique

Le SSR se réchauffe pendant le fonctionnement.

Même si le boîtier dit un grand courant, cela ne signifie pas que le relais le gèrera sans dissipateur thermique dans un boîtier fermé.

Vérifiez :

- le courant de charge ;
- la chute de tension sur SSR ;
- la puissance dissipée ;
- les exigences du dissipateur thermique ;
- la température du boîtier SSR après le fonctionnement ;
- y a-t-il de l'air qui circule.

Si le SSR est si chaud qu'il est difficile à tenir, c'est une raison d'arrêter et de comprendre.

## MOSFET pour le courant alternatif 110-230V

Les modules MOSFET réguliers pour Arduino/ESP32 sont généralement pour les charges CC : 12V ou 24V.

Ils ne peuvent pas être utilisés comme un simple interrupteur pour le secteur alternatif 110-230V.

Pour la charge secteur, vous avez besoin de composants différents, isolement différent, bornes différentes, mise à la terre et compréhension de la sécurité électrique.

Si vous n'êtes pas sûr que le module sélectionné est conçu pour la charge secteur, ne le connectez pas au secteur.

## Pas de fusible

Un fusible ne rend pas l'appareil complètement sûr, mais il limite les conséquences de certaines défaillances.

Mauvaises idées :

- « Je vais l'ajouter plus tard » ;
- « l'alimentation se protégera elle-même » ;
- « mon chauffage est petit » ;
- « si le fusible saute, je mettrai un plus gros ».

Le fusible est sélectionné pour le circuit, le câblage et la charge. Il ne peut pas être augmenté juste parce qu'il saute.

Si le fusible saute, trouvez la cause.

## Pas de protection thermique indépendante

Le firmware et le capteur de température ne sont pas la seule protection.

Pour le chauffage, la protection matérielle indépendante est utile :

- thermostat ;
- fusible thermique ;
- commutateur bimétallique ;
- interruption d'alimentation du chauffage d'urgence séparée.

Une telle protection doit fonctionner indépendamment du contrôleur et du firmware.

Si le contrôleur se bloque, la broche reste dans l'état activé, le SSR échoue ou le capteur se déconnecte, la protection matérielle peut être la dernière ligne de défense.

## Capteur de température mal monté

Le chauffage est contrôlé par la rétroaction du capteur.

Si le capteur :

- est déconnecté ;
- est mal appuyé ;
- est au mauvais endroit ;
- n'a pas de contact thermique ;
- affiche la température de l'air au lieu du chauffage ;
- le mauvais type est sélectionné dans le firmware ;

le contrôleur peut continuer à chauffer car il voit la mauvaise température.

Le mauvais contact thermique est l'une des erreurs les plus dangereuses dans les systèmes de chauffage.

## Puissance du chauffage incorrecte

La puissance du chauffage doit être calculée avant la connexion.

Exemple :

```text
24V 120W -> 5A
24V 240W -> 10A
230V 300W -> environ 1.3A
```

Pour les chauffages basse tension puissants, le courant devient rapidement grand. Cela nécessite des fils appropriés, des bornes, un MOSFET/SSR et une alimentation.

Pour les chauffages secteur, le courant est moins mais le risque de choc est beaucoup plus élevé.

## Bornes et fils faibles

Une borne qui « tient un peu » peut se réchauffer sous le courant.

Raisons :

- mauvais contact ;
- isolant serré ;
- fil trop mince ;
- borne non évaluée pour le courant ;
- fil torsadé sans ferrule s'effiloche ;
- vis desserrée par la chaleur et la vibration.

La borne noircie, l'odeur, le chauffage ou le ramollissement du plastique autour est une raison d'éteindre l'appareil.

## Ce à ne pas faire

Vous ne pouvez pas :

- tenir ouverte la partie secteur sous tension ;
- changer les fils sous tension ;
- utiliser le module Arduino MOSFET pour le courant alternatif 230V ;
- utiliser le SSR sans dissipateur thermique si nécessaire ;
- désactiver la protection thermique ;
- court-circuiter le thermostat d'urgence ;
- augmenter le fusible « pour qu'il ne saute pas » ;
- laisser le chauffage sans surveillance en premier test ;
- utiliser le montage PLA près du chauffage.

## Ce à vérifier

Avant le premier chauffage :

1. Tension du chauffage.
2. Puissance et courant.
3. Type de commutateur d'alimentation : MOSFET, SSR AC, SSR DC, relais.
4. Marge de courant.
5. Dissipateur thermique du SSR ou MOSFET, si nécessaire.
6. Fusible.
7. Mise à la terre, si nécessaire.
8. Bornes et fils.
9. Montage du capteur de température.
10. « sensor_type » correct dans le firmware.
11. « min_temp » et « max_temp ».
12. Protection thermique indépendante.
13. Comportement quand le contrôleur est éteint.
14. Température du terminal et du SSR après un test bref.

## Points clés

- Le chauffage ne peut pas être testé comme une charge petite ordinaire.
- SSR AC et SSR DC sont des appareils différents.
- Le SSR nécessite souvent un dissipateur thermique.
- Le module MOSFET pour les charges CC ne fonctionne pas pour le courant alternatif 110-230V.
- Le capteur de température doit être monté fermement au bon endroit.
- La protection thermique du matériel doit être indépendante du firmware.
- S'il y a une odeur, le chauffage du terminal ou un comportement de chauffage inhabituel, éteignez l'alimentation.

## Références

- [Klipper Configuration Reference : verify_heater](https://www.klipper3d.org/Config_Reference.html#verify_heater) - vérification officielle du chauffage et vérification du capteur de température par taux de hausse et erreur accumulée.
- [Tom's Hardware : Comment corriger la fuite thermique de l'imprimante 3D](https://www.tomshardware.com/3d-printing/how-to-fix-3d-printer-thermal-runaway) - vérification du thermisteur, de la cartouche de chauffage, du ventilateur, de l'alimentation et du câblage lors d'une fuite thermique.
- [Marlin Configuration : Plages de température et protection thermique](https://marlinfw.org/docs/configuration/configuration.html#temperature-ranges) - « MINTEMP », « MAXTEMP » et protection thermique dans le cadre de la sécurité.
- [Sensata/Crydom SSR Heat Sink Selection](https://www.sensata.com/sites/default/files/a/sensata-ssr-heat-sink-selection-white-paper.pdf) - pourquoi le SSR nécessite le calcul thermique et le dissipateur thermique à courants significatifs.
- [Omron : Solid State Relay Basics](https://components.omron.com/us-en/products/basic-knowledge/relays/solid-state-relays) - informations de base sur le SSR, l'application, le chauffage et les différences avec les relais mécaniques.
