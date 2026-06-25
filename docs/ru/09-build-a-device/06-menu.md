---
title: "Меню устройства из YAML: настройки в NVS и на портале"
description: "Как описать меню устройства на idryer-core в menu.yaml: целевая температура и гистерезис сохраняются в NVS и отображаются виджетами на портале iDryer."
---

# Меню из YAML

Меню — это набор настроек устройства: целевая температура, гистерezис, пороги вентилятора. На `idryer-core` меню описывается одним файлом `menu.yaml`, а всё остальное — C++-структуры, сохранение в энергонезависимую память (NVS) и публикация на портал — генерируется автоматически.

Это один из ключевых блоков ядра. Вы не пишете код хранения настроек и не придумываете формат для портала — вы только перечисляете параметры в YAML.

## Зачем меню

После предыдущих шагов устройство читает датчики, но все пороги «зашиты» в код. Меню решает три задачи сразу:

- **хранение**: значения переживают перезагрузку (NVS);
- **управление с портала**: каждый параметр становится виджетом (слайдер, переключатель);
- **единый источник правды**: один файл описывает и память, и интерфейс.

## Как работает

Один файл `menu.yaml` проходит через генератор при сборке:

```text
menu.yaml → (сборка pio run) → C++-файлы в src/menu/ + NVS + JSON для портала
```

Пункт с полем `role:` виден порталу и отображается виджетом. Пункт без `role:` — приватный, только для внутренней логики устройства.

!!! warning "Не редактируйте сгенерированные файлы"
    Файлы `menu_state.*`, `menu_bindings.*`, `menu_ids.h` и другие создаёт генератор. Правьте только `menu.yaml` и пересобирайте — иначе ваши изменения затрутся.

## Шаг 1. Скопируйте шаблон

В библиотеке есть шаблон меню. Скопируйте его в проект:

```bash
mkdir -p src/menu
cp path/to/idryer-core/menu/menu.template.yaml src/menu/menu.yaml
```

## Шаг 2. Подключите генерацию при сборке

Скопируйте образец хука из проекта `iDryer-Storage` (его можно взять как есть, настраивать не нужно):

```bash
mkdir -p extra_scripts
cp path/to/iDryer-Storage/extra_scripts/pre_gen_menu.py extra_scripts/pre_gen_menu.py
```

Затем в `platformio.ini` добавьте в секцию `[env:cabinet]` строку `-Isrc/menu` (чтобы код видел `#include <menu_state.h>`) и подключите хук через `extra_scripts`:

```ini
[env:cabinet]
; ... platform / board / lib_deps из главы 4 — без изменений ...

build_flags =
    -Isrc/menu                      ; ← добавили: путь к сгенерированному меню
    -DIDRYER_API_BASE='"https://portal.idryer.org/api"'
    -DMQTT_BROKER='"mqtt.idryer.org"'
    -DMQTT_PORT=8883
    -DMQTT_USE_TLS=1

extra_scripts =                     ; ← добавили
    pre:extra_scripts/pre_gen_menu.py
```

Хук сам найдёт генератор по пути `lib/idryer-core/menu/menu_gen.py`, поэтому библиотека должна быть подключена через `lib/` (симлинк или копия), как описано в главе 4.

## Шаг 3. Опишите параметры шкафа

Откройте `src/menu/menu.yaml`. В шаблоне уже есть корневой пункт `root` с массивом `children` и примерами параметров. Удалите примеры (`my_param`, `my_flag`, `my_mode_group`) и добавьте свои внутрь `children`. Два последних пункта — `units_count` и `language` — оставьте на месте: это фиксированный контракт с порталом.

Для базового шкафа достаточно нескольких параметров.

Целевая температура хранения:

```yaml
- id: target_temp
  type: value
  role: storage.target_temperature   # делает параметр виджетом на портале
  title: { ru: "ТЕМПЕРАТУРА", en: "TARGET TEMP" }
  unit:  { ru: "°C", en: "°C" }
  vtype: uint16
  min: 30
  max: 50
  step: 1
  bind: target_temp            # NVS-ключ (≤ 15 символов)
  persist: true
  scope: global
  default: 45
```

