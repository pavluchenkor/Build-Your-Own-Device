
// Auto-generated. Do not edit.
#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "menu_ids.h"

typedef enum { MN_SUBMENU, MN_ACTION, MN_VALUE, MN_TOGGLE } MenuType;
typedef enum { VT_F32, VT_U16, VT_U8, VT_I32, VT_BOOL, VT_U32} ValueType;

typedef struct {
  ValueType vtype;
  void*     ptr;
  float     minv, maxv, step;
  void    (*on_change)(void*);
  bool      apply_live;
} ValueSpec;

typedef struct MenuItem {
  uint16_t id;
  const char* title[LANG_COUNT];
  const char* unit[LANG_COUNT];
  MenuType type;
  int16_t parent;
  int16_t first_child;
  uint16_t child_count;
  struct {
    struct { void (*invoke)(); } action;
    ValueSpec value;
  } u;
  int16_t ee_offset; // kept for ABI compatibility; always -1 in NVS backend
  uint16_t ee_size;  // kept for ABI compatibility; always 0 in NVS backend
} MenuItem;

extern const MenuItem g_menu[MENU__COUNT];
