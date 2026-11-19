// functions3.c
//
// C passes arguments *by value*: the function receives a copy. Changing a
// parameter inside a function does not affect the caller's variable.
//
// (Later you'll learn to use pointers to change the caller's variable. For
// now, use the return value.)
//
// Fix `double_it` and the code in main so the checks pass.

// I AM NOT DONE

#include "clings.h"

void double_it(int x) {
    x = x * 2;
}

int main(void) {
    int value = 21;
    double_it(value);
    CHECK_INT(value, 42);

    return clings_report();
}
