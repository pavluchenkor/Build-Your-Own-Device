---
title: "柜加热管理：温度维护和风扇"
description: "idryer-core 加热柜的逻辑：按磁滞维护目标温度，通过温度计保护加热器，风扇和门户网站命令。"
---

# 加热管理

在本页中，你将传感器、设置和电源部分关联为工作逻辑。设备在柜中保持指定的温度，保护加热器免受过热，并响应来自门户网站的命令。

逻辑在 `loop()` 中旁边执行网络服务。所有计时器和阈值是非阻塞的，没有 `delay()`。

## 应该发生什么

柜的行为由三个简单规则组成：

1. **温度维护。** 如果柜内空气比目标低磁滞量 — 打开加热。到达目标时 — 关闭。
2. **加热器保护。** 温度计控制加热器本身。如果它过热 — 加热关闭，无论空气温度如何。
3. **风扇。** 打开以在柜中吹动热量，当不需要加热时关闭。

## 加热器和风扇开关

控制器通过开关管理加热器和风扇：MOSFET 模块（版本 A）或 SSR（版本 B）— 见[接线图](03-wiring.md)。从代码的角度来看，这只是一个 GPIO 引脚：`HIGH` — 打开，`LOW` — 关闭。

用小结构描述这样的开关并制作两个实例 — 用于加热器和风扇。在 `src/main.cpp` 中添加（在 `setup()` 之前）：

```cpp
struct GpioOutput {
    int pin;
    void begin() { pinMode(pin, OUTPUT); digitalWrite(pin, LOW); }
    void on()    { digitalWrite(pin, HIGH); }
    void off()   { digitalWrite(pin, LOW); }
};

static GpioOutput myHeater{4};   // GPIO4 — 加热器控制
static GpioOutput myFan{5};      // GPIO5 — 风扇控制
```

引脚号与[接线图](03-wiring.md)相同。在 `setup()` 中两个开关都应初始化：`myHeater.begin();` 和 `myFan.begin();`。

!!! warning "启动时的安全状态"
    `begin()` 立即设置 `LOW` — 加热器和风扇关闭，直到逻辑决定另外。这很重要：打开电源时加热器不应意外打开。

## 按磁滞维护温度

对于 `40-45 °C` 的柜子，简单的磁滞足够：加热打开和关闭围绕目标。这比完整 PID 更简单，对温暖维护可靠。

从菜单获取目标温度和磁滞（`menu.target_temp`、`menu.hysteresis`）— 它已在[第 6 章](06-menu.md)中连接。添加状态标志和决策函数：

```cpp
static bool s_heating = false;

static void controlLoop() {
    float air    = s_link.telemetry.airTempC[0];     // SHT31
    float target = (float)menu.target_temp;          // 从菜单
    float hyst   = (float)menu.hysteresis;           // 从菜单

    if (air < target - hyst) {
        s_heating = true;     // 冷了 — 加热
    } else if (air >= target) {
        s_heating = false;    // 到达目标 — 停止
    }
}
```

目标温度和磁滞来自[菜单](06-menu.md) — 用户从门户网站改变它们。

## 通过温度计保护加热器

空气缓慢加热，加热器线圈很快。没有单独的控制，加热器可能在空气到达目标之前过热。这就是为什么加热器的温度计设置硬性限制。

```cpp
static const float HEATER_MAX_C = 80.0f;   // 加热器温度的上限

static void applyHeater() {
    float heaterTemp = s_link.telemetry.heaterTempC[0];   // 温度计

    bool allow = s_heating && heaterTemp < HEATER_MAX_C;

    if (allow) {
        myHeater.on();
        s_link.telemetry.heaterPower01[0] = 1.0f;   // 反映在遥测中
    } else {
        myHeater.off();
        s_link.telemetry.heaterPower01[0] = 0.0f;
    }
}
```

!!! warning "加热器上限是保护，不是气候调节"
    `HEATER_MAX_C` 限制加热器本身的温度，而不是空气。值取决于加热器构造和外壳材料。选择它的余量低于打印部件变形的温度 — 见[耐热材料](../07-3d-printing/04-heat-resistant-materials.md)。

为获得更平滑的加热，而不是"全部或无"的打开/关闭，你可以通过 PWM 管理功率，且 `heaterPower01[0]` 字段接受从 `0.0` 到 `1.0` 的值。对于温暖维护柜，上面的简单逻辑通常足够。

## 风扇

