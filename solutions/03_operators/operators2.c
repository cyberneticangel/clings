// operators2.c - solution

#include "clings.h"

int main(void) {
    int a = 5;
    int b = a++;
    CHECK_INT(a, 6);
    CHECK_INT(b, 5);

    int c = ++a;
    CHECK_INT(a, 7);
    CHECK_INT(c, 7);

    int d = a--;
    CHECK_INT(a, 6);
    CHECK_INT(d, 7);

    return clings_report();
}
