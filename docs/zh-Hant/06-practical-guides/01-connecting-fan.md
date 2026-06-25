# 連接風扇

風扇看起來像一个簡單的組件：接上電源，它就会转。

實際问题通常来自四件事：

- 選擇了錯誤電壓的風扇；
- 把風扇接到承载能力不足的控制器輸出；
- 不理解 2-pin、3-pin 和 4-pin 風扇之間的差異；
- 把風扇放在因濾網、格柵或風道而压力不足的位置。

在类似 iDryer 的設備中，風扇通常用於空氣循環、加熱器冷卻、艙體排风、过滤或電子元件冷卻。

## 連接前要檢查什么

連接前，先確認風扇參數：

- 電壓：`5V`、`12V` 或 `24V`；
- 電流或功率；
- 連接器類型：2-pin、3-pin 或 4-pin；
- 是否支持 PWM 控制；
- 是否有測速訊號；
- 風量；
- 靜壓；
- 噪音等級；
- 工作溫度。

這些資料通常在標籤、產品頁面或技術 datasheet 中。

例如，風扇 datasheet 通常不仅包含電壓和電流，还包含風量、靜壓、噪音 `SPL dB(A)`、工作溫度和壽命。按這些參數選擇，比只看尺寸可靠得多。

## 不要从 GPIO 给風扇供電

控制器的 GPIO 是控制訊號，不是電源輸出。

不要直接从 GPIO 给風扇供電。这可能损坏控制器，或在風扇启动时造成控制器重置。

正確邏輯是：

- 風扇从電源或板载電源輸出获得供電；
- 控制器只負責开关或速度控制；
- 如果使用外部 MOSFET 模組，電源 `GND` 和控制器 `GND` 必須共地。

![N-channel MOSFET in switching mode (low-side) for load control](../../img/01-electronics-basics/02-nmos-switch-operation.png)

