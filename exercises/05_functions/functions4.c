// functions4.c
//
// Normal local variables are created fresh every time a function is called.
// A local variable declared `static` is created once and keeps its value
// between calls (but is still only visible inside the function).
//
// Make `next_id` return 1, 2, 3, ... on successive calls.

// I AM NOT DONE

#include "clings.h"

int next_id(void) {
    int id = 0;
    id++;
    return id;
}

int main(void) {
    CHECK_INT(next_id(), 1);
    CHECK_INT(next_id(), 2);
    CHECK_INT(next_id(), 3);

    return clings_report();
}
