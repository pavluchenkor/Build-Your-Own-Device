# USB-UART 轉接器

USB-UART 轉接器讓電腦或 Linux 主機能透過 USB 與 UART 裝置通訊。它將 USB 轉換為標準序列訊號線 `TX`、`RX` 與 `GND`。

這類轉接器常用於燒錄、查看日誌、診斷，以及修復沒有標準 USB 接口的開發板。

## 使用場景

USB-UART 轉接器適用於以下情況：

- 燒錄某些微控制器開發板；
- 讀取序列日誌；
- 存取裝置控制台；
- 燒錄器模式診斷；
- 連接 Arduino Pro Mini 及部分 Nano 相容板；
- 使用沒有內建 USB 的開發板；
- 燒錄失敗後的救援；
- 透過序列埠將 MCU 暫時連接至主機。

如果開發板本身已有標準 USB 並可被識別為序列裝置，則不需要額外的 USB-UART 轉接器。

## 接腳說明

常見接腳：

- `TX` 或 `TXO` — 從轉接器傳送資料至裝置；
- `RX` 或 `RXI` — 從裝置接收資料；
- `GND` — 共地；
- `VCC`、`3V3` 或 `5V` — 電源，視需求而定；
- `DTR` — 常用於自動重置／燒錄；
- `RTS`、`CTS` — 流量控制線，或用於開機／重置場景。

接線圖：

![基於 CH340T 晶片的 USB-UART 轉接器](../../../img/02-controllers/10-usb-uart-ch340-adapter.jpg)

