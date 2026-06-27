---
title: "YAMLからのデバイスメニュー：NVSとポータルの設定"
description: "idryer-coreでのYAMLデバイスメニューの記述方法：目標温度とヒステリシスはNVSに保存され、iDryerポータルのウィジェットに表示されます。"
---

# YAMLからのメニュー

メニューは、デバイスの設定の集合です：目標温度、ヒステリシス、ファンのしきい値。`idryer-core`では、メニューは単一の`menu.yaml`ファイルで記述され、その後すべて - C++構造、不揮発メモリ（NVS）への保存、ポータルへの発行 - 自動的に生成されます。

これはコアの主要なブロックの1つです。設定保存コードを書かず、ポータルのフォーマットを発明しません。YAMLでパラメーターをリストするだけです。

## メニューの理由

前のステップの後、デバイスはセンサーを読みますが、すべてのしきい値はコードに「ハード」です。メニューは3つのタスクを一度に解決します：

- **保存**：値は再起動後に保持されます（NVS）；
- **ポータルからの制御**：各パラメーターはウィジェット（スライダー、スイッチ）になります；
- **単一の信頼できる情報源**：1つのファイルがメモリとインターフェースの両方を説明します。

## どのように機能するか

単一の`menu.yaml`ファイルはビルド中にジェネレーターを通過します：

```text
menu.yaml → (pio runビルド) → src/menu/内のC++ファイル + NVS + ポータル用JSON
```

`role:`フィールド付きのアイテムはポータルに表示され、ウィジェットとして表示されます。`role:`なしのアイテムはプライベート（内部ロジック用のみ）です。

!!! warning "生成されたファイルを編集しないでください"
    `menu_state.*`、`menu_bindings.*`、`menu_ids.h`などのファイルはジェネレーターによって作成されます。`menu.yaml`のみを編集してリビルドします。そうしないと、変更は上書きされます。

## ステップ1。テンプレートをコピーする

ライブラリにはメニューテンプレートがあります。プロジェクトにコピーします：

```bash
mkdir -p src/menu
cp path/to/idryer-core/menu/menu.template.yaml src/menu/menu.yaml
```

## ステップ2。ビルド時に生成を接続する

プロジェクト`iDryer-Storage`からサンプルフックをコピーします（そのまま使用でき、調整は不要です）：

```bash
mkdir -p extra_scripts
cp path/to/iDryer-Storage/extra_scripts/pre_gen_menu.py extra_scripts/pre_gen_menu.py
```

次に、`platformio.ini`の`[env:cabinet]`セクションに`-Isrc/menu`行を追加します（コードが`#include <menu_state.h>`を見るため）と`extra_scripts`を通じたフック接続：

```ini
[env:cabinet]
; ... 章4からのplatform/board/lib_deps - 変更なし ...

build_flags =
    -Isrc/menu                      ; ← 追加：生成されたメニューへのパス
    -DIDRYER_API_BASE='"https://portal.idryer.org/api"'
    -DMQTT_BROKER='"mqtt.idryer.org"'
    -DMQTT_PORT=8883
    -DMQTT_USE_TLS=1

extra_scripts =                     ; ← 追加
    pre:extra_scripts/pre_gen_menu.py
```

フックは自動的にパス`lib/idryer-core/menu/menu_gen.py`でジェネレーターを見つけます。ライブラリは[4章](04-firmware-start.md)で説明されているとおり、`lib/`（シムリンクまたはコピー）を通じて接続される必要があります。

## ステップ3。シャフトのパラメーターを説明する

`src/menu/menu.yaml`を開きます。テンプレートには既にルートアイテム`root`（`children`配列と例パラメーター）があります。例（`my_param`、`my_flag`、`my_mode_group`）を削除し、`children`内に独自を追加します。最後の2つのアイテム`units_count`と`language`はそのままにしておきます。これはポータルとの固定された契約です。

基本的なシャフトには、いくつかのパラメーターで十分です。

保管用の目標温度：

```yaml
- id: target_temp
  type: value
  role: storage.target_temperature   # ポータルでウィジェットを作成します
  title: { ru: "ТЕМПЕРАТУРА", en: "TARGET TEMP" }
  unit:  { ru: "°C", en: "°C" }
  vtype: uint16
  min: 30
  max: 50
  step: 1
  bind: target_temp            # NVSキー（15文字以下）
  persist: true
  scope: global
  default: 45
```

ヒステリシス（温度が目標より何度下がるか、その後ヒートが再度オンになるまで）：

```yaml
- id: hysteresis
  type: value
  title: { ru: "ГИСТЕРЕЗИС", en: "HYSTERESIS" }
  unit:  { ru: "°C", en: "°C" }
  vtype: uint8
  min: 1
  max: 5
  step: 1
  bind: hysteresis
  persist: true
  scope: global
  default: 2
```

