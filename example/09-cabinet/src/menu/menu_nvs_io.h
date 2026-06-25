
// Auto-generated. Do not edit.
// NVS I/O helpers — шаблоны поверх ESP32 Preferences.
#pragma once
#include <Arduino.h>
#include <Preferences.h>
#include <string.h>
#include "menu_nvs.h"

// Общий экземпляр Preferences для меню.
// Открывается один раз в menu_nvs_begin(), не требует begin/end на каждый доступ.
extern Preferences g_menu_prefs;

bool menu_nvs_begin();
void menu_nvs_end();

// Чтение значения по ключу. Если ключа нет — out остаётся с исходным значением
// (используется как default), возвращаем false.
template<typename T> inline bool ee_read(const char* key, T& out);

template<> inline bool ee_read<float>(const char* k, float& o){
  if (!g_menu_prefs.isKey(k)) return false;
  o = g_menu_prefs.getFloat(k, o); return true;
}
template<> inline bool ee_read<uint8_t>(const char* k, uint8_t& o){
  if (!g_menu_prefs.isKey(k)) return false;
  o = g_menu_prefs.getUChar(k, o); return true;
}
template<> inline bool ee_read<uint16_t>(const char* k, uint16_t& o){
  if (!g_menu_prefs.isKey(k)) return false;
  o = g_menu_prefs.getUShort(k, o); return true;
}
template<> inline bool ee_read<uint32_t>(const char* k, uint32_t& o){
  if (!g_menu_prefs.isKey(k)) return false;
  o = g_menu_prefs.getUInt(k, o); return true;
}
template<> inline bool ee_read<int32_t>(const char* k, int32_t& o){
  if (!g_menu_prefs.isKey(k)) return false;
  o = g_menu_prefs.getInt(k, o); return true;
}
template<> inline bool ee_read<bool>(const char* k, bool& o){
  if (!g_menu_prefs.isKey(k)) return false;
  o = g_menu_prefs.getBool(k, o); return true;
}

// Безусловная запись (всегда).
template<typename T> inline bool ee_write(const char* key, const T& val);

template<> inline bool ee_write<float>(const char* k, const float& v){
  return g_menu_prefs.putFloat(k, v) > 0;
}
template<> inline bool ee_write<uint8_t>(const char* k, const uint8_t& v){
  return g_menu_prefs.putUChar(k, v) > 0;
}
template<> inline bool ee_write<uint16_t>(const char* k, const uint16_t& v){
  return g_menu_prefs.putUShort(k, v) > 0;
}
template<> inline bool ee_write<uint32_t>(const char* k, const uint32_t& v){
  return g_menu_prefs.putUInt(k, v) > 0;
}
template<> inline bool ee_write<int32_t>(const char* k, const int32_t& v){
  return g_menu_prefs.putInt(k, v) > 0;
}
template<> inline bool ee_write<bool>(const char* k, const bool& v){
  return g_menu_prefs.putBool(k, v) > 0;
}

// Запись только если значение изменилось. Возвращает true если было изменение.
template<typename T>
inline bool ee_store_field(const char* key, const T& val){
  T cur = val;
  bool had = ee_read<T>(key, cur);
  if (had && cur == val) return false;
  ee_write<T>(key, val);
  return true;
}

// Построить NVS-ключ для per_controller поля: "{bind}_{idx}".
// out буфер должен быть >= 16 байт.
inline void menu_nvs_key_per_unit(char* out, size_t cap, const char* bind, uint8_t idx){
  snprintf(out, cap, "%s_%u", bind, (unsigned)idx);
}
