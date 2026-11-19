// functions2.c
//
// A function's signature declares its return type and the type of each
// parameter:
//
//     double area(double width, double height)
//
// A function that returns nothing has return type `void`.
// A function that takes nothing has parameter list `(void)`.
//
// Fix the signatures. Don't change the function bodies or main.

// I AM NOT DONE

#include "clings.h"

int counter = 0;

void square(int n) {
    return n * n;
}

double half(int x) {
    return x / 2.0;
}

int bump() {
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
