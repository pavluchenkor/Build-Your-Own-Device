---
title: "櫃加熱控制：溫度維持和風扇"
description: "idryer-core加熱櫃邏輯：透過滯後維持目標溫度，根據溫敏電阻保護加熱器，風扇和門戶命令。"
---

# 加熱控制

本頁你將感應器、設定和電源部分連接到工作邏輯。設備將櫃內保持在設定的溫度，保護加熱器免過熱，並回應門戶命令。

邏輯在`loop()`中執行，位於網路維護旁邊。所有計時器和閾值——無阻塞，無`delay()`。

## 應該發生什麼

櫃的行為由三個簡單規則組成：

1. **溫度維持。** 如果櫃內空氣冷於目標溫度加滯後——開啟加熱。到達目標後——關閉。
2. **加熱器保護。** 溫敏電阻控制加熱器本身。如果超過允許溫度——加熱獨立關閉，無論空氣溫度如何。
3. **風扇。** 開啟以在櫃內傳播熱量，在不需要加熱時關閉。

## 加熱器和風扇開關

控制器透過開關控制加熱器和風扇：MOSFET模組（版本A）或SSR（版本B）——見[接線圖](03-wiring.md)。從程式碼角度，這只是GPIO引腳：`HIGH` — 開啟，`LOW` — 關閉。

用小結構描述此類開關，並製作兩個例項——一個用於加熱器，一個用於風扇。在`src/main.cpp`中新增這個（在`setup()`之前）：

```cpp
struct GpioOutput {
    int pin;
    void begin() { pinMode(pin, OUTPUT); digitalWrite(pin, LOW); }
    void on()    { digitalWrite(pin, HIGH); }
    void off()   { digitalWrite(pin, LOW); }
};

static GpioOutput myHeater{4};   // GPIO4 — 加熱器控制
static GpioOutput myFan{5};      // GPIO5 — 風扇控制
```

引腳號與[接線圖](03-wiring.md)中的相同。在`setup()`中都應初始化：`myHeater.begin();`和`myFan.begin();`。

!!! warning "啟動時的安全狀態"
    `begin()`立即設定`LOW` — 加熱器和風扇關閉，直到邏輯決定否則。這很重要：開啟電源時，加熱器不應意外開啟。

## 透過滯後維持溫度

對於`40-45 °C`的櫃子，簡單的滯後就足夠了：加熱在目標周圍開啟和關閉。這比完整的PID更簡單，對於溫和的保溫效果可靠。

目標溫度和滯後來自菜單（`menu.target_temp`、`menu.hysteresis`）——它已在[第6章](06-menu.md)中連接。新增狀態旗標和決策函式：

```cpp
static bool s_heating = false;

static void controlLoop() {
    float air    = s_link.telemetry.airTempC[0];     // SHT31
    float target = (float)menu.target_temp;          // 來自菜單
    float hyst   = (float)menu.hysteresis;           // 來自菜單

    if (air < target - hyst) {
        s_heating = true;     // 冷卻 — 加熱
    } else if (air >= target) {
        s_heating = false;    // 達到目標 — 停止
    }
}
```

目標溫度和滯後來自[菜單](06-menu.md)——使用者從門戶更改它們。

## 根據溫敏電阻保護加熱器

空氣加熱緩慢，加熱器螺旋快速。沒有單獨的控制，加熱器會在空氣到達目標前就過熱。因此加熱器溫敏電阻設定了硬限制。

```cpp
static const float HEATER_MAX_C = 80.0f;   // 加熱器溫度上限

static void applyHeater() {
    float heaterTemp = s_link.telemetry.heaterTempC[0];   // 溫敏電阻

    bool allow = s_heating && heaterTemp < HEATER_MAX_C;

    if (allow) {
        myHeater.on();
        s_link.telemetry.heaterPower01[0] = 1.0f;   // 反映在遙測中
    } else {
        myHeater.off();
        s_link.telemetry.heaterPower01[0] = 0.0f;
    }
}
```

!!! warning "加熱器上限是保護，不是氣候控制"
    `HEATER_MAX_C`限制加熱器本身的溫度，不是空氣。值取決於加熱器構造和外殼材料。選擇時要有餘量，低於列印件變形的溫度——見[熱耐受材料](../07-3d-printing/04-heat-resistant-materials.md)。

為了更平順的加熱，不是打開/關閉「全開或全閉」，可透過PWM控制功率，`heaterPower01[0]`接受`0.0`至`1.0`的值。對於帶溫和保溫的櫃子，上面的簡單邏輯通常足夠。

## 風扇

