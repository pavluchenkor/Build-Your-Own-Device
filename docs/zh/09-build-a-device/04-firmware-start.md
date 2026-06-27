---
title: "在 idryer-core 上启动固件：首次启动和绑定到门户网站"
description: "在 idryer-core 库上创建 PlatformIO 项目：platformio.ini、secrets.h、Config 设备、首次 ESP32 固件和绑定到 iDryer 门户网站。"
---

# 在核心上启动固件

在本页中，你创建固件项目，使 ESP32 在门户网站上达到在线状态，并检查网络部分是否有效。在下一步中添加传感器和加热逻辑。

该方法基于 `iDryer::Link` 外观。你用一个 `iDryer::Config` 结构描述设备，调用 `link.begin()` 和 `link.loop()` — 核心库自己处理所有网络连接。

## 1. 准备工具

你需要：

- VS Code 与 PlatformIO 扩展；
- USB 电缆；
- `2.4 GHz` Wi-Fi 网络（ESP32 不适用于仅 `5 GHz` 网络）。

什么是控制器固件以及它如何进入板——[刷入控制器](../02-controllers/11-flashing-controller.md)。

## 2. 创建项目

在 PlatformIO 中，项目是具有固定结构的文件夹。创建项目文件夹（例如 `my-cabinet`）并在 VS Code 中打开它。里面应该有这些文件：

```text
my-cabinet/
├── platformio.ini        # 构建设置（步骤 4 中填写）
├── include/
│   └── secrets.h         # Wi-Fi 登录名和密码（步骤 3）
├── lib/
│   └── idryer-core/      # 核心库（符号链接或副本）
└── src/
    └── main.cpp          # 设备代码：Config + setup() + loop()
```

下面的所有代码片段都放在这些文件中——每个步骤都指定了文件的位置。如果没有的话，手动创建 `include/`、`lib/` 和 `src/` 文件夹。

将 `idryer-core` 库放在 `lib/` 中 — PlatformIO 自动在那里查找库。最简单的方法是对下载的库创建符号链接：

```bash
ln -s /path/to/idryer-core lib/idryer-core
```

这也是菜单生成所需的（第 6 章）—— 钩子在 `lib/idryer-core/` 内查找生成器。

## 3. 创建 secrets.h

从库中复制 `secrets.h.example` 示例到项目的 `include/secrets.h` 并指定你的网络数据：

```cpp
#define WIFI_SSID      "your-ssid"
#define WIFI_PASSWORD  "your-password"
```

将 `include/secrets.h` 添加到 `.gitignore`，以防密码进入存储库。

## 4. 配置 platformio.ini

填充项目根目录中的 `platformio.ini`：

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

将 `board` 替换为你的板（例如 `esp32-s3-devkitc-1`）。不需要在 `lib_deps` 中指定 `idryer-core` — 它在 `lib/` 中（步骤 2）。

!!! note "所有这些依赖项的用途"
    `ArduinoJson`、`PubSubClient`、`base64`、`WebSockets` 和 `Improv-WiFi-Library` 是 `idryer-core` 库本身所需的（MQTT、LAN 上的 WebSocket 访问、Wi-Fi 配置）。没有其中任何一个，构建都会失败，错误信息如 `... .h: No such file`。`MQTT_BROKER` 和 `MQTT_PORT` 标志也是强制性的 — 没有它们，核心将不会编译（`'MQTT_BROKER' was not declared`）。

## 5. 在 Config 中描述设备

接下来的一切都发生在一个文件中 — `src/main.cpp`。打开它并记录本步骤和后续步骤的代码。

`iDryer::Config` 是设备的护照。`has*` 标志告诉门户网站设备有什么，并确定发布了哪些遥测字段。

对于加热柜，在 `src/main.cpp` 的开头

```cpp
#include <iDryer.h>

static const iDryer::Config CFG = {
    .deviceType        = iDryer::DeviceType::Dryer,
    .unitsCount        = 1,
    // 外围设备：
    .hasHeater         = true,    // 受控加热器
    .hasFan            = true,    // 风扇
    .hasAirTemp        = true,    // 空气温度（SHT31）
    .hasAirHumidity    = true,    // 空气湿度（SHT31）
    .hasHeaterTemp     = true,    // 加热器温度（温度计）
    // 自动发布周期：
    .telemetryPeriodMs = 5000,
    .statusPeriodMs    = 10000,
    // 门户网站上的标识：
    .hardwareVersion   = "1.0",
    .firmwareVersion   = "0.1.0",
    .model             = "DIY Storage Cabinet",
};

static iDryer::Link s_link(CFG);
```

!!! note "has* 标志是与门户网站的合约"
    没有相应的 `false` 标志的遥测字段不会被发布。例如，如果没有 `hasAirHumidity = true`，湿度不会进入云端，即使你在代码中写入它。只包括设备中物理存在的内容。

组件和标志的列表——[系统组成](02-bom.md)。

## 6. 最小主程序

在相同的文件中，在 `Config` 块之后添加 `setup()` 和 `loop()` 函数。对于首次启动，已经足够启动链接并在 `loop()` 中运行它：

```cpp
void setup() {
    Serial.begin(115200);
    s_link.begin();
}

void loop() {
    s_link.loop();
}
```

这足以使设备连接到 Wi-Fi 并在门户网站上线。在[传感器](05-sensors.md)步骤添加传感器。

### 本章后 `src/main.cpp` 的完整版本

将上面的两个块放在一个文件中 — 这是此步骤中的整个 `src/main.cpp`：

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

前一章展示了**要添加什么**以及**更改后的完整 `src/main.cpp`**，这样你总能看到完整的画面，而不是分散的片段。

## 7. 刷入固件

```bash
pio run -e cabinet -t upload
```

## 8. 打开串行监视器

```bash
pio device monitor -b 115200
```

日志中的预期序列：

```text
[CLOUD] Connecting to WiFi...
[CLOUD] WiFi connected, IP: 192.168.1.42
[CLOUD] Provisioning device...
[CLOUD] PIN: 1234567 (expires in 600s)
```

如果设备在 `PIN: ...` 行上停止 — 这是正常的。转到绑定。

## 9. 将设备绑定到门户网站

1. 打开 [portal.idryer.org](https://portal.idryer.org/)。
2. 转到 **Add device** 部分。
3. 输入来自串行监视器的 PIN。

绑定后，设备将转换为 `Online` 状态。日志中将出现：

```text
[CLOUD] Device claimed!
[CLOUD] MQTT connected!
```

## 检查结果

在此步骤中，设备应该在门户网站上处于在线状态。传感器没有数据 — 这是预期的。如果设备未连接：

- 检查 `2.4 GHz` 网络以及 `secrets.h` 中的密码是否正确；
- 检查 ESP32 的电源（启动时 Wi-Fi 的下降是重启的常见原因）；
- 见[电源错误](../08-common-mistakes/02-power-mistakes.md)和[控制器错误](../08-common-mistakes/04-controller-mistakes.md)。

## 接下来

网络部分工作正常。转到[传感器](05-sensors.md)：连接 SHT31 和温度计并在门户网站上查看它们的数据。
