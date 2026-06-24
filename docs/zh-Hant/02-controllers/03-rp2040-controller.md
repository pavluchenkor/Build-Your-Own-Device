# RP2040 控制器

RP2040 是 Raspberry Pi 微控制器。基於它最著名的板是 Raspberry Pi Pico。

對於 3D 打印機周圍的 DIY 外設，RP2040 是最實用的選項之一：便宜、文檔齊全、使用 `3.3V` 邏輯、便於通過 USB 刷新，並且適合作為 Klipper 的附加 MCU。

## RP2040 有用的地方

RP2040 適合於：

- Klipper 的附加 I/O 板
- 通過 MOSFET/驅動器的風扇控制器
- 讀取熱敏電阻和簡單的類比傳感器
- 通過 I2C 連接 OLED
- 通過 SPI 或 UART 連接 RFID/NFC
- 用 PWM 信號控制伺服
- 沒有 Wi-Fi 的簡單獨立板
- 傳感器和介面的測試平台

如果您需要開箱即用的網絡，更容易查看 ESP32 或 Pico W。如果您需要 Klipper 的附加有線 MCU，RP2040 通常更方便。

## Raspberry Pi Pico 為何方便

Raspberry Pi Pico 是基於 RP2040 的現成開發板。它已經有 USB、閃存、電源調節器、`BOOTSEL` 按鈕和公開引腳。

Pico 優勢：

- 低成本
- 體面的文檔和引腳圖
- 用於刷新和通信的 USB
- 許多 GPIO
- `3.3V` 邏輯
- 2 UART、2 SPI、2 I2C
- 16 PWM 通道
- Pico 暴露引腳上的 3 個 ADC 輸入
- 用於非標準介面的 PIO
- 通過 USB 大容量存儲方便的 UF2 刷新

對於第一個項目，最好獲得帶焊接引腳的 Pico 或 Pico H，而不是裸 RP2040 芯片。裸芯片需要自訂板、閃存、電源、USB、佈線和測試。

## BOOTSEL 和 UF2

Pico 的優勢之一是簡單的刷新過程：

1. 按住 `BOOTSEL` 按鈕。
2. 將 USB 連接到您的計算機。
3. 該板顯示為 USB 驅動器。
4. 複製 `.uf2` 固件文件。
5. 該板使用新固件重新啟動。

這對於 MicroPython、CircuitPython、C/C++ 項目和 Klipper 固件很方便。對於初學者，此方法通常比 ST-Link、DFU 或單獨的 USB-UART 更容易理解。

## RP2040 和 Klipper

RP2040 是 Klipper 附加 MCU 的良好候選者。

典型方案：

![帶有 RP2040 芯片的 Raspberry Pi Pico](../../img/02-controllers/03-rp2040-pico-photo.jpg)

*來源：[Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Raspberry_Pi_Pico_oblique.jpg)、Phiarc、CC BY-SA 4.0*

想法是：

- 帶有 Klipper 的 Linux 主機保持為主要控制器
- Pico/RP2040 用 Klipper MCU 固件刷新
- 向 `printer.cfg` 添加主要或附加 `[mcu]` 部分
- RP2040 引腳可用於風扇、傳感器、PWM 和其他外設
- 電力負荷仍通過 MOSFET、驅動器、繼電器或 SSR 連接

當您需要將外設的一部分分離到單獨的塊中時，這很有用：例如風扇、攝像頭傳感器、過濾器、背光、按鈕、限制開關或服務輸出。

## GPIO 和 3.3V 邏輯

RP2040 使用 `3.3V` 邏輯。這意味著：

- 不要向 GPIO 應用 `5V`
- 對於 `5V` 模塊，您可能需要電平轉換器
- I2C 上拉應進入 `3.3V`
- GPIO 不應直接為負載供電
- 風扇、LED 條帶、繼電器或加熱器需要外部開關/驅動器

模塊是否為 "Arduino 相容" 並不意味著它對 RP2040 安全。您需要檢查輸入電平和上拉。

## 電源

Pico 通常從 USB 或通過 `VSYS` 引腳供電。該板有一個用於為微控制器供電的調節器。

實踐規則：

- 不要從 Pico 上的 `3V3` 引腳為馬達、伺服和繼電器供電
- 為負荷使用單獨的電源
- 連接低電壓驅動器的公共 GND
- 檢查 `VSYS` 和 USB 的電源來自何處
- 考慮外部模塊的電流，而不僅僅是 Pico 本身

