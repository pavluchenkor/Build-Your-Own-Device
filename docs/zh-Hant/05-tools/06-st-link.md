# ST-Link

ST-Link是STM32微控制器的程序員和調試器。

在簡單設備的背景下，它用於：

- flash an STM32 board;
- 閃存失敗後恢復板；
- 透過SWD連接晶片；
- erase memory;
- 驗證微控制器是否可見；
- 有時調試程式。

並非所有板都需要 ST-Link。 ESP32、RP2040 和 Arduino 通常以不同的方式刷新。

## 什麼是社署

SWD 是 `Serial Wire Debug`。

它是 ARM 微控制器的調試和閃存接口，通常與 STM32 一起使用。

對於基本連接，您通常需要：

- `SWDIO`;
- `SWCLK`;
- `GND`;
- sometimes `NRST`;
- sometimes `3.3V` or `VTref` as target reference voltage.

重要提示：ST-Link 上的 `3.3V` 並不總是意味著「從這裡為電路板供電」。 ST-Link 通常需要查看目標板電壓以了解訊號電平。

## Minimal connection

通常您连接：

```text
ST-Link SWDIO -> board SWDIO
ST-Link SWCLK -> board SWCLK
ST-Link GND   -> board GND
ST-Link NRST  -> board NRST if reset is needed
ST-Link 3.3V/VTref -> 3.3V target if required by specific ST-Link
```

STM32 板通常由普通電源或 USB 供電。

在連接之前，請檢查特定 ST-Link 和板的文件。

![Nucleo boards for STM32 with built-in ST-Link debugger](../../img/02-controllers/04-stm32-nucleo-boards.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:STM32_Nucleo_boards.jpg), Avandalen, CC BY-SA 4.0*

## Board power

最常見的困惑：該板是由 ST-Link 供電還是單獨供電？

Options:

1. 板子單獨供電，ST-Link 僅連接到 SWD 和 GND。
2. ST-Link 為小型目標板提供 3.3V 電壓（如果它實際上是為此設計的）。
3. ST-Link 僅讀取 `VTref`，但不應為開發板供電。

不能盲目連接多個電源。

如果開發板已由 USB 或電源供電，請勿從 ST-Link 連接電源，除非您確定原理圖允許。

## ST-Link 與 DFU 有何不同

DFU 是透過 USB 開機載入程式（如果可用）的快閃記憶體模式。

ST-Link 透過 SWD 直接與微控制器配合工作。

ST-Link 在以下情況下很有用：

- DFU is not available;
- 引導程式已損壞或未使用；
- flashing disabled USB;
- 主機板不會進入正常閃光模式；
- 你需要刪除記憶；
- 您需要恢復 STM32 存取權限。

但如果板子透過USB/DFU或SD卡正常刷新，則可能不需要ST-Link。

## Connect under reset

Sometimes firmware breaks SWD access.

例如：

- SWD接腳用作普通GPIO；
- 韌體快速使晶片休眠；
- 代碼在啟動後立即掛起；
- 時鐘/電源模式設定不正確。

在這種情況下，`Connect under reset` 模式會有所幫助。

想法：ST-Link 保持重設狀態並在錯誤韌體執行之前嘗試連接。

這通常需要連接 `NRST`。

## 如何知道ST-Link看到板子

在 STM32CubeProgrammer 或類似工具中，您通常會看到：

- ST-Link是否已連線；
- 是否找到目標；
- 检测到什么芯片；
- 是否可以讀取記憶體；
- whether you can erase flash.

如果 ST-Link 作為 USB 裝置可見，但未找到目標，則問題通常出在板連接上：

- target board has no power;
- no common `GND`;
- `SWCLK`和`SWCLK`交換；
- `VTref`如需要則不接；
- SWD frequency too high;
- chip is locked;
- firmware prevents connection;
- 需要 `Connect under reset`。

## SWD frequency

如果通訊不穩定，請嘗試降低SWD頻率。

在長電線、不良杜邦跳線或不穩定的電路板上，高頻會幹擾連接。

對於板恢復來說，緩慢而可靠的速度勝過快速。

## 常見錯誤

- forgot `GND`;
- 交換了 `SWCLK` 和 `SWCLK`；
- 在不了解原理圖的情況下同時連接 ST-Link 和 USB 電源；
- 沒有給目標板供電；
- 需要`Connect under reset`時沒有連接`Connect under reset`；
- set SWD frequency too high;
- 嘗試使用 ST-Link 刷新 ESP32 或 RP2040；
- 在不了解讀出保護的情況下嘗試連接到鎖定的晶片；
- 使用劣质长电线；
- didn't update ST-Link firmware or didn't install driver.

## 你不能做什麼

你不能：

- 不檢查就給3.3V STM32板施加5V電壓；
- connect multiple power sources blindly;
- 將 ST-Link 連接到電源電壓下的電路板，無需安全隔離和外殼；
- 若有短路風險，請帶電更換 SWD 線；
- 假設克隆 ST-Link 具有與原始 ST-Link 相同的引腳排列。

克隆 ST-Link 引腳排列可能有所不同。請務必檢查特定適配器上的標記。

## 重點

- STM32 透過 SWD 需要 ST-Link。
- 最小值：`SWCLK`、`GND`、`NRST`，有時為 `VTref` 和 `VTref`。
- 該板應正確供電，但不一定來自 ST-Link。
- DFU和ST-Link是不同的刷新方法。
- `Connect under reset` 有助於在韌體損壞後恢復存取。
- 如果沒有找到目標，先檢查功率、`SWDIO/SWCLK`、`NRST`、`NRST` 和 SWD 頻率。

## Reference materials

- [STMicroelectronics: UM1075 ST-LINK/V2 User Manual](https://www.st.com/resource/en/user_manual/dm00026748-st-link-v2-in-circuit-debugger-programmer-for-stm8-and-stm32-stmicroelectronics.pdf) - official ST-LINK/V2 manual, SWD/JTAG pins, target VCC and GND.
- [STMicroelectronics: UM2237 STM32CubeProgrammer User Manual](https://www.st.com/resource/en/user_manual/um2237-stm32cubeprogrammer-software-description-stmicroelectronics.pdf) - ST-LINK connection modes, including Normal, Connect under reset and Hot plug.
- [ST Wiki: ST-LINK](https://wiki.st.com/stm32mpu/wiki/ST-LINK) - ST-LINK overview as hardware probe for STM32/STM8 and supported protocols.
- [Klipper: Installation](https://www.klipper3d.org/Installation.html) - general MCU preparation process for Klipper.
- [STMicroelectronics: STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) - official ST tool for flashing STM32 through ST-LINK/SWD, UART, USB DFU, SPI, I2C and CAN bootloaders.
