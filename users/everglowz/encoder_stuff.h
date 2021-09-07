// Copyright 2021 Everglowz

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#ifdef ENCODER_ENABLE

void matrix_scan_encoder(void);

// ----- Inspired by users/ninjonas & thomasbaart

bool left_encoder_rotated;
bool right_encoder_rotated;
uint16_t encoder_rotated_timer;

bool is_alt_tab_active;
uint16_t alt_tab_timer;
bool is_ctrl_tab_active;
uint16_t ctrl_tab_timer;

#endif  // ENCODER_ENABLE
