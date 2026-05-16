# 工具

本章节不是关于工具收集。

它是关于最少的工具集，帮助你安全地组装设备、验证连接、发现简单错误而不需要猜测。

在家用设备（如iDryer和3D打印机）中，工具需用于实际任务：

- 检查24V电源是否存在；
- 理解正极和负极是否接反；
- 检查电线的连续性；
- 测试热敏电阻；
- 查看UART信号是否到达；
- 刷新控制器；
- 制作正确的连接器；
- 查找电源下垂；
- 了解风扇或加热器为什么不打开。

## 最小工具集

对于大多数简单的组装，有用的工具包括：

- 万用表；
- USB-UART或USB-TTL适配器；
- 焊枪；
- 压接工具；
- 电线剪刀和绝缘皮剥线器；
- 热缩管；
- 正确的端子和连接器；
- 如果使用STM32，则需要ST-Link；
- 示波器或至少具有频率计数器的万用表可用于更复杂的诊断。

不需要同时购买所有工具。但万用表和正确的电线工具通常会很快收回成本。

## 工具不能替代理解

万用表不能使主电源部分安全。

焊枪不能修复不良的电路图。

示波器不是解决正极和负极接反的需要。

因此顺序是：

1. 理解应该连接什么。
2. 检查电源。
3. 检查接线。
4. 检查传感器和信号。
5. 只有在那之后才寻找复杂的问题。

## 本章节将包含什么

- `02-multimeter.md` - 测量直流电压、连续性、电阻、熔断器以及为什么电流测量更危险。
- `03-usb-ttl-adapter.md` - USB-UART适配器、TX/RX/GND、3.3V/5V逻辑电平、刷新和日志。
- `04-soldering.md` - 焊接电线、焊盘、模块、冷焊接点、热缩管和应力释放。
- `05-crimping-connectors.md` - Dupont、JST、套管、Faston、端子和压接品质检查。
- `06-st-link.md` - ST-Link、STM32、SWD、刷新失败后的开发板恢复。
- `07-oscilloscope.md` - PWM、UART、电源下垂、噪声和关于主电压的重要安全警告。

## 值得正确购买的东西

有些东西不应该节省：

- 一个有适当探针和连续性模式的万用表；
- 一个带有温度控制的焊枪；
- 优质焊料和助焊剂；
- 用于特定端子的压接工具；
- 额定电流需求的连接器和端子；
- 热缩管；
- 正确规格的电线。

不良的压接或弱端子可能导致比不良固件更多的问题。

## 你不能做的事

你不能：

- 测量通电电路上的电阻；
- 以与测量电压相同的方式测量电流；
- 在不理解安全的情况下将万用表戳入110-230V交流电；
- 以"某种方式"焊接电源部分；
- 对加热器使用Dupont连接器；
- 在电源打开时更换电线；
- 在桌子上放置开启的主电源部分；
- 认为如果电线"能承受"，接触就是好的。

## 要点

- 万用表是第一个诊断工具。
- USB-UART用于日志、刷新和与UART设备的通信。
- 焊接和压接是不同的任务，对于连接器，压接通常更好。
- 当你使用STM32和SWD时需要ST-Link。
- 示波器不是每个人都需要，但它可以快速显示信号、下垂和噪声。
- 对于电源部分，接触品质、电线规格和安全比组装外观更重要。

## Reference materials

- [SparkFun: How to Use a Multimeter](https://learn.sparkfun.com/tutorials/how-to-use-a-multimeter/all) - multimeter basics: voltage, current, resistance, continuity.
- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - hardware checks for power, connections and heat.
- [SparkFun: Serial Communication](https://learn.sparkfun.com/tutorials/serial-communication) - UART and basic serial communication logic.
- [Adafruit: Guide to Excellent Soldering](https://learn.adafruit.com/adafruit-guide-excellent-soldering) - practical soldering guide and connection quality.
- [STMicroelectronics: ST-LINK/V2 User Manual](https://www.st.com/resource/en/user_manual/um1075-stlinkv2-incircuit-debuggerprogrammer-for-stm8-and-stm32-stmicroelectronics.pdf) - official ST-Link documentation and SWD/SWIM.
