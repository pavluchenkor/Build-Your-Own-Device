# STM32 控制器

STM32 是意法半导体公司基于 Arm Cortex-M 核心的 32 位微控制器系列。它不是单个电路板或芯片：在 STM32 名称下有数十个系列和数百个型号。

在 3D 打印机世界中，STM32 非常普遍。许多现成的打印机电路板、扩展板、CAN 板和控制器都使用 STM32。对于 Klipper 和打印机外围设备，如果您准备与特定电路板合作，它是最实用的选项之一。

## STM32 何时有用

STM32 适用于：

- 主 3D 打印机电路板；
- Klipper 中的附加 MCU；
- 风扇、传感器和输出控制板；
- CAN 板或工具头板；
- 更严肃的自定义电路板；
- 需要计时器、PWM、ADC、UART、SPI、I2C、CAN 或 USB 的任务；
- 需要现成工业生态系统和文档的项目。

如果 RP2040 是简单而清晰的起点，STM32 是一个广阔的控制器世界，您可以为几乎任何任务选择芯片。但灵活性是以复杂性为代价的。

## STM32 是一个系列

您不能说"我得到了 STM32"并停止选择。您需要知道确切的型号。

系列示例：

- **STM32F0 / STM32C0 / STM32G0** — 预算和大众市场系列；
- **STM32F1** — 老但非常著名的系列，经常在 Blue Pill 和旧电路板上发现；
- **STM32F4** — 更强大的系列，在控制器中很受欢迎；
- **STM32G4** — 对于控制、计时器和模拟外围设备任务很有趣；
- **STM32H7** — 强大的高端控制器；
- **STM32L / STM32U** — 专注于低功耗的系列。

对于典型用户，重要的不是系列的营销，而是具体的事情：

- 需要的固件中是否有支持；
- 电路板上实际暴露了多少 GPIO；
- 它是否具有 USB、CAN、UART、I2C、SPI；
- 闪存和 RAM 的数量；
- 如何刷新它；
- 是否有适当的引脚图和原理图。

## 电路板比芯片名称更重要

相同的 STM32 可能在非常不同的电路板上。

常见变体：

- **Blue Pill / Black Pill** — 便宜的小型电路板，通常采用 STM32F103 或 STM32F4 级别，但克隆品质不同；
- **STM32 Nucleo** — 具有内置 ST-LINK 的官方 ST 开发电路板；
- **现成的 3D 打印机电路板** — 已经具有驱动程序、连接器、MOSFET 输出、热敏电阻输入、保险丝和电源连接器；
- **工具头/CAN 板** — 用于打印机头或远程模块的专用板；
- **自定义电路板** — 需要完整的电源、USB、SWD、保护和布线设计。

对于第一个实际项目，通常更容易获得带有文档的现成电路板，而不是裸露的 STM32 或没有原理图的随机克隆。

## STM32 和 Klipper

STM32 是 Klipper MCU 的主要路径之一。

典型架构：

![STMicroelectronics 的 STM8 和 STM32 Nucleo 板](../../img/02-controllers/04-stm32-nucleo-boards.jpg)

*来源：[Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Nucleo-board.jpg), Avandalen, CC BY-SA 4.0*

Klipper 主机在 Linux 设备上运行，STM32 电路板物理控制引脚：切换 MOSFET 输出、读取热敏电阻、控制风扇、接收限位开关信号并通过 USB、UART 或 CAN 与主机通信。

对于类似 iDryer 的外围设备，STM32 有意义如果：

- 设备应该是 Klipper 配置的一部分；
- 您需要一个具有电力输出的现成打印机电路板；
- 您需要 CAN；
- 您需要更多的工业板方法；
- 您已经有一个 STM32 电路板和已知的配置。

如果您需要快速添加几个引脚和传感器，RP2040 通常更简单。如果您需要一个带有连接器和驱动程序的现成强大电路板，STM32 电路板可能会更好。

## 刷新：USB、DFU、UART、SWD、ST-LINK

STM32 没有一个适用于所有电路板的通用刷新方法。

选项：

- **USB 引导加载程序 / DFU** — 如果电路板和芯片支持，通过内置 USB 引导加载程序刷新；
- **UART 引导加载程序** — 以正确的 BOOT 模式通过串行引脚刷新；
- **SWD via ST-LINK** — 通过编程器刷新和调试的可靠方式；
- **Nucleo 上的内置 ST-LINK** — 便于开发；
- **打印机电路板上的引导加载程序** — 有时刷新通过 SD 卡、USB 或制造商的特殊引导加载程序进行。

因此，在购买电路板之前，您不仅需要查找芯片数据表，还需要查找该特定电路板的说明。对于 Klipper，特别重要的是阅读现成电路板配置中的评论和制造商的说明。

## Nucleo、Blue Pill 和打印机电路板

**STM32 Nucleo** 电路板便于学习和原型制作。它们通常具有内置 ST-LINK、Arduino Uno V3 连接器和提供对更多信号访问的 ST morpho 引脚。如果您想学习 STM32 并有官方刷新工具，这是一个不错的选择。

