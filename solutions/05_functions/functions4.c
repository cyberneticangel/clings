// functions4.c - solution

#include "clings.h"

int next_id(void) {
    static int id = 0;
    id++;
    return id;
}

int main(void) {
    CHECK_INT(next_id(), 1);
    CHECK_INT(next_id(), 2);
    CHECK_INT(next_id(), 3);

    return clings_report();
}
