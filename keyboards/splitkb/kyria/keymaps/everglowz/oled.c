// Copyright 2021 Everglowz
// Inspired by users/ninjonas

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "everglowz.h"
#include "version.h"

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

void e_oled_white_space(void) {
    oled_write_P(PSTR(" "), false);
}

void e_oled_slash_separator(void) {
    oled_write_P(PSTR(" / "), false);
}

static void e_render_layout_state(void) {
    oled_write_P(PSTR("Layout: "), false);
    switch (biton32(default_layer_state)) {
        case BASE:
            oled_write_P(PSTR("Colmak DH"), false);
            break;
        case QWERTY:
            oled_write_P(PSTR("Qwerty"), false);
            break;
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
}

#ifdef ENCODER_ENABLE
static void e_render_encoder_state(void) {
    oled_write_P(PSTR("\n\nEnc: "), false);

    uint8_t layer = get_highest_layer(layer_state);

    // Left encoder
    switch (layer) {
        case SYM:
            oled_write_P(PSTR("MOD  "), left_encoder_rotated);
            break;
        case NUM:
            oled_write_P(PSTR("HUE  "), left_encoder_rotated);
            break;
        case FUN:
            oled_write_P(PSTR("TABSW"), left_encoder_rotated);
            break;
        default:
            oled_write_P(PSTR("APPSW"), left_encoder_rotated);
    }

    e_oled_slash_separator();

    // Right encoder
    switch (layer) {
        case MEDIA:
            oled_write_P(PSTR("VOL  "), right_encoder_rotated);
            break;
        case NAV:
            oled_write_P(PSTR("SAT  "), right_encoder_rotated);
            break;
        case MOUSE:
            oled_write_P(PSTR("VAL  "), right_encoder_rotated);
            break;
        default:
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
            oled_write_P(PSTR("Base      "), false);
    }
}

void e_render_mod_state(uint8_t modifiers) {
    oled_write_P(PSTR("\n\nMods: "), false);
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

    const char* led_blank_str = PSTR("    ");
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : led_blank_str, false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : led_blank_str, false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR") : led_blank_str, false);

}

static void e_print_number(uint16_t m) {
    char string[4];
    string[3] = '\0';
    string[2] = '0' + m % 10;
    string[1] = ( m /= 10) % 10 ? '0' + (m) % 10 : (m / 10) % 10 ? '0' : ' ';
    string[0] =  m / 10 ? '0' + m / 10 : ' ';
    oled_write(string, false);
    e_oled_white_space();
}

static void e_render_rgbled_status(void) {
    if (RGBLIGHT_MODES > 1 && rgblight_is_enabled()) {
        oled_write_P(PSTR("\nLED:"), false);

        e_print_number(rgblight_get_mode());
        e_print_number(rgblight_get_hue()/RGBLIGHT_HUE_STEP);
        e_print_number(rgblight_get_sat()/RGBLIGHT_SAT_STEP);
        e_print_number(rgblight_get_val()/RGBLIGHT_VAL_STEP);
        oled_write_ln_P(PSTR("\n    MOD HUE SAT VAL"), false);
    }
}

static void render_primary_status(void) {

    e_render_layout_state();        // L1
    e_render_no_hold_state();       // L2

    #ifdef ENCODER_ENABLE
    e_render_encoder_state();       // L3-4
    #endif

    e_render_layer_state();         // L5
    e_render_mod_state(get_mods()); // L6-7
}

static void render_secondary_status(void) {
    oled_write_P(PSTR("Kyria rev1.0\n"), false);    // L1

    // build date e.g. 2021-09-03-00:25:17
    oled_write_P(PSTR("v " QMK_VERSION "\n@" QMK_BUILDDATE "\n"), false);     // L2-4 if not dirty

    e_render_keyboard_led_state();      // L5

    #ifdef RGBLIGHT_ENABLE
    e_render_rgbled_status();           // L6-7
    #endif
}

void oled_task_user(void) {
    // Limits for my 128x64 OLED display:
    // 8? lines, 20 chars per line

    if (is_keyboard_master()) {
        render_primary_status();
    } else {
        render_secondary_status();
    }
}

#endif  // OLED_ENABLE
