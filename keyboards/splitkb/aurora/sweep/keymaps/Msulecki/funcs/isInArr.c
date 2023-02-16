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
