---
title: "Construire son propre sécheur de filament"
description: "Documentation pratique pour construire un sécheur de filament, une chambre chauffée et des modules pour imprimante 3D: électronique, chauffage, ventilation, boîtier et sécurité."
---

# Construire son propre sécheur de filament

Cette section aide à concevoir et construire un sécheur de filament ou une chambre chauffée active pour imprimante 3D. Elle couvre les bases de l’électronique, le choix du contrôleur, les chauffages, ventilateurs, capteurs, le boîtier et les erreurs à éviter avant le premier montage.

Cette section couvre tout ce dont vous avez besoin pour construire un séchoir à filament à partir de zéro — des bases de l'électronique aux guides de câblage pratiques.

Aucune expérience en électronique préalable n'est requise. Chaque article se concentre sur un sujet spécifique et se lie au matériel connexe.

## Contenus

### 00. Commencez ici

| Fichier | Contenu |
|---|---|
| `00-start-here/01-introduction.md` | Pour qui est cette section, comment la lire et pourquoi le chemin va du simple au complexe. |

### 01. Bases de l'électronique

| Fichier | Contenu |
|---|---|
| `01-electronics-basics/01-load-calculation-24v.md` | Tension, courant, puissance, loi d'Ohm, calcul de charge 24V, déclassement, lecture des fiches techniques. |
| `01-electronics-basics/02-mosfet-module.md` | MOSFET comme interrupteur électronique, modules prêts à l'emploi, charges CC, ventilateurs, bandes LED, chauffages. |
| `01-electronics-basics/03-triac.md` | TRIAC pour les charges AC, optoisolateur, isolement galvanique, circuit d'amortissement, chaleur et dissipateur thermique. |
| `01-electronics-basics/04-solid-state-relay-ssr.md` | SSR, différences des relais mécaniques, variantes AC/DC, dissipateur thermique, sélection de tension et courant. |

### 02. Contrôleurs

| Fichier | Contenu |
|---|---|
| `02-controllers/00-how-to-choose-controller.md` | Tableau de sélection du contrôleur par tâche. Lisez ceci en premier. |
| `02-controllers/01-esp32-controller.md` | ESP32, Wi-Fi/Bluetooth, pourquoi ce n'est pas idéal comme MCU Klipper. |
| `02-controllers/02-arduino-controller.md` | Arduino comme plateforme d'apprentissage, limitations pour les appareils réels et Klipper. |
| `02-controllers/03-rp2040-controller.md` | RP2040/Pico, flashage facile via BOOTSEL, utilisation comme MCU Klipper. |
| `02-controllers/04-stm32-controllers.md` | Famille STM32, cartes d'imprimante, DFU/SWD/ST-Link, complexité de la sélection et du flashage. |
| `02-controllers/05-mcu-in-klipper.md` | Qu'est-ce qu'un MCU, le rôle de l'hôte Klipper, la configuration des broches, la planification G-code. |
| `02-controllers/06-uart-interface.md` | Interface série UART, croisement RX/TX, GND, niveaux 3.3V/5V. |
| `02-controllers/07-i2c-interface.md` | Bus I2C, SDA/SCL, adresses d'appareil, affichages, capteurs, lignes courtes. |
| `02-controllers/08-spi-interface.md` | SPI, MOSI/MISO/SCK/CS, affichages, RFID, échange de données rapide, CS séparé par appareil. |
| `02-controllers/09-can-interface.md` | Bus CAN, paire différentielle, cartes de tête d'outil, terminateurs, immunité au bruit. |
| `02-controllers/10-usb-uart-adapters.md` | Adaptateurs USB-UART, flashage, logs série, RX/TX, niveaux de tension, erreurs courantes. |
| `02-controllers/11-flashing-controller.md` | Ce que signifie le flashage, méthodes UF2/USB/DFU/ST-Link, processus de génération Klipper. |

### 03. Composants courants

| Fichier | Contenu |
|---|---|
| `03-common-components/01-overview.md` | Qu'est-ce que les composants, liste de sujets et leur rôle dans l'appareil. |
| `03-common-components/02-heaters.md` | Chauffages 12V/24V/110-230V AC, puissance, capteur de température, sécurité. |
| `03-common-components/03-fans.md` | Flux d'air, pression statique, bruit, types 2 broches/3 broches/4 broches. |
| `03-common-components/04-thermistors.md` | Thermistors, contact thermique, pâte thermique/manche, retour PID. |
| `03-common-components/05-led-strips.md` | Bandes LED 5V/12V/24V, courant par mètre, MOSFET, puissance, bandes adressables. |
| `03-common-components/06-servo-motors.md` | Moteurs servo, puissance, signal, courant de pic, alimentation séparée. |
| `03-common-components/07-load-cells.md` | Cellules de charge, amplificateur HX711, mécanique de montage, étalonnage. |
| `03-common-components/08-oled-display.md` | Affichages OLED, I2C/SPI, adresse, puissance, quand utiliser un affichage. |
| `03-common-components/09-touchscreen.md` | Écrans TFT/tactiles, UART/SPI/HDMI, puissance, compatibilité. |
| `03-common-components/10-rfid-and-nfc.md` | RFID/NFC, cartes, tags, fréquences, câblage, cas d'utilisation. |

