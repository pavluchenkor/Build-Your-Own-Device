# 压接连接器

压接是在不焊接的情况下将电线连接到端子或接触点的方法。

一个好的压接提供：

- electrical contact;
- mechanical wire retention;
- insulation support;
- repeatability;
- 组装、维修方便。

不良的压接可能会变热、脱落、导致随机错误，但看起来几乎是正常的。

## 为什么压接通常比焊接更好

对于连接器和端子，压接通常比焊接更好，因为：

- 电线保持灵活；
- 触点由制造商设计；
- 保留绝缘；
- 关节更好地处理振动；
- 连接器可以拆卸和维修；
- 焊接过程中没有熔化塑料连接器主体的风险。

焊接对于焊盘和电线有好处，但如果制造商打算压接，则不应取代连接器中的正确触点。

## 端子和连接器的类型

在简单的设备中，您经常会发现：

- 杜邦 - 面包板的弱信号连接；
- JST-XH/JST-PH 及类似产品 - 传感器、风扇、小模块；
- 套圈 - 螺丝端子中多股线的尖端；
- Faston - 用于某些电源连接的扁平端子；
- 环形端子和铲形端子；
- screw terminals;
- board-mounted terminal blocks.

每种类型都需要自己的触点、自己的线规和自己的工具。

## 您需要合适的工具

钳子不是压接工具。

您可以挤压触点，使其看起来固定，但无法获得适当的压接。

为了获得良好的压接效果，您需要：

- 用于正确线规的端子；
- correct strip length;
- correct tool matrix;
- 矩阵中正确的接触位置；
- 绞线和绝缘压接的单独区域；
- no damaged strands.

专业连接器制造商提供压接规格、压接高度、剥线长度和拉力。对于 DIY 组装，您并不总是能够完全控制，但原则是相同的：触点、电线和工具必须相互匹配。

## Open barrel crimp

许多小型触点，例如 JST 或杜邦，都有两对“翅膀”：

- 一对压接裸露导体；
- 另一对固定绝缘层。

Good result:

- 导体在正确的区域可见；
- 绝缘由后翼保持；
- 外露长度不能太长；
- conductor strands don't stick out;
- 触点不歪斜；
- 触点进入连接器主体并锁定到位。

如果绝缘体进入导体压接区，电接触将会不良。

如果仅压接导体而未固定绝缘层，则移动时电线可能会断裂。

## Ferrules

对于螺钉端子中的多股电线，套圈通常很有用。

They:

- gather all strands together;
- 防止股线分离；
- 改善航站楼的座位；
- 降低某些股线被留在外面的风险；
- 使接缝更整齐。

这对于要维修的电源线、端子块和组件特别有用。

但套圈还必须与线规匹配，并用正确的矩阵进行压接。

## 如何检查压接

压接后，验证：

- 触点不会在线路上移动；
- insulation is held;
- 导体不拉出；
- no strands are cut;
- 外露长度不能太长；
- 触头进入连接器本体；
- 锁卡入到位；
- 电线可以承受轻微的拉扯。

轻柔的拉力测试很有用：小心地拉动电线。它不应该从接触中出来。

不需要用尽全力去拉。目标是在安装前找到明显不良的压接。

## 为什么不良压接会变热

不良压接会产生高电阻。

在电流下这会变成热量。

首先，终端可能只是温暖。然后塑料变暗，接触变差，热量增加。

这对于以下人员来说尤其危险：

- heaters;
- 有大电流的风扇；
- LED strips;
- power supplies;
- SSR/MOSFET circuits;
- mains connections.

如果终端变热，请关闭电源并重新连接。

## 杜邦不是为了权力

杜邦对于面包板和弱信号来说很方便。

但它不能用作适当的电源连接器：

- a heater;
- device power;
- a powerful LED strip;
- mains parts;
- 大电流的电机或伺服。

即使连接器在物理上适合引脚，也不意味着它能够满足所需的电流、振动和热量。

## 常见错误

- 用钳子压接；
- 选择了错误的仪表端子；
- stripped too much insulation;
- stripped too little insulation;
- 压接绝缘体代替导体；
- 没有压接绝缘支撑；
- cut some strands;
- 触点未锁定在体内；
- 杜邦电源线；
- 套圈规格错误；
- didn't do a pull test;
- terminal gets hot but device keeps running.

## 要点

- 压接既是电接触又是机械保持。
- 触点、电线和工具必须相互匹配。
- Pliers don't replace a crimping tool.
- 对于螺钉端子中的多股电线，套圈通常很有用。
- 不良的卷曲可能会变热并且很危险。
- 电源部件不应依赖于薄弱的面包板连接器。

## Reference materials

- [Molex: Quality Crimp Handbook](https://www.molex.com/content/dam/molex/molex-dot-com/products/automated/en-us/commercialcrimpbookpdf/638/63800/TM-638000029-001.pdf?inline=) - detailed crimp quality reference, pull force, conductor and insulation crimp.
- [Molex: Industrial Crimp Quality Handbook](https://www.molex.com/content/dam/molex/molex-dot-com/products/automated/en-us/industrialcrimpbookpdf/640/64016/TM-640160065-001.pdf?inline=) - visual inspection of open and closed barrel crimp, strip length, wire brush and common defects.
- [JST: Application Tooling Guide, Crimp Style](https://www.jst.com/resources/application-tooling-guide/crimp-style/) - example of how specific JST contacts need specific tools, strip length and tensile specs.
- [American Electrical: Wire Ferrules](https://www.americanelectrical.com/wire-ferrules/) - why ferrules are useful for multi-strand wire in terminal blocks.
- [TE Connectivity: Wire Splices](https://www.te.com/en/products/terminals-splices/splices.html) - industrial crimp/splice connection types and why crimping is engineered separately, not random squeezing.
