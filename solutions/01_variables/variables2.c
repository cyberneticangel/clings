// variables2.c - solution

#include "clings.h"

int main(void) {
    int a = 3, b = 4;
    int sum = a + b;

    a = 10;
    int product = a * b;

    b = b + 1;

    CHECK_INT(sum, 7);
    CHECK_INT(product, 40);
    CHECK_INT(b, 5);

    return clings_report();
}
