/* Copyright 2022 splitkb.com <support@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"
#include "oled_driver.h"
#include <stdio.h>
#include <string.h>

extern bool is_linux_mode(void);
extern const char *get_oled_typed_buffer(void);

#ifdef OLED_ENABLE



oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

static void oled_render_os_selector(void) {
    bool linux_mode = is_linux_mode();

    oled_write_P(PSTR("OS:    "), false);
    oled_write_P(PSTR("Lnx"), linux_mode);
    oled_write_P(PSTR("  | "), false);
    oled_write_P(PSTR("Wndws"), !linux_mode);
}


bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    if (is_keyboard_master()) {

        oled_write_P(PSTR("Keyboard: KYRIA "), false);
   
        #if defined(KEYBOARD_splitkb_kyria_rev1)
                oled_write_P(PSTR("Rev1\n"), false);
        #elif defined(KEYBOARD_splitkb_kyria_rev2)
                oled_write_P(PSTR("Rev2\n"), false);
        #elif defined(KEYBOARD_splitkb_kyria_rev3)
                oled_write_P(PSTR("Rev3\n"), false);
        #endif
        // Host Keyboard Layer Status
        oled_write_P(PSTR("\n"), false);
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case 0: oled_write_P(PSTR("QWRT\n"), false); break;
            case 1: oled_write_P(PSTR("Dvrk\n"), false); break;
            case 2: oled_write_P(PSTR("Game\n"), false); break;
            case 3: oled_write_P(PSTR("Navy\n"), false); break;
            case 4: oled_write_P(PSTR("Symb\n"), false); break;
            case 5: oled_write_P(PSTR("Func\n"), false); break;
            case 6: oled_write_P(PSTR("Adjs\n"), false); break;
            case 7: oled_write_P(PSTR("NmPd\n"), false); break;
            default: oled_write_P(PSTR("Undefined\n"), false);
        }

        // Host Keyboard LED Status
        //oled_write_P(PSTR("OS: "), false);
        led_t led_usb_state = host_keyboard_led_state();
        oled_render_os_selector();
        oled_write_P(PSTR("\n"), false);

        oled_write_P(PSTR("Fnct:  "), false);
        oled_write_P(led_usb_state.num_lock ?  PSTR("NLCK ") : PSTR("     "), false);
        oled_write_P(PSTR("| "), false);
        oled_write_P(led_usb_state.caps_lock ? PSTR("CLCK ") : PSTR("     "), false);
        oled_write_P(PSTR("\n"), false);
        //oled_write_P(PSTR("| "), false);
        //oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK") : PSTR("       "), false);
        //oled_write_P(PSTR("OS: "), false);
        //oled_write_P(is_linux_mode() ? PSTR("Lnx\n") : PSTR("Wndws\n"),false);
        oled_write_P(PSTR("\n"), false);
        oled_write_P(PSTR(">: "), false);
        oled_write_ln(get_oled_typed_buffer(), false);
        
    } else {
        // OLED del esclavo
        oled_set_cursor(0,0);
  
        oled_write_P(PSTR("       -------------\n"), false);
        uint8_t mods = get_mods();
        oled_write_P(PSTR("MODS: "), false);

        // [C]trl
        oled_write_P(PSTR("| "), false);
        if (mods & MOD_MASK_CTRL) {
            oled_write_P(PSTR("Ctrl"), mods & MOD_MASK_CTRL);
        } else {
            oled_write_P(PSTR("Ctrl"), false);
        }
        oled_write_P(PSTR(" | "), false);
        // [S]hift
        if (mods & MOD_MASK_SHIFT) {
            oled_write_P(PSTR("Shft"), mods & MOD_MASK_SHIFT);
        } else {
            oled_write_P(PSTR("Shft"), false);
        }
        oled_write_P(PSTR(" |"), false);
        oled_write_P(PSTR("      --------------"), false);
        oled_write_P(PSTR("      "), false);
        // [A]lt
        oled_write_P(PSTR(" | "), false);
        if (mods & MOD_MASK_ALT) {
            oled_write_P(PSTR("Alt"), mods & MOD_MASK_ALT);
        } else {
            oled_write_P(PSTR("Alt"), false);
        }
        oled_write_P(PSTR("  | "), false);
        // Alt[G]r
        if (mods & MOD_BIT(KC_RALT)) {
            oled_write_P(PSTR("Gr"), mods & MOD_BIT(KC_RALT));
        } else {
            oled_write_P(PSTR("Gr"), false);
        }
        oled_write_P(PSTR("   |"), false);
        oled_write_P(PSTR("       -------------\n"), false);

        oled_write_P("Words/min: ", false);
        char wpm_str[5];
        snprintf(wpm_str, sizeof(wpm_str), "%3d", get_current_wpm());
        oled_write_ln(wpm_str, false);
        oled_write_ln("", false); // Línea en blanco
                // Mostrar estado de modificadores
  // Mostrar estado de modificadores


        
        // Muestra el texto tecleado en las líneas siguientes
        // clang-format off
        //static const char PROGMEM kyria_logo[] = {
        //    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        //    0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        //    0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        //    0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
        //    0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
        //    0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        //    0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        //    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
        //};
        // clang-format on
        //oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
    }
    return true;
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }

    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}
#endif
