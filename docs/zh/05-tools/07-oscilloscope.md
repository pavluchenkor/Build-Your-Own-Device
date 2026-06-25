# 示波器

示波器显示信号如何随时间变化。

万用表可以显示"约3.3V"或"有频率"。示波器显示信号形状：脉冲、边缘、下垂、噪声、弹跳、UART数据包、PWM。

![Screen of a digital oscilloscope](../../img/05-tools/07-digital-oscilloscope.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Digital_oscilloscope.jpg), premek.v, Public Domain*

示波器屏幕上的 PWM 信号如下所示：

![Animation of PWM: duty cycle change and signal waveform](../../img/05-tools/07-pwm-signal-waveform.gif)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Pwm.gif), Mik81, CC0 Public Domain*

您不需要为每个简单的构建都配备一个。但是，当设备运行不稳定时，示波器可以在几分钟内显示万用表无法看到的内容。

## 你能看到什么

在类似 iDryer 的设备中，示波器可用于查看：

- fan PWM;
- MOSFET module PWM;
- UART `TX/RX`;
- 5V or 3.3V sag at servo startup;
- power supply noise;
- button bounce;
- tachometric fan signal;
- 万用表平均消除的短暂故障。

示波器不仅可以回答“是否有电压”，还可以回答“信号随时间变化的情况”。

## 最重要的警告

大多数台式示波器的探头接地连接到电源保护接地。

这意味着：探头的接地夹不仅仅是“另一根电线”。

如果将接地夹连接到低压电路的 `GND` 以外的点，则可以通过示波器创建短路。

用普通示波器进入市电110-230V交流部分、SSR、电源或高压部分尤其危险。

你不能：

- 断开示波器接地以进行“浮动”测量；
- 将探头接地连接到相或另一个电压点；
- 在不了解电路的情况下用普通探头测量市电电压；
- 假设两个通道完全独立：通道接地通常连接在一起。

对于浮动测量、高侧测量和高压测量，您需要正确的方法：差分探头、隔离设备或其他安全方法。

## 如何连接探头

对于低压电路：

1. 将探头连接到示波器。
2. 将探头接地连接到设备的 `GND`。
3. 将探头尖端连接到信号。
4. 选择正确的探头设置：`10x` 或 `10x`。
5. 确保示波器设置为相同的系数。

对于大多数数字信号，请使用 `10x`：探头对电路的负载较小，通常可以更好地显示信号形状。

## PWM

PWM is a pulse signal.

示波器显示：

- frequency;
- duty cycle;
- logic high level;
- logic low level;
- edges;
- jitter;
- noise.

对于风扇或 MOSFET，这有助于理解：

- 引脚是否输出信号；
- 3.3V或5V电平是否足够；
- 频率是否与设定相符；
- 占空比是否根据命令改变；
- 连接负载时信号是否不会下垂。

## UART

示波器上的 UART 看起来像一个脉冲序列。

示波器有助于查看：

- `TX` 上是否有活动；
- 逻辑电平是否不交换；
- 空闲级别是多少；
- 是否有强烈噪音；
- whether baud rate roughly matches.

对于文本解码，逻辑分析仪或 USB-UART 适配器更方便。但示波器可以快速显示信号是否有效。

## Power supply sag

万用表可能看不到短暂的电压下降。

例如，当伺服系统启动时，5V 线路可能会下降几毫秒。万用表显示5V几乎正常，但控制器已经重新启动。

An oscilloscope lets you see:

- 电压下降多少；
- 下垂持续多久；
- 是否有尖峰；
- whether a capacitor helps;
- 情况是否因不同的电源或电线而改变。

这对于 ESP32、伺服系统、风扇和 DC-DC 特别有用。

## 噪音和干扰

电源或信号线上的噪声可能会破坏传感器和通信。

An oscilloscope helps see:

- DC-DC ripple;
- motor spikes;
- 加热器附近的噪音；
- button bounce;
- 长电线上的干扰。

但要了解其局限性：探头接地不良可能会增加显示器本身的噪声。短探头接地弹簧或短接地线通常比长夹子提供更真实的图像。

## 带频率测量功能的万用表

有时初始检查不需要示波器。

一些万用表可以测量信号频率。在规范中，这可能称为 `frequency`、`frequency counter` 或 `frequency counter`。

如果您需要快速理解以下内容，这很有用：

- whether a PWM signal exists at all;
- 频率是否随调整而变化；
- 控制器输出是否工作；
- 简单数字线路上是否有活动。

例如，如果控制器要向风扇或MOSFET模块输出PWM，测频万用表可以显示信号存在并且其频率与预期值大致匹配。

But a multimeter doesn't show signal shape. It won't show:

- logic high level;
- pulse width;
- PWM duty cycle;
- signal edges;
- brief dips;
- 噪音和干扰；
- line distortion.

因此，测频万用表是快速检查的好工具，但不能完全替代示波器。

## 测量前要检查什么

连接探头之前：

1. 电路中的`GND`是什么？
2. 该点是否连接到电源保护接地？
3. 没有市电电压吗？
4. 探头的额定电压是多少？
5. 如果需要的话是否选择`10x`？
6. 探头和通道设置是否相同？
7. 通道地不连接不同的电路点吗？
8. 可以先检查一下低压侧的信号吗？

如果您对 110-230V AC 有疑问，请勿连接示波器。

## 常见错误

- 接地夹连接到电压点，而不是 `GND`；
- 试图将示波器接地与电源“断开”；
- 使用无差动的普通探头测量电源电压；
- 忘记通道接地已连接；
- 探头设置为 `1x`，示波器设置为 `1x`；
- 使用长探头接地并看到额外的噪声；
- 仅用万用表查看并错过了短暂的电压下降；
- 当线路上没有物理信号时，认为 UART 问题是软件问题。

## 要点

- An oscilloscope shows signal shape over time.
- 它对于 PWM、UART、功率骤降、噪声和短暂毛刺非常有用。
- 普通台式示波器接地连接到电源保护接地。
- 您不能将探头接地连接到任意电路点。
- 对于干线和浮动测量，需要特殊的安全方法。
- 测频万用表很有用，但不能替代示波器。

## Reference materials

- [SparkFun: How to Use an Oscilloscope](https://learn.sparkfun.com/tutorials/how-to-use-an-oscilloscope/introduction) - basic practical introduction to oscilloscopes, signals and controls.
- [Tektronix: How to Use an Oscilloscope](https://www.tek.com.cn/documents/primer/how-to-use-an-oscilloscope) - grounding, setup, controls and basic oscilloscope use.
- [Tektronix: ABCs of Probes Primer](https://www.tek.com/en/documents/whitepaper/abcs-probes-primer) - warnings about probe ground, mains earth and danger of floating measurements with a normal oscilloscope.
- [Tektronix: Floating Oscilloscope Measurements and Operator Protection](https://www.tek.com/en/documents/technical-brief/floating-oscilloscope-measurements-and-operator-protection) - why disconnecting oscilloscope mains earth is dangerous and what safe alternatives exist.
- [Keysight: Floating an oscilloscope](https://docs.keysight.com/kkbopen/how-can-i-float-an-infiniium-or-infiniivision-x-oscilloscope-isolating-it-from-mains-power-607258715.html) - Keysight does not recommend bypassing grounding and suggests differential probes.
