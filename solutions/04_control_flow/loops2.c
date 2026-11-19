// loops2.c - solution

#include "clings.h"

int count_digits(int n) {
    int digits = 0;
    if (n < 0) {
        n = -n;
    }
    do {
        n /= 10;
        digits++;
    } while (n != 0);
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
