---
title: "从哪里开始制作耗材干燥箱"
description: "第一个项目的清晰路线：如何规划耗材干燥箱，选择电子、电加热、气流、外壳，并避免安全遗漏。"
---

# 从哪里开始制作耗材干燥箱

如果你想制作自己的耗材干燥箱、打印机加热腔或独立加热模块，请从这里开始。本页说明文档的阅读顺序，以及购买元件前需要先决定的问题。

您已经在3D打印机上打印，并想制造一个灯丝烘干机。但当您打开电路图时，问题立即出现：选择哪个电源、接地应该在哪里、MOSFET或SSR、为什么需要散热片。本部分逐步回答这些问题——从第一次电流计算到工作正常的设备。

完成本部分后，您将了解您要构建什么、为什么采用这种方式、可能存在的危险在哪里，以及如何在通电前检查设备。

部分逐渐从简单的概念引导至实际结果。

这里的路径从简单到复杂：

1. 首先理解电力、电流、负载和基本安全。
2. 然后确定存在哪些控制器以及选择哪个。
3. 然后理解基本元件：加热器、风扇、传感器、显示器、RFID和负载单元格。
4. 然后学习使用最少工具：万用表、USB-UART、焊枪、压线钳。
5. 然后进行实用连接。
6. 然后考虑外壳和3D打印件。
7. 最后，准备一份常见错误清单和诊断检查清单。

主要想法：

您不需要一次理解所有电子知识。逐步进行，每次理解下一个小步骤就足够了。

本部分应提供的内容：

- 对低电压`12V`/`24V DC`电路如何不同于商用电源`110-230V AC`的理解；
- 粗略计算负载电流的能力；
- 理解何时需要MOSFET、SSR或继电器；
- 理解ESP32、Arduino、RP2040和STM32在实际中的区别；
- 理解为什么对于Klipper MCU，最好查看RP2040或STM32；
- 对传感器、风扇、加热器和显示器的基本理解；
- 最少的万用表诊断技能；
- 理解哪些打印件可以放在热源附近；
- 更好不重复的错误列表。

本部分不做的事：

- 在使用`110-230V AC`时不能取代电工；
- 不教授深层电路设计；
- 不试图解释所有物理；
- 不允许在不理解安全的情况下组装危险设备。

如何阅读：

- 如果主题是新的——按顺序进行；
- 如果您已经制造过设备——作为参考打开所需部分；
- 如果设备不工作——首先查看`08-common-mistakes`；
- 如果您使用`110-230V AC`——首先阅读与安全、SSR、电线、端子和保护接地相关的所有内容。

## 参考资料

- [SparkFun: Voltage, Current, Resistance, and Ohm's Law](https://learn.sparkfun.com/tutorials/voltage-current-resistance-and-ohms-law) - 电压、电流、电阻、闭路和欧姆定律的基本概念。
- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/all) - 初始诊断的实用顺序：电力、连接、极性、焊点、电缆和电压降。
- [Fluke: How to Measure Resistance with a Digital Multimeter](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-resistance) - 为什么在断电状态下进行电阻测量，以及为什么需要万用表检查元件。
- [OSHA: Electrical Incidents - Grounding](https://www.osha.gov/etools/construction/electrical-incidents/grounding) - 为什么需要保护接地，以及为什么使用商用电压需要单独的安全规范。

## 另请参阅

- [Load calculation 24V](../01-electronics-basics/01-load-calculation-24v.md) - 关于电压、电流、电力和电源容量的第一个实用主题。
- [Common components](../03-common-components/01-overview.md) - 在简单设备中最常见的零件地图。
- [Tools](../05-tools/01-overview.md) - 检查、刷新、焊接和诊断所需的内容。
- [Practical guides](../06-practical-guides/01-connecting-fan.md) - 通过控制器进行第一次安全负载连接的例子。
- Common mistakes - 当设备不开启、发热、发出噪音或行为不稳定时要查看的内容。
