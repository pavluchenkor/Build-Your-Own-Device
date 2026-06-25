# 检查热敏电阻

热敏电阻是一种温度传感器，加热或冷却时电阻会变化。

在 3D 打印机、干燥机和腔体加热器中，最常见的是额定 `100K` 的 NTC 热敏电阻。NTC 表示温度升高时电阻降低。

出现以下情况时需要检查热敏电阻：

- 温度读数不现实；
- 温度读数跳动；
- 加热器进入错误状态；
- 固件报告 `MINTEMP`、`MAXTEMP`、`Thermal runaway` 或类似错误；
- 热敏电阻被更换、移动或重新压接；
- 设备是第一次组装。

## 首先关闭电源

电阻只能在断电电路上测量。

检查前：

1. 关闭设备。
2. 从市电或电源断开供电。
3. 等待加热器冷却。
4. 如果需要测量传感器本身，请把热敏电阻从板上拔下。

如果热敏电阻仍连接在板上，测得的电阻可能会被其他电路元件影响。如果带电测量电阻，可能损坏万用表或板子。

## NTC 100K 应该是什么样

典型 NTC `100K` 在 `25°C` 时电阻约为 `100 kOhm`。

这并不表示万用表一定会精确显示 `100.0 kOhm`。

室温下读数略有差异是正常的：

- 房间较冷时电阻更高；
- 房间较热时电阻更低；
- 不同热敏电阻类型有不同表格；
- 长导线和接触不良会影响测量。

核心检查很简单：室温下 100K NTC 应显示几十千欧到约一百千欧，而不是 `0 Ohm` 或 `OL`。

## 用万用表测量

把万用表设为电阻模式 `Ohm`。

如果万用表不是自动量程，请选择高于 `100 kOhm` 的档位，例如 `200 kOhm` 或 `2 MOhm`。

然后：

1. 从板上断开热敏电阻。
2. 用万用表表笔接触热敏电阻的两根线。
3. 不要同时握住表笔和导线的金属端：人体会增加并联电阻。
4. 等待读数稳定。
5. 记录数值。

![Digital multimeter for measuring thermistor resistance](../../img/05-tools/02-digital-multimeter.jpg)

*来源：[Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Aneng_AN870_multimeter_02.jpg), Retired electrician, CC0 Public Domain*

## 用手指快速加热测试

在室温测量后，可以小心地用手指加热传感器。

对于 NTC 热敏电阻，电阻应该开始下降。

例如：

- 室温时约为 `100 kOhm`；
- 手指加热后变低。

这里精确数字不重要，变化方向才重要。

如果电阻完全不变、随机跳动，或移动导线时读数消失，问题可能在传感器、导线、压接或连接器。

## 断路和短路

万用表能快速区分正常传感器和明显故障。

典型迹象：

- `OL`、`over limit`、显示屏左侧 `1` 或无限电阻 - 断路；
- 接近 `0 Ohm` - 短路；
- 移动导线时数值大幅跳变 - 接触不良或导体断裂；
- 室温约 `100 kOhm`，加热后下降 - 看起来像健康的 NTC 100K。

不同万用表对断路有不同显示。通常是 `OL` 或超出所选量程。

## 检查接线

热敏电阻本身可能正常，问题在接线。

检查：

- 连接器是否完全插入；
- 引脚是否从连接器外壳中退出；
- 导线是否磨损；
- 加热器附近绝缘是否损坏；
- 轴或盖板移动时导线是否受拉；
- 电缆是否无理由紧贴加热器电源线；
- 压接位置是否牢固。

如果移动导线时读数变化，这不是“传感器特性”。这是接触问题，必须在开启加热器前修复。

## 在 Klipper 中检查

在 Klipper 中，传感器类型在配置中设置。

典型腔体温度传感器示例：

```ini
[temperature_sensor chamber]
sensor_type: Generic 3950
sensor_pin: PA0
min_temp: 0
max_temp: 100
```

腔体加热器示例：

```ini
[heater_generic chamber_heater]
gcode_id: C
heater_pin: PA8
sensor_type: Generic 3950
sensor_pin: PA0
control: watermark
min_temp: 0
max_temp: 90
```

这里的引脚名只是典型示例。真实设备中请检查板卡 pinout。

