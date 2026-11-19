// pointers1.c - solution

#include "clings.h"

int main(void) {
    int x = 10;
    int *p = &x;

    CHECK_INT(*p, 10);

    *p = 25;
    CHECK_INT(x, 25);

    x = x + 5;
    CHECK_INT(*p, 30);

    int y = 100;
    p = &y;
    *p = *p / 2;
    CHECK_INT(x, 30);
    CHECK_INT(y, 50);

    int *q = p;
    *q = 7;
    CHECK_INT(*p, 7);
    CHECK(p == q);

    return clings_report();
}
