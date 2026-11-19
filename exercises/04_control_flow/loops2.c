// loops2.c
//
// `while (cond) { ... }` checks the condition *before* each iteration, so the
// body might never run.
// `do { ... } while (cond);` checks *after*, so the body always runs at
// least once.
//
// `count_digits` should return how many decimal digits a number has.
// 0 has one digit! Fix the function.

// I AM NOT DONE

#include "clings.h"

int count_digits(int n) {
    int digits = 0;
    if (n < 0) {
        n = -n;
    }
    while (n != 0) {
        n /= 10;
        digits++;
    }
    return digits;
}

int main(void) {
    CHECK_INT(count_digits(7), 1);
    CHECK_INT(count_digits(42), 2);
    CHECK_INT(count_digits(12345), 5);
    CHECK_INT(count_digits(-900), 3);
    CHECK_INT(count_digits(0), 1);

    return clings_report();
}
