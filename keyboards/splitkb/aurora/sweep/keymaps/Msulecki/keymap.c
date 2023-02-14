#include QMK_KEYBOARD_H

/*
LED MAP
         0-5 - left backlight        23-28 - right backlight
            6  7  8  9  10              29 30 31 32 33
            11 12 13 14 15              34 35 36 37 38
            16 17 18 19 20              39 40 41 42 43
                        21 22        44 45
*/

static uint8_t rgb_offset = 0;

enum custom_keycodes { MKR_ARROW = SAFE_RANGE, MKR_ARROW_FN, MKR_QUOTE, MKR_CURLY, MKR_BRACKET, MKR_ARRAY, RGB_INC, RGB_DEC, LAY_DEF_2, LAY_DEF_3 };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_BSPC, KC_A, KC_R, LT(0, KC_S), KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O, KC_Z, LT(0, KC_X), LT(0, KC_C), KC_D, LT(0, KC_V), KC_K, KC_H, LT(0, KC_LBRC), LT(0, KC_RBRC), KC_SLSH, LSFT_T(KC_ENT), KC_SPC, OPT_T(KC_COMM), LT(1, KC_DOT)),

    [1] = LAYOUT(KC_PMNS, KC_PPLS, KC_7, KC_8, KC_9, KC_MINS, KC_EQL, KC_F3, KC_F12, TO(2), KC_PSLS, KC_PAST, KC_4, KC_5, KC_6, KC_SCLN, KC_QUOT, KC_BSLS, KC_SLSH, TO(3), KC_PENT, KC_0, KC_1, KC_2, KC_3, KC_LBRC, KC_RBRC, KC_COMM, KC_DOT, TO(4), LSFT_T(KC_ENT), KC_SPC, KC_NO, KC_TRNS),

    [2] = LAYOUT(KC_ESC, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, MKR_QUOTE, MKR_CURLY, KC_TRNS, KC_TRNS, TO(2), KC_TAB, KC_WH_U, KC_BTN1, KC_MS_U, KC_BTN2, MKR_ARROW, MKR_ARROW_FN, KC_GRV, KC_SLSH, TO(3), KC_DEL, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, MKR_BRACKET, MKR_ARRAY, KC_COMM, KC_DOT, TO(4), LSFT_T(KC_ENT), KC_SPC, LAY_DEF_2, TO(0)),

    [3] = LAYOUT(KC_F1, KC_F2, KC_F3, KC_F4, RGB_TOG, KC_BRID, KC_BRIU, KC_VOLD, KC_VOLU, TO(2), KC_F5, KC_F6, KC_F7, KC_F8, RGB_INC, KC_INS, KC_HOME, KC_PGUP, RGB_INC, TO(3), KC_F9, KC_F10, KC_F11, KC_F12, RGB_DEC, KC_DEL, KC_END, KC_PGDN, RGB_DEC, TO(4), LSFT_T(KC_ENT), KC_SPC, LAY_DEF_3, TO(0)),

    [4] = LAYOUT(KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_ENT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_NO, KC_NO, KC_NO, KC_LSFT, KC_SPC, KC_LALT, TO(0))};

