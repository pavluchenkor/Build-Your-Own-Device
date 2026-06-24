# UART 接口

UART 是两个设备之间的简单串行数据传输接口。展开：`通用异步接收器/发射器`。

在实际项目中，您通常会听到"UART"、"串行"、"TX/RX"或"UART 端口"。对于初学者，关键点是：UART 在 `TX` 线上传输数据，在 `RX` 线上接收，两个设备都需要共同的 `GND` 以实现正确运行。

## UART 使用的地方

UART 几乎随处可见：

- 来自微控制器的调试日志；
- 通过 USB-UART 适配器闪新电路板；
- 某些 Klipper 场景中的主机-MCU 通信；
- GPS、RFID、指纹和传感器模块；
- TMC 步进驱动程序配置；
- 两个微控制器之间的通信；
- 电路板上的服务端口。

UART 很方便，因为它需要很少的电线，非常适合简单的文本、命令和诊断交换。

## TX、RX 和 GND

最小连接：

- `TX` - 传输；
- `RX` - 接收；
- `GND` - 共同接地。

一个设备的 TX 连接到另一个设备的 RX：

![UART 连接中的交叉连接 TX/RX 和共同 GND](../../img/02-controllers/06-uart-tx-rx-crossover.png)

*来源：[SparkFun Electronics](https://learn.sparkfun.com/tutorials/serial-communication/all), CC BY-SA 4.0*

规则：

```text
设备 A TX -> 设备 B RX
设备 A RX <- 设备 B TX
设备 A GND -> 设备 B GND
```

最常见的错误是将 `TX` 连接到 `TX`，将 `RX` 连接到 `RX`。有时模块标记令人困惑，因此如果没有连接，首先仔细检查引脚图和文档，而不是随机更改所有电线。

## UART、USB 和 USB-UART

UART 不是 USB。

计算机通常没有裸 UART 引脚。这就是需要 USB-UART 适配器的原因：它连接到计算机的 USB 一侧，并在另一侧提供 `TX`、`RX`、`GND`，有时还提供 `VCC`、`DTR`、`CTS` 线。

示例：

- 计算机通过 USB-UART 从电路板读取日志；
- USB-UART 闪新没有内置 USB 的电路板；
- 主机通过串行连接到 MCU；
- 适配器帮助在闪新失败后恢复电路板。

不要将电路板上的 USB 连接器与接头上的 UART 引脚混淆。在某些电路板上，USB 已经连接到内置的 USB-UART 芯片，而在其他电路板上，USB 直接连接到微控制器。

## 逻辑电平：3.3V、5V、RS-232

UART 描述数据传输方法，但不保证安全的电压电平。

在 DIY 电子产品中，TTL/CMOS UART 最常见：

- `3.3V` UART - ESP32、RP2040、STM32 和许多现代电路板；
- `5V` UART - Arduino Uno/Nano 和一些较旧的模块。

将 `5V` 信号应用于 `3.3V` 微控制器输入可能会损坏电路板。对于不兼容的电平，需要电平转换器或其他匹配电路。

还有 RS-232，这是分开的。这不是"只是 DB9 连接器上的 UART"。RS-232 具有不同的电压电平和不同的电学逻辑。您不能将真正的 RS-232 端口直接连接到微控制器 GPIO。需要电平转换器，例如 MAX232 类电路或现成的适配器。

## 速度和格式

UART 速度必须匹配。常见值：

```text
9600
57600
115200
250000
1000000
```

如果速度不匹配，终端将显示垃圾或沉默。

还有传输格式。`8N1` 经常使用：

- `8` - 8 个数据位；
- `N` - 无奇偶校验；
- `1` - 一个停止位。

对于大多数简单的任务，设置相同的速度和标准 `8N1` 就足够了，除非模块文档另外要求。

## 3D 打印机中的 UART

在 3D 打印机中，UART 通常提供三个不同的角色。

**主机和电路板通信**

某些电路板可以通过串行/UART 与主机通信。在 Klipper 中，这通过 `[mcu]` 部分中的 `serial` 描述。

**TMC 驱动程序配置**

某些步进驱动程序使用 UART 配置电流、stealthChop/spreadCycle、诊断和状态读取。电机本身通常不由 UART 控制，而是由 `STEP` 和 `DIR` 信号控制。

**调试和闪新**

UART 可用于通过 USB-UART 适配器的日志、引导加载程序模式和电路板恢复。

## 一个 UART - 通常两个活跃设备

经典 UART 是两个设备之间的连接。您不能盲目地将多个发射器连接到一条 `RX` 线。

问题：

- 两个设备同时拉 `TX` 线；
- 数据混合；
- 一个模块接收用于另一个模块的命令；
- 可能的电气冲突。

有时一个 `TX` 可以被多个接收器监听，但这是一个有意的决定，不适合作为通用规则。对于初学者，假设更安全：一个 UART 端口 - 一个设备对。

## 连接前要检查的事项

在连接 UART 之前，验证：

- `TX` 和 `RX` 在哪里；
- 是否需要共同的 `GND`；
- 逻辑电平：`3.3V` 或 `5V`；
- 这是 TTL UART 还是 RS-232；
- 传输速度；
- 格式（如果指定）；
- 这个 UART 没有被 USB 日志或闪新占用；
- 是否有另一个发射器连接到这条线；
- 是否需要连接电源或仅 `TX`/`RX`/`GND`。

USB-UART 适配器的电源仅在清楚电路板应该由其供电时连接。通常对于诊断，只需要 `TX`、`RX` 和 `GND`。

## 典型错误

- 将 `TX` 与 `TX` 连接，`RX` 与 `RX`；
- 忘记共同的 `GND`；
- 将 `5V` UART 应用于 `3.3V` 输入；
- 混淆 TTL UART 和 RS-232；
- 选择错误的波特率；
- 将电源从 USB-UART 适配器连接到已通电的电路板；
- 使用被 USB 日志或引导加载程序占用的 UART 引脚；
- 将多个发射器连接到一条线；
- 认为 UART 可以直接驱动强大的负载。

## 要点

UART 是两个设备之间数据交换的简单接口。您需要交叉连接的 `TX`/`RX`、共同的 `GND`、匹配的速度和兼容的逻辑电平。

UART 不是电源，不能作为电源输出工作。它传输数据，而不是直接旋转电动机或激活加热器。

## 相关资料

- [SparkFun: Serial Communication](https://learn.sparkfun.com/tutorials/serial-communication/all) - 有关 UART、TX/RX、波特率、TTL 串行、RS-232 和常见错误的很好的实践解释。
- [SparkFun: Serial Communication - UARTs](https://learn.sparkfun.com/tutorials/serial-communication/uarts) - UART 在微控制器内部的作用以及为什么需要 TX/RX。
- [Adafruit: Serial UART on FT232H](https://learn.adafruit.com/adafruit-ft232h-breakout/serial-uart) - USB-UART 适配器示例和将 TX/RX/GND 连接到串行设备。
- [SparkFun: Serial Basic CH340C Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide) - USB-UART 适配器、RX/TX/VCC/GND 引脚和环回测试的示例。
- [Klipper: Configuration reference - `[mcu]`](https://www.klipper3d.org/Config_Reference.html#mcu) - Klipper 配置中如何描述串行 MCU 连接。
