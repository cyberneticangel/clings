// types3.c - solution

#include "clings.h"

int main(void) {
    unsigned char a = 250;
    a = a + 10;
    CHECK_INT(a, 4);

    unsigned char b = 0;
    b = b - 1;
    CHECK_INT(b, 255);

    unsigned int c = 3;
    c = c - 5;
    CHECK_INT(c, 4294967294);

    return clings_report();
}
