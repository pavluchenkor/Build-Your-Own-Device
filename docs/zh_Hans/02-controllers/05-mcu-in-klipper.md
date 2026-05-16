# Klipper 中的 MCU

Klipper 由两个主要部分组成：

- **主机** — 带有 Klipper 的 Linux 计算机，如 Raspberry Pi、Orange Pi、迷你 PC 等；
- **MCU** — 物理控制引脚的微控制器板。

主机进行高级决策、读取配置、处理 G 码并计划操作。MCU 在硬件上执行精确命令：切换输出、读取输入、计数时间、生成 PWM 并向主机报告状态。

## Klipper 中的 MCU 是什么

MCU 代表微控制器单元。

在 Klipper 的上下文中，它是一个特定的板：

- 主 3D 打印机电路板；
- 单独的 RP2040 板；
- 单独的 STM32 板；
- CAN/工具头板；
- 附加 I/O 板。

MCU 不会"像整个打印机一样思考"。它执行主机发送的低级命令。这种分离使 Klipper 灵活：您可以添加第二个或第三个 MCU 并在一个共享配置中使用其引脚。

## 它看起来如何

简化方案：

![Klipper 主机和多个 MCU](../../../img/02-controllers/05-klipper-host-mcu-architecture.svg)

主机通过 USB、UART 或 CAN 与 MCU 通信。在 Klipper 配置中，每个 MCU 获得自己的部分，该 MCU 的引脚然后在风扇、传感器、加热器、输出和其他模块设置中使用。

## 主机做什么

主机：

- 存储和读取 `printer.cfg`；
- 接受 G 码和用户命令；
- 维护高级逻辑；
- 随时间安排操作；
- 同步与 MCU 的通信；
- 决定何时切换风扇、加热器或其他输出；
- 从 MCU 接收读数和状态。

如果这些引脚在外部板上，主机不会直接向风扇施加电流或读取热敏电阻。它只告诉 MCU 要做什么。

## MCU 做什么

MCU：

- 物理控制 GPIO；
- 读取输入和传感器；
- 生成 PWM；
- 在正确的时间执行命令；
- 向主机报告结果；
- 如果固件和配置这样设置，在错误时进入关闭。

例如，如果配置在引脚 `PA8` 上有风扇，则具有该引脚的 MCU 会改变其状态。主机只发送命令。

## `[mcu]` 是什么意思

在 `printer.cfg` 中，`[mcu]` 部分描述 Klipper 应该连接的微控制器。

USB/串行示例：

```ini
[mcu]
serial: /dev/serial/by-id/usb-Klipper_stm32f446xx_...
```

对于附加 MCU，您使用名称：

```ini
[mcu chamber]
serial: /dev/serial/by-id/usb-Klipper_rp2040_...
```

之后，可以使用前缀指定附加 MCU 的引脚：

```ini
[temperature_sensor chamber_air]
sensor_type: Generic 3950
sensor_pin: chamber:gpio26

[fan_generic chamber_fan]
pin: chamber:gpio15
```

逻辑很简单：`chamber:gpio15` 表示"MCU `chamber` 上的引脚 `gpio15`"。

## 引脚名称和前缀

Klipper 使用硬件引脚名称。

例子：

- 对于 STM32：`PA4`、`PB0`、`PC13`；
- 对于 RP2040：`gpio15`、`gpio26`；
- 对于 Arduino/AVR，可能有他们自己的别名。

引脚名称之前可能有符号：

- `!` — 反转逻辑；
- `^` — 如果 MCU 支持，启用上拉；
- `~` — 如果 MCU 支持，启用下拉。

例子：

```ini
[gcode_button chamber_door]
pin: ^chamber:gpio12
```

这不是"Klipper 魔法"，而是特定 MCU 上输入引脚的特定设置。因此，电路板引脚图必须准确。

## 为什么需要附加 MCU

当您需要将外围设备分离到单独的块中时，附加 MCU 很有用。

iDryer 类设备的示例：

- 腔室温度和湿度传感器；
- 循环风扇；
- 过滤器风扇；
- 背光；
- 门按钮；
- 盖子传感器；
- 阻尼伺服；
- 带负载单元的单独模块；
- 附加 OLED 或 RFID；
- 在设备附近路由更方便的紧急输入。

当设备应该是 Klipper 系统的一部分而不是单独的 Wi-Fi 盒时，这种方法很方便。

## MCU 方法或独立控制器

有两条不同的路径。

**Klipper 中的 MCU**：

