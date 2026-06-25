// Auto-generated. Do not edit.
#include <string.h>
#include <stdio.h>
#include "menu_state.h"
#include "menu_types.h"
#include "menu_nvs.h"
#include "menu_nvs_io.h"

MenuState menu;

void MenuState::initDefaults(){
  this->target_temp = (uint16_t)45;
  this->hysteresis = (uint8_t)2;
  this->units_count = (uint8_t)1;
  this->language = (uint8_t)1;
}

void MenuState::loadFromNVS(){
  menu_nvs_begin();
  uint32_t magic = 0, ver = 0;
  ee_read(NVS_KEY_MAGIC, magic);
  ee_read(NVS_KEY_VERSION, ver);
  if (magic != NVS_MENU_MAGIC || ver != (uint32_t)NVS_MENU_VERSION) {
    menu_nvs_end();
    saveToNVS();  // first boot: persist defaults + magic
    return;
  }
  char key[16];
  (void)key;
  ee_read("target_temp", this->target_temp);
  ee_read("hysteresis", this->hysteresis);
  ee_read("units_count", this->units_count);
  ee_read("language", this->language);
  menu_nvs_end();
}

void MenuState::saveToNVS(){
  menu_nvs_begin();
  ee_write(NVS_KEY_MAGIC,   (uint32_t)NVS_MENU_MAGIC);
  ee_write(NVS_KEY_VERSION, (uint32_t)NVS_MENU_VERSION);
  char key[16];
  (void)key;
  ee_store_field("target_temp", this->target_temp);
  ee_store_field("hysteresis", this->hysteresis);
  ee_store_field("units_count", this->units_count);
  ee_store_field("language", this->language);
  menu_nvs_end();
}