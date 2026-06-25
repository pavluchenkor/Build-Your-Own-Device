# 連接伺服馬達

伺服馬達是带齒輪箱和控制電子元件的小馬達。你可以告诉它把轴转到哪个位置。

在类似 iDryer 的設備中，伺服馬達可以打开風門、移動小锁扣、按下機械開關，或改变氣流方向。

伺服馬達的主要錯誤是：把它当成“小东西”，以为可以从控制器任意 5V 腳位供電。伺服馬達可能消耗很大電流，尤其是在啟動、突然動作或機構卡住时。

## 三條線

典型 hobby servo 有三條線：

- 電源：通常是 `5V` 或 `6V`；
- 地：`GND`；
- 訊號：来自控制器的控制脈衝。

常见顏色：

- 紅色 - 電源；
- 黑色或棕色 - 地；
- 黃色、橙色或白色 - 訊號。

但不能盲目信任顏色。不同廠商可能使用不同配色。連接前，请檢查標示、產品頁面或 datasheet。

## 電源分开，訊號分开

訊號线不给伺服馬達供電。它只告诉伺服馬達转到哪里。

伺服馬達从電源线取得能量。

正確邏輯是：

- 控制器只提供控制訊號；
- 伺服馬達由能承受其電流的 5V/6V 電源供電；
- 控制器地和伺服馬達電源地連接在一起。

![Servo wire color code](../../img/03-common-components/06-servo-color-code.jpg)

