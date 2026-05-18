# USB-UART 适配器

USB-UART 适配器用于让计算机或 Linux 主机通过 USB 与 UART 设备通信。它将 USB 转换为普通串行线路 `TX`、`RX` 和 `GND`。

此类适配器通常用于烧录、日志查看、诊断以及恢复没有 USB 接口的板子。

## 适用场景

USB-UART 适配器适用于：

- 烧录某些微控制器开发板；
- 读取串行日志；
- 访问设备控制台；
- bootloader 模式诊断；
- 连接 Arduino Pro Mini 及部分 Nano 克隆版；
- 用于没有内置 USB 的开发板；
- 烧录失败后的恢复；
- 通过串口将 MCU 临时连接到主机。

如果开发板已有 USB 接口并作为串行设备被识别，则通常不需要单独的 USB-UART 适配器。

## 引脚说明

典型引脚：

- `TX` 或 `TXO` - 从适配器发送到设备；
- `RX` 或 `RXI` - 从设备接收；
- `GND` - 公共地；
- `VCC`、`3V3` 或 `5V` - 电源（如需要）；
- `DTR` - 常用于自动复位/烧录；
- `RTS`、`CTS` - 流控线或 boot/reset 场景。

接线图：

![CH340T 芯片 USB-UART 适配器](../../../img/02-controllers/10-usb-uart-ch340-adapter.jpg)

