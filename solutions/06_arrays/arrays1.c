// arrays1.c - solution

#include "clings.h"

int main(void) {
    int primes[5] = {2, 3, 5, 7, 11};

    CHECK_INT(primes[0], 2);
    CHECK_INT(primes[3], 7);

    primes[1] = 13;
    CHECK_INT(primes[1], 13);

    int zeros[4] = {9};
    CHECK_INT(zeros[0], 9);
    CHECK_INT(zeros[3], 0);

    double readings[] = {1.5, 2.5, 3.5};
    CHECK_INT(sizeof(readings) / sizeof(readings[0]), 3);

    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += primes[i];
    }
    CHECK_INT(sum, 2 + 13 + 5 + 7 + 11);

    return clings_report();
}
