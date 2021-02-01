/* Copyright 2019 Danny Nguyen <danny@keeb.io>
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
#include QMK_KEYBOARD_H

enum encoder_names {
  _LEFT,
  _RIGHT,
  _MIDDLE,
};

enum custom_keycodes {
  MACOS_LOCK_SCREEN = SAFE_RANGE,
  WINDOWS_LOCK_SCREEN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        | Knob 1: Vol Dn/Up   | Knob 2: FF/Rewind | Knob 3: Page Dn/Up |
        | Windows Lock Screen | macOS Lock Screen | Esc                |
        | F20                 | F21               | Hold: Layer 2      |
     */
    [0] = LAYOUT(
        KC_MUTE            , KC_MEDIA_PLAY_PAUSE, KC_HOME,
        WINDOWS_LOCK_SCREEN, MACOS_LOCK_SCREEN  , KC_ESC ,
        KC_F20             , KC_F21             , MO(1)
    ),
    /*
        | Press: RESET | Press: Play/Pause | Press: Home   |
        | F22          | F23               | F24           |
        | F13          | F14               | Held: Layer 2 |
     */
    [1] = LAYOUT(
        RESET  , _______, _______,
        KC_F22 , KC_F23 , KC_F24 ,
        _______, _______, _______
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _LEFT) {
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
    else if (index == _MIDDLE) {
        if (clockwise) {
            tap_code(KC_MEDIA_FAST_FORWARD);
        } else {
            tap_code(KC_MEDIA_REWIND);
        }
    }
    else if (index == _RIGHT) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MACOS_LOCK_SCREEN:
      if (record->event.pressed) {
        // ^⌘Q
        SEND_STRING(SS_DOWN(X_LCTRL) SS_LCMD("q") SS_UP(X_LCTRL));
      }
      break;
    case WINDOWS_LOCK_SCREEN:
      if (record->event.pressed) {
        // Win + L
        SEND_STRING(SS_LWIN("L"));
      }
      break;
  }
  return true;
};
