// bits2.c - solution

#include <stdbool.h>
#include <stdint.h>

#include "clings.h"

enum {
    PERM_READ = 1 << 0,
    PERM_WRITE = 1 << 1,
    PERM_EXEC = 1 << 2,
};

void perms_to_string(unsigned perms, char out[4]) {
    out[0] = (perms & PERM_READ) ? 'r' : '-';
    out[1] = (perms & PERM_WRITE) ? 'w' : '-';
    out[2] = (perms & PERM_EXEC) ? 'x' : '-';
    out[3] = '\0';
}

int popcount(uint32_t x) {
    int count = 0;
    while (x != 0) {
        count += x & 1u;
        x >>= 1;
    }
    return count;
}

bool is_power_of_two(uint32_t x) {
    return x != 0 && (x & (x - 1)) == 0;
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
