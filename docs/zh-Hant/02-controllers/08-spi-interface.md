# SPI 介面

SPI 是控制器和周邊設備之間的快速串列通訊介面。展開：`Serial Peripheral Interface`（序列周邊介面）。

SPI 常用於需要比 I2C 更快速的資料傳輸，或設備本身就是為 SPI 設計的場景：顯示器、記憶卡、RFID 模組、感應器、驅動器或記憶體晶片。

## SPI 的應用場景

在 3D 印表機和 iDryer 類設備中，SPI 可能出現在：

- RFID/NFC 模組，例如 RC522；
- OLED/TFT 顯示器；
- 記憶卡；
- 用於輸入整形的加速度感應器；
- 步進馬達驅動器，例如 TMC2130/TMC5160；
- 記憶體晶片；
- ADC/DAC 和擴展板；
- 某些感應器和專用模組。

SPI 通常比 I2C 更快，但需要更多線路和更仔細的腳位選擇。

## 基本信號線

典型的 SPI 使用：

- `SCK` 或 `CLK` - 時鐘信號；
- `MOSI` - 控制器到設備的資料；
- `MISO` - 設備到控制器的資料；
- `CS`、`SS` 或 `NSS` - 選擇特定設備；
- `GND` - 共同接地；
- 模組電源。

包含兩個設備的圖示：

![SPI: 主設備和從設備之間的基本交換操作](../../img/02-controllers/08-spi-basic-operation.png)

