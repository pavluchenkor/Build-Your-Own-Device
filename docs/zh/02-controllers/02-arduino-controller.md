# Arduino 控制器

Arduino 不是一個特定的微控制器，而是板、庫、示例和開發環境的生態系統。當初學者說 "Arduino" 時，他們通常指的是 Arduino Uno、Nano 或基於 ATmega328P 的兼容板。

對於教育，Arduino 仍然非常有用：容易理解 GPIO、按鈕、LED、PWM、模擬輸入、I2C、SPI 和簡單的傳感器。但對於 3D 打印機周圍的新設備，Arduino Uno/Nano 並不總是最佳選擇。

## Arduino 為何受歡迎

Arduino 的優勢：

- 大量的教育資料
- 簡單的 Arduino IDE
- 許多現成的庫
- 易於理解的例子，如 Blink
- 方便快速測試桌子上的傳感器
- 容易找到兼容的模塊
- 舊板文檔充分

如果目標是理解微控制器的基礎，Arduino 很好。它降低了進入門檻，讓您快速看到結果。

## 作為教育板的 Arduino

Arduino 便於：

- 快速測試按鈕、限制開關或傳感器
- 通過電壓分壓器進行簡單的熱敏電阻測試
- 測試 I2C OLED
- 測試 SPI RFID 模塊
- 為小型測試生成 PWM
- 讀取模擬電壓
- 麵包板上的快速實驗

在此模式中，Arduino 是一個優秀的實驗室工具。您不需要在其上構建最終設備：您可以首先理解電路和傳感器，然後將解決方案轉移到 ESP32、RP2040、STM32 或打印機板。

## Uno 和 Nano 簡明扼要

經典 Arduino Uno 和 Nano 通常基於 ATmega328P。

典型特性：

- `5V` 邏輯
- 16 MHz 時鐘
- 32 KB 閃存
- 2 KB SRAM
- 14 個數字引腳
- Uno/Nano 等級上的 6 個 PWM 引腳
- Uno 上 6 個類比輸入，Nano 上 8 個
- 用於刷新和為板供電的 USB

這對於教育草圖和簡單的獨立任務是足夠的，但對於複雜的邏輯、網絡、Web 介面、大型庫和現代系統的方便集成是不夠的。

## 原始、克隆和 Arduino 兼容

您需要區分：

- 原始 Arduino 板
- 廉價 Uno/Nano 克隆
- 基於其他微控制器的 Arduino 相容板
- 具有 Wi-Fi、USB-C、Arm 芯片和其他邏輯的現代 Arduino 板

幾美元的 Nano 克隆可以適合實驗，但 USB-UART、調節器、焊接和引導載入器的品質可能會有所不同。有時對於 Arduino IDE 中的 Nano 克隆，您需要選擇舊的引導載入器或不同的處理器。

如果設備必須長時間無人監管，板質量、調節器、連接器和文檔比最低價格更重要。

## 5V 邏輯

舊的 Arduino Uno/Nano 使用 `5V` 邏輯。

這對於某些舊模塊很方便，但對於 `3.3V` 設備很危險：

- ESP32 通常不能容忍 GPIO 上的 `5V`
- 許多 OLED、RFID、傳感器和無線電模塊設計用於 `3.3V`
- I2C 上拉至 `5V` 可能會損壞 `3.3V` 設備
- 某些模塊輸入與 `5V` 相容，但這需要在文檔中檢查

如果 Arduino 連接到 `3.3V` 模塊，您需要電平轉換器或已知兼容級別的電路。

## GPIO 不向負載供電

Arduino 引腳可以通過電阻點亮 LED 或提供控制信號。它不應直接為風扇、加熱器、伺服、繼電器或 LED 燈條供電。

典型電路：

![帶 ATmega328P 微控制器的 Arduino Uno Rev3](../../../img/02-controllers/02-arduino-uno-rev3.jpg)

*來源：[Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Arduino_Uno_Rev3_with_Atmega328P.jpg)、HonCode、CC0 Public Domain*

對於負載，您需要：

- 直流風扇、LED 條帶或直流加熱器的 MOSFET 或驅動器
- 繼電器線圈的晶體管驅動器和保護二極體
- 用於 AC 網絡負載的 SSR 或繼電器
- 伺服的獨立電源
- 低壓電路在需要時的公共 GND

GPIO 是一個命令，而不是電源輸出。

## PWM 和 analogWrite

在 Arduino 中，Uno/Nano 上的 `analogWrite()` 通常意味著 PWM，而不是真實的類比輸出。電路板快速切換引腳、開啟和關閉，改變信號占空比。

這適合於：

- LED 亮度
- 驅動器輸入的控制
- 風扇或 MOSFET 模塊的簡單 PWM
- 教育實驗

但有限制：

- PWM 不適用於所有引腳
- PWM 頻率是固定的或以非顯而易見的方式改變
- `analogWrite()` 和 `analogRead()` 是不同的東西
- 4 引腳 PC 風扇可能需要不同的頻率和適當的開集/開漏方法
- 加熱器和 SSR 不能在不了解電源部分的情況下使用任何快速 PWM

