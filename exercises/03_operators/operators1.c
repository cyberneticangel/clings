// operators1.c
//
// Arithmetic operators: +  -  *  /  %
//
// `%` is the remainder ("modulo") operator. With integers, `/` truncates
// toward zero, and the sign of `%` follows the left-hand side.
//
// Fill in the FIXMEs. Try to work them out before peeking at the output!

// I AM NOT DONE

#include "clings.h"

int main(void) {
    CHECK_INT(17 / 5, FIXME);
    CHECK_INT(17 % 5, FIXME);
    CHECK_INT(-17 / 5, FIXME);
    CHECK_INT(-17 % 5, FIXME);

    // Precedence: * / % bind tighter than + -
    CHECK_INT(2 + 3 * 4, FIXME);
    CHECK_INT((2 + 3) * 4, FIXME);

    // Compound assignment
    int x = 10;
    x += 5;
    x *= 2;
    x -= 1;
    x %= 7;
    CHECK_INT(x, FIXME);

    return clings_report();
}
