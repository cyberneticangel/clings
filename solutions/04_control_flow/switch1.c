// switch1.c - solution

#include "clings.h"

int days_in_month(int month) {
    int days;
    switch (month) {
    case 2:
        days = 28;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        days = 30;
        break;
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
