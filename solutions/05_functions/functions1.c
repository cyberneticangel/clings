// functions1.c - solution

#include "clings.h"

int triple(int n);

int main(void) {
    CHECK_INT(triple(3), 9);
    CHECK_INT(triple(-2), -6);

    return clings_report();
}

int triple(int n) {
    return n * 3;
}
