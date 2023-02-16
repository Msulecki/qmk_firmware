#include QMK_KEYBOARD_H

void keyboard_pre_init_user(void) {
    // Turn off cyntroller led
    setPinOutput(24);
    writePinHigh(24);
}
