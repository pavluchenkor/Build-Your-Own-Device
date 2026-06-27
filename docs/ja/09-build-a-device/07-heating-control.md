---
title: "シャフト加熱制御：温度保持とファン"
description: "idryer-coreでのシャフト加熱ロジック：ヒステリシスによる目標温度の保持、温度計による加熱器保護、ファン、ポータルコマンド。"
---

# 加熱制御

このページでは、センサー、設定、電力部を実際のロジックに接続します。デバイスはシャフト内の設定温度を保つ、加熱器を過熱から保護し、ポータルコマンドに応答します。

ロジックは、ネット保守と同じ`loop()`内で実行されます。すべてのタイマーとしきい値は非ブロッキング（`delay()`なし）です。

## 何が起こるべきか

シャフトの動作は3つの単純なルールで構成されています：

1. **温度保持。**シャフト内の空気が目標よりヒステリシス値だけ低い場合 - ヒートをオンにします。目標に達したら - オフにします。
2. **加熱器保護。**温度計は加熱器自体を制御します。許容値より過熱した場合 - 空気温度に関係なく、ヒートはオフになります。
3. **ファン。**シャフト周辺の熱を分散させるためにオンになり、ヒートが不要になるとオフになります。

## 加熱器とファンのキー

加熱器とファンはコントローラーがキーを通じてオンにします：MOSFETモジュール（バージョンA）またはSSR（バージョンB）。[接続図](03-wiring.md)を参照してください。コードの観点からは、これは単なるGPIOピンです：`HIGH` - オン、`LOW` - オフ。

小さな構造を通じてこのようなキーを説明し、加熱器とファン用の2つのインスタンスを作成します。`src/main.cpp`に（`setup()`の前）追加：

```cpp
struct GpioOutput {
    int pin;
    void begin() { pinMode(pin, OUTPUT); digitalWrite(pin, LOW); }
    void on()    { digitalWrite(pin, HIGH); }
    void off()   { digitalWrite(pin, LOW); }
};

static GpioOutput myHeater{4};   // GPIO4 - 加熱器制御
static GpioOutput myFan{5};      // GPIO5 - ファン制御
```

ピン番号は[接続図](03-wiring.md)と同じです。`setup()`では、両方のキーを初期化する必要があります：`myHeater.begin();`と`myFan.begin();`。

!!! warning "開始時の安全な状態"
    `begin()`は直ちに`LOW`を設定します。加熱器とファンがオフ（ロジックが別の決定をするまで）。これが重要です：電源をオンする際、加熱器が誤ってオンになってはいけません。

## ヒステリシスによる温度保持

`40～45 °C`のシャフトの場合、単純なヒステリシスで十分です：ヒートは目標周辺でオン/オフします。これはフル機能のPIDよりもシンプルで、温かい保持に確実に機能します。

目標温度とヒステリシスはメニュー（`menu.target_temp`、`menu.hysteresis`）から取得します。[6章](06-menu.md)で既に接続されています。フラグと決定関数を追加：

```cpp
static bool s_heating = false;

static void controlLoop() {
    float air    = s_link.telemetry.airTempC[0];     // SHT31
    float target = (float)menu.target_temp;          // メニューから
    float hyst   = (float)menu.hysteresis;           // メニューから

    if (air < target - hyst) {
        s_heating = true;     // 冷えた - 暖める
    } else if (air >= target) {
        s_heating = false;    // 目標に達した - 停止
    }
}
```

目標温度とヒステリシスは[メニュー](06-menu.md)から取得されます。ユーザーはポータルから変更します。

## 温度計による加熱器保護

空気はゆっくり温まり、スパイラルヒーター は速く温まります。加熱器の単独制御がなければ、空気が目標に達する前に加熱器は過熱する可能性があります。したがって、加熱器の温度計は固いキャップを設定します。

