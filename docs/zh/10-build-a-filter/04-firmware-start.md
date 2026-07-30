---
title: "智能过滤器：固件启动和门户绑定"
description: "过滤器固件框架基于idryer-core：非标设备类型的Config、首次启动、通过PIN码绑定到账户。"
---

# 固件启动

项目框架完全模仿[加热柜示例中的章节](../09-build-a-device/04-firmware-start.md)：PlatformIO、`secrets.h`、`lib/`中的`idryer-core`，同样的`platformio.ini`（只需将环境名改为`filter`）。这里只讲不同的部分。

## Config：非标设备类型

过滤器既没有加热器，也没有生态系统字典中的气候传感器。从字典功能中它只有风机。在`src/main.cpp`中：

```cpp
#include <iDryer.h>

static const iDryer::Config CFG = {
    .deviceType        = iDryer::DeviceType::Unknown, // 非标设备
    .unitsCount        = 1,
    // 外围设备：字典中只有风机。
    .hasFan            = true,
    // 自动发布周期：
    .telemetryPeriodMs = 5000,
    .statusPeriodMs    = 10000,
    // 门户识别：
    .hardwareVersion   = "1.0",
    .firmwareVersion   = "0.1.0",
    .model             = "DIY Air Filter",
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

!!! note "DeviceType::Unknown是正常的"
    类型`Unknown`意思是"门户不知道这个产品"。从前这是个问题：门户没有未知类型的卡片。现在这是标准做法：设备的整个界面由卡片清单描述（[第6章](06-card.md)），门户根据清单构建卡片。类型只对iDryer自己的产品需要，那些有官方卡片的。

`hasFan = true`标志给我们免费得到：遥测中的`fanStatus`字段、卡片上的"风机"单元、以及清单中的实体——全部来自生态系统字典。

## Config中没有VOC传感器——这是应该的

注意：`Config`中没有`hasVoc`标志。`has*`字典描述生态系统知道的外围设备。你的自定义传感器用另外两种机制加入：在遥测中加入它的读数（你自己的字段）并在卡片清单中声明它——这是接下来的两章。这正是这种方法的精妙之处：不需要为每个新设备扩展字典。

## 首次启动和绑定

程序与加热柜示例相同：

1. 烧入固件，打开Serial Monitor。
2. 设备启动Wi-Fi（数据来自`secrets.h`），注册，并打印PIN：
   ```text
   [CLOUD] PIN: 1234567 (expires in 600s)
   ```
3. 在[门户](https://portal.idryer.org/) —— "添加设备" → 输入PIN。
4. 绑定后日志中出现`Device claimed!`，设备转为`Online`。

详细的绑定说明、Wi-Fi错误和重新绑定——见[加热柜示例中的章节](../09-build-a-device/04-firmware-start.md)。

设备已在门户上可见，但卡片还几乎是空的——还没有数据。继续连接传感器。
