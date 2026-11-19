// types2.c
//
// Integer division throws away the fractional part:  7 / 2 == 3
//
// If you want a fractional result, at least one side of the division must
// be a floating point value. You can convert ("cast") a value to another type
// by writing the type in parentheses in front of it:  (double)x
//
// Fix `average` so it returns the real average. Don't change the checks.

// I AM NOT DONE

#include "clings.h"

double average(int total, int count) {
    return total / count;
}

int main(void) {
    CHECK_INT(7 / 2, 3);
    CHECK_DBL(7.0 / 2, 3.5);

    CHECK_DBL(average(10, 4), 2.5);
    CHECK_DBL(average(9, 3), 3.0);
    CHECK_DBL(average(1, 3), 0.333333);

    return clings_report();
}
