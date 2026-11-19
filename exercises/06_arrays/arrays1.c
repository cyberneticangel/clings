// arrays1.c
//
// An array is a fixed-size sequence of elements of the same type, stored
// next to each other in memory:
//
//     int primes[5] = {2, 3, 5, 7, 11};
//
// Elements are accessed with an index starting at 0: primes[0] is 2,
// primes[4] is 11.
//
// sizeof(array) is the size of the whole array in bytes, so the number of
// elements is  sizeof(array) / sizeof(array[0]).
//
// Fill in the FIXMEs.

// I AM NOT DONE

#include "clings.h"

int main(void) {
    int primes[5] = {2, 3, 5, 7, 11};

    CHECK_INT(primes[0], FIXME);
    CHECK_INT(primes[3], FIXME);

    primes[1] = 13;
    CHECK_INT(primes[1], FIXME);

    // Missing elements in an initializer are set to 0.
    int zeros[4] = {9};
    CHECK_INT(zeros[0], FIXME);
    CHECK_INT(zeros[3], FIXME);

    // If you leave the size out, the compiler counts for you.
    double readings[] = {1.5, 2.5, 3.5};
    CHECK_INT(sizeof(readings) / sizeof(readings[0]), FIXME);

    // Sum up all the elements of primes.
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        // TODO
    }
    CHECK_INT(sum, 2 + 13 + 5 + 7 + 11);

    return clings_report();
}