void keyboard_pre_init_user(void) {
    // Turn off cyntroller led
    setPinOutput(24);
    writePinHigh(24);
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MKR_ARROW: // =>
            if (record->event.pressed) {
                SEND_STRING("=>");
            }
            return false;

        case MKR_ARROW_FN: // = () => {|}
            if (record->event.pressed) {
                SEND_STRING("=()=>{}");
                tap_code(KC_LEFT);
            }
            return false;
        case MKR_QUOTE: // "|"
            if (record->event.pressed) {
                register_code(KC_LSFT);
                tap_code(KC_QUOT);
                tap_code(KC_QUOT);
                unregister_code(KC_LSFT);
                tap_code(KC_LEFT);
            }
            return false;
        case MKR_CURLY: // {|}
            if (record->event.pressed) {
                SEND_STRING("{}");
                tap_code(KC_LEFT);
            }
            return false;
        case MKR_BRACKET: // (|)
            if (record->event.pressed) {
                SEND_STRING("()");
                tap_code(KC_LEFT);
            }
            return false;
        case MKR_ARRAY: // [|]
            if (record->event.pressed) {
                SEND_STRING("[]");
                tap_code(KC_LEFT);
            }
            return false;
        case LT(0, KC_X):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(G(KC_X)); // Intercept hold function to send Ctrl-X
                return false;
            }
            return true; // Return true for normal processing of tap keycode
        case LT(0, KC_C):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(G(KC_C)); // Intercept hold function to send Ctrl-C
                return false;
            }
            return true; // Return true for normal processing of tap keycode
        case LT(0, KC_V):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(G(KC_V)); // Intercept hold function to send Ctrl-V
                return false;
            }
            return true; // Return true for normal processing of tap keycode
        case LT(0, KC_S):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(G(KC_S)); // Intercept hold function to send Ctrl-S
                return false;
            }
            return true; // Return true for normal processing of tap keycode
        case LT(0, KC_LBRC):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_EQL); // Intercept hold function to send =
                return false;
            }

        case LT(0, KC_RBRC):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_GRV); // Intercept hold function to send `
                return false;
            }

        case RGB_INC:
            // Handle brightness increase
            if (record->event.pressed) {
                rgb_offset += 10;
            }
            return false;
        case RGB_DEC:
            // Handle brightness decrease
            if (record->event.pressed) {
                rgb_offset -= 10;
            }
            return false;
        case LAY_DEF_2:
            if (record->event.pressed) {
                layer_move(0);
                return false;
            } else {
                layer_move(2);
                return false;
            }

        case LAY_DEF_3:
            if (record->event.pressed) {
                layer_move(0);
                return false;
            } else {
                layer_move(3);
                return false;
            }
    }
    return true;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

bool isInArr(uint8_t arr[], uint8_t len, uint8_t num) {
    bool success = false;

    for (uint8_t i = 0; i < len; i++) {
        if (arr[i] == num) {
            success = true;
            break;
        }
    }

    return success;
}

void adjOffset(uint8_t r, uint8_t g, uint8_t b) {
    if ((r + rgb_offset >= 255) || (g + rgb_offset >= 255) || (b + rgb_offset >= 255)) {
        rgb_offset -= 10;
    } else if ((r + rgb_offset <= 0) || (g + rgb_offset <= 0) || (b + rgb_offset <= 0)) {
        rgb_offset += 10;
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t curr_layer = get_highest_layer(layer_state | default_layer_state);

    adjOffset(0, 145, 145);

    uint8_t r = 0 + rgb_offset;
    uint8_t g = 90 + rgb_offset;
    uint8_t b = 90 + rgb_offset;

    uint8_t h_index[5][16] = {{33, 41, 42, 43}, {8, 9, 10, 13, 14, 15, 17, 18, 19, 20, 33, 38, 43}, {7, 8, 9, 10, 29, 30, 33, 34, 35, 38, 39, 40, 43}, {29, 30, 31, 32, 33, 38, 43}, {38}};
    uint8_t h_sizes[5]     = {4, 13, 13, 7, 1};

    switch (curr_layer) {
        case 4:
            adjOffset(0, 120, 0);

            r = rgb_offset;
            g = 120 + rgb_offset;
            b = rgb_offset;
            break;
        case 3:
            adjOffset(120, 0, 0);

            r = 120 + rgb_offset;
            g = 0 + rgb_offset;
            b = 0 + rgb_offset;
            break;
        case 2:
            adjOffset(0, 0, 120);

            r = rgb_offset;
            g = rgb_offset;
            b = 120 + rgb_offset;
            break;
        case 1:
            adjOffset(120, 120, 0);

            r = 120 + rgb_offset;
            g = 120 + rgb_offset;
            b = rgb_offset;
            break;

        default:
            break;
    }

    for (uint8_t i = led_min; i < led_max; i++) {
        if (i < 6 || (i > 22 && i < 29)) {
            // underglow/bottom plate
            rgb_matrix_set_color(i, r, g, b);
        } else if ((i > 20 && i < 23) || (i > 43 && i < 46)) {
            // thumb keys backlight
            rgb_matrix_set_color(i, min(r + 60, 255), min(g + 60, 255), min(b + 60, 255));
        } else if (isInArr(h_index[curr_layer], h_sizes[curr_layer], i)) {
            // special highlighted cases
            rgb_matrix_set_color(i, min(g + 30, 255), min(b + 30, 255), min(r + 30, 255));
        } else {
            rgb_matrix_set_color(i, min(b + 30, 255), min(r + 30, 255), min(g + 30, 255));
        }
    }
    return false;
}
