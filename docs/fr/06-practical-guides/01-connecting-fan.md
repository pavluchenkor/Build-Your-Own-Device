# Connexion d'un ventilateur

Un ventilateur semble être un composant simple : appliquer de l'énergie et il tourne.

En pratique, les problèmes proviennent de quatre choses :

- sélection d'un ventilateur avec une tension incorrecte;
- connexion à une sortie de contrôleur faible;
- mauvaise compréhension des différences entre les ventilateurs 2 broches, 3 broches et 4 broches;
- placement du ventilateur où il manque de pression en raison d'un filtre, d'une grille ou d'un conduit.

Dans les appareils de type iDryer, un ventilateur est généralement nécessaire pour la circulation de l'air, le refroidissement du réchauffeur, l'échappement de la chambre, la filtration ou le refroidissement de l'électronique.

## Ce qu'il faut vérifier avant la connexion

Avant la connexion, trouvez les paramètres du ventilateur :

- tension : `5V`, `12V` ou `24V`;
- courant ou puissance;
- type de connecteur : 2 broches, 3 broches ou 4 broches;
- capacité de contrôle PWM;
- présence d'un signal tachométrique;
- flux d'air;
- pression statique;
- niveau sonore;
- température de fonctionnement.

Ces données se trouvent sur une étiquette, une page produit ou dans la fiche technique.

Par exemple, une fiche technique de ventilateur contient généralement non seulement la tension et le courant, mais aussi le flux d'air, la pression statique, le bruit `SPL dB(A)`, la température de fonctionnement et la durée de vie. Ceux-ci sont plus utiles que de sélectionner un ventilateur uniquement par taille.

## Ne pas alimenter un ventilateur depuis GPIO

GPIO d'un contrôleur est un signal de contrôle, pas une sortie de puissance.

Ne jamais alimenter un ventilateur directement à partir de GPIO. Cela peut endommager le contrôleur ou causer des redémarrages au démarrage du ventilateur.

La logique correcte est :

- le ventilateur reçoit de l'énergie d'une alimentation électrique ou d'une sortie de puissance de la carte;
- le contrôleur ne gère que marche/arrêt ou vitesse;
- si un module MOSFET externe est utilisé, l'alimentation `GND` et le contrôleur `GND` doivent être communs.

![MOSFET canal N en mode commutation (bas-côté) pour le contrôle de charge](../../img/01-electronics-basics/02-nmos-switch-operation.png)

*Source : [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:NMOS_PWR_WHOLE.PNG), KjellElec, CC BY-SA 4.0*

## Option la plus simple : ventilateur 2 broches

Un ventilateur 2 broches a généralement seulement :

- `+` alimentation;
- `-` alimentation.

S'il s'agit d'un ventilateur 24V, le connecter à 24V. S'il s'agit d'un ventilateur 12V, le connecter à 12V.

Pour un contrôle simple marche/arrêt, vous pouvez utiliser :

- une sortie ventilateur dédiée sur la carte, si évaluée pour la tension et le courant nécessaires;
- un module MOSFET externe pour les charges DC;
- un contrôleur de ventilateur séparé.

Si le ventilateur doit tourner en continu, il peut être connecté directement à une alimentation appropriée via un fusible ou une ligne d'alimentation protégée. Mais dans un appareil avec réchauffeur, il est souvent préférable que le ventilateur soit contrôlé par le contrôleur dans le cadre de la logique de sécurité.

## Ventilateur 3 broches

Un ventilateur 3 broches a généralement :

- alimentation;
- masse;
- signal tachométrique.

Le signal tachométrique vous permet de surveiller le RPM du ventilateur. Il ne contrôle pas la vitesse par lui-même.

La vitesse d'un ventilateur 3 broches est généralement modifiée en réduisant la tension d'alimentation ou le PWM sur la ligne d'alimentation, si la carte spécifique et le ventilateur le supportent. Mais cette méthode peut fonctionner moins bien que le PWM 4 broches approprié : le ventilateur peut grincer, échouer à démarrer à basse vitesse ou fonctionner de manière instable.

Si le contrôle de vitesse n'est pas nécessaire, un ventilateur 3 broches peut être utilisé comme un ventilateur 2 broches ordinaire : l'alimentation et la masse sont connectées, le fil tachométrique n'est pas utilisé.

## Ventilateur PWM 4 broches

Un ventilateur PWM 4 broches a généralement :

- masse;
- alimentation;
- signal tachométrique;
- signal de contrôle PWM.

La différence clé : l'alimentation du ventilateur est appliquée en continu, et la vitesse est définie par un signal PWM séparé.

