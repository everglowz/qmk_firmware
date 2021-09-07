#pragma once

#include "quantum.h"

enum custom_keycodes {
  // Custom Macros
  M_RGB_SAVE = SAFE_RANGE,
  M_RGB_RESET,
  M_RGB_TOGGLE,
  M_RGB_TIMEOUT_TOGGLE,

  // Custom layer keys
  M_NO_HOLD_LEFT,
  M_NO_HOLD_RIGHT
};

bool process_record_secrets(uint16_t keycode, keyrecord_t *record);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
