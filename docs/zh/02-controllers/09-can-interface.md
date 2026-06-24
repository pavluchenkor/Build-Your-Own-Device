# CAN 接口

CAN 是一个在公共差分线上进行多个设备通信的接口。展开为：`Controller Area Network`（控制器局域网）。

CAN 来自汽车和工业电子产品，但在 3D 打印机中，它因用于工具头板、远程 MCU 和需要比 I2C/SPI 更长和更可靠通信的模块而流行。

## CAN 的用途

在打印机和 iDryer 等外围设备中，CAN 用于：

- 打印机头的工具头板；
- 远程块中的额外 MCU；
- 减少线束中的线数；
- 与 CAN 过滤器、摄像头或干燥机板的通信；
- 多个控制器的分布式系统；
- USB 或长的 I2C/SPI 不方便的情况。

当节点远离主机或主板，附近有电机、加热器和其他噪声源时，CAN 特别有用。

## CANH、CANL 和 GND

物理 CAN 总线通常使用：

- `CANH`；
- `CANL`；
- 有时是 `GND` 或公共参考线；
- 模块电源分开，如果需要的话。

信号作为 `CANH` 和 `CANL` 之间的差值传输。这就是 CAN 处理噪声优于单信号线的原因。

简化的接线图：

![高速 CAN ISO 11898-2 总线与多个节点和终端](../../img/02-controllers/09-can-iso11898-2-network.png)

*来源: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:CAN_ISO11898-2_Network.png), EE JRW, CC BY-SA 4.0*

对于接线，`CANH`/`CANL` 通常使用绞合对。`GND` 取决于具体的电路、板和文档，但在小型 DIY 系统中，通常需要公共参考以获得稳定的操作和接口安全。

## 需要 CAN 收发器

重要提示：微控制器中的 CAN 支持和板上的 CAN 不是同一回事。

要使 CAN 工作，你需要：

- 具有 CAN 控制器或合适固件支持的微控制器；
- 板上的 CAN 收发器；
- 正确的 `CANH`/`CANL` 连接器；
- 收发器电源；
- 终端；
- 为 CAN 构建的固件。

如果微控制器数据表提到 CAN，但板上没有收发器，你无法直接连接到 CAN 总线。

## 拓扑和终端

CAN 是一个总线。良好的拓扑看起来像一条线，节点通过短分支连接。

通常需要两个 `120 欧` 终端：

- 一个在总线的一个物理端；
- 第二个在另一个物理端。

不是一个，不是三个，也不是"在每个板上"。恰好两个在末尾。

如果电源关闭，在正确终止的总线上，万用表在 `CANH` 和 `CANL` 之间通常显示约 `60 欧`，因为两个 `120 欧` 电阻并联。

许多板都有终端跳线。有些内置了终端而没有方便的禁用。所以在组装前，检查总线上所有板的原理图。

## 比特率

CAN 速度必须在所有节点上匹配。在 Klipper 中，CAN 通常使用 `1000000`，即 `1 Mbit/s`，但具体值取决于固件、设置和总线长度。

如果比特率不同，节点将无法正常通信。

对于长距离或有问题的接线，速度可能很关键。速度越高，对总线拓扑、终端和线质量的要求就越严格。

## Klipper 中的 CAN

在 Klipper 中，CAN 用于与 MCU 通信。

CAN 上的设备通常不通过 `serial:` 指定。相反，配置使用 `canbus_uuid`：

```ini
[mcu toolhead]
canbus_uuid: 11aa22bb33cc
```

在 Linux 端，你通常需要一个 `can0` 接口。主机必须有一个 CAN 适配器：

- USB-CAN 适配器；
- USB 转 CAN 网桥模式的板；
- SBC 的 HAT/适配器；
- 其他支持的电路。

Klipper 有一个工具来查找新未初始化设备的 `canbus_uuid`。重要的是要理解：如果设备已由 Klipper 配置，它可能不再显示在列表中作为"新"。

## USB 转 CAN 网桥

某些板可以刷入 USB 转 CAN 网桥模式。然后该板通过 USB 连接到主机，并作为 CAN 适配器出现在 Linux 中。

