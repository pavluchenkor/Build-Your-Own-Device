# ESP32 控制器

ESP32 是 Espressif 微控制器系列，具有 Wi-Fi、藍牙和一整套外設。在 DIY 設備中，當您需要構建獨立模塊時，通常會選擇它：它可以自行連接到網絡、讀取傳感器、在瀏覽器中顯示頁面並控制簡單的輸出。

對於 3D 打印機周圍的設備，ESP32 不是作為"另一個電源板"有用，而是作為小型聯網控制器：溫度/濕度傳感器、通風模塊、具有 Web 界面的簡單過濾器、獨立的攝像頭監控或獨立烘乾機。

## ESP32 有用的地方

典型任務：

- Wi-Fi 溫度和濕度傳感器
- 通過 MOSFET 模塊的獨立風扇控制器
- 用低電壓信號控制繼電器或 SSR
- 通過 I2C 的 OLED 顯示器
- 通過 SPI 或 UART 的 RFID/NFC 讀卡器
- 獨立電源的伺服
- 狀態和設置的簡單網頁
- 與 MQTT、Home Assistant 或您自己的本地邏輯集成
- 不需要是 Klipper 一部分的自主原型

當設備應該獨立於打印機工作並通過網絡交換數據時，ESP32 最為擅長。如果任務只是簡單地向 Klipper 添加引腳，通常最好查看 RP2040、STM32 或現成的打印機板。

## 典型設備架構

ESP32 不直接為負載供電。它輸出控制信號，單獨的模塊進行電源工作。

![帶 GPIO 引腳的 ESP32 開發板](../../img/02-controllers/01-esp32-dev-board.jpg)

