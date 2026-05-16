# RP2040 控制器

RP2040 是 Raspberry Pi 微控制器。基于它最著名的板是 Raspberry Pi Pico。

对于 3D 打印机周围的 DIY 外设，RP2040 是最实用的选项之一：便宜、文档齐全、使用 `3.3V` 逻辑、便于通过 USB 刷新，并且适合作为 Klipper 的附加 MCU。

## RP2040 有用的地方

RP2040 适合于：

- Klipper 的附加 I/O 板
- 通过 MOSFET/驱动器的风扇控制器
- 读取热敏电阻和简单的模拟传感器
- 通过 I2C 连接 OLED
- 通过 SPI 或 UART 连接 RFID/NFC
- 用 PWM 信号控制伺服
- 没有 Wi-Fi 的简单独立板
- 传感器和界面的测试平台

如果您需要开箱即用的网络，更容易查看 ESP32 或 Pico W。如果您需要 Klipper 的附加有线 MCU，RP2040 通常更方便。

## Raspberry Pi Pico 为何方便

Raspberry Pi Pico 是基于 RP2040 的现成开发板。它已经有 USB、闪存、电源调节器、`BOOTSEL` 按钮和公开引脚。

Pico 优势：

- 低成本
- 体面的文档和引脚图
- 用于刷新和通信的 USB
- 许多 GPIO
- `3.3V` 逻辑
- 2 UART、2 SPI、2 I2C
- 16 PWM 通道
- Pico 暴露引脚上的 3 个 ADC 输入
- 用于非标准界面的 PIO
- 通过 USB 大容量存储方便的 UF2 刷新

对于第一个项目，最好获得带焊接引脚的 Pico 或 Pico H，而不是裸 RP2040 芯片。裸芯片需要自定义板、闪存、电源、USB、布线和测试。

## BOOTSEL 和 UF2

Pico 的优势之一是简单的刷新过程：

1. 按住 `BOOTSEL` 按钮。
2. 将 USB 连接到您的计算机。
3. 该板显示为 USB 驱动器。
4. 复制 `.uf2` 固件文件。
5. 该板使用新固件重新启动。

这对于 MicroPython、CircuitPython、C/C++ 项目和 Klipper 固件很方便。对于初学者，此方法通常比 ST-Link、DFU 或单独的 USB-UART 更容易理解。

## RP2040 和 Klipper

RP2040 是 Klipper 附加 MCU 的良好候选者。

典型方案：

![带有 RP2040 芯片的 Raspberry Pi Pico](../../../img/02-controllers/03-rp2040-pico-photo.jpg)

*来源：[Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Raspberry_Pi_Pico_oblique.jpg)、Phiarc、CC BY-SA 4.0*

想法是：

- 带有 Klipper 的 Linux 主机保持为主要控制器
- Pico/RP2040 用 Klipper MCU 固件刷新
- 向 `printer.cfg` 添加主要或附加 `[mcu]` 部分
- RP2040 引脚可用于风扇、传感器、PWM 和其他外设
- 电力负荷仍通过 MOSFET、驱动器、继电器或 SSR 连接

当您需要将外设的一部分分离到单独的块中时，这很有用：例如风扇、摄像头传感器、过滤器、背光、按钮、限制开关或服务输出。

## GPIO 和 3.3V 逻辑

RP2040 使用 `3.3V` 逻辑。这意味着：

- 不要向 GPIO 应用 `5V`
- 对于 `5V` 模块，您可能需要电平转换器
- I2C 上拉应进入 `3.3V`
- GPIO 不应直接为负载供电
- 风扇、LED 条带、继电器或加热器需要外部开关/驱动器

模块是否为 "Arduino 兼容" 并不意味着它对 RP2040 安全。您需要检查输入电平和上拉。

## 电源

Pico 通常从 USB 或通过 `VSYS` 引脚供电。该板有一个用于为微控制器供电的调节器。

实践规则：

- 不要从 Pico 上的 `3V3` 引脚为马达、伺服和继电器供电
- 为负荷使用单独的电源
- 连接低电压驱动器的公共 GND
- 检查 `VSYS` 和 USB 的电源来自何处
- 考虑外部模块的电流，而不仅仅是 Pico 本身

如果 Pico 在伺服或风扇启动时重置，问题几乎总是电源、接地或噪声。

