# Contrôleur Arduino

Arduino n'est pas un microcontrôleur spécifique, mais un écosystème de cartes, de bibliothèques, d'exemples et d'environnement de développement. Quand un débutant dit « Arduino », il pense généralement à Arduino Uno, Nano ou une carte compatible basée sur l'ATmega328P.

Pour l'apprentissage, Arduino reste très utile : il est facile de comprendre GPIO, les boutons, les LEDs, PWM, les entrées analogiques, I2C, SPI et les capteurs simples. Mais pour un nouveau dispositif autour d'une imprimante 3D, Arduino Uno/Nano n'est pas toujours le meilleur choix.

## Pourquoi Arduino est populaire

Les points forts d'Arduino :

- beaucoup de ressources pédagogiques ;
- EDI Arduino simple ;
- nombreuses bibliothèques prêtes à l'emploi ;
- exemples compréhensibles comme Blink ;
- pratique pour tester rapidement un capteur sur la table ;
- facile de trouver des modules compatibles ;
- les anciennes cartes sont bien documentées.

Si l'objectif est de comprendre les bases des microcontrôleurs, Arduino est bien adapté. Il abaisse la barrière d'entrée et permet de voir des résultats rapidement.

## Arduino comme carte d'apprentissage

Arduino est pratique pour :

- tester un bouton, un fin de course ou un capteur ;
- tester simple de thermistance via un diviseur de tension ;
- tester un OLED I2C ;
- tester un module RFID SPI ;
- générer du PWM pour un petit test ;
- lire une tension analogique ;
- expériences rapides sur une plaque d'essai.

Dans ce mode, Arduino est un excellent outil de laboratoire. Il n'est pas nécessaire de construire un dispositif final dessus : on peut d'abord comprendre le circuit et le capteur, puis transférer la solution vers ESP32, RP2040, STM32 ou une carte d'imprimante.

## Uno et Nano en bref

Les Arduino Uno et Nano classiques sont généralement basés sur l'ATmega328P.

Caractéristiques typiques :

- logique `5V` ;
- horloge à 16 MHz ;
- 32 Ko de mémoire flash ;
- 2 Ko de SRAM ;
- 14 broches numériques ;
- 6 broches PWM sur les cartes Uno/Nano ;
- 6 entrées analogiques sur Uno, 8 sur Nano ;
- USB pour flasher et alimenter la carte.

C'est suffisant pour des sketches éducatifs et des tâches autonomes simples, mais pas pour une logique complexe, la mise en réseau, une interface web, de grandes bibliothèques et une intégration aisée avec les systèmes modernes.

## Original, clone et Arduino-compatible

Il faut distinguer :

- les cartes Arduino originales ;
- les clones Uno/Nano bon marché ;
- les cartes Arduino-compatibles basées sur d'autres microcontrôleurs ;
- les cartes Arduino modernes avec Wi-Fi, USB-C, puces Arm et autre logique.

Un clone Nano à quelques euros peut convenir pour des expériences, mais la qualité du USB-UART, du régulateur, de la soudure et du bootloader peut varier. Parfois, pour un clone Nano dans l'Arduino IDE, il faut sélectionner un ancien bootloader ou un processeur différent.

Si le dispositif doit fonctionner longtemps sans surveillance, la qualité de la carte, du régulateur, des connecteurs et de la documentation est plus importante que le prix le plus bas.

## Logique 5V

Les anciens Arduino Uno/Nano utilisent la logique `5V`.

C'est pratique avec certains anciens modules, mais dangereux pour les appareils `3.3V` :

- ESP32 ne tolère généralement pas `5V` sur GPIO ;
- de nombreux OLED, RFID, capteurs et modules radio sont conçus pour `3.3V` ;
- les résistances de tirage I2C vers `5V` peuvent endommager un appareil `3.3V` ;
- certaines entrées de modules sont compatibles `5V`, mais cela doit être vérifié dans la documentation.