*來源：[SparkFun Electronics](https://learn.sparkfun.com/tutorials/hobby-servo-tutorial/all), CC BY-SA 4.0*

## 為什麼不能从弱 5V 供電

許多板子都有 5V 腳位。这不表示可以安全地从它给伺服馬達供電。

伺服馬達運動时消耗的電流可能远大于它的尺寸暗示。如果電源不足，常见症狀包括：

- 控制器重置；
- 螢幕閃爍；
- USB 連接斷開；
- 伺服馬達抽動；
- ESP32 的 Wi-Fi 斷線；
- 伺服馬達嗡嗡响但不移動；
- 動作開始时電源下陷。

一个小伺服馬達有时可以由板載電源供電，前提是板子和電源明確支持该電流。但在带風門、锁扣或機構的真實設備中，最好使用带餘量的獨立 5V/6V DC-DC 或電源。

## 共地

如果伺服馬達由獨立電源供電，就需要共地。

没有共地时，控制器和伺服馬達没有共同訊號參考電平。伺服馬達可能不回應、抽動或隨機動作。

簡單連接：

1. 電源的 `+5V` 或 `+6V` 接伺服馬達電源。
2. 電源的 `GND` 接伺服馬達地。
3. 控制器 `GND` 接到同一个地。
4. 控制器 PWM/GPIO 腳位接伺服馬達訊號线。

伺服馬達電源和控制器電源可以不同，但地必須共用。

## 需要什么訊號

典型位置伺服馬達由脈衝控制。

典型訊號：

- 大约每 `20 ms` 一个脈衝；
- 约 `1 ms` - 行程一端；
- 约 `1.5 ms` - 中間；
- 约 `2 ms` - 行程另一端。

这不是用于 LED 亮度或风扇速度的普通 PWM。这里重要的是微秒级脈衝寬度。

具体伺服馬達的實際極限可能不同。有些伺服馬達安全範圍不是 0 到 180 度，而更小。因此極限位置需要謹慎測試。

## 不要让伺服馬達頂住機構

伺服馬達会嘗試保持命令位置。

如果風門碰到外殼、連桿卡住，或機構在命令结束前到达物理限位，伺服馬達会繼續推。此时電流升高，馬達發熱，齒輪箱磨損。

这对風門和锁扣尤其重要。

長期運行前確認：

- 機構在整個範圍内能自由移動；
- 没有錯位；
- 連桿不卡住；
- 伺服馬達在終點位置不嗡嗡响；
- 韌體中的極限角度不会把機構顶到限位；
- 斷電时設備仍安全，或按設計由彈簧復位。

如果伺服馬達靜止时嗡嗡响，通常表示有負載、顶到限位或槓桿几何錯誤。

## 啟動電流和堵转電流

伺服馬達有正常運行電流，也有轴被卡住时的電流。后者通常叫 stall current。

当伺服馬達嘗試運動但轴被卡住，或機構太重时，会出现堵转電流。

这种模式常导致：

- 電源下陷；
- 控制器重置；
- 導線發熱；
- DC-DC 过热；
- 齒輪箱損壞。

如果 datasheet 列出 stall current，选择電源时要按该值和安全餘量計算。如果没有 datasheet，就不能凭感觉认为伺服馬達安全。

## 伺服馬達旁的電容

有时在伺服馬達旁边的 `+5V` 和 `GND` 之间加一个電解電容会有帮助。

它不能取代合適電源，但可以緩和動作開始时的短暫下陷。

对于小伺服馬達：几百微法，例如 `470 uF` 或更大，耐壓高于供電电压。

電解電容有極性：

- 電容正极接 `+5V`；
- 電容负极接 `GND`。

如果設備需要可靠，先选择正確電源和接线，再把電容作为額外措施。

## Klipper 設定範例

在 Klipper 中，伺服馬達用 `[servo]` 段描述。

範例：

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

这里的腳位名只是典型範例。真實設備中，请檢查板卡 pinout。

对于機械部分，不要一開始就用 `0` 和 `180`。先測試安全範圍，例如 `60`、`90`、`120`，然后再擴大角度。

## Arduino/ESP32 邏輯範例

Arduino 方式通常使用 Servo 函式庫：

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

这只是訊號邏輯範例。伺服馬達電源仍需要單獨設計。即使訊號线連接到 Arduino 或 ESP32，伺服馬達馬達也不能让控制器電源過載。

## 連接后要檢查什么

安裝到外殼前：

- 伺服馬達取得正確电压；
- 電源能承受伺服馬達電流；
- 控制器地和伺服馬達地共用；
- 訊號线接到正確腳位；
- 伺服馬達運動方向正確；
- 極限角度不会損壞機構；
- 機構不卡住；
- 伺服馬達不持續嗡嗡响；
- 導線不会被搖臂或齒輪挂住；
- 動作后電源不下陷；
- 控制器不重置。

在無負載和真實負載下測試機械結構。手动移動很轻松的風門，装进外殼后可能会卡住。

## 常見錯誤

- 从 GPIO 给伺服馬達供電；
- 从板子弱 5V 腳位给伺服馬達供電；
- 忘記共地；
- 不檢查就相信線色；
- 電源接反；
- 使用過細導線；
- 没有計算啟動和堵转電流；
- 強迫伺服馬達推機械限位；
- 真實機構只在較小範圍安全，却使用角度 `0` 或 `180`；
- 把伺服馬達装在熱源附近却不檢查工作溫度；
- 把連續旋轉伺服馬達当普通位置伺服馬達使用。

## 要點

- 伺服馬達有三條線：電源、地、訊號。
- 訊號不给伺服馬達供電。
- 真實設備通常需要獨立 5V/6V 電源。
- 伺服馬達地和控制器地必須共用。
- 最危险的負載是卡死或機械卡住。
- 極限角度需要謹慎选择，不能直接用 `0` 和 `180`。
- 如果伺服馬達動作时控制器重置，先檢查電源和共地。

## 相關閱讀

- [Klipper Configuration Reference: Servo](https://www.klipper3d.org/Config_Reference.html#servo) - 官方 `[servo]` 段、`SET_SERVO`、角度和脈衝寬度。
- [SparkFun: Hobby Servo Tutorial](https://learn.sparkfun.com/tutorials/hobby-servo-tutorial/introduction) - hobby servo、三條線和脈衝控制的基本說明。
- [SparkFun: Servo Trigger Hookup Guide](https://learn.sparkfun.com/tutorials/servo-trigger-hookup-guide/servo-motor-background) - 电气連接、常见線色和 hobby servo 機械結構說明。
- [Adafruit: Arduino Lesson 14. Servo Motors](https://learn.adafruit.com/adafruit-arduino-lesson-14-servo-motors?view=all) - 連接、電源下陷行为和伺服馬達旁電容的实用範例。
- [Arduino Servo Library Reference](https://www.arduino.cc/reference/en/libraries/servo/) - Arduino 方式的官方 Servo 函式庫。
