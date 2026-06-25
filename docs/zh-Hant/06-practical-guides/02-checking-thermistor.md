# 檢查熱敏電阻

熱敏電阻是一种溫度感測器，加熱或冷卻时電阻会變化。

在 3D 打印机、乾燥機和艙體加熱器中，最常見的是额定 `100K` 的 NTC 熱敏電阻。NTC 表示溫度升高时電阻降低。

出现以下情况时需要檢查熱敏電阻：

- 溫度讀數不现实；
- 溫度讀數跳动；
- 加熱器进入錯誤状态；
- 韌體報告 `MINTEMP`、`MAXTEMP`、`Thermal runaway` 或類似錯誤；
- 熱敏電阻被更換、移動或重新壓接；
- 設備是第一次組裝。

## 首先關閉電源

電阻只能在斷電電路上測量。

檢查前：

1. 關閉設備。
2. 从市電或電源断开供电。
3. 等待加熱器冷卻。
4. 如果需要測量感測器本身，请把熱敏電阻从板上拔下。

如果熱敏電阻仍连接在板上，测得的電阻可能会被其他電路元件影響。如果带电測量電阻，可能損壞萬用表或板子。

## NTC 100K 应该是什么样

典型 NTC `100K` 在 `25°C` 时電阻约为 `100 kOhm`。

这并不表示萬用表一定会精确顯示 `100.0 kOhm`。

室温下讀數略有差异是正常的：

- 房間較冷时電阻更高；
- 房間較热时電阻更低；
- 不同熱敏電阻类型有不同表格；
- 长導線和接觸不良会影響測量。

核心檢查很簡單：室温下 100K NTC 应顯示幾十千欧到约一百千欧，而不是 `0 Ohm` 或 `OL`。

## 用萬用表測量

把萬用表设为電阻模式 `Ohm`。

如果萬用表不是自动量程，请選擇高于 `100 kOhm` 的檔位，例如 `200 kOhm` 或 `2 MOhm`。

然后：

1. 从板上断开熱敏電阻。
2. 用萬用表錶筆接觸熱敏電阻的两根线。
3. 不要同时握住錶筆和導線的金屬端：人体会增加並聯電阻。
4. 等待讀數稳定。
5. 記錄數值。

![Digital multimeter for measuring thermistor resistance](../../img/05-tools/02-digital-multimeter.jpg)

*來源：[Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Aneng_AN870_multimeter_02.jpg), Retired electrician, CC0 Public Domain*

## 用手指快速加熱测试

在室温測量后，可以小心地用手指加熱感測器。

对于 NTC 熱敏電阻，電阻应该开始下降。

例如：

- 室温时约为 `100 kOhm`；
- 手指加熱后变低。

这里精确数字不重要，變化方向才重要。

如果電阻完全不变、隨機跳动，或移動導線时讀數消失，问题可能在感測器、導線、壓接或連接器。

## 斷路和短路

萬用表能快速区分正常感測器和明顯故障。

典型跡象：

- `OL`、`over limit`、顯示器左侧 `1` 或無限電阻 - 斷路；
- 接近 `0 Ohm` - 短路；
- 移動導線时數值大幅跳变 - 接觸不良或导体断裂；
- 室温约 `100 kOhm`，加熱后下降 - 看起来像健康的 NTC 100K。

不同萬用表对斷路有不同顯示。通常是 `OL` 或超出所选量程。

## 檢查接線

熱敏電阻本身可能正常，问题在接線。

檢查：

- 連接器是否完全插入；
- 腳位是否从連接器外殼中退出；
- 導線是否磨損；
- 加熱器附近絕緣是否損壞；
- 轴或蓋板移動时導線是否受拉；
- 電纜是否无理由紧贴加熱器電源線；
- 壓接位置是否牢固。

如果移動導線时讀數變化，这不是“感測器特性”。这是接觸问题，必须在開啟加熱器前修復。

## 在 Klipper 中檢查

在 Klipper 中，感測器类型在設定中设置。

典型艙體溫度感測器範例：

```ini
[temperature_sensor chamber]
sensor_type: Generic 3950
sensor_pin: PA0
min_temp: 0
max_temp: 100
```

艙體加熱器範例：

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

这里的腳位名只是典型範例。真實設備中请檢查板卡 pinout。

重要：`sensor_type` 必须与真實感測器匹配。两个熱敏電阻外观看起来可能相同，但表格不同。如果选错类型，溫度会明顯不准，尤其是在實際加熱工作範圍内。

