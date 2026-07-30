---
title: "idryer-coreでのファームウェア開始：最初の起動とポータルバインディング"
description: "idryer-coreライブラリでPlatformIOプロジェクトを作成：platformio.ini、secrets.h、デバイス設定、ESP32最初のフラッシュ、iDryerポータルへのバインディング。"
---

# コアでのファームウェア開始

このページでは、ファームウェアプロジェクトを作成し、ESP32をポータルのオンライン状態に進め、ネットワーク部が機能していることを確認します。センサーと加熱ロジックは次のステップで追加します。

アプローチは`iDryer::Link`ファサードに基づいています。単一の`iDryer::Config`構造でデバイスを説明し、`link.begin()`と`link.loop()`を呼び出します。すべてのネットワーク接続はコアが自分で行います。

## 1. ツールを準備する

必要なもの：

- VS CodeとPlatformIOエクステンション；
- USBケーブル；
- Wi-Fi`2.4 GHz`ネットワーク（ESP32は5 GHzのみのネットワークで動作しません）。

コントローラーファームウェアとボードへの入り方について - [コントローラーファームウェア](../02-controllers/11-flashing-controller.md)。

## 2. プロジェクトを作成する

PlatformIOのプロジェクトは固定構造を持つフォルダーです。プロジェクトフォルダを作成（例`my-cabinet`）し、VS Codeで開きます。内部には次のファイルが必要です：

```text
my-cabinet/
├── platformio.ini        # ビルド設定（ステップ4で入力）
├── include/
│   └── secrets.h         # Wi-Fiログインとパスワード（ステップ3）
├── lib/
│   └── idryer-core/      # コアライブラリ（シムリンクまたはコピー）
└── src/
    └── main.cpp          # デバイスコード：Config + setup() + loop()
```

以下のコードのすべてのフラグメントは、正確にこれらのファイルに配置されます。各ステップは、どちらにあるかを示します。フォルダ`include/`、`lib/`、`src/`がない場合は、手動で作成してください。

`idryer-core`ライブラリを`lib/`に配置します。PlatformIOはそこから自動的にライブラリを見つけます。最も簡単な方法は、ダウンロードしたライブラリへのシムリンクを作成することです：

```bash
ln -s /path/to/idryer-core lib/idryer-core
```

これはメニュー生成（章6）にも必要です。フックは`lib/idryer-core/`内でジェネレーターを探します。

## 3. secrets.hを作成する

ライブラリから`secrets.h.example`の例をプロジェクトの`include/secrets.h`にコピーし、ネットワークデータを指定してください：

```cpp
#define WIFI_SSID      "your-ssid"
#define WIFI_PASSWORD  "your-password"
```

パスワードがリポジトリに入らないように、`include/secrets.h`を`.gitignore`に追加してください。

## 4. platformio.iniを設定する

プロジェクトのルート内の`platformio.ini`を入力してください：

```ini
[env:cabinet]
platform    = espressif32
framework   = arduino
board       = esp32-c3-devkitm-1

lib_deps =
    bblanchon/ArduinoJson @ ^6.21.0
    knolleary/PubSubClient
    densaugeo/base64 @ ^1.4.0
    links2004/WebSockets @ ^2.4.0
    https://github.com/jnthas/Improv-WiFi-Library.git

build_flags =
    -DIDRYER_API_BASE='"https://portal.idryer.org/api"'
    -DMQTT_BROKER='"mqtt.idryer.org"'
    -DMQTT_PORT=8883
    -DMQTT_USE_TLS=1
```

`board`を自分のボード（例えば、`esp32-s3-devkitc-1`）に置き換えます。`lib_deps`で`idryer-core`を指定する必要はありません。それは`lib/`（ステップ2）にあります。

!!! note "これらすべての依存関係が必要な理由"
    `ArduinoJson`、`PubSubClient`、`base64`、`WebSockets`、`Improv-WiFi-Library`は`idryer-core`ライブラリ自体（MQTT、LAN WebSocket アクセス、Wi-Fi プロビジョニング）に必要です。これらのいずれかなしで、ビルドは`... .h: No such file`のようなエラーで失敗します。`MQTT_BROKER`と`MQTT_PORT`フラグも必須です。それらがなければ、コアはコンパイルされません（`'MQTT_BROKER' was not declared`）。

## 5. Configでデバイスを説明する

すべての作業は1つのファイルで行われます。 - `src/main.cpp`。それを開き、このステップ以下のコードを書きます。

