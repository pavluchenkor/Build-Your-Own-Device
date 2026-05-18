# 刷微控制器

固件（`firmware`）是一个写入微控制器闪存的程序。没有固件，板不知道如何处理引脚、传感器、风扇和接口。

重要：不要混淆固件和配置。固件写入控制器。Klipper 配置通常位于主机上的 `printer.cfg` 中，并告诉已刷入的 MCU 使用哪些引脚和参数。

## 固件、引导加载程序、配置

三个不同的概念：

- **固件** - 微控制器的主程序；
- **引导加载程序** - 帮助写入主固件的小程序；
- **配置** - 设备设置，例如 Klipper 中的 `printer.cfg`。

引导加载程序首先运行，可以通过 USB、UART、DFU、SD 卡、CAN 或其他机制接受新固件。如果引导加载程序被意外擦除，刷入板可能会变得困难：有时需要 ST-LINK/SWD、USB-UART 或其他编程器。

## 通用路线

刷入前，正常的流程是：

1. 了解确切的板型号。
2. 了解确切的微控制器。
3. 查找引脚分配、原理图和制造商说明。
4. 了解是否需要独立固件或 Klipper MCU 固件。
5. 为这个板查找现成的配置或示例。
6. 选择正确的刷入方法。
7. 构建或下载正确的文件。
8. 将板置于刷入模式。
9. 写入固件。
10. 验证板在系统中出现。
11. 在没有负载的情况下验证与主机和基本引脚的通信。

你不能猜测固件设置。对于 Klipper，微控制器类型、引导加载程序偏移、时钟参考和通信接口特别重要。

## 典型的刷入方法

不同的板刷入方式不同：

![刷微控制器的主要路径](../../../img/02-controllers/11-controller-flashing-paths.svg)

常见的变体：

- **USB 大容量存储 / UF2** - 板显示为磁盘，`.uf2` 被复制到它；
- **USB DFU** - 板进入 DFU 模式，固件通过 USB 写入；
- **USB 串行 / UART 引导加载程序** - 通过串行端口的固件；
- **ST-LINK / SWD** - 编程器连接到 SWD 引脚；
- **SD 卡** - 一些 3D 打印机板用卡上的文件刷入；
- **CAN/Katapult/CanBoot** - 通过 CAN 引导加载程序的固件；
- **Arduino 引导加载程序** - 通过 Arduino IDE 或 avrdude 的草图刷入。

没有一个通用的方法对所有板都适用。方法由特定的板、引导加载程序和固件决定。

## RP2040 和 UF2

对于 Raspberry Pi Pico 和许多 RP2040 板，最简单的方法是 `BOOTSEL` 和 UF2。

通常：

1. 按住 `BOOTSEL`。
2. 连接 USB。
3. 板显示为 `RPI-RP2` 磁盘。
4. 复制 `.uf2` 文件。
5. 磁盘消失，板重新启动。

Pico 的 BOOTSEL 在微控制器 ROM 中，所以在正常刷入时不能被意外擦除。这使 RP2040 对初学者很方便。

## STM32：DFU、ST-LINK、SD 卡

STM32 板以不同的方式刷入。

可能的选项：

- 内置 USB DFU 引导加载程序；
- UART 引导加载程序；
- ST-LINK/SWD；
- 打印机板上的 SD 卡；
- 板制造商引导加载程序；
- CAN 引导加载程序。

对于 STM32，引导加载程序偏移通常很重要。例如，如果引导加载程序占用前 `8 KiB`，Klipper 必须使用正确的偏移量构建。如果选择错误，板刷入后可能无法启动。

ST-LINK/SWD 作为更低级的选项很有用：如果正常的引导加载程序不工作，它通常可以恢复板。但这需要 SWD 引脚、编程器和理解连接。

## Klipper：make menuconfig

对于 Klipper 固件，你通常执行：

```bash
cd ~/klipper
make menuconfig
make
```

在 `make menuconfig` 中，你选择：

- 微控制器体系结构；
- 处理器型号；
- 引导加载程序偏移；
- 时钟参考；
- 通信接口：USB、串行、CAN 等；
- 有时特定板的附加参数。

正确的值通常写在现成配置文件顶部的注释中。如果存在这样的配置，首先阅读其顶部注释。

构建后，固件文件通常出现在 `~/klipper/out/`。接下来，使用适合特定板的方法写入。

