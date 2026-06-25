---
title: "Build your own filament dryer"
description : "Documentation pratique pour la construction d'un séchoir à filament, d'une chambre chauffée et de modules de support pour une imprimante 3D : électronique, chauffage, flux d'air, boîtier et sécurité."
---

# Construisez votre propre sèche-filament

Cette section vous aide à concevoir et à construire votre propre sèche-filament ou chambre chauffée active pour une imprimante 3D. Elle couvre les bases de l'électronique, la sélection du contrôleur, les éléments chauffants, les ventilateurs, les capteurs, la conception du boîtier et les erreurs courantes à corriger avant la première construction.

Cette section couvre tout ce dont vous avez besoin pour construire un sèche-filament de zéro — des fondamentaux de l'électronique aux guides de câblage pratiques.

Aucune expérience préalable en électronique n'est requise. Chaque article se concentre sur un sujet spécifique et renvoie au matériel connexe.

## Table des matières

### 00. Commencez ici

| Fichier | Contenu |
|---|---|
| `00-start-here/01-introduction.md` | Pour qui est cette section, comment la lire et pourquoi le chemin va du simple au complexe. |

### 01. Bases de l'électronique

| Fichier | Contenu |
|---|---|
| `01-electronics-basics/01-load-calculation-24v.md` | Tension, courant, puissance, loi d'Ohm, calcul de charge 24V, dégonflement, lecture des fiches techniques. |
| `01-electronics-basics/02-mosfet-module.md` | MOSFET en tant qu'interrupteur électronique, modules prêts à l'emploi, charges CC, ventilateurs, bandes LED, éléments chauffants. |
| `01-electronics-basics/03-triac.md` | TRIAC pour les charges CA, optocoupleur, isolation galvanique, circuit d'amortissement, chaleur et dissipateur. |
| `01-electronics-basics/04-solid-state-relay-ssr.md` | SSR, différences par rapport aux relais mécaniques, variantes CA/CC, dissipateur, sélection de tension et de courant. |

### 02. Contrôleurs

| Fichier | Contenu |
|---|---|
| `02-controllers/00-how-to-choose-controller.md` | Tableau de sélection du contrôleur par tâche. Lisez ceci en premier. |
| `02-controllers/01-esp32-controller.md` | ESP32, Wi-Fi/Bluetooth, pourquoi ce n'est pas idéal comme MCU Klipper. |
| `02-controllers/02-arduino-controller.md` | Arduino en tant que plateforme d'apprentissage, limitations pour les appareils réels et Klipper. |
| `02-controllers/03-rp2040-controller.md` | RP2040/Pico, flashage facile via BOOTSEL, utilisation comme MCU Klipper. |
| `02-controllers/04-stm32-controllers.md` | Famille STM32, cartes d'imprimantes, DFU/SWD/ST-Link, complexité de sélection et de flashage. |
| `02-controllers/05-mcu-in-klipper.md` | Ce qu'est une MCU, rôle de l'hôte Klipper, configuration des broches, programmation G-code. |
| `02-controllers/06-uart-interface.md` | Interface série UART, croisement RX/TX, GND, niveaux 3.3V/5V. |
| `02-controllers/07-i2c-interface.md` | Bus I2C, SDA/SCL, adresses de périphériques, affichages, capteurs, lignes courtes. |
| `02-controllers/08-spi-interface.md` | SPI, MOSI/MISO/SCK/CS, affichages, RFID, échange de données rapide, CS séparé par périphérique. |
| `02-controllers/09-can-interface.md` | Bus CAN, paire différentielle, cartes de têtes d'outil, terminateurs, immunité au bruit. |
| `02-controllers/10-usb-uart-adapters.md` | Adaptateurs USB-UART, flashage, journaux série, RX/TX, niveaux de tension, erreurs courantes. |
| `02-controllers/11-flashing-controller.md` | Ce que signifie le flashage, méthodes UF2/USB/DFU/ST-Link, processus de construction Klipper. |

### 03. Composants courants

| Fichier | Contenu |
|---|---|
| `03-common-components/01-overview.md` | Ce que sont les composants, liste des sujets et leur rôle dans l'appareil. |
| `03-common-components/02-heaters.md` | Éléments chauffants 12V/24V/110–230V CA, puissance, capteur de température, sécurité. |
| `03-common-components/03-fans.md` | Flux d'air, pression statique, bruit, types 2 broches/3 broches/4 broches. |
| `03-common-components/04-thermistors.md` | Thermistances, contact thermique, pâte/gaine thermique, rétroaction PID. |
| `03-common-components/05-led-strips.md` | Bandes LED 5V/12V/24V, courant par mètre, MOSFET, puissance, bandes adressables. |
| `03-common-components/06-servo-motors.md` | Servomoteurs, puissance, signal, courant de crête, alimentation séparée. |
| `03-common-components/07-load-cells.md` | Jauges de charge, amplificateur HX711, mécanique de montage, étalonnage. |
| `03-common-components/08-oled-display.md` | Affichages OLED, I2C/SPI, adresse, puissance, quand utiliser un affichage. |
| `03-common-components/09-touchscreen.md` | Écrans tactiles TFT, UART/SPI/HDMI, puissance, compatibilité. |
| `03-common-components/10-rfid-and-nfc.md` | RFID/NFC, cartes, étiquettes, fréquences, câblage, cas d'utilisation. |