*來源：[Wikimedia Commons](https://commons.wikimedia.org/wiki/File:SPI_basic_operation,_single_Main_%26_Sub.svg), Em3rgent0rdr, CC0 Public Domain*

`SCK`、`MOSI` 和 `MISO` 可由多個設備共用。但每個設備通常需要自己的 `CS`。

## CS 代替位址

在 I2C 中，設備由位址區分。在 SPI 中，通常沒有位址。控制器透過單獨的 `CS` 線選擇設備。

範例：

```text
SCK  -> 所有 SPI 設備共用
MOSI -> 共用
MISO -> 共用
CS1  -> RFID 模組
CS2  -> 顯示器
CS3  -> 記憶卡
```

當控制器想與 RFID 模組通訊時，它啟動 `CS1`。當它想與顯示器通訊時，它啟動 `CS2`。

最常見的情況是，`CS` 是低電位活躍的：閒置時線路為 `HIGH`，選擇設備時為 `LOW`。但這需要在技術資料表中驗證。

## MOSI/MISO 和新名稱

在舊的和非常常見的配置中，名稱是：

- `MOSI` - Master Out Slave In（主設備出，從設備入）；
- `MISO` - Master In Slave Out（主設備入，從設備出）；
- `SS` - Slave Select（從設備選擇）。

在較新的文件中，你可能會看到中立的名稱：

- `PICO` - Peripheral In Controller Out（周邊入，控制器出，相當於 MOSI）；
- `POCI` - Peripheral Out Controller In（周邊出，控制器入，相當於 MISO）；
- `CS` - Chip Select（晶片選擇）。

在 3D 印表機電子設備中，`MOSI`、`MISO`、`SCK`、`CS` 仍然很常見。關鍵是要理解信號方向，並檢查特定模組的腳位圖。

## MISO 可能不需要

並非每個 SPI 設備都實際傳回資料。

例如，簡單的顯示器可能只接收命令和像素。那麼 `MISO` 線可能缺失或未使用。

但對於需要讀取資料的設備，`MISO` 是必需的：

- RFID 模組；
- 記憶卡；
- 感應器；
- 具有診斷功能的驅動器；
- 記憶體晶片。

如果模組應該回應，但 `MISO` 未連接或接錯了，初始化可能會失敗。

## SPI 速度和模式

SPI 有速度。它可以遠高於 I2C，但這不意味著你需要立即設定最高速度。

工作受到以下因素的影響：

- 線路長度；
- 接地品質；
- 模組及其資料表；
- 噪聲等級；
- 控制器頻率；
- 選擇的 SPI 模式。

SPI 模式由時鐘極性和時鐘相位參數設定：`CPOL` 和 `CPHA`。通常使用模式 0，但並非總是如此。如果模式不正確，設備可能無法回應或返回不正確的資料。

在大多數現成的程式庫中，模式已經設定好了。但如果你連接的是不尋常的模組或編寫低層配置，你需要檢查資料表。

## 3.3V 和 5V

與其他介面一樣，SPI 不能保證安全的電壓等級。

ESP32、RP2040、STM32 和許多現代模組使用 `3.3V` 邏輯。Arduino Uno/Nano 通常使用 `5V`。

連接前，驗證：

- 模組電源；
- `SCK`、`MOSI`、`MISO`、`CS` 的邏輯等級；
- 是否有電壓匹配；
- 模組是否容許信號輸入上的 `5V`；
- 控制器輸入是否容許 `5V`。

例如，RC522 通常需要 `3.3V` 電源和邏輯。在沒有電壓匹配的情況下將其連接到 `5V` Arduino 是個壞主意。

## Klipper 中的 SPI

在 Klipper 中，SPI 用於各種設備：TMC 驅動器、加速度感應器、某些顯示器和感應器。

配置可能包括：

- `cs_pin` - 設備選擇腳位；
- `spi_bus` - 硬體 SPI 匯流排；
- `spi_speed` - 速度（Hz）；
- `spi_software_sclk_pin`；
- `spi_software_mosi_pin`；
- `spi_software_miso_pin`。

如果設備連接到額外的 MCU，腳位應屬於該 MCU。與其他 Klipper 部分一樣，特定主板的腳位圖比猜測更重要。

粗略想法：

```ini
[some_spi_device]
cs_pin: chamber:gpio9
spi_software_sclk_pin: chamber:gpio10
spi_software_mosi_pin: chamber:gpio11
spi_software_miso_pin: chamber:gpio12
```

這不是特定設備的現成配置，而是說明：所有 SPI 腳位必須在實際連接模組的 MCU 上。

## 線路長度和干擾

SPI 可以很快運行，但不喜歡長的、雜亂的線路。

實務規則：

- 保持 `SCK`、`MOSI`、`MISO`、`CS` 簡短；
- 靠近 `GND` 佈線；
- 不要與加熱器和馬達線路平行佈線；
- 如果出現錯誤，減少 `spi_speed`；
- 使用適當的連接器；
- 不要無故將 SPI 拉過整個印表機；
- 對於遠端節點，更常選擇 CAN、UART/RS-485 或靠近模組的獨立 MCU。

`SCK` 線特別敏感：它是時鐘信號。如果它很髒，所有通訊都可能變得不穩定。

## SPI 和 RC522

RC522 是一個命名混淆的 SPI 模組的好例子。

在許多 RC522 主板上，`SDA` 腳實際上用作 SPI 的 `SS`/`CS`。這不是 I2C `SDA`。

對於 RC522，你通常需要：

- `3.3V`；
- `GND`；
- `SCK`；
- `MOSI`；
- `MISO`；
- `SDA`/`SS`/`CS`；
- `RST`；
- 有時 `IRQ`，但在簡單的專案中通常不使用。

詳細的圖示在實務文章中：[連接 RFID 讀卡機](../06-practical-guides/05-connecting-rfid-reader.md)。

## 連接前要檢查的事項

在連接 SPI 模組之前，驗證：

- 模組電源；
- 邏輯等級；
- 特定主板的腳位圖；
- `SCK`、`MOSI`、`MISO`、`CS` 在哪裡；
- 是否需要 `RST`、`DC`、`IRQ` 或其他腳位；
- 哪個 `CS` 被指派給該設備；
- 如果 `CS` 與另一個模組衝突；
- 是否需要硬體 SPI 或軟體 SPI；
- 文件建議什麼速度；
- 韌體是否支援此模組。

## 常見錯誤

- 混淆 `MOSI` 和 `MISO`；
- 忘記 `CS`；
- 將兩個設備連接到一個 `CS`；
- 未連接共同的 `GND`；
- 對 `3.3V` SPI 模組施加 `5V`；
- 將 RC522 上的 `SDA` 誤認為 I2C `SDA`；
- 選擇了過高的速度；
- 製作了過長的線路；
- 將模組連接到一個 MCU，但指定了另一個的腳位；
- 認為 SPI 是驅動負載的電源介面。

## 要點

SPI 是控制器附近模組的快速介面。通常你需要 `SCK`、`MOSI`、`MISO`、`CS`、電源和 `GND`。

與 I2C 的主要區別：SPI 通常沒有位址，每個設備都由單獨的 `CS` 選擇。連接前，驗證腳位圖、邏輯等級、速度、線路長度和韌體支援。

## 相關資料

- [SparkFun: Serial Peripheral Interface](https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi) - SPI 的實務解說、資料線、新的 PICO/POCI 名稱和基本交換邏輯。
- [SparkFun: SPI Chip Select](https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi/chip-select-cs) - 為什麼需要 `CS` 以及如何連接多個 SPI 設備。
- [Adafruit: SPI Devices](https://learn.adafruit.com/circuitpython-basics-i2c-and-spi/spi-devices) - SPI 與 I2C 的比較、單獨的 `CS`、速度、極性/相位和限制。
- [DigiKey: SPI Simplifies Device Communication](https://www.digikey.com/en/articles/why-how-to-use-serial-peripheral-interface-simplify-connections-between-multiple-devices) - 連接多個 SPI 設備的選項和 `CS` 的角色。
- [Klipper Configuration Reference: Common SPI settings](https://www.klipper3d.org/Config_Reference.html) - Klipper 中的 `spi_speed`、`spi_bus`、軟體 SPI 和 `cs_pin` 參數。