如果 Pico 在伺服或風扇啟動時重置，問題幾乎總是電源、接地或雜訊。

## Pico 上的 ADC

Pico 有 ADC 輸入，您可以將其用於簡單的類比任務：

- 通過分壓器的熱敏電阻
- 電位計
- 光傳感器
- 通過分壓器測量低電壓

限制：

- ADC 輸入不得超過安全 GPIO 電壓
- 要測量 `12V` 或 `24V`，您需要分壓器和保護
- 熱敏電阻需要正確的電阻、表格/模型和機械接觸
- ADC 不能替代萬用表或工業儀表

對於加熱器，請記住：ADC 僅讀取傳感器。加熱安全由電源開關、固件限制、保險絲和獨立的熱保護提供。

## 簡單術語中的 PIO

PIO 是可編程 I/O。RP2040 有小型可編程塊，無需對主代碼施加持續負荷，就可以生成或讀取非標準信號。

初學者不需要從 PIO 開始。但這是 RP2040 在介面、定時和非標準外設中受歡迎的原因之一。

對於簡單的 iDryer 之類的設備，通常常規 GPIO、PWM、I2C、SPI、UART 和 ADC 就足夠了。

## Pico、Pico W 和 Pico 2

重要的是不要混淆這些板：

- **Pico / Pico H** — 沒有 Wi-Fi 的經典 RP2040 板
- **Pico W / Pico WH** — RP2040 配備板載 Wi-Fi/藍牙模塊
- **Pico 2 / Pico 2 W** — 基於 RP2350 的新一代，這不是 RP2040

如果文章或項目說 RP2040，通常指的是第一代 Pico 或相容板。Pico 2 在概念上相似，但它是不同的微控制器，固件/引腳相容性需要單獨檢查。

## 購買前檢查

購買基於 RP2040 的板之前，請檢查：

- 它是原始 Pico、Pico W 還是克隆
- 引腳是否焊接
- 它是否有您需要的 USB 連接器
- 是否有正確的引腳圖
- 哪些 GPIO 可用
- 您是否需要 Wi-Fi
- 該板是否適合 Klipper 固件
- 電路板和負荷如何供電
- 您是否有足夠的 ADC/PWM/I2C/SPI/UART 來完成任務
- 外殼中是否有安裝空間

如果計劃 Klipper MCU，請提前檢查特定板和刷新方法的現有說明。

## 常見錯誤

- 向 RP2040 GPIO 應用 `5V`
- 從 `3V3` 為伺服或繼電器供電
- 忘記與 MOSFET/驅動器的公共 GND
- 認為 Pico W 是常規 Pico，不考慮使用的資源/Wi-Fi 電源
- 購買 Pico 2 期望精確的 RP2040 行為
- 不使用分壓器在 ADC 上測量 `12V`/`24V`
- 將加熱器直接連接到引腳
- 當常規 Pico 沒有 Wi-Fi 時，為 Wi-Fi 任務選擇 RP2040
- 不檢查特定克隆的引腳圖

## 關鍵要點

RP2040 和 Raspberry Pi Pico 是有線 DIY 外設和 Klipper 附加 MCU 的強大選擇。該板便宜、易於理解、文檔齊全、便於刷新。

但 RP2040 是 `3.3V` 微控制器，而不是電源控制器。負荷通過驅動器、MOSFET、繼電器或 SSR 連接。對於 Wi-Fi 任務，您需要 Pico W 或另一個聯網控制器。

## 相關資料

- [Raspberry Pi: RP2040 specifications](https://www.raspberrypi.com/products/rp2040/specifications/) — 官方 RP2040 規格：CPU、SRAM、UART/SPI/I2C、PWM、USB 和 PIO
- [Raspberry Pi Documentation: Pico-series microcontrollers](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html) — Pico、Pico W、Pico 2、GPIO、ADC、PWM 和板變體的區別
- [RP2040 Datasheet](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf) — 微控制器、外設、PIO、GPIO 和 ADC 的詳細技術描述
- [Raspberry Pi Pico Datasheet](https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf) — Pico 板本身的文檔：電源、USB、暴露的 GPIO 和板限制
- [Raspberry Pi Documentation: C/C++ SDK - Your First Binaries](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html#your-first-binaries) — BOOTSEL、USB 大容量存儲 `RPI-RP2` 和複製 UF2 到 Pico 的官方示例
- [Klipper Configuration Reference](https://www.klipper3d.org/Config_Reference.html) — Klipper 中 RP2040 支持的背景和 I2C 等外設的設置
