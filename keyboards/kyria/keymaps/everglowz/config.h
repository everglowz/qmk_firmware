// Copyright 2021 Everglowz

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

// ----- Copied from default keymap
// Then modified to suit personal preferences.

#ifdef OLED_DRIVER_ENABLE
  #define OLED_DISPLAY_128X64
  #define OLED_TIMEOUT 15000
#endif

#ifdef RGBLIGHT_ENABLE
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 150
  #define RGBLIGHT_SPLIT

  // Animations I liked
  // #define RGBLIGHT_EFFECT_RAINBOW_MOOD
  #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
  #define RGBLIGHT_EFFECT_KNIGHT
  #define RGBLIGHT_EFFECT_SNAKE
  #define RGBLIGHT_EFFECT_TWINKLE
  // #define RGBLIGHT_EFFECT_BREATHING
#endif

// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
// #define SPLIT_USB_DETECT
// #define NO_USB_STARTUP_CHECK


// ----- Copied from thomasbaart keymap
// Then modified to suit personal preferences.

// The Leader key allows to flexibly assign macros to key sequences.
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 350
#define LEADER_NO_TIMEOUT

// Allows media codes to properly register in macros and rotary encoder code
#define TAP_CODE_DELAY 10


// ----- Copied from https://github.com/moben/qmk_firmware/blob/master/keyboards/kyria/keymaps/moben/config.h
// Then modified to suit personal preferences.

#define GML COLEMAKDH_NO_HOLD_L
#define GMR COLEMAKDH_NO_HOLD_R
#define QML QWERTY_NO_HOLD_L
#define QMR QWERTY_NO_HOLD_R

// To toggle between BASE layer and other default layers
#define GKF BASE
#define QKF QWERTY

#define TGL TG(GML)
#define TGR TG(GMR)
#define TQL TG(QML)
#define TQR TG(QMR)

// To toggle between BASE layer and other default layers
#define DFG DF(GKF)
#define DFQ DF(QKF)

// ----- Copied from manna-harbour_miryoku keymap. Then modified to suit personal preferences.

#define XXX KC_NO

#define EL0 XXX
#define EL1 KC_PGUP
#define EL2 KC_PGDN
#define ER0 XXX
#define ER1 KC_HOME
#define ER2 KC_END
#define EXL XXX
#define EXR KC_LEAD

#define LAYOUT_miryoku( \
     K00, K01, K02, K03, K04,                          K05, K06, K07, K08, K09, \
     K10, K11, K12, K13, K14,                          K15, K16, K17, K18, K19, \
     K20, K21, K22, K23, K24,                          K25, K26, K27, K28, K29, \
     N30, N31, K32, K33, K34,                          K35, K36, K37, N38, N39 \
) \
LAYOUT( \
EL0, K00, K01, K02, K03, K04,                          K05, K06, K07, K08, K09, ER0, \
EL1, K10, K11, K12, K13, K14,                          K15, K16, K17, K18, K19, ER1, \
EL2, K20, K21, K22, K23, K24, TQL, TGL,      TGR, TQR, K25, K26, K27, K28, K29, ER2, \
               DFG, K32, K33, K34, EXL,      EXR, K35, K36, K37, DFQ \
)


// ----- everglowz specific settings

#ifdef ENCODER_ENABLE
  // My encoder rotation appears to be flipped (I connect to the left USB port if that matters).
  // Some other Kyria keymaps also have this. My encoders are at the bottom row.
  #define ENCODER_DIRECTION_FLIP

  // EC11K encoders have a different resolution than other EC11 encoders.
  // When using the default resolution of 4, if you notice your encoder skipping
  // every other tick, lower the resolution to 2.
  #define ENCODER_RESOLUTION 2
#endif

// Save memory
#define NO_ACTION_ONESHOT     // saves 266 bytes
//#define NO_ACTION_TAPPING     // saves 1922 bytes but I need mod-tap functionality

