// structs2.c - solution

#include "clings.h"

typedef struct {
    int x;
    int y;
} Point;

void move_by(Point *p, int dx, int dy) {
    p->x += dx;
    p->y += dy;
}

int main(void) {
    Point p = {.x = 1, .y = 1};

    move_by(&p, 2, 3);
    CHECK_INT(p.x, 3);
    CHECK_INT(p.y, 4);

    move_by(&p, -3, 0);
    CHECK_INT(p.x, 0);
    CHECK_INT(p.y, 4);

    return clings_report();
}
