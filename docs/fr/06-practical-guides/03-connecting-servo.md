# Connexion d'un Servo

Un servo est un petit moteur avec une boîte de vitesses et l'électronique de contrôle. Vous pouvez lui dire à quelle position faire tourner l'arbre.

Dans les appareils de type iDryer, un servo peut ouvrir un amortisseur, déplacer un petit loquet, appuyer sur un interrupteur mécanique ou rediriger le flux d'air.

L'erreur principale avec les servos : penser que c'est une « petite chose » et vous pouvez l'alimenter à partir de n'importe quelle broche 5V du contrôleur. Un servo peut tirer un courant significatif, surtout au démarrage, mouvement soudain, ou quand le mécanisme se bloque.

## Trois fils

Un servo de loisir typique a trois fils :

- alimentation : généralement `5V` ou `6V` ;
- masse : `GND` ;
- signal : impulsions de contrôle du contrôleur.

Couleurs courantes :

- rouge - alimentation ;
- noir ou brun - masse ;
- jaune, orange ou blanc - signal.

Mais vous ne pouvez pas faire confiance aveuglément aux couleurs. Différents fabricants peuvent utiliser différents schémas de couleurs. Avant de connecter, vérifiez le marquage, la page produit, ou la fiche technique.

## Alimentation séparée, signal séparé

Le fil de signal n'alimente pas le servo. Il dit seulement au servo où tourner.

Le servo tire l'énergie du fil d'alimentation.

La logique correcte est :

- le contrôleur ne fournit que le signal de contrôle ;
- le servo est alimenté par une source 5V/6V qui peut gérer son courant ;
- la masse du contrôleur et la masse de l'alimentation du servo sont connectées ensemble.

![Code de couleur du fil du servo](../../../img/03-common-components/06-servo-color-code.jpg)

