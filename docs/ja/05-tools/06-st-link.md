# ST-Link

ST-Linkはプログラマーであり、STM32マイクロコントローラーのデバッガーです。

単純なデバイスの文脈では、以下に使用されます。

- STM32ボードをフラッシュする
- 不正なフラッシュ後のボード回復
- SWDを介してチップに接続する
- メモリを消去する
- マイクロコントローラーが見えることを確認する
- 時々プログラムをデバッグする

ST-Linkはすべてのボードで必要ではありません。ESP32、RP2040、Arduino は通常別の方法をフラッシュします。

## SWDとは何か

SWDは `Serial Wire Debug` です。

これはARMマイクロコントローラー、一般的にSTM32で使用されるデバッグおよびフラッシュインターフェースです。

基本的な接続の場合、通常以下が必要です。

- `SWDIO`
- `SWCLK`
- `GND`
- 時々 `NRST`
- 時々 `3.3V` または `VTref` をターゲット参照電圧として

重要。ST-Link上の `3.3V` は常に「ここからボードに電力を供給する」を意味するとは限りません。多くの場合、ST-Linkはターゲットボード電圧を見て、信号レベルを理解する必要があります。

## 最小接続

通常、接続します。

```text
ST-Link SWDIO -> board SWDIO
ST-Link SWCLK -> board SWCLK
ST-Link GND   -> board GND
ST-Link NRST  -> board NRST if reset is needed
ST-Link 3.3V/VTref -> 3.3V target if required by specific ST-Link
```

STM32ボードは通常、通常の電源またはUSBから電力を供給されます。

接続する前に、特定のST-Linkとボードのドキュメンテーションを確認してください。

![STM32用のNucleauボードに組み込まれたST-Linkデバッガー](../../../img/02-controllers/04-stm32-nucleo-boards.jpg)

*出典: [ウィキメディア・コモンズ](https://commons.wikimedia.org/wiki/File:STM32_Nucleo_boards.jpg)、Avandalen、CC BY-SA 4.0*

## ボード電力

最も一般的な混乱。ボードはST-Linkまたは別々で電力を供給されていますか？

オプション。

1. ボードは別々に電力を供給し、ST-LinkはすべてのSWDとGNDに接続します。
2. ST-Link は小さなターゲットボードに3.3Vを提供します。実際にこれに対して設計されている場合。
3. ST-Link は `VTref` を読んでいますが、ボードに電力を供給してはいけません。

複数の電力源を盲目的に接続することはできません。

ボードが既にUSBまたは電源で電力を供給されている場合は、ST-Linkからの電力を接続しないでください。回路図がそれを許可することが確実なまで。

## ST-LinkとDFUの違い

DFUは、利用可能な場合、USBブートローダーを介したフラッシュモードです。

ST-LinkはSWDを介してマイクロコントローラーで直接動作します。

ST-Linkは以下の場合に役立ちます。

- DFUは利用できません
- ブートローダーが破損されているか、使用されていない
- フラッシングが無効にされたUSB
- ボードは通常のフラッシュモードに入りません
- メモリをクリアする必要があります
- STM32アクセスを回復する必要があります

ただし、ボードがUSB/DFUまたはSDカードを通じて正常にフラッシュされる場合、ST-Linkは必要でないかもしれません。

## リセット下で接続

時々、ファームウェアはSWDアクセスを破ります。

例えば。

- SWDピンは通常のGPIOとして使用されます
- ファームウェアはすぐにチップを眠らせます
- コードは起動直後にハングします
- クロック/電力モードが正しく設定されていない

そのような場合、 `Connect under reset` モードが役立ちます。

アイデア。ST-Linkはリセットを保持し、悪いファームウェアが実行される前に接続しようとします。

これはしばしば `NRST` を接続する必要があります。

## ST-Linkがボードを見るかどうかを知る方法

STM32CubeProgrammerまたは同様のツールでは、通常、以下が表示されます。

- ST-Linkが接続されているかどうか
- ターゲットが見つかるかどうか
- どのチップが検出されるか
- メモリを読むことができるかどうか
- フラッシュを消去できるかどうか

ST-Linkが USB デバイスとして見えるがターゲットが見つからない場合、問題はしばしばボード接続です。

- ターゲットボードに電力がない
- 共通の `GND` なし
- `SWDIO` と `SWCLK` が交換されている
- `VTref` が必要な場合は接続されていない
- SWD周波数が高すぎ
- チップがロックされている
- ファームウェアが接続を防ぐ
- `Connect under reset` が必要です

## SWD周波数

通信が不安定な場合は、SWD周波数を低減してみてください。

長いワイヤー、不十分なDupontジャンパー、または不安定なボードでは、高い周波数が接続に干渉することができます。

ボード回復の場合、遅く信頼できるが高速です。

## 一般的なエラー

- `GND` を忘れた
- `SWDIO` と `SWCLK` を交換
- ST-LinkとUSBから同時に電力を接続せずに回路図を理解
- ターゲットボードに電力を供給していない
- `Connect under reset` が必要な場合は `NRST` を接続していない
- SWD周波数が高すぎる
- ESP32またはRP2040をST-Linkでフラッシュしようとする
- ロックされたチップに接続しようとする
- 長い不十分な品質のワイヤーを使用する
- ST-Linkファームウェアを更新していないか、ドライバーがインストールされていない

## できないこと

できません。

- 確認なしに5Vを3.3V STM32ボードに適用
- 複数の電力源を盲目的に接続
- 安全な隔離と囲いなしに商用電圧下のボードにST-Linkを接続
- 短絡のリスクがある場合、電力をオンにしながらSWDワイヤーを変更
- クローンST-Linkがオリジナルと同じピンアウトを持つと想定する

クローンST-Linkのピンアウトが異なる場合があります。常に特定のアダプターのマーキングを確認してください。

## 重要な点

- ST-LinkはSWDを通じてSTM32に必要です
- 最小。`SWDIO`、`SWCLK`、`GND`、時々 `NRST` と `VTref`
- ボードは正しく電力を供給される必要がありますが、必ずしもST-Linkからではありません
- DFUとST-Linkは異なるフラッシング方法です
- `Connect under reset` は、不正なファームウェアの後のアクセスを回復するのに役立ちます
- ターゲットが見つからない場合、まず電源、`GND`、`SWDIO/SWCLK`、`NRST`、およびSWD周波数を確認してください

## 参考資料

- [STMicroelectronics: UM1075 ST-LINK/V2 User Manual](https://www.st.com/resource/en/user_manual/dm00026748-st-link-v2-in-circuit-debugger-programmer-for-stm8-and-stm32-stmicroelectronics.pdf) - 公式ST-LINK/V2マニュアル、SWD/JTAGピン、ターゲットVCCとGND
- [STMicroelectronics: UM2237 STM32CubeProgrammer User Manual](https://www.st.com/resource/en/user_manual/um2237-stm32cubeprogrammer-software-description-stmicroelectronics.pdf) - ST-LINK接続モード。通常、リセット下で接続、ホットプラグを含む
- [ST Wiki: ST-LINK](https://wiki.st.com/stm32mpu/wiki/ST-LINK) - STM32/STM8用ハードウェアプローブとしてのST-LINKの概要とサポートされるプロトコル
- [Klipper: Installation](https://www.klipper3d.org/Installation.html) - Klipperの一般的なMCU準備プロセス
- [STMicroelectronics: STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) - ST-LINK/SWD、UART、USB DFU、SPI、I2C、CAN bootloaders を介してSTM32をフラッシュするための公式STツール
