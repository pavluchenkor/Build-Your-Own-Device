---
title: "Choisir un contrôleur pour un sécheur de filament DIY"
description: "Comparaison ESP32, Arduino, RP2040, STM32 et Klipper MCU pour sécheur de filament, chambre chauffée, éclairage, capteurs et modules d’imprimante 3D."
---

# Choisir un contrôleur pour un sécheur de filament DIY

Le contrôleur définit comment le sécheur de filament ou la chambre chauffée pilote le chauffage, les ventilateurs, l’éclairage, les capteurs et la communication avec l’imprimante. Cette page aide à choisir une plateforme selon le projet.

Cette section décrit quatre familles de contrôleurs : ESP32, Arduino, RP2040 et STM32. Tous peuvent contrôler les ventilateurs, lire les capteurs et commuter les charges. La différence est celle pour laquelle chacun est le mieux adapté.

## Sélection rapide

| Tâche | Contrôleur |
|---|---|
| Sèche-linge autonome ou capteur Wi-Fi | ESP32 |
| Prototype pédagogique, premières expériences | Arduino |
| MCU dans Klipper (broches supplémentaires) | RP2040 |
| Plaque d'imprimante, MCU dans Klipper | STM32 |

## Si vous travaillez avec Klipper

Klipper utilise une architecture « hôte + MCU ». L'hôte est un Raspberry Pi ou un ordinateur similaire. Le MCU est un microcontrôleur distinct qui gère les radiateurs, ventilateurs et capteurs en temps réel.

Pour un MCU dans Klipper, regardez **RP2040** ou **STM32** : ils sont bien supportés, peuvent être flashés sans ST-Link et fonctionnent directement sur USB ou CAN.

ESP32 n'est pas le meilleur choix comme MCU pour Klipper — il n'a pas le support du firmware Klipper natif de la même manière que STM32 ou RP2040.

## Si vous construisez un appareil autonome

ESP32 est un bon choix si l'appareil doit fonctionner seul : lire les capteurs, gérer le chauffage, envoyer des données via Wi-Fi ou afficher une page dans un navigateur.

Arduino convient pour un prototype simple ou un projet pédagogique, mais ses limitations — RAM, Flash, ADC faibles et USB obsolètes — le font un mauvais choix pour un appareil final.

## Quoi lire après

- [ESP32](./01-esp32-controller.md) — Wi-Fi, capteurs, interface Web
- [Arduino](./02-arduino-controller.md) — premiers pas et expériences
- [RP2040](./03-rp2040-controller.md) — MCU Klipper, firmware simple
- [STM32](./04-stm32-controllers.md) — plaques d'imprimante, CAN, SWD
- [MCU dans Klipper](./05-mcu-in-klipper.md) — comment un MCU est intégré dans un système Klipper
