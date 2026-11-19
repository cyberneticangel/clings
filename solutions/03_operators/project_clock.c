// project_clock.c - solution

#include <stdbool.h>

#include "clings.h"

int main(void) {
    int total_seconds = 9999;
    int hours = total_seconds / 3600;
    int minutes = total_seconds % 3600 / 60;
    int seconds = total_seconds % 60;
    CHECK_INT(hours, 2);
    CHECK_INT(minutes, 46);
    CHECK_INT(seconds, 39);

    int now = 22;
    int later = (now + 5) % 24;
    CHECK_INT(later, 3);

    int change = 93;
    int quarters = 0, dimes = 0, nickels = 0, pennies = 0;
    quarters = change / 25;
    change %= 25;
    dimes = change / 10;
    change %= 10;
    nickels = change / 5;
    change %= 5;
    pennies = change;
    CHECK_INT(quarters, 3);
    CHECK_INT(dimes, 1);
    CHECK_INT(nickels, 1);
    CHECK_INT(pennies, 3);

    int code = 4096;
    int digit_sum = code / 1000 + code / 100 % 10 + code / 10 % 10 + code % 10;
    CHECK_INT(digit_sum, 19);
    bool valid = digit_sum % 2 == 1 && code > 1000;
    CHECK(valid);

    return clings_report();
}
