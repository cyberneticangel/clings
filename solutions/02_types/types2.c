// types2.c - solution

#include "clings.h"

double average(int total, int count) {
    return (double)total / count;
}

int main(void) {
    CHECK_INT(7 / 2, 3);
    CHECK_DBL(7.0 / 2, 3.5);

    CHECK_DBL(average(10, 4), 2.5);
    CHECK_DBL(average(9, 3), 3.0);
    CHECK_DBL(average(1, 3), 0.333333);

    return clings_report();
}
