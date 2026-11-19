// pointers1.c
//
// Every variable lives somewhere in memory, at an *address*.
//
//     &x     - "address of x"
//     int *p - "p is a pointer to an int": a variable that holds an address
//     *p     - "the int that p points to" (dereferencing)
//
//     int x = 10;
//     int *p = &x;   // p now holds x's address
//     *p = 20;       // writes through p: x is now 20
//
// Fix the compile error, then fill in the FIXMEs.

// I AM NOT DONE

#include "clings.h"

int main(void) {
    int x = 10;
    int *p = x;

    CHECK_INT(*p, FIXME);

    *p = 25;
    CHECK_INT(x, FIXME);

    x = x + 5;
    CHECK_INT(*p, FIXME);

    int y = 100;
    p = &y;
    *p = *p / 2;
    CHECK_INT(x, FIXME);
    CHECK_INT(y, FIXME);

    // Two pointers can point at the same thing.
    int *q = p;
    *q = 7;
    CHECK_INT(*p, FIXME);
    CHECK(p == q);

    return clings_report();
}
