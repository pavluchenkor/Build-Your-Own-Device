# STM32 控制器

STM32 是意法半導體公司基於 Arm Cortex-M 核心的 32 位微控制器系列。它不是單個電路板或芯片：在 STM32 名稱下有數十個系列和數百個型號。

在 3D 打印機世界中，STM32 非常普遍。許多現成的打印機電路板、擴展板、CAN 板和控制器都使用 STM32。對於 Klipper 和打印機外圍設備，如果您準備與特定電路板合作，它是最實用的選項之一。

## STM32 何時有用

STM32 適用於：

- 主 3D 打印機電路板；
- Klipper 中的附加 MCU；
- 風扇、傳感器和輸出控制板；
- CAN 板或工具頭板；
- 更嚴肅的自訂電路板；
- 需要計時器、PWM、ADC、UART、SPI、I2C、CAN 或 USB 的任務；
- 需要現成工業生態系統和文檔的項目。

如果 RP2040 是簡單而清晰的起點，STM32 是一個廣闊的控制器世界，您可以為幾乎任何任務選擇芯片。但靈活性是以複雜性為代價的。

## STM32 是一個系列

您不能說「我得到了 STM32」並停止選擇。您需要知道確切的型號。

系列示例：

- **STM32F0 / STM32C0 / STM32G0** — 預算和大眾市場系列；
- **STM32F1** — 老但非常著名的系列，經常在 Blue Pill 和舊電路板上發現；
- **STM32F4** — 更強大的系列，在控制器中很受歡迎；
- **STM32G4** — 對於控制、計時器和模擬外圍設備任務很有趣；
- **STM32H7** — 強大的高端控制器；
- **STM32L / STM32U** — 專注於低功耗的系列。

對於典型用戶，重要的不是系列的營銷，而是具體的事情：

- 需要的固件中是否有支援；
- 電路板上實際暴露了多少 GPIO；
- 它是否具有 USB、CAN、UART、I2C、SPI；
- 閃存和 RAM 的數量；
- 如何刷新它；
- 是否有適當的引腳圖和原理圖。

## 電路板比芯片名稱更重要

相同的 STM32 可能在非常不同的電路板上。

常見變體：

- **Blue Pill / Black Pill** — 便宜的小型電路板，通常採用 STM32F103 或 STM32F4 級別，但克隆品質不同；
- **STM32 Nucleo** — 具有內置 ST-LINK 的官方 ST 開發電路板；
- **現成的 3D 打印機電路板** — 已經具有驅動程序、連接器、MOSFET 輸出、熱敏電阻輸入、保險絲和電源連接器；
- **工具頭/CAN 板** — 用於打印機頭或遠程模塊的專用板；
- **自訂電路板** — 需要完整的電源、USB、SWD、保護和佈線設計。

對於第一個實際項目，通常更容易獲得帶有文檔的現成電路板，而不是裸露的 STM32 或沒有原理圖的隨機克隆。

## STM32 和 Klipper

STM32 是 Klipper MCU 的主要路徑之一。

典型架構：

![STMicroelectronics 的 STM8 和 STM32 Nucleo 板](../../img/02-controllers/04-stm32-nucleo-boards.jpg)

*來源：[Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Nucleo-board.jpg), Avandalen, CC BY-SA 4.0*

Klipper 主機在 Linux 設備上運行，STM32 電路板物理控制引腳：切換 MOSFET 輸出、讀取熱敏電阻、控制風扇、接收限位開關信號並通過 USB、UART 或 CAN 與主機通信。

對於類似 iDryer 的外圍設備，STM32 有意義如果：

- 設備應該是 Klipper 配置的一部分；
- 您需要一個具有電力輸出的現成打印機電路板；
- 您需要 CAN；
- 您需要更多的工業板方法；
- 您已經有一個 STM32 電路板和已知的配置。

如果您需要快速添加幾個引腳和傳感器，RP2040 通常更簡單。如果您需要一個帶有連接器和驅動程序的現成強大電路板，STM32 電路板可能會更好。

## 刷新：USB、DFU、UART、SWD、ST-LINK

STM32 沒有一個適用於所有電路板的通用刷新方法。

選項：

- **USB 引導加載程序 / DFU** — 如果電路板和芯片支援，通過內置 USB 引導加載程序刷新；
- **UART 引導加載程序** — 以正確的 BOOT 模式通過串行引腳刷新；
- **SWD via ST-LINK** — 通過編程器刷新和調試的可靠方式；
- **Nucleo 上的內置 ST-LINK** — 便於開發；
- **打印機電路板上的引導加載程序** — 有時刷新通過 SD 卡、USB 或製造商的特殊引導加載程序進行。

因此，在購買電路板之前，您不僅需要查找芯片數據表，還需要查找該特定電路板的說明。對於 Klipper，特別重要的是閱讀現成電路板配置中的評論和製造商的說明。

## Nucleo、Blue Pill 和打印機電路板

**STM32 Nucleo** 電路板便於學習和原型製作。它們通常具有內置 ST-LINK、Arduino Uno V3 連接器和提供對更多信號訪問的 ST morpho 引腳。如果您想學習 STM32 並有官方刷新工具，這是一個不錯的選擇。

