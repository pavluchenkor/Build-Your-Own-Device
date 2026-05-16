# Contrôleur ESP32

L'ESP32 est une famille de microcontrôleurs Espressif avec Wi-Fi, Bluetooth et un large ensemble de périphériques. Dans les appareils DIY, il est souvent choisi quand vous avez besoin de construire un module autonome : il se connecte au réseau lui-même, lit les capteurs, affiche une page dans un navigateur et contrôle les sorties simples.

Pour les appareils autour d'une imprimante 3D, l'ESP32 est utile non pas comme « une autre carte de puissance », mais comme un petit contrôleur réseau : un capteur de température/humidité, un module de ventilation, un filtre simple avec une interface web, une surveillance de caméra séparée, ou un sèchoir autonome.

## Où l'ESP32 est utile

Tâches typiques :

- Capteur de température et humidité Wi-Fi ;
- contrôleur de ventilateur séparé via module MOSFET ;
- contrôle d'un relais ou SSR avec un signal basse tension ;
- écran OLED sur I2C ;
- lecteur RFID/NFC sur SPI ou UART ;
- servo avec alimentation séparée ;
- page web simple pour l'état et les paramètres ;
- intégration avec MQTT, Home Assistant ou votre propre logique locale ;
- prototype autonome qui n'a pas besoin de faire partie de Klipper.

L'ESP32 est bon quand l'appareil doit vivre séparément de l'imprimante et échanger des données sur le réseau. Si la tâche est simplement d'ajouter des broches à Klipper, il est généralement préférable de considérer RP2040, STM32 ou une carte d'imprimante prête à l'emploi.

## Architecture typique d'un appareil

L'ESP32 n'alimente pas les charges directement. Il sort des signaux de contrôle, et les modules séparés font le travail de puissance.

![Carte de développement ESP32 avec broches GPIO](../../../img/02-controllers/01-esp32-dev-board.jpg)

*Source : [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:ESP32_Dev_Board.jpg), Edwiyanto, CC BY-SA 4.0*

En pratique, cela ressemble à :

- L'ESP32 est alimenté par USB ou un `5V` stable sur la carte de développement ;
- la logique ESP32 elle-même fonctionne sur `3.3V` ;
- les capteurs sont connectés à GPIO, I2C, SPI, UART ou ADC ;
- les ventilateurs, les bandes LED, les radiateurs DC sont connectés via MOSFET ou driver ;
- les radiateurs réseau sont connectés uniquement via un SSR/relais AC approprié et une section de puissance sécurisée ;
- le servo est alimenté à partir d'une source `5V/6V` séparée, et l'ESP32 ne fournit que le signal.

GPIO n'est pas une source de puissance pour une charge. Une broche peut basculer l'entrée du driver, mais ne devrait pas alimenter un ventilateur, un radiateur, un relais, un servo ou une bande LED directement.

## Ce que ESP32 signifie sur une carte

L'étiquette « ESP32 » peut signifier différentes choses :

- la puce ESP32 elle-même ;
- un module avec la puce, la mémoire flash et une antenne, comme ESP32-WROOM ;
- une carte de développement avec USB, régulateur de puissance, boutons et broches exposées ;
- variantes plus récentes : ESP32-S3, ESP32-C3, ESP32-C6, et d'autres.

Pour un premier projet, il est plus pratique d'utiliser une carte de développement qu'un module nu. Une carte de développement a déjà USB, un régulateur de puissance, des boutons `BOOT`/`EN` et des broches pour les breadboards.

Avant d'acheter, vérifiez :

- le nom exact de la carte et de la puce ;
- si elle a USB-C ou micro-USB ;
- quel USB-UART ou USB intégré est utilisé ;
- s'il y a un schéma et un pinout ;
- quelles GPIO sont vraiment exposées ;
- quel régulateur de puissance est sur la carte ;
- si elle a une antenne correcte et de l'espace autour ;
- si la taille de la carte s'adapte à votre boîtier.

## Logique 3.3V

L'ESP32 fonctionne avec la logique `3.3V`. Cela signifie qu'un niveau `HIGH` typique sur GPIO est d'environ `3.3V`, pas `5V`.

Ce qui compte :

