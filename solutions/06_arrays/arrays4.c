// arrays4.c - solution

#include "clings.h"

#define N 3

void transpose(int in[N][N], int out[N][N]) {
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            out[c][r] = in[r][c];
        }
    }
}

int trace(int m[N][N]) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum += m[i][i];
    }
    return sum;
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