## 在介面中觀察什么

连接后，在 Klipper 介面、Mainsail、Fluidd 或其他 UI 中檢查溫度。

室温下，讀數应接近真實室温。

可疑跡象：

- 明顯低于實際溫度；
- 明顯高于實際溫度；
- 溫度跳动幾十度；
- 移動導線时溫度變化；
- 加熱開啟时溫度不上升；
- 溫度上升很慢；
- 加熱器關閉时溫度仍上升。

如果感測器安装在加熱器上，讀數看起来合理之前，不要进行長時間加熱。

## 韌體錯誤

在 3D 打印机韌體中，溫度錯誤不是小问题，而是安全的一部分。

对于带 NTC 和板载上拉的典型電路：

- 感測器斷路通常表现为溫度过低或 `MINTEMP`；
- 短路通常表现为溫度过高或 `MAXTEMP`；
- 热接觸不良可能导致 `Heating failed` 或 `Thermal runaway`；
- 加熱块被强烈冷卻时，溫度上升太慢或无法保持，也可能报错。

錯誤名称取决于韌體，但含义相同：控制器不再信任溫度，或发现加熱没有按預期工作。

不要为了“檢查”而關閉热保護。如果保護触发，先从感測器、接線、固定、加熱器、PID 设置和冷卻中查找原因。

## 热接觸

電氣上正常的熱敏電阻并不保證溫度正確。

感測器必须能很好地从被测部件传热。

檢查：

- 感測器是否完全坐入套管或孔中；
- 是否有正常夹紧；
- 感測器和表面之间是否没有間隙；
- 如果使用導熱膏，是否没有干裂或脫落；
- 緊韌體是否没有鬆動；
- 感測器是否没有从座位中脱出；
- 導線是否没有把感測器拉出来。

接觸不良很危险，因为感測器读到的溫度低于真實溫度。控制器繼續加熱，而真實部件可能已經過熱。

## 小檢查表

第一次加熱前：

- 熱敏電阻電阻看起来符合預期；
- NTC 電阻用手指加熱时下降；
- 没有斷路或短路；
- 移動導線时讀數不跳；
- 連接器插入正確；
- 韌體中選擇了正確的 `sensor_type`；
- 介面溫度看起来像室温；
- 感測器牢固安装在正確位置；
- `min_temp` 和 `max_temp` 对設備来说设置合理。

## 常見錯誤

- 板子带电时測量電阻；
- 不从板上断开感測器，结果得到奇怪數值；
- 把 `100K` 熱敏電阻和另一种感測器类型混淆；
- 選擇錯誤的 `sensor_type`；
- 看到 `OL` 就以为是“100K”；
- 假設所有 100K NTC 都相同；
- 把熱敏電阻鬆散地留在加熱器旁；
- 用螺絲过度拧紧玻璃熱敏電阻；
- 導線受拉导致感測器从套管中出来；
- 關閉热保護，而不是修復錯誤原因。

## 要點

- 電阻只能在斷電電路上測量。
- 典型 NTC 100K 在 `25°C` 约为 `100 kOhm`。
- 加熱时，NTC 電阻下降。
- `OL` 通常表示斷路，接近 `0 Ohm` 表示短路。
- 韌體必须選擇正確感測器类型。
- 良好热接觸和正常接線一样重要。
- 如果溫度讀數看起来錯誤，不要启动加熱器。

## 相關閱讀

- [Klipper Configuration Reference: Temperature sensors](https://www.klipper3d.org/Config_Reference.html#temperature-sensors) - 官方 `sensor_type`、`sensor_pin`、`pullup_resistor` 参数和常見熱敏電阻清單。
- [Marlin Configuration: Temperature Ranges and Thermal Protection](https://marlinfw.org/docs/configuration/configuration.html#temperature-ranges) - `MINTEMP`、`MAXTEMP` 和 thermal runaway 保護說明。
- [Marlin Troubleshooting: Heating Failed](https://marlinfw.org/docs/basics/troubleshooting.html#heating-failed) - 常見加熱錯誤原因：熱敏電阻、溫度上升慢、thermal runaway。
- [RepRap Wiki: Thermistor](https://reprap.org/wiki/Thermistor) - NTC/PTC 熱敏電阻和室温電阻檢查的基本說明。
- [Fluke: How to Measure Resistance with a Digital Multimeter](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-resistance) - 使用数字萬用表安全測量電阻的步驟。