## 刷入后验证

刷入后，你必须验证的不仅仅是"刷入器写成功"。

检查：

- 设备是否在系统中出现；
- 如果使用 USB/serial，`/dev/serial/by-id/...` 是否存在；
- 如果使用 CAN，`canbus_uuid` 是否可见；
- 路径是否匹配 `printer.cfg`；
- Klipper 中没有通信错误；
- 引脚是否匹配此特定板的引脚分配；
- 在没有电源负载的情况下基本输入/输出是否工作；
- 风扇/MOSFET/SSR 在安全状态下是否关闭。

对于第一次检查，不要连接加热器作为最终负载。首先在安全条件下验证通信、传感器和逻辑。

## 刷入前要保存什么

更改固件前，保存以下内容很有用：

- 当前的 `printer.cfg`；
- 旧固件版本（如果有）；
- 板型号和微控制器；
- 找到的串行路径或 CAN UUID；
- 连接的照片；
- 引脚分配；
- `make menuconfig` 设置；
- 制造商说明的链接。

如果出错，这些数据将帮助快速恢复。

## 可能出错的事

常见问题：

- USB 线缆是充电专用的；
- 板没有进入引导加载程序；
- 选择了错误的微控制器；
- 选择了错误的引导加载程序偏移；
- 选择了错误的通信接口；
- 写入固件，但在错误的地方查找板；
- 重新连接后串行路径改变；
- SD 卡未被板读取；
- 固件文件对于板引导加载程序名称错误；
- 未安装 DFU/USB-UART 驱动程序；
- 板从两侧供电；
- 刷入后，配置引用旧引脚。

不要因为第一个错误而改变所有内容。最好逐步进行：线缆、引导加载程序模式、MCU 型号、构建设置、写入方法、系统设备出现、配置。

## 刷入和安全

固件可以打开和关闭输出，但它不能替代硬件安全。

对于加热器，你需要：

- 正确的电源开关；
- 保险丝；
- 独立的热保护；
- 正确的温度传感器；
- 安全的机箱；
- 检查固件错误、MCU 挂起或失去通信时的行为。

刷入控制器后，不要连接加热器，直到验证引脚是否选择正确、开启逻辑是否未反转以及安全限制是否有效。

## 典型错误

- 混淆固件和 `printer.cfg`；
- 刷入来自相似但不同板的文件；
- 不阅读现成 Klipper 配置顶部的注释；
- 选择错误的引导加载程序偏移；
- 在不理解后果的情况下擦除引导加载程序；
- 使用充电专用 USB 线缆；
- 不将板置于刷入模式；
- 在 `/dev/serial/by-id` 中查找 CAN 板；
- 通过 `canbus_uuid` 查找 USB-serial 板；
- 在验证引脚前连接电源负载；
- 不保存旧配置。

## 关键要点

固件是控制器内的程序，配置是其操作设置。对于每个板，你必须知道确切的型号、微控制器、引导加载程序、刷入方法和构建参数。

对于 RP2040，UF2/BOOTSEL 通常最简单。对于 STM32，检查特定的板：DFU、ST-LINK、SD 卡、UART 或 CAN 引导加载程序。对于 Klipper，首先查找现成的配置和 `make menuconfig` 的注释。

## 相关资料

- [Klipper: Installation - Building and flashing the micro-controller](https://www.klipper3d.org/Installation.html#building-and-flashing-the-micro-controller) - `make menuconfig`、`make` 和串行路径验证的官方路线。
- [Klipper: Bootloaders](https://www.klipper3d.org/Bootloaders.html) - 为什么板之间的引导加载程序不同、为什么需要引导加载程序偏移以及如何刷入不同的 MCU。
- [Raspberry Pi Documentation: Pico-series microcontrollers](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html) - BOOTSEL、UF2 和 Pico/RP2040/RP2350 的细节。
- [Raspberry Pi Documentation: C/C++ SDK - Your First Binaries](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html#your-first-binaries) - BOOTSEL、USB 大容量存储 `RPI-RP2` 和通过 UF2 刷入 Pico 的官方示例。
- [STMicroelectronics: STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) - 用于通过 ST-LINK/SWD、UART、USB DFU、SPI、I2C 和 CAN 引导加载程序刷入的官方 STM32 工具。
