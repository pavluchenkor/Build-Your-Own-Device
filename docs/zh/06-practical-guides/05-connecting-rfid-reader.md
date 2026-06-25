# 连接RFID读卡器

RFID/NFC读卡器让你可以不用有线接触就能读取卡、标签或钥匙扣。

在类似iDryer的设备中，这对于线轴标识、材料配置选择、服务访问或消耗品追踪实验很有用。

主要错误：购买“RFID 模块”并假设任何卡都可以在任何控制器上从任何距离读取。实际上，您需要验证频率、标签类型、接口、功率、逻辑电平和天线放置。

## Popular modules

常见的包括：

- RC522 / MFRC522;
- PN532;
- ready-made USB/UART RFID readers;
- 具有 I2C、SPI 或 UART 的 NFC 模块。

对于简单的 3D 打印机项目，13.56 MHz 模块和标签最常见：卡、密钥卡、NTAG/MIFARE 兼容标签。

## 连接前要检查什么

连接之前，找到：

- module frequency;
- 支持的卡和标签类型；
- interface: SPI, I2C, or UART;
- supply voltage;
- logic levels;
- board pinout;
- interface selection via jumpers or solder bridges;
- 读取距离；
- 天线和放置要求。

如果模块的额定值为 `5V`，则不能在不检查的情况下将其直接连接到 `5V` 逻辑。有些板有电压调节器，但缺乏信号线上的电平转换。

## RC522：典型的 SPI 连接

廉价的 RC522 模块通常在 `3.3V` 上运行，并且最常见的是通过 SPI 连接。

典型线路：

- `VCC` - `3.3V` power;
- `GND` - ground;
- `SCK` - SPI clock signal;
- `MOSI`——从控制器到模块的数据；
- `MISO`——模块到控制器的数据；
- `SDA`, `SS`, or `CS` - SPI chip select;
- `RST` - reset;
- `IRQ` - 中断，在简单项目中经常使用。

![RFID RC522 (MFRC522) module for reading 13.56 MHz cards](../../img/06-practical-guides/05-rfid-rc522-module.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:RFID-RC522_photo.jpg), Giacomo Alessandroni, CC BY-SA 4.0*

引脚名称可能不同。例如，在 RC522 上，引脚 `SS` 通常表示 SPI 的 `CS`/`SDA`，而不是 I2C `SDA` 线。这是造成混乱的常见原因。

## PN532: SPI, I2C, or UART

PN532是一个更灵活的模块。根据主板的不同，它可以通过以下方式工作：

- SPI;
- I2C;
- UART.

但你不能只连接任何引脚。在许多 PN532 板上，接口是通过跳线、DIP 开关或焊桥来选择的。

连接之前，请检查：

- 在板上物理选择哪个接口；
- 哪些引脚与所选接口匹配；
- I2C是否需要上拉电阻；
- 是否需要上拉或复位引脚；
- 逻辑电平是否与控制器兼容。

如果板上显示“3.3V 逻辑”，请勿将其直接连接到 5V GPIO。

## 共同点

与其他模块一样，需要共同点。

如果 RFID 模块由一个电源供电而控制器由另一个电源供电，则必须连接它们的 `GND`。

如果没有共地，SPI/I2C/UART可能无法工作或工作不稳定。

## 标签必须与阅读器匹配

RFID/NFC 不是单一的通用标准。

模块在物理上只能读取其芯片和库支持的标签。

检查：

- tag frequency;
- card or fob type;
- 模块是否支持 MIFARE、NTAG、ISO14443A 或所需的类型；
- 只需要读取UID还是同时读取/写入数据？
- 所选库是否支持所需的操作。

对于简单的材料配置文件选择，通常仅读取标签 UID 并将 UID -> 材料映射存储在固件或主机中就足够了。

## 读取距离

小型 RFID/NFC 模块的读取距离通常很短。

Results depend on:

- antenna size;
- tag type;
- tag orientation;
- distance;
- housing plastic;
- nearby metal;
- interference;
- module power.

天线附近的金属会严重影响读数。如果读取器安装在干燥器、腔室或线轴支架中，请在实际组装中测试距离，而不仅仅是在工作台上。

## 阅读器放置在哪里