*來源：[Wikimedia Commons](https://commons.wikimedia.org/wiki/File:15938_-_USBtoSerial_1.jpg)，SparkFun Electronics，CC BY 2.0*

若僅需讀取日誌，通常只需連接 `TX`、`RX` 與 `GND`。只有在確認開發板應由轉接器供電時，才連接電源腳位。

## TX 與 RX 的連接方式

連接時需交叉對接：

```text
TX adapter -> RX device
RX adapter <- TX device
GND adapter -> GND device
```

若無法連線，首先檢查：`TX` 與 `RX` 是否接反、是否有共地、通訊速率是否一致，以及是否選擇了正確的 COM/tty 連接埠。

## 3.3V 與 5V

USB-UART 轉接器有以下幾種類型：

- 僅支援 `3.3V`；
- 僅支援 `5V`；
- 附有 `3.3V/5V` 切換開關；
- 以跳線或焊接跳線選擇電壓；
- `VCC` 為某一電壓，但訊號線為另一電壓準位。

這點很重要：`VCC` 電壓準位與 `TX/RX` 訊號準位未必能從標示直接判斷。

ESP32、RP2040 與 STM32 通常使用 `3.3V` 邏輯。Arduino Uno/Nano 通常使用 `5V` 邏輯。若將 `5V` 訊號施加於 `3.3V` 輸入，可能損壞開發板。

連接前請查閱轉接器與開發板的說明文件，不要僅憑跳線顏色或外殼標示判斷。

## TTL UART 與 RS-232

微控制器用的 USB-UART 轉接器通常輸出 TTL/CMOS UART 訊號：`3.3V` 或 `5V`。

這與真正的 RS-232 不同。

RS-232 電壓準位不同，無法直接連接微控制器的 GPIO。若需要與真實的 RS-232 連接埠通訊，需使用 USB-RS232 轉接器或準位轉換器，而非普通的 USB-UART TTL 轉接器。

## 轉接器供電

轉接器上的 `VCC` 腳位有其用途，但常被誤用。

安全做法：

- 查看日誌或診斷時，先只連接 `TX`、`RX`、`GND`；
- 若開發板已透過 USB、電源供應器或其他電路供電，請勿連接 `VCC`；
- 不要透過 USB-UART 轉接器為馬達、伺服機、繼電器、加熱器及 LED 燈帶供電；
- 確認轉接器實際能提供的最大電流；
- 注意 `VCC` 可能是 `3.3V` 或 `5V`。

若在未充分了解電路的情況下同時連接兩組電源，可能導致反向供電、不穩定或損壞開發板。

## DTR 與 RTS

部分開發板使用 `DTR` 與 `RTS` 進行自動重置或進入燒錄器模式。

範例：

- Arduino Pro Mini 通常透過電容使用 `DTR` 進行燒錄時的重置；
- ESP32 開發板可能使用 `DTR`/`RTS` 自動控制 `EN` 與 `BOOT`；
- 若這些訊號線未連接，某些燒錄器場景需要手動按下按鈕。

若燒錄無法自動啟動，原因不一定是 `TX/RX` 問題，也可能是 `DTR`/`RTS` 未連接、選擇了錯誤的燒錄器，或需要手動按下 `BOOT`/`RESET`。

## CH340、CP2102、FTDI

常見的 USB-UART 晶片：

- **CH340/CH341** — 廉價且普及的轉接器；
- **CP2102/CP210x** — Silicon Labs 常見的 USB-UART 晶片；
- **FT232/FTDI** — 經典選擇，通常較貴；
- **PL2303** — 常見於舊款轉接器與連接線。

在現代系統上，驅動程式通常會自動安裝，但並非總是如此。若連接埠未出現，請檢查：

- USB 連接線是否為純充電線；
- 系統是否已偵測到裝置；
- 是否需要安裝驅動程式；
- 舊版驅動程式是否有衝突；
- 連接埠是否被其他程式佔用。

## 測試轉接器

簡易回環測試：

1. 將轉接器連接至電腦。
2. 將轉接器的 `TX` 連接至自身的 `RX`。
3. 開啟序列終端機。
4. 選擇連接埠與速率，例如 `115200`。
5. 輸入字元。
6. 若正常運作，輸入的字元會回顯。

此測試可在不連接外部開發板的情況下，驗證轉接器本身、驅動程式、連接線與終端機程式是否正常。

## 購買前的注意事項

購買 USB-UART 轉接器前，請確認：

- `TX/RX` 電壓準位：`3.3V`、`5V` 或可切換；
- 如何選擇電壓準位；
- 使用何種晶片：CH340、CP2102、FTDI 或其他；
- 您的系統是否有對應驅動程式；
- 是否具備 `DTR` 與 `RTS`（若需要自動燒錄）；
- USB 接口類型；
- `GND`、`TX`、`RX`、`VCC` 接腳排列是否方便使用；
- 是否有電路圖或完整說明文件；
- `VCC` 最大可提供電流（若有需求）。

針對 ESP32/RP2040/STM32 診斷，使用標示清晰、支援 `3.3V` 訊號的轉接器更為方便。

## 常見錯誤

- 將 `TX` 接 `TX`、`RX` 接 `RX`；
- 忘記接共地 `GND`；
- 對 `3.3V` 開發板選用 `5V` 電壓準位；
- 在開發板已供電的情況下仍連接 `VCC`；
- 透過 USB-UART 轉接器為負載供電；
- 將 USB-UART TTL 與 USB-RS232 混淆；
- 使用純充電 USB 連接線；
- 未安裝 CH340/CP2102/FTDI 驅動程式；
- 選擇錯誤的 COM/tty 連接埠；
- 需要自動燒錄時未連接 `DTR`/`RTS`；
- 序列終端機仍開著，卻不明白為何燒錄工具無法開啟連接埠。

## 重點摘要

USB-UART 轉接器是電腦 USB 與裝置 UART 腳位之間的橋樑。最基本的連接只需交叉對接的 `TX/RX` 與共地 `GND`。

主要風險：`3.3V/5V` 電壓準位錯誤、不必要的電源連接、將 TTL UART 與 RS-232 混淆，以及燒錄時缺少 `DTR`/`RTS` 訊號線。

## 參考資料

- [SparkFun: Serial Basic CH340C Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide) — USB-UART CH340C 實用指南，涵蓋 `DTR/RX/TX/VCC/CTS/GND` 接腳、電壓選擇與回環測試。
- [SparkFun: Serial Basic Overview](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide/serial-basic-overview) — 接腳說明與轉接器上的 `3.3V/5V` 切換。
- [Adafruit: FT232H Serial UART](https://learn.adafruit.com/adafruit-ft232h-breakout/serial-uart) — USB 序列轉接器範例，包含 `TX`/`RX`、流量控制線及與裝置的連接方式。
- [Silicon Labs: CP2102 USB to UART Bridge](https://www.silabs.com/interface/usb-bridges/classic/device.cp2102) — USB-UART 橋接晶片及虛擬 COM 連接埠驅動程式的官方範例。
- [Klipper Configuration Reference: `[mcu]`](https://www.klipper3d.org/Config_Reference.html#mcu) — Klipper 中透過 `serial` 設定 MCU 序列連接的方式。
