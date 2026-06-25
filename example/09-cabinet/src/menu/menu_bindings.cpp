// AUTO-GENERATED. DO NOT EDIT.
#include <string.h>
#include <stdio.h>
#include "menu_bindings.h"
#include "menu_nvs_io.h"
#include "menu_cache.h"   // g_menu_cache — sync inside menu_apply_by_bind

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

extern MenuState menu;
const MenuBinding g_bindings[] = {
  {MENU_TARGET_TEMP, "target_temp", VT_U16, (void*)&menu.target_temp, true, nullptr, false, SCOPE_GLOBAL},
  {MENU_HYSTERESIS, "hysteresis", VT_U8, (void*)&menu.hysteresis, true, nullptr, false, SCOPE_GLOBAL},
  {MENU_UNITS_COUNT, "units_count", VT_U8, (void*)&menu.units_count, true, nullptr, false, SCOPE_GLOBAL},
  {MENU_LANGUAGE, "language", VT_U8, (void*)&menu.language, true, nullptr, false, SCOPE_GLOBAL},
};
const uint16_t g_bindings_count = sizeof(g_bindings)/sizeof(g_bindings[0]);

ConfigChangeHookFn g_config_change_hook = nullptr;

void menu_set_config_change_hook(ConfigChangeHookFn hook) {
  g_config_change_hook = hook;
}

const MenuBinding* menu_find_bind(const char* bind) {
  if (!bind) return nullptr;
  for (uint16_t i=0;i<g_bindings_count;i++)
    if (strcmp(g_bindings[i].bind, bind) == 0) return &g_bindings[i];
  return nullptr;
}

static inline void store_value(const MenuBinding& b, float v, uint8_t idx) {
  switch (b.vtype) {
    case VT_F32:  if (b.scope==SCOPE_GLOBAL) *(float*)b.ptr    = v; else ((float*)b.ptr)[idx]    = v; break;
    case VT_U16:  if (b.scope==SCOPE_GLOBAL) *(uint16_t*)b.ptr = (uint16_t)v; else ((uint16_t*)b.ptr)[idx] = (uint16_t)v; break;
    case VT_U8:   if (b.scope==SCOPE_GLOBAL) *(uint8_t*)b.ptr  = (uint8_t)v;  else ((uint8_t*)b.ptr)[idx]  = (uint8_t)v;  break;
    case VT_I32:  if (b.scope==SCOPE_GLOBAL) *(int32_t*)b.ptr  = (int32_t)v;  else ((int32_t*)b.ptr)[idx]  = (int32_t)v;  break;
    case VT_BOOL: if (b.scope==SCOPE_GLOBAL) *(bool*)b.ptr     = (bool)(v!=0.0f); else ((bool*)b.ptr)[idx]     = (bool)(v!=0.0f); break;
    case VT_U32:  if (b.scope==SCOPE_GLOBAL) *(uint32_t*)b.ptr = (uint32_t)v; else ((uint32_t*)b.ptr)[idx] = (uint32_t)v; break;
  }
}

static inline void read_value(const MenuBinding& b, void* out_value, uint8_t idx) {
  switch (b.vtype) {
    case VT_F32:  *(float*)out_value    = (b.scope==SCOPE_GLOBAL)? *(float*)b.ptr    : ((float*)b.ptr)[idx]; break;
    case VT_U16:  *(uint16_t*)out_value = (b.scope==SCOPE_GLOBAL)? *(uint16_t*)b.ptr : ((uint16_t*)b.ptr)[idx]; break;
    case VT_U8:   *(uint8_t*)out_value  = (b.scope==SCOPE_GLOBAL)? *(uint8_t*)b.ptr  : ((uint8_t*)b.ptr)[idx]; break;
    case VT_I32:  *(int32_t*)out_value  = (b.scope==SCOPE_GLOBAL)? *(int32_t*)b.ptr  : ((int32_t*)b.ptr)[idx]; break;
    case VT_BOOL: *(bool*)out_value     = (b.scope==SCOPE_GLOBAL)? *(bool*)b.ptr     : ((bool*)b.ptr)[idx]; break;
    case VT_U32:  *(uint32_t*)out_value = (b.scope==SCOPE_GLOBAL)? *(uint32_t*)b.ptr : ((uint32_t*)b.ptr)[idx]; break;
  }
}

static inline void build_nvs_key(const MenuBinding& b, uint8_t idx, char* out, size_t cap){
  if (b.scope == SCOPE_GLOBAL) {
    strncpy(out, b.bind, cap - 1);
    out[cap - 1] = '\0';
  } else {
    snprintf(out, cap, "%s_%u", b.bind, (unsigned)idx);
  }
}

bool menu_read_by_bind(const char* bind, void* out_value) {
  const MenuBinding* b = menu_find_bind(bind);
  if (!b || !out_value) return false;
  uint8_t idx = 0;
  if (b->scope == SCOPE_PER_CONTROLLER) idx = menu_get_active_controller();
  read_value(*b, out_value, idx);
  return true;
}

