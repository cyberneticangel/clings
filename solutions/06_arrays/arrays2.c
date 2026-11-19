// arrays2.c - solution

#include "clings.h"

int main(void) {
    int squares[6];
    for (int i = 0; i < 6; i++) {
        squares[i] = i * i;
    }

    CHECK_INT(squares[0], 0);
    CHECK_INT(squares[5], 25);

    return clings_report();
}
