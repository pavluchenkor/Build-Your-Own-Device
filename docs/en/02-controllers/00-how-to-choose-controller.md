# How to choose a controller

This section describes four families of controllers: ESP32, Arduino, RP2040, and STM32. All of them can control fans, read sensors, and switch loads. The difference is what each one is best suited for.

## Quick selection

| Task | Controller |
|---|---|
| Standalone dryer or Wi-Fi sensor | ESP32 |
| Educational prototype, first experiments | Arduino |
| MCU in Klipper (extra pins) | RP2040 |
| Printer board, MCU in Klipper | STM32 |

## If you work with Klipper

Klipper uses a "host + MCU" architecture. The host is a Raspberry Pi or similar computer. The MCU is a separate microcontroller that manages heaters, fans, and sensors in real time.

For an MCU in Klipper, look at **RP2040** or **STM32**: they are well supported, can be flashed without ST-Link, and work directly over USB or CAN.

ESP32 is not the best choice as an MCU for Klipper — it does not have native Klipper firmware support in the same way that STM32 or RP2040 do.

## If you are building a standalone device

ESP32 is a good choice if the device must work on its own: read sensors, manage heating, send data over Wi-Fi, or show a page in a browser.

Arduino is suitable for a simple prototype or educational project, but its limitations — RAM, Flash, weak ADC, and outdated USB — make it a poor choice for a final device.

## What to read next

- [ESP32](./01-esp32-controller.md) — Wi-Fi, sensors, web interface
- [Arduino](./02-arduino-controller.md) — getting started and experiments
- [RP2040](./03-rp2040-controller.md) — Klipper MCU, simple firmware
- [STM32](./04-stm32-controllers.md) — printer boards, CAN, SWD
- [MCU in Klipper](./05-mcu-in-klipper.md) — how an MCU is integrated into a Klipper system
