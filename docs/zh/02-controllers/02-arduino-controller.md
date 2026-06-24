# Arduino 控制器

Arduino 不是一个特定的微控制器，而是板、库、示例和开发环境的生态系统。当初学者说 "Arduino" 时，他们通常指的是 Arduino Uno、Nano 或基于 ATmega328P 的兼容板。

对于教育，Arduino 仍然非常有用：容易理解 GPIO、按钮、LED、PWM、模拟输入、I2C、SPI 和简单的传感器。但对于 3D 打印机周围的新设备，Arduino Uno/Nano 并不总是最佳选择。

## Arduino 为何受欢迎

Arduino 的优势：

- 大量的教育资料
- 简单的 Arduino IDE
- 许多现成的库
- 易于理解的例子，如 Blink
- 方便快速测试桌子上的传感器
- 容易找到兼容的模块
- 旧板文档充分

如果目标是理解微控制器的基础，Arduino 很好。它降低了进入门槛，让您快速看到结果。

## 作为教育板的 Arduino

Arduino 便于：

- 快速测试按钮、限制开关或传感器
- 通过电压分压器进行简单的热敏电阻测试
- 测试 I2C OLED
- 测试 SPI RFID 模块
- 为小型测试生成 PWM
- 读取模拟电压
- 面包板上的快速实验

在此模式中，Arduino 是一个优秀的实验室工具。您不需要在其上构建最终设备：您可以首先理解电路和传感器，然后将解决方案转移到 ESP32、RP2040、STM32 或打印机板。

## Uno 和 Nano 简明扼要

经典 Arduino Uno 和 Nano 通常基于 ATmega328P。

典型特性：

- `5V` 逻辑
- 16 MHz 时钟
- 32 KB 闪存
- 2 KB SRAM
- 14 个数字引脚
- Uno/Nano 等级上的 6 个 PWM 引脚
- Uno 上 6 个模拟输入，Nano 上 8 个
- 用于刷新和为板供电的 USB

这对于教育草图和简单的独立任务是足够的，但对于复杂的逻辑、网络、Web 界面、大型库和现代系统的方便集成是不够的。

## 原始、克隆和 Arduino 兼容

您需要区分：

- 原始 Arduino 板
- 廉价 Uno/Nano 克隆
- 基于其他微控制器的 Arduino 兼容板
- 具有 Wi-Fi、USB-C、Arm 芯片和其他逻辑的现代 Arduino 板

几美元的 Nano 克隆可以适合实验，但 USB-UART、调节器、焊接和引导加载器的品质可能会有所不同。有时对于 Arduino IDE 中的 Nano 克隆，您需要选择旧的引导加载器或不同的处理器。

如果设备必须长时间无人监管，板质量、调节器、连接器和文档比最低价格更重要。

## 5V 逻辑

旧的 Arduino Uno/Nano 使用 `5V` 逻辑。

这对于某些旧模块很方便，但对于 `3.3V` 设备很危险：

- ESP32 通常不能容忍 GPIO 上的 `5V`
- 许多 OLED、RFID、传感器和无线电模块设计用于 `3.3V`
- I2C 上拉至 `5V` 可能会损坏 `3.3V` 设备
- 某些模块输入与 `5V` 兼容，但这需要在文档中检查

如果 Arduino 连接到 `3.3V` 模块，您需要电平转换器或已知兼容级别的电路。

## GPIO 不向负载供电

Arduino 引脚可以通过电阻点亮 LED 或提供控制信号。它不应直接为风扇、加热器、伺服、继电器或 LED 灯条供电。

典型电路：

![带 ATmega328P 微控制器的 Arduino Uno Rev3](../../img/02-controllers/02-arduino-uno-rev3.jpg)

*来源：[Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Arduino_Uno_Rev3_with_Atmega328P.jpg)、HonCode、CC0 Public Domain*

对于负载，您需要：

- 直流风扇、LED 条带或直流加热器的 MOSFET 或驱动器
- 继电器线圈的晶体管驱动器和保护二极管
- 用于 AC 网络负载的 SSR 或继电器
- 伺服的独立电源
- 低压电路在需要时的公共 GND

GPIO 是一个命令，而不是电源输出。

## PWM 和 analogWrite

在 Arduino 中，Uno/Nano 上的 `analogWrite()` 通常意味着 PWM，而不是真实的模拟输出。电路板快速切换引脚、开启和关闭，改变信号占空比。

这适合于：

- LED 亮度
- 驱动器输入的控制
- 风扇或 MOSFET 模块的简单 PWM
- 教育实验

但有限制：

- PWM 不适用于所有引脚
- PWM 频率是固定的或以非显而易见的方式改变
- `analogWrite()` 和 `analogRead()` 是不同的东西
- 4 引脚 PC 风扇可能需要不同的频率和适当的开集/开漏方法
- 加热器和 SSR 不能在不了解电源部分的情况下使用任何快速 PWM

