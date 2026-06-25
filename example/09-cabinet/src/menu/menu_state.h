// Auto-generated. Do not edit.
#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "menu_ids.h"

#ifndef NUM_UNITS
#define NUM_UNITS 1
#endif

class MenuState {
public:
  uint16_t target_temp = (uint16_t)45;
  uint8_t hysteresis = (uint8_t)2;
  uint8_t units_count = (uint8_t)1;
  uint8_t language = (uint8_t)1;

  void initDefaults();   // выставить дефолты из YAML
  void loadFromNVS();    // подхватить значения из NVS
  void saveToNVS();      // записать все поля в NVS (создать namespace)
};

extern MenuState menu;