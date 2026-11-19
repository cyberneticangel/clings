// fnptr1.c - solution

#include "clings.h"

typedef int (*BinaryOp)(int, int);

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }

int apply(BinaryOp op, int a, int b) {
    return op(a, b);
}

int fold(BinaryOp op, int initial, const int *arr, size_t len) {
    int acc = initial;
    for (size_t i = 0; i < len; i++) {
        acc = op(acc, arr[i]);
    }
    return acc;
}

int main(void) {
    CHECK_INT(apply(add, 2, 3), 5);
    CHECK_INT(apply(sub, 2, 3), -1);
    CHECK_INT(apply(mul, 2, 3), 6);

    BinaryOp ops[3] = {add, sub, mul};
    CHECK_INT(ops[0](10, 5), 15);
    CHECK_INT(ops[1](10, 5), 5);
    CHECK_INT(ops[2](10, 5), 50);

    int nums[] = {1, 2, 3, 4, 5};
    CHECK_INT(fold(add, 0, nums, 5), 15);
    CHECK_INT(fold(mul, 1, nums, 5), 120);

    return clings_report();
}
