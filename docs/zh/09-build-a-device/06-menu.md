---
title: "YAML 格式的设备菜单：NVS 和门户网站中的设置"
description: "如何在 idryer-core 上的 menu.yaml 中描述设备菜单：目标温度和磁滞保存在 NVS 中并在 iDryer 门户网站上显示为小部件。"
---

# YAML 格式的菜单

菜单是设备的一组设置：目标温度、磁滞、风扇阈值。在 `idryer-core` 上，菜单用单个文件 `menu.yaml` 描述，所有其他的 — C++ 结构、保存到非易失性内存（NVS）和发布到门户网站 — 自动生成。

这是核心库的关键块之一。你不编写设置存储代码，也不为门户网站设计格式 — 你只在 YAML 中列出参数。

## 为什么需要菜单

在前面的步骤之后，设备读取传感器，但所有阈值都"硬编码"在代码中。菜单立即解决三个任务：

- **存储**：值在重启后保持（NVS）；
- **从门户网站管理**：每个参数都成为小部件（滑块、开关）；
- **单一信息源**：一个文件描述内存和界面。

## 它如何工作

单个文件 `menu.yaml` 在构建期间通过生成器：

```text
menu.yaml → （构建 pio run） → src/menu/ 中的 C++ 文件 + NVS + 门户网站 JSON
```

带有 `role:` 字段的项对门户网站可见并显示为小部件。没有 `role:` 的项是私有的，仅用于设备内部逻辑。

!!! warning "不编辑生成的文件"
    文件 `menu_state.*`、`menu_bindings.*`、`menu_ids.h` 等是由生成器创建的。只编辑 `menu.yaml` 并重新构建 — 否则你的更改会被覆盖。

## 步骤 1. 复制模板

库中有一个菜单模板。将其复制到你的项目：

```bash
mkdir -p src/menu
cp path/to/idryer-core/menu/menu.template.yaml src/menu/menu.yaml
```

## 步骤 2. 在构建时连接生成

从 `iDryer-Storage` 项目复制钩子示例（可以按原样使用，不需要配置）：

```bash
mkdir -p extra_scripts
cp path/to/iDryer-Storage/extra_scripts/pre_gen_menu.py extra_scripts/pre_gen_menu.py
```

然后在 `platformio.ini` 中添加到 `[env:cabinet]` 部分一行 `-Isrc/menu`（以便代码看到 `#include <menu_state.h>`）并通过 `extra_scripts` 连接钩子：

```ini
[env:cabinet]
; ... 第 4 章的 platform / board / lib_deps — 没有变化 ...

build_flags =
    -Isrc/menu                      ; ← 添加了：生成菜单的路径
    -DIDRYER_API_BASE='"https://portal.idryer.org/api"'
    -DMQTT_BROKER='"mqtt.idryer.org"'
    -DMQTT_PORT=8883
    -DMQTT_USE_TLS=1

extra_scripts =                     ; ← 添加了
    pre:extra_scripts/pre_gen_menu.py
```

钩子将自动通过 `lib/idryer-core/menu/menu_gen.py` 路径查找生成器，因此库应该通过 `lib/`（符号链接或副本）连接，如第 4 章所述。

## 步骤 3. 描述柜的参数

打开 `src/menu/menu.yaml`。模板已有带 `children` 数组的根项 `root` 和参数示例。删除示例（`my_param`、`my_flag`、`my_mode_group`）并在 `children` 中添加你的。最后两个项 — `units_count` 和 `language` — 保留：这是与门户网站的固定合约。

对于基本柜子，几个参数就足够了。

存储目标温度：

```yaml
- id: target_temp
  type: value
  role: storage.target_temperature   # 在门户网站上创建小部件
  title: { ru: "ТЕМПЕРАТУРА", en: "TARGET TEMP" }
  unit:  { ru: "°C", en: "°C" }
  vtype: uint16
  min: 30
  max: 50
  step: 1
  bind: target_temp            # NVS 密钥（≤ 15 字符）
  persist: true
  scope: global
  default: 45
```

磁滞（温度可以低于目标多少度，然后加热再次打开）：

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

!!! note "role: — 这是一个封闭的列表"
    `role:` 的值不能任意发明 — 它必须来自核心合约的 `canonical_roles` 列表。如果没有合适的角色，构建将停止并显示允许的列表。对于存储柜，适合 `storage.*` 系列的角色：`storage.target_temperature`、`storage.target_humidity`、`storage.start`、`storage.stop`。完整列表在 `menu.template.yaml` 的顶部。没有 `role:` 的参数（如上面的磁滞）作为内部设置工作：存储在 NVS 中，但不输出到门户网站。

不能违反的限制：

- `bind` — 不超过 15 个字符（NVS 密钥限制）；
- 不在 `menu.yaml` 中添加 `widget:` 字段 — 小部件类型由 `role:` 的合约确定。

!!! warning "检查模板中的 ignore_external_cmd 项"
    模板有 `ignore_external_cmd` 项，其 `bind` 为 19 个字符，超过 15 的限制。如果保留原样，生成将失败：`bind 'ignore_external_cmd' ... 具有 19 个字符，限制为 15`。要么删除这个项，要么将 `bind` 缩短到 `ign_ext_cmd`（如在真实产品中）。对于基本柜子，你可以简单地删除它。

## 步骤 4. 构建项目并检查生成

```bash
pio run -e cabinet
```

在构建期间，pre-hook 将自动放置依赖项（一次）并生成 C++ 菜单文件。如果 `menu.yaml` 未改变 — 生成被跳过（`up-to-date`）。

检查生成是否通过。在构建日志中，出现关于菜单生成的一行，在 `src/menu/` 文件夹中 — 生成的文件：

```text
src/menu/
├── menu.yaml          # 你的文件（源）
├── menu_state.h/.cpp  # 带有所有参数的菜单对象
├── menu_bindings.*    # 按 bind 的访问 + NVS 写入
├── menu_ids.h
└── menu_meta.h        # 及其他
```

如果构建失败，出现有关未知 `role:` 的消息 — 这意味着角色没有写在 `canonical_roles` 列表中。纠正它并重新构建。标记为 autogen 的文件不要手动编辑。

## 步骤 5. 在主文件中连接菜单

要使用菜单代码，在 `src/main.cpp` 中连接两个东西：

1. 生成菜单的标题：

    ```cpp
    #include <menu_state.h>      # 带有所有参数的菜单对象
    ```

2. 在 `setup()` 中加载默认值 — **在** `s_link.begin()` **之前**：

    ```cpp
    menu.initDefaults();         # 从 YAML 设置默认值
    ```

之后，参数可通过全局 `menu` 对象访问：

```cpp
uint16_t target = menu.target_temp;   // 直接访问值
```

在下一步的加热逻辑中，你使用这些值。当用户在门户网站上更改参数时，核心自动应用新值并将其保存到 NVS。

## 本章后 `src/main.cpp` 的完整版本

相对于上一章，只添加了两行（标记为 `// ← 第 6 章`）：菜单连接和 `menu.initDefaults()`。

## 检查结果

刷入后：

- 门户网站上的设备卡中出现目标温度设置；
- 在门户网站上改变值保存并在重启后保持；
- 内部参数（磁滞）在代码中通过 `menu` 可用。

## 接下来

设置已描述并存储。现在在[加热控制](07-heating-control.md)中将它们与硬件连接：加热器保持目标温度，风扇按阈值打开。