*來源：[Wikimedia Commons](https://commons.wikimedia.org/wiki/File:ESP32_Dev_Board.jpg)，Edwiyanto，CC BY-SA 4.0*

實際上，這看起來像：

- ESP32 由開發板上的 USB 或穩定的 `5V` 供電
- ESP32 邏輯本身在 `3.3V` 上運行
- 傳感器連接到 GPIO、I2C、SPI、UART 或 ADC
- 風扇、LED 條帶、DC 加熱器通過 MOSFET 或驅動器連接
- 網絡加熱器僅通過適當的 AC SSR/繼電器和安全電源部分連接
- 伺服由獨立的 `5V/6V` 源供電，ESP32 只提供信號

GPIO 不是負載的電源。引腳可以切換驅動器輸入，但不應直接為風扇、加熱器、繼電器、伺服或 LED 條帶供電。

## 電路板上的 ESP32 意味著什麼

"ESP32" 標籤可以表示不同的東西：

- ESP32 芯片本身
- 帶有芯片、閃存和天線的模塊，例如 ESP32-WROOM
- 帶有 USB、電源調節器、按鈕和公開引腳的開發板
- 較新的變種：ESP32-S3、ESP32-C3、ESP32-C6 等

對於第一個項目，使用開發板比裸模塊更方便。開發板已經有 USB、電源調節器、`BOOT`/`EN` 按鈕和麵包板引腳。

購買前檢查：

- 確切的電路板和芯片名稱
- 是否有 USB-C 或微 USB
- 使用哪個 USB-UART 或內置 USB
- 是否有原理圖和引腳圖
- 實際公開了哪些 GPIO
- 電路板上有什麼電源調節器
- 是否有適當的天線和周圍空間
- 電路板尺寸是否適合您的外殼

## 3.3V 邏輯

ESP32 使用 `3.3V` 邏輯工作。這意味著 GPIO 上的典型 `HIGH` 電平約為 `3.3V`，而不是 `5V`。

重要的是：

- 不要將 `5V` 應用於 ESP32 GPIO
- 對於 `5V` 傳感器和模塊，您可能需要電平轉換器
- 如果總線連接到 ESP32，I2C 上拉應進入 `3.3V`
- 一些現成的 MOSFET/SSR 模塊可能無法從 `3.3V` 可靠工作
- 負載電源不能從 GPIO 獲取

許多傳感器已經以 `3.3V` 變種形式提供。對於 ESP32，這是最佳選擇。

## 電源

開發板通常具有 USB 輸入和 `5V`/`VIN` 引腳，ESP32 本身由 `3.3V` 調節器供電。

常見錯誤：

- 從弱 USB 電纜為 ESP32 供電
- 從電路板上的 `3.3V` 引腳為伺服、風扇或繼電器供電
- 不了解該電流來自何處就連接重負載到 `5V` 引腳
- 未連接 ESP32 和低電壓驅動器之間的公共 GND
- Wi-Fi 啟動時由於電壓下降而重置 ESP32

Wi-Fi 吸取脈動電流。為了穩定運行，良好的電纜、調節器、電路板上的電容和負載的獨立電源很重要。

## GPIO 和特殊引腳

ESP32 有許多 GPIO，但並非每個引腳都同樣方便。

在經典 ESP32 上：

- 某些引腳與芯片負載相關，這些是綁定引腳
- `GPIO6-GPIO11` 通常由閃存佔用，不使用
- `GPIO34-GPIO39` 是僅輸入的
- `GPIO1` 和 `GPIO3` 經常用作固件和日誌的 UART
- 特定開發板上的某些引腳可能由 LED、按鈕或其他電路佔用

綁定引腳在啟動時確定啟動模式。如果外部電路以錯誤的方式拉動這樣的引腳，ESP32 可能無法啟動或可能進入固件更新模式。

實踐規則：對於第一個版本，使用特定板的引腳圖中的引腳，除非您了解其角色，否則避免標記為 `BOOT`、`FLASH`、`STRAP`、`TX0`、`RX0`、`GPIO6-GPIO11` 的引腳。

## ESP32 上的 ADC

ESP32 可以通過 ADC 測量模擬電壓，但這不是實驗室萬用表。

重要的是：

- 在經典 ESP32 上有 ADC1 和 ADC2
- ADC2 與 Wi-Fi 衝突，因此對於 Wi-Fi 設備，最好使用 ADC1 引腳
- 測量範圍取決於衰減設置
- 測量可能需要校準
- 您不能將超過 GPIO 安全電平的電壓應用於 ADC
- NTC 熱敏電阻通常需要電壓分壓器和固件中的正確表格/模型

如果您需要精確的溫度傳感器，通常更簡單的是使用數字傳感器或具有已知庫的現成模塊。對於 NTC 熱敏電阻，ESP32 可以工作，但必須檢查電路和 ADC 設置。

## PWM、I2C、SPI 和 UART

ESP32 便於外設：

- 通過 LEDC 的 PWM 適合風扇、背光和伺服信號
- I2C 適合 OLED 顯示器和許多傳感器
- SPI 適合 RFID 模塊、顯示器和快速設備
- UART 適合 GPS、某些傳感器、其他控制器和調試

ESP32 具有靈活的 GPIO 矩陣：許多信號可以分配給不同的引腳。但這並不意味著任何引腳總是一個好選擇。特定的板限制、閃存、啟動引腳和佔用的 UART 仍然需要考慮。

## ESP32 和 Klipper

ESP32 最好被視為打印機附近的單獨 Wi-Fi/IoT 設備，而不是 Klipper 中其他 MCU 的主要路徑。

Klipper 組織為一個主機加一個或多個 MCU。對於新的其他 MCU，通常更實用的是使用：

- RP2040
- STM32
- 現成的 3D 打印機板

ESP32 可以與打印機系統分開交換數據：通過 MQTT、HTTP API、Home Assistant、您自己的服務器或另一個集成。但這不再與向 Klipper 配置添加 `[mcu]` 並直接使用引腳相同。

## 購買前檢查

購買 ESP32 電路板前，請檢查：

- 確切的模型：ESP32、S3、C3、C6 等
- 邏輯電壓
- 是否有 USB 以及如何刷新電路板
- 是否有官方引腳圖或原理圖
- 哪些引腳對 GPIO 安全
- 哪些引腳是僅輸入的
- 哪些引腳由閃存/PSRAM、USB、UART 或 LED 佔用
- 任務是否有足夠的 ADC/I2C/SPI/UART
- 電路板如何供電
- 它是否適合外殼
- 您的場景是否有庫或固件

如果來自市場的電路板沒有原理圖和正確的引腳圖，它可以用於實驗，但不適合需要長時間無人值守運行的設備。

## 常見錯誤

- 向 ESP32 GPIO 應用 `5V`
- 從 GPIO 為負載供電
- 從弱 `3.3V` 引腳為伺服或繼電器供電
- 忘記與 MOSFET/驅動器的公共 GND
- 為傳感器選擇 ADC2 引腳，然後啟用 Wi-Fi
- 使用啟動綁定引腳使 ESP32 無法啟動
- 使用 `GPIO34-GPIO39` 作為輸出
- 購買沒有引腳圖和原理圖的模塊
- 認為"帶有 Wi-Fi 的 ESP32"自動意味著安全的網絡加熱器控制
- 嘗試用固件替換電力電子學

## 關鍵要點

ESP32 是自主 Wi-Fi 設備的良好選擇：傳感器、Web 界面、簡單的通風控制、過濾器、顯示器和外設。

但 ESP32 使用 `3.3V` 邏輯，具有特殊引腳，不應直接為負載供電。對於電源電路，需要 MOSFET、驅動器、繼電器或 SSR，對於網絡加熱器，需要完整的安全電源部分。

## 相關資料

- [Espressif: ESP32 Wi-Fi & Bluetooth SoC](https://www.espressif.com/en/products/socs/esp32/datasheet) — ESP32 系列、模塊、開發板和文檔鏈接的官方概述
- [Espressif: ESP32 Series Datasheet](https://documentation.espressif.com/esp32_datasheet_en.html) — 芯片特性、外設、ADC、PWM、UART、I2C、SPI 和引腳限制
- [ESP-IDF Programming Guide: GPIO & RTC GPIO](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html) — GPIO 表、綁定引腳、僅輸入引腳、閃存/PSRAM 引腳和 Wi-Fi 的 ADC2 限制
- [Espressif: ESP32 Hardware Design Guidelines](https://docs.espressif.com/projects/esp-hardware-design-guidelines/en/latest/esp32/esp-hardware-design-guidelines-en-master-esp32.pdf) — 電源、綁定引腳、GPIO、ADC 和電路板設計的建議
- [Arduino-ESP32: LED Control API](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/ledc.html) — Arduino-ESP32 中用於風扇、背光和其他 PWM 信號的 PWM/LEDC
- [Klipper: Code overview](https://www.klipper3d.org/Code_Overview.html) — MCU 的 Klipper 架構上下文以及源樹中支持的微控制器後端列表
