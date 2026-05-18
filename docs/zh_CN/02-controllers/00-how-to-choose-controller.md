# 如何选择控制器

本节介绍四个控制器系列：ESP32、Arduino、RP2040 和 STM32。它们都可以控制风扇、读取传感器和切换负载。差别在于每个控制器最适合的用途。

## 快速选择

| 任务 | 控制器 |
|---|---|
| 独立烘干机或 Wi-Fi 传感器 | ESP32 |
| 教育原型、初步实验 | Arduino |
| Klipper 中的微控制器（额外引脚） | RP2040 |
| 打印机板、Klipper 中的微控制器 | STM32 |

## 如果您使用 Klipper

Klipper 使用"主机 + 微控制器"架构。主机是 Raspberry Pi 或类似的计算机。微控制器是一个单独的微控制器，实时管理加热器、风扇和传感器。

对于 Klipper 中的微控制器，请考虑 **RP2040** 或 **STM32**：它们得到良好支持，可以不用 ST-Link 刷写，并且可以通过 USB 或 CAN 直接工作。

ESP32 作为 Klipper 的微控制器不是最佳选择——它没有以与 STM32 或 RP2040 相同的方式获得原生 Klipper 固件支持。

## 如果您正在构建独立设备

如果设备必须独立工作，ESP32 是一个不错的选择：读取传感器、管理加热、通过 Wi-Fi 发送数据或在浏览器中显示页面。

Arduino 适合简单的原型或教育项目，但其局限性——RAM、Flash、较弱的 ADC 和过时的 USB——使其成为最终设备的糟糕选择。

## 接下来阅读什么

- [ESP32](./01-esp32-controller.md) — Wi-Fi、传感器、Web 界面
- [Arduino](./02-arduino-controller.md) — 入门和实验
- [RP2040](./03-rp2040-controller.md) — Klipper MCU、简单固件
- [STM32](./04-stm32-controllers.md) — 打印机板、CAN、SWD
- [MCU in Klipper](./05-mcu-in-klipper.md) — 微控制器如何集成到 Klipper 系统
