# 连接风扇

风扇看起来像一个简单的组件：接上电源，它就会转。

实际问题通常来自四件事：

- 选择了错误电压的风扇；
- 把风扇接到承载能力不足的控制器输出；
- 不理解 2-pin、3-pin 和 4-pin 风扇之间的区别；
- 把风扇放在因过滤器、格栅或风道而压力不足的位置。

在类似 iDryer 的设备中，风扇通常用于空气循环、加热器冷却、腔体排风、过滤或电子元件冷却。

## 连接前要检查什么

连接前，先确认风扇参数：

- 电压：`5V`、`12V` 或 `24V`；
- 电流或功率；
- 连接器类型：2-pin、3-pin 或 4-pin；
- 是否支持 PWM 控制；
- 是否有测速信号；
- 风量；
- 静压；
- 噪声水平；
- 工作温度。

这些数据通常在标签、产品页面或技术 datasheet 中。

例如，风扇 datasheet 通常不仅包含电压和电流，还包含风量、静压、噪声 `SPL dB(A)`、工作温度和寿命。按这些参数选择，比只看尺寸可靠得多。

## 不要从 GPIO 给风扇供电

控制器的 GPIO 是控制信号，不是电源输出。

不要直接从 GPIO 给风扇供电。这可能损坏控制器，或在风扇启动时导致控制器复位。

正确逻辑是：

- 风扇从电源或板载电源输出获得供电；
- 控制器只负责开关或速度控制；
- 如果使用外部 MOSFET 模块，电源 `GND` 和控制器 `GND` 必须共地。

![N-channel MOSFET in switching mode (low-side) for load control](../../img/01-electronics-basics/02-nmos-switch-operation.png)

