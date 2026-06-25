// Auto-generated for ESP32 LINK. Do not edit.
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "menu_meta.h"

#define MENU_MAX_UNITS 1

// Total menu items: 5, with values: 4

union MenuValue {
    float    f32;
    uint32_t u32;
    int32_t  i32;
    uint16_t u16;
    uint8_t  u8;
    bool     b;
};

class MenuCache {
public:
    uint16_t revision = 0;
    uint8_t  active_unit = 0;
    uint8_t  units_count = 1;
    uint8_t  lang = 0;

    MenuValue values[MENU_META_COUNT][MENU_MAX_UNITS] = {};

    float getFloat(uint16_t id, uint8_t unit = 255) const {
        if (id >= MENU_META_COUNT) return 0.0f;
        const MenuMeta* m = &g_menu_meta[id];
        uint8_t u = (unit == 255) ? active_unit : unit;
        if (m->scope == META_SCOPE_GLOBAL) u = 0;
        if (u >= MENU_MAX_UNITS) u = 0;
        const MenuValue& v = values[id][u];
        switch (m->vtype) {
            case META_VT_F32:  return v.f32;
            case META_VT_U32:  return (float)v.u32;
            case META_VT_I32:  return (float)v.i32;
            case META_VT_U16:  return (float)v.u16;
            case META_VT_U8:   return (float)v.u8;
            case META_VT_BOOL: return v.b ? 1.0f : 0.0f;
            default: return 0.0f;
        }
    }

    void setFloat(uint16_t id, float val, uint8_t unit = 255) {
        if (id >= MENU_META_COUNT) return;
        const MenuMeta* m = &g_menu_meta[id];
        uint8_t u = (unit == 255) ? active_unit : unit;
        if (m->scope == META_SCOPE_GLOBAL) u = 0;
        if (u >= MENU_MAX_UNITS) u = 0;
        MenuValue& v = values[id][u];
        switch (m->vtype) {
            case META_VT_F32:  v.f32 = val; break;
            case META_VT_U32:  v.u32 = (uint32_t)val; break;
            case META_VT_I32:  v.i32 = (int32_t)val; break;
            case META_VT_U16:  v.u16 = (uint16_t)val; break;
            case META_VT_U8:   v.u8  = (uint8_t)val; break;
            case META_VT_BOOL: v.b   = (val != 0.0f); break;
            default: break;
        }
    }

    bool getBool(uint16_t id, uint8_t unit = 255) const {
        return getFloat(id, unit) != 0.0f;
    }
    int32_t getInt(uint16_t id, uint8_t unit = 255) const {
        return (int32_t)getFloat(id, unit);
    }
    uint8_t getLang() const { return lang; }
    uint8_t getUnitsCount() const { return units_count; }
};

extern MenuCache g_menu_cache;
