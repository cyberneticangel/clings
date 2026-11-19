// functions2.c - solution

#include "clings.h"

int counter = 0;

int square(int n) {
    return n * n;
}

double half(double x) {
    return x / 2.0;
}

void bump(void) {
    counter++;
}

int main(void) {
    CHECK_INT(square(4), 16);
    CHECK_DBL(half(2.5), 1.25);

    bump();
    bump();
    CHECK_INT(counter, 2);

    return clings_report();
}
