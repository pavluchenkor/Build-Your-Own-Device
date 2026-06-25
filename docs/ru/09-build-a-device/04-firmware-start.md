---
title: "Старт прошивки на idryer-core: первый запуск и привязка к порталу"
description: "Создание проекта PlatformIO на библиотеке idryer-core: platformio.ini, secrets.h, Config устройства, первая прошивка ESP32 и привязка к порталу iDryer."
---

# Старт прошивки на ядре

На этой странице вы создаёте проект прошивки, доводите ESP32 до состояния Online на портале и проверяете, что сетевая часть работает. Датчики и логику нагрева добавим на следующих шагах.

Подход построен на фасаде `iDryer::Link`. Вы описываете устройство одной структурой `iDryer::Config`, вызываете `link.begin()` и `link.loop()` — всё подключение к сети ядро делает само.

## 1. Подготовьте инструменты

Понадобится:

- VS Code с расширением PlatformIO;
- USB-кабель;
- Wi-Fi-сеть `2.4 GHz` (ESP32 не работает с сетями только `5 GHz`).

Что такое прошивка контроллера и как она попадает в плату — [Прошивка контроллера](../02-controllers/11-flashing-controller.md).

## 2. Создайте проект

В PlatformIO проект — это папка с фиксированной структурой. Создайте папку проекта (например `my-cabinet`) и откройте её в VS Code. Внутри должны быть такие файлы:

```text
my-cabinet/
├── platformio.ini        # настройки сборки (заполним в шаге 4)
├── include/
│   └── secrets.h         # логин и пароль Wi-Fi (шаг 3)
├── lib/
│   └── idryer-core/      # библиотека ядра (симлинк или копия)
└── src/
    └── main.cpp          # код устройства: Config + setup() + loop()
```

Все фрагменты кода ниже кладутся именно в эти файлы — у каждого шага указано, в какой. Папки `include/`, `lib/` и `src/` создайте вручную, если их нет.

Библиотеку `idryer-core` положите в `lib/` — PlatformIO находит библиотеки там автоматически. Проще всего сделать симлинк на скачанную библиотеку:

```bash
ln -s /путь/к/idryer-core lib/idryer-core
```

Это же требуется для генерации меню (глава 6) — хук ищет генератор внутри `lib/idryer-core/`.

## 3. Создайте secrets.h

Скопируйте пример `secrets.h.example` из библиотеки в `include/secrets.h` своего проекта и укажите данные своей сети:

```cpp
#define WIFI_SSID      "your-ssid"
#define WIFI_PASSWORD  "your-password"
```

Добавьте `include/secrets.h` в `.gitignore`, чтобы пароль не попал в репозиторий.

## 4. Настройте platformio.ini

Заполните `platformio.ini` в корне проекта:

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

Замените `board` на свою плату (например, `esp32-s3-devkitc-1`). Саму `idryer-core` указывать в `lib_deps` не нужно — она лежит в `lib/` (шаг 2).

!!! note "Зачем все эти зависимости"
    `ArduinoJson`, `PubSubClient`, `base64`, `WebSockets` и `Improv-WiFi-Library` нужны самой библиотеке `idryer-core` (MQTT, WebSocket-доступ по LAN, Wi-Fi-provisioning). Без любой из них сборка упадёт с ошибкой вида `... .h: No such file`. Флаги `MQTT_BROKER` и `MQTT_PORT` тоже обязательны — без них ядро не скомпилируется (`'MQTT_BROKER' was not declared`).

## 5. Опишите устройство в Config

Дальше всё происходит в одном файле — `src/main.cpp`. Откройте его и запишите код этого и следующих шагов.

`iDryer::Config` — это паспорт устройства. Флаги `has*` сообщают порталу, что у устройства есть, и определяют, какие поля телеметрии публикуются.

Для обогреваемого шкафа в начало `src/main.cpp`

```cpp
#include <iDryer.h>

static const iDryer::Config CFG = {
    .deviceType        = iDryer::DeviceType::Dryer,
    .unitsCount        = 1,
    // Периферия:
    .hasHeater         = true,    // управляемый нагреватель
    .hasFan            = true,    // вентилятор
    .hasAirTemp        = true,    // температура воздуха (SHT31)
    .hasAirHumidity    = true,    // влажность воздуха (SHT31)
    .hasHeaterTemp     = true,    // температура нагревателя (термистор)
    // Периоды автопубликации:
    .telemetryPeriodMs = 5000,
    .statusPeriodMs    = 10000,
    // Идентификация на портале:
    .hardwareVersion   = "1.0",
    .firmwareVersion   = "0.1.0",
    .model             = "DIY Storage Cabinet",
};

static iDryer::Link s_link(CFG);
```

!!! note "Флаги has* — это контракт с порталом"
    Поле телеметрии, у которого соответствующий флаг `false`, не публикуется. Например, без `hasAirHumidity = true` влажность не попадёт в облако, даже если вы запишете её в код. Включайте только то, что физически есть в устройстве.

Перечень компонентов и флагов — [Состав системы](02-bom.md).

## 6. Минимальный основной

В том же файле после блока `Config` добавьте функции `setup()` и `loop()`. Для первого запуска достаточно завести ссылку и крутить ее в `loop()`:

```cpp
void setup() {
    Serial.begin(115200);
    s_link.begin();
}

void loop() {
    s_link.loop();
}
```

Этого хватит, чтобы устройство подключилось к Wi-Fi и вышло на портал. Датчики добавим на шаге [Датчики](05-sensors.md).

### Полный `src/main.cpp` после этой главы

Возьмите оба блока выше в один файл — это весь `src/main.cpp` на данном шаге:

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

Предыдущий глава показывает, **что добавить** и **полный `src/main.cpp` после изменений**, чтобы вы всегда видели целую картину, а не разрозненные куски.

## 7. Прошейте

```bash
pio run -e cabinet -t upload
```

## 8. Откройте Serial Monitor

```bash
pio device monitor -b 115200
```

Ожидаемая последовательность в логе:

```text
[CLOUD] Connecting to WiFi...
[CLOUD] WiFi connected, IP: 192.168.1.42
[CLOUD] Provisioning device...
[CLOUD] PIN: 1234567 (expires in 600s)
```

Если устройство остановилось на строке `PIN: ...` — это нормально. Переходите к привязке.

## 9. Привяжите устройство к порталу

1. Откройте [portal.idryer.org](https://portal.idryer.org/).
2. Перейдите в раздел **Add device**.
3. Введите PIN из Serial Monitor.

После привязки устройство перейдёт в статус `Online`. В логе появится:

```text
[CLOUD] Device claimed!
[CLOUD] MQTT connected!
```

## Проверка результата

На этом шаге устройство должно быть Online на портале. Данных с датчиков пока нет — это ожидаемо. Если устройство не подключается:

- проверьте, что сеть `2.4 GHz` и пароль в `secrets.h` верны;
- проверьте питание ESP32 (просадки при старте Wi-Fi — частая причина перезагрузок);
- смотрите [Ошибки питания](../08-common-mistakes/02-power-mistakes.md) и [Ошибки контроллеров](../08-common-mistakes/04-controller-mistakes.md).

## Что дальше

Сетевая часть работает. Переходите к [Датчикам](05-sensors.md): подключим SHT31 и термистор и увидим их данные на портале.
