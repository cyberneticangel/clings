// loops1.c
//
// The `for` loop has three parts: initialization, condition, and step.
//
//     for (int i = 0; i < 10; i++) {
//         // runs with i = 0, 1, 2, ..., 9
//     }
//
// `sum_to(n)` should return 1 + 2 + ... + n. It's off by one. Fix it.

// I AM NOT DONE

#include "clings.h"

int sum_to(int n) {
    int sum = 0;
    for (int i = 1; i < n; i++) {
        sum += i;
    }
    return sum;
}

int main(void) {
    CHECK_INT(sum_to(1), 1);
    CHECK_INT(sum_to(3), 6);
    CHECK_INT(sum_to(10), 55);
    CHECK_INT(sum_to(0), 0);

    return clings_report();
}
