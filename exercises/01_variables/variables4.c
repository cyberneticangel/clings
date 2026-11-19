// variables4.c
//
// `const` marks a variable as read-only. The compiler will stop you if you
// try to change it. That's a feature: it documents intent and catches bugs.
//
// Here, `max_players` is meant to change, but `board_size` is not.
// Fix the declarations (not the assignments) so this compiles.

// I AM NOT DONE

#include "clings.h"

int main(void) {
    const int max_players = 2;
    int board_size = 8;

    max_players = 4; // more players joined!

    CHECK_INT(max_players, 4);
    CHECK_INT(board_size, 8);

    return clings_report();
}