*来源：[Wikimedia Commons](https://commons.wikimedia.org/wiki/File:NMOS_PWR_WHOLE.PNG), KjellElec, CC BY-SA 4.0*

## 最简单的方案：2-pin 风扇

2-pin 风扇通常只有：

- `+` 电源；
- `-` 电源。

如果是 24V 风扇，就接到 24V。如果是 12V 风扇，就接到 12V。

简单开关控制可以使用：

- 板上的专用风扇输出，前提是它支持所需电压和电流；
- 用于 DC 负载的外部 MOSFET 模块；
- 独立风扇控制器。

如果风扇需要持续运行，可以通过保险丝或受保护的电源线直接接到合适电源。但在带加热器的设备中，通常最好让控制器把风扇作为安全逻辑的一部分来控制。

## 3-pin 风扇

3-pin 风扇通常有：

- 电源；
- 地；
- 测速信号。

测速信号允许监控风扇 RPM。它本身不控制速度。

3-pin 风扇通常通过降低供电电压或在电源线上做 PWM 来调速，前提是具体板子和风扇支持这种方式。但这种方法通常不如真正的 4-pin PWM：风扇可能啸叫、低速无法启动，或运行不稳定。

如果不需要调速，3-pin 风扇可以当普通 2-pin 使用：接电源和地，测速线不接。

## 4-pin PWM 风扇

4-pin PWM 风扇通常有：

- 地；
- 电源；
- 测速信号；
- PWM 控制信号。

关键区别是：风扇电源一直存在，速度由单独的 PWM 信号决定。

这是控制电脑 PWM 风扇的正确方式。不要以为 4-pin 风扇需要不断开关电源来控制。对于真正的 PWM 风扇，控制信号应接到单独的 PWM 引脚。

电脑 4-pin PWM 风扇的控制输入通常设计为开集电极/open-drain 信号，并带内部上拉，而不是接收任意 GPIO 电压。不要把 `12V` 或 `24V` 加到 PWM 引脚。查看风扇文档；如果需要 open-drain/open-collector，请使用合适的晶体管输出或 GPIO 模式。

许多 4-pin PWM 风扇的典型 PWM 频率约为 `25 kHz`。有些风扇能在附近范围工作，但频率太低或太高时，可能全速运行、停止或产生噪声。

如果 PWM 线没有连接，许多 4-pin 风扇会全速运行。

## 公共 GND / 公共负极

如果风扇由独立电源供电，而 PWM 信号来自控制器，就需要公共 `GND` / 公共负极。

没有公共 `GND` 时，控制器和风扇没有共同参考电平。结果是 PWM 可能不工作，或间歇工作。

简单规则：

- 风扇正极来自合适电源；
- 风扇负极接到电源负极；
- 控制器 `GND` 接到同一个负极；
- 控制信号只有在共地时才有效。

## 为任务选择风扇

风扇不仅看尺寸和电压。

重要参数：

- 风量；
- 静压；
- 噪声；
- 工作温度；
- 寿命；
- 轴承类型；
- 连接器；
- PWM/测速支持。

对于打印机腔体过滤器，普通安静机箱风扇可能太弱。它在自由空气中吹得很好，但很难推动空气穿过 HEPA 过滤器、活性炭层或狭窄通道。

经验规则：

- 对于空气混合和简单冷却，风量很重要；
- 对于过滤器、散热片和风道，静压很重要；
- 对于安静运行，不只看 `dB(A)`，还要看安装方式、格栅和振动；
- 对于加热腔体，要看风扇的工作温度。

## 启动电流和余量

风扇启动时，可能短时间消耗比正常运行更大的电流。

检查：

- 板载输出的最大电流；
- 单个风扇电流；
- 所有风扇总电流；
- 是否有启动余量；
- 长时间运行时端子、导线和 MOSFET 模块是否发热。

例如，如果一个风扇消耗 `0.25A`，四个这样的风扇总共约 `1A`，还没有计入启动电流。

## 示例：通过 MOSFET 模块连接

12V 或 24V 风扇的典型电路：

1. 电源正极接风扇正极。
2. 风扇负极接 MOSFET 模块的负载输出。
3. 电源负极接 MOSFET 模块。
4. 控制器 `GND` 接电源负极。
5. 控制器控制引脚接 MOSFET 模块输入。

这叫 low-side switching：MOSFET 断开负载的负极。

对于简单 2-pin 风扇，只要 MOSFET 模块满足电压和电流要求，这是标准且清晰的方案。对于带测速或独立 PWM 输入的 3-pin/4-pin 风扇，“切负极”不一定合适：RPM 监控和原生 PWM 控制通常需要持续的公共 `GND`。

## Klipper 配置示例

示例中的引脚名并不通用。复制前先检查你的板卡 pinout：错误的 `pin` 可能会激活错误输出。

如果风扇接到受控输出并需要手动控制：

```ini
[fan_generic chamber_fan]
pin: PA8
kick_start_time: 0.5
```

然后可以通过 G-code 控制：

```gcode
SET_FAN_SPEED FAN=chamber_fan SPEED=1.0
SET_FAN_SPEED FAN=chamber_fan SPEED=0.0
```

如果风扇需要根据腔体温度启动：

```ini
[temperature_fan chamber_exhaust]
pin: PA8
sensor_type: Generic 3950
sensor_pin: PA0
target_temp: 45.0
control: watermark
max_speed: 1.0
min_speed: 0.0
```

这里的引脚名只是典型示例。真实设备中必须检查板卡 pinout。

## 连接后要检查什么

长时间运行前，确认：

- 风扇旋转方向正确；
- 电压与风扇匹配；
- MOSFET 模块不过热；
- 端子不发热；
- 导线对所选电流来说不太细；
- 风扇能从完全停止状态启动；
- PWM 控制在整个范围内可用；
- 气流经过需要的区域，而不是从旁边绕过；
- 格栅、过滤器或外壳没有比预期更严重地阻塞气流。

如果风扇靠近加热器，请在真实腔体温度下测试。台架上工作正常的风扇，在热外壳中可能很快退化。

## 常见错误

- 把 12V 风扇接到 24V；
- 把 24V 风扇接到 12V，然后认为风扇坏了；
- 从 GPIO 给风扇供电；
- 忘记控制器和外部电源之间需要公共地；
- 期待 3-pin 风扇具备 PWM 控制；
- 用切断电源的方式控制 4-pin PWM 风扇，而不是使用 PWM 引脚；
- 没有计算多个风扇的总电流；
- 只按尺寸选风扇，不检查静压；
- 把安静风扇装在密集过滤器上，结果几乎没有气流；
- 安装后不检查气流方向；
- 导线没有固定，最终被叶轮或外壳磨损。

## 要点

- 风扇电压必须匹配电源。
- GPIO 不给风扇供电，只负责控制。
- 使用外部电源时，必须与控制器共地。
- 2-pin 风扇最容易通过电源输出或 MOSFET 控制。
- 3-pin 风扇有测速信号，但不一定有 PWM 控制。
- 4-pin PWM 最好用独立 PWM 信号控制，而不是开关电源。
- 对过滤器和风道来说，静压比漂亮的 `CFM` 数字更重要。
- 组装后不仅要检查旋转，还要检查气流是否真正穿过结构。

## 相关阅读

- [Noctua: PWM setup and RPM monitoring of a fan with microcontrollers](https://www.noctua.at/en/support/faqs/microcontroller-guide-pwm-setup-and-rpm-monitoring) - 4-pin PWM、RPM 信号、公共地和典型 PWM 频率的实用说明。
- [Klipper Configuration Reference: Fans](https://www.klipper3d.org/Config_Reference.html#fans) - 官方 `fan`、`heater_fan`、`controller_fan`、`temperature_fan` 和 `fan_generic` 配置。
- [Voron Documentation: Chamber Temperature & Exhaust Fan](https://docs.vorondesign.com/community/howto/alchemyEngine/chamber_temperature_exhaust_fan.html) - 在 Klipper 中按温度控制腔体排风风扇的示例。
- [DigiKey: Selecting A Fan](https://www.digikey.com/en/articles/selecting-a-fan) - 按风量、静压、外壳阻力和过滤器选择风扇。
- [SANYO DENKI: DC fan example datasheet](https://products.sanyodenki.com/en/sanace/dc/dc-fan/109P0405F601/) - 真实参数示例：电压、电流、风量、静压、噪声、工作温度和寿命。
