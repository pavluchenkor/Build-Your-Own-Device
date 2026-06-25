# Affichage OLED

Un affichage OLED est un petit écran pour montrer du texte, des chiffres, des icônes simples et l'état de l'appareil. Contrairement aux LCD réguliers, OLED s'éclaire lui-même et ne nécessite pas de rétroéclairage séparé. Donc, les petits modules OLED sont lisibles, prennent peu de place et sont pratiques pour les simples appareils DIY.

Dans un appareil de type iDryer, un OLED peut afficher la température, l'humidité, le mode de travail, l'erreur, l'état Wi-Fi, le filament restant ou la phase de séchage actuelle.

## Quand OLED est utile

Un OLED vaut la peine d'ajouter si les utilisateurs doivent voir l'état de l'appareil directement sur l'enceinte :

- température actuelle de la chambre ;
- humidité ;
- température cible ;
- mode de travail ;
- minuteur ;
- erreur capteur ;
- état du ventilateur ou du radiateur ;
- état de la connexion ;
- menu simple sans grand écran.

Si l'appareil est toujours géré via Klipper, une interface Web ou une application mobile, un OLED séparé peut être inutile. Il ajoute du câblage, de l'espace d'enceinte, du code et un autre point de défaillance.

## Tailles et contrôleurs typiques

Les modules OLED petits les plus courants :

- `128x32` pixels ;
- `128x64` pixels ;
- diagonale environ `0,91"` ou `0,96"` ;
- monochrome : blanc, bleu, jaune-bleu ;
- avec contrôleur `SSD1306` ou similaire `SH1106`.

`SSD1306` et `SH1106` se ressemblent mais ne sont pas toujours entièrement compatibles dans le code. Si une bibliothèque est définie pour `SSD1306` mais le module est réellement `SH1106`, l'écran peut montrer une image décalée, du charabia ou ne pas fonctionner.

Avant d'acheter, il est important de vérifier non seulement la taille de l'écran mais aussi le contrôleur, l'interface et la tension d'alimentation.

## I2C et SPI

Les petits modules OLED se connectent généralement via I2C ou SPI.

Un module I2C a généralement 4 contacts :

- `VCC` ;
- `GND` ;
- `SDA` ;
- `SCL`.

Un module SPI a généralement besoin de plus de lignes :

- `VCC` ;
- `GND` ;
- `SCK`/`CLK` ;
- `MOSI`/`DIN` ;
- `CS` ;
- `DC` ;
- parfois `RST`.

I2C est plus simple à câbler et généralement suffisant pour l'état, la température et le menu simple. SPI est plus rapide et mieux si l'écran se redessine souvent, mais pour un petit affichage d'état, ce n'est généralement pas critique.

