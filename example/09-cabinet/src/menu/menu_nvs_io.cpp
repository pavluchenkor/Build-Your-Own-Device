
// Auto-generated. Do not edit.
#include "menu_nvs_io.h"

Preferences g_menu_prefs;

bool menu_nvs_begin(){
  return g_menu_prefs.begin(NVS_MENU_NAMESPACE, /*readOnly=*/false);
}

void menu_nvs_end(){
  g_menu_prefs.end();
}