```cpp
static const float HEATER_MAX_C = 80.0f;   // 加熱器温度キャップ

static void applyHeater() {
    float heaterTemp = s_link.telemetry.heaterTempC[0];   // 温度計

    bool allow = s_heating && heaterTemp < HEATER_MAX_C;

    if (allow) {
        myHeater.on();
        s_link.telemetry.heaterPower01[0] = 1.0f;   // テレメトリーに反映
    } else {
        myHeater.off();
        s_link.telemetry.heaterPower01[0] = 0.0f;
    }
}
```

!!! warning "加熱器キャップは保護です（気候設定ではありません）"
    `HEATER_MAX_C`は空気ではなく加熱器自体の温度を制限します。値は加熱器の構造と材料に依存します。プリント部品が変形する温度より下で、十分に選択してください。[耐熱材](../07-3d-printing/04-heat-resistant-materials.md)を参照してください。

より円滑な加熱のため、オン/オフ「すべてまたは何もない」の代わりにPWMを通じて電力を管理できます。フィールド`heaterPower01[0]`は`0.0`から`1.0`の値を受け入れます。温かい保持を持つシャフトの場合、上記の単純ロジックで十分です。

## ファン

ファンはシャフル周辺の熱を分散させます。最も単純なロジックは、ヒートと同時にそれを有効にすることです：

```cpp
static void applyFan() {
    bool fanOn = s_heating;          // 暖まっている間、回転
    if (fanOn) myFan.on(); else myFan.off();
    s_link.telemetry.fanOn[0] = fanOn;   // テレメトリーに反映
}
```

シリーズコントローラーでは、ファンは温度で個別のしきい値（たとえば、オン時55 °C、オフ時35 °C）で制御され、境界でジャンプしないようにしています。シャフトの場合、同じアプローチを使用し、しきい値をメニューパラメーターに結合できます。

## loop()に集めます

```cpp
void loop() {
    s_link.loop();          // ネットと自動発行

    // センサー（「センサー」ステップを参照）：
    s_climate.tick(millis());
    SensorReading c = s_climate.get();
    if (c.ok) {
        s_link.telemetry.airTempC[0]       = c.temperature;
        s_link.telemetry.airHumidityPct[0] = c.humidity;
    }
    s_link.telemetry.heaterTempC[0] = readHeaterTempC();

    controlLoop();   // 暖めるか決定
    applyHeater();   // 加熱器に適用 + 保護
    applyFan();      // ファンに適用
}
```

テレメトリーフィールド（`heaterPower01`、`fanOn`）はファサード自身で発行されます。ポータルに現在ヒートしているかとファンが動作しているかが見えます。

## ポータルコマンド

ヒート保持の開始と停止はポータルからコマンドとして送信されます。ハンドラーはメソッド`s_link.onCommand(name, callback)`で登録されます。`s_link.begin()`の**後**。アクション命令は名前`invoke`で来て、フィールド`action`（メニューロール、例：`storage.start` / `storage.stop`）を持っています。

JSONを解析するには、`<ArduinoJson.h>`と`<string.h>`（`strcmp`用）ヘッダーが必要です。ファイルの`#include`の開始部に追加します。ハンドラー自身は`setup()`に配置されます：

```cpp
s_link.onCommand("invoke", [](JsonObjectConst data) {
    const char* action = data["action"] | "";
    if (strcmp(action, "storage.start") == 0) {
        s_heating = true;
        s_link.status.mode[0]        = iDryer::UnitMode::Storage;
        s_link.status.targetTempC[0] = (float)menu.target_temp;
        s_link.publishStatusNow();
    } else if (strcmp(action, "storage.stop") == 0) {
        s_heating = false;
        myHeater.off();
        s_link.status.mode[0] = iDryer::UnitMode::Idle;
        s_link.publishStatusNow();
    }
});
```

- `storage.start` / `storage.stop` - [メニュー](06-menu.md)で設定した同じロール；ポータルはそれらによってボタンを描画します。
- `iDryer::UnitMode::Storage` - ソフト暖かい保持モード。これはシャフトの主要モードです。
- `s_link.status.mode[0]`と`targetTempC[0]`はポータルのカメラの現在の状態を表示します。
- タイマーを待つのではなく、ポータルがすぐにそれを見られるように、ステータス変更後に`publishStatusNow()`を呼び出してください。

