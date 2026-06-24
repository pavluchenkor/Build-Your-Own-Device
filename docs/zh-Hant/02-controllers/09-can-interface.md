# CAN 介面

CAN 是一種讓多個裝置共用差動線路進行通訊的介面。全稱：`Controller Area Network`。

CAN 源自汽車與工業電子領域，但在 3D 印表機中因工具頭板、遠端 MCU 及需要比 I2C/SPI 更長距離、更可靠通訊的模組而普及。

## CAN 的適用場景

在印表機及類似 iDryer 的周邊裝置中，CAN 用於：

- 印表機列印頭上的工具頭板；
- 遠端模組中的額外 MCU；
- 減少線束中的導線數量；
- 與 CAN 濾波器、攝影機或乾燥機板的通訊；
- 多控制器的分散式系統；
- USB 或長距離 I2C/SPI 不適用的場合。

當節點距離主機或主板較遠，且周圍有馬達、加熱器及其他干擾源時，CAN 尤其有用。

## CANH、CANL 與 GND

實體 CAN 匯流排通常使用：

- `CANH`；
- `CANL`；
- 有時使用 `GND` 或共同參考線；
- 若有需要，模組電源獨立供應。

訊號以 `CANH` 與 `CANL` 之間的差值傳輸，這也是 CAN 比單一訊號線更能抗干擾的原因。

簡化示意圖：

![高速 CAN ISO 11898-2 匯流排，含多個節點與終端電阻](../../img/02-controllers/09-can-iso11898-2-network.png)

