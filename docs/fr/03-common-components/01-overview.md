# Composants courants

Les composants courants sont les pièces et modules que vous rencontrerez le plus souvent lors de l'assemblage d'un appareil de type iDryer ou de périphériques d'imprimante 3D.

Objectif de cette section :

Cette section sert de référence pour les pièces que vous aurez réellement en main pendant l'assemblage.

Vous n'avez pas besoin de connaissances approfondies en électronique ici. L'objectif principal est de vous aider à comprendre :

- ce que c'est que ce composant ;
- pourquoi vous en avez besoin ;
- comment il est généralement connecté ;
- par quoi vous pouvez le remplacer ;
- quels paramètres importent lors de l'achat ;
- ce qui casse le plus souvent à la première connexion.

Format de chaque page :

- ce que c'est ;
- où il est utilisé dans iDryer et les périphériques d'imprimante 3D ;
- à quoi ressemble une connexion typique ;
- caractéristiques importantes ;
- erreurs typiques ;
- une courte liste de contrôle avant d'acheter.

Fichiers proposés :

- `02-heaters.md` - radiateurs : PTC, coussinets silicone, cartouches, 12V/24V/110-230V AC.
- `03-fans.md` - ventilateurs : 2-broche, 3-broche, 4-broche PWM, tension, courant, bruit, débit d'air.
- `04-thermistors.md` - thermistances : NTC 100K, tables de consultation, montage, circuits ouverts/courts.
- `05-led-strips.md` - bandes LED : 5V/12V/24V, régulières et adressables, courant par mètre.
- `06-servo-motors.md` - servomoteurs : puissance, signal, angle, courant de crête.
- `07-load-cells.md` - capteurs de charge : HX711, étalonnage, montage mécanique.
- `08-oled-display.md` - OLED : I2C/SPI, adresse, puissance, quand nécessaire.
- `09-touchscreen.md` - TFT/écran tactile : UART/SPI/HDMI, puissance, compatibilité.
- `10-rfid-and-nfc.md` - RFID/NFC : cartes, étiquettes, fréquences, connexion.

## Matériaux de référence

- [Klipper Configuration Reference](https://www.klipper3d.org/Config_Reference.html) - sections officielles de Klipper sur les radiateurs, ventilateurs, capteurs de température, servomoteurs et écrans dans la configuration.
- [DigiKey: Selecting A Fan](https://www.digikey.com/en/articles/selecting-a-fan) - sélection pratique des ventilateurs par débit d'air, pression statique, résistance du boîtier et tâche thermique.
- [Adafruit: MOSFET Driver](https://learn.adafruit.com/adafruit-mosfet-driver) - pourquoi les charges haute puissance ne sont pas connectées directement à GPIO et pourquoi vous avez besoin d'un commutateur de puissance.
- [SparkFun: Load Cell Amplifier HX711 Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide) - exemple de capteur de charge, HX711, fils de puissance et signal et étalonnage.
- [Adafruit: PN532 RFID/NFC Breakout Wiring](https://learn.adafruit.com/adafruit-pn532-rfid-nfc/breakout-wiring) - exemple d'un composant où vous devez vérifier la puissance, les niveaux logiques et l'interface choisie à l'avance.

## Voir aussi

- [Radiateurs](02-heaters.md) - le type de charge le plus risqué : puissance, température, SSR/MOSFET et protection indépendante.
- [Ventilateurs](03-fans.md) - débit d'air, pression statique, 2-broche/3-broche/4-broche et puissance.
- [Thermistances](04-thermistors.md) - capteur de température comme base de rétroaction du radiateur.
- [Connexion d'un ventilateur](../06-practical-guides/01-connecting-a-fan.md) - exemple pratique de connexion de composant via un commutateur de puissance.
- [Erreurs de radiateur et SSR](../08-common-mistakes/05-heater-ssr-mistakes.md) - erreurs courantes avec les charges haute puissance et les charges secteur.
