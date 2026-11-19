// bits2.c
//
// A common use of bits: packing several yes/no flags into one integer.
// Each flag gets its own bit:
//
//     enum { PERM_READ = 1 << 0, PERM_WRITE = 1 << 1, PERM_EXEC = 1 << 2 };
//     unsigned perms = PERM_READ | PERM_WRITE;    // combine flags
//     if (perms & PERM_WRITE) { ... }             // test a flag
//     perms &= ~PERM_WRITE;                       // remove a flag
//
// Implement the functions below.

// I AM NOT DONE

#include <stdbool.h>
#include <stdint.h>

#include "clings.h"

enum {
    PERM_READ = 1 << 0,
    PERM_WRITE = 1 << 1,
    PERM_EXEC = 1 << 2,
};

// Writes a 3-character permission string like "rw-" or "r-x" into out
// (out must have room for 4 chars including '\0').
void perms_to_string(unsigned perms, char out[4]) {
    // TODO
}

// Counts how many bits are set to 1.
int popcount(uint32_t x) {
    // TODO
}

// A power of two has exactly one bit set. (0 is not a power of two.)
// Bonus: can you do it without a loop? Hint: look at x & (x - 1).
bool is_power_of_two(uint32_t x) {
    // TODO
}

int main(void) {
    char buf[4];
    perms_to_string(PERM_READ | PERM_WRITE, buf);
    CHECK_STR(buf, "rw-");
    perms_to_string(PERM_READ | PERM_EXEC, buf);
    CHECK_STR(buf, "r-x");
    perms_to_string(0, buf);
    CHECK_STR(buf, "---");
    perms_to_string(PERM_READ | PERM_WRITE | PERM_EXEC, buf);
    CHECK_STR(buf, "rwx");

    CHECK_INT(popcount(0), 0);
    CHECK_INT(popcount(0xFF), 8);
    CHECK_INT(popcount(0x80000001), 2);
    CHECK_INT(popcount(0xFFFFFFFF), 32);

    CHECK(is_power_of_two(1));
    CHECK(is_power_of_two(64));
    CHECK(is_power_of_two(0x80000000));
    CHECK(!is_power_of_two(0));
    CHECK(!is_power_of_two(12));

    return clings_report();
}
