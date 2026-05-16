# Premiers pas

Vous imprimez déjà sur une imprimante 3D et souhaitez construire un séchoir à filament. Mais quand vous ouvrez le schéma, des questions apparaissent immédiatement : quel alimentation électrique, où va la masse, MOSFET ou SSR, pourquoi avez-vous besoin d'un dissipateur thermique. Cette section répond à ces questions étape par étape — du premier calcul de courant au dispositif fonctionnant.

Après cette section, vous comprendrez ce que vous construisez, pourquoi exactement de cette façon, où les dangers pourraient être, et comment vérifier le dispositif avant de le mettre sous tension.

La section vous guide progressivement des concepts simples aux résultats réels.

Le chemin ici va du simple au complexe :

1. D'abord comprenez la puissance, le courant, la charge et la sécurité de base.
2. Ensuite, découvrez quels contrôleurs existent et lequel choisir.
3. Ensuite, comprenez les composants de base : radiateur, ventilateur, capteurs, écrans, RFID et capteurs de charge.
4. Ensuite, apprenez à utiliser les outils minimaux : multimètre, USB-UART, fer à souder, pince à sertir.
5. Ensuite, passez aux connexions pratiques.
6. Ensuite, pensez au boîtier et aux pièces imprimées en 3D.
7. À la fin, ayez une liste d'erreurs courantes et une liste de contrôle diagnostique à portée de main.

L'idée principale :

Vous n'avez pas besoin de comprendre toute l'électronique à la fois. Il suffit de procéder étape par étape et chaque fois de comprendre le prochain petit pas.

Ce que cette section devrait donner :

- comprendre comment les circuits basse tension `12V`/`24V DC` diffèrent de l'alimentation secteur `110-230V AC`;
- capacité à calculer approximativement le courant de charge ;
- compréhension de quand vous avez besoin de MOSFET, SSR ou relais ;
- comprendre comment ESP32, Arduino, RP2040 et STM32 diffèrent en pratique ;
- comprendre pourquoi pour Klipper MCU il est préférable de regarder RP2040 ou STM32 ;
- compréhension de base des capteurs, ventilateurs, radiateurs et écrans ;
- compétences minimales en diagnostic au multimètre ;
- comprendre quelles pièces imprimées peuvent être placées près de la chaleur ;
- liste d'erreurs qu'il vaut mieux ne pas répéter.

Ce que cette section ne fait pas :

- ne remplace pas un électricien lors du travail avec `110-230V AC` ;
- n'enseigne pas la conception profonde des circuits ;
- ne essaye pas d'expliquer toute la physique ;
- ne donne pas la permission d'assembler des appareils dangereux sans comprendre la sécurité.

Comment lire :

- si le sujet est nouveau — allez dans l'ordre ;
- si vous avez déjà construit des appareils — ouvrez la section requise comme référence ;
- si l'appareil ne fonctionne pas — regardez d'abord `08-common-mistakes` ;
- si vous travaillez avec `110-230V AC` — lisez d'abord tout ce qui concerne la sécurité, les SSR, les fils, les bornes et la mise à la terre de protection.

## Matériaux de référence

- [SparkFun: Voltage, Current, Resistance, and Ohm's Law](https://learn.sparkfun.com/tutorials/voltage-current-resistance-and-ohms-law) - concepts fondamentaux de tension, courant, résistance, circuit fermé et loi d'Ohm.
- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/all) - ordre pratique du diagnostic initial : alimentation, connexions, polarité, joints de soudure, câbles et chutes de tension.
- [Fluke: How to Measure Resistance with a Digital Multimeter](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-resistance) - pourquoi les mesures de résistance sont effectuées hors tension et pourquoi un multimètre est nécessaire pour vérifier les composants.
- [OSHA: Electrical Incidents - Grounding](https://www.osha.gov/etools/construction/electrical-incidents/grounding) - pourquoi la mise à la terre de protection est nécessaire et pourquoi travailler avec l'alimentation secteur nécessite une discipline de sécurité séparée.

## Voir aussi

- [Calcul de charge 24V](../01-electronics-basics/01-load-calculation-24v.md) - premier sujet pratique sur la tension, le courant, la puissance et la marge de l'alimentation électrique.
- [Composants communs](../03-common-components/01-overview.md) - plan des pièces les plus souvent trouvées dans les appareils simples.
- [Outils](../05-tools/01-overview.md) - ce dont vous avez besoin pour vérifier, flasher, souder et diagnostiquer.
- [Guides pratiques](../06-practical-guides/01-connecting-fan.md) - exemple de première connexion de charge sûre via le contrôleur.
- [Erreurs courantes](../08-common-mistakes/01-overview.md) - ce à quoi vous devez faire attention si l'appareil ne s'allume pas, surchauffe, fait du bruit ou se comporte de manière instable.
