---
title: "Controller für einen DIY-Filamenttrockner auswählen"
description: "Vergleich von ESP32, Arduino, RP2040, STM32 und Klipper MCU für Filamenttrockner, beheizte Kammer, Beleuchtung, Sensoren und weitere 3D-Drucker-Module."
---

# Controller für einen DIY-Filamenttrockner auswählen

Der Controller bestimmt, wie ein Filamenttrockner oder eine beheizte Kammer Heizung, Lüfter, Beleuchtung, Sensoren und die Kommunikation mit dem Drucker steuert. Diese Seite hilft bei der Wahl der Plattform für einfache Module, Wi-Fi-Geräte, Klipper MCU oder erweiterbare Projekte.

Dieser Abschnitt beschreibt vier Familien von Controllern: ESP32, Arduino, RP2040 und STM32. Alle können Lüfter steuern, Sensoren auslesen und Lasten schalten. Der Unterschied liegt darin, wofür jeder am besten geeignet ist.

## Schnellauswahl

| Aufgabe | Controller |
|---|---|
| Standalone-Trockner oder Wi-Fi-Sensor | ESP32 |
| Lehr-Prototyp, erste Experimente | Arduino |
| MCU in Klipper (zusätzliche Pins) | RP2040 |
| Druckerplatine, MCU in Klipper | STM32 |

## Wenn Sie mit Klipper arbeiten

Klipper nutzt eine "Host + MCU"-Architektur. Der Host ist ein Raspberry Pi oder ähnlicher Computer. Das MCU ist ein separater Mikrocontroller, der in Echtzeit Heizer, Lüfter und Sensoren verwaltet.

Für ein MCU in Klipper schauen Sie sich **RP2040** oder **STM32** an: Sie werden gut unterstützt, können ohne ST-Link geflasht werden und funktionieren direkt über USB oder CAN.

ESP32 ist nicht die beste Wahl als MCU für Klipper — es hat keine native Klipper-Firmware-Unterstützung wie STM32 oder RP2040.

## Wenn Sie ein eigenständiges Gerät entwickeln

ESP32 ist eine gute Wahl, wenn das Gerät eigenständig funktionieren muss: Sensoren auslesen, Heizung verwalten, Daten über Wi-Fi versenden oder eine Seite im Browser anzeigen.

Arduino ist geeignet für einen einfachen Prototyp oder ein Lehr-Projekt, aber seine Einschränkungen — RAM, Flash, schwacher ADC und veraltetes USB — machen es zu einer schlechten Wahl für ein finales Gerät.

## Was Sie danach lesen sollten

- [ESP32](./01-esp32-controller.md) — Wi-Fi, Sensoren, Web-Interface
- [Arduino](./02-arduino-controller.md) — Erste Schritte und Experimente
- [RP2040](./03-rp2040-controller.md) — Klipper MCU, einfache Firmware
- [STM32](./04-stm32-controllers.md) — Druckerplatinen, CAN, SWD
- [MCU in Klipper](./05-mcu-in-klipper.md) — wie ein MCU in einem Klipper-System integriert wird
