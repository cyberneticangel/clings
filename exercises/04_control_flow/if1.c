// if1.c
//
// `if` runs a block only when its condition is true:
//
//     if (temperature > 30) {
//         ...
//     } else if (temperature > 15) {
//         ...
//     } else {
//         ...
//     }
//
// Implement `bigger` so it returns the larger of its two arguments.

// I AM NOT DONE

#include "clings.h"

int bigger(int a, int b) {
    // TODO: complete this function
}

int main(void) {
    CHECK_INT(bigger(10, 8), 10);
    CHECK_INT(bigger(32, 42), 42);
    CHECK_INT(bigger(-5, -9), -5);
    CHECK_INT(bigger(7, 7), 7);

    return clings_report();
}
