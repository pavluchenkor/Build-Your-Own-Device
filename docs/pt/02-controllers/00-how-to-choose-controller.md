---
title: "Como escolher um controlador para um secador de filamento DIY"
description: "Comparação de ESP32, Arduino, RP2040, STM32 e Klipper MCU para secador de filamento, câmara aquecida, iluminação, sensores e outros módulos de impressora 3D."
---

# Como escolher um controlador para um secador de filamento DIY

O controlador define como o secador de filamento ou a câmara aquecida controla aquecimento, ventoinhas, iluminação, sensores e comunicação com a impressora. Esta página ajuda a escolher a plataforma certa.

Esta seção descreve quatro famílias de controladores: ESP32, Arduino, RP2040 e STM32. Todos eles podem controlar ventiladores, ler sensores e comutar cargas. A diferença é para o que cada um é melhor adequado.

## Seleção rápida

| Tarefa | Controlador |
|---|---|
| Secadora autónoma ou sensor Wi-Fi | ESP32 |
| Protótipo educacional, primeiras experiências | Arduino |
| MCU em Klipper (pinos extras) | RP2040 |
| Placa de impressora, MCU em Klipper | STM32 |

## Se trabalha com Klipper

Klipper usa uma arquitectura "anfitrião + MCU". O anfitrião é um Raspberry Pi ou computador similar. O MCU é um microcontrolador separado que gere aquecedores, ventiladores e sensores em tempo real.

Para um MCU em Klipper, procure **RP2040** ou **STM32**: são bem suportados, podem ser gravados sem ST-Link e funcionam directamente através de USB ou CAN.

ESP32 não é a melhor escolha como MCU para Klipper — não tem suporte de firmware Klipper nativo da mesma forma que STM32 ou RP2040.

## Se está construindo um dispositivo autónomo

ESP32 é uma boa escolha se o dispositivo deve funcionar por conta própria: ler sensores, gerenciar aquecimento, enviar dados via Wi-Fi ou mostrar uma página num navegador.

Arduino é adequado para um protótipo simples ou projeto educacional, mas suas limitações — RAM, Flash, ADC fraco e USB desactualizado — tornam-no uma má escolha para um dispositivo final.

## O que ler a seguir

- [ESP32](./01-esp32-controller.md) — Wi-Fi, sensores, interface web
- [Arduino](./02-arduino-controller.md) — como começar e experiências
- [RP2040](./03-rp2040-controller.md) — MCU Klipper, firmware simples
- [STM32](./04-stm32-controllers.md) — placas de impressora, CAN, SWD
- [MCU em Klipper](./05-mcu-in-klipper.md) — como um MCU é integrado num sistema Klipper
