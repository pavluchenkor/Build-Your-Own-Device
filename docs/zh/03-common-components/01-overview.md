# 常用组件

常用组件是你在组装 iDryer 等设备或 3D 打印机外围设备时最常遇到的零件和模块。

本部分的目的：

本部分作为你在组装过程中会实际拿到的零件的参考。

你不需要深厚的电子知识。主要目标是帮助你理解：

- 这个组件是什么；
- 为什么你需要它；
- 它通常如何连接；
- 你可以用什么来替代它；
- 购买时哪些参数重要；
- 第一次连接时最常出故障的地方。

每页的格式：

- 它是什么；
- 它在 iDryer 和 3D 打印机外围设备中的用途；
- 典型的连接方式；
- 重要特性；
- 典型错误；
- 购买前的简短清单。

建议的文件：

- `02-heaters.md` - 加热器：PTC、硅胶垫、热筒、12V/24V/110-230V AC。
- `03-fans.md` - 风扇：2 针、3 针、4 针 PWM、电压、电流、噪声、气流。
- `04-thermistors.md` - 热敏电阻：NTC 100K、查找表、安装、开路/短路。
- `05-led-strips.md` - LED 灯带：5V/12V/24V、普通和可寻址、每米电流。
- `06-servo-motors.md` - 伺服电机：电源、信号、角度、峰值电流。
- `07-load-cells.md` - 应变片：HX711、标定、机械安装。
- `08-oled-display.md` - OLED：I2C/SPI、地址、电源、何时需要。
- `09-touchscreen.md` - TFT/触摸屏：UART/SPI/HDMI、电源、兼容性。
- `10-rfid-and-nfc.md` - RFID/NFC：卡、标签、频率、连接。

## 参考资料

- [Klipper Configuration Reference](https://www.klipper3d.org/Config_Reference.html) - 官方 Klipper 关于加热器、风扇、温度传感器、伺服电机和显示器的配置部分。
- [DigiKey: Selecting A Fan](https://www.digikey.com/en/articles/selecting-a-fan) - 根据气流、静压、机箱阻力和热任务的实用风扇选择。
- [Adafruit: MOSFET Driver](https://learn.adafruit.com/adafruit-mosfet-driver) - 为什么大功率负载不能直接连接到 GPIO，以及为什么你需要电源开关。
- [SparkFun: Load Cell Amplifier HX711 Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide) - 应变片、HX711、电源、信号线和标定的示例。
- [Adafruit: PN532 RFID/NFC Breakout Wiring](https://learn.adafruit.com/adafruit-pn532-rfid-nfc/breakout-wiring) - 一个组件的示例，你需要提前检查电源、逻辑电平和所选接口。

## 另见

- [加热器](02-heaters.md) - 最危险的负载类型：电源、温度、SSR/MOSFET 和独立保护。
- [风扇](03-fans.md) - 气流、静压、2 针/3 针/4 针和电源。
- [热敏电阻](04-thermistors.md) - 作为加热器反馈基础的温度传感器。
- [连接风扇](../06-practical-guides/01-connecting-fan.md) - 通过电源开关的组件连接的实用示例。
- 加热器和 SSR 错误 - 大功率和市电负载的常见错误。
