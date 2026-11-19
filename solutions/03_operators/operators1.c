// operators1.c - solution

#include "clings.h"

int main(void) {
    CHECK_INT(17 / 5, 3);
    CHECK_INT(17 % 5, 2);
    CHECK_INT(-17 / 5, -3);
    CHECK_INT(-17 % 5, -2);

    CHECK_INT(2 + 3 * 4, 14);
    CHECK_INT((2 + 3) * 4, 20);

    int x = 10;
    x += 5;
    x *= 2;
    x -= 1;
    x %= 7;
    CHECK_INT(x, 1);

    return clings_report();
}
