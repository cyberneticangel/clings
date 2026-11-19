// functions3.c - solution

#include "clings.h"

int double_it(int x) {
    return x * 2;
}

int main(void) {
    int value = 21;
    value = double_it(value);
    CHECK_INT(value, 42);

    return clings_report();
}
