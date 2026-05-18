# 燒錄控制器

韌體（`firmware`）是寫入微控制器快閃記憶體的程式。沒有韌體，主板不知道如何使用腳位、感應器、風扇和介面。

重要：不要混淆韌體和配置。韌體寫入控制器。Klipper 配置通常在主機上的 `printer.cfg` 中，並告訴已燒錄的 MCU 使用哪些腳位和參數。

## 韌體、啟動載入程式、配置

三個不同的概念：

- **韌體** - 微控制器的主程式；
- **啟動載入程式** - 幫助寫入主韌體的小程式；
- **配置** - 設備設定，例如 Klipper 中的 `printer.cfg`。

啟動載入程式首先運行，可以透過 USB、UART、DFU、SD 卡、CAN 或其他機制接受新韌體。如果啟動載入程式意外被刪除，燒錄主板可能會變得困難：有時需要 ST-LINK/SWD、USB-UART 或其他程式設計器。

## 一般路線

在燒錄之前，正常的程序是：

1. 學習確切的主板型號。
2. 學習確切的微控制器。
3. 找到腳位圖、原理圖和製造商說明。
4. 了解是否需要獨立韌體或 Klipper MCU 韌體。
5. 找到適合此主板的現成配置或示例。
6. 選擇正確的燒錄方法。
7. 建構或下載正確的檔案。
8. 將主板放入燒錄模式。
9. 寫入韌體。
10. 驗證主板是否出現在系統中。
11. 驗證與主機的通訊和基本腳位，不帶負載。

你無法猜測韌體設定。對於 Klipper，微控制器型別、啟動載入程式偏移、時鐘參考和通訊介面特別重要。

## 典型的燒錄方法

不同的主板燒錄方式不同：

![控制器的主要燒錄路徑](../../../img/02-controllers/11-controller-flashing-paths.svg)

常見的變體：

- **USB 大量儲存 / UF2** - 主板顯示為磁碟，`.uf2` 被複製到它；
- **USB DFU** - 主板進入 DFU 模式，韌體透過 USB 寫入；
- **USB 序列 / UART 啟動載入程式** - 透過序列埠的韌體；
- **ST-LINK / SWD** - 程式設計器連接到 SWD 腳位；
- **SD 卡** - 某些 3D 印表機主板用卡上的檔案燒錄；
- **CAN/Katapult/CanBoot** - 透過 CAN 啟動載入程式的韌體；
- **Arduino 啟動載入程式** - 透過 Arduino IDE 或 avrdude 的素描草圖燒錄。

所有主板都沒有一種通用的方法。該方法由特定的主板、啟動載入程式和韌體決定。

## RP2040 和 UF2

對於 Raspberry Pi Pico 和許多 RP2040 主板，最簡單的方式是 `BOOTSEL` 和 UF2。

通常：

1. 按住 `BOOTSEL`。
2. 連接 USB。
3. 主板顯示為 `RPI-RP2` 磁碟。
4. 複製 `.uf2` 檔案。
5. 磁碟消失，主板重新啟動。

Pico 的 BOOTSEL 在微控制器 ROM 中，因此無法被正常燒錄意外刪除。這使得 RP2040 對初學者很方便。

## STM32：DFU、ST-LINK、SD 卡

STM32 主板以不同的方式燒錄。

可能的選項：

- 內建的 USB DFU 啟動載入程式；
- UART 啟動載入程式；
- ST-LINK/SWD；
- 印表機主板上的 SD 卡；
- 主板製造商啟動載入程式；
- CAN 啟動載入程式。

對於 STM32，啟動載入程式偏移通常很重要。例如，如果啟動載入程式佔用前 `8 KiB`，Klipper 必須以正確的偏移量建構。如果選擇錯誤，主板在燒錄後可能無法啟動。

ST-LINK/SWD 是一個更低層次的有用選項：如果正常啟動載入程式不起作用，它通常可以恢復主板。但這需要 SWD 腳位、程式設計器和連接方式的理解。

## Klipper：make menuconfig

對於 Klipper 韌體，你通常執行：

```bash
cd ~/klipper
make menuconfig
make
```

在 `make menuconfig` 中，你選擇：

- 微控制器架構；
- 處理器型號；
- 啟動載入程式偏移；
- 時鐘參考；
- 通訊介面：USB、序列、CAN 等；
- 有時特定主板的額外參數。

正確的值通常寫在主板現成配置檔案頂部的註釋中。如果存在這樣的配置，請先讀其頂部的註釋。

構建後，韌體檔案通常出現在 `~/klipper/out/` 中。接下來，使用適合特定主板的方法寫入。

