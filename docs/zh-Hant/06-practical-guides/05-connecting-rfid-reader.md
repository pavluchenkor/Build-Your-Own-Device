# 連接RFID讀卡器

RFID/NFC讀卡器讓你可以不用有線接觸就能讀取卡、標籤或鑰匙扣。

在類似iDryer的設備中，這對於線軸標識、材料配置選擇、服務訪問或消耗品追蹤實驗很有用。

主要錯誤：購買“RFID 模組”並假設任何卡片都可以在任何控制器上從任何距離讀取。實際上，您需要驗證頻率、標籤類型、介面、功率、邏輯電平和天線放置。

## Popular modules

常見的包括：

- RC522 / MFRC522;
- PN532;
- ready-made USB/UART RFID readers;
- 具有 I2C、SPI 或 UART 的 NFC 模組。

對於簡單的 3D 列印機項目，13.56 MHz 模組和標籤最常見：卡片、金鑰卡、NTAG/MIFARE 相容標籤。

## 連接前要檢查什麼

連接之前，找到：

- module frequency;
- 支援的卡片和標籤類型；
- interface: SPI, I2C, or UART;
- supply voltage;
- logic levels;
- board pinout;
- interface selection via jumpers or solder bridges;
- 讀取距離；
- 天線和放置要求。

如果模組的額定值為 `5V`，則無法在不檢查的情況下將其直接連接到 `5V` 邏輯。有些板有電壓調節器，但缺乏訊號線上的電平轉換。

## RC522：典型的 SPI 連接

廉價的 RC522 模組通常在 `3.3V` 上運行，最常見的是透過 SPI 連接。

典型線路：

- `VCC` - `3.3V` power;
- `GND` - ground;
- `SCK` - SPI clock signal;
- `MOSI`－從控制器到模組的資料；
- `MISO`－模組到控制器的資料；
- `SDA`, `SS`, or `CS` - SPI chip select;
- `RST` - reset;
- `IRQ` - 中斷，在簡單專案中經常使用。

![RFID RC522 (MFRC522) module for reading 13.56 MHz cards](../../img/06-practical-guides/05-rfid-rc522-module.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:RFID-RC522_photo.jpg), Giacomo Alessandroni, CC BY-SA 4.0*

引腳名稱可能不同。例如，在 RC522 上，接腳 `SS` 通常表示 SPI 的 `CS`/`SDA`，而不是 I2C `SDA` 線。這是造成混亂的常見原因。

## PN532: SPI, I2C, or UART

PN532是一個更靈活的模組。根據主機板的不同，它可以透過以下方式工作：

- SPI;
- I2C;
- UART.

但你不能只連接任何引腳。在許多 PN532 板上，介面是透過跳線、DIP 開關或焊接橋來選擇的。

連接前，請檢查：

- 在板上物理選擇哪個介面；
- 哪些引腳與所選介面相符；
- I2C是否需要上拉電阻；
- 是否需要上拉或重設引腳；
- 邏輯電平是否與控制器相容。

如果板上顯示“3.3V 邏輯”，請勿將其直接連接到 5V GPIO。

## 共同點

與其他模組一樣，需要共同點。

如果 RFID 模組由一個電源供電而控制器由另一個電源供電，則必須連接它們的 `GND`。

如果沒有共地，SPI/I2C/UART可能無法工作或工作不穩定。

## 標籤必須與閱讀器匹配

RFID/NFC 不是單一的通用標準。

模組在物理上只能讀取其晶片和庫支援的標籤。

檢查：

- tag frequency;
- card or fob type;
- 模組是否支援 MIFARE、NTAG、ISO14443A 或所需的類型；
- 只需要讀取UID還是同時讀取/寫入資料？
- 所選庫是否支援所需的操作。

對於簡單的材料設定檔選擇，通常只讀取標籤 UID 並將 UID -> 材質映射儲存在韌體或主機中就足夠了。

## 讀取距離

小型 RFID/NFC 模組的讀取距離通常很短。

Results depend on:

- antenna size;
- tag type;
- tag orientation;
- distance;
- housing plastic;
- nearby metal;
- interference;
- module power.

天線附近的金屬會嚴重影響讀數。如果讀取器安裝在乾燥器、腔室或線軸支架中，請在實際組裝中測試距離，而不僅僅是在工作台上。

## 閱讀器放置在哪裡

