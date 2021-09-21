// Copyright 2021 Everglowz

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

// ----- Copied from default keymap
// Then modified to suit personal preferences.

#ifdef OLED_ENABLE
    #define OLED_DISPLAY_128X64
    // #define OLED_TIMEOUT 15000

    // Required for sharing state in split KBs for OLED display
    #define SPLIT_LED_STATE_ENABLE
#endif

#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8
    #define RGBLIGHT_LIMIT_VAL 150
    #define RGBLIGHT_SPLIT
    #define RGBLIGHT_SLEEP

    // Animations I liked
    // #define RGBLIGHT_EFFECT_RAINBOW_SWIRL   // 0,1,2,3,4,5
    #define RGBLIGHT_EFFECT_KNIGHT          // 0,1,2
    // #define RGBLIGHT_EFFECT_CHRISTMAS       // none
    #define RGBLIGHT_EFFECT_TWINKLE         // 0,1,2,3,4,5

    #define RGB_DEFAULT_TIME_OUT 70         // RGB timeout in seconds
#endif

// ----- Copied from thomasbaart keymap
// Then modified to suit personal preferences.

// The Leader key allows to flexibly assign macros to key sequences.
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 350
#define LEADER_NO_TIMEOUT

// Allows media codes to properly register in macros and rotary encoder code
#define TAP_CODE_DELAY 10

#define TAPPING_TOGGLE 1    // shorter tapping toggle for keycodes

// ----- Copied from https://github.com/moben/qmk_firmware/blob/master/keyboards/kyria/keymaps/moben/config.h
// Then modified to suit personal preferences.

#define TGL TG(COLEMAKDH_NO_HOLD_L)
#define TGR TG(COLEMAKDH_NO_HOLD_R)
#define TQL TG(QWERTY_NO_HOLD_L)
#define TQR TG(QWERTY_NO_HOLD_R)

// To toggle between BASE layer and other default layers
#define DFG DF(BASE)
#define DFQ DF(QWERTY)

// ----- Copied from manna-harbour_miryoku keymap. Then modified to suit personal preferences.

#define XXX KC_NO

#define EL0 XXX
#define EL1 KC_LSFT
#define EL2 KC_LCTL
#define EL3 TT(SYM)
#define EL4 TT(NUM)
#define ER0 KC_LEAD
#define ER1 KC_HOME
#define ER2 KC_END
#define ER3 TT(VIEWER_FULL)
#define ER4 XXX
#define EB1 M_NO_HOLD_LEFT
#define EB2 M_NO_HOLD_RIGHT

// Using the MIRYOKU_MAPPING_EXTENDED_THUMBS version
#define LAYOUT_miryoku( \
    K00, K01, K02, K03, K04,                          K05, K06, K07, K08, K09, \
    K10, K11, K12, K13, K14,                          K15, K16, K17, K18, K19, \
    K20, K21, K22, K23, K24,                          K25, K26, K27, K28, K29, \
    N30, N31, K32, K33, K34,                          K35, K36, K37, N38, N39 \
) \
LAYOUT( \
EL0, K00, K01, K02, K03, K04,                          K05, K06, K07, K08, K09, ER0, \
EL1, K10, K11, K12, K13, K14,                          K15, K16, K17, K18, K19, ER1, \
EL2, K20, K21, K22, K23, K24, EL3, EL4,      ER4, ER3, K25, K26, K27, K28, K29, ER2, \
               DFG, EB1, K32, K33, K34,      K35, K36, K37, EB2, DFQ \
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
