// operators2.c
//
// `++` and `--` add or subtract one. They come in two flavors:
//
//     x++   (postfix)  - the expression's value is x *before* incrementing
//     ++x   (prefix)   - the expression's value is x *after* incrementing
//
// Either way, x itself ends up incremented.
//
// Fill in the FIXMEs.

// I AM NOT DONE

#include "clings.h"

int main(void) {
    int a = 5;
    int b = a++;
    CHECK_INT(a, FIXME);
    CHECK_INT(b, FIXME);

    int c = ++a;
    CHECK_INT(a, FIXME);
    CHECK_INT(c, FIXME);

    int d = a--;
    CHECK_INT(a, FIXME);
    CHECK_INT(d, FIXME);

    return clings_report();
}