### 04. Physique thermique et matériaux

| Fichier | Contenu |
|---|---|
| `04-thermal-physics-and-materials/01-overview.md` | Pourquoi une section sur la chaleur, les matériaux, les boîtiers, l'isolation et la sécurité. |
| `04-thermal-physics-and-materials/02-thermal-conductivity.md` | Conductivité thermique, isolation, ponts thermiques, indices de température des matériaux. |
| `04-thermal-physics-and-materials/03-material-safety.md` | Inflammabilité, vapeurs, toxicité, PIR/XPS/EPS, fiches de sécurité (SDS/MSDS). |
| `04-thermal-physics-and-materials/04-convection-and-airflow.md` | Convection, élément chauffant 100W sans flux vs. flux faible vs. flux d'air approprié, transfert de chaleur. |

### 05. Outils

| Fichier | Contenu |
|---|---|
| `05-tools/01-overview.md` | Liste des outils : multimètre, USB-TTL, soudage, sertissage, ST-Link, oscilloscope. |
| `05-tools/02-multimeter.md` | Tension, continuité, résistance, sécurité de la mesure. |
| `05-tools/03-usb-ttl-adapter.md` | Adaptateur USB-TTL/USB-UART, flashage, journaux série, RX/TX, niveaux de tension. |
| `05-tools/04-soldering.md` | Soudage de fils, connecteurs JST, thermistances, erreurs courantes. |
| `05-tools/05-crimping-connectors.md` | Sertissage de terminaux et de connecteurs, qualité de contact, mauvaises connexions sertis. |
| `05-tools/06-st-link.md` | ST-Link, STM32, interface SWD, récupération après un flashage échoué. |
| `05-tools/07-oscilloscope.md` | PWM, UART, bruit, chute de tension, sécurité de la tension secteur, mesure de fréquence. |

### 06. Guides pratiques

| Fichier | Contenu |
|---|---|
| `06-practical-guides/01-connecting-fan.md` | Câblage du ventilateur, tension, contrôle du côté du contrôleur, bruit. |
| `06-practical-guides/02-checking-thermistor.md` | Vérification thermistance avec multimètre, résistance, câblage, lectures du firmware. |
| `06-practical-guides/03-connecting-servo.md` | Alimentation du servomoteur, ligne de signal, courant de crête, réinitialisations du contrôleur. |
| `06-practical-guides/04-connecting-load-cell.md` | Jauge de charge, amplificateur HX711, puissance, fils de signal, étalonnage. |
| `06-practical-guides/05-connecting-rfid-reader.md` | Lecteur RFID, puissance, SPI/UART/I2C, erreurs courantes. |

### 07. Impression 3D

| Fichier | Contenu |
|---|---|
| `07-3d-printing/01-overview.md` | Pourquoi une section sur les pièces imprimées, les boîtiers, les conduits et les supports. |
| `07-3d-printing/02-what-is-stl.md` | Format STL, limitations, pourquoi un fichier STL ne suffit pas pour l'assemblage. |
| `07-3d-printing/03-materials-petg-abs-asa.md` | PETG, ABS, ASA — où les utiliser, limites près des sources de chaleur. |
| `07-3d-printing/04-heat-resistant-materials.md` | Matériaux pour les pièces près de la chaleur, déformation, marge de température. |
| `07-3d-printing/05-enclosure-design.md` | Conception du boîtier, ventilation, supports, distance du chauffage, accès de service. |
| `07-3d-printing/06-why-pla-is-risky.md` | PLA près des sources de chaleur, ramollissement, déformation, risque de défaillance du boîtier. |

### 08. Erreurs courantes

| Fichier | Contenu |
|---|---|
| `08-common-mistakes/01-overview.md` | Liste des erreurs typiques et la logique derrière la section de diagnostic. |
| `08-common-mistakes/02-power-mistakes.md` | Alimentations faibles, chute de tension, marge de puissance, mauvais terminaux. |
| `08-common-mistakes/03-wiring-mistakes.md` | Fils permutés, terre manquante, RX/TX, fils fins, mauvaises connexions. |
| `08-common-mistakes/04-controller-mistakes.md` | Inadéquation 3.3V/5V, mauvaise carte, firmware, niveaux de signal. |
| `08-common-mistakes/05-heater-ssr-mistakes.md` | Éléments chauffants, SSR, 110–230V CA, dissipateurs, type de relais incorrect. |
| `08-common-mistakes/06-diagnostic-checklist.md` | Séquence rapide de diagnostic d'appareil étape par étape. |
