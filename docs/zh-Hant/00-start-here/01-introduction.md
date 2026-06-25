---
title: "从哪里开始制作耗材干燥箱"
description: "第一个项目的清晰路线：如何规划耗材干燥箱，选择电子、电加热、气流、外壳，并避免安全遗漏。"
---

# 从哪里开始制作耗材干燥箱

如果你想制作自己的耗材干燥箱、打印机加热腔或独立加热模块，请从这里开始。本页说明文档的阅读顺序，以及购买元件前需要先决定的问题。

您已經在3D打印機上列印，並想製造一個絲材烘乾機。但當您打開電路圖時，問題立即出現：選擇哪個電源、接地應該在哪裡、MOSFET或SSR、為什麼需要散熱片。本部分逐步回答這些問題——從第一次電流計算到工作正常的設備。

完成本部分後，您將了解您要構建什麼、為什麼採用這種方式、可能存在的危險在哪裡，以及如何在通電前檢查設備。

部分逐漸從簡單的概念引導至實際結果。

這裡的路徑從簡單到複雜：

1. 首先理解電力、電流、負載和基本安全。
2. 然後確定存在哪些控制器以及選擇哪個。
3. 然後理解基本元件：加熱器、風扇、感測器、顯示器、RFID和負載單元格。
4. 然後學習使用最少工具：萬用表、USB-UART、焊槍、壓線鉗。
5. 然後進行實用連接。
6. 然後考慮外殼和3D列印件。
7. 最後，準備一份常見錯誤清單和診斷檢查清單。

主要想法：

您不需要一次理解所有電子知識。逐步進行，每次理解下一個小步驟就足夠了。

本部分應提供的內容：

- 對低電壓`12V`/`24V DC`電路如何不同於商用電源`110-230V AC`的理解；
- 粗略計算負載電流的能力；
- 理解何時需要MOSFET、SSR或繼電器；
- 理解ESP32、Arduino、RP2040和STM32在實際中的區別；
- 理解為什麼對於Klipper MCU，最好查看RP2040或STM32；
- 對感測器、風扇、加熱器和顯示器的基本理解；
- 最少的萬用表診斷技能；
- 理解哪些列印件可以放在熱源附近；
- 更好不重複的錯誤列表。

本部分不做的事：

- 在使用`110-230V AC`時不能取代電工；
- 不教授深層電路設計；
- 不試圖解釋所有物理；
- 不允許在不理解安全的情況下組裝危險設備。

如何閱讀：

- 如果主題是新的——按順序進行；
- 如果您已經製造過設備——作為參考打開所需部分；
- 如果設備不工作——首先查看`08-common-mistakes`；
- 如果您使用`110-230V AC`——首先閱讀與安全、SSR、電線、端子和保護接地相關的所有內容。

## 參考資料

- [SparkFun: Voltage, Current, Resistance, and Ohm's Law](https://learn.sparkfun.com/tutorials/voltage-current-resistance-and-ohms-law) - 電壓、電流、電阻、閉路和歐姆定律的基本概念。
- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/all) - 初始診斷的實用順序：電力、連接、極性、焊點、電纜和電壓降。
- [Fluke: How to Measure Resistance with a Digital Multimeter](https://www.fluke.com/en-us/learn/best-practices/test-tools-basics/digital-multimeters/how-to-measure-resistance) - 為什麼在斷電狀態下進行電阻測量，以及為什麼需要萬用表檢查元件。
- [OSHA: Electrical Incidents - Grounding](https://www.osha.gov/etools/construction/electrical-incidents/grounding) - 為什麼需要保護接地，以及為什麼使用商用電壓需要單獨的安全規範。

## 另請參閱

- [Load calculation 24V](../01-electronics-basics/01-load-calculation-24v.md) - 關於電壓、電流、電力和電源容量的第一個實用主題。
- [Common components](../03-common-components/01-overview.md) - 在簡單設備中最常見的零件地圖。
- [Tools](../05-tools/01-overview.md) - 檢查、閃存、焊接和診斷所需的內容。
- [Practical guides](../06-practical-guides/01-connecting-fan.md) - 通過控制器進行第一次安全負載連接的例子。
- 常見錯誤 - 當設備不開啟、發熱、發出噪音或行為不穩定時要查看的內容。