風扇在櫃內傳播熱量。最簡單的邏輯——在加熱時開啟：

```cpp
static void applyFan() {
    bool fanOn = s_heating;          // 加熱時旋轉
    if (fanOn) myFan.on(); else myFan.off();
    s_link.telemetry.fanOn[0] = fanOn;   // 反映在遙測中
}
```

在系列控制器中，風扇透過有單獨開啟和關閉閾值的溫度控制（例如，`55 °C`時開啟，`35 °C`時關閉），以免在邊界處抖動。對於櫃子，可以應用相同的方法，將閾值繫結到菜單參數。

## 在loop()中組裝

```cpp
void loop() {
    s_link.loop();          // 網路和自動發佈

    // 感應器（見「感應器」步驟）：
    s_climate.tick(millis());
    SensorReading c = s_climate.get();
    if (c.ok) {
        s_link.telemetry.airTempC[0]       = c.temperature;
        s_link.telemetry.airHumidityPct[0] = c.humidity;
    }
    s_link.telemetry.heaterTempC[0] = readHeaterTempC();

    controlLoop();   // 決定是否加熱
    applyHeater();   // 應用到加熱器 + 保護
    applyFan();      // 應用到風扇
}
```

遙測欄位（`heaterPower01`、`fanOn`）由外觀自動發佈——在門戶中看到設備現在是否加熱和風扇是否工作。

## 來自門戶的命令

門戶作為命令傳送保溫的啟動和停止。處理器透過方法`s_link.onCommand(name, callback)`註冊——**在`s_link.begin()`之後**。操作命令帶有名稱`invoke`和`action`欄位（菜單中的角色，例如`storage.start` / `storage.stop`）。

要解析JSON，需要標題`<ArduinoJson.h>`和`<string.h>`（用於`strcmp`）——將它們新增到檔案開始的其他`#include`。處理器本身在`setup()`中設定：

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

- `storage.start` / `storage.stop` — 與你在[菜單](06-menu.md)中設定的相同角色；門戶根據它們繪製按鈕。
- `iDryer::UnitMode::Storage` — 溫和保溫模式。這是櫃的主要模式。
- `s_link.status.mode[0]`和`targetTempC[0]`在門戶上顯示腔室的當前狀態。
- `publishStatusNow()`在每次狀態改變後呼叫，以便門戶立即看到它，不用等待計時器。

!!! warning "處理器中無delay()"
    `onCommand`處理器從網路回調呼叫。其中的任何阻塞都會中斷MQTT會話。改變旗標和狀態，而在`loop()`中做實際工作。

## 本章後的完整`src/main.cpp`

這是最終完整的設備檔案。相對於上一章的新行標記為`// ← 第7章`。同一個檔案作為現成範例位於儲存庫的`example/09-cabinet/`資料夾中，並透過`pio run -e cabinet`命令構建。

??? note "第6章結束後的`src/main.cpp`"

    ```cpp
    #include <iDryer.h>
    #include <Wire.h>
    #include <math.h>
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

    void setup() {
        Serial.begin(115200);
        Wire.begin(8, 9);
        s_climateOk = s_climate.begin();
        menu.initDefaults();
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
#include <Wire.h>
#include <ArduinoJson.h>          // ← 第7章（onCommand：JsonObjectConst）
#include <string.h>              // ← 第7章（strcmp）
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

// ← 第7章：加熱器和風扇開關
struct GpioOutput {
    int pin;
    void begin() { pinMode(pin, OUTPUT); digitalWrite(pin, LOW); }
    void on()    { digitalWrite(pin, HIGH); }
    void off()   { digitalWrite(pin, LOW); }
};
static GpioOutput myHeater{4};
static GpioOutput myFan{5};

// ← 第7章：溫度維持邏輯
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
    myHeater.begin();              // ← 第7章
    myFan.begin();                 // ← 第7章
    menu.initDefaults();
    s_link.begin();

    s_link.onCommand("invoke", [](JsonObjectConst data) {   // ← 第7章
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

    controlLoop();   // ← 第7章
    applyHeater();   // ← 第7章
    applyFan();      // ← 第7章
}
```

## 驗證結果

此步驟後：

- 門戶啟動將櫃轉為儲存模式，設備開始加熱；
- 空氣溫度逼近目標，保持在滯後範圍內；
- 加熱器不會超過`HEATER_MAX_C`；
- 風扇和加熱功率在遙測中可見；
- 門戶停止關閉加熱並轉為閒置。

## 下一步

邏輯已準備好。剩下的是將設備組裝到外殼中並檢查在打開——[組裝和檢查](08-assembly-and-check.md)。