!!! note "role：はクローズドリストです"
    `role:`の値は任意には発明できません。コア契約の`canonical_roles`リストからである必要があります。適切なロールがない場合、ビルドは停止し、許可されたリストが表示されます。保管用シャフトの場合、`storage.*`ファミリーロール：`storage.target_temperature`、`storage.target_humidity`、`storage.start`、`storage.stop`が適切です。完全なリスト - `menu.template.yaml`のヘッダーで。`role:`なしのパラメーター（上記のヒステリシスなど）は内部設定として機能します：NVSに保存されますが、ポータルには表示されません。

守る必要がある制限：

- `bind`- 15文字以下（NVSキーの制限）；
- `menu.yaml`に`widget:`フィールドを追加しないでください。ウィジェットの種類は`role:`による契約で決定されます。

!!! warning "テンプレートのignore_external_cmdアイテムを確認してください"
    テンプレートに`ignore_external_cmd`アイテムがあり、`bind` - 19文字（制限15）。そのまま放置すると、生成は失敗します：`bind 'ignore_external_cmd' ... 19文字、制限15`。このアイテムを削除するか、`bind`を`ign_ext_cmd`に短縮します（実際の製品のように）。基本的なシャフトの場合、単に削除できます。

## ステップ4。プロジェクトをビルドして生成を確認します

```bash
pio run -e cabinet
```

ビルド中、フックは依存関係を自分で配置（一度）し、C++メニューファイルを生成します。`menu.yaml`が変わらなかった場合、生成はスキップされます（`最新`）。

生成が成功したかを確認します。ビルドログにメニュー生成について行が表示され、`src/menu/`フォルダに生成されたファイルがあります：

```text
src/menu/
├── menu.yaml          # あなたのファイル（ソース）
├── menu_state.h/.cpp  # すべてのパラメーターを含むメニューオブジェクト
├── menu_bindings.*    # bind + NVSへの書き込みでのアクセス
├── menu_ids.h
└── menu_meta.h        # 他
```

ビルドが未知の`role:`について失敗した場合、ロールが`canonical_roles`リストの外です。修正してリビルドします。autogenマークのファイルを手動で編集しないでください。

## ステップ5。メインメニューに接続します

メニューコードを使用するには、`src/main.cpp`に2つを接続します：

1. 生成されたメニューのヘッダー：

    ```cpp
    #include <menu_state.h>      // すべてのパラメーターを持つメニューオブジェクト
    ```

2. `setup()`で`s_link.begin()`の**前**にデフォルトをロードします：

    ```cpp
    menu.initDefaults();         // YAMLからのデフォルト値を設定
    ```

その後、パラメーターはグローバルオブジェクト`menu`を通じて利用可能です：

```cpp
uint16_t target = menu.target_temp;   // 値への直接アクセス
```

これらの値は、次のステップで加熱ロジックで使用します。ユーザーがポータルでパラメーターを変更すると、コアが新しい値を自動的に適用し、NVSに保存します。

## この章の後の完全な`src/main.cpp`

前の章に対して、2行のみが追加されました（`// ← 章6`でマークされています）：メニュー接続と`menu.initDefaults()`。

```cpp
#include <iDryer.h>
#include <Wire.h>
#include <math.h>
#include "Sht31ClimateSensor.h"
#include <menu_state.h>           // ← 章6

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

static Sht31ClimateSensor s_climate(&Wire);
static bool               s_climateOk = false;

static const int   THERM_PIN  = 2;
static const float SERIES_R   = 4700.0f;
static const float NOMINAL_R  = 100000.0f;
static const float NOMINAL_T  = 25.0f;
static const float BETA       = 3950.0f;

static float readHeaterTempC() {
    int   raw = analogRead(THERM_PIN);
    float v   = (float)raw / 4095.0f;
    float r   = SERIES_R * (1.0f - v) / v;
    float tK  = 1.0f / (1.0f / (NOMINAL_T + 273.15f) + logf(r / NOMINAL_R) / BETA);
    return tK - 273.15f;
}

void setup() {
    Serial.begin(115200);
    Wire.begin(8, 9);
    s_climateOk = s_climate.begin();
    menu.initDefaults();           // ← 章6
    s_link.begin();
}

void loop() {
    s_link.loop();

    if (s_climateOk) {
        s_climate.tick(millis());
        SensorReading r = s_climate.get();
        if (r.ok) {
            s_link.telemetry.airTempC[0]       = r.temperature;
            s_link.telemetry.airHumidityPct[0] = r.humidity;
        }
    }
    s_link.telemetry.heaterTempC[0] = readHeaterTempC();
}
```

## 結果の確認

フラッシュ後：

- ポータルのデバイスカードに目標温度の設定が表示されます；
- ポータルでの値の変更が保存され、再起動後に保持されます；
- 内部パラメーター（ヒステリシス）は`menu`を通じてコードで利用可能です。

## 次のステップ

設定が説明され、保存されています。次に、[加熱制御](07-heating-control.md)のハードウェアに接続します：加熱器が目標温度を保つ、ファンはしきい値で常時オンになります。
