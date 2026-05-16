# 常見元件

常見元件是在組裝 iDryer 類設備或 3D 印表機周邊設備時最常遇到的零件和模組。

本部分的目的：

本部分用作組裝時實際持有的零件的參考。

這裡不需要深厚的電子學知識。主要目標是幫助你理解：

- 這個元件是什麼；
- 為什麼你需要它；
- 它通常如何連接；
- 你可以用什麼替代它；
- 購買時哪些參數很重要；
- 第一次連接時最容易損壞的地方。

每個頁面的格式：

- 它是什麼；
- 它在 iDryer 和 3D 印表機周邊設備中的用途；
- 典型的連接方式；
- 重要特性；
- 常見錯誤；
- 購買前的簡短檢查清單。

提議的檔案：

- `02-heaters.md` - 加熱器：PTC、矽膠墊、筒狀加熱器、12V/24V/110-230V AC。
- `03-fans.md` - 風扇：2 腳、3 腳、4 腳 PWM、電壓、電流、噪聲、氣流。
- `04-thermistors.md` - 溫度計：NTC 100K、查詢表、安裝、開路/短路。
- `05-led-strips.md` - LED 燈條：5V/12V/24V、常規和可定址、每米電流。
- `06-servo-motors.md` - 伺服馬達：電源、信號、角度、峰值電流。
- `07-load-cells.md` - 負載傳感器：HX711、校準、機械安裝。
- `08-oled-display.md` - OLED：I2C/SPI、位址、電源、何時需要。
- `09-touchscreen.md` - TFT/觸控：UART/SPI/HDMI、電源、相容性。
- `10-rfid-and-nfc.md` - RFID/NFC：卡、標籤、頻率、連接。

## 參考資料

- [Klipper Configuration Reference](https://www.klipper3d.org/Config_Reference.html) - 官方 Klipper 關於加熱器、風扇、溫度感應器、伺服馬達和配置中的顯示器部分。
- [DigiKey: Selecting A Fan](https://www.digikey.com/en/articles/selecting-a-fan) - 按氣流、靜壓、外殼阻力和熱任務的實務風扇選擇。
- [Adafruit: MOSFET Driver](https://learn.adafruit.com/adafruit-mosfet-driver) - 為什麼高功率負載不直接連接到 GPIO 以及為什麼你需要電源開關。
- [SparkFun: Load Cell Amplifier HX711 Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide) - 負載傳感器、HX711、電源、信號線和校準的示例。
- [Adafruit: PN532 RFID/NFC Breakout Wiring](https://learn.adafruit.com/adafruit-pn532-rfid-nfc/breakout-wiring) - 元件示例，你需要事先檢查電源、邏輯等級和選擇的介面。

## 另請參閱

- [加熱器](02-heaters.md) - 最危險的負載類型：電源、溫度、SSR/MOSFET 和獨立保護。
- [風扇](03-fans.md) - 氣流、靜壓、2 腳/3 腳/4 腳和電源。
- [溫度計](04-thermistors.md) - 作為加熱器反饋基礎的溫度感應器。
- [連接風扇](../06-practical-guides/01-connecting-fan.md) - 透過電源開關連接元件的實務示例。
- [加熱器和 SSR 錯誤](../08-common-mistakes/05-heater-ssr-mistakes.md) - 高功率和市電負載的常見錯誤。