## 模拟输入

Arduino Uno/Nano 便于简单的模拟测量：

- 电位计
- 通过电压分压器的热敏电阻
- 光传感器
- 通过电压分压器的简单电压传感器

但模拟输入不应看到超过其安全范围的电压。对于 Uno/Nano，这通常是相对于 `5V` 电源或所选 `AREF` 的范围。如果测量更高的电压，您需要分压器和保护。

对于精确的温度测量，您不仅需要 `analogRead()`，还需要：

- 正确的电压分压器电路
- 电阻值
- 热敏电阻表或 Beta 参数
- 稳定的电源/参考电压
- 噪声滤波
- 与物体的机械传感器接触

## Arduino 和 Klipper

一些旧的 AVR 板在历史上可能会在 3D 打印机附近找到，但对于 Klipper 周围的新设备，最好不要从 Uno/Nano 开始。

原因：

- 记忆有限
- 性能较弱
- 5V 逻辑可能会干扰现代 `3.3V` 模块
- 没有附加模块的网络
- 不是新 Klipper MCU 的最实用路径

如果您需要 Klipper 的其他 MCU，通常更实用的是查看 RP2040、STM32 或现成的 3D 打印机板。Arduino 可以保留用于教育、面包板和单个传感器测试。

## Arduino 何时仍然合适

Arduino 适合于：

- 您需要快速测试一个想法
- 您需要解释某些事情如何运作
- 设备非常简单，不需要网络
- 您已经有一个有效的草图
- 清晰度比紧凑性和性能更重要
- 这是一个教育板，而不是最终的电力电子学

Arduino 如果不是好的选择：

- 您需要开箱即用的 Wi-Fi
- 您需要与 Klipper 的紧密集成
- 您需要大量记忆
- 您需要许多现代 `3.3V` 传感器
- 设备必须小巧、长寿且在工业上整洁
- 有一个电源部分，其中独立保护很重要

## 购买前检查

购买 Arduino 兼容板之前，检查：

- 它是原始的、克隆的还是兼容的板
- 安装了哪个微控制器
- `5V` 或 `3.3V` 逻辑
- 使用哪个 USB-UART 芯片
- 您的计算机是否有驱动程序
- 需要哪个引导加载器
- 多少闪存和 SRAM
- 多少个 PWM 和模拟输入
- 是否有原理图和引脚图
- 电源调节器和连接器的质量
- 板是否适合最终任务

## 常见错误

- 认为 Arduino 是一个特定的板
- 将 `5V` Arduino 直接连接到 `3.3V` 模块
- 从 GPIO 为负载供电
- 从 `5V` 引脚为伺服供电并获得重置
- 将 `analogWrite()` 用作真实模拟输出
- 为 Nano 克隆选择错误的引导加载器
- 未安装 USB-UART 的驱动程序
- 尝试在没有理由的情况下在 Uno 上构建现代网络设备
- 将教育面包板转移到没有修改电源、配线和保护的封闭电力设备

## 关键要点

Arduino 是一个很好的教育生态系统，是快速测试的便利工具。它非常适合理解 GPIO、PWM、ADC 和传感器。

但经典 Uno/Nano 是老 `5V` 板，记忆有限，没有网络。对于 3D 打印机周围的新设备，ESP32、RP2040、STM32 或现成的打印机板通常更实用，让 Arduino 成为教育和诊断工具。

## 相关资料

- [Arduino Docs: UNO R3](https://docs.arduino.cc/hardware/uno-rev3) — 官方 Uno R3 规格：ATmega328P、`5V`、引脚、PWM、模拟输入和电路板资源
- [Arduino Store: UNO Rev3 Tech Specs](https://store.arduino.cc/collections/arduino/products/arduino-uno-rev3) — 包含电压、GPIO 电流、记忆、频率和电路板尺寸的表格
- [Arduino Store: Arduino Nano](https://store-usa.arduino.cc/products/arduino-nano) — Nano 规格、电源、记忆、数字和模拟引脚
- [Arduino Help Center: Select the right processor for Arduino Nano](https://support.arduino.cc/hc/en-us/articles/4401874304274-Select-the-right-processor-for-Arduino-Nano) — 为什么 Nano 和 Nano 克隆可能有不同的引导加载器
- [Arduino Language Reference](https://docs.arduino.cc/language-reference/) — `pinMode`、`digitalWrite`、`analogRead`、`analogWrite`、PWM 和基本功能的官方参考
- [Arduino Help Center: Use PWM output with Arduino](https://support.arduino.cc/hc/en-us/articles/9350537961500-Use-PWM-output-with-Arduino) — 常见板的 PWM 引脚列表和 `analogWrite()` 的限制
