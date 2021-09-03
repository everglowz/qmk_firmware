// Copyright 2021 Everglowz
// Inspired by users/ninjonas

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "process_records.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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

        #endif  // RGBLIGHT_ENABLE

        default:
            // Anything we don't handle, we let the default code handle it.
            return true;
    }

    // If we get here, it's because we handled the key ourselves.
    return false;
}
