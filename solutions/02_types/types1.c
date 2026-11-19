// types1.c - solution

#include "clings.h"

int main(void) {
    CHECK_INT(sizeof(char), 1);
    CHECK_INT(sizeof(int), 4);
    CHECK_INT(sizeof(double), 8);

    char letter = 'A';
    CHECK_INT(letter, 65);
    CHECK_INT(letter + 2, 'C');

    double pi = 3.14159;
    CHECK_DBL(pi * 2, 6.28318);

    return clings_report();
}