对于细丝线轴，最好将 RFID/NFC 读取器放置在用户有意携带标签的位置。

不要假设标签总是自动读取来设计逻辑。

Practical options:

- 外壳上的“将标签带到这里”区域；
- 靠近线轴支架的位置；
- 门禁卡服务区；
- 独立面板，读取距离短。

如果标签位于线轴上，请使用不同的线轴、不同的标签方向、不同的塑料和金属接近度进行测试。

## 首次启动

整合前：

1. 连接工作台上的模块。
2. 从库中为您的模块运行一个示例。
3. 验证卡或标签的读取是否稳定。
4. 记录多个标签的UID。
5. 检查不支持的卡是否不会破坏逻辑。
6. 将模块安装到外壳中并重新测试。

在这个阶段，不要立即构建复杂的配置文件系统。首先，实现稳定的UID读取。

## 示例设备逻辑

对于材料剖面，简单的逻辑可以是：

1. User brings tag.
2. 设备读取 UID。
3. UID 在表中查找。
4. 如果 UID 已知，则选择材料配置文件。
5. 如果 UID 未知，设备会要求手动选择配置文件。

RFID不应该是唯一的控制方法。您需要手动备份：菜单、按钮、屏幕或界面设置中的配置文件。

## 组装后要检查什么

Verify:

- module receives correct voltage;
- 逻辑电平与控制器兼容；
- 选择正确的接口；
- `MISO`、`SCK`、`CS`、`CS` 不交换为 SPI；
- `SCL`、`SCL` 不交换为 I2C；
- 对于 UART，`RX` 和 `RX` 正确交叉；
- common ground exists;
- 根据库的要求连接复位/IRQ；
- 读取正确类型的标签；
- 外壳内读取距离正常；
- 金属和电线不要遮挡天线；
- 如果没有读取标签，设备可以正常工作。

## 常见错误

- 将3.3V RC522连接到5V电源或5V逻辑；
- 将 RC522 `SDA` 与 I2C `SDA` 混淆；
- 忘记 SPI 上的 `SS`/`SS`；
- 交换 `MISO` 和 `MISO`；
- 用跳线选择PN532上的一个接口，但连接另一个接口；
- 使用不受支持的卡类型；
- 将天线放置在金属旁边；
- 在工作台上测试读取距离，但不在外壳内测试；
- 使 RFID 成为唯一的配置文件选择方法；
- 仅将重要逻辑存储在 UID 中，而不进行读取错误检查。

## 要点

- 必须针对特定标签和接口选择 RFID/NFC 模块。
- RC522通常需要`3.3V`和SPI。
- PN532 可以通过 SPI、I2C 或 UART 工作，但必须在板上选择接口。
- 需要共同基础。
- Metal near antenna can greatly worsen reading.
- 对于材料配置文件，标签 UID 通常就足够了，但需要手动备份选择。
- 在实际住房中进行测试，而不仅仅是在工作台上进行测试。

## 相关阅读

- [Adafruit: PN532 RFID/NFC Breakout Wiring](https://learn.adafruit.com/adafruit-pn532-rfid-nfc/breakout-wiring) - PN532 connection, SPI/I2C/UART selection, and 3.3V logic warnings.
- [Adafruit: PN532 RFID/NFC guide, single page](https://learn.adafruit.com/adafruit-pn532-rfid-nfc?view=all) - full PN532 guide, wiring, CircuitPython, Raspberry Pi, and interface selection.
- [Adafruit PN532 product page](https://www.adafruit.com/product/364) - PN532 capabilities, NFC/RFID tag support, and 3.3V UART/I2C/SPI interfaces.
- [NXP: MFRC522 Standard performance MIFARE and NTAG frontend](https://www.nxp.com/products/rfid-nfc/nfc-hf/nfc-readers/standard-performance-mifare-and-ntag-frontend:MFRC52202HN1) - official MFRC522/RC522 page for 13.56 MHz MIFARE/NTAG scenarios.
- [DigiKey: MFRC522 Datasheet by NXP](https://www.digikey.com/htmldatasheets/production/993456/0/0/1/mfrc522.html) - MFRC522 technical datasheet: supported cards, power, communication interfaces with controller, and antenna/power effects on distance.