*來源：[Wikimedia Commons](https://commons.wikimedia.org/wiki/File:NMOS_PWR_WHOLE.PNG), KjellElec, CC BY-SA 4.0*

## 最簡單的方案：2-pin 風扇

2-pin 風扇通常只有：

- `+` 電源；
- `-` 電源。

如果是 24V 風扇，就接到 24V。如果是 12V 風扇，就接到 12V。

簡單开关控制可以使用：

- 板上的专用風扇輸出，前提是它支持所需電壓和電流；
- 用於 DC 负载的外部 MOSFET 模組；
- 獨立風扇控制器。

如果風扇需要持续運行，可以透過保險絲或受保护的電源线直接接到合適電源。但在帶加熱器的設備中，通常最好让控制器把風扇作為安全邏輯的一部分来控制。

## 3-pin 風扇

3-pin 風扇通常有：

- 電源；
- 地；
- 測速訊號。

測速訊號允许監控風扇 RPM。它本身不控制速度。

3-pin 風扇通常透過降低供電電壓或在電源线上做 PWM 来调速，前提是具体板子和風扇支持这种方式。但这种方法通常不如真正的 4-pin PWM：風扇可能啸叫、低速无法启动，或運行不穩定。

如果不需要调速，3-pin 風扇可以当普通 2-pin 使用：接電源和地，測速线不接。

## 4-pin PWM 風扇

4-pin PWM 風扇通常有：

- 地；
- 電源；
- 測速訊號；
- PWM 控制訊號。

關鍵差異是：風扇電源一直存在，速度由單獨的 PWM 訊號決定。

这是控制電腦 PWM 風扇的正確方式。不要以為 4-pin 風扇需要不断开关電源来控制。对于真正的 PWM 風扇，控制訊號应接到單獨的 PWM 腳位。

電腦 4-pin PWM 風扇的控制输入通常设计為开集电极/open-drain 訊號，并帶内部上拉，而不是接收任意 GPIO 電壓。不要把 `12V` 或 `24V` 加到 PWM 腳位。查看風扇文件；如果需要 open-drain/open-collector，请使用合適的晶体管輸出或 GPIO 模式。

許多 4-pin PWM 風扇的典型 PWM 頻率约為 `25 kHz`。有些風扇能在附近範圍工作，但頻率太低或太高时，可能全速運行、停止或產生噪音。

如果 PWM 线沒有連接，許多 4-pin 風扇会全速運行。

## 公共 GND / 公共負極

如果風扇由獨立電源供電，而 PWM 訊號来自控制器，就需要公共 `GND` / 公共負極。

沒有公共 `GND` 时，控制器和風扇沒有共同參考電平。結果是 PWM 可能不工作，或間歇工作。

簡單規則：

- 風扇正极来自合適電源；
- 風扇負極接到電源負極；
- 控制器 `GND` 接到同一个負極；
- 控制訊號只有在共地时才有效。

## 為任務選擇風扇

風扇不仅看尺寸和電壓。

重要參數：

- 風量；
- 靜壓；
- 噪音；
- 工作溫度；
- 壽命；
- 轴承類型；
- 連接器；
- PWM/測速支持。

对于打印机艙體濾網，普通安静机箱風扇可能太弱。它在自由空氣中吹得很好，但很难推动空氣穿过 HEPA 濾網、活性炭层或狭窄通道。

经验規則：

- 对于空氣混合和簡單冷卻，風量很重要；
- 对于濾網、散熱片和風道，靜壓很重要；
- 对于安静運行，不只看 `dB(A)`，还要看安装方式、格柵和振动；
- 对于加熱艙體，要看風扇的工作溫度。

## 启动電流和余量

風扇启动时，可能短时间消耗比正常運行更大的電流。

檢查：

- 板载輸出的最大電流；
- 单个風扇電流；
- 所有風扇总電流；
- 是否有启动余量；
- 长时间運行时端子、導線和 MOSFET 模組是否发熱。

例如，如果一个風扇消耗 `0.25A`，四个这样的風扇总共约 `1A`，还沒有计入启动電流。

## 範例：透過 MOSFET 模組連接

12V 或 24V 風扇的典型电路：

1. 電源正极接風扇正极。
2. 風扇負極接 MOSFET 模組的负载輸出。
3. 電源負極接 MOSFET 模組。
4. 控制器 `GND` 接電源負極。
5. 控制器控制腳位接 MOSFET 模組输入。

这叫 low-side switching：MOSFET 断开负载的負極。

对于簡單 2-pin 風扇，只要 MOSFET 模組满足電壓和電流要求，这是标准且清晰的方案。对于帶測速或獨立 PWM 输入的 3-pin/4-pin 風扇，“切負極”不一定合適：RPM 監控和原生 PWM 控制通常需要持续的公共 `GND`。

## Klipper 設定範例

範例中的腳位名并不通用。复制前先檢查你的板卡 pinout：錯誤的 `pin` 可能会激活錯誤輸出。

如果風扇接到受控輸出并需要手动控制：

```ini
[fan_generic chamber_fan]
pin: PA8
kick_start_time: 0.5
```

然后可以透過 G-code 控制：

```gcode
SET_FAN_SPEED FAN=chamber_fan SPEED=1.0
SET_FAN_SPEED FAN=chamber_fan SPEED=0.0
```

如果風扇需要根据艙體溫度启动：

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

这里的腳位名只是典型範例。真實設備中必須檢查板卡 pinout。

## 連接後要檢查什么

长时间運行前，確認：

- 風扇旋轉方向正確；
- 電壓与風扇匹配；
- MOSFET 模組不過熱；
- 端子不发熱；
- 導線对所選電流来说不太細；
- 風扇能从完全停止状态启动；
- PWM 控制在整个範圍内可用；
- 气流經過需要的區域，而不是从旁邊繞過；
- 格柵、濾網或外殼沒有比预期更嚴重地阻塞气流。

如果風扇靠近加熱器，请在真實艙體溫度下測試。台架上工作正常的風扇，在熱外殼中可能很快退化。

## 常見錯誤

- 把 12V 風扇接到 24V；
- 把 24V 風扇接到 12V，然后认為風扇坏了；
- 从 GPIO 给風扇供電；
- 忘記控制器和外部電源之間需要公共地；
- 期待 3-pin 風扇具备 PWM 控制；
- 用切断電源的方式控制 4-pin PWM 風扇，而不是使用 PWM 腳位；
- 沒有計算多個風扇的总電流；
- 只按尺寸选風扇，不檢查靜壓；
- 把安静風扇装在密集濾網上，結果幾乎沒有气流；
- 安装后不檢查气流方向；
- 導線沒有固定，最終被葉輪或外殼磨損。

## 要點

- 風扇電壓必須匹配電源。
- GPIO 不给風扇供電，只負責控制。
- 使用外部電源时，必須与控制器共地。
- 2-pin 風扇最容易透過電源輸出或 MOSFET 控制。
- 3-pin 風扇有測速訊號，但不一定有 PWM 控制。
- 4-pin PWM 最好用獨立 PWM 訊號控制，而不是开关電源。
- 对濾網和風道来说，靜壓比漂亮的 `CFM` 數字更重要。
- 组装后不仅要檢查旋轉，还要檢查气流是否真正穿过結構。

## 相關閱讀

- [Noctua: PWM setup and RPM monitoring of a fan with microcontrollers](https://www.noctua.at/en/support/faqs/microcontroller-guide-pwm-setup-and-rpm-monitoring) - 4-pin PWM、RPM 訊號、公共地和典型 PWM 頻率的实用說明。
- [Klipper Configuration Reference: Fans](https://www.klipper3d.org/Config_Reference.html#fans) - 官方 `fan`、`heater_fan`、`controller_fan`、`temperature_fan` 和 `fan_generic` 設定。
- [Voron Documentation: Chamber Temperature & Exhaust Fan](https://docs.vorondesign.com/community/howto/alchemyEngine/chamber_temperature_exhaust_fan.html) - 在 Klipper 中按溫度控制艙體排风風扇的範例。
- [DigiKey: Selecting A Fan](https://www.digikey.com/en/articles/selecting-a-fan) - 按風量、靜壓、外殼阻力和濾網選擇風扇。
- [SANYO DENKI: DC fan example datasheet](https://products.sanyodenki.com/en/sanace/dc/dc-fan/109P0405F601/) - 真實參數範例：電壓、電流、風量、靜壓、噪音、工作溫度和壽命。
