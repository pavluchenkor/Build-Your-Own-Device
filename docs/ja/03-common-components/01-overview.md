# 一般的なコンポーネント

一般的なコンポーネントは、iDryer のようなデバイスまたは 3D プリンター周辺機器を組み立てる際に最も頻繁に遭遇する部品とモジュールです。

このセクションの目的:

このセクションは、組立時に実際に手で持つ部品のリファレンスとして機能します。

ここで深い電子工学の知識は不要です。主な目標は、以下を理解するのを助けることです:

- このコンポーネントが何であるか;
- それなぜ必要か;
- 通常どのように接続されているか;
- それを何で置き換えることができるか;
- 購入時に重要なパラメータは何か;
- 最初の接続で何がほとんど壊れるか。

各ページの形式:

- それが何であるか;
- iDryer および 3D プリンター周辺機器でどこで使用されているか;
- 典型的な接続がどのようなものか;
- 重要な特性;
- 典型的な間違い;
- 購入前の簡単なチェックリスト。

提案されたファイル:

- `02-heaters.md` - ヒーター: PTC、シリコンパッド、カートリッジ、12V/24V/110-230V AC。
- `03-fans.md` - ファン: 2ピン、3ピン、4ピン PWM、電圧、電流、ノイズ、気流。
- `04-thermistors.md` - サーミスタ: NTC 100K、ルックアップテーブル、取り付け、オープン/短絡。
- `05-led-strips.md` - LED ストリップ: 5V/12V/24V、通常およびアドレス指定可能、メートルあたりの電流。
- `06-servo-motors.md` - サーボモーター: 電力、信号、角度、ピーク電流。
- `07-load-cells.md` - ロードセル: HX711、キャリブレーション、機械的取り付け。
- `08-oled-display.md` - OLED: I2C/SPI、アドレス、電力、必要な場合。
- `09-touchscreen.md` - TFT/タッチ: UART/SPI/HDMI、電力、互換性。
- `10-rfid-and-nfc.md` - RFID/NFC: カード、タグ、周波数、接続。

## 参考資料

- [Klipper Configuration Reference](https://www.klipper3d.org/Config_Reference.html) - 設定内のヒーター、ファン、温度センサー、サーボモーター、ディスプレイに関する公式 Klipper セクション。
- [DigiKey: Selecting A Fan](https://www.digikey.com/en/articles/selecting-a-fan) - 気流、静圧、ハウジング抵抗、熱的タスク別の実用的なファン選択。
- [Adafruit: MOSFET Driver](https://learn.adafruit.com/adafruit-mosfet-driver) - 高電力ロードが GPIO に直接接続されていない理由と、なぜパワースイッチが必要か。
- [SparkFun: Load Cell Amplifier HX711 Breakout Hookup Guide](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide) - ロードセル、HX711、電力、信号ワイヤ、キャリブレーションの例。
- [Adafruit: PN532 RFID/NFC Breakout Wiring](https://learn.adafruit.com/adafruit-pn532-rfid-nfc/breakout-wiring) - 電力、ロジックレベル、選択されたインターフェースを事前にチェックする必要があるコンポーネントの例。

## 関連項目

- [ヒーター](02-heaters.md) - 最もリスクの高いロードタイプ: 電力、温度、SSR/MOSFET、独立した保護。
- [ファン](03-fans.md) - 気流、静圧、2ピン/3ピン/4ピン、電力。
- [サーミスタ](04-thermistors.md) - ヒーターフィードバックの基礎となる温度センサー。
- [ファンの接続](../06-practical-guides/01-connecting-fan.md) - パワースイッチを通じたコンポーネント接続の実用的な例。
- [ヒーターおよび SSR エラー](../08-common-mistakes/05-heater-ssr-mistakes.md) - 高電力とメイン負荷の一般的な間違い。
