# USB-TTL

USB-TTL适配器或USB-UART适配器，让你的电脑通过USB与微控制器通过UART通信。

你需要它用于：

- 刷新某些板；
- 读取日志；
- 调试UART通信；
- 配置模块；
- 当常规USB不工作时恢复板；
- 连接到没有内置USB-UART的设备。

常见的适配器使用CH340、CP2102、FT232等芯片。

## USB-TTL或USB-UART

消费者描述通常说USB-TTL。

从技术上讲，它通常意味着具有TTL逻辑电平的USB-UART适配器。

主要的事情是理解：

- USB侧连接到电脑；
- UART侧连接到微控制器；
- 适配器不是所有板的程序员；
- 如果你需要通过SWD刷新STM32，适配器不会替代ST-Link。

## 主要引脚

通常有：

- `GND`；
- `TX`；
- `RX`；
- `VCC`或`3V3`/`5V`；
- 有时`DTR`；
- 有时`CTS`、`RTS`。

最小通信：

- `GND`；
- `TX`；
- `RX`。

只有在你确定适配器应该为板供电时，才连接电源。

## TX和RX是交叉连接

UART连接如下：

```text
adapter TX -> board RX
adapter RX -> board TX
adapter GND -> board GND
```

`TX`是发送。

`RX`是接收。

一个设备的发送器必须连接到另一个的接收器。

如果你连接`TX`到`TX`，通信通常无法进行。

![UART连接中的交叉连接TX/RX](../../../img/02-controllers/06-uart-tx-rx-crossover.png)

*Source: [SparkFun Electronics](https://learn.sparkfun.com/tutorials/serial-communication/all), CC BY-SA 4.0*

## 公共接地

适配器`GND`和板`GND`必须连接。

没有公共接地，UART可能无法工作或不稳定。

即使板由单独的电源供电，接地仍然需要作为公共信号电平。

## 3.3V和5V逻辑电平

这是最重要的要点之一。

适配器可以工作的逻辑：

- `3.3V`；
- `5V`；
- 可切换`3.3V/5V`。

许多现代板和模块使用3.3V逻辑：ESP32、RP2040、许多STM32。

如果你将5V UART信号应用于3.3V输入，你可能会损坏引脚或整个板。

连接前，验证：

- 板使用什么逻辑电平；
- 适配器使用什么逻辑电平；
- 3.3V/5V跳线做什么；
- 跳线是否只改变`VCC`电源或也改变`TX/RX`电平。

某些适配器提供5V电源但3.3V逻辑信号。其他的同时改变电源和电平。检查特定适配器文档。

## 来自适配器的电源

你不总是需要连接`VCC`。

通常，只连接是更安全的：

- `GND`；
- `TX`；
- `RX`。

从其正常来源为板供电。

你可以连接适配器的`VCC`，如果：

- 板额定为该电压；
- 板电流在适配器能力范围内；
- 同时没有其他电源；
- 板文档允许通过此引脚供电。

一个危险的错误是同时从USB-UART适配器和单独的电源供电，导致源冲突。

## DTR和自动重置

某些板使用`DTR`进行刷新期间的自动重置。

例如，Arduino Pro Mini和类似的板可以通过电容器使用DTR进行自动重置。

如果刷新不会自动启动，可能是因为：

- DTR未连接；
- 需要手动重置；
- 选择了错误的适配器；
- 选择了错误的引导加载程序；
- IDE中的速度或板选择不正确。

对于简单的日志阅读，DTR通常不需要。

## 如何检查适配器是否对系统可见

在macOS和Linux上，适配器通常在`/dev`中显示为设备。

示例：

```bash
ls /dev/tty.*
ls /dev/cu.*
ls /dev/ttyUSB*
ls /dev/ttyACM*
```

在Windows上，它显示为`COM`端口。

如果端口未显示：

- 检查USB电缆；
- 尝试不同的USB端口；
- 检查驱动程序；
- 验证它不只是一根充电电缆；
- 查看适配器上的芯片：CH340、CP2102、FT232。

便宜的适配器有时需要单独的驱动程序，尤其是在Windows上。

## 环路测试

检查适配器的简单方法：

1. 连接适配器的`TX`和`RX`。
2. 打开序列终端。
3. 选择端口和速度。
4. 输入文本。

如果你输入的字符返回，适配器和端口可能工作。

测试后，移除`TX`和`RX`之间的跳线。

## 常见错误

- `TX`连接到`TX`，`RX`到`RX`；
- 忘记公共`GND`；
- 为3.3V板选择了5V电平；
- 连接了`VCC`，尽管板已由单独供电；
- USB电缆是充电专用；
- CH340/CP210x/FTDI驱动未安装；
- 选择了错误的COM端口；
- UART速度不匹配；
- 期望USB-UART通过SWD刷新STM32；
- 混淆了刷新期间的启动模式或重置。

## 要点

- USB-UART适配器是电脑和板之间UART通信所需的。
- 最小通信：`GND`、`TX`、`RX`。
- 适配器`TX`进入板`RX`，适配器`RX`进入板`TX`。
- 连接前检查3.3V/5V逻辑电平。
- `VCC`仅在你绝对需要适配器的电源时才连接。
- 如果适配器不可见，检查电缆、驱动程序和USB端口。

## 参考资料

- [SparkFun: Serial Basic Hookup Guide](https://learn.sparkfun.com/tutorials/serial-basic-hookup-guide) - USB转序列适配器、TX/RX/GND、VCC、DTR和3.3V/5V切换。
- [SparkFun: Serial Basic CH340C Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide/serial-basic-overview) - 现代CH340C USB-UART适配器、引脚、LED和电压选择。
- [SparkFun: Serial Communication](https://learn.sparkfun.com/tutorials/serial-communication) - UART基础、TX/RX和序列通信。
- [Silicon Labs: CP210x USB to UART Bridge VCP Drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) - 官方CP210x虚拟COM端口驱动程序。
- [Adafruit FTDI TTL-232 USB Type C Cable](https://www.adafruit.com/product/4364) - 具有5V电源和3.3V逻辑的电缆示例，显示为什么需要单独读取电源和信号电平。
