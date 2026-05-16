# SPIインターフェース

SPI は、コントローラと周辺機器の間の高速シリアル通信インターフェースです。展開形: `Serial Peripheral Interface`。

SPI は、I2C よりも高速なデータ転送が必要な場合、またはデバイスが SPI 向けに設計されている場合によく使用されます: ディスプレイ、SD カード、RFID モジュール、センサー、ドライバー、メモリチップなど。

## SPI の使用場所

3D プリンターや iDryer 類似デバイスでは、SPI は次の場面で登場することがあります:

- RC522 などの RFID/NFC モジュール;
- OLED/TFT ディスプレイ;
- SD カード;
- 入力シェーパー用加速度センサー;
- TMC2130/TMC5160 などのステッピングドライバー;
- メモリチップ;
- ADC/DAC および拡張ボード;
- 一部のセンサーや専用モジュール。

SPI は通常 I2C より高速ですが、より多くのワイヤーと慎重なピン選択が必要です。

## 基本ライン

標準的な SPI では以下を使用します:

- `SCK` または `CLK` - クロック信号;
- `MOSI` - コントローラからデバイスへのデータ;
- `MISO` - デバイスからコントローラへのデータ;
- `CS`、`SS`、または `NSS` - 特定デバイスの選択;
- `GND` - 共通グランド;
- モジュール電源。

2 デバイス構成の図:

![SPI: basic exchange operation between master and slave device](../../../img/02-controllers/08-spi-basic-operation.png)

*出典: [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:SPI_basic_operation,_single_Main_%26_Sub.svg), Em3rgent0rdr, CC0 パブリックドメイン*

`SCK`、`MOSI`、`MISO` は複数のデバイスで共有できます。ただし、各デバイスには通常それぞれ独自の `CS` が必要です。

## アドレスの代わりに CS

I2C ではデバイスはアドレスで区別されます。SPI では通常アドレスはありません。コントローラは個別の `CS` ラインでデバイスを選択します。

例:

```text
SCK  -> common to all SPI devices
MOSI -> common
MISO -> common
CS1  -> RFID module
CS2  -> display
CS3  -> SD card
```

コントローラが RFID モジュールと通信したい場合は `CS1` をアクティブにします。ディスプレイと通信したい場合は `CS2` をアクティブにします。

多くの場合、`CS` はアクティブローです: 待機時にラインは `HIGH`、デバイスを選択するには `LOW` にします。ただし、これは技術データシートで確認する必要があります。

## MOSI/MISO と新しい名称

古くて非常に一般的な回路図では、名称は以下の通りです:

- `MOSI` - Master Out Slave In;
- `MISO` - Master In Slave Out;
- `SS` - Slave Select。

新しいドキュメントでは、中立的な名称が使われることがあります:

- `PICO` - Peripheral In Controller Out、MOSI に相当;
- `POCI` - Peripheral Out Controller In、MISO に相当;
- `CS` - Chip Select。

3D プリンター用電子機器では、`MOSI`、`MISO`、`SCK`、`CS` が依然として広く使われています。重要なのは信号の方向を理解し、特定のモジュールのピンアウトを確認することです。

## MISO が不要な場合

すべての SPI デバイスが実際にデータを送り返すわけではありません。

たとえば、シンプルなディスプレイはコマンドとピクセルを受信するだけの場合があります。その場合、`MISO` ラインがない、または未使用の場合があります。

ただし、データを読み取るデバイスには `MISO` が必要です:

- RFID モジュール;
- SD カード;
- センサー;
- 診断機能付きドライバー;
- メモリチップ。

モジュールが応答を返すはずなのに `MISO` が接続されていなかったり混同されていたりすると、初期化が失敗する場合があります。

## SPI の速度とモード

SPI には速度があります。I2C よりはるかに高速にできますが、すぐに最大値に設定する必要があるわけではありません。

動作に影響するのは:

- ワイヤーの長さ;
- グランドの品質;
- モジュールとそのデータシート;
- ノイズレベル;
- コントローラの周波数;
- 選択した SPI モード。

SPI モードはクロック極性とクロック位相のパラメーターによって設定されます: `CPOL` と `CPHA`。モード 0 が多く使われますが、常にそうとは限りません。モードが誤っている場合、デバイスが応答しないか、誤ったデータを返すことがあります。

既製のライブラリのほとんどでは、モードはすでに設定されています。ただし、特殊なモジュールを接続したり、低レベルの設定を記述したりする場合は、データシートを確認する必要があります。

## 3.3V と 5V

他のインターフェースと同様に、SPI は安全な電圧レベルを保証しません。

ESP32、RP2040、STM32、および多くの現代のモジュールは `3.3V` ロジックで動作します。Arduino Uno/Nano は多くの場合 `5V` を使用します。

接続前に確認してください:

- モジュールの電源;
- `SCK`、`MOSI`、`MISO`、`CS` のロジックレベル;
- レベル変換があるかどうか;
- モジュールが信号入力で `5V` を許容するかどうか;
- コントローラの入力が `5V` を許容するかどうか。

たとえば、RC522 は通常 `3.3V` の電源とロジックを必要とします。レベル変換なしで `5V` の Arduino に接続するのは好ましくありません。

