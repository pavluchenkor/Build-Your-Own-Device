# Outils

Cette section n'est pas sur la collection d'outils.

Il s'agit de l'ensemble minimal qui vous aide à assembler un appareil en toute sécurité, vérifier les connexions et trouver les erreurs simples sans deviner.

Dans les appareils faits maison autour d'iDryer et des imprimantes 3D, les outils sont nécessaires pour des tâches pratiques :

- vérifier si 24V est présent sur l'alimentation ;
- comprendre si plus et moins sont inversés ;
- vérifier la continuité sur un fil ;
- tester une thermistance ;
- voir si le signal UART arrive ;
- flasher un contrôleur ;
- faire un connecteur approprié ;
- trouver l'affaissement de l'alimentation ;
- comprendre pourquoi un ventilateur ou un chauffage ne s'allume pas.

## Ensemble minimal

Pour la plupart des builds simples, les outils utiles incluent :

- multimètre ;
- adaptateur USB-UART ou USB-TTL ;
- fer à souder ;
- outil de sertissage ;
- pinces à couper et dénudeur de fil ;
- gaine thermorétractable ;
- terminaux et connecteurs appropriés ;
- ST-Link si vous travaillez avec STM32 ;
- oscilloscope ou au moins un multimètre avec compteur de fréquence pour les diagnostics plus complexes.

Tout n'a pas besoin d'être acheté à la fois. Mais un multimètre et les bons outils de câblage se rentabilisent généralement rapidement.

## Les outils ne remplacent pas la compréhension

Un multimètre ne rend pas la partie secteur sûre.

Un fer à souder ne corrige pas un mauvais schéma.

Un oscilloscope n'est pas nécessaire si plus et moins sont inversés.

Donc l'ordre est :

1. Comprendre ce qui devrait être connecté.
2. Vérifier l'alimentation.
3. Vérifier le câblage.
4. Vérifier les capteurs et les signaux.
5. Ce n'est qu'alors que vous cherchez des problèmes complexes.

## Ce qui sera dans cette section

- `02-multimeter.md` - mesure de la tension DC, continuité, résistance, fusibles et pourquoi la mesure de courant est plus dangereuse.
- `03-usb-ttl-adapter.md` - adaptateurs USB-UART, TX/RX/GND, niveaux logiques 3.3V/5V, flashage et journaux.
- `04-soldering.md` - soudage de fils, pads, modules, joints froids, gaine thermorétractable et soulagement de la déformation.
- `05-crimping-connectors.md` - Dupont, JST, cosses, Faston, terminaux et vérification de la qualité du sertissage.
- `06-st-link.md` - ST-Link, STM32, SWD, récupération de la carte après flashage échoué.
- `07-oscilloscope.md` - PWM, UART, affaissement de l'alimentation, bruit et avertissement de sécurité critique concernant la tension secteur.

## Ce qui vaut la peine d'acheter correctement

Il y a des choses sur lesquelles vous ne devriez pas économiser :

- un multimètre avec des sondes appropriées et mode continuité ;
- un fer à souder avec contrôle de température ;
- soudure et flux de qualité ;
- un outil de sertissage pour terminaux spécifiques ;
- connecteurs et terminaux évalués pour le courant nécessaire ;
- gaine thermorétractable ;
- fils de calibre correct.

Un sertissage médiocre ou des terminaux faibles peuvent causer plus de problèmes qu'un mauvais firmware.

## Ce que vous ne pouvez pas faire

Vous ne pouvez pas :

- mesurer la résistance sur un circuit sous tension ;
- mesurer le courant de la même manière que vous mesurez la tension ;
- enfoncer un multimètre dans 110-230V AC sans comprendre la sécurité ;
- souder la partie puissance « de quelque manière » ;
- utiliser Dupont pour un chauffage ;
- changer les fils alors que l'alimentation est active ;
- laisser les parties secteur ouvertes sur la table ;
- penser que si un fil « tient », le contact est bon.

## Les éléments essentiels

- Le multimètre est le premier outil de diagnostic.
- USB-UART est nécessaire pour les journaux, le flashage et la communication avec les appareils UART.
- Le soudage et le sertissage sont des tâches différentes, et pour les connecteurs, le sertissage est souvent meilleur.
- ST-Link est nécessaire lorsque vous travaillez avec STM32 et SWD.
- L'oscilloscope n'est pas nécessaire pour tout le monde, mais il montre rapidement les signaux, l'affaissement et le bruit.
- Pour la partie puissance, la qualité du contact, le calibre du fil et la sécurité importent plus que l'apparence de l'assemblage.

## Matériaux de référence

- [SparkFun: How to Use a Multimeter](https://learn.sparkfun.com/tutorials/how-to-use-a-multimeter/all) - notions de base du multimètre : tension, courant, résistance, continuité.
- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - vérifications matérielles pour l'alimentation, les connexions et la chaleur.
- [SparkFun: Serial Communication](https://learn.sparkfun.com/tutorials/serial-communication) - UART et logique de communication série de base.
- [Adafruit: Guide to Excellent Soldering](https://learn.adafruit.com/adafruit-guide-excellent-soldering) - guide de soudage pratique et qualité de connexion.
- [STMicroelectronics: ST-LINK/V2 User Manual](https://www.st.com/resource/en/user_manual/um1075-stlinkv2-incircuit-debuggerprogrammer-for-stm8-and-stm32-stmicroelectronics.pdf) - documentation officielle ST-Link et SWD/SWIM.