!!! warning "ハンドラーで遅延をしない"
    `onCommand`ハンドラーはネットワークコールバックから呼び出されます。その内部のブロッキングはMQTTセッションを破ります。フラグとステータスを変更し、実際の作業は`loop()`で行ってください。

## この章の後の完全な`src/main.cpp`

これは最終的で完全なデバイスファイルです。前の章に対する新しい行は`// ← 章7`でマークされています。同じファイルはリポジトリの`example/09-cabinet/`フォルダーに完成した例として存在し、`pio run -e cabinet`コマンドで構築されます。

```cpp
#include <Wire.h>
#include <ArduinoJson.h>          // ← 章7（onCommand：JsonObjectConst）
#include <string.h>              // ← 章7（strcmp）
#include <math.h>
#include <iDryer.h>
#include "Sht31ClimateSensor.h"
#include <menu_state.h>

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

// ← 章7：加熱器とファンのキー
struct GpioOutput {
    int pin;
    void begin() { pinMode(pin, OUTPUT); digitalWrite(pin, LOW); }
    void on()    { digitalWrite(pin, HIGH); }
    void off()   { digitalWrite(pin, LOW); }
};
static GpioOutput myHeater{4};
static GpioOutput myFan{5};

// ← 章7：温度保持ロジック
static bool        s_heating    = false;
static const float HEATER_MAX_C = 80.0f;

static void controlLoop() {
    float air    = s_link.telemetry.airTempC[0];
    float target = (float)menu.target_temp;
    float hyst   = (float)menu.hysteresis;
    if (air < target - hyst)  s_heating = true;
    else if (air >= target)   s_heating = false;
}

static void applyHeater() {
    float heaterTemp = s_link.telemetry.heaterTempC[0];
    bool  allow = s_heating && heaterTemp < HEATER_MAX_C;
    if (allow) myHeater.on(); else myHeater.off();
    s_link.telemetry.heaterPower01[0] = allow ? 1.0f : 0.0f;
}

static void applyFan() {
    if (s_heating) myFan.on(); else myFan.off();
    s_link.telemetry.fanOn[0] = s_heating;
}

void setup() {
    Serial.begin(115200);
    Wire.begin(8, 9);
    s_climateOk = s_climate.begin();
    myHeater.begin();              // ← 章7
    myFan.begin();                 // ← 章7
    menu.initDefaults();
    s_link.begin();

    s_link.onCommand("invoke", [](JsonObjectConst data) {   // ← 章7
        const char* action = data["action"] | "";
        if (strcmp(action, "storage.start") == 0) {
            s_heating = true;
            s_link.status.mode[0]        = iDryer::UnitMode::Storage;
            s_link.status.targetTempC[0] = (float)menu.target_temp;
            s_link.publishStatusNow();
        } else if (strcmp(action, "storage.stop") == 0) {
            s_heating = false;
            myHeater.off();
            s_link.status.mode[0] = iDryer::UnitMode::Idle;
            s_link.publishStatusNow();
        }
    });
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

    controlLoop();   // ← 章7
    applyHeater();   // ← 章7
    applyFan();      // ← 章7
}
```

## 結果の確認

このステップの後：

- ポータルから開始がストレージモードにシャフトを移動し、デバイスが暖め始めます；
- 空気温度がターゲットに上昇し、ヒステリシス内で保たれます；
- 加熱器は`HEATER_MAX_C`より上に行きません；
- ファンと加熱電力がテレメトリーに表示されます；
- ポータルからの停止がヒートをオフにし、アイドルに移動します。

## 次のステップ

ロジックは完成しました。ケースにデバイスを組み立てるだけです。確認する準備 - [組み立てと確認](08-assembly-and-check.md)。
