# ESP32 控制器

ESP32 是 Espressif 微控制器系列，具有 Wi-Fi、蓝牙和一整套外设。在 DIY 设备中，当您需要构建独立模块时，通常会选择它：它可以自行连接到网络、读取传感器、在浏览器中显示页面并控制简单的输出。

对于 3D 打印机周围的设备，ESP32 不是作为"另一个电源板"有用，而是作为小型联网控制器：温度/湿度传感器、通风模块、具有 Web 界面的简单过滤器、独立的摄像头监控或独立烘干机。

## ESP32 有用的地方

典型任务：

- Wi-Fi 温度和湿度传感器
- 通过 MOSFET 模块的独立风扇控制器
- 用低电压信号控制继电器或 SSR
- 通过 I2C 的 OLED 显示器
- 通过 SPI 或 UART 的 RFID/NFC 读卡器
- 独立电源的伺服
- 状态和设置的简单网页
- 与 MQTT、Home Assistant 或您自己的本地逻辑集成
- 不需要是 Klipper 一部分的自主原型

当设备应该独立于打印机工作并通过网络交换数据时，ESP32 最为擅长。如果任务只是简单地向 Klipper 添加引脚，通常最好查看 RP2040、STM32 或现成的打印机板。

## 典型设备架构

ESP32 不直接为负载供电。它输出控制信号，单独的模块进行电源工作。

![带 GPIO 引脚的 ESP32 开发板](../../img/02-controllers/01-esp32-dev-board.jpg)

