# 連接負載傳感器

負載傳感器通過金屬梁、按鈕或平台的微小變形來測量力或重量。

在類似iDryer的設備中，負載傳感器可以估計線軸重量、剩餘細絲或機制負載。

重點：稱重感測器幾乎從不直接連接到控制器。它的信號太小。通常，HX711 模組或類似的放大器/ADC 放置在感測器和控制器之間。

## 你需要什麼

Minimum set:

- 所需重量範圍的稱重感測器；
- HX711 module;
- controller: Arduino, ESP32, RP2040, STM32, or other board;
- rigid mechanical mounting;
- 用於校準的已知質量；
- short, neat wires.

如果機械性能較差，電路將無濟於事。稱重感測器可以完美接線，但由於未對準、遊隙或在錯誤點施加負載而給出毫無意義的讀數。

## 連接是如何安排的

稱重感測器透過類比線連接到 HX711。

HX711透過數位線連接到控制器。

典型鏈條：

```text
load cell -> HX711 -> controller
```

HX711通常有兩個側面：

- 來自稱重感測器的輸入：`E-`、`A+`、`A-`、`A-` 或類似的；
- 連接到控制器：`GND`、`DT`、`DOUT`/`SCK`、`CLK`/`CLK`。

![HX711 and load cell connection diagram](../../img/06-practical-guides/04-hx711-load-cell-fritzing.jpg)

*Source: [SparkFun Electronics](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide/all), CC BY-SA 4.0*

## Load cell wires

常見的四線稱重感測器通常具有：

- `E+` - bridge supply plus;
- `E-` - bridge supply minus;
- `S+`, `A+`, or `O+` - positive measurement signal;
- `S-`, `A-`, or `O-` - negative measurement signal.

常見配色：

- red - `E+`;
- black - `E-`;
- green or blue - `A+`;
- white - `A-`.

但顏色不是法律。不同的感測器可能會有所不同。如果有特定稱重感測器的數據表，請遵循該數據表。

如果感測器有第五根電線、箔片或屏蔽，則通常是電磁屏蔽。不要將其與電橋測量線混淆。通常，屏蔽連接到 `A+` 或一側的外殼（如果文件有說明），但不連接到測量 `A-`/`A-`。

如果沒有接線圖，請勿「隨意」連接稱重感測器。首先找到感測器資料表或按照製造商指南圈出電橋：不正確的電線很容易導致讀數不穩定或 HX711 輸入過載。

## 將 HX711 連接到控制器

在控制器端，通常需要四行：

- `VCC` - module power;
- `GND` - common negative;
- `DT`, `DOUT`, or `DATA` - data;
- `SCK`, `CLK`, or `PD_SCK` - clock.

對於許多 HX711 模組，電源可以是 `5V` 或 `5V`，但請檢查特定模組。如果控制器運作在3.3V，則使用與3.3V邏輯相容的模組和電源會很方便。

引腳 `SCK` 和 `SCK` 通常可以連接到常規 GPIO。這不是通常意義上的I2C或SPI，而是簡單的兩線HX711介面。

## 機械原理比電路更重要

稱重感測器必須按照製造商的預期變形。

對於光束感測器，一側通常安裝在固定底座上，另一側承受負載。如果兩側都剛性地安裝到一個零件上，感測器將不會正常彎曲。

檢查：

- 感測器的安裝面在哪裡；
- 應在何處施加負載；
- 力應該朝哪個方向移動；
- 是否需要墊片；
- 運動部件是否離開外殼；
- no misalignment;
- no side loading;
- 螺絲沒有擰得太緊；
- 線軸或平台不會落在感測器的工作區域之外。

對於線軸重量，尤其重要的是所有負載都必須通過感測器，而不是部分通過外殼壁、軸、電纜或裝飾蓋。

## 不要使感測器過載

稱重感測器的範圍不是建議，而是測量限制。

如果將 1 kg 感測器放置在線軸和支架可能超過此重量的位置，則感測器將工作不良或永久變形。

選擇帶邊距的範圍：

- maximum spool weight;
- holder weight;
- possible jerks;
- misalignment;
- 使用者錯誤的安全裕度。

但太大的範圍也不總是好的。 100 公斤感測器對小線軸的感應效果比具有相同機械和電子設備的 5 公斤或 10 公斤感測器差。

## 首次啟動

在安裝到設備之前，請在工作台上測試系統：