![Connexion de l'affichage I2C OLED au contrôleur](../../img/03-common-components/08-oled-i2c-wiring.jpg)

*Source: [Adafruit Learning System](https://learn.adafruit.com/adafruit-128x64-oled-featherwing/), CC BY-SA 3.0*

## Puissance et niveaux logiques

Un module OLED peut être évalué pour `3,3V`, pour `5V`, ou avoir un régulateur et un décalage de niveau sur la carte. Extérieurement, de tels modules peuvent se ressembler presque identiquement.

Avant de connecter, vérifiez :

- quelle puissance est listée sur le module ou la page produit ;
- si les lignes `SDA`/`SCL` sont compatibles avec la logique du contrôleur ;
- si le module a des pull-ups I2C ;
- si les pull-ups ne conflictent pas avec la tension du contrôleur.

Pour ESP32 et la plupart des microcontrôleurs modernes, il est plus sûr d'assumer une logique `3,3V`. Si un module OLED tire I2C à `5V`, cela peut être problématique pour un contrôleur 3,3V.

Beaucoup de modules I2C OLED populaires fonctionnent à partir de `3,3V` et se connectent bien à ESP32 directement, mais vous devez vérifier le module spécifique.

## Adresse I2C

Les OLED I2C ont souvent des adresses :

- `0x3C` ;
- `0x3D`.

Si l'écran ne répond pas, l'adresse est la première chose à vérifier après l'alimentation et les fils. Certains modules vous permettent de changer l'adresse via un cavalier ou en soudant un petit cavalier sur la carte.

Signes d'une adresse incorrecte :

- l'esquisse ou le micrologiciel démarre mais l'écran est vide ;
- le scanner I2C voit le périphérique à une adresse différente ;
- la bibliothèque initialise l'affichage sans résultat visible ;
- changer `0x3C` en `0x3D` le fait fonctionner.

## Quoi afficher sur un petit écran

Un OLED `128x32` ou `128x64` a très peu d'espace. N'essayez pas de créer une interface téléphonique complète dessus.

Bon ensemble pour un sécheur ou un radiateur :

- grande température actuelle ;
- température cible ;
- humidité s'il y a un capteur ;
- mode : `CHALEUR`, `SÉCHAGE`, `INACTIF`, `ERREUR` ;
- petite icône ventilateur/chaleur ;
- code d'erreur ou message court.

Mauvais ensemble :

- longues phrases ;
- petits tableaux ;
- nombreux éléments de menu sur un écran ;
- texte en scrolling constant ;
- animation décorativement au lieu d'état utile.

Pour un appareil avec un radiateur, il est plus important de voir rapidement une erreur qu'un bel écran d'accueil.

## Burn-in et luminosité

Les pixels OLED vieillissent de briller. Si vous affichez le même texte lumineux au même endroit pendant de nombreuses heures, une trace peut éventuellement apparaître.

Pour un appareil DIY, ce n'est pas toujours critique, mais il est préférable de :

- ne pas maintenir la luminosité au maximum sans besoin ;
- éteindre l'écran après un temps d'inactivité ;
- déplacer occasionnellement les éléments statiques ;
- ne pas afficher le remplissage blanc constamment ;
- utiliser des mises à jour brèves au lieu d'animation supplémentaire.

Dans une chambre chaude ou près d'un radiateur, OLED vieillit aussi plus mal. Il est préférable de garder l'électronique dans une zone avec une température contrôlée sans dépasser la plage du module.

## Longueur de fil et interférence

I2C n'aime pas les longs fils, surtout près des moteurs, des radiateurs et des lignes d'alimentation. Si OLED est sur une porte ou un panneau amovible, un long câble flexible peut devenir une source de bruit.

Règles pratiques :

- gardez `SDA` et `SCL` courts ;
- routez-les loin des fils d'alimentation du radiateur ;
- utilisez `GND` commun ;
- ne faites pas de connecteur qui rentre à l'envers ;
- pour un couvercle amovible, utilisez un connecteur approprié et une protection contre les tractions ;
- si I2C est instable, d'abord raccourcissez les fils et vérifiez les pull-ups.

SPI tolère généralement mieux la vitesse de mise à jour plus rapide, mais a plus de fils et les erreurs de connexion sont plus courantes.

## OLED ou écran tactile

OLED est bon pour montrer l'état. Il ne résout pas le problème d'entrée sans boutons, encodeur ou autre contrôle.

Si les utilisateurs doivent souvent changer les paramètres directement sur l'appareil, vous pourriez avoir besoin de :

- encodeur + OLED ;
- plusieurs boutons + OLED ;
- écran TFT ;
- écran tactile ;
- interface Web ou application.

N'installez pas un écran tactile juste parce que OLED semble petit. Pour les simples appareils, un petit OLED avec un bouton est parfois plus fiable et clair.

## Quoi vérifier avant d'acheter

Avant d'acheter un module OLED, vérifiez :

- taille : `128x32`, `128x64` ou autre ;
- contrôleur : `SSD1306`, `SH1106`, `SH1107` ;
- interface : I2C ou SPI ;
- puissance : `3,3V`, `5V` ou plage ;
- niveau logique ;
- adresse I2C si listée ;
- support de broche de réinitialisation ;
- support dans le micrologiciel ou la bibliothèque choisis ;
- dimensions de la carte physique et trous de montage ;
- localisation du connecteur ;
- température de fonctionnement ;
- couleur et lisibilité à l'angle que vous avez besoin.

Pour un appareil ESP32, OLED I2C `128x64` sur `SSD1306` avec l'adresse `0x3C` est généralement le plus pratique. Pour une carte Klipper, vérifiez si la carte spécifique prend en charge le bus choisi et comment l'affichage est décrit dans la configuration.

## Erreurs typiques

- confusion de `SDA` et `SCL` ;
- connexion d'alimentation à la mauvaise tension ;
- n'a pas vérifié l'adresse I2C ;
- sélectionné `SSD1306` dans le code mais le module est `SH1106` ;
- créé des fils I2C trop longs ;
- oublié `GND` commun ;
- connecté le module de pull-up 5V au contrôleur 3,3V sans vérifier ;
- sélectionné le module SPI s'attendre à 4 broches comme I2C ;
- placé l'écran dans une zone chaude ;
- ajouté l'affichage sans comprendre quel problème il résout pour les utilisateurs.

## Point principal

Un affichage OLED est bon pour l'état court et l'interface locale simple. Pour la plupart des appareils DIY, un OLED I2C `128x64` suffit s'il est compatible par alimentation et pris en charge par le micrologiciel choisi.

Avant de connecter, vérifiez le contrôleur d'affichage, l'interface, l'alimentation, l'adresse I2C et la longueur du fil. Si l'appareil est déjà pratique via l'interface Web, OLED peut ne pas être nécessaire.

## Matériaux de référence

- [Adafruit: Monochrome OLED Breakouts](https://learn.adafruit.com/monochrome-oled-breakouts) - guide pratique du petit OLED SSD1306, connexion I2C/SPI, tailles et exemples.
- [SparkFun: Qwiic Micro OLED Hookup Guide](https://learn.sparkfun.com/tutorials/qwiic-micro-oled-hookup-guide) - exemple de module OLED I2C, bibliothèque et sortie de texte/graphiques.
- [ESPHome: SSD1306 OLED Display](https://esphome.io/components/display/ssd1306) - documentation sur `ssd1306_i2c`, `ssd1306_spi`, adresses, modèles SSD1306/SH1106 et configuration.
- [Klipper Configuration Reference: display](https://www.klipper3d.org/Config_Reference.html#display) - support d'affichage dans Klipper, y compris `ssd1306` et `sh1106`.
- [SSD1306 Datasheet: Solomon Systech](https://www.radiolocman.com/datasheet/pdf.html?di=168297) - description technique du contrôleur SSD1306 : résolution, interfaces I2C/SPI/parallèle et commandes.
