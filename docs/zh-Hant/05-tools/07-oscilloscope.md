# 示波器

示波器顯示信號如何隨時間變化。

萬用表可以顯示"約3.3V"或"有頻率"。示波器顯示信號形狀：脈衝、邊緣、下垂、噪聲、彈跳、UART數據包、PWM。

![Screen of a digital oscilloscope](../../img/05-tools/07-digital-oscilloscope.jpg)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Digital_oscilloscope.jpg), premek.v, Public Domain*

示波器螢幕上的 PWM 訊號如下所示：

![Animation of PWM: duty cycle change and signal waveform](../../img/05-tools/07-pwm-signal-waveform.gif)

*Source: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Pwm.gif), Mik81, CC0 Public Domain*

您不需要為每個簡單的構建都配備一個。但是，當設備運作不穩定時，示波器可以在幾分鐘內顯示萬用電表無法看到的內容。

## 你能看到什麼

在類似 iDryer 的設備中，示波器可用於檢視：

- fan PWM;
- MOSFET module PWM;
- UART `TX/RX`;
- 5V or 3.3V sag at servo startup;
- power supply noise;
- button bounce;
- tachometric fan signal;
- 萬用電錶平均消除的短暫故障。

示波器不僅可以回答“是否有電壓”，還可以回答“訊號隨時間變化的情況”。

## 最重要的警告

大多數桌上型示波器的探頭接地連接到電源保護接地。

這意味著：探頭的接地夾不僅僅是「另一根電線」。

如果將接地夾連接到低電壓電路的 `GND` 以外的點，則可以透過示波器建立短路。

用普通示波器進入市電110-230V交流部分、SSR、電源或高壓部分尤其危險。

你不能：

- 斷開示波器接地以進行“浮動”測量；
- 將探頭接地連接到相或另一個電壓點；
- 在不了解電路的情況下用普通探頭測量市電電壓；
- 假設兩個通道完全獨立：通道接地通常連接在一起。

對於浮動測量、高側測量和高壓測量，您需要正確的方法：差分探頭、隔離設備或其他安全方法。

## 如何連接探頭

對於低電壓電路：

1. 將探頭連接到示波器。
2. 將探頭接地連接到設備的 `GND`。
3. 將探頭尖端連接到訊號。
4. 選擇正確的探頭設定：`10x` 或 `10x`。
5. 確保示波器設定為相同的係數。

對於大多數數位訊號，請使用 `10x`：探頭對電路的負載較小，通常可以更好地顯示訊號形狀。

## PWM

PWM is a pulse signal.

示波器顯示：

- frequency;
- duty cycle;
- logic high level;
- logic low level;
- edges;
- jitter;
- noise.

對於風扇或 MOSFET，這有助於理解：

- 引腳是否輸出訊號；
- 3.3V或5V電平是否足夠；
- 頻率是否與設定相符；
- 佔空比是否根據命令改變；
- 連接負載時訊號是否不會下垂。

## UART

示波器上的 UART 看起來像是脈衝序列。

示波器有助於檢視：

- `TX` 上是否有活動；
- 邏輯電平是否不交換；
- 空閒等級是多少；
- 是否有強烈噪音；
- whether baud rate roughly matches.

對於文字解碼，邏輯分析儀或 USB-UART 轉接器更方便。但示波器可以快速顯示訊號是否有效。

## Power supply sag

萬用電表可能看不到短暫的電壓下降。

例如，當伺服系統啟動時，5V 線路可能會下降幾毫秒。萬用電表顯示5V幾乎正常，但控制器已經重新啟動。

An oscilloscope lets you see:

- 電壓下降多少；
- 下垂持續多久；
- 是否有尖峰；
- whether a capacitor helps;
- 情況是否因不同的電源或電線而改變。

這對於 ESP32、伺服系統、風扇和 DC-DC 特別有用。

## 噪音和乾擾

電源或訊號線上的雜訊可能會破壞感測器和通訊。

An oscilloscope helps see:

- DC-DC ripple;
- motor spikes;
- 加熱器附近的噪音；
- button bounce;
- 長電線上的干擾。

但要了解其限制：探頭接地不良可能會增加顯示器本身的雜訊。短探頭接地彈簧或短接地線通常比長夾子提供更真實的影像。

## 帶頻率測量功能的萬用電錶

有時初始檢查不需要示波器。

一些萬用電表可以測量訊號頻率。在規範中，這可能稱為 `frequency`、`frequency counter` 或 `frequency counter`。

如果您需要快速理解以下內容，這很有用：

- whether a PWM signal exists at all;
- 頻率是否隨調整而變化；
- 控制器輸出是否工作；
- 簡單數字線路上是否有活動。

例如，如果控制器要向風扇或MOSFET模組輸出PWM，則測頻萬用電表可以顯示訊號存在並且其頻率與預期值大致相符。

But a multimeter doesn't show signal shape. It won't show:

- logic high level;
- pulse width;
- PWM duty cycle;
- signal edges;
- brief dips;
- 噪音和乾擾；
- line distortion.

因此，測頻萬用電表是快速檢查的好工具，但不能完全取代示波器。

## 測量前要檢查什麼

連接探頭之前：

1. 電路中的`GND`是什麼？
2. 該點是否連接到電源保護接地？
3. 沒有市電電壓嗎？
4. 探頭的額定電壓是多少？
5. 如果需要的話是否選擇`10x`？
6. 探頭和頻道設定是否相同？
7. 通道地不連接不同的電路點嗎？
8. 可以先檢查一下低壓側的訊號嗎？

如果您對 110-230V AC 有疑問，請勿連接示波器。

## 常見錯誤

- 接地夾連接到電壓點，而不是 `GND`；
- 試圖將示波器接地與電源「斷開」；
- 使用無差動的普通探頭測量電源電壓；
- 忘記通道接地已連接；
- 探頭設定為 `1x`，示波器設定為 `1x`；
- 使用長探頭接地並看到額外的噪音；
- 僅用萬用電表查看並錯過了短暫的電壓下降；
- 當線路上沒有實體訊號時，認為 UART 問題是軟體問題。

## 重點

- An oscilloscope shows signal shape over time.
- 它對於 PWM、UART、功率驟降、噪音和短暫毛邊非常有用。
- 普通桌上型示波器接地連接到電源保護接地。
- 您不能將探頭接地連接到任意電路點。
- 對於乾線和浮動測量，需要特殊的安全方法。
- 測頻萬用電表很有用，但不能取代示波器。

## Reference materials

- [SparkFun: How to Use an Oscilloscope](https://learn.sparkfun.com/tutorials/how-to-use-an-oscilloscope/introduction) - basic practical introduction to oscilloscopes, signals and controls.
- [Tektronix: How to Use an Oscilloscope](https://www.tek.com.cn/documents/primer/how-to-use-an-oscilloscope) - grounding, setup, controls and basic oscilloscope use.
- [Tektronix: ABCs of Probes Primer](https://www.tek.com/en/documents/whitepaper/abcs-probes-primer) - warnings about probe ground, mains earth and danger of floating measurements with a normal oscilloscope.
- [Tektronix: Floating Oscilloscope Measurements and Operator Protection](https://www.tek.com/en/documents/technical-brief/floating-oscilloscope-measurements-and-operator-protection) - why disconnecting oscilloscope mains earth is dangerous and what safe alternatives exist.
- [Keysight: Floating an oscilloscope](https://docs.keysight.com/kkbopen/how-can-i-float-an-infiniium-or-infiniivision-x-oscilloscope-isolating-it-from-mains-power-607258715.html) - Keysight does not recommend bypassing grounding and suggests differential probes.
