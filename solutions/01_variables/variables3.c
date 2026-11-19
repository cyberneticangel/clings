// variables3.c - solution

#include "clings.h"

int main(void) {
    int total = 0;
    int answer = 42;

    {
        total = total + answer;
    }

    CHECK_INT(answer, 42);
    CHECK_INT(total, 42);

    return clings_report();
}