- n'appliquez pas `5V` aux GPIO ESP32 ;
- pour les capteurs et modules `5V`, vous pourriez avoir besoin d'un convertisseur de niveau ;
- les pull-ups I2C doivent aller à `3.3V` si le bus est connecté à ESP32 ;
- certains modules MOSFET/SSR prêts à l'emploi peuvent ne pas fonctionner de manière fiable avec `3.3V` ;
- la puissance de charge ne peut pas être tirée de GPIO.

De nombreux capteurs sont déjà disponibles dans des variantes `3.3V`. Pour l'ESP32, c'est le meilleur choix.

## Puissance

Les cartes de développement ont généralement une entrée USB et une broche `5V`/`VIN`, et l'ESP32 lui-même est alimenté par un régulateur `3.3V`.

Erreurs courantes :

- alimenter l'ESP32 à partir d'un câble USB faible ;
- alimenter un servo, un ventilateur ou un relais à partir de la broche `3.3V` sur la carte ;
- connecter une charge lourde à la broche `5V` sans comprendre d'où vient ce courant ;
- ne pas connecter la masse commune entre ESP32 et le driver basse tension ;
- l'ESP32 réinitialise quand Wi-Fi démarre en raison d'une chute de tension.

Wi-Fi consomme du courant impulsif. Pour un fonctionnement stable, un bon câble, un régulateur, des condensateurs sur la carte et une alimentation séparée pour les charges sont importants.

## GPIO et broches spéciales

L'ESP32 a beaucoup de GPIO, mais pas toutes les broches sont également pratiques.

Sur ESP32 classique :

- certaines broches sont liées au chargement de la puce, ce sont des broches de strapping ;
- `GPIO6-GPIO11` sont généralement occupées par la mémoire flash et ne sont pas utilisées ;
- `GPIO34-GPIO39` sont entrée uniquement ;
- `GPIO1` et `GPIO3` sont souvent utilisées comme UART pour le firmware et les journaux ;
- certaines broches peuvent être occupées par une LED, un bouton ou d'autres circuits sur une carte de développement spécifique.

Les broches de strapping détermine le mode d'amorçage au démarrage. Si un circuit externe tire une telle broche de la mauvaise manière, l'ESP32 peut ne pas démarrer ou peut entrer en mode de mise à jour du firmware.

Règle pratique : pour la première version, utilisez les broches du pinout de votre carte spécifique et évitez les broches marquées `BOOT`, `FLASH`, `STRAP`, `TX0`, `RX0`, `GPIO6-GPIO11` sauf si vous comprenez leur rôle.

## ADC sur ESP32

L'ESP32 peut mesurer la tension analogique via ADC, mais ce n'est pas un multimètre de laboratoire.

Ce qui compte :

- sur ESP32 classique il y a ADC1 et ADC2 ;
- ADC2 entre en conflit avec Wi-Fi, donc pour un appareil Wi-Fi il est préférable d'utiliser les broches ADC1 ;
- la plage de mesure dépend du paramètre d'atténuation ;
- la mesure peut nécessiter un étalonnage ;
- vous ne pouvez pas appliquer une tension supérieure au niveau sécurisé GPIO à ADC ;
- une thermistance NTC nécessite généralement un diviseur de tension et la bonne table/modèle dans le firmware.

Si vous avez besoin d'un capteur de température précis, il est souvent plus simple d'utiliser un capteur numérique ou un module prêt à l'emploi avec une bibliothèque connue. Pour une thermistance NTC, l'ESP32 fonctionne, mais le circuit et les paramètres ADC doivent être vérifiés.

## PWM, I2C, SPI et UART

L'ESP32 est pratique pour les périphériques :

- PWM via LEDC convient aux ventilateurs, rétroéclairage et signaux servo ;
- I2C convient aux écrans OLED et à de nombreux capteurs ;
- SPI convient aux modules RFID, aux écrans et aux appareils rapides ;
- UART convient au GPS, à certains capteurs, à d'autres contrôleurs et au débogage.

L'ESP32 a une matrice GPIO flexible : de nombreux signaux peuvent être assignés à différentes broches. Mais cela ne signifie pas que n'importe quelle broche est toujours un bon choix. Les limitations spécifiques de la carte, la mémoire flash, les broches d'amorçage et l'UART occupée doivent toujours être prises en compte.

## ESP32 et Klipper

