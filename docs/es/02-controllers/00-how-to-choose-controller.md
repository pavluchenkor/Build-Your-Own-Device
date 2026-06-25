---
title: "Cómo elegir un controlador para un secador de filamento DIY"
description: "Comparación de ESP32, Arduino, RP2040, STM32 y Klipper MCU para secador de filamento, cámara calefactada, iluminación, sensores y otros módulos de impresora 3D."
---

# Cómo elegir un controlador para un secador de filamento DIY

El controlador define cómo un secador de filamento o una cámara calefactada controla calefacción, ventiladores, iluminación, sensores y comunicación con la impresora. Esta página ayuda a elegir la plataforma adecuada.

Esta sección describe cuatro familias de controladores: ESP32, Arduino, RP2040 y STM32. Todos pueden controlar ventiladores, leer sensores e interrumpir cargas. La diferencia es para qué está mejor adaptado cada uno.

## Selección rápida

| Tarea | Controlador |
|---|---|
| Secadora autónoma o sensor Wi-Fi | ESP32 |
| Prototipo educativo, primeros experimentos | Arduino |
| MCU en Klipper (pines adicionales) | RP2040 |
| Placa de impresora, MCU en Klipper | STM32 |

## Si trabaja con Klipper

Klipper utiliza una arquitectura "host + MCU". El host es un Raspberry Pi u ordenador similar. El MCU es un microcontrolador separado que gestiona calentadores, ventiladores y sensores en tiempo real.

Para un MCU en Klipper, considere **RP2040** o **STM32**: tienen buen soporte, se pueden grabar sin ST-Link y funcionan directamente en USB o CAN.

ESP32 no es la mejor opción como MCU para Klipper — no tiene soporte de firmware Klipper nativo de la misma manera que STM32 o RP2040.

## Si está construyendo un dispositivo autónomo

ESP32 es una buena opción si el dispositivo debe funcionar solo: leer sensores, gestionar calefacción, enviar datos por Wi-Fi o mostrar una página en un navegador.

Arduino es adecuado para un prototipo simple o proyecto educativo, pero sus limitaciones (RAM, Flash, ADC débil y USB obsoleto) lo hacen una mala opción para un dispositivo final.

## Qué leer después

- [ESP32](./01-esp32-controller.md) — Wi-Fi, sensores, interfaz web
- [Arduino](./02-arduino-controller.md) — primeros pasos y experimentos
- [RP2040](./03-rp2040-controller.md) — MCU Klipper, firmware simple
- [STM32](./04-stm32-controllers.md) — placas de impresora, CAN, SWD
- [MCU en Klipper](./05-mcu-in-klipper.md) — cómo se integra un MCU en un sistema Klipper
