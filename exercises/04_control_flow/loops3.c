// loops3.c
//
// Inside a loop:
//     `continue` skips the rest of this iteration and moves on to the next.
//     `break` exits the loop entirely.
//
// Implement both functions using a loop and `continue` / `break`.

// I AM NOT DONE

#include "clings.h"

// Sum of all numbers from 1 to n that are NOT divisible by 3.
int sum_skipping_threes(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        // TODO: skip multiples of 3
        sum += i;
    }
    return sum;
}

// Smallest number >= start that is divisible by both 7 and 11.
int first_multiple_of_7_and_11(int start) {
    int found = -1;
    for (int i = start; ; i++) {
        // TODO: when i is divisible by both, remember it and stop the loop
    }
    return found;
}

int main(void) {
    CHECK_INT(sum_skipping_threes(5), 1 + 2 + 4 + 5);
    CHECK_INT(sum_skipping_threes(10), 37);
    CHECK_INT(first_multiple_of_7_and_11(1), 77);
    CHECK_INT(first_multiple_of_7_and_11(78), 154);
    CHECK_INT(first_multiple_of_7_and_11(154), 154);

    return clings_report();
}