重要：`sensor_type` 必须与真实传感器匹配。两个热敏电阻外观看起来可能相同，但表格不同。如果选错类型，温度会明显不准，尤其是在实际加热工作范围内。

## 在界面中观察什么

连接后，在 Klipper 界面、Mainsail、Fluidd 或其他 UI 中检查温度。

室温下，读数应接近真实室温。

可疑迹象：

- 明显低于实际温度；
- 明显高于实际温度；
- 温度跳动几十度；
- 移动导线时温度变化；
- 加热开启时温度不上升；
- 温度上升很慢；
- 加热器关闭时温度仍上升。

如果传感器安装在加热器上，读数看起来合理之前，不要进行长时间加热。

## 固件错误

在 3D 打印机固件中，温度错误不是小问题，而是安全的一部分。

对于带 NTC 和板载上拉的典型电路：

- 传感器断路通常表现为温度过低或 `MINTEMP`；
- 短路通常表现为温度过高或 `MAXTEMP`；
- 热接触不良可能导致 `Heating failed` 或 `Thermal runaway`；
- 加热块被强烈冷却时，温度上升太慢或无法保持，也可能报错。

错误名称取决于固件，但含义相同：控制器不再信任温度，或发现加热没有按预期工作。

不要为了“检查”而关闭热保护。如果保护触发，先从传感器、接线、固定、加热器、PID 设置和冷却中查找原因。

## 热接触

电气上正常的热敏电阻并不保证温度正确。

传感器必须能很好地从被测部件传热。

检查：

- 传感器是否完全坐入套管或孔中；
- 是否有正常夹紧；
- 传感器和表面之间是否没有间隙；
- 如果使用导热膏，是否没有干裂或脱落；
- 紧固件是否没有松动；
- 传感器是否没有从座位中脱出；
- 导线是否没有把传感器拉出来。

接触不良很危险，因为传感器读到的温度低于真实温度。控制器继续加热，而真实部件可能已经过热。

## 小检查表

第一次加热前：

- 热敏电阻电阻看起来符合预期；
- NTC 电阻用手指加热时下降；
- 没有断路或短路；
- 移动导线时读数不跳；
- 连接器插入正确；
- 固件中选择了正确的 `sensor_type`；
- 界面温度看起来像室温；
- 传感器牢固安装在正确位置；
- `min_temp` 和 `max_temp` 对设备来说设置合理。

## 常见错误

- 板子带电时测量电阻；
- 不从板上断开传感器，结果得到奇怪数值；
- 把 `100K` 热敏电阻和另一种传感器类型混淆；
- 选择错误的 `sensor_type`；
- 看到 `OL` 就以为是“100K”；
- 假设所有 100K NTC 都相同；
- 把热敏电阻松散地留在加热器旁；
- 用螺丝过度拧紧玻璃热敏电阻；
- 导线受拉导致传感器从套管中出来；
- 关闭热保护，而不是修复错误原因。

## 要点

- 电阻只能在断电电路上测量。
- 典型 NTC 100K 在 `25°C` 约为 `100 kOhm`。
- 加热时，NTC 电阻下降。
- `OL` 通常表示断路，接近 `0 Ohm` 表示短路。
- 固件必须选择正确传感器类型。
- 良好热接触和正常接线一样重要。
- 如果温度读数看起来错误，不要启动加热器。

## 相关阅读

- [Klipper Configuration Reference: Temperature sensors](https://www.klipper3d.org/Config_Reference.html#temperature-sensors) - 官方 `sensor_type`、`sensor_pin`、`pullup_resistor` 参数和常见热敏电阻列表。
- [Marlin Configuration: Temperature Ranges and Thermal Protection](https://marlinfw.org/docs/configuration/configuration.html#temperature-ranges) - `MINTEMP`、`MAXTEMP` 和 thermal runaway 保护说明。
- [Marlin Troubleshooting: Heating Failed](https://marlinfw.org/docs/basics/troubleshooting.html#heating-failed) - 常见加热错误原因：热敏电阻、温度上升慢、thermal runaway。
- [RepRap Wiki: Thermistor](https://reprap.org/wiki/Thermistor) - NTC/PTC 热敏电阻和室温电阻检查的基本说明。
- [Fluke: How to Measure Resistance with a Digital Multimeter](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-resistance) - 使用数字万用表安全测量电阻的步骤。
