---
title: "Starting firmware on idryer-core: first launch and device pairing"
description: "Creating a PlatformIO project based on idryer-core library: platformio.ini, secrets.h, device Config, first ESP32 firmware upload and device pairing to the iDryer portal."
---

# Starting firmware on the core

On this page you create a firmware project, bring the ESP32 to Online state on the portal, and verify that the network part works. Sensors and heating logic will be added in the following steps.

The approach is built on the `iDryer::Link` facade. You describe the device with a single `iDryer::Config` structure, call `link.begin()` and `link.loop()` — the core handles all network connection itself.

## 1. Prepare the tools

You will need:

- VS Code with PlatformIO extension;
- USB cable;
- Wi-Fi network `2.4 GHz` (ESP32 does not work with `5 GHz` only networks).

For information on what controller firmware is and how it gets into the board — see [Controller firmware](../02-controllers/11-flashing-controller.md).

## 2. Create a project

In PlatformIO a project is a folder with a fixed structure. Create a project folder (for example `my-cabinet`) and open it in VS Code. Inside should be these files:

```text
my-cabinet/
├── platformio.ini        # build settings (fill in step 4)
├── include/
│   └── secrets.h         # Wi-Fi login and password (step 3)
├── lib/
│   └── idryer-core/      # core library (symlink or copy)
└── src/
    └── main.cpp          # device code: Config + setup() + loop()
```

All code fragments below go into these specific files — each step indicates which file. Create the `include/`, `lib/` and `src/` folders manually if they don't exist.

Place the `idryer-core` library in `lib/` — PlatformIO automatically finds libraries there. The easiest way is to create a symlink to the downloaded library:

```bash
ln -s /path/to/idryer-core lib/idryer-core
```

This is also required for menu generation (chapter 6) — the hook looks for the generator inside `lib/idryer-core/`.

## 3. Create secrets.h

Copy the `secrets.h.example` example from the library to `include/secrets.h` in your project and specify your network credentials:

```cpp
#define WIFI_SSID      "your-ssid"
#define WIFI_PASSWORD  "your-password"
```

Add `include/secrets.h` to `.gitignore` so the password doesn't end up in the repository.

## 4. Configure platformio.ini

Fill in `platformio.ini` in the project root:

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

Replace `board` with your board (for example, `esp32-s3-devkitc-1`). You don't need to specify `idryer-core` in `lib_deps` — it's located in `lib/` (step 2).

!!! note "Why all these dependencies"
    `ArduinoJson`, `PubSubClient`, `base64`, `WebSockets` and `Improv-WiFi-Library` are required by the `idryer-core` library itself (MQTT, WebSocket access over LAN, Wi-Fi provisioning). Without any of them the build will fail with an error like `... .h: No such file`. The `MQTT_BROKER` and `MQTT_PORT` flags are also required — without them the core won't compile (`'MQTT_BROKER' was not declared`).

## 5. Describe the device in Config

Next, everything happens in one file — `src/main.cpp`. Open it and write the code from this and the following steps.

`iDryer::Config` is the device's passport. The `has*` flags tell the portal what the device has and determine which telemetry fields are published.

For a heated cabinet, add to the beginning of `src/main.cpp`:

```cpp
#include <iDryer.h>

static const iDryer::Config CFG = {
    .deviceType        = iDryer::DeviceType::Dryer,
    .unitsCount        = 1,
    // Peripherals:
    .hasHeater         = true,    // controlled heater
    .hasFan            = true,    // fan
    .hasAirTemp        = true,    // air temperature (SHT31)
    .hasAirHumidity    = true,    // air humidity (SHT31)
    .hasHeaterTemp     = true,    // heater temperature (thermistor)
    // Auto-publish periods:
    .telemetryPeriodMs = 5000,
    .statusPeriodMs    = 10000,
    // Portal identification:
    .hardwareVersion   = "1.0",
    .firmwareVersion   = "0.1.0",
    .model             = "DIY Storage Cabinet",
};

static iDryer::Link s_link(CFG);
```

!!! note "has* flags are a contract with the portal"
    A telemetry field whose corresponding flag is `false` is not published. For example, without `hasAirHumidity = true` humidity won't be sent to the cloud, even if you write it in the code. Enable only what physically exists in the device.

For a complete list of components and flags — see [System components](02-bom.md).

## 6. Minimal main

In the same file after the `Config` block, add the `setup()` and `loop()` functions. For the first launch it's enough to initialize the link and run it in `loop()`:

```cpp
void setup() {
    Serial.begin(115200);
    s_link.begin();
}

void loop() {
    s_link.loop();
}
```

This is enough for the device to connect to Wi-Fi and reach the portal. We'll add sensors in the [Sensors](05-sensors.md) step.

### Complete `src/main.cpp` after this chapter

Combine both blocks above into one file — this is the entire `src/main.cpp` at this stage:

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

Each chapter shows **what to add** and **the complete `src/main.cpp` after changes**, so you always see the full picture rather than scattered pieces.

## 7. Flash the firmware

```bash
pio run -e cabinet -t upload
```

## 8. Open Serial Monitor

```bash
pio device monitor -b 115200
```

Expected sequence in the log:

```text
[CLOUD] Connecting to WiFi...
[CLOUD] WiFi connected, IP: 192.168.1.42
[CLOUD] Provisioning device...
[CLOUD] PIN: 1234567 (expires in 600s)
```

If the device stops at the `PIN: ...` line — this is normal. Proceed to pairing.

## 9. Pair the device with the portal

1. Open [portal.idryer.org](https://portal.idryer.org/).
2. Go to the **Add device** section.
3. Enter the PIN from Serial Monitor.

After pairing, the device will transition to `Online` status. The log will show:

```text
[CLOUD] Device claimed!
[CLOUD] MQTT connected!
```

## Verification

At this stage the device should be Online on the portal. There's no sensor data yet — this is expected. If the device doesn't connect:

- verify that the `2.4 GHz` network and password in `secrets.h` are correct;
- check the ESP32 power supply (voltage drops on startup are a common cause of resets);
- see [Power mistakes](../08-common-mistakes/02-power-mistakes.md) and [Controller mistakes](../08-common-mistakes/04-controller-mistakes.md).

## What's next

The network part is working. Move on to [Sensors](05-sensors.md): we'll connect the SHT31 and thermistor and see their data on the portal.