风扇在柜中吹动热量。最简单的逻辑是在我们加热时打开它：

```cpp
static void applyFan() {
    bool fanOn = s_heating;          // 当我们加热时旋转
    if (fanOn) myFan.on(); else myFan.off();
    s_link.telemetry.fanOn[0] = fanOn;   // 反映在遥测中
}
```

在系列控制器中，风扇通过温度以独立阈值管理（例如，在 `55 °C` 打开，在 `35 °C` 关闭），以防它在边界附近抖动。对于柜子，你可以应用相同的方法，将阈值绑定到菜单参数。

## 在 loop() 中汇总

```cpp
void loop() {
    s_link.loop();          // 网络和自动发布

    // 传感器（见"传感器"步骤）：
    s_climate.tick(millis());
    SensorReading c = s_climate.get();
    if (c.ok) {
        s_link.telemetry.airTempC[0]       = c.temperature;
        s_link.telemetry.airHumidityPct[0] = c.humidity;
    }
    s_link.telemetry.heaterTempC[0] = readHeaterTempC();

    controlLoop();   // 决定是否加热
    applyHeater();   // 应用于加热器 + 保护
    applyFan();      // 应用于风扇
}
```

遥测字段（`heaterPower01`、`fanOn`）外观自己发布 — 门户网站上可见设备现在是否在加热，风扇是否工作。

## 来自门户网站的命令

门户网站将启动和停止热维护作为命令发送。处理器通过 `s_link.onCommand(name, callback)` 方法注册 — **在** `s_link.begin()` **之后**。操作命令带有名称 `invoke` 和 `action` 字段（菜单中的角色，例如 `storage.start` / `storage.stop`）。

要解析 JSON，需要 `<ArduinoJson.h>` 和 `<string.h>` 标题（用于 `strcmp`）— 将它们添加到文件开头的其他 `#include` 中。处理器本身在 `setup()` 中设置：

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

- `storage.start` / `storage.stop` — 与[菜单](06-menu.md)中指定的相同角色；门户网站通过它们绘制按钮。
- `iDryer::UnitMode::Storage` — 温暖维护的模式。这是柜的主要模式。
- `s_link.status.mode[0]` 和 `targetTempC[0]` 在门户网站上显示室的当前状态。
- 在每次状态更改后调用 `publishStatusNow()` 使门户网站立即看到它，不等计时器。

!!! warning "处理器中没有 delay()"
    `onCommand` 处理器从网络回调调用。处理器内的任何阻塞都断裂 MQTT 会话。改变标志和状态，在 `loop()` 中做实际工作。

## 本章后 `src/main.cpp` 的完整版本

这是最终的、完整的设备文件。相对于上一章的新行标记为 `// ← 第 7 章`。这个文件也位于存储库的 `example/09-cabinet/` 文件夹中作为现成示例，并通过 `pio run -e cabinet` 命令构建。

??? note "第 6 章结束后的 `src/main.cpp`"

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
#include <ArduinoJson.h>          // ← 第 7 章（onCommand：JsonObjectConst）
#include <string.h>              // ← 第 7 章（strcmp）
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

// ← 第 7 章：加热器和风扇开关
struct GpioOutput {
    int pin;
    void begin() { pinMode(pin, OUTPUT); digitalWrite(pin, LOW); }
    void on()    { digitalWrite(pin, HIGH); }
    void off()   { digitalWrite(pin, LOW); }
};
static GpioOutput myHeater{4};
static GpioOutput myFan{5};

// ← 第 7 章：温度维护逻辑
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
    myHeater.begin();              // ← 第 7 章
    myFan.begin();                 // ← 第 7 章
    menu.initDefaults();
    s_link.begin();

    s_link.onCommand("invoke", [](JsonObjectConst data) {   // ← 第 7 章
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

    controlLoop();   // ← 第 7 章
    applyHeater();   // ← 第 7 章
    applyFan();      // ← 第 7 章
}
```

## 检查结果

在这一步之后：

- 从门户网站启动将柜转换为存储模式，设备开始加热；
- 空气温度上升到目标并保持在磁滞范围内；
- 加热器不超过 `HEATER_MAX_C`；
- 风扇和加热电源在遥测中可见；
- 从门户网站停止关闭加热并转换为空闲。

## 接下来

逻辑准备好了。仍然在外壳中组装设备并在打开时检查 — [组装和检查](08-assembly-and-check.md)。
