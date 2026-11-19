// functions1.c
//
// The C compiler reads your file from top to bottom. If you call a function
// before the compiler has seen it, it doesn't know the function's parameter
// and return types.
//
// The fix is a *prototype* (a declaration): the function's signature
// followed by a semicolon, placed before the first use:
//
//     int triple(int n);
//
// The definition (with the body) can then come later. Header files (.h) are
// mostly collections of prototypes like this.
//
// Make this compile WITHOUT moving `triple` above main.

// I AM NOT DONE

#include "clings.h"

int main(void) {
    CHECK_INT(triple(3), 9);
    CHECK_INT(triple(-2), -6);

    return clings_report();
}

int triple(int n) {
    return n * 3;
}
