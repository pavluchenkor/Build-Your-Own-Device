# Vérification d'une thermistance

Une thermistance est un capteur de température qui change de résistance lorsqu'elle est chauffée ou refroidie.

Dans les imprimantes 3D, les sèche-linge et les chaufferettes de chambre, le type le plus courant est une thermistance NTC nominale de `100K`. NTC signifie que la résistance diminue à mesure que la température augmente.

Vous devez vérifier une thermistance si:

- les lectures de température sont irréalistes;
- la température saute;
- le chauffage entre en erreur;
- le firmware signale `MINTEMP`, `MAXTEMP`, `Thermal runaway`, ou similaire;
- la thermistance a été remplacée, déplacée ou re-serrée;
- l'appareil a été assemblé pour la première fois.

## Première, couper l'alimentation

La résistance n'est mesurée que sur les circuits désexcités.

Avant la vérification:

1. Éteindre l'appareil.
2. Débrancher l'alimentation du réseau ou de la source d'alimentation.
3. Attendre que le chauffage refroidisse.
4. Débrancher la thermistance de la carte si vous devez mesurer le capteur lui-même.

Si vous mesurez la résistance tandis que la thermistance est connectée à la carte, les lectures peuvent être déformées par d'autres composants du circuit. Si vous mesurez la résistance sous tension, vous pouvez endommager le multimètre ou la carte.

## Ce qu'une NTC 100K devrait avoir

Une NTC typique `100K` a une résistance d'environ `100 kOhm` à `25°C`.

Cela ne signifie pas que le multimètre affichera toujours exactement `100.0 kOhm`.

Il est normal que la lecture diffère légèrement à température ambiante:

- dans une pièce froide, la résistance sera plus élevée;
- dans une pièce chaude, la résistance sera plus basse;
- différents types de thermistances ont des tables différentes;
- les longs fils et les mauvais contacts peuvent affecter la mesure.

La vérification principale est simple: une NTC 100K à température ambiante devrait lire des dizaines ou environ cent kilohms, pas `0 Ohm` ou `OL`.

## Mesure avec un multimètre numérique

Réglez votre multimètre en mode résistance `Ohm`.

Si votre multimètre n'est pas automatique, sélectionnez une plage supérieure à `100 kOhm`, comme `200 kOhm` ou `2 MOhm`.

Puis:

1. Débrancher la thermistance de la carte.
2. Toucher les sondes du multimètre aux deux fils de thermistance.
3. Ne pas tenir les extrémités métalliques des sondes et des fils en même temps: votre corps peut ajouter une résistance parallèle.
4. Attendre que la lecture se stabilise.
5. Enregistrer la valeur.

![Multimètre numérique pour mesurer la résistance de thermistance](../../img/05-tools/02-digital-multimeter.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Aneng_AN870_multimeter_02.jpg), Électricien à la retraite, CC0 Domaine public*

## Test thermique rapide avec votre doigt

Après la mesure à température ambiante, vous pouvez réchauffer délicatement le capteur avec vos doigts.

Pour une thermistance NTC, la résistance devrait commencer à diminuer.

Par exemple:

- était autour de `100 kOhm` à température ambiante;
- est devenue inférieure après réchauffement du doigt.

Les nombres exacts n'ont pas d'importance ici. La direction du changement a de l'importance.

Si la résistance ne change pas du tout, saute aléatoirement ou disparaît lorsque le fil bouge, le problème peut être dans le capteur, le fil, le crimp ou le connecteur.

## Rupture et court-circuit

Un multimètre aide à distinguer rapidement un capteur normal d'une défaillance évidente.

Signes typiques:

- `OL`, `dépassement`, `1` sur le côté gauche de l'écran, ou résistance infinie - circuit ouvert;
- près de `0 Ohm` - court-circuit;
- la valeur saute considérablement quand le fil bouge - mauvais contact ou conducteur rompu;
- valeur autour de `100 kOhm` à température ambiante et diminue avec le chauffage - semble une NTC 100K saine.

Différents multimètres utilisent des désignations différentes pour le circuit ouvert. Habituellement c'est `OL` ou une valeur au-delà de la plage sélectionnée.

## Vérification du câblage

La thermistance peut être fine tandis que le problème se situe dans le câblage.

Vérifier:

- le connecteur est complètement inséré;
- les broches ne sont pas sorties du boîtier du connecteur;
- les fils ne sont pas effilochés;
- pas de dommages à l'isolation près du chauffage;
- pas de tension du fil quand les axes ou le couvercle bougent;
- le câble ne monte pas directement à côté des fils d'alimentation du chauffage sans raison;
- l'emplacement du crimp est sécurisé.

Si les lectures changent quand vous bougez le fil, ce n'est pas une "caractéristique du capteur". C'est un problème de contact qui doit être réparé avant d'allumer le chauffage.

## Vérification dans Klipper

Dans Klipper, le type de capteur est défini dans la configuration.

Exemple pour un capteur de température de chambre typique:

```ini
[temperature_sensor chamber]
sensor_type: Generic 3950
sensor_pin: PA0
min_temp: 0
max_temp: 100
```

Exemple pour un chauffage de chambre:

```ini
[heater_generic chamber_heater]
gcode_id: C
heater_pin: PA8
sensor_type: Generic 3950
sensor_pin: PA0
control: watermark
min_temp: 0
max_temp: 90
```

Les noms de broches ici sont typiques. Dans un appareil réel, vérifiez la disposition de votre carte.