*来源：[Wikimedia Commons](https://commons.wikimedia.org/wiki/File:ESP32_Dev_Board.jpg)，Edwiyanto，CC BY-SA 4.0*

实际上，这看起来像：

- ESP32 由开发板上的 USB 或稳定的 `5V` 供电
- ESP32 逻辑本身在 `3.3V` 上运行
- 传感器连接到 GPIO、I2C、SPI、UART 或 ADC
- 风扇、LED 条带、DC 加热器通过 MOSFET 或驱动器连接
- 网络加热器仅通过适当的 AC SSR/继电器和安全电源部分连接
- 伺服由独立的 `5V/6V` 源供电，ESP32 只提供信号

GPIO 不是负载的电源。引脚可以切换驱动器输入，但不应直接为风扇、加热器、继电器、伺服或 LED 条带供电。

## 电路板上的 ESP32 意味着什么

"ESP32" 标签可以表示不同的东西：

- ESP32 芯片本身
- 带有芯片、闪存和天线的模块，例如 ESP32-WROOM
- 带有 USB、电源调节器、按钮和公开引脚的开发板
- 较新的变种：ESP32-S3、ESP32-C3、ESP32-C6 等

对于第一个项目，使用开发板比裸模块更方便。开发板已经有 USB、电源调节器、`BOOT`/`EN` 按钮和面包板引脚。

购买前检查：

- 确切的电路板和芯片名称
- 是否有 USB-C 或微 USB
- 使用哪个 USB-UART 或内置 USB
- 是否有原理图和引脚图
- 实际公开了哪些 GPIO
- 电路板上有什么电源调节器
- 是否有适当的天线和周围空间
- 电路板尺寸是否适合您的外壳

## 3.3V 逻辑

ESP32 使用 `3.3V` 逻辑工作。这意味着 GPIO 上的典型 `HIGH` 电平约为 `3.3V`，而不是 `5V`。

重要的是：

- 不要将 `5V` 应用于 ESP32 GPIO
- 对于 `5V` 传感器和模块，您可能需要电平转换器
- 如果总线连接到 ESP32，I2C 上拉应进入 `3.3V`
- 一些现成的 MOSFET/SSR 模块可能无法从 `3.3V` 可靠工作
- 负载电源不能从 GPIO 获取

许多传感器已经以 `3.3V` 变种形式提供。对于 ESP32，这是最佳选择。

## 电源

开发板通常具有 USB 输入和 `5V`/`VIN` 引脚，ESP32 本身由 `3.3V` 调节器供电。

常见错误：

- 从弱 USB 电缆为 ESP32 供电
- 从电路板上的 `3.3V` 引脚为伺服、风扇或继电器供电
- 不了解该电流来自何处就连接重负载到 `5V` 引脚
- 未连接 ESP32 和低电压驱动器之间的公共 GND
- Wi-Fi 启动时由于电压下降而重置 ESP32

Wi-Fi 吸取脉动电流。为了稳定运行，良好的电缆、调节器、电路板上的电容和负载的独立电源很重要。

## GPIO 和特殊引脚

ESP32 有许多 GPIO，但并非每个引脚都同样方便。

在经典 ESP32 上：

- 某些引脚与芯片负载相关，这些是绑定引脚
- `GPIO6-GPIO11` 通常由闪存占用，不使用
- `GPIO34-GPIO39` 是仅输入的
- `GPIO1` 和 `GPIO3` 经常用作固件和日志的 UART
- 特定开发板上的某些引脚可能由 LED、按钮或其他电路占用

绑定引脚在启动时确定启动模式。如果外部电路以错误的方式拉动这样的引脚，ESP32 可能无法启动或可能进入固件更新模式。

实践规则：对于第一个版本，使用特定板的引脚图中的引脚，除非您了解其角色，否则避免标记为 `BOOT`、`FLASH`、`STRAP`、`TX0`、`RX0`、`GPIO6-GPIO11` 的引脚。

## ESP32 上的 ADC

ESP32 可以通过 ADC 测量模拟电压，但这不是实验室万用表。

重要的是：

- 在经典 ESP32 上有 ADC1 和 ADC2
- ADC2 与 Wi-Fi 冲突，因此对于 Wi-Fi 设备，最好使用 ADC1 引脚
- 测量范围取决于衰减设置
- 测量可能需要校准
- 您不能将超过 GPIO 安全电平的电压应用于 ADC
- NTC 热敏电阻通常需要电压分压器和固件中的正确表格/模型

如果您需要精确的温度传感器，通常更简单的是使用数字传感器或具有已知库的现成模块。对于 NTC 热敏电阻，ESP32 可以工作，但必须检查电路和 ADC 设置。

## PWM、I2C、SPI 和 UART

ESP32 便于外设：

- 通过 LEDC 的 PWM 适合风扇、背光和伺服信号
- I2C 适合 OLED 显示器和许多传感器
- SPI 适合 RFID 模块、显示器和快速设备
- UART 适合 GPS、某些传感器、其他控制器和调试

ESP32 具有灵活的 GPIO 矩阵：许多信号可以分配给不同的引脚。但这并不意味着任何引脚总是一个好选择。特定的板限制、闪存、启动引脚和占用的 UART 仍然需要考虑。

## ESP32 和 Klipper

ESP32 最好被视为打印机附近的单独 Wi-Fi/IoT 设备，而不是 Klipper 中其他 MCU 的主要路径。

Klipper 组织为一个主机加一个或多个 MCU。对于新的其他 MCU，通常更实用的是使用：

- RP2040
- STM32
- 现成的 3D 打印机板

ESP32 可以与打印机系统分开交换数据：通过 MQTT、HTTP API、Home Assistant、您自己的服务器或另一个集成。但这不再与向 Klipper 配置添加 `[mcu]` 并直接使用引脚相同。

## 购买前检查

购买 ESP32 电路板前，请检查：

- 确切的模型：ESP32、S3、C3、C6 等
- 逻辑电压
- 是否有 USB 以及如何刷新电路板
- 是否有官方引脚图或原理图
- 哪些引脚对 GPIO 安全
- 哪些引脚是仅输入的
- 哪些引脚由闪存/PSRAM、USB、UART 或 LED 占用
- 任务是否有足够的 ADC/I2C/SPI/UART
- 电路板如何供电
- 它是否适合外壳
- 您的场景是否有库或固件

如果来自市场的电路板没有原理图和正确的引脚图，它可以用于实验，但不适合需要长时间无人值守运行的设备。

## 常见错误

- 向 ESP32 GPIO 应用 `5V`
- 从 GPIO 为负载供电
- 从弱 `3.3V` 引脚为伺服或继电器供电
- 忘记与 MOSFET/驱动器的公共 GND
- 为传感器选择 ADC2 引脚，然后启用 Wi-Fi
- 使用启动绑定引脚使 ESP32 无法启动
- 使用 `GPIO34-GPIO39` 作为输出
- 购买没有引脚图和原理图的模块
- 认为"带有 Wi-Fi 的 ESP32"自动意味着安全的网络加热器控制
- 尝试用固件替换电力电子学

## 关键要点

ESP32 是自主 Wi-Fi 设备的良好选择：传感器、Web 界面、简单的通风控制、过滤器、显示器和外设。

但 ESP32 使用 `3.3V` 逻辑，具有特殊引脚，不应直接为负载供电。对于电源电路，需要 MOSFET、驱动器、继电器或 SSR，对于网络加热器，需要完整的安全电源部分。

## 相关资料

- [Espressif: ESP32 Wi-Fi & Bluetooth SoC](https://www.espressif.com/en/products/socs/esp32/datasheet) — ESP32 系列、模块、开发板和文档链接的官方概述
- [Espressif: ESP32 Series Datasheet](https://documentation.espressif.com/esp32_datasheet_en.html) — 芯片特性、外设、ADC、PWM、UART、I2C、SPI 和引脚限制
- [ESP-IDF Programming Guide: GPIO & RTC GPIO](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html) — GPIO 表、绑定引脚、仅输入引脚、闪存/PSRAM 引脚和 Wi-Fi 的 ADC2 限制
- [Espressif: ESP32 Hardware Design Guidelines](https://docs.espressif.com/projects/esp-hardware-design-guidelines/en/latest/esp32/esp-hardware-design-guidelines-en-master-esp32.pdf) — 电源、绑定引脚、GPIO、ADC 和电路板设计的建议
- [Arduino-ESP32: LED Control API](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/ledc.html) — Arduino-ESP32 中用于风扇、背光和其他 PWM 信号的 PWM/LEDC
- [Klipper: Code overview](https://www.klipper3d.org/Code_Overview.html) — MCU 的 Klipper 架构上下文以及源树中支持的微控制器后端列表
