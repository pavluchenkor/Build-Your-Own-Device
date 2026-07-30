---
title: "idryer-core上的韌體啟動：首次執行和門戶綁定"
description: "在idryer-core函式庫上建立PlatformIO項目：platformio.ini、secrets.h、設備Config、首次燒錄ESP32和與iDryer門戶綁定。"
---

# 核心上的韌體啟動

本頁你建立一個韌體項目，將ESP32帶到門戶上的線上狀態，並驗證網路部分工作。感應器和加熱邏輯將在後續步驟中新增。

該方法基於`iDryer::Link`外觀。你用一個`iDryer::Config`結構描述設備，呼叫`link.begin()`和`link.loop()`——核心會自動處理所有網路連接。

## 1. 準備工具

你需要：

- VS Code及PlatformIO擴充功能；
- USB連接線；
- `2.4 GHz` Wi-Fi網路（ESP32不支援僅`5 GHz`的網路）。

什麼是控制器韌體以及它如何進入板——[控制器韌體](../02-controllers/11-flashing-controller.md)。

## 2. 建立項目

在PlatformIO中，項目是具有固定結構的資料夾。建立項目資料夾（例如`my-cabinet`）並在VS Code中打開。內部應該有這些檔案：

```text
my-cabinet/
├── platformio.ini        # 構建設定（步驟4填寫）
├── include/
│   └── secrets.h         # Wi-Fi登入和密碼（步驟3）
├── lib/
│   └── idryer-core/      # 核心函式庫（符號連結或複本）
└── src/
    └── main.cpp          # 設備程式碼：Config + setup() + loop()
```

下面代碼片段的所有片段都放在這些檔案中——每個步驟都指定放在哪裡。如果`include/`、`lib/`和`src/`資料夾不存在，請手動建立。

將`idryer-core`函式庫放在`lib/`中——PlatformIO會自動在那裡找到函式庫。最簡單的方法是為下載的函式庫建立符號連結：

```bash
ln -s /path/to/idryer-core lib/idryer-core
```

菜單生成也需要這個（第6章）——hook在`lib/idryer-core/`內尋找生成器。

## 3. 建立secrets.h

從函式庫複製示例`secrets.h.example`到你的項目`include/secrets.h`並指定你的網路資料：

```cpp
#define WIFI_SSID      "your-ssid"
#define WIFI_PASSWORD  "your-password"
```

將`include/secrets.h`新增到`.gitignore`，以防止密碼進入儲存庫。

## 4. 配置platformio.ini

在項目根目錄填寫`platformio.ini`：

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

將`board`替換為你的板（例如`esp32-s3-devkitc-1`）。`idryer-core`本身不需要在`lib_deps`中指定——它位於`lib/`（步驟2）。

!!! note "為什麼需要所有這些依賴項"
    `ArduinoJson`、`PubSubClient`、`base64`、`WebSockets`和`Improv-WiFi-Library`由`idryer-core`函式庫本身需要（MQTT、LAN上的WebSocket存取、Wi-Fi佈建）。沒有其中任何一個，構建都會失敗並顯示錯誤消息，如`... .h: No such file`。`MQTT_BROKER`和`MQTT_PORT`標誌也是必需的——沒有它們，核心無法編譯（`'MQTT_BROKER' was not declared`）。

## 5. 在Config中描述設備

接下來的一切都在一個檔案中進行——`src/main.cpp`。打開它並記錄此步驟和後續步驟的程式碼。

`iDryer::Config`是設備的護照。`has*`標誌告訴門戶設備有什麼，並確定發佈哪些遙測欄位。

對於加熱的櫃子，在`src/main.cpp`的開頭

```cpp
#include <iDryer.h>

static const iDryer::Config CFG = {
    .deviceType        = iDryer::DeviceType::Dryer,
    .unitsCount        = 1,
    // 外設：
    .hasHeater         = true,    // 可控加熱器
    .hasFan            = true,    // 風扇
    .hasAirTemp        = true,    // 空氣溫度（SHT31）
    .hasAirHumidity    = true,    // 空氣濕度（SHT31）
    .hasHeaterTemp     = true,    // 加熱器溫度（溫敏電阻）
    // 自動發佈週期：
    .telemetryPeriodMs = 5000,
    .statusPeriodMs    = 10000,
    // 門戶上的識別：
    .hardwareVersion   = "1.0",
    .firmwareVersion   = "0.1.0",
    .model             = "DIY Storage Cabinet",
};

static iDryer::Link s_link(CFG);
```

!!! note "has*標誌——這是與門戶的契約"
    對應`has*`標誌為`false`的遙測欄位不會發佈。例如，沒有`hasAirHumidity = true`，濕度將不會進入雲端，即使你在程式碼中寫入它。只啟用設備中實際存在的內容。

元件清單和標誌——[系統組成](02-bom.md)。

## 6. 最小主函式

在相同檔案的`Config`塊之後，新增`setup()`和`loop()`函式。對於首次啟動，足以啟動連結並在`loop()`中執行它：

```cpp
void setup() {
    Serial.begin(115200);
    s_link.begin();
}

void loop() {
    s_link.loop();
}
```

這足以讓設備連接到Wi-Fi並進入門戶。感應器將在[感應器](05-sensors.md)步驟中新增。

### 本章後的完整`src/main.cpp`

將上述兩個塊放入一個檔案——這是此步驟的整個`src/main.cpp`：

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

前面的章節展示了**要新增什麼**和**變更後的完整`src/main.cpp`**，所以你始終看到整體情況，而不是零散的片段。

## 7. 刷新

```bash
pio run -e cabinet -t upload
```

## 8. 打開Serial Monitor

```bash
pio device monitor -b 115200
```

日誌中的預期序列：

```text
[CLOUD] Connecting to WiFi...
[CLOUD] WiFi connected, IP: 192.168.1.42
[CLOUD] Provisioning device...
[CLOUD] PIN: 1234567 (expires in 600s)
```

如果設備停在`PIN: ...`行——這是正常的。繼續綁定。

## 9. 將設備綁定到門戶

1. 打開[portal.idryer.org](https://portal.idryer.org/)。
2. 轉到**Add device**部分。
3. 輸入Serial Monitor中的PIN。

綁定後，設備轉為`線上`狀態。在日誌中出現：

```text
[CLOUD] Device claimed!
[CLOUD] MQTT connected!
```

## 驗證結果

在此步驟，設備應在門戶上線。感應器資料還沒有——這是預期的。如果設備無法連接：

- 驗證網路是`2.4 GHz`且`secrets.h`中的密碼正確；
- 檢查ESP32電源（Wi-Fi啟動時的壓降是常見的重啟原因）；
- 見[電源錯誤](../08-common-mistakes/02-power-mistakes.md)和[控制器錯誤](../08-common-mistakes/04-controller-mistakes.md)。

## 下一步

網路部分工作。轉到[感應器](05-sensors.md)：連接SHT31和溫敏電阻，並在門戶中看到它們的資料。