對於細絲線軸，最好將 RFID/NFC 讀取器放置在使用者有意攜帶標籤的位置。

不要假設標籤總是自動讀取來設計邏輯。

Practical options:

- 外殼上的「將標籤帶到這裡」區域；
- 靠近線軸支架的位置；
- 門禁卡服務區；
- 獨立面板，讀取距離短。

如果標籤位於線軸上，請使用不同的線軸、不同的標籤方向、不同的塑膠和金屬接近度進行測試。

## 首次啟動

整合前：

1. 連接工作台上的模組。
2. 從庫中為您的模組運行一個範例。
3. 驗證卡片或標籤的讀取是否穩定。
4. 記錄多個標籤的UID。
5. 檢查不支援的卡片是否不會破壞邏輯。
6. 將模組安裝到外殼中並重新測試。

在這個階段，不要立即建立複雜的設定檔系統。首先，實現穩定的UID讀取。

## 範例設備邏輯

對於材料剖面，簡單的邏輯可以是：

1. User brings tag.
2. 設備讀取 UID。
3. UID 在表中尋找。
4. 如果 UID 已知，則選擇材料設定檔。
5. 如果 UID 未知，設備會要求手動選擇設定檔。

RFID不應該是唯一的控制方法。您需要手動備份：選單、按鈕、螢幕或介面設定中的設定檔。

## 組裝後要檢查什麼

Verify:

- module receives correct voltage;
- 邏輯電平與控制器相容；
- 選擇正確的介面；
- `MISO`、`SCK`、`CS`、`CS` 不交換為 SPI；
- `SCL`、`SCL` 不交換為 I2C；
- 對於 UART，`RX` 和 `RX` 正確交叉；
- common ground exists;
- 根據庫的要求連接重設/IRQ；
- 讀取正確類型的標籤；
- 外殼內讀取距離正常；
- 金屬和電線不要遮擋天線；
- 如果沒有讀取標籤，設備可以正常運作。

## 常見錯誤

- 將3.3V RC522連接到5V電源或5V邏輯；
- 將 RC522 `SDA` 與 I2C `SDA` 混淆；
- 忘記 SPI 上的 `SS`/`SS`；
- 交換 `MISO` 和 `MISO`；
- 用跳線選擇PN532上的一個接口，但連接另一個接口；
- 使用不支援的卡類型；
- 將天線放置在金屬旁邊；
- 在工作台上測試讀取距離，但不在外殼內測試；
- 使 RFID 成為唯一的設定檔選擇方法；
- 僅將重要邏輯儲存在 UID 中，而不進行讀取錯誤檢查。

## 要點

- 必須針對特定標籤和介面選擇 RFID/NFC 模組。
- RC522通常需要`3.3V`和SPI。
- PN532 可以透過 SPI、I2C 或 UART 運作，但必須在板上選擇介面。
- 需要共同基礎。
- Metal near antenna can greatly worsen reading.
- 對於材料配置文件，標籤 UID 通常就足夠了，但需要手動備份選擇。
- 在實際住房中進行測試，而不僅僅是在工作台上進行測試。

## 相關閱讀

- [Adafruit: PN532 RFID/NFC Breakout Wiring](https://learn.adafruit.com/adafruit-pn532-rfid-nfc/breakout-wiring) - PN532 connection, SPI/I2C/UART selection, and 3.3V logic warnings.
- [Adafruit: PN532 RFID/NFC guide, single page](https://learn.adafruit.com/adafruit-pn532-rfid-nfc?view=all) - full PN532 guide, wiring, CircuitPython, Raspberry Pi, and interface selection.
- [Adafruit PN532 product page](https://www.adafruit.com/product/364) - PN532 capabilities, NFC/RFID tag support, and 3.3V UART/I2C/SPI interfaces.
- [NXP: MFRC522 Standard performance MIFARE and NTAG frontend](https://www.nxp.com/products/rfid-nfc/nfc-hf/nfc-readers/standard-performance-mifare-and-ntag-frontend:MFRC52202HN1) - official MFRC522/RC522 page for 13.56 MHz MIFARE/NTAG scenarios.
- [DigiKey: MFRC522 Datasheet by NXP](https://www.digikey.com/htmldatasheets/production/993456/0/0/1/mfrc522.html) - MFRC522 technical datasheet: supported cards, power, communication interfaces with controller, and antenna/power effects on distance.
