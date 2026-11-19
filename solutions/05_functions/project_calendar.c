// project_calendar.c - solution

#include <stdbool.h>

#include "clings.h"

bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int days_in_month(int month, int year) {
    switch (month) {
    case 2:
        return is_leap_year(year) ? 29 : 28;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    default:
        return 0;
    }
}

int day_of_year(int day, int month, int year) {
    int total = day;
    for (int m = 1; m < month; m++) {
        total += days_in_month(m, year);
    }
    return total;
}

int day_of_week(int day, int month, int year) {
    long days = 0;
    for (int y = 1900; y < year; y++) {
        days += is_leap_year(y) ? 366 : 365;
    }
    days += day_of_year(day, month, year) - 1;
    return (int)((1 + days) % 7);
}

int main(void) {
    CHECK(is_leap_year(1996));
    CHECK(is_leap_year(2000));
    CHECK(!is_leap_year(1900));
    CHECK(!is_leap_year(2023));

    CHECK_INT(days_in_month(1, 2023), 31);
    CHECK_INT(days_in_month(2, 2023), 28);
    CHECK_INT(days_in_month(2, 2024), 29);
    CHECK_INT(days_in_month(4, 2023), 30);
    CHECK_INT(days_in_month(13, 2023), 0);

    CHECK_INT(day_of_year(1, 1, 2023), 1);
    CHECK_INT(day_of_year(1, 2, 2023), 32);
    CHECK_INT(day_of_year(31, 12, 2023), 365);
    CHECK_INT(day_of_year(31, 12, 2024), 366);

    CHECK_INT(day_of_week(1, 1, 1900), 1);
    CHECK_INT(day_of_week(20, 7, 1969), 0);
    CHECK_INT(day_of_week(1, 1, 2000), 6);
    CHECK_INT(day_of_week(29, 2, 2024), 4);

    return clings_report();
}
