// switch1.c
//
// `switch` jumps to the `case` label matching a value. Careful though:
// execution then *falls through* into the following cases until it hits a
// `break` (or `return`). Forgetting `break` is a famous source of bugs, so
// our compiler flags make accidental fall-through an error.
//
// Fix `days_in_month` (ignore leap years for now).

// I AM NOT DONE

#include "clings.h"

int days_in_month(int month) {
    int days;
    switch (month) {
    case 2:
        days = 28;
    case 4:
    case 6:
    case 9:
    case 11:
        days = 30;
    default:
        days = 31;
    }
    return days;
}

int main(void) {
    CHECK_INT(days_in_month(1), 31);
    CHECK_INT(days_in_month(2), 28);
    CHECK_INT(days_in_month(4), 30);
    CHECK_INT(days_in_month(11), 30);
    CHECK_INT(days_in_month(12), 31);

    return clings_report();
}
