// loops3.c - solution

#include "clings.h"

int sum_skipping_threes(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        if (i % 3 == 0) {
            continue;
        }
        sum += i;
    }
    return sum;
}

int first_multiple_of_7_and_11(int start) {
    int found = -1;
    for (int i = start; ; i++) {
        if (i % 7 == 0 && i % 11 == 0) {
            found = i;
            break;
        }
    }
    return found;
}

int main(void) {
    CHECK_INT(sum_skipping_threes(5), 1 + 2 + 4 + 5);
    CHECK_INT(sum_skipping_threes(10), 37);
    CHECK_INT(first_multiple_of_7_and_11(1), 77);
    CHECK_INT(first_multiple_of_7_and_11(78), 154);
    CHECK_INT(first_multiple_of_7_and_11(154), 154);

    return clings_report();
}