1. 將稱重感測器連接至 HX711。
2. 將 HX711 連接到控制器。
3. Run test code or a library.
4. 確保按下感應器時原始值會改變。
5. 卸下負載並檢查該值是否相當穩定。
6. 放置一個已知質量並檢查是否有變化。

在此階段，不要求克精度。首先，您需要查看感測器是否處於活動狀態、負載方向正確且讀數變化可預測。

如果該值隨著權重的增加而減少，通常只需交換 `A-` 和 `A-` 或考慮登入代碼即可。

## 皮重和校準

未經校準的稱重感測器不知道克是什麼。

典型流程：

1. Place empty platform.
2. 皮重：平台重量為零。
3. Place a known mass.
4. Select calibration factor.
5. 檢查幾個不同的重量。

對於細絲線軸，確定什麼算是重量：

- 整個線軸採用塑膠；
- 僅剩餘塑料，無空線軸重量；
- 重量相對於初始值的變化。

如果不同製造商的空線軸重量不同，則準確的剩餘計算需要了解具體的空線軸重量或進行粗略估計。

## 噪音和讀數不穩定

HX711 測量非常小的訊號，因此系統對雜訊和機械問題很敏感。

讀數不穩定的原因：

- 從感測器到 HX711 的電線很長；
- poor contacts;
- 訊號線旁的加熱器電源線；
- fan or printer vibration;
- soft base;
- play in mounting;
- temperature drift;
- 負載繞過感測器接觸外殼。

Practical measures:

- 使 HX711 靠近稱重感測器；
- 請勿將訊號線與加熱器電源線並排走線；
- 固定電線，使其不會拉動感應器；
- 使用測量平均值；
- 安裝到外殼後進行校準；
- 如果溫度顯著影響讀數，請在設備預熱後去皮。

## 組裝後要檢查什麼

使用前：

- 感測器額定重量為所需重量；
- 負載通過感測器的工作部分；
- 緊固件不阻擋變形；
- HX711 receives correct power;
- `SCK`和`SCK`連接到右側GPIO；
- common ground exists;
- 原始值在負載下會改變；
- 無負載時，讀數不會漂移太快；
- 已知質量顯示校準後的預期重量；
- 電線不會拉動平台；
- 線軸或支架不會越過感知器接觸外殼。

## 常見錯誤

- 將稱重感測器直接連接到控制器類比輸入；
- 混淆 `E-`/`A+` 和 `A-`/`A-`；
- 無需數據表即可信任電線顏色；
- forgetting calibration;
- 最終機械安裝前去皮重；
- 安裝感應器，使其不能彎曲；
- 感測器過載；
- 選擇太大的範圍而失去靈敏度；
- 由於長電線和乾擾而導致不穩定；
- 期望從沒有剛性機械結構的柔性塑膠體獲得克數精度。

## 要點

- 稱重感測器通常透過HX711連接，而不是直接連接到控制器。
- 感測器線連接至 `E-`、`A+`、`A-`、`A-`。
- HX711 透過電源、接地、`SCK` 和 `SCK` 連接到控制器。
- 機械裝置比電路更重要：負載必須正確通過感測器。
- 需要使用已知質量進行皮重和校準。
- 如果沒有牢固的安裝和適當的機械結構，就不可能獲得準確的讀數。

## 相關閱讀

- [SparkFun: Load Cell Amplifier HX711 Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide/all) - practical HX711 and load cell connection, wire colors, `DT`/`SCK`, and calibration example.
- [SparkFun: Load Cell Amplifier HX711 product page](https://www.sparkfun.com/sparkfun-load-cell-amplifier-hx711.html) - HX711 module description, purpose, and microcontroller interface.
- [DigiKey: HX711 Datasheet by Avia Semiconductor](https://www.digikey.com/en/htmldatasheets/production/1836471/0/0/1/hx711.html) - HX711 technical datasheet: 24-bit ADC, differential bridge input, gain, and digital interface.
- [Phidgets: Load Cell Guide](https://cdn.phidgets.com/docs/Load_Cell_Guide) - practical examples of load cell mechanical installation and load application direction.
- [SparkFun retired HX711 guide: load cell mechanical setup](https://learn.sparkfun.com/tutorials/retired---load-cell-amplifier-hx711-breakout-hookup-guide) - useful illustrations of beam, button, and platform sensor mounting options.