Si Arduino est connecté à un module `3.3V`, un convertisseur de niveaux est nécessaire, ou un circuit où les niveaux sont connus comme compatibles.

## GPIO ne alimente pas les charges

Une broche Arduino peut allumer une LED via une résistance ou fournir un signal de commande. Elle ne doit pas alimenter directement un ventilateur, un radiateur, un servo, un relais ou un ruban LED.

Circuit typique :

![Arduino Uno Rev3 avec microcontrôleur ATmega328P](../../img/02-controllers/02-arduino-uno-rev3.jpg)

*Source : [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Arduino_Uno_Rev3_with_Atmega328P.jpg), HonCode, CC0 Domaine public*

Pour les charges, il faut :

- MOSFET ou driver pour ventilateur DC, ruban LED ou radiateur DC ;
- driver à transistor et diode de protection pour la bobine de relais ;
- SSR ou relais pour une charge réseau AC ;
- alimentation séparée pour le servo ;
- masse commune là où le circuit basse tension l'exige.

GPIO est une commande, pas une sortie de puissance.

## PWM et analogWrite

Dans Arduino, `analogWrite()` sur Uno/Nano signifie généralement PWM, et non une vraie sortie analogique. La carte commute rapidement la broche en marche et arrêt, modifiant le rapport cyclique du signal.

C'est adapté pour :

- la luminosité des LEDs ;
- l'entrée de commande d'un driver ;
- PWM simple pour un ventilateur ou un module MOSFET ;
- les expériences éducatives.

Mais il y a des limites :

- PWM n'est pas disponible sur toutes les broches ;
- la fréquence PWM est fixe ou change de façon non évidente ;
- `analogWrite()` et `analogRead()` sont deux choses différentes ;
- un ventilateur PC 4 broches peut nécessiter une fréquence différente et une approche open-collector/open-drain appropriée ;
- les radiateurs et SSR ne peuvent pas simplement utiliser n'importe quel PWM rapide sans comprendre la section de puissance.

## Entrées analogiques

Arduino Uno/Nano est pratique pour des mesures analogiques simples :

- potentiomètre ;
- thermistance via diviseur de tension ;
- capteur de lumière ;
- capteur de tension simple via diviseur de tension.

Mais une entrée analogique ne doit pas voir une tension supérieure à sa plage de sécurité. Pour Uno/Nano, c'est généralement la plage relative à l'alimentation `5V` ou à l'`AREF` sélectionné. Pour mesurer une tension plus élevée, un diviseur et une protection sont nécessaires.

Pour des mesures de température précises, il ne suffit pas d'`analogRead()`, il faut aussi :

- un circuit diviseur de tension correct ;
- la valeur de la résistance ;
- la table de la thermistance ou le paramètre Beta ;
- une alimentation/tension de référence stable ;
- le filtrage du bruit ;
- le contact mécanique du capteur avec l'objet.

## Arduino et Klipper

Certaines vieilles cartes AVR peuvent historiquement se trouver près des imprimantes 3D, mais pour un nouveau dispositif autour de Klipper, il vaut mieux ne pas commencer avec Uno/Nano.

Raisons :

- mémoire limitée ;
- performances insuffisantes ;
- la logique 5V peut interférer avec les modules modernes `3.3V` ;
- pas de réseau sans modules supplémentaires ;
- pas le chemin le plus pratique pour un nouveau MCU Klipper.

Si un MCU supplémentaire est nécessaire pour Klipper, il est généralement plus pratique de se tourner vers RP2040, STM32 ou une carte d'imprimante 3D prête à l'emploi. Arduino peut être conservé pour l'enseignement, le prototypage sur plaque d'essai et les tests de capteurs individuels.

## Quand Arduino reste approprié

Arduino est approprié si :

