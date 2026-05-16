# Erreurs du contrôleur

Un contrôleur n'est pas une boîte universelle où vous pouvez tout brancher directement.

Il lit les capteurs, produit les signaux de contrôle et communique avec l'hôte. Mais les charges d'alimentation doivent être alimentées par les sorties appropriées, MOSFETs, relais, SSRs ou drivers.

## Symptômes

Les signes typiques de problèmes de contrôleur ou de connexion :

- la carte n'est pas détectée via USB ;
- le firmware ne démarre pas ;
- les broches ne répondent pas ;
- le contrôleur redémarre ;
- le contrôleur se réchauffe considérablement ;
- la carte s'arrête après la connexion du module ;
- ESP32 perd le Wi-Fi quand la charge est activée ;
- le capteur n'est pas visible bien que l'alimentation soit présente ;
- Klipper ne se connecte pas au MCU ;
- les commandes fonctionnent sur une mauvaise broche.

## Mauvais contrôleur choisi

Avant de choisir une carte, vous devez comprendre la tâche.

Pour un appareil autonome Wi-Fi simple, ESP32 peut être un bon choix.

Pour un MCU supplémentaire dans Klipper, il est souvent plus pratique de regarder :

- RP2040 ;
- STM32 ;
- la carte d'imprimante 3D prête à l'emploi.

Arduino Uno/Nano sont utiles pour apprendre et les expériences simples, mais pour un nouvel appareil sérieux autour d'une imprimante, vous rencontrez rapidement des limites.

L'erreur est de choisir une carte seulement parce que « c'est populaire », sans vérifier :

- le nombre de broches nécessaires ;
- les niveaux de logique ;
- l'alimentation ;
- le support du firmware ;
- la disponibilité USB/UART/CAN ;
- le support des bibliothèques nécessaires ;
- le courant de sortie ;
- l'environnement de développement.

## ESP32 comme MCU Klipper

ESP32 est utile comme appareil IoT/Wi-Fi séparé.

Mais ne comptez pas automatiquement sur ESP32 comme meilleur choix en tant que MCU Klipper.

Si l'objectif est l'intégration avec Klipper comme MCU supplémentaire, regardez d'abord les options officielles et éprouvées pour Klipper. Pour les nouvelles extensions matérielles, il est souvent plus simple et plus fiable d'utiliser RP2040 ou STM32.

ESP32 est bon si l'appareil doit :

- fonctionner de manière autonome ;
- avoir Wi-Fi ;
- fournir des données via MQTT ou HTTP ;
- avoir une interface Web ;
- communiquer avec Home Assistant ;
- fonctionner séparément de Klipper.

## Logique 3.3V et 5V

De nombreux contrôleurs modernes fonctionnent avec la logique 3.3V.

Par exemple :

- ESP32 ;
- RP2040 ;
- de nombreux STM32.

L'erreur est d'appliquer un signal 5V à une entrée conçue seulement pour 3.3V.

Cela peut :

- endommager immédiatement la broche ;
- endommager le contrôleur plus tard ;
- causer un fonctionnement instable ;
- casser un module qui semblait correct.

Avant de connecter, vérifiez :

- la tension d'alimentation du module ;
- le niveau de logique d'entrée/sortie ;
- est-il y a un convertisseur de niveau ;
- l'entrée accepte-t-elle 5V ;
- ce qui est écrit dans la description technique.

## GPIO ne fait pas fonctionner une charge

GPIO est une broche de signal.

Il ne doit pas alimenter :

- ventilateur ;
- servo ;
- chauffage ;
- bande LED ;
- relais sans driver ;
- solénoïde ;
- moteur.

GPIO peut envoyer une commande. Le courant de charge doit passer par une sortie d'alimentation, un MOSFET, un driver, un relais ou un module séparé.

Si la charge est connectée directement à GPIO, vous pouvez endommager la broche ou l'ensemble de la carte.