bool menu_apply_by_bind(const char* bind, float v) {
  const MenuBinding* b = menu_find_bind(bind);
  if (!b) return false;
  uint8_t idx = 0;
  if (b->scope == SCOPE_PER_CONTROLLER) idx = menu_get_active_controller();
  store_value(*b, v, idx);

  // Sync into g_menu_cache so menu_buildFullJson() returns the fresh value.
  // Cache lives separately from MenuState — without this sync the
  // re-published config after commands/set would show stale data.
  {
    float cached = 0.0f;
    switch (b->vtype) {
      case VT_F32:  cached = (b->scope==SCOPE_GLOBAL) ? *(const float*)b->ptr    : ((const float*)b->ptr)[idx]; break;
      case VT_U16:  cached = (float)((b->scope==SCOPE_GLOBAL) ? *(const uint16_t*)b->ptr : ((const uint16_t*)b->ptr)[idx]); break;
      case VT_U8:   cached = (float)((b->scope==SCOPE_GLOBAL) ? *(const uint8_t*)b->ptr  : ((const uint8_t*)b->ptr)[idx]); break;
      case VT_I32:  cached = (float)((b->scope==SCOPE_GLOBAL) ? *(const int32_t*)b->ptr  : ((const int32_t*)b->ptr)[idx]); break;
      case VT_BOOL: cached = ((b->scope==SCOPE_GLOBAL) ? *(const bool*)b->ptr    : ((const bool*)b->ptr)[idx]) ? 1.0f : 0.0f; break;
      case VT_U32:  cached = (float)((b->scope==SCOPE_GLOBAL) ? *(const uint32_t*)b->ptr : ((const uint32_t*)b->ptr)[idx]); break;
    }
    g_menu_cache.setFloat(b->id, cached, (b->scope==SCOPE_GLOBAL) ? 0 : idx);
  }

  if (b->persist) {
    char key[16];
    build_nvs_key(*b, idx, key, sizeof(key));
    menu_nvs_begin();
    switch (b->vtype) {
      case VT_F32:  ee_store_field<float>(   key, (b->scope==SCOPE_GLOBAL)? *(float*)b->ptr    : ((float*)b->ptr)[idx]); break;
      case VT_U16:  ee_store_field<uint16_t>(key, (b->scope==SCOPE_GLOBAL)? *(uint16_t*)b->ptr : ((uint16_t*)b->ptr)[idx]); break;
      case VT_U8:   ee_store_field<uint8_t>( key, (b->scope==SCOPE_GLOBAL)? *(uint8_t*)b->ptr  : ((uint8_t*)b->ptr)[idx]); break;
      case VT_I32:  ee_store_field<int32_t>( key, (b->scope==SCOPE_GLOBAL)? *(int32_t*)b->ptr  : ((int32_t*)b->ptr)[idx]); break;
      case VT_BOOL: ee_store_field<bool>(    key, (b->scope==SCOPE_GLOBAL)? *(bool*)b->ptr     : ((bool*)b->ptr)[idx]); break;
      case VT_U32:  ee_store_field<uint32_t>(key, (b->scope==SCOPE_GLOBAL)? *(uint32_t*)b->ptr : ((uint32_t*)b->ptr)[idx]); break;
    }
    menu_nvs_end();
  }
  if (b->on_change) b->on_change((void*)b->ptr);
  if (g_config_change_hook) g_config_change_hook(b->id, idx, b->bind);
  return true;
}

void menu_sync_state_to_cache() {
  for (uint16_t i = 0; i < g_bindings_count; i++) {
    const MenuBinding& b = g_bindings[i];
    if (b.scope == SCOPE_GLOBAL) {
      float v = 0.0f;
      switch (b.vtype) {
        case VT_F32:  v = *(const float*)b.ptr; break;
        case VT_U16:  v = (float)*(const uint16_t*)b.ptr; break;
        case VT_U8:   v = (float)*(const uint8_t*)b.ptr; break;
        case VT_I32:  v = (float)*(const int32_t*)b.ptr; break;
        case VT_BOOL: v = (*(const bool*)b.ptr) ? 1.0f : 0.0f; break;
        case VT_U32:  v = (float)*(const uint32_t*)b.ptr; break;
      }
      g_menu_cache.setFloat(b.id, v, 0);
    } else {
      // per_controller: копируем NUM_UNITS значений.
      for (uint8_t u = 0; u < MENU_MAX_UNITS; u++) {
        float v = 0.0f;
        switch (b.vtype) {
          case VT_F32:  v = ((const float*)b.ptr)[u]; break;
          case VT_U16:  v = (float)((const uint16_t*)b.ptr)[u]; break;
          case VT_U8:   v = (float)((const uint8_t*)b.ptr)[u]; break;
          case VT_I32:  v = (float)((const int32_t*)b.ptr)[u]; break;
          case VT_BOOL: v = ((const bool*)b.ptr)[u] ? 1.0f : 0.0f; break;
          case VT_U32:  v = (float)((const uint32_t*)b.ptr)[u]; break;
        }
        g_menu_cache.setFloat(b.id, v, u);
      }
    }
  }
}
