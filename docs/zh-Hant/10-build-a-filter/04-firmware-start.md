---
title: "智慧濾清器：韌體啟動與入口網站綁定"
description: "濾清器韌體框架在 idryer-core 上：非標準裝置型別的 Config、首次啟動、透過 PIN 碼綁定到帳戶。"
---

# 韌體啟動

專案框架完全重複[機櫃範例的章節](../09-build-a-device/04-firmware-start.md)：PlatformIO、`secrets.h`、`lib/` 中的 `idryer-core`、相同的 `platformio.ini`（只需將環境名稱改為 `filter`）。這裡只是差異部分。

## Config：非標準裝置型別

濾清器沒有加熱器，也沒有生態系統辭彙中的氣候感測器。從「辭彙」技能中，它只有風扇。在 `src/main.cpp` 中：

```cpp
#include <iDryer.h>

static const iDryer::Config CFG = {
    .deviceType        = iDryer::DeviceType::Unknown, // 非標準裝置
    .unitsCount        = 1,
    // 週邊：生態系統辭彙中我們只有風扇
    .hasFan            = true,
    // 自動發佈週期：
    .telemetryPeriodMs = 5000,
    .statusPeriodMs    = 10000,
    // 在入口網站上的識別：
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

!!! note "DeviceType::Unknown 是正常的"
    `Unknown` 型別意味著「入口網站不知道這種產品」。過去這是個問題：入口網站沒有未知型別的卡片。現在是標準路徑：卡片清單將完全描述裝置介面（[第 6 章](06-card.md)），入口網站會根據它組建卡片。型別只對 iDryer 自有產品需要，它們有品牌卡片。

`hasFan = true` 標誌給了我們免費的：遙測中的 `fanStatus` 欄位、卡片上的「風扇」儲存格和清單中的實體——全部來自生態系統辭彙。

## 在 Config 中沒有 VOC 感測器——不應該有

注意：在 `Config` 中沒有「hasVoc」標誌。`has*` 辭彙描述生態系統知道的週邊。你的自訂感測器不是透過辭彙新增，而是透過兩個其他機制：你會向遙測新增它的讀數作為你的欄位，並在卡片清單中宣告它——這是接下來的兩章。這就是這種方法的本質：不需要為每個新裝置擴展辭彙。

## 首次啟動和綁定

程序與機櫃範例中的沒有區別：

1. 燒錄韌體到主板，打開序列監視器。
2. 裝置連上 Wi-Fi（使用 `secrets.h` 中的設定），完成註冊並輸出 PIN：
   ```text
   [CLOUD] PIN: 1234567 (expires in 600s)
   ```
3. 在[入口網站](https://portal.idryer.org/)——「新增裝置」→ 輸入 PIN。
4. 綁定後，日誌中會出現 `Device claimed!`，裝置會轉到 `Online`。

詳細的綁定解析、Wi-Fi 錯誤和重新綁定——見[機櫃範例的章節](../09-build-a-device/04-firmware-start.md)。

裝置在入口網站上已經可見，但卡片現在幾乎是空的——還沒有資料。接著來連接感測器。
