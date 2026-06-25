# Erreurs de câblage

Le câblage casse souvent plus l'appareil que l'électronique elle-même.

Une mauvaise connexion, une polarité inversée ou une mauvaise borne peut ressembler à une erreur de firmware, capteur ou contrôleur.

## Symptômes

Les signes typiques de problèmes de câblage :

- l'appareil fonctionne parfois, puis ne fonctionne pas ;
- la carte n'est détectée que quand le câble est bougé ;
- les capteurs affichent des ordures ;
- la température saute ;
- le ventilateur démarre par intermittence ;
- l'USB s'arrête ;
- la borne se réchauffe ;
- le fil noircit ou sent ;
- le module fonctionne sur le banc mais ne fonctionne pas dans le boîtier ;
- après la fermeture du capot, l'appareil s'arrête.

Si un symptôme change quand le fil est bougé, d'abord vérifiez le câblage.

## Plus et moins inversés

La polarité ne peut pas être vérifiée « par couleur ».

Le fil rouge est souvent plus, le fil noir souvent moins, mais ce n'est pas une garantie. Dans un appareil DIY, le constructeur précédent ou vous-même pouvez avoir mélangé les couleurs.

Avant de connecter :

- vérifiez les marquages de la carte ;
- vérifiez le pinout du module ;
- mesurez la tension avec un multimètre ;
- vérifiez où est « + » et où est « GND » ;
- ne connectez pas le module si le pinout n'est pas clair.

La polarité inversée peut instantanément détruire une carte, un capteur, un ventilateur ou un CC-CC.

## Pas de masse commune

La masse commune est nécessaire quand un module est alimenté séparément et le signal vient du contrôleur.

Exemples :

- servo avec alimentation 5V séparée ;
- module MOSFET pour ventilateur ;
- ventilateur PWM 4 broches ;
- HX711 ;
- module RFID ;
- capteur externe.

Sans la « GND » commune, le signal peut ne pas avoir de sens. L'appareil peut ne pas répondre, saccader ou fonctionner instable.

## Mauvais contact en borne

La borne peut sembler serrée, mais tenir le fil mal.

Raisons :

- le fil n'est pas complètement inséré ;
- l'isolation est serrée au lieu du conducteur ;
- le fil torsadé s'effiloche ;
- la vis s'est desserrée ;
- la borne n'est pas évaluée pour le courant ;
- le fil est trop mince ou trop épais pour la borne ;
- pas de ferrule où elle est nécessaire.

Le mauvais contact cause le chauffage. Le chauffage aggrave le contact. C'est un cycle dangereux.

Après un test bref sous charge, vérifiez si les bornes et connecteurs se réchauffent.

## Dupont pas pour la charge d'alimentation

Les fils Dupont sont pratiques pour les breadboards et les signaux faibles.

Mais ils ne peuvent pas être définis comme le câblage d'alimentation normal pour :

- chauffages ;
- ventilateurs puissants ;
- bandes LED ;
- servos avec grand courant ;
- alimentation de l'appareil ;
- courant alternatif 110-230V.

Dupont peut tenir mal, avoir une petite zone de contact et se réchauffer aux courants pour lesquels il n'est pas conçu.

Pour la partie alimentation, vous avez besoin des bonnes bornes, connecteurs, section de fil et soulagement de contrainte.

## TX et RX

Pour UART, souvent le câblage croisé est nécessaire :

- « TX » d'un appareil à « RX » d'un autre ;
- « RX » d'un appareil à « TX » d'un autre ;
- « GND » commune.

Erreurs typiques :

- connecté « TX » à « TX » ;
- connecté « RX » à « RX » ;
- oublié « GND » ;
- a choisi une mauvaise vitesse ;
- les niveaux de logique ne correspondent pas : 5V et 3.3V.

Si UART ne fonctionne pas, d'abord vérifiez « TX/RX/GND », puis vitesse et paramètres.

## I2C et SPI

Pour I2C :

- « SDA » doit aller à « SDA » ;
- « SCL » doit aller à « SCL » ;
- besoin de « GND » commune ;
- l'adresse de l'appareil ne doit pas entrer en conflit ;
- les fils doivent être courts.

Pour SPI :

- « MOSI », « MISO », « SCK », « CS » doivent correspondre au pinout ;
- chaque appareil a son propre « CS » ;
- besoin de « GND » commune ;
- les fils longs peuvent casser la connexion.

RFID RC522 confond souvent les gens : la broche « SDA » sur la carte peut signifier « SS/CS » pour SPI, pas « SDA » I2C.

## Fils secteur et signal

Les fils courant alternatif 110-230V, la charge CC et les signaux faibles ne doivent pas être posés au hasard dans un bundle.

Problèmes :

- interférence ;
- chauffage ;
- endommagement de l'isolant ;
- risque de toucher la partie secteur ;
- diagnostic difficile ;
- danger pour l'utilisateur.

La partie secteur doit être séparée physiquement. Les capteurs basse tension, UART/I2C/SPI et les fils thermisteur sont mieux exécutés séparément des fils de puissance du chauffage.

## Brins exposés

Un fil exposé en dehors d'une borne est un mauvais signe.

Il peut :

- toucher une borne voisine ;
- court-circuiter le boîtier ;
- se retrouver sous le capot ;
- heurter le ventilateur ;
- créer un danger lors de la maintenance.

Après le serrage en borne, aucun long brin nu ne doit dépasser.

## Ce à vérifier

Mini-liste de contrôle :

1. Polarité de l'alimentation.
2. « GND » commune.
3. Correspondance du pinout.
4. Qualité de la borne.
5. Pas d'isolant serré au lieu du conducteur.
6. Pas de brins exposés.
7. Les fils ne sont pas tendus.
8. Le capot ne pince pas le câble.
9. Les fils secteur et signal sont séparés.
10. Le connecteur est évalué pour le courant.
11. L'appareil ne change pas de comportement quand le fil est bougé.

## Ce à ne pas faire

Vous ne pouvez pas :

- changer les fils sous tension ;
- tenir ouverte la partie secteur sur le banc ;
- utiliser Dupont pour le chauffage ;
- serrer le fil torsadé afin que certains brins restent détachés ;
- tordre les fils d'alimentation sans connexion appropriée ;
- ignorer une borne qui se réchauffe ;
- considérer « fonctionne parfois » comme normal.

## Points clés

- Si l'appareil répond au mouvement du fil, c'est un problème de câblage.
- La polarité est vérifiée avec un multimètre, pas par couleur.
- La « GND » commune est nécessaire pour la plupart des modules externes avec alimentation séparée.
- Dupont convient aux breadboards et signaux, mais pas pour la charge d'alimentation.
- Les fils secteur et basse tension doivent être séparés.
- La borne qui se réchauffe est une raison d'arrêter, pas de continuer le test.

## Références

- [SparkFun : Conseils de dépannage](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - vérification élémentaire des connexions, continuité, cycle d'alimentation et chauffage.
- [SparkFun : Communication série](https://learn.sparkfun.com/tutorials/serial-communication) - UART, TX/RX et communication série.
- [SparkFun : I2C](https://learn.sparkfun.com/tutorials/i2c) - les lignes « SDA », « SCL », les adresses et les erreurs typiques I2C.
- [SparkFun : Interface de périphérique série](https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi) - les lignes SPI, « MOSI », « MISO », « SCK », « SS/CS ».
- [FRC Design : Design for 3D Printing](https://www.frcdesign.org/design-handbook/structure/design-for-3d-printing/) - conseils pratiques pour les cas électroniques : les trous de fil, la ventilation, l'accès aux ports et le retrait du service des composants.
