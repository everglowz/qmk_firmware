// Copyright 2021 Everglowz
// Inspired by users/ninjonas

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "everglowz.h"

#ifdef ENCODER_ENABLE
void left_encoder_cw(void) {
    switch (get_highest_layer(layer_state)) {
        case FUN:
            // Switch between browser/editor tabs with ctrl tab.
            if (!is_ctrl_tab_active) {
                is_ctrl_tab_active = true;
                register_code(KC_LCTRL);
            }
            ctrl_tab_timer = timer_read();
            tap_code16(KC_TAB);
            break;
        default:
            // Switch between windows on Windows with alt tab.
            if (!is_alt_tab_active) {
                is_alt_tab_active = true;
                register_code(KC_LALT);
            }
            alt_tab_timer = timer_read();
            tap_code16(KC_TAB);
            break;
        }
}

void left_encoder_ccw(void) {
    switch (get_highest_layer(layer_state)) {
        case FUN:
            // Switch between browser/editor tabs with ctrl tab.
            ctrl_tab_timer = timer_read();
            tap_code16(S(KC_TAB));
            break;
        default:
            // Switch between windows on Windows with alt tab.
            alt_tab_timer = timer_read();
            tap_code16(S(KC_TAB));
            break;
        }
}

void right_encoder_cw(void) {
    switch (get_highest_layer(layer_state)) {
        case MEDIA:
            tap_code(KC_VOLU);
            break;
        default:
            tap_code(KC_PGDN);
            break;
        }
}

void right_encoder_ccw(void) {
    switch (get_highest_layer(layer_state)) {
        case MEDIA:
            tap_code(KC_VOLD);
            break;
        default:
            tap_code(KC_PGUP);
            break;
        }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    encoder_rotated_timer = timer_read();
    if (index == 0) {
        left_encoder_rotated = true;
        if (clockwise) {
            left_encoder_cw();
        } else {
            left_encoder_ccw();
        }
    }
    else if (index == 1) {
        right_encoder_rotated = true;
        if (clockwise) {
            right_encoder_cw();
        } else {
            right_encoder_ccw();
        }
    }

    // Do not run keyboard level encoder behavior
    return false;
}

#endif
