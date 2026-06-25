# 连接舵机

舵机是带齿轮箱和控制电子元件的小电机。你可以告诉它把轴转到哪个位置。

在类似 iDryer 的设备中，舵机可以打开风门、移动小锁扣、按下机械开关，或改变气流方向。

舵机的主要错误是：把它当成“小东西”，以为可以从控制器任意 5V 引脚供电。舵机可能消耗很大电流，尤其是在启动、突然动作或机构卡住时。

## 三根线

典型 hobby servo 有三根线：

- 电源：通常是 `5V` 或 `6V`；
- 地：`GND`；
- 信号：来自控制器的控制脉冲。

常见颜色：

- 红色 - 电源；
- 黑色或棕色 - 地；
- 黄色、橙色或白色 - 信号。

但不能盲目信任颜色。不同厂商可能使用不同配色。连接前，请检查标识、产品页面或 datasheet。

## 电源分开，信号分开

信号线不给舵机供电。它只告诉舵机转到哪里。

舵机从电源线获取能量。

正确逻辑是：

- 控制器只提供控制信号；
- 舵机由能承受其电流的 5V/6V 电源供电；
- 控制器地和舵机电源地连接在一起。

![Servo wire color code](../../img/03-common-components/06-servo-color-code.jpg)

*来源：[SparkFun Electronics](https://learn.sparkfun.com/tutorials/hobby-servo-tutorial/all), CC BY-SA 4.0*

## 为什么不能从弱 5V 供电

许多板子都有 5V 引脚。这不表示可以安全地从它给舵机供电。

舵机运动时消耗的电流可能远大于它的尺寸暗示。如果电源不足，常见症状包括：

- 控制器重启；
- 屏幕闪烁；
- USB 连接断开；
- 舵机抽动；
- ESP32 的 Wi-Fi 掉线；
- 舵机嗡嗡响但不移动；
- 动作开始时电源下陷。

一个小舵机有时可以由板载电源供电，前提是板子和电源明确支持该电流。但在带风门、锁扣或机构的真实设备中，最好使用带余量的独立 5V/6V DC-DC 或电源。

## 公共地

如果舵机由独立电源供电，就需要公共地。

没有公共地时，控制器和舵机没有共同信号参考电平。舵机可能不响应、抽动或随机动作。

简单连接：

1. 电源的 `+5V` 或 `+6V` 接舵机电源。
2. 电源的 `GND` 接舵机地。
3. 控制器 `GND` 接到同一个地。
4. 控制器 PWM/GPIO 引脚接舵机信号线。

舵机电源和控制器电源可以不同，但地必须共用。

## 需要什么信号

典型位置舵机由脉冲控制。

典型信号：

- 大约每 `20 ms` 一个脉冲；
- 约 `1 ms` - 行程一端；
- 约 `1.5 ms` - 中间；
- 约 `2 ms` - 行程另一端。

这不是用于 LED 亮度或风扇速度的普通 PWM。这里重要的是微秒级脉冲宽度。

具体舵机的实际极限可能不同。有些舵机安全范围不是 0 到 180 度，而更小。因此极限位置需要谨慎测试。

## 不要让舵机顶住机构

舵机会尝试保持命令位置。

如果风门碰到外壳、连杆卡住，或机构在命令结束前到达物理限位，舵机会继续推。此时电流升高，电机发热，齿轮箱磨损。

这对风门和锁扣尤其重要。

长期运行前确认：

- 机构在整个范围内能自由移动；
- 没有错位；
- 连杆不卡住；
- 舵机在终点位置不嗡嗡响；
- 固件中的极限角度不会把机构顶到限位；
- 断电时设备仍安全，或按设计由弹簧复位。

如果舵机静止时嗡嗡响，通常表示有负载、顶到限位或杠杆几何错误。

## 启动电流和堵转电流

舵机有正常运行电流，也有轴被卡住时的电流。后者通常叫 stall current。

当舵机尝试运动但轴被卡住，或机构太重时，会出现堵转电流。

这种模式常导致：

- 电源下陷；
- 控制器重启；
- 导线发热；
- DC-DC 过热；
- 齿轮箱损坏。

如果 datasheet 列出 stall current，选择电源时要按该值和安全余量计算。如果没有 datasheet，就不能凭感觉认为舵机安全。

## 舵机旁的电容

有时在舵机旁边的 `+5V` 和 `GND` 之间加一个电解电容会有帮助。

它不能替代合适电源，但可以缓和动作开始时的短暂下陷。

对于小舵机：几百微法，例如 `470 uF` 或更大，耐压高于供电电压。

电解电容有极性：

- 电容正极接 `+5V`；
- 电容负极接 `GND`。

如果设备需要可靠，先选择正确电源和接线，再把电容作为额外措施。

## Klipper 配置示例

在 Klipper 中，舵机用 `[servo]` 段描述。

示例：

```ini
[servo chamber_damper]
pin: PA8
maximum_servo_angle: 180
minimum_pulse_width: 0.001
maximum_pulse_width: 0.002
initial_angle: 90
```

命令：

```gcode
SET_SERVO SERVO=chamber_damper ANGLE=0
SET_SERVO SERVO=chamber_damper ANGLE=90
SET_SERVO SERVO=chamber_damper ANGLE=180
```

这里的引脚名只是典型示例。真实设备中，请检查板卡 pinout。

对于机械部分，不要一开始就用 `0` 和 `180`。先测试安全范围，例如 `60`、`90`、`120`，然后再扩大角度。

## Arduino/ESP32 逻辑示例

Arduino 方式通常使用 Servo 库：

```cpp
#include <Servo.h>

Servo damper;

void setup() {
  damper.attach(9);
  damper.write(90);
}

void loop() {
}
```

这只是信号逻辑示例。舵机电源仍需要单独设计。即使信号线连接到 Arduino 或 ESP32，舵机电机也不能让控制器电源过载。

## 连接后要检查什么

安装到外壳前：

- 舵机获得正确电压；
- 电源能承受舵机电流；
- 控制器地和舵机地共用；
- 信号线接到正确引脚；
- 舵机运动方向正确；
- 极限角度不会损坏机构；
- 机构不卡住；
- 舵机不持续嗡嗡响；
- 导线不会被摇臂或齿轮挂住；
- 动作后电源不下陷；
- 控制器不重启。

在无负载和真实负载下测试机械结构。手动移动很轻松的风门，装进外壳后可能会卡住。

## 常见错误

- 从 GPIO 给舵机供电；
- 从板子弱 5V 引脚给舵机供电；
- 忘记公共地；
- 不检查就相信线色；
- 电源接反；
- 使用过细导线；
- 没有计算启动和堵转电流；
- 强迫舵机推机械限位；
- 真实机构只在较小范围安全，却使用角度 `0` 或 `180`；
- 把舵机装在热源附近却不检查工作温度；
- 把连续旋转舵机当普通位置舵机使用。

## 要点

- 舵机有三根线：电源、地、信号。
- 信号不给舵机供电。
- 真实设备通常需要独立 5V/6V 电源。
- 舵机地和控制器地必须共用。
- 最危险的负载是卡死或机械卡住。
- 极限角度需要谨慎选择，不能直接用 `0` 和 `180`。
- 如果舵机动作时控制器重启，先检查电源和公共地。

## 相关阅读

- [Klipper Configuration Reference: Servo](https://www.klipper3d.org/Config_Reference.html#servo) - 官方 `[servo]` 段、`SET_SERVO`、角度和脉冲宽度。
- [SparkFun: Hobby Servo Tutorial](https://learn.sparkfun.com/tutorials/hobby-servo-tutorial/introduction) - hobby servo、三根线和脉冲控制的基本说明。
- [SparkFun: Servo Trigger Hookup Guide](https://learn.sparkfun.com/tutorials/servo-trigger-hookup-guide/servo-motor-background) - 电气连接、常见线色和 hobby servo 机械结构说明。
- [Adafruit: Arduino Lesson 14. Servo Motors](https://learn.adafruit.com/adafruit-arduino-lesson-14-servo-motors?view=all) - 连接、电源下陷行为和舵机旁电容的实用示例。
- [Arduino Servo Library Reference](https://www.arduino.cc/reference/en/libraries/servo/) - Arduino 方式的官方 Servo 库。
