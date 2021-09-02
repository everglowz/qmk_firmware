// Copyright 2021 Everglowz
// Inspired by users/ninjonas

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "everglowz.h"

#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

static void render_qmk_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

    oled_write_P(qmk_logo, false);
}

void e_oled_white_space(void) {
    oled_write_P(PSTR(" "), false);
}

void e_oled_slash_separator(void) {
    oled_write_P(PSTR(" / "), false);
}

static void e_render_layout_state(void) {
    oled_write_P(PSTR("\nLayout: "), false);
    switch (biton32(default_layer_state)) {
        case BASE:
            oled_write_P(PSTR("Colmak DH"), false);
            break;
        #if defined QWERTY
        case QWERTY:
            oled_write_P(PSTR("Qwerty"), false);
            break;
        #endif
        default:
            oled_write_P(PSTR("?"), false);
    }
}

static void e_render_no_hold_state(void) {
    oled_write_P(PSTR("\nNo hold: "), false);

    oled_write_P(PSTR("GL"), layer_state_is(COLEMAKDH_NO_HOLD_L));
    e_oled_white_space();
    oled_write_P(PSTR("GR"), layer_state_is(COLEMAKDH_NO_HOLD_R));
    e_oled_white_space();
    oled_write_P(PSTR("QL"), layer_state_is(QWERTY_NO_HOLD_L));
    e_oled_white_space();
    oled_write_P(PSTR("QR"), layer_state_is(QWERTY_NO_HOLD_R));
    e_oled_white_space();
}

#ifdef ENCODER_ENABLE
static void e_render_encoder_state(void) {
    oled_write_P(PSTR("\nEnc: "), false);
    bool function = layer_state_is(FUN);
    bool media = layer_state_is(MEDIA);

    // Left encoder
    if (function) {
        oled_write_P(PSTR("TABSW"), left_encoder_rotated);
        e_oled_slash_separator();
    } else {
        oled_write_P(PSTR("APPSW"), left_encoder_rotated);
        e_oled_slash_separator();
    }

    // Right encoder
    if (media) {
        oled_write_P(PSTR("VOL"), right_encoder_rotated);
    } else {
        oled_write_P(PSTR("PAGE"), right_encoder_rotated);
    }

    // Reset rotation state
    if (timer_elapsed(encoder_rotated_timer) > 200) {
        left_encoder_rotated = false;
        right_encoder_rotated = false;
    }
}
#endif

static void e_render_layer_state(void) {
    oled_write_P(PSTR("\nLayer: "), false);

    // This checks only for the non-default, non-no-hold layers.
    // These have no transparent keys so highest layer check works.
    switch (get_highest_layer(layer_state)) {
        case MOUSE:
            oled_write_P(PSTR("Mouse     "), true);
            break;
        case MEDIA:
            oled_write_P(PSTR("Media     "), true);
            break;
        case NAV:
            oled_write_P(PSTR("Navigation"), true);
            break;
        case SYM:
            oled_write_P(PSTR("Symbols   "), true);
            break;
        case NUM:
            oled_write_P(PSTR("Numbers   "), true);
            break;
        case FUN:
            oled_write_P(PSTR("Functions "), true);
            break;
        default:
            // If we get here, we could have different default layers.
            if (layer_state_is(QWERTY)) {
                oled_write_P(PSTR("Qwerty    "), false);
                break;
            }

            oled_write_P(PSTR("Base      "), false);
    }
}

void e_render_mod_state(uint8_t modifiers) {
    oled_write_P(PSTR("\nMods: "), false);
    oled_write_P(PSTR("SHF"), (modifiers & MOD_MASK_SHIFT));
    e_oled_white_space();
    oled_write_P(PSTR("CTL"), (modifiers & MOD_MASK_CTRL));
    e_oled_white_space();
    oled_write_P(PSTR("ALT"), (modifiers & MOD_MASK_ALT));
    e_oled_white_space();
    oled_write_P(PSTR("GUI"), (modifiers & MOD_MASK_GUI));
}

static void e_render_keyboard_led_state(void) {
    oled_write_P(PSTR("\nLock: "), false);
    led_t led_state = host_keyboard_led_state();
    oled_write_P(PSTR("NUM"), led_state.num_lock);
    e_oled_white_space();
    oled_write_P(PSTR("CAP"), led_state.caps_lock);
    e_oled_white_space();
    oled_write_P(PSTR("SCR"), led_state.scroll_lock);
}

static void e_render_rgbled_status(void) {
    char string[4];
    if (RGBLIGHT_MODES > 1 && rgblight_is_enabled()) {
        uint16_t m = rgblight_get_mode();
        string[3] = '\0';
        string[2] = '0' + m % 10;
        string[1] = ( m /= 10) % 10 ? '0' + (m) % 10 : (m / 10) % 10 ? '0' : ' ';
        string[0] =  m / 10 ? '0' + m / 10 : ' ';
        oled_write_P(PSTR("LED: "), false);
        oled_write(string, false);
        uint16_t h = rgblight_get_hue()/RGBLIGHT_HUE_STEP;
        string[3] = '\0';
        string[2] = '0' + h % 10;
        string[1] = ( h /= 10) % 10 ? '0' + (h) % 10 : (h / 10) % 10 ? '0' : ' ';
        string[0] =  h / 10 ? '0' + h / 10 : ' ';
        oled_write_P(PSTR(","), false);
        oled_write(string, false);
        uint16_t s = rgblight_get_sat()/RGBLIGHT_SAT_STEP;
        string[3] = '\0';
        string[2] = '0' + s % 10;
        string[1] = ( s /= 10) % 10 ? '0' + (s) % 10 : (s / 10) % 10 ? '0' : ' ';
        string[0] =  s / 10 ? '0' + s / 10 : ' ';
        oled_write_P(PSTR(","), false);
        oled_write(string, false);
        uint16_t v = rgblight_get_val()/RGBLIGHT_VAL_STEP;
        string[3] = '\0';
        string[2] = '0' + v % 10;
        string[1] = ( v /= 10) % 10 ? '0' + (v) % 10 : (v / 10) % 10 ? '0' : ' ';
        string[0] =  v / 10 ? '0' + v / 10 : ' ';
        oled_write_P(PSTR(","), false);
        oled_write(string, false);
        oled_write_ln_P(PSTR("\n     MOD HUE SAT VAL"), false);
    }
}

static void render_primary_status(void) {
    oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

    e_render_layout_state();

    #ifdef ENCODER_ENABLE
    e_render_encoder_state();
    #endif

    e_render_layer_state();
    e_render_mod_state(get_mods());
}

static void render_secondary_status(void) {
    render_qmk_logo();
    e_render_no_hold_state();
    e_render_keyboard_led_state();

    #ifdef RGBLIGHT_ENABLE
    e_render_rgbled_status();
    #endif
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_primary_status();
    } else {
        render_secondary_status();
    }
}
#endif
