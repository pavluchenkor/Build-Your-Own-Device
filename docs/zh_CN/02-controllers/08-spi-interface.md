# SPI 接口

SPI 是控制器与外设之间的高速串行通信接口。展开为: `Serial Peripheral Interface`（串行外设接口）。

在需要比 I2C 更快的数据传输速度，或设备为 SPI 设计时使用 SPI：显示器、SD 卡、RFID 模块、传感器、驱动器或存储芯片。

## SPI 的应用场景

在 3D 打印机和 iDryer 等设备中，SPI 可能出现在：

- RFID/NFC 模块，如 RC522；
- OLED/TFT 显示器；
- SD 卡；
- 加速度计（用于输入整形）；
- 步进驱动器，例如 TMC2130/TMC5160；
- 存储芯片；
- ADC/DAC 和扩展板；
- 某些传感器和专用模块。

SPI 通常比 I2C 快，但需要更多的线路和更谨慎的引脚选择。

## 基本线路

典型的 SPI 使用：

- `SCK` 或 `CLK` - 时钟信号；
- `MOSI` - 从控制器到设备的数据；
- `MISO` - 从设备到控制器的数据；
- `CS`、`SS` 或 `NSS` - 选择特定设备；
- `GND` - 公共地；
- 模块电源。

两个设备的接线图：

![SPI: 主从设备之间的基本交换操作](../../../img/02-controllers/08-spi-basic-operation.png)

*来源: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:SPI_basic_operation,_single_Main_%26_Sub.svg), Em3rgent0rdr, CC0 Public Domain*

`SCK`、`MOSI` 和 `MISO` 可以由多个设备共享。但每个设备通常需要自己的 `CS`。

## CS 而不是地址

在 I2C 中，设备由地址区分。在 SPI 中，通常没有地址。控制器用单独的 `CS` 线路选择设备。

例如：

```text
SCK  -> 所有 SPI 设备共享
MOSI -> 共享
MISO -> 共享
CS1  -> RFID 模块
CS2  -> 显示器
CS3  -> SD 卡
```

当控制器想与 RFID 模块通信时，它激活 `CS1`。当它想与显示器通信时，它激活 `CS2`。

最常见的是，`CS` 是低电平有效：在静止状态下线路为 `HIGH`，选择设备时为 `LOW`。但这需要在技术数据表中验证。

## MOSI/MISO 和新名称

在旧的和很常见的方案中，名称是：

- `MOSI` - Master Out Slave In（主出从入）；
- `MISO` - Master In Slave Out（主入从出）；
- `SS` - Slave Select（从选择）。

在较新的文档中，你可能会看到中立的名称：

- `PICO` - Peripheral In Controller Out（外设进控制器出），等同于 MOSI；
- `POCI` - Peripheral Out Controller In（外设出控制器进），等同于 MISO；
- `CS` - Chip Select（芯片选择）。

在 3D 打印机电子产品中，`MOSI`、`MISO`、`SCK`、`CS` 仍然很常见。主要是要理解信号方向并检查特定模块的引脚分配。

## MISO 可能不需要

不是每个 SPI 设备都实际发送数据回来。

例如，简单的显示器可能只接收命令和像素。那么 `MISO` 线路可能缺失或未使用。

但对于读取数据的设备，`MISO` 是必需的：

- RFID 模块；
- SD 卡；
- 传感器；
- 带诊断功能的驱动器；
- 存储芯片。

如果模块应该响应但 `MISO` 未连接或连接错误，初始化可能会失败。

## SPI 速度和模式

SPI 有速度。它可以比 I2C 快得多，但这并不意味着你需要立即设置为最大速度。

工作受以下因素影响：

- 线路长度；
- 地质量；
- 模块及其数据表；
- 噪声水平；
- 控制器频率；
- 选择的 SPI 模式。

SPI 模式由时钟极性和时钟相位参数设定：`CPOL` 和 `CPHA`。模式 0 经常使用，但并非总是如此。如果模式错误，设备可能无法响应或返回不正确的数据。

在大多数现成的库中，模式已经设置。但如果你连接不寻常的模块或编写低级配置，你需要查看数据表。

## 3.3V 和 5V

像其他接口一样，SPI 不保证安全的电压水平。

ESP32、RP2040、STM32 和许多现代模块使用 `3.3V` 逻辑。Arduino Uno/Nano 通常使用 `5V`。

连接前，验证：

- 模块电源；
- `SCK`、`MOSI`、`MISO`、`CS` 的逻辑电平；
- 是否有电平匹配；
- 模块是否容许信号输入的 `5V`；
- 控制器输入是否容许 `5V`。

例如，RC522 通常需要 `3.3V` 电源和逻辑。不通过电平匹配将其连接到 `5V` Arduino 是个坏主意。

