// fnptr1.c
//
// Functions live in memory too, so you can take a pointer to a function and
// call it later. The syntax takes some getting used to:
//
//     int (*op)(int, int);   // op is a pointer to a function taking two
//                            // ints and returning an int
//     op = add;              // the function name turns into a pointer
//     int r = op(2, 3);      // call it like a normal function
//
// A typedef makes this much more readable:
//
//     typedef int (*BinaryOp)(int, int);
//     BinaryOp op = add;
//
// Implement `apply`, and fill in the table of operations.

// I AM NOT DONE

#include "clings.h"

typedef int (*BinaryOp)(int, int);

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }

// Calls op on a and b.
int apply(BinaryOp op, int a, int b) {
    // TODO
}

// Applies op to every element of arr, combining from left to right:
//   fold(add, 0, {1,2,3}) = ((0 + 1) + 2) + 3
int fold(BinaryOp op, int initial, const int *arr, size_t len) {
    // TODO
}

int main(void) {
    CHECK_INT(apply(add, 2, 3), 5);
    CHECK_INT(apply(sub, 2, 3), -1);
    CHECK_INT(apply(mul, 2, 3), 6);

    BinaryOp ops[3] = {FIXME};
    CHECK_INT(ops[0](10, 5), 15);
    CHECK_INT(ops[1](10, 5), 5);
    CHECK_INT(ops[2](10, 5), 50);

    int nums[] = {1, 2, 3, 4, 5};
    CHECK_INT(fold(add, 0, nums, 5), 15);
    CHECK_INT(fold(mul, 1, nums, 5), 120);

    return clings_report();
}
