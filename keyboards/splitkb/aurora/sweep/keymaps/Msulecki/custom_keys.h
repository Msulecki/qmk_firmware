#include QMK_KEYBOARD_H

/*
LED MAP
         0-5 - left backlight        23-28 - right backlight
            6  7  8  9  10              29 30 31 32 33
            11 12 13 14 15              34 35 36 37 38
            16 17 18 19 20              39 40 41 42 43
                        21 22        44 45
*/

enum custom_keycodes { MKR_ARROW = SAFE_RANGE, MKR_ARROW_FN, MKR_QUOTE, MKR_CURLY, MKR_BRACKET, MKR_ARRAY, RGB_INC, RGB_DEC, LAY_DEF_2, LAY_DEF_3 };