*來源：[Wikimedia Commons](https://commons.wikimedia.org/wiki/File:CAN_ISO11898-2_Network.png)，EE JRW，CC BY-SA 4.0*

佈線時，`CANH`/`CANL` 通常採用雙絞線。`GND` 的連接方式取決於具體電路、電路板與說明文件，但在小型 DIY 系統中，通常需要共同參考點以確保穩定運作與介面安全。

## 必須具備 CAN 收發器

重要提示：微控制器支援 CAN 與電路板上具備 CAN 功能並非同一回事。

要讓 CAN 正常運作，需要：

- 具有 CAN 控制器或適當韌體支援的微控制器；
- 電路板上的 CAN 收發器；
- 正確的 `CANH`/`CANL` 接頭；
- 收發器電源；
- 終端電阻；
- 為 CAN 編譯的韌體。

若微控制器規格表提及 CAN，但電路板上沒有收發器，則無法直接連接至 CAN 匯流排。

## 拓撲架構與終端電阻

CAN 是一種匯流排。良好的拓撲架構形如一條直線，各節點透過短分支連接。

通常需要兩個 `120 Ohm` 終端電阻：

- 一個位於匯流排的一端；
- 另一個位於另一端。

不是一個，不是三個，也不是「每塊板子各一個」。確切地說，兩端各一個。

在斷電狀態下，一條正確終接的匯流排，用三用電錶量 `CANH` 與 `CANL` 之間，通常會顯示約 `60 Ohm`，因為兩個 `120 Ohm` 電阻並聯。

許多電路板設有終端電阻跳線，有些則內建終端電阻且不易停用。因此在組裝前，請檢查匯流排上所有電路板的電路圖。

## 位元率

CAN 速率必須在所有節點上一致。在 Klipper 中，CAN 通常使用 `1000000`，即 `1 Mbit/s`，但具體數值取決於韌體、設定及匯流排長度。

若位元率不同，節點將無法正常通訊。

對於較長或有問題的佈線，速率可能至關重要。速率越高，匯流排對拓撲架構、終端電阻及線材品質的要求也越嚴格。

## Klipper 中的 CAN

在 Klipper 中，CAN 作為與 MCU 通訊的方式之一。

CAN 上的裝置通常不透過 `serial:` 指定，而是在設定中使用 `canbus_uuid`：

```ini
[mcu toolhead]
canbus_uuid: 11aa22bb33cc
```

在 Linux 端，通常需要 `can0` 介面。主機必須具備 CAN 轉接器：

- USB-CAN 轉接器；
- 處於 USB-to-CAN 橋接模式的電路板；
- SBC 用 HAT/轉接器；
- 其他受支援的電路。

Klipper 提供工具來尋找新未初始化裝置的 `canbus_uuid`。請注意：若裝置已由 Klipper 設定，它可能不再出現在清單中的「新」裝置列表裡。

## USB-to-CAN 橋接

部分電路板可以燒錄為 USB-to-CAN 橋接模式。此時電路板透過 USB 連接主機，並在 Linux 中顯示為 CAN 轉接器。

這種方式很方便，但有一個重要限制：橋接模式的用途是與真實 CAN 匯流排及其他 CAN 節點通訊。若主機附近只有一塊板子且沒有真實 CAN 匯流排，通常直接使用一般 USB/串列模式會更簡單。

此外，USB-to-CAN 橋接器不會顯示為 `/dev/serial/by-id/...`。它被設定為 CAN 介面，使用 `canbus_uuid` 而非 `serial:`。

## 何時適合使用 CAN

以下情況值得考慮使用 CAN：

- 需要連接工具頭板；
- 需要透過長線束進行通訊；
- 需要多個遠端 MCU；
- 希望減少移動部件與外殼之間的導線；
- 已有 CAN 基礎設施；
- 所選電路板有完善的 Klipper CAN 說明文件。

以下情況 CAN 可能並非必要：

- 電路板位於主機附近；
- 只需一個額外的 MCU；
- USB 運作穩定；
- 對燒錄、`can0`、終端電阻及 Linux 網路設定缺乏經驗；
- 所選電路板說明文件不完善。

對於第一個簡單的額外控制器，USB 通常更快速且清晰。當 CAN 真正能解決佈線或板卡分散問題時，才有使用的意義。

## CAN 不為負載供電

CAN 僅用於通訊。

若 CAN 板控制風扇、加熱器、SSR 或伺服馬達，仍需要：

- 電路板電源；
- 負載電源；
- MOSFET/驅動器/SSR；
- 保險絲；
- 適當的接線端子；
- 加熱器的熱保護；
- 安全的外殼。

CAN 無法取代電力電子元件，也不能讓加熱器變得安全。

## 購買前的確認事項

購買 CAN 板前，請確認：

- 使用的是什麼微控制器；
- 電路板是否支援 Klipper CAN；
- 是否有 CAN 收發器；
- `CANH` 和 `CANL` 的位置；
- 是否有終端電阻及如何啟用；
- 使用的是什麼接頭；
- 電路板如何供電；
- 電路板如何燒錄；
- 是否有 `canbus_uuid` 的操作說明；
- 是否需要獨立的 USB-CAN 轉接器；
- 是否有電路圖及引腳分配圖；
- 有哪些可用的引腳與電源輸出。

若賣家僅因晶片理論上支援 CAN 就標示「CAN」，但電路板上沒有收發器也沒有說明文件，這是個不好的選擇。

## 常見錯誤

- 混淆 `CANH` 和 `CANL`；
- 忘記需要 CAN 收發器；
- 只裝一個終端電阻而非兩個；
- 在每塊板子上都啟用了終端電阻；
- 未檢查 `CANH` 與 `CANL` 之間的電阻；
- 各節點設定了不同的位元率；
- 期望從 USB-to-CAN 橋接器找到 `/dev/serial/by-id`；
- 將板子燒錄為 USB 模式，卻以 CAN 方式連接；
- 燒錄為 CAN 模式，卻未設定 `can0`；
- 用長分支組成星型架構而非匯流排；
- 以為 CAN 可以為負載供電。

## 重點摘要

CAN 是遠端 MCU、工具頭板及印表機內分散式系統的理想介面。它使用差動對 `CANH`/`CANL`，需要 CAN 收發器、正確的拓撲架構，以及匯流排兩端各一個終端電阻。

對於 Klipper，CAN 雖有用但比 USB 複雜：需要將板子燒錄為 CAN 模式、設定轉接器/`can0`、尋找 `canbus_uuid`，並確認實體匯流排。在 CAN 確實能簡化佈線或提升連接可靠性的場合再使用。

## 相關資料

- [Klipper: CANBUS](https://www.klipper3d.org/CANBUS.html) - Klipper 官方 CAN 說明文件：硬體、主機轉接器、`can0`、`canbus_uuid`、終端電阻及 USB-to-CAN 橋接。
- [Klipper: CANBUS protocol](https://www.klipper3d.org/CANBUS_protocol.html) - Klipper 如何指派 CAN 節點 ID 及使用 `canbus_uuid`。
- [CAN Bus Debugger: CAN Bus Termination Explained](https://www.canbusdebugger.com/articles/can-bus-termination) - 兩個 `120 Ohm` 終端電阻、`60 Ohm` 量測方法及常見錯誤的實用說明。
- [DigiKey: CAN Bus explained](https://www.digikey.com/en/blog/can-bus-explained) - CAN 匯流排、差動通訊及其在分散式系統中應用的概觀。
- [Texas Instruments: Introduction to CAN](https://www.ti.com/lit/an/sloa101b/sloa101b.pdf) - CAN 實體層、收發器及典型網路的基礎說明。