C'est la bonne façon de contrôler les ventilateurs PWM informatiques. Ne supposez pas qu'un ventilateur 4 broches doit être contrôlé en commutant constamment l'alimentation. Pour un ventilateur PWM approprié, le signal de contrôle doit aller à une broche PWM séparate.

Les ventilateurs PWM 4 broches informatiques ont souvent une entrée de contrôle conçue pour les signaux open-collector/open-drain avec pull-up interne, pas n'importe quelle tension de GPIO. N'appliquez pas `12V` ou `24V` à la broche PWM. Vérifiez la documentation du ventilateur ; si open-drain/open-collector est requis, utilisez une sortie de transistor appropriée ou un mode GPIO.

Pour de nombreux ventilateurs PWM 4 broches, la fréquence PWM typique est autour de `25 kHz`. Certains ventilateurs fonctionnent dans une plage proche, mais à une fréquence trop basse ou trop élevée, ils peuvent se comporter de manière imprévisible : tourner à pleine vitesse, s'arrêter ou faire du bruit.

Si le fil PWM n'est pas connecté, de nombreux ventilateurs 4 broches tournent à pleine vitesse.

## GND commun / négatif commun

Si le ventilateur est alimenté par une alimentation séparée et que le signal PWM provient du contrôleur, un `GND` commun / négatif commun est nécessaire.

Sans un `GND` commun, le contrôleur et le ventilateur n'ont pas de niveau de référence commun. En conséquence, le PWM peut ne pas fonctionner ou fonctionner de manière intermittente.

Règle simple :

- l'alimentation positive du ventilateur provient d'une alimentation appropriée;
- l'alimentation négative du ventilateur est connectée au négatif de l'alimentation;
- le `GND` du contrôleur est connecté au même négatif;
- le signal de contrôle ne fonctionne qu'avec une masse commune.

## Sélection d'un ventilateur pour la tâche

Pour le refroidissement en circuit ouvert, le flux d'air est important.

Pour un filtre, un radiateur, une grille serrée, un long conduit ou un canal étroit, la pression statique est plus importante.

Donc pour un filtre de chambre d'imprimante, un ventilateur de boîtier ordinaire et silencieux peut être faible. Il soufflera bien dans l'air libre mais poussera à peine l'air à travers un filtre HEPA, une couche de charbon ou un canal étroit.

Lignes directrices :

- pour la circulation d'air libre, regarder `CFM` ou `m³/h`;
- pour les filtres, les radiateurs et les conduits, la pression statique est essentielle;
- pour un fonctionnement silencieux, regarder non seulement `dB(A)` mais aussi le montage, la grille et la vibration;
- pour une chambre chauffée, regarder la température de fonctionnement du ventilateur.

## Courant de démarrage et marge

Quand un ventilateur démarre, il peut tirer plus de courant que pendant le fonctionnement normal.

Si plusieurs ventilateurs sont connectés à une sortie, leurs courants s'ajoutent.

Vérifier :

- courant de sortie maximal de la carte;
- courant d'un ventilateur;
- courant total de tous les ventilateurs;
- au moins 50% de marge;
- échauffement des bornes, des fils et du module MOSFET pendant un fonctionnement prolongé.

Par exemple, si un ventilateur tire `0.25A`, quatre ventilateurs de ce type tirent environ `1A` sans tenir compte du courant de démarrage.

## Exemple : connexion via module MOSFET

Circuit typique pour un ventilateur 12V ou 24V :

1. Le positif de l'alimentation va au positif du ventilateur.
2. Le négatif du ventilateur va à la sortie de puissance du module MOSFET.
3. Le négatif de l'alimentation va au module MOSFET.
4. Le `GND` du contrôleur est connecté au négatif de l'alimentation.
5. La broche de contrôle du contrôleur va à l'entrée du module MOSFET.

C'est ce qu'on appelle la commutation bas-côté : le MOSFET casse le négatif de la charge.

Pour un ventilateur 2 broches simple, c'est une option standard et claire si le module MOSFET est courant évalué pour la tension et le nécessaire. Pour un ventilateur 3 broches/4 broches avec tachymètre ou entrée PWM séparée, « couper le négatif » n'est pas toujours bon : la surveillance RPM et le contrôle PWM natif généralement un `GND` commun constant.

## Exemple de configuration Klipper

Les noms de broches dans les exemples ne sont pas universels. Avant de copier, vérifiez la disposition de votre carte : un mauvais `pin` peut activer la mauvaise sortie.

Si le ventilateur est connecté à une sortie contrôlée et doit être contrôlé manuellement :