### 04. Physique thermique et matériaux

| Fichier | Contenu |
|---|---|
| `04-thermal-physics-and-materials/01-overview.md` | Pourquoi une section sur la chaleur, les matériaux, les boîtiers, l'isolation et la sécurité. |
| `04-thermal-physics-and-materials/02-thermal-conductivity.md` | Conductivité thermique, isolation, ponts thermiques, cotes de température des matériaux. |
| `04-thermal-physics-and-materials/03-material-safety.md` | Inflammabilité, fumées, toxicité, PIR/XPS/EPS, fiches de sécurité des matériaux (SDS/MSDS). |
| `04-thermal-physics-and-materials/04-convection-and-airflow.md` | Convection, chauffage 100W sans flux d'air vs faible vs flux approprié, transfert de chaleur. |

### 05. Outils (était 04 dans la structure du dossier EN — note : le dossier est `05-tools/`)

| Fichier | Contenu |
|---|---|
| `05-tools/01-overview.md` | Liste des outils : multimètre, USB-TTL, soudage, sertissage, ST-Link, oscilloscope. |
| `05-tools/02-multimeter.md` | Tension, continuité, résistance, sécurité de mesure. |
| `05-tools/03-usb-ttl-adapter.md` | Adaptateur USB-TTL/USB-UART, flashage, logs série, RX/TX, niveaux de tension. |
| `05-tools/04-soldering.md` | Soudage de fils, connecteurs JST, thermistors, erreurs courantes. |
| `05-tools/05-crimping-connectors.md` | Sertissage de bornes et connecteurs, qualité de contact, mauvaises soudures sertis. |
| `05-tools/06-st-link.md` | ST-Link, STM32, interface SWD, récupération après le flashage échoué. |
| `05-tools/07-oscilloscope.md` | PWM, UART, bruit, affaissement de tension, sécurité de tension secteur, mesure de fréquence. |

### 06. Guides pratiques (dossier : `06-practical-guides/`)

| Fichier | Contenu |
|---|---|
| `06-practical-guides/01-connecting-fan.md` | Câblage du ventilateur, tension, contrôle côté contrôleur, bruit. |
| `06-practical-guides/02-checking-thermistor.md` | Vérification du thermisteur avec un multimètre, résistance, câblage, lectures du firmware. |
| `06-practical-guides/03-connecting-servo.md` | Alimentation du servo, ligne de signal, courant de pic, redémarrages du contrôleur. |
| `06-practical-guides/04-connecting-load-cell.md` | Cellule de charge, amplificateur HX711, puissance, fils de signal, étalonnage. |
| `06-practical-guides/05-connecting-rfid-reader.md` | Lecteur RFID, puissance, SPI/UART/I2C, erreurs courantes. |

### 07. Impression 3D (dossier : `07-3d-printing/`)

| Fichier | Contenu |
|---|---|
| `07-3d-printing/01-overview.md` | Pourquoi une section sur les pièces imprimées, les boîtiers, les conduits et les montages. |
| `07-3d-printing/02-what-is-stl.md` | Format STL, limitations, pourquoi un fichier STL n'est pas suffisant pour l'assemblage. |
| `07-3d-printing/03-materials-petg-abs-asa.md` | PETG, ABS, ASA — où l'utiliser, limites près des sources de chaleur. |
| `07-3d-printing/04-heat-resistant-materials.md` | Matériaux pour les pièces près de la chaleur, déformation, marge de température. |
| `07-3d-printing/05-enclosure-design.md` | Conception de boîtier, ventilation, montages, espace libre du chauffage, accès au service. |
| `07-3d-printing/06-why-pla-is-risky.md` | PLA près des sources de chaleur, ramollissement, déformation, risque d'échec du boîtier. |

### 08. Erreurs courantes (dossier : `08-common-mistakes/`)

| Fichier | Contenu |
|---|---|
| `08-common-mistakes/01-overview.md` | Liste des erreurs typiques et la logique derrière la section diagnostic. |
| `08-common-mistakes/02-power-mistakes.md` | Alimentations faibles, affaissement de tension, marge d'alimentation, mauvaises bornes. |
| `08-common-mistakes/03-wiring-mistakes.md` | Fils échangés, mise à la terre manquante, RX/TX, fils minces, mauvaises connexions. |
| `08-common-mistakes/04-controller-mistakes.md` | Incompatibilité 3.3V/5V, mauvaise carte, firmware, niveaux de signal. |
| `08-common-mistakes/05-heater-ssr-mistakes.md` | Chauffages, SSR, courant alternatif 110-230V, dissipateurs thermiques, type de relais incorrect. |
| `08-common-mistakes/06-diagnostic-checklist.md` | Séquence de diagnostic d'appareil rapide et étape par étape. |
