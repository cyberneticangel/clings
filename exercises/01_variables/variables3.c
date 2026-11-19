// variables3.c
//
// A variable only exists inside the block `{ ... }` where it is declared.
// This is called its *scope*.
//
// Make this compile without changing the checks.

// I AM NOT DONE

#include "clings.h"

int main(void) {
    int total = 0;

    {
        int answer = 42;
        total = total + answer;
    }

    CHECK_INT(answer, 42);
    CHECK_INT(total, 42);

    return clings_report();
}
