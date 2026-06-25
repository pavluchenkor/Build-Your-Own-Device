# 焊接

焊接用于当你需要可靠地连接电线到焊盘、焊接连接器、修复断开的连接或组装小模块时。

但焊接不应该替代电线会拉动、振动或发热的地方的适当的连接器、端子或机械紧固。

## 何时适合焊接

Soldering is good for:

- 将电线焊接到板上；
- installing a pin header;
- repairing a broken wire;
- connecting a small module;
- soldering a thermistor or signal wire;
- prototype assembly.

对于以下情况，焊接不是最佳选择：

- frequently disassembled connections;
- 电源端子无应力消除装置；
- 会移动的电线；
- 热区内的连接无保护；
- 电源 110-230V 交流部件没有适当的端子和外壳。

## Minimal kit

为了正确焊接，您需要：

- 带温度控制的烙铁；
- solder;
- flux;
- soldering iron stand;
- 用于清洁尖端的海绵或铜丝；
- wire cutters;
- wire stripper;
- tweezers or third hand;
- heat shrink tubing;
- 如果需要，可使用异丙醇进行清洁。

没有支架的烙铁是个坏主意。热尖很容易烧伤您的手、电线、外壳或桌子。

## Tin a wire

给电线镀锡意味着在裸露的电线上涂上一层薄薄的焊料。

Procedure:

1. 剥去一点绝缘层。
2. 如果电线是多股线，请将股线绞合在一起。
3. 如果焊料流动性不好，请涂抹助焊剂。
4. 用烙铁加热电线。
5. 在加热区域涂抹一些焊料。
6. 让焊料流过绞线。

不要将电线末端变成厚厚的硬块。镀锡应整齐、薄。

## Solder a wire to a pad

Procedure:

1. 固定电路板和电线。
2. 给垫子上锡。
3. 给电线镀锡。
4. 将电线连接到焊盘上。
5. 同时加热电线和垫。
6. 让焊料熔化并连接零件。
7. 除去焊料，然后除去烙铁。
8. 焊料冷却时不要移动接头。

良好的焊点看起来光滑、有光泽或均匀暗淡，具体取决于焊料。它不应该是位于顶部的未弄湿垫的斑点。

## Cold solder joints

冷焊点是指焊料未正常加热且未正常流动的地方。

Signs:

- rough surface;
- solder in a lump;
- wire moves;
- 接触来来去去；
- 轻微活动时关节就会断裂。

冷焊点很危险，因为它们有时可能会起作用。在加热或振动的设备中，这种接触会退化。

通常，通过用助焊剂重新加热直至焊料适当流动来固定冷接点。

## Overheated pad

如果加热垫时间过长，它可能会从电路板上脱离。

这尤其影响：

- cheap modules;
- small pads;
- thin traces;
- multiple rework attempts;
- 电线拉动焊盘。

如果焊料不流动，您并不总是需要加热更长时间。通常添加助焊剂、清洁烙铁头、使用合适的温度或更大的烙铁头会有所帮助。

## Flux

助焊剂有助于焊料润湿金属。

如果没有助焊剂，焊料通常会成球并且无法很好地连接部件。

焊接后，需要清洗掉一些助焊剂。这取决于助焊剂类型：

- no-clean can often be left;
- 水溶性的必须除去；
- 活性助焊剂不应留在板上。

如果您不知道助焊剂类型，请使用电子级助焊剂并阅读其说明。

## 热缩和绝缘

焊点必须绝缘。

对于电线，通常使用热缩管。

Procedure:

1. 焊接前将热缩管滑过电线。
2. 焊接电线。
3. 检查接头。
4. 将热缩管滑入到位。
5. Heat it gently.

请勿将焊接接头暴露在可能接触外壳、其他电线、端子或风扇的地方。

## Strain relief

Solder doesn't like mechanical stress.

如果电线会拉动、振动或移动，则需要消除应力：

- cable tie;
- clamp;
- strain relief connector;
- 将硅胶块放在安全的地方；
- 固定在外壳上的电线；
- 连接器而不是直接焊接。

不好的做法：电线仅由焊盘固定。随着时间的推移，它可能会将垫子撕松。

## Power wires

电源线的焊接必须格外小心。

Verify:

- 电线规格正确；
- 接头已充分加热；
- no cold solder joints;
- no exposed strands;
- 存在绝缘；
- 存在机械紧固；
- 接头不在没有保护的情况下靠近热区。

对于电源线，合适的端子或连接器通常比永久焊接电线更好。

## 焊接后要检查什么

焊接后：

- 检查接头；
- 检查相邻触点是否短路；
- 使用万用表检查所需的连接；
- 验证`GND`和`GND`之间没有短路；
- 轻轻拉动电线；
- 确认热收缩覆盖金属；
- 检查电线是否不会拉动垫子。

## 常见错误

- 用肮脏的烙铁头进行焊接；
- 不使用助焊剂；
- 仅加热焊料，不加热焊盘和导线；
- making a solder blob;
- 在焊料冷却时移动焊丝；
- 垫子过热；
- 留下未热缩的开放接缝；
- 仅用焊料固定电线；
- 用弱铁焊接电源线太细；
- 使用不适合电子产品的酸性焊剂。

## 要点

- 良好的焊接需要加热两个部件，而不仅仅是滴焊料。
- Flux often solves poor wetting problems.
- 冷焊点有时可能会起作用，因此很危险。
- 焊点必须绝缘并进行机械释放。
- 对于经常拆卸和电源连接，连接器或端子通常比焊接更好。

## Reference materials

- [SparkFun: How to Solder, Through-Hole Soldering](https://learn.sparkfun.com/tutorials/how-to-solder-through-hole-soldering) - tools, temperature, flux, good soldering and connection checking.
- [SparkFun: Soldering Your First Component](https://learn.sparkfun.com/tutorials/how-to-solder-through-hole-soldering/soldering-your-first-component) - basic rules: heating the pad and lead, solder application order, good joint shape.
- [Adafruit: Guide to Excellent Soldering](https://learn.adafruit.com/adafruit-guide-excellent-soldering) - practical soldering guide for electronics.
- [Adafruit: Common Soldering Problems](https://learn.adafruit.com/adafruit-guide-excellent-soldering/common-problems) - cold joints, overheating, too much solder and fixes.
- [NASA Workmanship: Soldered Electrical Connections](https://workmanship.nasa.gov/lib/insp/2%20books/links/sections/407%20Soldering.html) - reference material on solder joint quality and mechanical wire support.