## Pico 上的 ADC

Pico 有 ADC 输入，您可以将其用于简单的模拟任务：

- 通过分压器的热敏电阻
- 电位计
- 光传感器
- 通过分压器测量低电压

限制：

- ADC 输入不得超过安全 GPIO 电压
- 要测量 `12V` 或 `24V`，您需要分压器和保护
- 热敏电阻需要正确的电阻、表格/模型和机械接触
- ADC 不能替代万用表或工业仪表

对于加热器，请记住：ADC 仅读取传感器。加热安全由电源开关、固件限制、保险丝和独立的热保护提供。

## 简单术语中的 PIO

PIO 是可编程 I/O。RP2040 有小型可编程块，无需对主代码施加持续负荷，就可以生成或读取非标准信号。

初学者不需要从 PIO 开始。但这是 RP2040 在界面、定时和非标准外设中受欢迎的原因之一。

对于简单的 iDryer 之类的设备，通常常规 GPIO、PWM、I2C、SPI、UART 和 ADC 就足够了。

## Pico、Pico W 和 Pico 2

重要的是不要混淆这些板：

- **Pico / Pico H** — 没有 Wi-Fi 的经典 RP2040 板
- **Pico W / Pico WH** — RP2040 配备板载 Wi-Fi/蓝牙模块
- **Pico 2 / Pico 2 W** — 基于 RP2350 的新一代，这不是 RP2040

如果文章或项目说 RP2040，通常指的是第一代 Pico 或兼容板。Pico 2 在概念上相似，但它是不同的微控制器，固件/引脚兼容性需要单独检查。

## 购买前检查

购买基于 RP2040 的板之前，请检查：

- 它是原始 Pico、Pico W 还是克隆
- 引脚是否焊接
- 它是否有您需要的 USB 连接器
- 是否有正确的引脚图
- 哪些 GPIO 可用
- 您是否需要 Wi-Fi
- 该板是否适合 Klipper 固件
- 电路板和负荷如何供电
- 您是否有足够的 ADC/PWM/I2C/SPI/UART 来完成任务
- 外壳中是否有安装空间

如果计划 Klipper MCU，请提前检查特定板和刷新方法的现有说明。

## 常见错误

- 向 RP2040 GPIO 应用 `5V`
- 从 `3V3` 为伺服或继电器供电
- 忘记与 MOSFET/驱动器的公共 GND
- 认为 Pico W 是常规 Pico，不考虑使用的资源/Wi-Fi 电源
- 购买 Pico 2 期望精确的 RP2040 行为
- 不使用分压器在 ADC 上测量 `12V`/`24V`
- 将加热器直接连接到引脚
- 当常规 Pico 没有 Wi-Fi 时，为 Wi-Fi 任务选择 RP2040
- 不检查特定克隆的引脚图

## 关键要点

RP2040 和 Raspberry Pi Pico 是有线 DIY 外设和 Klipper 附加 MCU 的强大选择。该板便宜、易于理解、文档齐全、便于刷新。

但 RP2040 是 `3.3V` 微控制器，而不是电源控制器。负荷通过驱动器、MOSFET、继电器或 SSR 连接。对于 Wi-Fi 任务，您需要 Pico W 或另一个联网控制器。

## 相关资料

- [Raspberry Pi: RP2040 specifications](https://www.raspberrypi.com/products/rp2040/specifications/) — 官方 RP2040 规格：CPU、SRAM、UART/SPI/I2C、PWM、USB 和 PIO
- [Raspberry Pi Documentation: Pico-series microcontrollers](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html) — Pico、Pico W、Pico 2、GPIO、ADC、PWM 和板变体的区别
- [RP2040 Datasheet](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf) — 微控制器、外设、PIO、GPIO 和 ADC 的详细技术描述
- [Raspberry Pi Pico Datasheet](https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf) — Pico 板本身的文档：电源、USB、暴露的 GPIO 和板限制
- [Raspberry Pi Documentation: C/C++ SDK - Your First Binaries](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html#your-first-binaries) — BOOTSEL、USB 大容量存储 `RPI-RP2` 和复制 UF2 到 Pico 的官方示例
- [Klipper Configuration Reference](https://www.klipper3d.org/Config_Reference.html) — Klipper 中 RP2040 支持的背景和 I2C 等外设的设置
