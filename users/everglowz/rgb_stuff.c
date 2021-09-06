// Copyright 2021 Everglowz

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "everglowz.h"

#ifdef RGBLIGHT_ENABLE

static uint16_t idle_timer;             // Idle LED timeout timer
static uint8_t idle_second_counter;     // Idle LED seconds counter, counts seconds not milliseconds
static uint8_t key_event_counter;       // This counter is used to check if any keys are being held

void matrix_init_rgb_light(void) {
    idle_second_counter = 0;                        // Counter for number of seconds keyboard has been idle.
    key_event_counter = 0;                          // Counter to determine if keys are being held, neutral at 0.
    rgb_on = rgblight_is_enabled();
    rgb_time_out_enable = true;                     // Enable RGB timeout by default. Disable using toggle key.
}

void matrix_scan_rgb_light(void) {
    // Check for RGB idle timeout
    if(rgb_time_out_enable && rgb_on) {
        // If the key event counter is not zero then some key was pressed down but not released, thus reset the timeout counter.
        if (key_event_counter) {
            idle_second_counter = 0;
        } else if (timer_elapsed(idle_timer) > MILLISECONDS_IN_SECOND) {
            idle_second_counter++;
            idle_timer = timer_read();
        }

        if (idle_second_counter >= RGB_DEFAULT_TIME_OUT) {
            rgblight_disable_noeeprom();
            rgb_on = false;
            idle_second_counter = 0;
        }
    }
}

bool process_record_user_rgb_light(uint16_t keycode, keyrecord_t *record) {
    // Increment key event counter for every press and decrement for every release.
    if (record->event.pressed) {
        key_event_counter++;
    } else {
        key_event_counter--;
    }

    if (rgb_time_out_enable) {
        idle_timer = timer_read();
        // Reset the seconds counter. Without this, something like press> leave x seconds> press, would be x seconds on the effective counter not 0 as it should.
        idle_second_counter = 0;
        if (!rgb_on) {
            rgblight_enable_noeeprom();
            rgb_on = true;
        }
    }

    return true;
}

#endif  // RGBLIGHT_ENABLE
