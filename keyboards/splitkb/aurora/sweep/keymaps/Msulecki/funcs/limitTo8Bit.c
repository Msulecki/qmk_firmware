uint8_t limitTo8Bit(uint8_t input, uint8_t offset) {
    int8_t  adj_offset = offset - 10;
    uint8_t result     = input;

    if (adj_offset < 0) {
        result = input * (10 + adj_offset) / 10;
    } else if (adj_offset > 0) {
        result = input + (255 - input) * adj_offset / 10;
        result = result > 255 ? 255 : result;
    }
    return result;
}