## Pas de GND commune

Un contrôleur peut drive un module externe seulement s'ils ont un niveau de référence commun.

Erreur typique :

- servo alimenté à partir d'une alimentation 5V séparée ;
- le signal vient du contrôleur ;
- « GND » non connectée ;
- le servo saccade ou ne répond pas.

Pareil avec les modules MOSFET, ventilateurs PWM, certains capteurs et cartes externes.

## Firmware incorrect

La carte peut être correcte, mais le firmware n'y correspond pas.

Erreurs :

- le firmware flashé pour le mauvais microcontrôleur ;
- a choisi le mauvais bootloader ;
- a mélangé le firmware USB et UART ;
- a choisi le mauvais port série ;
- Klipper a spécifié le mauvais chemin d'appareil ;
- les broches dans la configuration ne correspondent pas à la carte ;
- n'a pas redémarré le firmware/hôte après le flashage.

Avant de flasher, vous devez connaître exactement le modèle de la carte et du microcontrôleur.

## La broche existe sur le schéma mais ne convient pas

Pas toutes les broches sont les mêmes.

Les broches peuvent avoir des restrictions :

- entrée seulement ;
- utilisée par USB/UART/SPI ;
- utilisée lors du démarrage ;
- liée au mode de démarrage ;
- ne supporte pas le PWM nécessaire ;
- tiré vers le haut ou vers le bas ;
- conflit avec un autre module.

Si une broche se comporte étrangement, vérifiez la documentation de la carte, pas seulement le numéro GPIO.

## Ce à vérifier

Mini-liste de contrôle :

1. La bonne carte est-elle choisie pour la tâche ?
2. Quelle alimentation la carte a-t-elle besoin ?
3. Quelle logique : 3.3V ou 5V ?
4. Y a-t-il une « GND » commune avec les modules externes ?
5. La charge n'est-elle pas alimentée par GPIO ?
6. La carte supporte-t-elle l'interface nécessaire ?
7. La broche sélectionnée n'est-elle pas utilisée ?
8. Le firmware est-il correct ?
9. La carte est-elle visible via USB ?
10. La configuration correspond-elle au pinout de la carte ?

## Ce à ne pas faire

Vous ne pouvez pas :

- appliquer 5V à l'entrée 3.3V sans vérifier ;
- connecter la charge directement à GPIO ;
- flasher le firmware aléatoire d'une carte « similaire » ;
- changer le câblage sous tension ;
- supposer que n'importe quel GPIO convient à n'importe quelle tâche ;
- ignorer le chauffage du contrôleur ;
- connecter les modules externes sans masse commune quand elle est nécessaire.

## Points clés

- Le contrôleur contrôle mais ne fait pas directement fonctionner une charge.
- La logique 3.3V et 5V doit être compatible.
- GPIO est un signal, pas une alimentation.
- Pour Klipper MCU, vous regardez souvent RP2040/STM32, ESP32 est plus pratique comme appareil Wi-Fi autonome.
- Le firmware et le pinout doivent correspondre à la carte réelle.
- Si la carte se réchauffe ou cesse d'être détectée, éteignez l'alimentation et trouvez l'erreur de connexion.

## Références

- [Klipper : Installation](https://www.klipper3d.org/Installation.html) - processus général de préparation et de flashage du MCU pour Klipper.
- [Klipper : Config Reference, MCU](https://www.klipper3d.org/Config_Reference.html#mcu) - la section « [mcu] », la connexion série/CAN et les MCUs supplémentaires.
- [Arduino : Broches numériques](https://docs.arduino.cc/learn/microcontrollers/digital-pins/) - explication de base des broches numériques comme entrées/sorties, pas l'alimentation.
- [Fiche technique ESP32 d'Espressif](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf) - spécifications électriques officielles d'ESP32.
- [Fiche technique Raspberry Pi Pico](https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf) - données officielles sur RP2040/Pico, alimentation et GPIO.
