// variables2.c
//
// Variables can be reassigned, and you can declare several at once.
// Fill in the FIXMEs with the values you expect each variable to hold.

// I AM NOT DONE

#include "clings.h"

int main(void) {
    int a = 3, b = 4;
    int sum = a + b;

    a = 10;            // changing `a` now does NOT change `sum`
    int product = a * b;

    b = b + 1;

    CHECK_INT(sum, FIXME);
    CHECK_INT(product, FIXME);
    CHECK_INT(b, FIXME);

    return clings_report();
}
