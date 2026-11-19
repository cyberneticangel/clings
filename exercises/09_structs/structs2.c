// structs2.c
//
// Structs are passed by value too: the function gets a copy of the whole
// struct. To modify the caller's struct (or to avoid copying a big one), pass
// a pointer.
//
// With a pointer to a struct, use `->` to reach its members:
//
//     p->x    is shorthand for    (*p).x
//
// `typedef` gives a type a new name, so you can write `Point` instead of
// `struct Point`.
//
// Fix `move_by` so it actually moves the point.

// I AM NOT DONE

#include "clings.h"

typedef struct {
    int x;
    int y;
} Point;

void move_by(Point p, int dx, int dy) {
    p.x += dx;
    p.y += dy;
}

int main(void) {
    Point p = {.x = 1, .y = 1};

    move_by(p, 2, 3);
    CHECK_INT(p.x, 3);
    CHECK_INT(p.y, 4);

    move_by(p, -3, 0);
    CHECK_INT(p.x, 0);
    CHECK_INT(p.y, 4);

    return clings_report();
}