## Klipper における SPI

Klipper では、SPI は TMC ドライバー、加速度センサー、一部のディスプレイやセンサーなど、さまざまなデバイスに使用されます。

設定には以下が含まれる場合があります:

- `cs_pin` - デバイス選択ピン;
- `spi_bus` - ハードウェア SPI バス;
- `spi_speed` - 速度 (Hz 単位);
- `spi_software_sclk_pin`;
- `spi_software_mosi_pin`;
- `spi_software_miso_pin`。

デバイスが追加の MCU に接続されている場合、ピンはその MCU に属している必要があります。他の Klipper セクションと同様に、推測よりも特定のボードのピンアウトが重要です。

おおまかなイメージ:

```ini
[some_spi_device]
cs_pin: chamber:gpio9
spi_software_sclk_pin: chamber:gpio10
spi_software_mosi_pin: chamber:gpio11
spi_software_miso_pin: chamber:gpio12
```

これは特定のデバイス向けの完成した設定ではなく、あくまで説明のためのものです: すべての SPI ピンは、モジュールが実際に接続されている MCU 上になければなりません。

## ワイヤー長と干渉

SPI は高速に動作できますが、長くて雑なケーブル配線は好みません。

実用的なルール:

- `SCK`、`MOSI`、`MISO`、`CS` は短く保つ;
- `GND` の近くに配線する;
- ヒーターやモータのワイヤーと並行して配線しない;
- エラーが発生した場合は `spi_speed` を下げる;
- 適切なコネクターを使用する;
- 理由なく SPI をプリンター全体に引き回さない;
- リモートノードには、CAN、UART/RS-485、またはモジュール近くに独立した MCU を選択することが多い。

`SCK` ラインは特に敏感です: クロック信号です。これが乱れると、すべての通信が不安定になる可能性があります。

## SPI と RC522

RC522 は、命名に混乱が生じやすい SPI モジュールの好例です。

多くの RC522 ボードでは、`SDA` ピンが実際には SPI の `SS`/`CS` として使用されます。これは I2C の `SDA` ではありません。

RC522 には通常以下が必要です:

- `3.3V`;
- `GND`;
- `SCK`;
- `MOSI`;
- `MISO`;
- `SDA`/`SS`/`CS`;
- `RST`;
- `IRQ` が必要な場合もありますが、シンプルなプロジェクトでは多くの場合使用されません。

詳細な配線図は実践的な記事にあります: [RFID リーダーの接続](../05-practical-guides/05-connecting-rfid-reader.md)。

## 接続前に確認すること

SPI モジュールを接続する前に確認してください:

- モジュールの電源;
- ロジックレベル;
- 特定のボードのピンアウト;
- `SCK`、`MOSI`、`MISO`、`CS` の位置;
- `RST`、`DC`、`IRQ`、またはその他のピンが必要かどうか;
- デバイスに割り当てられている `CS`;
- `CS` が他のモジュールと競合していないか;
- ハードウェア SPI またはソフトウェア SPI が必要かどうか;
- ドキュメントが推奨する速度;
- ファームウェアがこのモジュールをサポートしているかどうか。

## よくあるミス

- `MOSI` と `MISO` を混同した;
- `CS` を忘れた;
- 2 つのデバイスを 1 つの `CS` に接続した;
- 共通の `GND` を接続しなかった;
- `3.3V` の SPI モジュールに `5V` を印加した;
- RC522 の `SDA` を I2C の `SDA` と勘違いした;
- 速度を高く設定しすぎた;
- ワイヤーを長くしすぎた;
- モジュールを 1 つの MCU に接続したが、別の MCU のピンを指定した;
- SPI を負荷を駆動する電源インターフェースだと思った。

## まとめ

SPI はコントローラ近くのモジュール向けの高速インターフェースです。通常、`SCK`、`MOSI`、`MISO`、`CS`、電源、`GND` が必要です。

I2C との主な違い: SPI には通常アドレスがなく、各デバイスは個別の `CS` で選択されます。接続前に、ピンアウト、ロジックレベル、速度、ワイヤー長、ファームウェアのサポートを確認してください。

## 関連資料

- [SparkFun: Serial Peripheral Interface](https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi) - SPI の実践的な解説、データライン、新しい PICO/POCI の名称、基本的なデータ交換ロジック。
- [SparkFun: SPI Chip Select](https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi/chip-select-cs) - `CS` が必要な理由と複数の SPI デバイスの接続方法。
- [Adafruit: SPI Devices](https://learn.adafruit.com/circuitpython-basics-i2c-and-spi/spi-devices) - SPI と I2C の比較、個別の `CS`、速度、極性/位相、および制限事項。
- [DigiKey: SPI Simplifies Device Communication](https://www.digikey.com/en/articles/why-how-to-use-serial-peripheral-interface-simplify-connections-between-multiple-devices) - 複数の SPI デバイス接続のオプションと `CS` の役割。
- [Klipper Configuration Reference: Common SPI settings](https://www.klipper3d.org/Config_Reference.html) - Klipper における `spi_speed`、`spi_bus`、ソフトウェア SPI、`cs_pin` パラメーター。