```ini
[fan_generic chamber_fan]
pin: PA8
max_power: 1.0
shutdown_speed: 0.0
kick_start_time: 0.5
off_below: 0.15
```

Contrôle :

```gcode
SET_FAN_SPEED FAN=chamber_fan SPEED=1.0
SET_FAN_SPEED FAN=chamber_fan SPEED=0.4
SET_FAN_SPEED FAN=chamber_fan SPEED=0
```

Si le ventilateur doit s'allumer en fonction de la température de la chambre :

```ini
[temperature_fan chamber_exhaust]
pin: PA8
max_power: 1.0
shutdown_speed: 0.0
kick_start_time: 2.0
off_below: 0.15
sensor_type: NTC 100K beta 3950
sensor_pin: PA0
min_temp: 0
max_temp: 80
target_temp: 45
control: watermark
```

Les noms de broches ici sont typiques. Dans un appareil réel, vérifiez la disposition de votre carte.

## Ce qu'il faut vérifier après la connexion

Avant un fonctionnement prolongé, vérifier :

- le ventilateur tourne dans la bonne direction;
- la tension correspond au ventilateur;
- le module MOSFET ne surchauffe pas;
- les bornes ne surchauffent pas;
- les fils ne sont pas trop fins pour le courant choisi;
- le ventilateur démarre après un arrêt complet;
- pas de grincement ou calage à basse vitesse;
- le flux d'air traverse la zone nécessaire, pas par-dessus;
- la grille, le filtre ou le boîtier ne limite pas le flux plus que prévu.

Si le ventilateur se trouve près d'un radiateur, testez-le à la température réelle de la chambre. Un ventilateur qui fonctionne bien sur le banc peut se dégrader rapidement dans une enceinte chaude.

## Erreurs courantes

- connexion d'un ventilateur 12V à 24V;
- connexion d'un ventilateur 24V à 12V et décision qu'il est cassé;
- alimentation d'un ventilateur depuis GPIO;
- oubli de masse commune entre contrôleur et alimentation externe;
- attendre le contrôle PWM d'un ventilateur 3 broches;
- contrôler un ventilateur PWM 4 broches en coupant l'alimentation au lieu d'utiliser la broche PWM;
- pas de prise en compte du courant total de plusieurs ventilateurs;
- choix d'un ventilateur par taille sans vérifier la pression statique;
- placement d'un ventilateur silencieux sur un filtre dense et obtention d'un flux près de zéro;
- non-vérification de la direction du flux après l'installation;
- laisser les fils non sécurisés et avoir des effilochures contre l'hélice ou le boîtier.

## Points clés

- La tension du ventilateur doit correspondre à l'alimentation.
- GPIO n'alimente pas un ventilateur, il ne le contrôle que.
- Pour l'alimentation externe, une masse commune avec le contrôleur est requise.
- Un ventilateur 2 broches est plus facile à contrôler via une sortie d'alimentation ou un MOSFET.
- 3 broches ajoute un tachymètre mais pas d'entrée PWM séparée.
- PWM 4 broches est mieux contrôlé par un signal PWM séparé, pas la commutation de puissance.
- Pour les filtres et conduits, la pression statique est plus importante qu'un beau nombre de `CFM`.
- Après l'assemblage, vérifiez non seulement la rotation mais le flux réel à travers la construction.

## Lectures connexes

- [Noctua : Configuration PWM et surveillance RPM d'un ventilateur avec microcontrôleurs](https://www.noctua.at/en/support/faqs/microcontroller-guide-pwm-setup-and-rpm-monitoring) - explication pratique de PWM 4 broches, signal RPM, masse commune et fréquence PWM typique.
- [Référence de configuration Klipper : Ventilateurs](https://www.klipper3d.org/Config_Reference.html#fans) - sections officielles `fan`, `heater_fan`, `controller_fan`, `temperature_fan` et `fan_generic`.
- [Documentation Voron : Température de la chambre et ventilateur d'échappement](https://docs.vorondesign.com/community/howto/alchemyEngine/chamber_temperature_exhaust_fan.html) - exemple de contrôle du ventilateur d'échappement de chambre par température dans Klipper.
- [DigiKey : Sélection d'un ventilateur](https://www.digikey.com/en/articles/selecting-a-fan) - sélection du ventilateur tenant compte du flux d'air, de la pression statique, de la résistance du boîtier et des filtres.
- [SANYO DENKI : Exemple de fiche technique de ventilateur DC](https://products.sanyodenki.com/en/sanace/dc/dc-fan/109P0405F601/) - exemple de paramètres réels : tension, courant, flux d'air, pression statique, bruit, température de fonctionnement et durée de vie.