**Blue Pill / Black Pill** 在價格和尺寸上很有吸引力，但克隆品往往有問題：錯誤的芯片、弱弱的調節器、糟糕的 USB、沒有適當的原理圖、奇怪的引導加載程序。對於實驗，它們是有用的，對於可靠的設備——只有在驗證之後。

**現成的 3D 打印機電路板**對於加熱器、風扇和傳感器通常更實用，因為電源部分已經佈線：有端子、MOSFET 輸出、熱敏電阻輸入、電源、保險絲或它們的空間。但即使是現成的電路板也需要檢查電流、連接器、冷卻和安全性。

## 3.3V 邏輯和 GPIO

大多數 STM32 使用 `3.3V` 邏輯工作。

重要：

- 除非芯片數據表明確指出該引腳接受 `5V`，否則不要向引腳施加 `5V`；
- Nucleo 上的 Arduino 屏蔽兼容性並不意味著所有信號都像在 `5V` Arduino Uno 上一樣安全；
- I2C 上拉通常是 `3.3V`；
- GPIO 不應直接為負載供電；
- 風扇、LED 條、加熱器、繼電器和伺服通過驅動器和單獨的電源連接。

即使某些 STM32 引腳接受 `5V`，這也不是連接所有東西的許可。您需要檢查特定芯片的引腳圖表和電氣特性。

## 為什麼 STM32 經常被選擇用於打印機

STM32 對 3D 打印機電路板很好，因為它有許多有用的外圍設備：

- 用於風扇、加熱器和信號的計時器和 PWM；
- 用於熱敏電阻和傳感器的 ADC；
- 用於步進驅動程序和模塊的 UART/SPI；
- 用於顯示器和傳感器的 I2C；
- 與主機通信的 USB；
- 某些系列和電路板中的 CAN；
- 足夠的實時 MCU 任務性能。

但微控制器本身不會使電路板安全。加熱器、電源 MOSFET、SSR、保險絲、連接器和熱保護仍然是單獨的工程任務。

## 購買前要檢查的事項

購買 STM32 電路板之前，請檢查：

- 確切的微控制器型號；
- Klipper 或需要的固件中是否有支援；
- 閃存和 RAM 的數量；
- 電路板如何刷新；
- 它是否具有 USB、CAN、UART 或其他需要的接口；
- 是否有官方引腳圖和原理圖；
- LED、USB、振蕩器、啟動模式或 SWD 佔用的引腳；
- 哪些引腳是 5V 容限的，哪些不是；
- 電路板上的電源輸出以及它們的額定電流；
- 是否有保險絲、端子和適當的電源；
- 製造商的文檔有多容易理解。

如果電路板只用漂亮的照片出售，沒有原理圖，那麼它不是帶加熱器的設備的良好基礎。

## 常見錯誤

- 認為 STM32 是一個特定的電路板；
- 購買 Blue Pill 克隆並期望官方電路板行為；
- 不檢查確切的芯片型號；
- 不了解如何刷新電路板；
- 混淆 DFU、BOOT0、UART 和 ST-LINK；
- 將 `5V` 模塊連接到 `5V` 不容限的引腳；
- 將 SWD 引腳用作常規 GPIO 並失去閃新/調試的能力；
- 認為 GPIO 是電源輸出；
- 為加熱器選擇沒有原理圖的電路板；
- 在購買前不檢查現成的 Klipper 配置。

## 要點

STM32 是一個強大而實用的微控制器系列，特別是對於 3D 打印機電路板和 Klipper MCU。但您需要選擇不是「一般 STM32」，而是特定的電路板、特定的芯片、引腳圖、刷新方法和文檔。

對於第一個簡單的控制器，RP2040 通常更容易。對於現成的打印機電子產品、CAN 板和更嚴肅的外圍設備，STM32 通常是正確的選擇。

## 相關資料

- [STMicroelectronics: STM32 32-bit Arm Cortex MCUs](https://www.st.com/en/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-mcus.html) — STM32 系列、系列、性能和工具的官方概述。
- [STMicroelectronics: STM32 Mainstream MCUs](https://www.st.com/en/microcontrollers-microprocessors/stm32-mainstream-mcus.html) — 大眾市場系列 STM32C0、G0、F0、F1、G4 的概述及其定位。
- [STMicroelectronics: STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) — 通過 ST-LINK/SWD、UART、USB DFU、I2C、SPI 和 CAN 引導加載程序的官方 STM32 刷新工具。
- [STMicroelectronics: NUCLEO-F103RB](https://www.st.com/en/product/nucleo-f103rb) — 具有內置 ST-LINK、Arduino Uno V3 連接器和 ST morpho 引腳的官方 Nucleo 板的示例。
- [ST UM1724: STM32 Nucleo-64 boards user manual](https://www.st.com/resource/en/user_manual/dm00105823-stlink-v2-in-circuit-debugger-programmer-for-stm8-and-stm32-stmicroelectronics.pdf) — Nucleo-64、連接器、ST-LINK 和關於 `3.3V` I/O 的警告的文檔。
- [Klipper: Code overview](https://www.klipper3d.org/Code_Overview.html) — Klipper 架構和 MCU 後端上下文，包括源樹中的 STM32。
