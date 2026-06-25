# 焊接

焊接用於當你需要可靠地連接電線到焊盤、焊接連接器、修復斷開的連接或組裝小模組時。

但焊接不應該替代電線會拉動、振動或發熱的地方的適當的連接器、端子或機械緊固。

## 何時適合焊接

Soldering is good for:

- 將電線焊接到板上；
- installing a pin header;
- repairing a broken wire;
- connecting a small module;
- soldering a thermistor or signal wire;
- prototype assembly.

對於以下情況，焊接不是最佳選擇：

- frequently disassembled connections;
- 電源端子無應力消除裝置；
- 會移動的電線；
- 熱區內的連接無保護；
- 電源 110-230V 交流電部件沒有適當的端子和外殼。

## Minimal kit

為了正確焊接，您需要：

- 帶溫度控制的烙鐵；
- solder;
- flux;
- soldering iron stand;
- 用於清潔尖端的海綿或銅絲；
- wire cutters;
- wire stripper;
- tweezers or third hand;
- heat shrink tubing;
- 如有需要，可使用異丙醇進行清潔。

沒有支架的烙鐵是個壞主意。熱尖很容易燒傷您的手、電線、外殼或桌子。

## Tin a wire

將電線鍍錫意味著在裸露的電線上塗上一層薄薄的焊料。

Procedure:

1. 剝去一點絕緣層。
2. 如果電線是多股線，請將股線絞在一起。
3. 如果焊料流動性不好，請塗抹助焊劑。
4. 用烙鐵加熱電線。
5. 在加熱區域塗抹一些焊料。
6. 讓焊料流過絞線。

不要將電線末端變成厚厚的硬塊。鍍錫應整齊、薄。

## Solder a wire to a pad

Procedure:

1. 固定電路板和電線。
2. 給墊子上錫。
3. 給電線鍍錫。
4. 將電線連接到焊盤上。
5. 同時加熱電線和墊。
6. 讓焊錫熔化並連接零件。
7. 除去焊料，然後除去烙鐵。
8. 焊料冷卻時請勿移動接頭。

良好的焊點看起來光滑、有光澤或均勻暗淡，具體取決於焊料。它不應該是位於頂部的未弄濕墊的斑點。

## Cold solder joints

冷焊點是指焊料未正常加熱且未正常流動的地方。

Signs:

- rough surface;
- solder in a lump;
- wire moves;
- 接觸來來去去；
- 輕微活動時關節就會斷裂。

冷焊點很危險，因為它們有時可能會起作用。在加熱或振動的設備中，這種接觸會退化。

通常，透過用助焊劑重新加熱直至焊料適當流動來固定冷接點。

## Overheated pad

如果加熱墊時間過長，它可能會從電路板上脫離。

這尤其影響：

- cheap modules;
- small pads;
- thin traces;
- multiple rework attempts;
- 電線拉動焊盤。

如果焊料不流動，您並不總是需要加熱更長時間。通常添加助焊劑、清潔烙鐵頭、使用合適的溫度或更大的烙鐵頭會有所幫助。

## Flux

助焊劑有助於焊錫潤濕金屬。

如果沒有助焊劑，焊料通常會成球並且無法很好地連接零件。

焊接後，需要清洗掉一些助焊劑。這取決於助焊劑類型：

- no-clean can often be left;
- 水溶性的必須除去；
- 活性助焊劑不應留在板上。

如果您不知道助焊劑類型，請使用電子級助焊劑並閱讀其說明。

## 熱縮和絕緣

焊點必須絕緣。

對於電線，通常使用熱縮管。

Procedure:

1. 焊接前將熱縮管滑過電線。
2. 焊接電線。
3. 檢查接頭。
4. 將熱縮管滑入到位。
5. Heat it gently.

請勿將焊接接頭暴露在可能接觸到外殼、其他電線、端子或風扇的地方。

## Strain relief

Solder doesn't like mechanical stress.

如果電線會拉動、振動或移動，則需要消除應力：

- cable tie;
- clamp;
- strain relief connector;
- 將矽膠塊放在安全的地方；
- 固定在外殼上的電線；
- 連接器而不是直接焊接。

不好的做法：電線僅由焊盤固定。隨著時間的推移，它可能會將墊子撕松。

## Power wires

電源線的焊接必須格外小心。

Verify:

- 電線規格正確；
- 接頭已充分加熱；
- no cold solder joints;
- no exposed strands;
- 存在絕緣；
- 存在機械緊固；
- 接頭不在沒有保護的情況下靠近熱區。

對於電源線，合適的端子或連接器通常比永久焊接電線更好。

## 焊接後要檢查什麼

焊接後：

- 檢查接頭；
- 檢查相鄰觸點是否短路；
- 使用萬用電表檢查所需的連接；
- 驗證`GND`和`GND`之間沒有短路；
- 輕輕拉動電線；
- 確認熱收縮覆蓋金屬；
- 檢查電線是否不會拉動墊子。

## 常見錯誤

- 用骯髒的烙鐵頭進行焊接；
- 不使用助焊劑；
- 僅加熱焊料，不加熱焊盤和導線；
- making a solder blob;
- 在焊料冷卻時移動焊絲；
- 墊子過熱；
- 留下未熱縮的開放接縫；
- 僅用焊錫固定電線；
- 用弱鐵焊接電源線太細；
- 使用不適合電子產品的酸性焊劑。

## 重點

- 良好的焊接需要加熱兩個部件，而不僅僅是滴焊料。
- Flux often solves poor wetting problems.
- 冷焊點有時可能會起作用，因此很危險。
- 焊點必須絕緣並進行機械釋放。
- 對於經常拆卸和電源連接，連接器或端子通常比焊接更好。

## Reference materials

- [SparkFun: How to Solder, Through-Hole Soldering](https://learn.sparkfun.com/tutorials/how-to-solder-through-hole-soldering) - tools, temperature, flux, good soldering and connection checking.
- [SparkFun: Soldering Your First Component](https://learn.sparkfun.com/tutorials/how-to-solder-through-hole-soldering/soldering-your-first-component) - basic rules: heating the pad and lead, solder application order, good joint shape.
- [Adafruit: Guide to Excellent Soldering](https://learn.adafruit.com/adafruit-guide-excellent-soldering) - practical soldering guide for electronics.
- [Adafruit: Common Soldering Problems](https://learn.adafruit.com/adafruit-guide-excellent-soldering/common-problems) - cold joints, overheating, too much solder and fixes.
- [NASA Workmanship: Soldered Electrical Connections](https://workmanship.nasa.gov/lib/insp/2%20books/links/sections/407%20Soldering.html) - reference material on solder joint quality and mechanical wire support.
