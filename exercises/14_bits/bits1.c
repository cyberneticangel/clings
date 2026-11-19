// bits1.c
//
// Bitwise operators work on the individual bits of integers:
//
//     a & b    AND   - 1 where both bits are 1
//     a | b    OR    - 1 where either bit is 1
//     a ^ b    XOR   - 1 where the bits differ
//     ~a       NOT   - flips every bit
//     a << n   shift left  (multiply by 2^n)
//     a >> n   shift right (divide by 2^n, for unsigned)
//
// (1u << n) is a number with only bit n set: a "mask".
// Always use unsigned types for bit manipulation.
//
// Implement the four helper functions using bitwise operators.

// I AM NOT DONE

#include <stdbool.h>
#include <stdint.h>

#include "clings.h"

uint32_t set_bit(uint32_t value, int bit) {
    // TODO
}

uint32_t clear_bit(uint32_t value, int bit) {
    // TODO
}

uint32_t toggle_bit(uint32_t value, int bit) {
    // TODO
}

bool test_bit(uint32_t value, int bit) {
    // TODO
}

int main(void) {
    CHECK_INT(0xF0 & 0x3C, FIXME);
    CHECK_INT(0xF0 | 0x0F, FIXME);
    CHECK_INT(5 << 3, FIXME);

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
