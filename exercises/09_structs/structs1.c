// structs1.c
//
// A struct groups related values together into a new type:
//
//     struct Point {
//         int x;
//         int y;
//     };
//
//     struct Point p = {3, 4};          // positional initializer
//     struct Point q = {.y = 4, .x = 3}; // designated initializer (clearer!)
//     p.x = 10;                          // access a member with `.`
//
// Define `struct Rect` with two members, `width` and `height` (both double),
// then implement `area`.

// I AM NOT DONE

#include "clings.h"

// TODO: define struct Rect here

double area(struct Rect r) {
    // TODO
}

int main(void) {
    struct Rect r = {.width = 3.0, .height = 4.0};
    CHECK_DBL(r.width, 3.0);
    CHECK_DBL(area(r), 12.0);

    r.height = 10.0;
    CHECK_DBL(area(r), 30.0);

    struct Rect square = {2.5, 2.5};
    CHECK_DBL(area(square), 6.25);

    return clings_report();
}
