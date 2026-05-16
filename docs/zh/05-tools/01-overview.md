# 工具

本章節不是關於工具收集。

它是關於最少的工具集，幫助你安全地組裝設備、驗證連接、發現簡單錯誤而不需要猜測。

在家用設備（如iDryer和3D印表機）中，工具需用於實際任務：

- 檢查24V電源是否存在；
- 理解正極和負極是否接反；
- 檢查電線的連續性；
- 測試熱敏電阻；
- 查看UART信號是否到達；
- 刷新控制器；
- 製作正確的連接器；
- 查找電源下垂；
- 瞭解風扇或加熱器為什麼不打開。

## 最小工具集

對於大多數簡單的組裝，有用的工具包括：

- 萬用表；
- USB-UART或USB-TTL適配器；
- 焊槍；
- 壓接工具；
- 電線剪刀和絕緣皮剝線器；
- 熱縮管；
- 正確的端子和連接器；
- 如果使用STM32，則需要ST-Link；
- 示波器或至少具有頻率計功器的萬用表可用於更複雜的診斷。

不需要同時購買所有工具。但萬用表和正確的電線工具通常會很快收回成本。

## 工具不能替代理解

萬用表不能使主電源部分安全。

焊槍不能修復不良的電路圖。

示波器不是解決正極和負極接反的需要。

因此順序是：

1. 理解應該連接什麼。
2. 檢查電源。
3. 檢查接線。
4. 檢查感測器和信號。
5. 只有在那之後才尋找複雜的問題。

## 本章節將包含什麼

- `02-multimeter.md` - 測量直流電壓、連續性、電阻、熔斷器以及為什麼電流測量更危險。
- `03-usb-ttl-adapter.md` - USB-UART適配器、TX/RX/GND、3.3V/5V邏輯電平、刷新和日誌。
- `04-soldering.md` - 焊接電線、焊盤、模組、冷焊接點、熱縮管和應力釋放。
- `05-crimping-connectors.md` - Dupont、JST、套管、Faston、端子和壓接品質檢查。
- `06-st-link.md` - ST-Link、STM32、SWD、刷新失敗後的開發板恢復。
- `07-oscilloscope.md` - PWM、UART、電源下垂、噪聲和關於主電壓的重要安全警告。

## 值得正確購買的東西

有些東西不應該節省：

- 一個有適當探針和連續性模式的萬用表；
- 一個帶有溫度控制的焊槍；
- 優質焊料和助焊劑；
- 用於特定端子的壓接工具；
- 額定電流需求的連接器和端子；
- 熱縮管；
- 正確規格的電線。

不良的壓接或弱端子可能導致比不良固件更多的問題。

## 你不能做的事

你不能：

- 測量通電電路上的電阻；
- 以與測量電壓相同的方式測量電流；
- 在不理解安全的情況下將萬用表戳入110-230V交流電；
- 以"某種方式"焊接電源部分；
- 對加熱器使用Dupont連接器；
- 在電源打開時更換電線；
- 在桌子上放置開啟的主電源部分；
- 認為如果電線"能承受"，接觸就是好的。

## 要點

- 萬用表是第一個診斷工具。
- USB-UART用於日誌、刷新和與UART設備的通信。
- 焊接和壓接是不同的任務，對於連接器，壓接通常更好。
- 當你使用STM32和SWD時需要ST-Link。
- 示波器不是每個人都需要，但它可以快速顯示信號、下垂和噪聲。
- 對於電源部分，接觸品質、電線規格和安全比組裝外觀更重要。

## Reference materials

- [SparkFun: How to Use a Multimeter](https://learn.sparkfun.com/tutorials/how-to-use-a-multimeter/all) - multimeter basics: voltage, current, resistance, continuity.
- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - hardware checks for power, connections and heat.
- [SparkFun: Serial Communication](https://learn.sparkfun.com/tutorials/serial-communication) - UART and basic serial communication logic.
- [Adafruit: Guide to Excellent Soldering](https://learn.adafruit.com/adafruit-guide-excellent-soldering) - practical soldering guide and connection quality.
- [STMicroelectronics: ST-LINK/V2 User Manual](https://www.st.com/resource/en/user_manual/um1075-stlinkv2-incircuit-debuggerprogrammer-for-stm8-and-stm32-stmicroelectronics.pdf) - official ST-Link documentation and SWD/SWIM.
