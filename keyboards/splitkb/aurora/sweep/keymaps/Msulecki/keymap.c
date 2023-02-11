#include QMK_KEYBOARD_H

enum custom_keycodes { MKR_ARROW = SAFE_RANGE, MKR_ARROW_FN, MKR_QUOTE, MKR_CURLY, MKR_BRACKET, MKR_ARRAY };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[0] = LAYOUT(KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_BSPC, KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O, KC_Z, LT(0, KC_X), LT(0, KC_C), KC_D, LT(0, KC_V), KC_K, KC_H, LT(0, KC_LBRC), LT(0, KC_RBRC), KC_SLSH, LSFT_T(KC_ENT), KC_SPC, LGUI_T(KC_COMM), LT(1, KC_DOT)),
                                                              [1] = LAYOUT(KC_PMNS, KC_PPLS, KC_7, KC_8, KC_9, KC_MINS, KC_EQL, KC_F3, KC_F12, TG(2), KC_PSLS, KC_PAST, KC_4, KC_5, KC_6, KC_SCLN, KC_QUOT, KC_BSLS, KC_SLSH, TG(3), KC_PENT, KC_0, KC_1, KC_2, KC_3, KC_LBRC, KC_RBRC, KC_COMM, KC_DOT, TG(4), LSFT_T(KC_ENT), KC_SPC, KC_NO, KC_TRNS),
                                                              [2] = LAYOUT(KC_ESC, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, MKR_QUOTE, MKR_CURLY, KC_TRNS, KC_TRNS, TG(2), KC_TAB, KC_WH_U, KC_BTN1, KC_MS_U, KC_BTN2, MKR_ARROW, MKR_ARROW_FN, KC_GRV, KC_SLSH, TG(3), KC_DEL, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, MKR_BRACKET, MKR_ARRAY, KC_COMM, KC_DOT, TG(4), LSFT_T(KC_ENT), KC_SPC, LT(0, KC_NO), TG(0)),
                                                              [3] = LAYOUT(KC_F1, KC_F2, KC_F3, KC_F4, KC_NO, KC_BRID, KC_BRIU, KC_VOLD, KC_VOLU, TG(2), KC_F5, KC_F6, KC_F7, KC_F8, KC_NO, KC_INS, KC_HOME, KC_PGUP, KC_NO, TG(3), KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, KC_DEL, KC_END, KC_PGDN, KC_NO, TG(4), LSFT_T(KC_ENT), KC_SPC, LT(0, KC_NO), TG(0)),
                                                              [4] = LAYOUT(KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_ENT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_NO, KC_NO, KC_NO, KC_LSFT, KC_SPC, KC_LALT, TG(0))};

void keyboard_pre_init_user(void) {
    // Set our LED pin as output
    setPinOutput(24);
    // Turn the LED off
    // (Due to technical reasons, high is off and low is on)
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
    }
    return true;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t r = 50;
    uint8_t g = 50;
    uint8_t b = 230;

    switch (get_highest_layer(layer_state | default_layer_state)) {
        case 8:
            r = 230;
            g = 50;
            b = 50;
            break;
        case 7:
            r = 230;
            g = 10;
            b = 50;
            break;
        case 6:
            r = 230;
            g = 50;
            b = 10;
            break;
        case 5:
            r = 50;
            g = 230;
            b = 50;
            break;
        case 4:
            r = 10;
            g = 230;
            b = 50;
            break;
        case 3:
            r = 50;
            g = 230;
            b = 10;
            break;
        case 2:
            r = 230;
            g = 10;
            b = 230;
            break;
        case 1:
            r = 10;
            g = 230;
            b = 230;
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
            rgb_matrix_set_color(i, RGB_BLUE);
        } else {
            // standard keys backlight
            rgb_matrix_set_color(i, RGB_PINK);
        }
    }
    return false;
}