## 類比輸入

Arduino Uno/Nano 便於簡單的類比測量：

- 電位計
- 通過電壓分壓器的熱敏電阻
- 光傳感器
- 通過電壓分壓器的簡單電壓傳感器

但類比輸入不應看到超過其安全範圍的電壓。對於 Uno/Nano，這通常是相對於 `5V` 電源或所選 `AREF` 的範圍。如果測量更高的電壓，您需要分壓器和保護。

對於精確的溫度測量，您不僅需要 `analogRead()`，還需要：

- 正確的電壓分壓器電路
- 電阻值
- 熱敏電阻表或 Beta 參數
- 穩定的電源/參考電壓
- 雜訊濾波
- 與物體的機械傳感器接觸

## Arduino 和 Klipper

一些舊的 AVR 板在歷史上可能會在 3D 打印機附近找到，但對於 Klipper 周圍的新設備，最好不要從 Uno/Nano 開始。

原因：

- 記憶有限
- 性能較弱
- 5V 邏輯可能會干擾現代 `3.3V` 模塊
- 沒有附加模塊的網絡
- 不是新 Klipper MCU 的最實用路徑

如果您需要 Klipper 的其他 MCU，通常更實用的是查看 RP2040、STM32 或現成的 3D 打印機板。Arduino 可以保留用於教育、麵包板和單個傳感器測試。

## Arduino 何時仍然合適

Arduino 適合於：

- 您需要快速測試一個想法
- 您需要解釋某些事情如何運作
- 設備非常簡單，不需要網絡
- 您已經有一個有效的草圖
- 清晰度比緊湊性和性能更重要
- 這是一個教育板，而不是最終的電力電子學

Arduino 如果不是好的選擇：

- 您需要開箱即用的 Wi-Fi
- 您需要與 Klipper 的緊密集成
- 您需要大量記憶
- 您需要許多現代 `3.3V` 傳感器
- 設備必須小巧、長壽且在工業上整潔
- 有一個電源部分，其中獨立保護很重要

## 購買前檢查

購買 Arduino 相容板之前，檢查：

- 它是原始的、克隆的還是相容的板
- 安裝了哪個微控制器
- `5V` 或 `3.3V` 邏輯
- 使用哪個 USB-UART 芯片
- 您的計算機是否有驅動程序
- 需要哪個引導載入器
- 多少閃存和 SRAM
- 多少個 PWM 和類比輸入
- 是否有原理圖和引腳圖
- 電源調節器和連接器的質量
- 板是否適合最終任務

## 常見錯誤

- 認為 Arduino 是一個特定的板
- 將 `5V` Arduino 直接連接到 `3.3V` 模塊
- 從 GPIO 為負載供電
- 從 `5V` 引腳為伺服供電並獲得重置
- 將 `analogWrite()` 用作真實類比輸出
- 為 Nano 克隆選擇錯誤的引導載入器
- 未安裝 USB-UART 的驅動程序
- 嘗試在沒有理由的情況下在 Uno 上構建現代網絡設備
- 將教育麵包板轉移到沒有修改電源、配線和保護的封閉電力設備

## 關鍵要點

Arduino 是一個很好的教育生態系統，是快速測試的便利工具。它非常適合理解 GPIO、PWM、ADC 和傳感器。

但經典 Uno/Nano 是老 `5V` 板，記憶有限，沒有網絡。對於 3D 打印機周圍的新設備，ESP32、RP2040、STM32 或現成的打印機板通常更實用，讓 Arduino 成為教育和診斷工具。

## 相關資料

- [Arduino Docs: UNO R3](https://docs.arduino.cc/hardware/uno-rev3) — 官方 Uno R3 規格：ATmega328P、`5V`、引腳、PWM、類比輸入和電路板資源
- [Arduino Store: UNO Rev3 Tech Specs](https://store.arduino.cc/collections/arduino/products/arduino-uno-rev3) — 包含電壓、GPIO 電流、記憶、頻率和電路板尺寸的表格
- [Arduino Store: Arduino Nano](https://store-usa.arduino.cc/products/arduino-nano) — Nano 規格、電源、記憶、數字和類比引腳
- [Arduino Help Center: Select the right processor for Arduino Nano](https://support.arduino.cc/hc/en-us/articles/4401874304274-Select-the-right-processor-for-Arduino-Nano) — 為什麼 Nano 和 Nano 克隆可能有不同的引導載入器
- [Arduino Language Reference](https://docs.arduino.cc/language-reference/) — `pinMode`、`digitalWrite`、`analogRead`、`analogWrite`、PWM 和基本功能的官方參考
- [Arduino Help Center: Use PWM output with Arduino](https://support.arduino.cc/hc/en-us/articles/9350537961500-Use-PWM-output-with-Arduino) — 常見板的 PWM 引腳列表和 `analogWrite()` 的限制