*来源：[Wikimedia Commons](https://commons.wikimedia.org/wiki/File:15938_-_USBtoSerial_1.jpg)，SparkFun Electronics，CC BY 2.0*

仅读取日志时，`TX`、`RX` 和 `GND` 通常已足够。只有在明确需要由适配器为开发板供电时，才连接电源。

## TX 与 RX 的连接方式

连接为交叉方式：

```text
TX adapter -> RX device
RX adapter <- TX device
GND adapter -> GND device
```

如果无法连接，首先检查：`TX` 和 `RX` 是否接反、是否有公共 `GND`、波特率是否匹配，以及是否选择了正确的 COM/tty 端口。

## 3.3V 与 5V

USB-UART 适配器分为：

- 仅 `3.3V`；
- 仅 `5V`；
- 带 `3.3V/5V` 切换开关；
- 带跳线或焊接跳线；
- `VCC` 为某一电压，但信号为另一电平。

这一点很重要：`VCC` 电平与 `TX/RX` 电平并不总是能从标签上直接判断。

ESP32、RP2040 和 STM32 通常使用 `3.3V` 逻辑。Arduino Uno/Nano 通常使用 `5V` 逻辑。若将 `5V` 信号接入 `3.3V` 输入，可能损坏开发板。

连接前请查阅适配器和开发板的文档，不要仅凭跳线颜色或外壳标签判断。

## TTL UART 与 RS-232

用于微控制器的 USB-UART 适配器通常输出 TTL/CMOS UART：`3.3V` 或 `5V`。

这与真正的 RS-232 不同。

RS-232 具有不同的电压电平，不能直接连接到微控制器的 GPIO。如果需要与真实的 RS-232 端口通信，需要 USB-RS232 适配器或电平转换器，而非普通的 USB-UART TTL 适配器。

## 适配器供电

适配器上的 `VCC` 引脚有时很有用，但也常被误用。

安全做法：

- 用于日志和诊断时，先只连接 `TX`、`RX`、`GND`；
- 如果开发板已通过 USB、电源或其他电路供电，不要连接 `VCC`；
- 不要通过 USB-UART 为电机、舵机、继电器、加热器和 LED 灯条供电；
- 确认适配器实际能提供的电流量；
- 注意 `VCC` 可能为 `3.3V` 或 `5V`。

在不了解电路的情况下连接两个电源，可能导致反向供电、不稳定或损坏开发板。

## DTR 与 RTS

部分开发板使用 `DTR` 和 `RTS` 实现自动复位或进入 bootloader。

示例：

- Arduino Pro Mini 通常通过电容将 `DTR` 用于烧录时的复位；
- ESP32 开发板可能使用 `DTR`/`RTS` 自动控制 `EN` 和 `BOOT`；
- 某些 bootloader 场景中，若未连接这些线路，需要手动按下按钮。

如果烧录无法自动启动，原因不一定是 `TX/RX` 问题，也可能是 `DTR`/`RTS` 未连接、选择了错误的 bootloader，或需要手动按下 `BOOT`/`RESET`。

## CH340、CP2102、FTDI

常见的 USB-UART 芯片：

- **CH340/CH341** - 价格低廉、使用广泛的适配器；
- **CP2102/CP210x** - 常见的 Silicon Labs USB-UART；
- **FT232/FTDI** - 经典方案，通常价格较高；
- **PL2303** - 见于旧款适配器和线缆。

在现代系统上，驱动程序通常会自动安装，但并非总是如此。如果端口未出现，请检查：

- USB 线缆是否仅为充电线；
- 设备是否被系统识别；
- 是否需要安装驱动；
- 旧驱动是否存在冲突；
- 端口是否被其他程序占用。

## 如何测试适配器

简单的回环测试：

1. 将适配器连接到计算机。
2. 将适配器的 `TX` 连接到适配器的 `RX`。
3. 打开串行终端。
4. 选择端口和波特率，例如 `115200`。
5. 输入字符。
6. 如果工作正常，字符会回显。

此测试可在不使用外部开发板的情况下，验证适配器本身、驱动、线缆和终端程序是否正常。

## 购买前注意事项

购买 USB-UART 适配器前，请确认：

- `TX/RX` 电平：`3.3V`、`5V` 还是可切换；
- 如何选择电平；
- 使用的芯片：CH340、CP2102、FTDI 或其他；
- 是否有适用于你系统的驱动；
- 若需要自动烧录，是否有 `DTR` 和 `RTS`；
- USB 接口类型；
- `GND`、`TX`、`RX`、`VCC` 引脚排列是否方便使用；
- 是否有原理图或完整文档；
- `VCC` 能提供多少电流（如需要）。

用于 ESP32/RP2040/STM32 诊断时，带 `3.3V` 信号且标识清晰的适配器更为方便。

## 常见错误

- 将 `TX` 接 `TX`、`RX` 接 `RX`；
- 忘记连接公共 `GND`；
- 为 `3.3V` 开发板选择了 `5V` 电平；
- 将 `VCC` 连接到已供电的开发板；
- 通过 USB-UART 适配器为负载供电；
- 混淆 USB-UART TTL 与 USB-RS232；
- 使用仅充电的 USB 线缆；
- 未安装 CH340/CP2102/FTDI 驱动；
- 选择了错误的 COM/tty 端口；
- 自动烧录所需的 `DTR`/`RTS` 未连接；
- 串行终端仍处于打开状态，却疑惑为何烧录工具无法打开端口。

## 关键总结

USB-UART 适配器是计算机 USB 与设备 UART 引脚之间的桥梁。最小连接需要交叉连接的 `TX/RX` 和公共 `GND`。

主要风险：`3.3V/5V` 电平错误、不必要的电源连接、将 TTL UART 与 RS-232 混淆，以及烧录时缺少 `DTR`/`RTS` 线路。

## 相关资料

- [SparkFun: Serial Basic CH340C Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide) - USB-UART CH340C 实用指南，包括 `DTR/RX/TX/VCC/CTS/GND` 引脚、电压选择和回环测试。
- [SparkFun: Serial Basic Overview](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide/serial-basic-overview) - 引脚描述及适配器上的 `3.3V/5V` 切换说明。
- [Adafruit: FT232H Serial UART](https://learn.adafruit.com/adafruit-ft232h-breakout/serial-uart) - USB 串行适配器示例，包括 `TX`/`RX`、流控线及设备连接。
- [Silicon Labs: CP2102 USB to UART Bridge](https://www.silabs.com/interface/usb-bridges/classic/device.cp2102) - USB-UART 桥接芯片及虚拟 COM 端口驱动的官方示例。
- [Klipper Configuration Reference: `[mcu]`](https://www.klipper3d.org/Config_Reference.html#mcu) - Klipper 中通过 `serial` 描述串行 MCU 连接的方式。
