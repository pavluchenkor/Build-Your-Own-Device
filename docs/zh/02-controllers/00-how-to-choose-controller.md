# 如何選擇控制器

本節介紹四個控制器系列：ESP32、Arduino、RP2040 和 STM32。它們都可以控制風扇、讀取感測器和切換負載。差別在於每個控制器最適合的用途。

## 快速選擇

| 任務 | 控制器 |
|---|---|
| 獨立乾衣機或 Wi-Fi 感測器 | ESP32 |
| 教育原型、初步實驗 | Arduino |
| Klipper 中的微控制器（額外引腳） | RP2040 |
| 印表機板、Klipper 中的微控制器 | STM32 |

## 如果您使用 Klipper

Klipper 使用「主機 + 微控制器」架構。主機是 Raspberry Pi 或類似的計算機。微控制器是一個單獨的微控制器，實時管理加熱器、風扇和感測器。

對於 Klipper 中的微控制器，請考慮 **RP2040** 或 **STM32**：它們得到良好支持，可以不用 ST-Link 刷寫，並且可以通過 USB 或 CAN 直接工作。

ESP32 作為 Klipper 的微控制器不是最佳選擇——它沒有以與 STM32 或 RP2040 相同的方式獲得原生 Klipper 韌體支持。

## 如果您正在構建獨立設備

如果設備必須獨立工作，ESP32 是一個不錯的選擇：讀取感測器、管理加熱、通過 Wi-Fi 發送數據或在瀏覽器中顯示頁面。

Arduino 適合簡單的原型或教育項目，但其局限性——RAM、Flash、較弱的 ADC 和過時的 USB——使其成為最終設備的糟糕選擇。

## 接下來閱讀什麼

- [ESP32](./01-esp32-controller.md) — Wi-Fi、感測器、Web 介面
- [Arduino](./02-arduino-controller.md) — 入門和實驗
- [RP2040](./03-rp2040-controller.md) — Klipper MCU、簡單韌體
- [STM32](./04-stm32-controllers.md) — 印表機板、CAN、SWD
- [MCU in Klipper](./05-mcu-in-klipper.md) — 微控制器如何集成到 Klipper 系統
