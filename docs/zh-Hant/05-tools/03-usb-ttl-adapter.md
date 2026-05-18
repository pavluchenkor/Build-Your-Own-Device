# USB-TTL

USB-TTL適配器或USB-UART適配器，讓你的電腦通過USB與微控制器通過UART通信。

你需要它用於：

- 刷新某些板；
- 讀取日誌；
- 調試UART通信；
- 配置模組；
- 當常規USB不工作時恢復板；
- 連接到沒有內置USB-UART的設備。

常見的適配器使用CH340、CP2102、FT232等芯片。

## USB-TTL或USB-UART

消費者描述通常說USB-TTL。

從技術上講，它通常意味著具有TTL邏輯電平的USB-UART適配器。

主要的事情是理解：

- USB側連接到電腦；
- UART側連接到微控制器；
- 適配器不是所有板的程序員；
- 如果你需要通過SWD刷新STM32，適配器不會替代ST-Link。

## 主要引腳

通常有：

- `GND`；
- `TX`；
- `RX`；
- `VCC`或`3V3`/`5V`；
- 有時`DTR`；
- 有時`CTS`、`RTS`。

最小通信：

- `GND`；
- `TX`；
- `RX`。

只有在你確定適配器應該為板供電時，才連接電源。

## TX和RX是交叉連接

UART連接如下：

```text
adapter TX -> board RX
adapter RX -> board TX
adapter GND -> board GND
```

`TX`是發送。

`RX`是接收。

一個設備的發送器必須連接到另一個的接收器。

如果你連接`TX`到`TX`，通信通常無法進行。

![UART連接中的交叉連接TX/RX](../../../img/02-controllers/06-uart-tx-rx-crossover.png)

*Source: [SparkFun Electronics](https://learn.sparkfun.com/tutorials/serial-communication/all), CC BY-SA 4.0*

## 公共接地

適配器`GND`和板`GND`必須連接。

沒有公共接地，UART可能無法工作或不穩定。

即使板由單獨的電源供電，接地仍然需要作為公共信號電平。

## 3.3V和5V邏輯電平

這是最重要的要點之一。

適配器可以工作的邏輯：

- `3.3V`；
- `5V`；
- 可切換`3.3V/5V`。

許多現代板和模組使用3.3V邏輯：ESP32、RP2040、許多STM32。

如果你將5V UART信號應用於3.3V輸入，你可能會損壞引腳或整個板。

連接前，驗證：

- 板使用什麼邏輯電平；
- 適配器使用什麼邏輯電平；
- 3.3V/5V跳線做什麼；
- 跳線是否只改變`VCC`電源或也改變`TX/RX`電平。

某些適配器提供5V電源但3.3V邏輯信號。其他的同時改變電源和電平。檢查特定適配器文檔。

## 來自適配器的電源

你不總是需要連接`VCC`。

通常，只連接是更安全的：

- `GND`；
- `TX`；
- `RX`。

從其正常來源為板供電。

你可以連接適配器的`VCC`，如果：

- 板額定為該電壓；
- 板電流在適配器能力範圍內；
- 同時沒有其他電源；
- 板文檔允許通過此引腳供電。

一個危險的錯誤是同時從USB-UART適配器和單獨的電源供電，導致源衝突。

## DTR和自動重置

某些板使用`DTR`進行刷新期間的自動重置。

例如，Arduino Pro Mini和類似的板可以通過電容器使用DTR進行自動重置。

如果刷新不會自動啟動，可能是因為：

- DTR未連接；
- 需要手動重置；
- 選擇了錯誤的適配器；
- 選擇了錯誤的引導加載程序；
- IDE中的速度或板選擇不正確。

對於簡單的日誌閱讀，DTR通常不需要。

## 如何檢查適配器是否對系統可見

在macOS和Linux上，適配器通常在`/dev`中显示为設備。

示例：

```bash
ls /dev/tty.*
ls /dev/cu.*
ls /dev/ttyUSB*
ls /dev/ttyACM*
```

在Windows上，它显示为`COM`端口。

如果端口未显示：

- 檢查USB電纜；
- 嘗試不同的USB端口；
- 檢查驅動程序；
- 驗證它不只是一根充電電纜；
- 查看適配器上的芯片：CH340、CP2102、FT232。

便宜的適配器有時需要單獨的驅動程序，尤其是在Windows上。

## 環路測試

檢查適配器的簡單方法：

1. 連接適配器的`TX`和`RX`。
2. 打開序列終端。
3. 選擇端口和速度。
4. 輸入文本。

如果你輸入的字符返回，適配器和端口可能工作。

測試後，移除`TX`和`RX`之間的跳線。

## 常見錯誤

- `TX`連接到`TX`，`RX`到`RX`；
- 忘記公共`GND`；
- 為3.3V板選擇了5V電平；
- 連接了`VCC`，儘管板已由單獨供電；
- USB電纜是充電專用；
- CH340/CP210x/FTDI驅動未安裝；
- 選擇了錯誤的COM端口；
- UART速度不匹配；
- 期望USB-UART通過SWD刷新STM32；
- 混淆了刷新期間的啟動模式或重置。

## 要點

- USB-UART適配器是電腦和板之間UART通信所需的。
- 最小通信：`GND`、`TX`、`RX`。
- 適配器`TX`進入板`RX`，適配器`RX`進入板`TX`。
- 連接前檢查3.3V/5V邏輯電平。
- `VCC`僅在你絕對需要適配器的電源時才連接。
- 如果適配器不可見，檢查電纜、驅動程序和USB端口。

## 參考資料

- [SparkFun: Serial Basic Hookup Guide](https://learn.sparkfun.com/tutorials/serial-basic-hookup-guide) - USB轉序列適配器、TX/RX/GND、VCC、DTR和3.3V/5V切換。
- [SparkFun: Serial Basic CH340C Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide/serial-basic-overview) - 現代CH340C USB-UART適配器、引腳、LED和電壓選擇。
- [SparkFun: Serial Communication](https://learn.sparkfun.com/tutorials/serial-communication) - UART基礎、TX/RX和序列通信。
- [Silicon Labs: CP210x USB to UART Bridge VCP Drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) - 官方CP210x虛擬COM端口驅動程序。
- [Adafruit FTDI TTL-232 USB Type C Cable](https://www.adafruit.com/product/4364) - 具有5V電源和3.3V邏輯的電纜示例，顯示為什麼需要單獨讀取電源和信號電平。
