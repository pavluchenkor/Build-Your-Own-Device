# ST-Link

ST-Link是STM32微控制器的程序员和调试器。

在简单设备的背景下，它用于：

- flash an STM32 board;
- 闪存失败后恢复板；
- 通过SWD连接芯片；
- erase memory;
- 验证微控制器是否可见；
- 有时调试程序。

并非所有板都需要 ST-Link。 ESP32、RP2040 和 Arduino 通常以不同的方式刷新。

## 什么是社署

SWD 是 `Serial Wire Debug`。

它是 ARM 微控制器的调试和闪存接口，通常与 STM32 一起使用。

对于基本连接，您通常需要：

- `SWDIO`;
- `SWCLK`;
- `GND`;
- sometimes `NRST`;
- sometimes `3.3V` or `VTref` as target reference voltage.

重要提示：ST-Link 上的 `3.3V` 并不总是意味着“从这里为电路板供电”。 ST-Link 通常需要查看目标板电压以了解信号电平。

## Minimal connection

通常您连接：

```text
ST-Link SWDIO -> board SWDIO
ST-Link SWCLK -> board SWCLK
ST-Link GND   -> board GND
ST-Link NRST  -> board NRST if reset is needed
ST-Link 3.3V/VTref -> 3.3V target if required by specific ST-Link
```

STM32 板通常由普通电源或 USB 供电。

连接之前，请检查特定 ST-Link 和板的文档。

![Nucleo boards for STM32 with built-in ST-Link debugger](../../img/02-controllers/04-stm32-nucleo-boards.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:STM32_Nucleo_boards.jpg), Avandalen, CC BY-SA 4.0*

## Board power

最常见的困惑：该板是由 ST-Link 供电还是单独供电？

Options:

1. 板子单独供电，ST-Link 仅连接到 SWD 和 GND。
2. ST-Link 为小型目标板提供 3.3V 电压（如果它实际上是为此设计的）。
3. ST-Link 仅读取 `VTref`，但不应为开发板供电。

不能盲目连接多个电源。

如果开发板已由 USB 或电源供电，请不要从 ST-Link 连接电源，除非您确定原理图允许。

## ST-Link 与 DFU 有何不同

DFU 是通过 USB 引导加载程序（如果可用）的闪存模式。

ST-Link 通过 SWD 直接与微控制器配合工作。

ST-Link 在以下情况下很有用：

- DFU is not available;
- 引导加载程序已损坏或未使用；
- flashing disabled USB;
- 主板不会进入正常闪光模式；
- 你需要删除记忆；
- 您需要恢复 STM32 访问权限。

但如果板子通过USB/DFU或SD卡正常刷新，则可能不需要ST-Link。

## Connect under reset

Sometimes firmware breaks SWD access.

例如：

- SWD引脚用作普通GPIO；
- 固件快速使芯片休眠；
- 代码在启动后立即挂起；
- 时钟/电源模式设置不正确。

在这种情况下，`Connect under reset` 模式会有所帮助。

想法：ST-Link 保持复位状态并在错误固件执行之前尝试连接。

这通常需要连接 `NRST`。

## 如何知道ST-Link看到板子

在 STM32CubeProgrammer 或类似工具中，您通常会看到：

- ST-Link是否已连接；
- 是否找到目标；
- 检测到什么芯片；
- 是否可以读取内存；
- whether you can erase flash.

如果 ST-Link 作为 USB 设备可见，但未找到目标，则问题通常出在板连接上：

- target board has no power;
- no common `GND`;
- `SWCLK`和`SWCLK`交换；
- `VTref`如需要则不接；
- SWD frequency too high;
- chip is locked;
- firmware prevents connection;
- 需要 `Connect under reset`。

## SWD frequency

如果通讯不稳定，请尝试降低SWD频率。

在长电线、不良杜邦跳线或不稳定的电路板上，高频会干扰连接。

对于板恢复来说，缓慢而可靠的速度胜过快速。

## 常见错误

- forgot `GND`;
- 交换了 `SWCLK` 和 `SWCLK`；
- 在不了解原理图的情况下同时连接 ST-Link 和 USB 电源；
- 没有给目标板供电；
- 需要`Connect under reset`时没有连接`Connect under reset`；
- set SWD frequency too high;
- 尝试使用 ST-Link 刷新 ESP32 或 RP2040；
- 在不了解读出保护的情况下尝试连接到锁定的芯片；
- 使用劣质长电线；
- didn't update ST-Link firmware or didn't install driver.

## 你不能做什么

你不能：

- 不检查就给3.3V STM32板施加5V电压；
- connect multiple power sources blindly;
- 将 ST-Link 连接到电源电压下的电路板，无需安全隔离和外壳；
- 如果存在短路风险，请带电更换 SWD 线；
- 假设克隆 ST-Link 具有与原始 ST-Link 相同的引脚排列。

克隆 ST-Link 引脚排列可能有所不同。请务必检查特定适配器上的标记。

## 要点

- STM32 通过 SWD 需要 ST-Link。
- 最小值：`SWCLK`、`GND`、`NRST`，有时为 `VTref` 和 `VTref`。
- 该板应正确供电，但不一定来自 ST-Link。
- DFU和ST-Link是不同的刷新方法。
- `Connect under reset` 有助于在固件损坏后恢复访问。
- 如果没有找到目标，首先检查功率、`SWDIO/SWCLK`、`NRST`、`NRST` 和 SWD 频率。

## Reference materials

- [STMicroelectronics: UM1075 ST-LINK/V2 User Manual](https://www.st.com/resource/en/user_manual/dm00026748-st-link-v2-in-circuit-debugger-programmer-for-stm8-and-stm32-stmicroelectronics.pdf) - official ST-LINK/V2 manual, SWD/JTAG pins, target VCC and GND.
- [STMicroelectronics: UM2237 STM32CubeProgrammer User Manual](https://www.st.com/resource/en/user_manual/um2237-stm32cubeprogrammer-software-description-stmicroelectronics.pdf) - ST-LINK connection modes, including Normal, Connect under reset and Hot plug.
- [ST Wiki: ST-LINK](https://wiki.st.com/stm32mpu/wiki/ST-LINK) - ST-LINK overview as hardware probe for STM32/STM8 and supported protocols.
- [Klipper: Installation](https://www.klipper3d.org/Installation.html) - general MCU preparation process for Klipper.
- [STMicroelectronics: STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) - official ST tool for flashing STM32 through ST-LINK/SWD, UART, USB DFU, SPI, I2C and CAN bootloaders.
