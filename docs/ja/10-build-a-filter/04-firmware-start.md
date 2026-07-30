---
title: "スマートフィルター: ファームウェア開始とポータルへのバインディング"
description: "フィルターのファームウェアスケルトンをidryer-coreで: 非標準型デバイスのConfig、初回起動、PINでのアカウントバインディング。"
---

# ファームウェア開始

プロジェクトのひな型は[キャビネットサンプルの章](../09-build-a-device/04-firmware-start.md)と全く同じです: PlatformIO、`secrets.h`、`lib/`内の`idryer-core`、同じ`platformio.ini`（環境名を`filter`に変えるだけ）。ここでは異なる部分だけを説明します。

## Config: 非標準型デバイス

フィルターには、ヒーターもエコシステム辞書のクライメートセンサーもありません。辞書スキルの中でこのデバイスが持つのはファンだけです。`src/main.cpp`内:

```cpp
#include <iDryer.h>

static const iDryer::Config CFG = {
    .deviceType        = iDryer::DeviceType::Unknown, // 非標準デバイス
    .unitsCount        = 1,
    // 周辺機器: エコシステム辞書から「ファン」だけあります。
    .hasFan            = true,
    // 自動公開期間:
    .telemetryPeriodMs = 5000,
    .statusPeriodMs    = 10000,
    // ポータル上の識別:
    .hardwareVersion   = "1.0",
    .firmwareVersion   = "0.1.0",
    .model             = "DIY Air Filter",
};

static iDryer::Link s_link(CFG);

void setup() {
    Serial.begin(115200);
    s_link.begin();
}

void loop() {
    s_link.loop();
}
```

!!! note "DeviceType::Unknown — これで問題ありません"
    `Unknown`型は「ポータルがこのデバイス種別を知らない」という意味です。以前はこれが問題でした: 未知の型にはポータル側にカードがありませんでした。現在はこれが正規の手順です: デバイスのインターフェースはcard manifestが完全に記述し（[第6章](06-card.md)）、ポータルはそれに基づいてカードを構築します。型（deviceType）が必要なのは、専用カードを持つiDryer純正デバイスだけです。

`hasFan = true`フラグを設定するだけで、テレメトリの`fanStatus`フィールド、カード上の「ファン」セル、マニフェスト内のエンティティがすべて自動的に追加されます — エコシステム辞書の機能です。

## VOCセンサーはConfigにない — それで正しい

注意してください: `Config`には「hasVoc」というフラグはありません。`has*`辞書はエコシステムが知っている周辺機器を記述するものです。独自センサーは辞書経由ではなく、2つの別のメカニズムで追加します: テレメトリに独自フィールドを書き込み、card manifestで宣言する — 次の2章がその内容です。これがこのアプローチの本質です: 新しいデバイスごとに辞書を拡張する必要はありません。

## 初回起動と登録

この手順はキャビネットサンプルと同じです:

1. ボードに書き込み、シリアルモニターを開きます。
2. デバイスがWi-Fiに接続（`secrets.h`の設定を使用）、登録完了後にPINを表示します:
   ```text
   [CLOUD] PIN: 1234567 (expires in 600s)
   ```
3. [ポータル](https://portal.idryer.org/) で「デバイスを追加」→ PINを入力します。
4. 登録完了後、ログに`Device claimed!`が表示され、デバイスは`Online`状態になります。

バインディングの詳細、Wi-Fiエラーへの対処、再バインディング方法については [キャビネットサンプルの章](../09-build-a-device/04-firmware-start.md) を参照してください。

ポータルにデバイスが表示されますが、カードはまだほぼ空です — データがないためです。センサーの接続に進みましょう。
