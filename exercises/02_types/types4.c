// types4.c
//
// Because `int` and `long` can have different sizes on different platforms,
// <stdint.h> provides *fixed-width* integer types whose size is guaranteed:
//
//     int8_t   int16_t   int32_t   int64_t     (signed)
//     uint8_t  uint16_t  uint32_t  uint64_t    (unsigned)
//
// The world population doesn't fit in 32 bits. Pick types that are big
// enough (and use unsigned where negatives make no sense).

// I AM NOT DONE

#include <stdint.h>

#include "clings.h"

int main(void) {
    int32_t world_population = 8100000000;
    uint8_t percent = 100;
    int8_t temperature = -40;

    CHECK_INT(world_population, 8100000000);
    CHECK_INT(percent, 100);
    CHECK_INT(temperature, -40);

    return clings_report();
}
