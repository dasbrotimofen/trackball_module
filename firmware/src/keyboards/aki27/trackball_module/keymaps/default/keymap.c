/*
Copyright 2022 aki27

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "quantum.h"


// Defines names for use in layer keycodes and the keymap
enum layer_number {
    _BASE = 0,
    _LOWER = 1,
    _RAISE = 2,
    _TRACKBALL = 3
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
       MS_BTN1,    MS_BTN2,    MS_BTN3
    ),
  [_LOWER] = LAYOUT(
       MS_BTN4,    KC_B,    SCRL_TO
    ),
  [_RAISE] = LAYOUT(
       KC_A,    KC_B,    KC_C
    ),
  [_TRACKBALL] = LAYOUT(
       KC_A,    KC_B,    KC_C
    )
};


#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[4][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]      = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_LOWER]     = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_RAISE]     = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_TRACKBALL] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
};
#endif



layer_state_t layer_state_set_user(layer_state_t state) {

    switch (get_highest_layer(state)) {
    case _LOWER:
    case _RAISE:
        cocot_set_scroll_mode(true);
        break;
    case _TRACKBALL:
        cocot_set_scroll_mode(false);
        break;
    default:
        cocot_set_scroll_mode(false);
        break;
    }
  return state;
};


#ifdef OLED_ENABLE
bool oled_task_user(void) {
    oled_write_layer_state();
    return false;
}
#endif