L'ESP32 est mieux vu comme un appareil Wi-Fi/IoT séparé près de l'imprimante, non pas comme le chemin principal pour un MCU supplémentaire dans Klipper.

Klipper est organisé comme un hôte plus un ou plusieurs MCU. Pour les nouveaux MCU supplémentaires, il est généralement plus pratique d'utiliser :

- RP2040 ;
- STM32 ;
- les cartes d'imprimante 3D prêtes à l'emploi.

L'ESP32 peut échanger des données avec le système d'imprimante séparément : via MQTT, API HTTP, Home Assistant, votre propre serveur ou une autre intégration. Mais ce n'est plus la même chose qu'ajouter `[mcu]` à la configuration de Klipper et utiliser les broches directement.

## Quoi vérifier avant d'acheter

Avant d'acheter une carte ESP32, vérifiez :

- modèle exact : ESP32, S3, C3, C6, etc. ;
- tension logique ;
- si elle a USB et comment la carte est flashée ;
- s'il y a un pinout ou un schéma officiel ;
- quelles broches sont sûres pour GPIO ;
- quelles broches sont entrée uniquement ;
- quelles broches sont occupées par flash/PSRAM, USB, UART ou LED ;
- si vous avez assez d'ADC/I2C/SPI/UART pour la tâche ;
- comment la carte est alimentée ;
- si elle rentre dans le boîtier ;
- s'il y a une bibliothèque ou un firmware pour votre scénario.

Si une carte d'un marché en ligne n'a pas de schéma et un pinout correct, elle peut être utilisée pour les expériences, mais ne convient pas à un appareil qui doit fonctionner sans surveillance pendant longtemps.

## Erreurs courantes

- appliquer `5V` aux GPIO ESP32 ;
- alimenter une charge à partir de GPIO ;
- alimenter un servo ou un relais à partir d'une broche `3.3V` faible ;
- oublier la masse commune avec MOSFET/driver ;
- choisir une broche ADC2 pour un capteur et ensuite activer Wi-Fi ;
- utiliser une broche de strapping d'amorçage pour que l'ESP32 ne démarre pas ;
- utiliser `GPIO34-GPIO39` comme sorties ;
- acheter un module sans pinout et schéma ;
- penser que « ESP32 avec Wi-Fi » signifie automatiquement un contrôle sécurisé des radiateurs réseau ;
- essayer de remplacer l'électronique de puissance par du firmware.

## Points clés

L'ESP32 est un bon choix pour les appareils Wi-Fi autonomes : capteurs, interfaces web, contrôle de ventilation simple, filtres, écrans et périphériques.

Mais l'ESP32 fonctionne avec la logique `3.3V`, a des broches spéciales et ne devrait pas alimenter directement les charges. Pour les circuits de puissance, MOSFET, drivers, relais ou SSR sont nécessaires, et pour un radiateur réseau, une section de puissance complète et sécurisée est nécessaire.

## Matériaux connexes

- [Espressif : ESP32 Wi-Fi & Bluetooth SoC](https://www.espressif.com/en/products/socs/esp32/datasheet) — aperçu officiel de la famille ESP32, modules, cartes de développement et liens vers la documentation.
- [Espressif : ESP32 Series Datasheet](https://documentation.espressif.com/esp32_datasheet_en.html) — caractéristiques de la puce, périphériques, ADC, PWM, UART, I2C, SPI et limitations de broches.
- [ESP-IDF Programming Guide: GPIO & RTC GPIO](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html) — tableau GPIO, broches de strapping, broches entrée uniquement, broches flash/PSRAM et limitation ADC2 avec Wi-Fi.
- [Espressif : ESP32 Hardware Design Guidelines](https://docs.espressif.com/projects/esp-hardware-design-guidelines/en/latest/esp32/esp-hardware-design-guidelines-en-master-esp32.pdf) — recommandations pour la puissance, les broches de strapping, GPIO, ADC et la conception de la carte.
- [Arduino-ESP32: LED Control API](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/ledc.html) — PWM/LEDC dans Arduino-ESP32 pour ventilateurs, rétroéclairage et autres signaux PWM.
- [Klipper: Code overview](https://www.klipper3d.org/Code_Overview.html) — contexte architectural de Klipper pour MCU et liste des backends micro-contrôleurs supportés dans l'arborescence source.