- vous avez besoin de tester rapidement une idée ;
- vous avez besoin d'expliquer comment quelque chose fonctionne ;
- le dispositif est très simple et n'a pas besoin de réseau ;
- vous disposez déjà d'un sketch fonctionnel ;
- la clarté est plus importante que la compacité et les performances ;
- c'est un banc éducatif, pas de l'électronique de puissance finale.

Arduino n'est pas un bon choix si :

- vous avez besoin de Wi-Fi intégré ;
- vous avez besoin d'une intégration étroite avec Klipper ;
- vous avez besoin de beaucoup de mémoire ;
- vous avez besoin de nombreux capteurs modernes `3.3V` ;
- le dispositif doit être compact, durable et propre industriellement ;
- il y a une section de puissance avec un radiateur où des protections indépendantes sont importantes.

## Ce qu'il faut vérifier avant d'acheter

Avant d'acheter une carte Arduino-compatible, vérifiez :

- s'il s'agit d'une carte originale, d'un clone ou d'une carte compatible ;
- quel microcontrôleur est installé ;
- logique `5V` ou `3.3V` ;
- quel chip USB-UART est utilisé ;
- s'il existe un driver pour votre ordinateur ;
- quel bootloader est nécessaire ;
- combien de flash et de SRAM ;
- combien de broches PWM et d'entrées analogiques ;
- s'il existe un schéma et un brochage ;
- qualité du régulateur d'alimentation et des connecteurs ;
- si la carte convient à la tâche finale.

## Erreurs courantes

- penser qu'Arduino est une carte spécifique ;
- connecter directement un Arduino `5V` à un module `3.3V` ;
- alimenter une charge depuis GPIO ;
- alimenter un servo depuis la broche `5V` et obtenir des resets ;
- utiliser `analogWrite()` comme une vraie sortie analogique ;
- sélectionner le mauvais bootloader pour un clone Nano ;
- ne pas installer le driver pour l'USB-UART ;
- essayer de construire un dispositif réseau moderne sur Uno sans raison ;
- transférer un prototype éducatif sur plaque d'essai dans un dispositif de puissance fermé sans retravailler l'alimentation, le câblage et les protections.

## Points clés

Arduino est un bon écosystème éducatif et un outil pratique pour des tests rapides. Il est excellent pour comprendre GPIO, PWM, ADC et les capteurs.

Mais les classiques Uno/Nano sont de vieilles cartes `5V` avec une mémoire limitée et sans réseau. Pour un nouveau dispositif autour d'une imprimante 3D, ESP32, RP2040, STM32 ou une carte d'imprimante prête à l'emploi est souvent plus pratique, laissant Arduino comme outil éducatif et de diagnostic.

## Ressources associées

- [Arduino Docs: UNO R3](https://docs.arduino.cc/hardware/uno-rev3) — spécifications officielles de l'Uno R3 : ATmega328P, `5V`, broches, PWM, entrées analogiques et ressources de la carte.
- [Arduino Store: UNO Rev3 Tech Specs](https://store.arduino.cc/collections/arduino/products/arduino-uno-rev3) — tableau avec tension, courant GPIO, mémoire, fréquence et dimensions de la carte.
- [Arduino Store: Arduino Nano](https://store-usa.arduino.cc/products/arduino-nano) — spécifications du Nano, alimentation, mémoire, broches numériques et analogiques.
- [Arduino Help Center: Select the right processor for Arduino Nano](https://support.arduino.cc/hc/en-us/articles/4401874304274-Select-the-right-processor-for-Arduino-Nano) — pourquoi Nano et les clones Nano peuvent avoir des bootloaders différents.
- [Arduino Language Reference](https://docs.arduino.cc/language-reference/) — référence officielle pour `pinMode`, `digitalWrite`, `analogRead`, `analogWrite`, PWM et les fonctions de base.
- [Arduino Help Center: Use PWM output with Arduino](https://support.arduino.cc/hc/en-us/articles/9350537961500-Use-PWM-output-with-Arduino) — liste des broches PWM pour les cartes populaires et limites d'`analogWrite()`.
