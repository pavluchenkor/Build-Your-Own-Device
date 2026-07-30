---
title: "來自YAML的設備菜單：NVS和門戶中的設定"
description: "如何在idryer-core中的menu.yaml中描述設備菜單：目標溫度和滯後保存在NVS中，並在iDryer門戶上顯示為小部件。"
---

# YAML菜單

菜單是設備的一組設定：目標溫度、滯後、風扇閾值。在`idryer-core`上，菜單用一個`menu.yaml`檔案描述，而所有其他內容——C++結構、儲存到非揮發性記憶體（NVS）和發佈到門戶——都是自動生成的。

這是核心的關鍵模組之一。你不編寫設定儲存程式碼，也不為門戶設計格式——你只在YAML中列出參數。

## 為什麼需要菜單

在前面的步驟之後，設備讀取感應器，但所有閾值都"硬編碼"在程式碼中。菜單一次解決三個問題：

- **儲存**：值在重啟後保持（NVS）；
- **從門戶管理**：每個參數都變成小部件（滑塊、開關）；
- **唯一的事實來源**：一個檔案描述記憶體和介面。

## 工作原理

一個`menu.yaml`檔案通過生成器在構建時：

```text
menu.yaml → (pio run構建) → src/menu/中的C++檔案 + NVS + 門戶用JSON
```

帶有`role:`欄位的項對門戶可見，並作為小部件顯示。不帶`role:`的項是私密的，僅用於設備內部邏輯。

!!! warning "不要編輯生成的檔案"
    生成器建立`menu_state.*`、`menu_bindings.*`、`menu_ids.h`等檔案。只編輯`menu.yaml`並重新構建——否則你的更改將被抹去。

## 步驟1。複製範本

函式庫中有菜單範本。將其複製到項目：

```bash
mkdir -p src/menu
cp path/to/idryer-core/menu/menu.template.yaml src/menu/menu.yaml
```

## 步驟2。在構建時連接生成

從`iDryer-Storage`項目複製hook樣本（可以按原樣取用，無需配置）：

```bash
mkdir -p extra_scripts
cp path/to/iDryer-Storage/extra_scripts/pre_gen_menu.py extra_scripts/pre_gen_menu.py
```

然後在`platformio.ini`中，在`[env:cabinet]`部分新增行`-Isrc/menu`（以便程式碼看到`#include <menu_state.h>`）並透過`extra_scripts`連接hook：

```ini
[env:cabinet]
; ... 第4章的platform / board / lib_deps——無變更 ...

build_flags =
    -Isrc/menu                      ; ← 新增：生成菜單的路徑
    -DIDRYER_API_BASE='"https://portal.idryer.org/api"'
    -DMQTT_BROKER='"mqtt.idryer.org"'
    -DMQTT_PORT=8883
    -DMQTT_USE_TLS=1

extra_scripts =                     ; ← 新增
    pre:extra_scripts/pre_gen_menu.py
```

Hook會自動在`lib/idryer-core/menu/menu_gen.py`路徑中找到生成器，所以函式庫應透過`lib/`（符號連結或複本）連接，如第4章所述。

## 步驟3。描述櫃的參數

打開`src/menu/menu.yaml`。在範本中已經有根項`root`和數組`children`以及參數範例。刪除範例（`my_param`、`my_flag`、`my_mode_group`）並在`children`內新增自己的。最後兩項——`units_count`和`language`——保留在原位：這是與門戶的固定契約。

對於基本的櫃子，只需幾個參數。

儲存目標溫度：

```yaml
- id: target_temp
  type: value
  role: storage.target_temperature   # 使參數在門戶上成為小部件
  title: { ru: "ТЕМПЕРАТУРА", en: "TARGET TEMP" }
  unit:  { ru: "°C", en: "°C" }
  vtype: uint16
  min: 30
  max: 50
  step: 1
  bind: target_temp            # NVS鍵（≤ 15字元）
  persist: true
  scope: global
  default: 45
```

滯後（溫度可以在重新啟動加熱之前下降到目標以下的度數）：

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

!!! note "role: — 這是一個封閉的清單"
    `role:`的值不能隨意想象——它必須來自核心契約的`canonical_roles`列表。如果沒有合適的角色，構建將停止並顯示允許的列表。對於儲存櫃，`storage.*`家族的角色很合適：`storage.target_temperature`、`storage.target_humidity`、`storage.start`、`storage.stop`。完整清單——在`menu.template.yaml`的標題中。沒有`role:`的參數（如上面的滯後）作為內部設定工作：儲存在NVS中，但不輸出到門戶。

不能違反的限制：

- `bind` — 不超過15個字元（NVS鍵限制）；
- 不要在`menu.yaml`中新增`widget:`欄位——小部件類型由`role:`契約決定。

!!! warning "檢查範本中的ignore_external_cmd項目"
    在範本中有一個`ignore_external_cmd`項，其`bind`——19個字元，超過限制15。如果保留原樣，生成將失敗：`bind 'ignore_external_cmd' ... 有19個字元，限制15`。要麼刪除此項，要麼將`bind`縮短為`ign_ext_cmd`（如實際產品中）。對於基本櫃子，可以簡單地刪除它。

## 步驟4。構建項目並驗證生成

```bash
pio run -e cabinet
```

在構建時，pre-hook本身會安裝依賴項（一次），並生成菜單的C++檔案。如果`menu.yaml`未改變——生成被跳過（`up-to-date`）。

驗證生成已通過。構建日誌中出現菜單生成行，`src/menu/`資料夾中生成文件：

```text
src/menu/
├── menu.yaml          # 你的檔案（源碼）
├── menu_state.h/.cpp  # 帶有所有參數的menu物件
├── menu_bindings.*    # 透過bind存取 + NVS寫入
├── menu_ids.h
└── menu_meta.h        # 及其他
```

如果構建因未知`role:`而失敗——角色不在`canonical_roles`清單中。修復它並重新構建。標記為autogen的檔案不要手動編輯。

## 步驟5。在主程式中連接菜單

要使用菜單程式碼，在`src/main.cpp`中連接兩件事：

1. 生成菜單的標題：

    ```cpp
    #include <menu_state.h>      // 帶有所有參數的menu物件
    ```

2. 在`setup()`中載入預設值——**在`s_link.begin()`之前**：

    ```cpp
    menu.initDefaults();         // 從YAML設定預設值
    ```

之後，參數透過全域`menu`物件存取：

```cpp
uint16_t target = menu.target_temp;   // 直接存取值
```

你在下一步的加熱邏輯中使用這些值。當使用者在門戶上更改參數時，核心會自動應用新值並將其儲存在NVS中。

## 本章後的完整`src/main.cpp`

相對於上一章只新增了兩行（標記為`// ← 第6章`）：菜單連接和`menu.initDefaults()`。

??? note "第5章結束後的`src/main.cpp`"

    ```cpp
    #include <iDryer.h>
    #include <Wire.h>
    #include <math.h>
    #include "Sht31ClimateSensor.h"

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

```cpp
#include <iDryer.h>
#include <Wire.h>
#include <math.h>
#include "Sht31ClimateSensor.h"
#include <menu_state.h>           // ← 第6章

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
    menu.initDefaults();           // ← 第6章
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

## 驗證結果

刷新後：

- 在門戶設備卡中出現目標溫度設定；
- 在門戶上改變值會被保存並在重啟後保持；
- 內部參數（滯後）可透過`menu`在程式碼中存取。

## 下一步

設定已描述並儲存。現在在[加熱控制](07-heating-control.md)中連接它們：加熱器維持目標溫度，風扇根據閾值開啟。