这很方便，但有一个重要的限制：需要网桥模式与真实 CAN 总线和其他 CAN 节点通信。如果你只有一个靠近主机的板，没有真实的 CAN 总线，通常更简单地使用普通 USB/serial 模式。

另外，USB 转 CAN 网桥不会显示为 `/dev/serial/by-id/...`。它配置为 CAN 接口，使用 `canbus_uuid`，而不是 `serial:`。

## CAN 何时合理

如果以下情况，CAN 值得考虑：

- 你需要连接工具头板；
- 你需要在长的线束上运行通信；
- 你需要多个远程 MCU；
- 你想减少移动部件和机箱之间的线；
- 你已经有 CAN 基础设施；
- 所选板为 Klipper CAN 提供了良好文档。

如果以下情况，CAN 可能不必要：

- 板靠近主机；
- 你只需要一个额外的 MCU；
- USB 工作稳定；
- 你对刷机、`can0`、终端和 Linux 网络没有经验；
- 所选板文档不充分。

对于第一个简单的附加控制器，USB 通常更快和更清楚。当 CAN 解决真实的接线或板分布问题时，它才有意义。

## CAN 不供电负载

CAN 仅用于通信。

如果 CAN 板控制风扇、加热器、SSR 或伺服，它仍需要：

- 板电源；
- 负载电源；
- MOSFET/驱动器/SSR；
- 保险丝；
- 适当的端子；
- 加热器的热保护；
- 安全的机箱。

CAN 不能替代功率电子产品，也不能使加热器安全。

## 购买前的检查清单

购买 CAN 板前，验证：

- 使用什么微控制器；
- 板是否支持 Klipper CAN；
- 是否有 CAN 收发器；
- `CANH` 和 `CANL` 在哪里；
- 是否有终端以及如何启用它；
- 使用什么连接器；
- 板如何供电；
- 板如何刷机；
- 是否有 `canbus_uuid` 的说明；
- 是否需要单独的 USB-CAN 适配器；
- 是否有原理图和引脚分配；
- 有哪些引脚和电源输出可用。

如果卖家只是因为芯片理论上支持它而写"CAN"，但板没有收发器和文档，那就是个差选择。

## 典型错误

- 混淆了 `CANH` 和 `CANL`；
- 遗漏了 CAN 收发器是必需的；
- 只放了一个终端而不是两个；
- 在每个板上启用终端；
- 没有检查 `CANH` 和 `CANL` 之间的电阻；
- 在节点上选择了不同的比特率；
- 期望从 USB 转 CAN 网桥得到 `/dev/serial/by-id`；
- 为 USB 刷入板，但作为 CAN 连接；
- 为 CAN 刷入，但没有配置 `can0`；
- 用长分支做了一个星形而不是总线；
- 认为 CAN 是供电负载的方法。

## 关键要点

CAN 是用于远程 MCU、工具头板和打印机内分布式系统的好接口。它使用差分对 `CANH`/`CANL`，需要 CAN 收发器、正确的拓扑和总线末端的两个终端。

对于 Klipper，CAN 很有用但比 USB 复杂：你需要为 CAN 刷入板，配置适配器/`can0`，查找 `canbus_uuid`，并验证物理总线。在 CAN 实际简化接线或改进连接鲁棒性的地方使用它。

## 相关资料

- [Klipper: CANBUS](https://www.klipper3d.org/CANBUS.html) - 官方 Klipper CAN 文档：硬件、主机适配器、`can0`、`canbus_uuid`、终端和 USB 转 CAN 网桥。
- [Klipper: CANBUS protocol](https://www.klipper3d.org/CANBUS_protocol.html) - Klipper 如何分配 CAN 节点 id 和使用 `canbus_uuid`。
- [CAN Bus Debugger: CAN Bus Termination Explained](https://www.canbusdebugger.com/articles/can-bus-termination) - 两个 `120 欧` 终端、`60 欧` 测量和常见错误的实用解释。
- [DigiKey: CAN Bus explained](https://www.digikey.com/en/blog/can-bus-explained) - CAN 总线、差分通信和在分布式系统中的应用的一般概述。
- [Texas Instruments: Introduction to CAN](https://www.ti.com/lit/an/sloa101b/sloa101b.pdf) - CAN 物理层、收发器和典型网络的基本描述。
