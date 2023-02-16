static uint8_t RGB_OFFSET = 10;

void set_offset(uint8_t offset) {
    RGB_OFFSET = offset;
}

uint8_t get_offset(void) {
    return RGB_OFFSET;
}

void correct_offset(int8_t val) {
    if (RGB_OFFSET < 15 && val > 0) {
        RGB_OFFSET += val;
    } else if (RGB_OFFSET > 1 && val < 0) {
        RGB_OFFSET += val;
    }
}
