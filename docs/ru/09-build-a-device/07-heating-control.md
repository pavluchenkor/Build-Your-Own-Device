---
title: "Управление нагревом шкафа: поддержание температуры и вентилятор"
description: "Логика нагреваемого шкафа на idryer-core: поддержание целевой температуры по гистерезису, защита нагревателя по термистору, вентилятор и команды портала."
---

# Управление нагревом

На этой странице вы связываете датчики, настройки и силовую часть в рабочую логику. Устройство держит в шкафу заданную температуру, защищает нагреватель от перегрева и реагирует на команды с портала.

Логика выполняется в `loop()` рядом с обслуживанием сети. Все таймеры и пороги — неблокирующие, без `delay()`.

## Что должно происходить

Поведение шкафа складывается из трёх простых правил:

1. **Поддержание температуры.** Если воздух в шкафу холоднее цели на величину гистерезиса — включить нагрев. Когда дошли до цели — выключить.
2. **Защита нагревателя.** Термистор контролирует сам нагреватель. Если он перегрелся выше допустимого — нагрев выключается независимо от температуры воздуха.
3. **Вентилятор.** Включается, чтобы разогнать тепло по шкафу, и выключается, когда нагрев не нужен.

## Ключи нагревателя и вентилятора

Нагреватель и вентилятор контроллер включает через ключ: MOSFET-модуль (версия A) или SSR (версия B) — см. [Схему подключения](03-wiring.md). С точки зрения кода это просто вывод GPIO: `HIGH` — включено, `LOW` — выключено.

Опишем такой ключ маленькой структурой и заведём два экземпляра — для нагревателя и вентилятора. Добавьте это в `main.cpp` (до `setup()`):

```cpp
struct GpioOutput {
    int pin;
    void begin() { pinMode(pin, OUTPUT); digitalWrite(pin, LOW); }
    void on()    { digitalWrite(pin, HIGH); }
    void off()   { digitalWrite(pin, LOW); }
};

static GpioOutput myHeater{4};   // GPIO4 — управление нагревателем
static GpioOutput myFan{5};      // GPIO5 — управление вентилятором
```

Номера выводов — те же, что в [Схеме подключения](03-wiring.md). В `setup()` оба ключа надо инициализировать: `myHeater.begin();` и `myFan.begin();`.

!!! warning "Безопасное состояние при старте"
    `begin()` сразу ставит `LOW` — нагреватель и вентилятор выключены, пока логика не решит иначе. Это важно: при включении питания нагреватель не должен оказаться включённым случайно.

## Поддержание температуры по гистерезису

Для шкафа на `40–45 °C` достаточно простого гистерезиса: нагрев включается и выключается вокруг цели. Это проще полноценного PID и для мягкого поддержания тепла работает надёжно.

Целевую температуру и гистерезис берём из меню (`menu.target_temp`, `menu.hysteresis`) — оно уже подключено в [главе 6](06-menu.md). Добавьте флаг состояния и функцию решения:

```cpp
static bool s_heating = false;

static void controlLoop() {
    float air    = s_link.telemetry.airTempC[0];     // SHT31
    float target = (float)menu.target_temp;          // из меню
    float hyst   = (float)menu.hysteresis;           // из меню

    if (air < target - hyst) {
        s_heating = true;     // остыли — греем
    } else if (air >= target) {
        s_heating = false;    // дошли до цели — стоп
    }
}
```

Целевая температура и гистерезис берутся из [меню](06-menu.md) — пользователь меняет их с портала.

## Защита нагревателя по термистору

Воздух прогревается медленно, а спираль нагревателя — быстро. Без отдельного контроля нагреватель успеет перегреться до того, как воздух дойдёт до цели. Поэтому термистор нагревателя задаёт жёсткий потолок.

```cpp
static const float HEATER_MAX_C = 80.0f;   // потолок температуры нагревателя

static void applyHeater() {
    float heaterTemp = s_link.telemetry.heaterTempC[0];   // термистор

    bool allow = s_heating && heaterTemp < HEATER_MAX_C;

    if (allow) {
        myHeater.on();
        s_link.telemetry.heaterPower01[0] = 1.0f;   // отразить в телеметрии
    } else {
        myHeater.off();
        s_link.telemetry.heaterPower01[0] = 0.0f;
    }
}
```

!!! warning "Потолок нагревателя — это защита, а не настройка климата"
    `HEATER_MAX_C` ограничивает температуру самого нагревателя, а не воздуха. Значение зависит от конструкции нагревателя и материалов корпуса. Выбирайте его с запасом ниже температуры, при которой деформируются печатные детали — см. [Термостойкие материалы](../07-3d-printing/04-heat-resistant-materials.md).

