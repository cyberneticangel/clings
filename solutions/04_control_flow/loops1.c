// loops1.c - solution

#include "clings.h"

int sum_to(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
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
