# 壓接連接器

壓接是在不焊接的情況下將電線連接到端子或接觸點的方法。

一個好的壓接提供：

- electrical contact;
- mechanical wire retention;
- insulation support;
- repeatability;
- 組裝、維修方便。

不良的壓接可能會變熱、脫落、導致隨機錯誤，但看起來幾乎是正常的。

## 為什麼壓接通常比焊接更好

對於連接器和端子，壓接通常比焊接更好，因為：

- 電線保持靈活；
- 觸點由製造商設計；
- 保留絕緣；
- 關節更好地處理震動；
- 連接器可以拆卸和維修；
- 焊接過程中沒有熔化塑膠連接器主體的風險。

焊接對於焊盤和電線有好處，但如果製造商打算壓接，則不應取代連接器中的正確接點。

## 端子和連接器的類型

在簡單的設備中，您經常會發現：

- 杜邦 - 麵包板的弱訊號連接；
- JST-XH/JST-PH 及類似產品 - 感測器、風扇、小模組；
- 套圈 - 螺絲端子中多股線的尖端；
- Faston - 用於某些電源連接的扁平端子；
- 環形端子和鏟形端子；
- screw terminals;
- board-mounted terminal blocks.

每種類型都需要自己的觸點、自己的線規和自己的工具。

## 您需要合適的工具

鉗子不是壓接工具。

您可以擠壓觸點，使其看起來固定，但無法獲得適當的壓接。

為了獲得良好的壓接效果，您需要：

- 用於正確線規的端子；
- correct strip length;
- correct tool matrix;
- 矩陣中正確的接觸位置；
- 絞線和絕緣壓接的單獨區域；
- no damaged strands.

專業連接器製造商提供壓接規格、壓接高度、剝線長度和拉力。對於 DIY 組裝，您並不總是能夠完全控制，但原則是相同的：觸點、電線和工具必須相互匹配。

## Open barrel crimp

許多小型觸點，例如 JST 或杜邦，都有兩對「翅膀」：

- 一對壓接裸露導體；
- 另一對固定絕緣層。

Good result:

- 導體在正確的區域可見；
- 絕緣由後翼保持；
- 外露長度不能太長；
- conductor strands don't stick out;
- 觸點不歪斜；
- 觸點進入連接器主體並鎖定到位。

如果絕緣體進入導體壓接區，電氣接觸將會不良。

如果僅壓接導體而未固定絕緣層，則移動時電線可能會斷裂。

## Ferrules

對於螺絲端子中的多股電線，套圈通常很有用。

They:

- gather all strands together;
- 防止股線分離；
- 改善航站的座位；
- 降低某些股線被留在外面的風險；
- 使接縫更整齊。

這對於要維修的電源線、端子塊和組件特別有用。

但套圈也必須與線規匹配，並用正確的矩陣進行壓接。

## 如何檢查壓接

壓接後，驗證：

- 觸點不會在線路上移動；
- insulation is held;
- 導體不拉出；
- no strands are cut;
- 外露長度不能太長；
- 觸點進入連接器本體；
- 鎖卡入到位；
- 電線可以承受輕微的拉扯。

輕柔的拉力測試很有用：小心地拉動電線。它不應該從接觸中出來。

不需要用盡全力去拉。目標是在安裝前找到明顯不良的壓接。

## 為什麼不良壓接會變熱

不良壓接會產生高電阻。

在電流下這會變成熱量。

首先，終端可能只是溫暖。然後塑膠變暗，接觸變差，熱度增加。

這對以下人員來說尤其危險：

- heaters;
- 有大電流的風扇；
- LED strips;
- power supplies;
- SSR/MOSFET circuits;
- mains connections.

如果終端變熱，請關閉電源並重新連接。

## 杜邦不是為了權力

杜邦對於麵包板和弱訊號來說很方便。

但它不能用作適當的電源連接器：

- a heater;
- device power;
- a powerful LED strip;
- mains parts;
- 大電流的馬達或伺服。

即使連接器在物理上適合引腳，也不代表它能夠滿足所需的電流、振動和熱量。

## 常見錯誤

- 用鉗子壓接；
- 選擇了錯誤的儀表端子；
- stripped too much insulation;
- stripped too little insulation;
- 壓接絕緣體代替導體；
- 沒有壓接絕緣支撐；
- cut some strands;
- 觸點未鎖定在體內；
- 杜邦電源線；
- 套圈規格錯誤；
- didn't do a pull test;
- terminal gets hot but device keeps running.

## 重點

- 壓接既是電接觸又是機械保持。
- 觸點、電線和工具必須相互匹配。
- Pliers don't replace a crimping tool.
- 對於螺絲端子中的多股電線，套圈通常很有用。
- 不良的捲曲可能會變熱並且很危險。
- 電源部件不應依賴薄弱的麵包板連接器。

## Reference materials

- [Molex: Quality Crimp Handbook](https://www.molex.com/content/dam/molex/molex-dot-com/products/automated/en-us/commercialcrimpbookpdf/638/63800/TM-638000029-001.pdf?inline=) - detailed crimp quality reference, pull force, conductor and insulation crimp.
- [Molex: Industrial Crimp Quality Handbook](https://www.molex.com/content/dam/molex/molex-dot-com/products/automated/en-us/industrialcrimpbookpdf/640/64016/TM-640160065-001.pdf?inline=) - visual inspection of open and closed barrel crimp, strip length, wire brush and common defects.
- [JST: Application Tooling Guide, Crimp Style](https://www.jst.com/resources/application-tooling-guide/crimp-style/) - example of how specific JST contacts need specific tools, strip length and tensile specs.
- [American Electrical: Wire Ferrules](https://www.americanelectrical.com/wire-ferrules/) - why ferrules are useful for multi-strand wire in terminal blocks.
- [TE Connectivity: Wire Splices](https://www.te.com/en/products/terminals-splices/splices.html) - industrial crimp/splice connection types and why crimping is engineered separately, not random squeezing.