*Source: [SparkFun Electronics](https://learn.sparkfun.com/tutorials/hobby-servo-tutorial/all), CC BY-SA 4.0*

## Pourquoi vous ne pouvez pas alimenter à partir d'une faible 5V

De nombreuses cartes ont une broche 5V. Cela ne signifie pas qu'un servo peut être alimenté en toute sécurité à partir d'elle.

En se déplaçant, un servo peut tirer beaucoup plus de courant que sa taille le suggère. Si l'alimentation est insuffisante, les symptômes typiques apparaissent :

- le contrôleur redémarre ;
- l'écran scintille ;
- la connexion USB tombe ;
- le servo saccade ;
- Wi-Fi sur ESP32 tombe ;
- le servo bourdonne mais ne bouge pas ;
- l'affaissement d'alimentation au démarrage du mouvement.

Pour un petit servo, l'alimentation fournie par la carte fonctionne parfois si la carte et la source sont explicitement évaluées pour ce courant. Mais pour un vrai appareil avec un amortisseur, un loquet, ou un mécanisme, il est préférable d'utiliser une DC-DC 5V/6V séparée ou une alimentation avec une marge.

## Masse commune

Si le servo est alimenté par une source séparée, une masse commune est nécessaire.

Sans masse commune, le contrôleur et le servo n'ont pas de niveau de signal commun. Le servo peut ne pas répondre, peut saccader, ou peut se comporter aléatoirement.

Connexion simple :

1. `+5V` ou `+6V` de la source d'alimentation va à l'alimentation du servo.
2. `GND` de la source d'alimentation va à la masse du servo.
3. Le `GND` du contrôleur est connecté à la même masse.
4. La broche PWM/GPIO du contrôleur va au fil de signal du servo.

L'alimentation du servo et l'alimentation du contrôleur peuvent être différentes, mais la masse doit être commune.

## Quel signal est nécessaire

Un servo de loisir positionnel typique est contrôlé par des impulsions.

Signal typique :

- impulsion à peu près tous les `20 ms` ;
- environ `1 ms` - une extrémité de la plage ;
- environ `1.5 ms` - milieu ;
- environ `2 ms` - l'autre extrémité de la plage.

Ce n'est pas un PWM typique pour la luminosité LED ou la vitesse du ventilateur. Ici, la largeur d'impulsion en microsecondes importe.

Les limites réelles d'un servo spécifique peuvent différer. Certains fonctionnent en toute sécurité pas de 0 à 180 degrés mais moins. Les positions extrêmes doivent donc être testées avec soin.

## Ne pas bloquer un servo contre le mécanisme

Un servo essaie de maintenir la position commandée.

Si un amortisseur frappe le boîtier, un bras se bloque, ou le mécanisme atteint une butée physique avant la fin de la commande, le servo continue à pousser. À ce moment, le courant augmente, le moteur chauffe, la boîte de vitesses s'use.

C'est particulièrement critique pour les amortisseurs et les loquets.

Avant le fonctionnement permanent, vérifiez :

- le mécanisme se déplace librement sur toute la plage ;
- pas de mauvais alignement ;
- pas de blocage des liaisons ;
- le servo ne bourdonne pas en position finale ;
- les angles extrêmes dans le firmware ne forcent pas le mécanisme dans un arrêt ;
- avec l'alimentation coupée, l'appareil reste sûr ou revient via le ressort, comme prévu.

Si un servo bourdonne au repos, cela signale souvent une charge, un arrêt, ou une géométrie de levier incorrecte.

## Courant de démarrage et de blocage

Un servo a un courant de fonctionnement normal et un courant quand l'arbre est bloqué. Ce dernier s'appelle souvent courant de blocage.

Le courant de blocage apparaît quand le servo essaie de se déplacer mais l'arbre est bloqué ou le mécanisme est trop lourd.

Ce mode cause souvent :

- affaissement d'alimentation ;
- redémarrage du contrôleur ;
- chauffage du fil ;
- surchauffe du DC-DC ;
- rupture de la boîte de vitesses.

Si la fiche technique liste le courant de blocage, choisissez la source d'alimentation en tenant compte de cette valeur et de la marge de sécurité. S'il n'y a pas de fiche technique, vous ne pouvez pas supposer qu'un servo est sûr de fonctionner « à vue ».

## Condensateur à côté du servo

Parfois, un condensateur électrolytique entre `+5V` et `GND` à côté du servo aide.

Il ne remplace pas une alimentation appropriée, mais peut lisser un affaissement bref au démarrage du mouvement.

Pour un petit servo : des centaines de microfarads, comme `470 uF` ou plus, avec calibre de tension au-dessus de la tension d'alimentation.

La polarité du condensateur électrolytique importe :

- plus du condensateur vers `+5V` ;
- moins du condensateur vers `GND`.

Si l'appareil doit être fiable, d'abord choisissez une alimentation et un câblage appropriés, puis utilisez un condensateur comme mesure supplémentaire.

## Exemple de configuration Klipper

Dans Klipper, un servo est décrit avec une section `[servo]`.

Exemple :

```ini
[servo chamber_damper]
pin: PA8
maximum_servo_angle: 180
minimum_pulse_width: 0.001
maximum_pulse_width: 0.002
initial_angle: 90
```

Commandes :

```gcode
SET_SERVO SERVO=chamber_damper ANGLE=0
SET_SERVO SERVO=chamber_damper ANGLE=90
SET_SERVO SERVO=chamber_damper ANGLE=180
```

Les noms de broches ici sont typiques. Dans un vrai appareil, vérifiez le brochage de votre carte.

Pour la mécanique, ne commencez pas avec `0` et `180` tout de suite. D'abord tester une plage sûre comme `60`, `90`, `120`, puis élargissez les angles.

## Exemple de logique Arduino/ESP32

L'approche Arduino utilise généralement la bibliothèque Servo :

```cpp
#include <Servo.h>

Servo damper;

void setup() {
  damper.attach(9);
  damper.write(90);
}

void loop() {
}
```

Ceci est juste un exemple de logique de signal. L'alimentation du servo doit toujours être conçue séparément. Même si le fil de signal est connecté à Arduino ou ESP32, le moteur du servo ne doit pas surcharger l'alimentation du contrôleur.

## Ce qu'il faut vérifier après la connexion

Avant le montage dans le boîtier :

- le servo reçoit la tension correcte ;
- la source d'alimentation peut gérer le courant du servo ;
- la masse du contrôleur et la masse du servo sont communes ;
- le fil de signal est connecté à la bonne broche ;
- le servo se déplace dans la bonne direction ;
- les angles extrêmes ne cassent pas le mécanisme ;
- le mécanisme ne se bloque pas ;
- le servo ne bourdonne pas en continu ;
- les fils ne s'accrochent pas au levier ou aux engrenages ;
- l'alimentation ne s'affaisse pas après le mouvement ;
- le contrôleur ne redémarre pas.

Testez la mécanique sans charge et sous charge réelle. Un amortisseur qui se déplace facilement à la main peut se bloquer après le montage dans le boîtier.

## Erreurs courantes

- alimentation du servo depuis GPIO ;
- alimentation du servo depuis une broche 5V faible de la carte ;
- oubli de masse commune ;
- confiance aux couleurs des fils sans vérification ;
- connexion de l'alimentation à l'envers ;
- utilisation de fils trop fins ;
- pas de comptabilité pour le courant de démarrage et de blocage ;
- forcer le servo à pousser contre une butée mécanique ;
- utilisant angle `0` ou `180` quand le mécanisme réel fonctionne en toute sécurité seulement dans une plage plus petite ;
- montage du servo près de la chaleur sans vérification de la température de fonctionnement ;
- traiter un servo de rotation continue comme un servo positionnel régulier.

## Points clés

- Un servo a trois lignes : alimentation, masse et signal.
- Le signal n'alimente pas le servo.
- Les appareils réels ont souvent besoin d'une source d'alimentation 5V/6V séparée.
- La masse du servo et la masse du contrôleur doivent être communes.
- La charge la plus dangereuse est le blocage ou le blocage mécanique.
- Les angles extrêmes nécessitent une sélection soignée, pas immédiatement `0` et `180`.
- Si le contrôleur redémarre quand le servo bouge, d'abord vérifiez l'alimentation et la masse commune.

## Lectures connexes

- [Klipper Configuration Reference: Servo](https://www.klipper3d.org/Config_Reference.html#servo) - section officielle `[servo]`, `SET_SERVO`, angles et largeur d'impulsion.
- [SparkFun: Hobby Servo Tutorial](https://learn.sparkfun.com/tutorials/hobby-servo-tutorial/introduction) - explication basique du servo de loisir, trois fils et contrôle d'impulsion.
- [SparkFun: Servo Trigger Hookup Guide](https://learn.sparkfun.com/tutorials/servo-trigger-hookup-guide/servo-motor-background) - ventilation de la connexion électrique, couleurs de fil typiques et mécanique du servo de loisir.
- [Adafruit: Arduino Lesson 14. Servo Motors](https://learn.adafruit.com/adafruit-arduino-lesson-14-servo-motors?view=all) - exemple pratique de connexion, comportement d'affaissement d'alimentation et condensateur à côté du servo.
- [Arduino Servo Library Reference](https://www.arduino.cc/reference/en/libraries/servo/) - référence officielle de la bibliothèque Servo pour l'approche Arduino.
