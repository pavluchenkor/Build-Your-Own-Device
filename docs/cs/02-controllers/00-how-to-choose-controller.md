# Jak zvolit řídící prvek

Tato část popisuje čtyři rodiny řídících prvků: ESP32, Arduino, RP2040 a STM32. Všechny z nich mohou ovládat ventilátory, číst senzory a přepínat zátěže. Rozdíl je v tom, na co je každá nejlépe vhodná.

## Rychlý výběr

| Úkol | Řídící prvek |
|---|---|
| Samostatná sušička nebo Wi-Fi senzor | ESP32 |
| Vzdělávací prototyp, první experimenty | Arduino |
| MCU v Klipper (extra piny) | RP2040 |
| Deska tiskárny, MCU v Klipper | STM32 |

## Pokud pracujete s Klipper

Klipper používá architekturu "host + MCU". Host je Raspberry Pi nebo podobný počítač. MCU je samostatný mikrokontrolér, který spravuje topidla, ventilátory a senzory v reálném čase.

Pro MCU v Klipper se podívejte na **RP2040** nebo **STM32**: jsou dobře podporovány, lze je flashovat bez ST-Link a fungují přímo přes USB nebo CAN.

ESP32 není nejlepší volbou jako MCU pro Klipper — nemá nativní podporu firmware Klipper stejným způsobem jako STM32 nebo RP2040.

## Pokud budujete samostatné zařízení

ESP32 je dobrá volba, pokud se zařízení musí provozovat samostatně: číst senzory, spravovat vytápění, posílat data přes Wi-Fi nebo zobrazit stránku v prohlížeči.

Arduino je vhodné pro jednoduchý prototyp nebo vzdělávací projekt, ale jeho omezení — RAM, Flash, slabé ADC a zastaralé USB — jej činí špatnou volbou pro konečné zařízení.

## Co si dál přečíst

- [ESP32](./01-esp32-controller.md) — Wi-Fi, senzory, webové rozhraní
- [Arduino](./02-arduino-controller.md) — začínáme a experimenty
- [RP2040](./03-rp2040-controller.md) — MCU Klipper, jednoduchý firmware
- [STM32](./04-stm32-controllers.md) — desky tiskárny, CAN, SWD
- [MCU v Klipper](./05-mcu-in-klipper.md) — jak je MCU integrován do systému Klipper
