// structs1.c - solution

#include "clings.h"

struct Rect {
    double width;
    double height;
};

double area(struct Rect r) {
    return r.width * r.height;
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
