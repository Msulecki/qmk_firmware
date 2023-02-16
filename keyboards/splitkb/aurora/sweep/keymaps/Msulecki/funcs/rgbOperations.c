#include QMK_KEYBOARD_H
#include "custom_func.h"

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t curr_layer = get_highest_layer(layer_state | default_layer_state);

    float curr_rgb_offset = get_offset();

    uint8_t r = limitTo8Bit(30, curr_rgb_offset);
    uint8_t g = limitTo8Bit(90, curr_rgb_offset);
    uint8_t b = limitTo8Bit(90, curr_rgb_offset);

    uint8_t h_index[5][16] = {{33, 41, 42, 43}, {8, 9, 10, 13, 14, 15, 17, 18, 19, 20, 33, 38, 43}, {7, 8, 9, 10, 29, 30, 33, 34, 35, 38, 39, 40, 43}, {29, 30, 31, 32, 33, 38, 43}, {38}};
    uint8_t h_sizes[5]     = {4, 13, 13, 7, 1};

    switch (curr_layer) {
        case 4:
            r = limitTo8Bit(30, curr_rgb_offset);
            g = limitTo8Bit(120, curr_rgb_offset);
            b = limitTo8Bit(30, curr_rgb_offset);
            break;
        case 3:
            r = limitTo8Bit(120, curr_rgb_offset);
            g = limitTo8Bit(30, curr_rgb_offset);
            b = limitTo8Bit(30, curr_rgb_offset);
            break;
        case 2:
            r = limitTo8Bit(30, curr_rgb_offset);
            g = limitTo8Bit(30, curr_rgb_offset);
            b = limitTo8Bit(120, curr_rgb_offset);
            break;
        case 1:
            r = limitTo8Bit(120, curr_rgb_offset);
            g = limitTo8Bit(120, curr_rgb_offset);
            b = limitTo8Bit(30, curr_rgb_offset);
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
            rgb_matrix_set_color(i, r, g, b);
        } else if (isInArr(h_index[curr_layer], h_sizes[curr_layer], i)) {
            // special highlighted cases
            rgb_matrix_set_color(i, g, b, r);
        } else {
            rgb_matrix_set_color(i, b, r, g);
        }
    }
    return false;
}