Для более плавного нагрева вместо включения/выключения «всё или ничего» можно управлять мощностью через ШИМ и поле `heaterPower01[0]` принимает значения от `0.0` до `1.0`. Для шкафа с мягким поддержанием тепла простой логики выше обычно достаточно.

## Вентилятор

Вентилятор разгоняет тепло по шкафу. Простейшая логика — включать его вместе с нагревом:

```cpp
static void applyFan() {
    bool fanOn = s_heating;          // крутим, пока греем
    if (fanOn) myFan.on(); else myFan.off();
    s_link.telemetry.fanOn[0] = fanOn;   // отразить в телеметрии
}
```

В серийном контроллере вентилятор управляется по температуре с отдельными порогами включения и выключения (например, включение при `55 °C`, выключение при `35 °C`), чтобы он не дёргался у границы. Для шкафа можно применить тот же подход, привязав пороги к параметрам меню.

## Собираем в loop()

```cpp
void loop() {
    s_link.loop();          // сеть и автопубликация

    // датчики (см. шаг «Датчики»):
    s_climate.tick(millis());
    SensorReading c = s_climate.get();
    if (c.ok) {
        s_link.telemetry.airTempC[0]       = c.temperature;
        s_link.telemetry.airHumidityPct[0] = c.humidity;
    }
    s_link.telemetry.heaterTempC[0] = readHeaterTempC();

    controlLoop();   // решаем, греть или нет
    applyHeater();   // применяем к нагревателю + защита
    applyFan();      // применяем к вентилятору
}
```

Поля телеметрии (`heaterPower01`, `fanOn`) фасад публикует сам — на портале видно, греет ли устройство сейчас и работает ли вентилятор.

## Команды с портала

Запуск и остановку поддержания тепла портал присылает как команды. Обработчик регистрируется методом `s_link.onCommand(имя, колбэк)` — **после** `s_link.begin()`. Команды действий приходят с именем `invoke` и полем `action` (роль из меню, например `storage.start` / `storage.stop`).

Для разбора JSON нужны заголовки `<ArduinoJson.h>` и `<string.h>` (для `strcmp`) — добавьте их к остальным `#include` в начале файла. Сам обработчик ставится в `setup()`:

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

- `storage.start` / `storage.stop` — те же роли, что вы задали в [меню](06-menu.md); по ним портал рисует кнопки.
- `iDryer::UnitMode::Storage` — режим мягкого поддержания тепла. Это основной режим шкафа.
- `s_link.status.mode[0]` и `targetTempC[0]` показывают на портале текущее состояние камеры.
- `publishStatusNow()` вызывайте после каждого изменения статуса, чтобы портал увидел его сразу, не дожидаясь таймера.

!!! warning "Никаких delay() в обработчике"
    Обработчик `onCommand` вызывается из сетевого колбэка. Любая блокировка внутри него рвёт MQTT-сессию. Меняйте флаги и статус, а саму работу делайте в `loop()`.

## Полный `main.cpp` после этой главы

Это финальный, законченный файл устройства. Новые относительно прошлой главы строки помечены `// ← глава 7`. Этот же файл лежит как готовый пример в `docs/example/09-cabinet/` и собирается командой `pio run -e cabinet`.

??? note "Что было — `main.cpp` после главы 6"

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
#include <ArduinoJson.h>          // ← глава 7 (onCommand: JsonObjectConst)
#include <string.h>              // ← глава 7 (strcmp)
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

// ← глава 7: ключи нагревателя и вентилятора
struct GpioOutput {
    int pin;
    void begin() { pinMode(pin, OUTPUT); digitalWrite(pin, LOW); }
    void on()    { digitalWrite(pin, HIGH); }
    void off()   { digitalWrite(pin, LOW); }
};
static GpioOutput myHeater{4};
static GpioOutput myFan{5};

// ← глава 7: логика поддержания температуры
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
    myHeater.begin();              // ← глава 7
    myFan.begin();                 // ← глава 7
    menu.initDefaults();
    s_link.begin();

    s_link.onCommand("invoke", [](JsonObjectConst data) {   // ← глава 7
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

    controlLoop();   // ← глава 7
    applyHeater();   // ← глава 7
    applyFan();      // ← глава 7
}
```

## Проверка результата

После этого шага:

- запуск с портала переводит шкаф в режим Storage, устройство начинает греть;
- температура воздуха подтягивается к цели и держится в пределах гистерезиса;
- нагреватель не уходит выше `HEATER_MAX_C`;
- вентилятор и мощность нагрева видны в телеметрии;
- остановка с портала выключает нагрев и переводит в Idle.

## Что дальше

Логика готова. Остаётся собрать устройство в корпус и проверить под нагрузкой — [Сборка и проверка](08-assembly-and-check.md).
