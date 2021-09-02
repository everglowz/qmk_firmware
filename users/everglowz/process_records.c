// Copyright 2021 Everglowz
// Inspired by users/ninjonas

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "process_records.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        #ifdef RGBLIGHT_ENABLE

        // Override all the default RGB keys to not save to EEPROM.
        case RGB_VAI:
            if(record->event.pressed) {
                rgblight_increase_val_noeeprom();
            }
            break;
        case RGB_VAD:
            if(record->event.pressed) {
                rgblight_decrease_val_noeeprom();
            }
            break;
        case RGB_SAI:
            if(record->event.pressed) {
                rgblight_increase_sat_noeeprom();
            }
            break;
        case RGB_SAD:
            if(record->event.pressed) {
                rgblight_decrease_sat_noeeprom();
            }
            break;
        case RGB_HUI:
            if(record->event.pressed) {
                rgblight_increase_hue_noeeprom();
            }
            break;
        case RGB_HUD:
            if(record->event.pressed) {
                rgblight_decrease_hue_noeeprom();
            }
            break;
        case RGB_TOG:
            if(record->event.pressed) {
                rgblight_toggle_noeeprom();
            }
            break;
        case RGB_MOD:
            if(record->event.pressed) {
                rgblight_step_noeeprom();
            }
            break;
        case RGB_RMOD:
            if(record->event.pressed) {
                rgblight_step_reverse_noeeprom();
            }
            break;

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

        #endif  // RGBLIGHT_ENABLE

        default:
            // Anything we don't handle, we let the default code handle it.
            return true;
    }

    // If we get here, it's because we handled the key ourselves.
    return false;
}