**Blue Pill / Black Pill** 在价格和尺寸上很有吸引力，但克隆品往往有问题：错误的芯片、弱弱的调节器、糟糕的 USB、没有适当的原理图、奇怪的引导加载程序。对于实验，它们是有用的，对于可靠的设备——只有在验证之后。

**现成的 3D 打印机电路板**对于加热器、风扇和传感器通常更实用，因为电源部分已经布线：有端子、MOSFET 输出、热敏电阻输入、电源、保险丝或它们的空间。但即使是现成的电路板也需要检查电流、连接器、冷却和安全性。

## 3.3V 逻辑和 GPIO

大多数 STM32 使用 `3.3V` 逻辑工作。

重要：

- 除非芯片数据表明确指出该引脚接受 `5V`，否则不要向引脚施加 `5V`；
- Nucleo 上的 Arduino 屏蔽兼容性并不意味着所有信号都像在 `5V` Arduino Uno 上一样安全；
- I2C 上拉通常是 `3.3V`；
- GPIO 不应直接为负载供电；
- 风扇、LED 条、加热器、继电器和伺服通过驱动器和单独的电源连接。

即使某些 STM32 引脚接受 `5V`，这也不是连接所有东西的许可。您需要检查特定芯片的引脚图表和电气特性。

## 为什么 STM32 经常被选择用于打印机

STM32 对 3D 打印机电路板很好，因为它有许多有用的外围设备：

- 用于风扇、加热器和信号的计时器和 PWM；
- 用于热敏电阻和传感器的 ADC；
- 用于步进驱动程序和模块的 UART/SPI；
- 用于显示器和传感器的 I2C；
- 与主机通信的 USB；
- 某些系列和电路板中的 CAN；
- 足够的实时 MCU 任务性能。

但微控制器本身不会使电路板安全。加热器、电源 MOSFET、SSR、保险丝、连接器和热保护仍然是单独的工程任务。

## 购买前要检查的事项

购买 STM32 电路板之前，请检查：

- 确切的微控制器型号；
- Klipper 或需要的固件中是否有支持；
- 闪存和 RAM 的数量；
- 电路板如何刷新；
- 它是否具有 USB、CAN、UART 或其他需要的接口；
- 是否有官方引脚图和原理图；
- LED、USB、振荡器、启动模式或 SWD 占用的引脚；
- 哪些引脚是 5V 容限的，哪些不是；
- 电路板上的电源输出以及它们的额定电流；
- 是否有保险丝、端子和适当的电源；
- 制造商的文档有多容易理解。

如果电路板只用漂亮的照片出售，没有原理图，那么它不是带加热器的设备的良好基础。

## 常见错误

- 认为 STM32 是一个特定的电路板；
- 购买 Blue Pill 克隆并期望官方电路板行为；
- 不检查确切的芯片型号；
- 不了解如何刷新电路板；
- 混淆 DFU、BOOT0、UART 和 ST-LINK；
- 将 `5V` 模块连接到 `5V` 不容限的引脚；
- 将 SWD 引脚用作常规 GPIO 并失去闪新/调试的能力；
- 认为 GPIO 是电源输出；
- 为加热器选择没有原理图的电路板；
- 在购买前不检查现成的 Klipper 配置。

## 要点

STM32 是一个强大而实用的微控制器系列，特别是对于 3D 打印机电路板和 Klipper MCU。但您需要选择不是"一般 STM32"，而是特定的电路板、特定的芯片、引脚图、刷新方法和文档。

对于第一个简单的控制器，RP2040 通常更容易。对于现成的打印机电子产品、CAN 板和更严肃的外围设备，STM32 通常是正确的选择。

## 相关资料

- [STMicroelectronics: STM32 32-bit Arm Cortex MCUs](https://www.st.com/en/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-mcus.html) — STM32 系列、系列、性能和工具的官方概述。
- [STMicroelectronics: STM32 Mainstream MCUs](https://www.st.com/en/microcontrollers-microprocessors/stm32-mainstream-mcus.html) — 大众市场系列 STM32C0、G0、F0、F1、G4 的概述及其定位。
- [STMicroelectronics: STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) — 通过 ST-LINK/SWD、UART、USB DFU、I2C、SPI 和 CAN 引导加载程序的官方 STM32 刷新工具。
- [STMicroelectronics: NUCLEO-F103RB](https://www.st.com/en/product/nucleo-f103rb) — 具有内置 ST-LINK、Arduino Uno V3 连接器和 ST morpho 引脚的官方 Nucleo 板的示例。
- [ST UM1724: STM32 Nucleo-64 boards user manual](https://www.st.com/resource/en/user_manual/dm00105823-stlink-v2-in-circuit-debugger-programmer-for-stm8-and-stm32-stmicroelectronics.pdf) — Nucleo-64、连接器、ST-LINK 和关于 `3.3V` I/O 的警告的文档。
- [Klipper: Code overview](https://www.klipper3d.org/Code_Overview.html) — Klipper 架构和 MCU 后端上下文，包括源树中的 STM32。