Important: `sensor_type` doit correspondre au capteur réel. Deux thermistances peuvent sembler identiques mais avoir des tables différentes. Si vous choisissez le mauvais type, la température peut être notablement inexacte, en particulier dans la plage de chauffage de travail.

## Ce à surveiller dans l'interface

Après la connexion, vérifiez la température dans l'interface Klipper, Mainsail, Fluidd ou autre interface utilisateur.

À température ambiante, la lecture devrait être proche de la température réelle de la pièce.

Signes suspects:

- lit significativement plus bas que la réalité;
- lit significativement plus haut que la réalité;
- la température saute de plusieurs degrés;
- la température change quand vous bougez le fil;
- la température n'augmente pas quand le chauffage est allumé;
- la température augmente très lentement;
- la température augmente bien que le chauffage soit éteint.

Si le capteur se trouve sur le chauffage, ne commencez pas un chauffage prolongé jusqu'à ce que les lectures semblent raisonnables.

## Erreurs de firmware

Dans le firmware de l'imprimante 3D, les erreurs de température ne sont pas une question mineure mais une partie de la sécurité.

Pour un circuit typique avec une NTC et un pull-up intégré:

- une défaillance du capteur ressemble souvent à une température trop basse ou `MINTEMP`;
- un court-circuit ressemble souvent à une température trop élevée ou `MAXTEMP`;
- un mauvais contact thermique peut causer `Heating failed` ou `Thermal runaway`;
- un refroidissement puissant du bloc de chauffage peut causer une erreur car la température n'augmente pas assez rapidement ou ne se maintient pas.

Les noms d'erreur dépendent du firmware, mais la signification est la même: le contrôleur ne fait plus confiance à la température ou voit que le chauffage ne fonctionne pas comme prévu.

N'désactivez pas la protection thermique juste pour "vérifier". Si la protection se déclenche, cherchez d'abord la cause dans le capteur, le câblage, le montage, le chauffage, les paramètres PID et le refroidissement.

## Contact thermique

Une thermistance électriquement fonctionnelle ne garantit pas une température correcte.

Le capteur doit transférer bien la chaleur du partie qu'il mesure.

Vérifier:

- le capteur s'assied complètement dans la douille ou le trou;
- il y a un serrage normal;
- pas d'écart entre le capteur et la surface;
- la pâte thermique n'a pas séché ni écaillée si elle est utilisée;
- les attaches ne sont pas lâches;
- le capteur n'est pas sorti de son siège;
- les fils ne tirent pas le capteur.

Un mauvais contact est dangereux car le capteur lit une température inférieure à la réalité. Le contrôleur continue de chauffer tandis que la pièce réelle peut déjà être surchauffée.

## Mini-checklist

Avant le premier chauffage:

- la résistance de la thermistance ressemble à ce qui est attendu;
- la résistance NTC diminue avec le chauffage des doigts;
- pas de circuit ouvert ou court-circuit;
- les fils ne réagissent pas avec des sauts quand ils sont bougés;
- le connecteur est inséré correctement;
- le `sensor_type` correct est choisi dans le firmware;
- la température en interface ressemble à la température ambiante;
- le capteur est solidement monté au bon endroit;
- `min_temp` et `max_temp` sont définis raisonnablement pour l'appareil.

## Erreurs courantes

- mesure de la résistance avec la carte sous tension;
- ne pas déconnecter le capteur de la carte et obtenir des valeurs étranges;
- confusion d'une thermistance `100K` avec un autre type de capteur;
- choix du mauvais `sensor_type`;
- voir `OL` et penser que cela signifie "100K";
- assumer que toute NTC 100K est identique;
- laisser la thermistance lâche à côté du chauffeur;
- surserrer une thermistance en verre avec une vis;
- tirer sur le fil de sorte que le capteur sorte de la douille;
- désactivation de la protection thermique au lieu de corriger la cause de l'erreur.

## Points clés

- La résistance ne se mesure que sur les circuits désexcités.
- Un NTC 100K typique est environ `100 kOhm` à `25°C`.
- Quand chauffé, la résistance NTC diminue.
- `OL` signifie généralement un circuit ouvert, près de `0 Ohm` signifie court-circuit.
- Le firmware doit avoir le type de capteur correct sélectionné.
- Un bon contact thermique est aussi important qu'un câblage fonctionnel.
- Ne démarrez pas le chauffage si les lectures de température semblent fausses.

## Lectures connexes

- [Référence de configuration Klipper: Capteurs de température](https://www.klipper3d.org/Config_Reference.html#temperature-sensors) - paramètres officiels `sensor_type`, `sensor_pin`, `pullup_resistor` et liste des thermistances courantes.
- [Configuration Marlin: Plages de température et protection thermique](https://marlinfw.org/docs/configuration/configuration.html#temperature-ranges) - explication de `MINTEMP`, `MAXTEMP` et de la protection contre le démarrage thermique.
- [Marlin Troubleshooting: Heating Failed](https://marlinfw.org/docs/basics/troubleshooting.html#heating-failed) - causes typiques d'erreurs de chauffage: thermistance, montée lente de température, démarrage thermique.
- [RepRap Wiki: Thermistance](https://reprap.org/wiki/Thermistor) - description de base des thermistances NTC/PTC et vérification de la résistance à température ambiante.
- [Fluke: Comment mesurer la résistance avec un multimètre numérique](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-resistance) - procédure sûre de mesure de la résistance avec un multimètre numérique.
