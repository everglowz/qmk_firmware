// Copyright 2021 Everglowz

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#ifdef RGBLIGHT_ENABLE

#define MILLISECONDS_IN_SECOND 1000

bool rgb_on;                    // Current LED state flag. If false then LED is off.
bool rgb_time_out_enable;       // Idle LED toggle enable. If false then LED will not turn off after idle timeout.

void matrix_init_rgb_light(void);
void matrix_scan_rgb_light(void);
bool process_record_user_rgb_light(uint16_t keycode, keyrecord_t *record);
void post_encoder_update_rgb_light(void);

#endif  // RGBLIGHT_ENABLE
