// Copyright 2021 Everglowz
// Inspired by users/ninjonas

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "everglowz.h"

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }
__attribute__((weak)) bool process_record_secrets(uint16_t keycode, keyrecord_t *record) { return true; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (!(process_record_keymap(keycode, record) && process_record_secrets(keycode, record)
#ifdef RGBLIGHT_ENABLE
          && process_record_user_rgb_light(keycode, record)
#endif
          && true)) {
        return false;
    }

    switch (keycode) {
        #ifdef RGBLIGHT_ENABLE
        // Save current RGB Light settings to EEPROM
        case M_RGB_SAVE:
            if (record->event.pressed) {
                eeconfig_update_rgblight_current();
            }
            break;

        // Reset RGB Light settings to default
        case M_RGB_RESET:
            if (record->event.pressed) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
            }
            break;

        case M_RGB_TOGGLE:
            if (record->event.pressed) {
                rgblight_toggle_noeeprom();
            }
            break;

        case M_RGB_TIMEOUT_TOGGLE:
            if (record->event.pressed) {
                // Toggle idle LED timeout on or off
                rgb_time_out_enable = !rgb_time_out_enable;
            }
            break;

        #endif  // RGBLIGHT_ENABLE

        case M_NO_HOLD_LEFT:
            if (record->event.pressed) {
                switch (get_highest_layer(layer_state)) {
                    case SYM:
                        layer_invert(QWERTY_NO_HOLD_L);
                        break;
                    default:
                        layer_invert(COLEMAKDH_NO_HOLD_L);
                }
            }
            break;

        case M_NO_HOLD_RIGHT:
            if (record->event.pressed) {
                switch (get_highest_layer(layer_state)) {
                    case MOUSE:
                        layer_invert(QWERTY_NO_HOLD_R);
                        break;
                    default:
                        layer_invert(COLEMAKDH_NO_HOLD_R);
                }
            }
            break;

        default:
            // Anything we don't handle, we let the default code handle it.
            return true;
    }

    // If we get here, it's because we handled the key ourselves.
    return false;
}
