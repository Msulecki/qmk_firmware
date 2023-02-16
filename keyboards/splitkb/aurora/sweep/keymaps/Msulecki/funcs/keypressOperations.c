#include QMK_KEYBOARD_H
#include "custom_func.h"
#include "../custom_keys.h"

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
                correct_offset(1);
            }
            return false;
        case RGB_DEC:
            // Handle brightness decrease
            if (record->event.pressed) {
                correct_offset(-1);
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
