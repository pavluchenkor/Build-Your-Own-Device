# ツール

このセクションはツール収集に関するものではありません。

デバイスを安全に組立て、接続を検証し、推測なしで簡単なエラーを見つけるのに役立つ最小限のセットに関するものです。

iDryerおよび3Dプリンタの周りの自作デバイスでは、ツールは実践的なタスクに必要です：

- 電源供給に24Vが存在するかどうかを確認する
- プラスとマイナスが交換されているかどうかを理解する
- ワイヤの連続性をチェック
- サーミスタをテスト
- UARTシグナルが到達するかどうかを確認
- コントローラをフラッシュ
- 適切なコネクタを作成
- 電源低下を見つける
- ファンまたはヒータがオンにならない理由を理解する

## 最小セット

ほとんどの単純なビルドで、有用なツール：

- マルチメータ
- USB-UARTまたはUSB-TTLアダプタ
- はんだごて
- クリンピングツール
- ワイヤカッターとストリッパー
- 熱収縮チューブ
- 適切な端子とコネクタ
- STM32で作業する場合はST-Link
- より複雑な診断用のオシロスコープまたは周波数カウンタ付きマルチメータ

すべてを一度に購入する必要はありません。しかし、マルチメータと適切なワイヤツールは通常、すぐに回収します。

## Tools don't replace understanding

マルチメーターは主電源部分を安全にするものではありません。

はんだごてを使用しても、悪い回路図は修正されません。

プラスとマイナスを入れ替えればオシロスコープは不要です。

したがって、順序は次のとおりです。

1. 何を接続すべきかを理解します。
2. 電源を確認する。
3. 配線を確認する。
4. センサーと信号を確認します。
5. その後でのみ、複雑な問題を探します。

## このセクションの内容

- `02-multimeter.md` - DC 電圧、導通、抵抗、ヒューズの測定、および電流測定がより危険である理由。
- `03-usb-ttl-adapter.md` - USB-UART アダプター、TX/RX/GND、3.3V/5V ロジック レベル、フラッシュおよびログ。
- `04-soldering.md` - はんだ付けワイヤー、パッド、モジュール、冷はんだ接合部、熱収縮および張力緩和。
- `05-crimping-connectors.md` - Dupont、JST、フェルール、ファストン、端子、圧着品質チェック。
- `06-st-link.md` - ST-Link、STM32、SWD、フラッシュ失敗後のボードリカバリ。
- `07-oscilloscope.md` - PWM、UART、停電、ノイズ、および主電源電圧に関する重要な安全警告。

## きちんと買う価値のあるもの

節約すべきではないものもあります。

- 適切なプローブと導通モードを備えたマルチメーター。
- 温度制御付きはんだごて。
- 高品質のはんだとフラックス。
- 特定の端子用の圧着工具。
- 必要な電流の定格を備えたコネクタと端子。
- heat shrink tubing;
- 正しいゲージのワイヤー。

Poor crimping or weak terminals can cause more problems than bad firmware.

## できないこと

次のことはできません:

- 通電された回路の抵抗を測定します。
- 電圧を測定するのと同じ方法で電流を測定します。
- 安全性を理解せずにマルチメーターを 110 ～ 230V AC に接続します。
- 電源部分を「何らかの方法で」はんだ付けします。
- ヒーターにはデュポン社を使用。
- 電源が入っているときにワイヤを交換します。
- 電源部分はテーブルの上に開いたままにしておきます。
- ワイヤーが「保持」されていれば、接触は良好であると考えてください。

## 必需品

- マルチメーターは最初の診断ツールです。
- USB-UART は、ログ、フラッシュ、UART デバイスとの通信に必要です。
- はんだ付けと圧着は異なる作業であり、コネクタの場合は圧着の方が優れていることがよくあります。
- STM32 および SWD を使用する場合は、ST-Link が必要です。
- オシロスコープは誰もが必要とするわけではありませんが、信号、サグ、ノイズをすぐに表示します。
- 電源部品の場合、アセンブリの見た目よりも、接触品質、ワイヤゲージ、安全性が重要です。

## Reference materials

- [SparkFun: How to Use a Multimeter](https://learn.sparkfun.com/tutorials/how-to-use-a-multimeter/all) - multimeter basics: voltage, current, resistance, continuity.
- [SparkFun: Troubleshooting Tips](https://learn.sparkfun.com/tutorials/sparkfun-troubleshooting-tips/hardware-checks) - hardware checks for power, connections and heat.
- [SparkFun: Serial Communication](https://learn.sparkfun.com/tutorials/serial-communication) - UART and basic serial communication logic.
- [Adafruit: Guide to Excellent Soldering](https://learn.adafruit.com/adafruit-guide-excellent-soldering) - practical soldering guide and connection quality.
- [STMicroelectronics: ST-LINK/V2 User Manual](https://www.st.com/resource/en/user_manual/um1075-stlinkv2-incircuit-debuggerprogrammer-for-stm8-and-stm32-stmicroelectronics.pdf) - official ST-Link documentation and SWD/SWIM.
