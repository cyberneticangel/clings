// types4.c - solution

#include <stdint.h>

#include "clings.h"

int main(void) {
    uint64_t world_population = 8100000000;
    uint8_t percent = 100;
    int8_t temperature = -40;

    CHECK_INT(world_population, 8100000000);
    CHECK_INT(percent, 100);
    CHECK_INT(temperature, -40);

    return clings_report();
}
