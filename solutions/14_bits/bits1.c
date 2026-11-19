// bits1.c - solution

#include <stdbool.h>
#include <stdint.h>

#include "clings.h"

uint32_t set_bit(uint32_t value, int bit) {
    return value | (1u << bit);
}

uint32_t clear_bit(uint32_t value, int bit) {
    return value & ~(1u << bit);
}

uint32_t toggle_bit(uint32_t value, int bit) {
    return value ^ (1u << bit);
}

bool test_bit(uint32_t value, int bit) {
    return (value >> bit) & 1u;
}

int main(void) {
    CHECK_INT(0xF0 & 0x3C, 0x30);
    CHECK_INT(0xF0 | 0x0F, 0xFF);
    CHECK_INT(5 << 3, 40);

    CHECK_INT(set_bit(0, 0), 1);
    CHECK_INT(set_bit(0, 4), 16);
    CHECK_INT(set_bit(16, 4), 16);

    CHECK_INT(clear_bit(0xFF, 0), 0xFE);
    CHECK_INT(clear_bit(0xFF, 7), 0x7F);
    CHECK_INT(clear_bit(0, 3), 0);

    CHECK_INT(toggle_bit(0x0F, 0), 0x0E);
    CHECK_INT(toggle_bit(0x0F, 4), 0x1F);

    CHECK(test_bit(0x80, 7));
    CHECK(!test_bit(0x80, 6));

    return clings_report();
}
