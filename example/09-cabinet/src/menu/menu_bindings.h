// AUTO-GENERATED. DO NOT EDIT.
#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "menu_types.h"
#include "menu_state.h"

typedef void (*MenuOnChangeFn)(void* ctx);

typedef enum { SCOPE_GLOBAL=0, SCOPE_PER_CONTROLLER=1 } MenuScope;

typedef struct {
  uint16_t      id;         // MENU_* enum ID
  const char*   bind;       // NVS ключ (global) или префикс (per_controller)
  ValueType     vtype;
  void*         ptr;
  bool          persist;
  MenuOnChangeFn on_change;
  bool          apply_live;
  MenuScope     scope;
} MenuBinding;

extern const MenuBinding g_bindings[];
extern const uint16_t     g_bindings_count;

#ifdef __cplusplus
extern "C" {
#endif
uint8_t menu_get_active_controller(void);
#ifdef __cplusplus
}
#endif

typedef void (*ConfigChangeHookFn)(uint16_t itemId, uint8_t unit, const char* bind);
#ifdef __cplusplus
extern "C" {
#endif
extern ConfigChangeHookFn g_config_change_hook;
void menu_set_config_change_hook(ConfigChangeHookFn hook);
#ifdef __cplusplus
}
#endif

bool menu_apply_by_bind(const char* bind, float v);
bool menu_read_by_bind(const char* bind, void* out_value);
const MenuBinding* menu_find_bind(const char* bind);

// Bootstrap sync: проходит по всем биндингам и записывает текущие
// значения MenuState в g_menu_cache. Вызывать один раз на boot
// ПОСЛЕ menu.loadFromNVS() — иначе menu_buildFullJson() отдаст
// дефолтные значения (cache живёт отдельно от MenuState).
void menu_sync_state_to_cache();