Гистерезис (на сколько градусов температура может уйти ниже цели, прежде чем снова включится нагрев):

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

!!! note "role: — это закрытый список"
    Значение `role:` нельзя придумать произвольно — оно должно быть из списка `canonical_roles` контракта ядра. Если подходящей роли нет, сборка остановится и покажет список допустимых. Для шкафа хранения подходят роли семейства `storage.*`: `storage.target_temperature`, `storage.target_humidity`, `storage.start`, `storage.stop`. Полный список — в шапке `menu.template.yaml`. Параметры без `role:` (как гистерезис выше) работают как внутренние настройки: хранятся в NVS, но на портал не выводятся.

Ограничения, которые нельзя нарушать:

- `bind` — не длиннее 15 символов (лимит ключа NVS);
- не добавляйте поле `widget:` в `menu.yaml` — вид виджета определяет контракт по `role:`.

!!! warning "Проверьте пункт ignore_external_cmd из шаблона"
    В шаблоне есть пункт `ignore_external_cmd`, и его `bind` — 19 символов, что превышает лимит 15. Если оставить как есть, генерация упадёт: `bind 'ignore_external_cmd' ... имеет 19 символов, лимит 15`. Либо удалите этот пункт, либо укоротите `bind` до `ign_ext_cmd` (как в реальных продуктах). Для базового шкафа его можно просто удалить.

## Шаг 4. Соберите проект и проверьте генерацию

```bash
pio run -e cabinet
```

При сборке pre-hook сам поставит зависимости (один раз) и сгенерирует C++-файлы меню. Если `menu.yaml` не менялся — генерация пропускается (`up-to-date`).

Проверьте, что генерация прошла. В логе сборки появляется строка о генерации меню, а в папке `src/menu/` — сгенерированные файлы:

```text
src/menu/
├── menu.yaml          # ваш файл (исходник)
├── menu_state.h/.cpp  # объект menu со всеми параметрами
├── menu_bindings.*    # доступ по bind + запись в NVS
├── menu_ids.h
└── menu_meta.h        # и другие
```

Если сборка упала с сообщением про неизвестную `role:` — значит роль написана не из списка `canonical_roles`. Исправьте её и пересоберите. Файлы с пометкой autogen руками не редактируйте.

## Шаг 5. Подключите меню в главное

Чтобы использовать код меню, подключите в `src/main.cpp` две вещи:

1. Заголовок сгенерированного меню:

    ```cpp
    #include <menu_state.h>      // объект menu со всеми параметрами
    ```

2. Загрузку дефолтов в `setup()` — **до** `s_link.begin()`:

    ```cpp
    menu.initDefaults();         // выставить значения по умолчанию из YAML
    ```

После этого параметры доступны через глобальный объект `menu`:

```cpp
uint16_t target = menu.target_temp;   // прямой доступ к значению
```

Эти значения вы используете в логике нагрева на следующем шаге. Когда пользователь меняет параметр на портале, ядро само применяет новое значение и сохраняет его в NVS.

## Полный `src/main.cpp` после этой главы

Относительно прошлой главы добавились только две строки (помечены `// ← глава 6`): подключение меню и `menu.initDefaults()`.

??? примечание «Что было — `src/main.cpp` после главы 5»

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
#include <menu_state.h>           // ← глава 6

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
    menu.initDefaults();           // ← глава 6
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

## Проверка результата

После прошивки:

- на портале в карточке устройства появляется настройка целевой температуры;
- изменение значения на портале сохраняется и переживает перезагрузку;
- внутренние параметры (гистерезис) доступны в коде через `menu`.

## Что дальше

Настройки описаны и хранятся. Теперь свяжем их с железом в [Управлении нагревом](07-heating-control.md): нагреватель держит целевую температуру, вентилятор включается по порогу.