## 燒錄後驗證

燒錄後，你必須驗證不止「燒錄器寫入成功」。

檢查：

- 設備是否出現在系統中；
- 如果使用 USB/序列，`/dev/serial/by-id/...` 是否存在；
- 如果使用 CAN，`canbus_uuid` 是否可見；
- 路徑是否與 `printer.cfg` 相符；
- Klipper 中是否沒有通訊錯誤；
- 腳位是否與此特定主板的腳位圖相符；
- 基本的輸入/輸出在無電源負載的情況下是否工作；
- 風扇/MOSFET/SSR 是否處於安全的關閉狀態。

對於第一次檢查，請不要將加熱器作為最終負載連接。首先驗證通訊、感應器和邏輯的安全條件。

## 燒錄前要保存的內容

在更改韌體之前，保存以下內容是有用的：

- 當前 `printer.cfg`；
- 舊韌體版本（如果可用）；
- 主板型號和微控制器；
- 找到的序列路徑或 CAN UUID；
- 連接照片；
- 腳位圖；
- `make menuconfig` 設定；
- 製造商說明的連結。

如果出現問題，此資料將幫助快速恢復。

## 可能出錯的地方

常見問題：

- USB 線只用於充電；
- 主板未進入啟動載入程式；
- 選擇了錯誤的微控制器；
- 選擇了錯誤的啟動載入程式偏移；
- 選擇了錯誤的通訊介面；
- 韌體已寫入，但在錯誤的位置查找主板；
- 重新連接後序列路徑已更改；
- SD 卡無法被主板讀取；
- 韌體檔案的命名方式對主板啟動載入程式不正確；
- 未安裝 DFU/USB-UART 驅動程式；
- 主板從兩側供電；
- 燒錄後，配置參考了舊腳位。

不要因為第一個錯誤就改變所有東西。最好一步一步地進行：線纜、啟動載入程式模式、MCU 型號、建構設定、寫入方法、系統設備外觀、配置。

## 燒錄和安全

韌體可以開啟和關閉輸出，但它不能替代硬體安全。

對於加熱器，你需要：

- 正確的電源開關；
- 保險絲；
- 獨立的熱保護；
- 正確的溫度感應器；
- 安全的外殼；
- 檢查韌體錯誤、MCU 掛起或通訊遺失時的行為。

燒錄控制器後，不要連接加熱器，除非驗證腳位選擇正確、開啟邏輯沒有反轉，以及安全限制有效。

## 常見錯誤

- 混淆韌體和 `printer.cfg`；
- 從相似但不同的主板燒錄檔案；
- 不讀 Klipper 配置頂部的現成註釋；
- 選擇錯誤的啟動載入程式偏移；
- 在不了解後果的情況下刪除啟動載入程式；
- 使用只充電的 USB 線；
- 不把主板放入燒錄模式；
- 在 `/dev/serial/by-id` 中查找 CAN 主板；
- 透過 `canbus_uuid` 查找 USB 序列主板；
- 在驗證腳位前連接電源負載；
- 不保存舊配置。

## 要點

韌體是控制器內部的程式，配置是其操作設定。對於每個主板，你必須知道確切的型號、微控制器、啟動載入程式、燒錄方法和建構參數。

對於 RP2040，UF2/BOOTSEL 通常最簡單。對於 STM32，檢查特定的主板：DFU、ST-LINK、SD 卡、UART 或 CAN 啟動載入程式。對於 Klipper，首先找到 `make menuconfig` 的現成配置和註釋。

## 相關資料

- [Klipper: Installation - Building and flashing the micro-controller](https://www.klipper3d.org/Installation.html#building-and-flashing-the-micro-controller) - `make menuconfig`、`make` 和序列路徑驗證的官方路線。
- [Klipper: Bootloaders](https://www.klipper3d.org/Bootloaders.html) - 為什麼主板之間的啟動載入程式不同、為什麼需要啟動載入程式偏移，以及如何燒錄不同的 MCU。
- [Raspberry Pi Documentation: Pico-series microcontrollers](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html) - BOOTSEL、UF2 和 Pico/RP2040/RP2350 的具體資訊。
- [Raspberry Pi Documentation: C/C++ SDK - Your First Binaries](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html#your-first-binaries) - BOOTSEL、USB 大量儲存 `RPI-RP2` 和透過 UF2 的 Pico 燒錄的官方示例。
- [STMicroelectronics: STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) - 官方 STM32 工具，用於透過 ST-LINK/SWD、UART、USB DFU、SPI、I2C 和 CAN 啟動載入程式燒錄。
