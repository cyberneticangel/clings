// types3.c
//
// Integer types have a fixed size, so they can only hold a limited range of
// values.
//
// *Unsigned* types (which can't be negative) wrap around when they overflow:
// for an 8-bit unsigned char, 255 + 1 becomes 0, and 0 - 1 becomes 255.
// (Overflowing a *signed* type like int is undefined behavior: a bug. The
// sanitizer in clings will catch it.)
//
// Fill in the FIXMEs.

// I AM NOT DONE

#include "clings.h"

int main(void) {
    unsigned char a = 250;
    a = a + 10;
    CHECK_INT(a, FIXME);

    unsigned char b = 0;
    b = b - 1;
    CHECK_INT(b, FIXME);

    unsigned int c = 3;
    c = c - 5;
    // unsigned int is 32 bits: it holds 0 to 4294967295
    CHECK_INT(c, FIXME);

    return clings_report();
}