## Klipper 中的 SPI

在 Klipper 中，SPI 用于各种设备：TMC 驱动器、加速度计、某些显示器和传感器。

配置可能包括：

- `cs_pin` - 设备选择引脚；
- `spi_bus` - 硬件 SPI 总线；
- `spi_speed` - 速度（单位 Hz）；
- `spi_software_sclk_pin`；
- `spi_software_mosi_pin`；
- `spi_software_miso_pin`。

如果设备连接到额外的 MCU，引脚应属于该 MCU。与其他 Klipper 部分一样，特定板的引脚分配比猜测更重要。

粗略示例：

```ini
[some_spi_device]
cs_pin: chamber:gpio9
spi_software_sclk_pin: chamber:gpio10
spi_software_mosi_pin: chamber:gpio11
spi_software_miso_pin: chamber:gpio12
```

这不是特定设备的现成配置，而是一个示例：所有 SPI 引脚必须在模块实际连接的 MCU 上。

## 线路长度和干扰

SPI 可以高速工作，但不喜欢长的、杂乱的接线。

实用规则：

- 保持 `SCK`、`MOSI`、`MISO`、`CS` 短；
- 靠近 `GND` 布线；
- 不要与加热器和电机线路平行布线；
- 如果有错误，减少 `spi_speed`；
- 使用适当的连接器；
- 不要无缘无故地将 SPI 布线贯穿整个打印机；
- 对于远程节点，更常选择 CAN、UART/RS-485 或靠近模块的单独 MCU。

`SCK` 线路特别敏感：它是时钟信号。如果它不干净，所有通信都会变得不稳定。

## SPI 和 RC522

RC522 是一个很好的 SPI 模块示例，有命名混淆。

在许多 RC522 板上，`SDA` 引脚实际上用作 SPI 的 `SS`/`CS`。这不是 I2C 的 `SDA`。

对于 RC522，你通常需要：

- `3.3V`；
- `GND`；
- `SCK`；
- `MOSI`；
- `MISO`；
- `SDA`/`SS`/`CS`；
- `RST`；
- 有时 `IRQ`，但在简单项目中通常不使用。

详细的接线图在实用文章中：[连接 RFID 读卡器](../06-practical-guides/05-connecting-rfid-reader.md)。

## 连接前的检查清单

连接 SPI 模块前，验证：

- 模块电源；
- 逻辑电平；
- 特定板的引脚分配；
- `SCK`、`MOSI`、`MISO`、`CS` 在哪里；
- 是否需要 `RST`、`DC`、`IRQ` 或其他引脚；
- 哪个 `CS` 分配给设备；
- `CS` 是否与另一个模块冲突；
- 是否需要硬件 SPI 或软件 SPI；
- 文档推荐什么速度；
- 固件是否支持此模块。

## 典型错误

- 混淆了 `MOSI` 和 `MISO`；
- 忘记了 `CS`；
- 两个设备连接到一个 `CS`；
- 没有连接公共 `GND`；
- 将 `5V` 施加到 `3.3V` SPI 模块；
- 将 RC522 上的 `SDA` 误认为 I2C `SDA`；
- 选择了过高的速度；
- 线路太长；
- 将模块连接到一个 MCU，但指定了另一个的引脚；
- 认为 SPI 是驱动负载的电源接口。

## 关键要点

SPI 是控制器附近模块的高速接口。通常你需要 `SCK`、`MOSI`、`MISO`、`CS`、电源和 `GND`。

与 I2C 的主要区别：SPI 通常没有地址，每个设备由单独的 `CS` 选择。连接前，验证引脚分配、逻辑电平、速度、线路长度和固件支持。

## 相关资料

- [SparkFun: Serial Peripheral Interface](https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi) - SPI 的实用解释、数据线、新的 PICO/POCI 名称和基本交换逻辑。
- [SparkFun: SPI Chip Select](https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi/chip-select-cs) - 为什么需要 `CS` 以及如何连接多个 SPI 设备。
- [Adafruit: SPI Devices](https://learn.adafruit.com/circuitpython-basics-i2c-and-spi/spi-devices) - SPI 与 I2C 的比较、单独的 `CS`、速度、极性/相位和局限性。
- [DigiKey: SPI Simplifies Device Communication](https://www.digikey.com/en/articles/why-how-to-use-serial-peripheral-interface-simplify-connections-between-multiple-devices) - 连接多个 SPI 设备的选项和 `CS` 的作用。
- [Klipper Configuration Reference: Common SPI settings](https://www.klipper3d.org/Config_Reference.html) - Klipper 中的 `spi_speed`、`spi_bus`、软件 SPI 和 `cs_pin` 参数。
