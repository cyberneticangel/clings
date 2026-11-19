// arrays4.c
//
// Arrays can have more than one dimension. A 2D array is an array of arrays:
//
//     int grid[2][3] = {
//         {1, 2, 3},
//         {4, 5, 6},
//     };
//
// grid[1][2] is row 1, column 2: the value 6.
//
// Implement `transpose`, which swaps rows and columns, and `trace`, which
// sums the main diagonal (grid[0][0] + grid[1][1] + ...).

// I AM NOT DONE

#include "clings.h"

#define N 3

void transpose(int in[N][N], int out[N][N]) {
    // TODO
}

int trace(int m[N][N]) {
    // TODO
}

int main(void) {
    int m[N][N] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
    };
    int t[N][N] = {{0}};

    transpose(m, t);
    CHECK_INT(t[0][0], 1);
    CHECK_INT(t[0][1], 4);
    CHECK_INT(t[0][2], 7);
    CHECK_INT(t[2][0], 3);
    CHECK_INT(t[1][2], 8);

    CHECK_INT(trace(m), 15);
    CHECK_INT(trace(t), 15);

    return clings_report();
}