- 设备从 `printer.cfg` 控制；
- 引脚对 Klipper 可见；
- 您可以使用现有部分，如 `fan_generic`、`temperature_sensor`、`heater_generic`、`output_pin`；
- 状态在 Klipper 界面中可见；
- 需要与主机通信。

**独立控制器**：

- 设备做出自己的决定；
- 可能有 Wi-Fi、网络界面、MQTT；
- 不需要依赖打印机；
- 需要自己的固件和安全逻辑；
- 不作为 Klipper 中的常规 `[mcu]` 连接。

ESP32 通常适合独立的 Wi-Fi 设备。RP2040 和 STM32 通常更方便作为 Klipper 中的有线 MCU。

## USB、UART 和 CAN

主机和 MCU 之间的通信可以不同。

**USB** — 对于主机附近的一个或两个板，最常见和简单的选择。对于 Pico、STM32 板和许多打印机板来说很方便。

**UART** — 通过单独的 TX/RX 引脚的串行通信。在某些板上可能有用，但需要仔细的级别、地面和速度连接。

**CAN** — 对于远程模块、工具头板和更稳定的有线架构很方便。但 CAN 需要受支持的微控制器、CAN 收发器、正确的总线、终结器和 Linux 接口设置。

对于第一个附加控制器，USB 通常更简单。当有真正的原因时，CAN 是有意义的：更长的布线、多个节点、工具头板或现有的 CAN 基础设施。

## MCU 不保护电源部分

重要：添加 MCU 不会使负载安全。

如果 MCU 控制风扇、加热器或 SSR，您仍然需要：

- 正确的电源开关；
- 适当的电源；
- 电流的电线和端子；
- 保险丝；
- 加热器的独立热保护；
- 安全外壳；
- 如果通信丢失或主机关闭时的行为验证。

如果主机与 MCU 失去通信，Klipper 可以关闭系统，但这不能替代硬件保护。加热器的设计应该使单个固件、传感器、SSR 或通信故障不会导致不安全模式。

## 选择 MCU 前要检查的内容

购买 MCU 的电路板之前，检查：

- 微控制器是否受 Klipper 支持；
- 电路板是否有现成的配置或说明；
- 需要的通信方法：USB、UART 或 CAN；
- 电路板如何闪存；
- 是否有足够的 GPIO、ADC、PWM、I2C、SPI、UART；
- 哪些引脚真正暴露；
- GPIO 逻辑：通常 `3.3V`；
- 负载是否需要驱动程序/MOSFET/SSR；
- 是否有电源和引脚图的文档；
- MCU 通信丢失时会发生什么。

对于第一个附加 MCU，通常更容易选择 RP2040/Pico 或具有清晰说明的众所周知的 STM32 板。

## 常见错误

- 认为 MCU 包含所有 Klipper 的逻辑；
- 混淆主机和 MCU；
- 添加 `[mcu chamber]` 但随后指定不带 `chamber:` 前缀的引脚；
- 从别人的引脚图中获取引脚；
- 在 `make menuconfig` 中闪新错误的微控制器类型；
- 不检查引导加载程序偏移和板闪新方法；
- 使用不稳定的 USB 电缆；
- 将 `5V` 连接到 `3.3V` 输入；
- 从 GPIO 为负载供电；
- 认为软件关闭取代保险丝和热保险丝。

## 要点

在 Klipper 中，MCU 是物理控制引脚的板，主机计划并协调工作。附加 MCU 允许您扩展系统并将外围设备移动到更靠近设备的位置。

对于类似 iDryer 的任务，这对于风扇、传感器、过滤器、背光、按钮和一些执行器很方便。但电源部分和加热器安全仍然是单独的硬件任务。

## 相关资料

- [Klipper: Code overview](https://www.klipper3d.org/Code_Overview.html) — Klipper 架构、主机代码和微控制器代码的划分、计时模型和 GPIO。
- [Klipper: Configuration reference - Micro-controller configuration](https://www.klipper3d.org/Config_Reference.html#micro-controller-configuration) — `[mcu]`、附加 `[mcu name]`、引脚名称格式和前缀。
- [Klipper: Installation - Building and flashing the micro-controller](https://www.klipper3d.org/Installation.html#building-and-flashing-the-micro-controller) — `make menuconfig`、构建和闪新 MCU 的一般过程。
- [Klipper: Bootloaders](https://www.klipper3d.org/Bootloaders.html) — 为什么不同的板具有不同的闪新方法以及为什么引导加载程序很重要。
- [Klipper: CANBUS](https://www.klipper3d.org/CANBUS.html) — CAN 通信、`canbus_uuid`、USB 到 CAN 网桥和硬件要求。