`iDryer::Config`はデバイスのパスポートです。フラグ`has*`はポータルに何があるかを伝え、発行されるテレメトリーフィールドを決定します。

ファイルの先頭`src/main.cpp`に加温シャフト用：

```cpp
#include <iDryer.h>

static const iDryer::Config CFG = {
    .deviceType        = iDryer::DeviceType::Dryer,
    .unitsCount        = 1,
    // ペリフェリー：
    .hasHeater         = true,    // 制御された加熱器
    .hasFan            = true,    // ファン
    .hasAirTemp        = true,    // 空気温度（SHT31）
    .hasAirHumidity    = true,    // 空気湿度（SHT31）
    .hasHeaterTemp     = true,    // 加熱器温度（温度計）
    // 自動発行期間：
    .telemetryPeriodMs = 5000,
    .statusPeriodMs    = 10000,
    // ポータル識別：
    .hardwareVersion   = "1.0",
    .firmwareVersion   = "0.1.0",
    .model             = "DIY Storage Cabinet",
};

static iDryer::Link s_link(CFG);
```

!!! note "has*フラグはポータルとの契約です"
    対応するフラグが`false`であるテレメトリーフィールドは発行されません。例えば、`hasAirHumidity = true`がなければ、湿度はコード内に書き込まれても、クラウドに行きません。物理的にデバイスに含まれているもののみを有効にしてください。

コンポーネントとフラグのリスト - [システムコンポーネント](02-bom.md)。

## 6. 最小限のメイン

同じファイルの`Config`ブロックの後、`setup()`と`loop()`関数を追加します。最初の起動では、リンクを初期化し、その中にループするだけで十分です：

```cpp
void setup() {
    Serial.begin(115200);
    s_link.begin();
}

void loop() {
    s_link.loop();
}
```

これは、デバイスがWi-Fiに接続し、ポータルに移動するのに十分です。センサーは[センサー](05-sensors.md)のステップで追加します。

### この章の後の完全な`src/main.cpp`

上記の両方のブロックを1つのファイルに組み合わせます。これは現在のステップの完全な`src/main.cpp`です：

```cpp
#include <iDryer.h>

static const iDryer::Config CFG = {
    .deviceType        = iDryer::DeviceType::Dryer,
    .unitsCount        = 1,
    .hasHeater         = true,
    .hasFan            = true,
    .hasAirTemp        = true,
    .hasAirHumidity    = true,
    .hasHeaterTemp     = true,
    .telemetryPeriodMs = 5000,
    .statusPeriodMs    = 10000,
    .hardwareVersion   = "1.0",
    .firmwareVersion   = "0.1.0",
    .model             = "DIY Storage Cabinet",
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

前の章は、**何を追加するか**と**変更後の完全な`src/main.cpp`**を示しているので、常に全体像が見えます。散在するピースではなく。

## 7. フラッシュ

```bash
pio run -e cabinet -t upload
```

## 8. シリアルモニターを開く

```bash
pio device monitor -b 115200
```

ログの予想される順序：

```text
[CLOUD] Connecting to WiFi...
[CLOUD] WiFi connected, IP: 192.168.1.42
[CLOUD] Provisioning device...
[CLOUD] PIN: 1234567 (expires in 600s)
```

デバイスが`PIN: ...`の行で停止した場合、それは正常です。バインディングに進みます。

## 9. デバイスをポータルにバインドする

1. [portal.idryer.org](https://portal.idryer.org/)を開きます。
2. **デバイスを追加**セクションに進みます。
3. シリアルモニターからPINを入力します。

バインディングの後、デバイスは`Online`ステータスに移動します。ログに表示されます：

```text
[CLOUD] Device claimed!
[CLOUD] MQTT connected!
```

## 結果の確認

このステップで、デバイスはポータルでオンラインである必要があります。センサーからのデータはまだありません。それは予想されています。デバイスが接続していない場合：

- ネットワークが`2.4 GHz`で、`secrets.h`のパスワードが正しいことを確認してください；
- ESP32の電力を確認してください（Wi-Fi開始時の電圧低下は一般的な再起動原因です）；
- [電力エラー](../08-common-mistakes/02-power-mistakes.md)と[コントローラーエラー](../08-common-mistakes/04-controller-mistakes.md)を参照してください。

## 次のステップ

ネットワーク部が動作しています。[センサー](05-sensors.md)に進んでください：SHT31と温度計を接続し、ポータルにデータを表示します。
