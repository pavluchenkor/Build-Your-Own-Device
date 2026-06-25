// Auto-generated. Do not edit.
#include <stddef.h>
#include "menu_ids.h"
#include "menu_types.h"
#include "menu_state.h"

extern MenuState menu;

const MenuItem g_menu[MENU__COUNT] = {
  [0] = {
    MENU_ROOT, { "MY DEVICE", "MY DEVICE" }, { nullptr, nullptr },
    MN_SUBMENU, -1, 1, 4,
    { { NULL }, { VT_F32, NULL, 0, 0, 0, NULL, false } },
    -1, 0
  },
  [1] = {
    MENU_TARGET_TEMP, { "ТЕМПЕРАТУРА", "TARGET TEMP" }, { "°C", "°C" },
    MN_VALUE, 0, -1, 0,
    { { NULL }, { VT_U16, (void*)&menu.target_temp, 30, 50, 1, nullptr, false } },
    -1, 0
  },
  [2] = {
    MENU_HYSTERESIS, { "ГИСТЕРЕЗИС", "HYSTERESIS" }, { "°C", "°C" },
    MN_VALUE, 0, -1, 0,
    { { NULL }, { VT_U8, (void*)&menu.hysteresis, 1, 5, 1, nullptr, false } },
    -1, 0
  },
  [3] = {
    MENU_UNITS_COUNT, { "КОЛ-ВО ЮНИТОВ", "UNITS" }, { nullptr, nullptr },
    MN_VALUE, 0, -1, 0,
    { { NULL }, { VT_U8, (void*)&menu.units_count, 1, 1, 1, nullptr, false } },
    -1, 0
  },
  [4] = {
    MENU_LANGUAGE, { "ЯЗЫК", "LANGUAGE" }, { nullptr, nullptr },
    MN_VALUE, 0, -1, 0,
    { { NULL }, { VT_U8, (void*)&menu.language, 0, 1, 1, nullptr, false } },
    -1, 0
  },
};
