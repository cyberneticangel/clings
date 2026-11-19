// variables4.c - solution

#include "clings.h"

int main(void) {
    int max_players = 2;
    const int board_size = 8;

    max_players = 4;

    CHECK_INT(max_players, 4);
    CHECK_INT(board_size, 8);

    return clings_report();
}
