// project_clock.c - PROJECT: Clocks, coins and checksums
//
// `/` and `%` together are surprisingly powerful. Fill in the TODOs.

// I AM NOT DONE

#include <stdbool.h>

#include "clings.h"

int main(void) {
    // --- Part 1: break a duration into hours, minutes, seconds ---
    int total_seconds = 9999;
    int hours = 0;   // TODO
    int minutes = 0; // TODO (0-59)
    int seconds = 0; // TODO (0-59)
    CHECK_INT(hours, 2);
    CHECK_INT(minutes, 46);
    CHECK_INT(seconds, 39);

    // --- Part 2: clock arithmetic ---
    // It's 22:00. What time will it be 5 hours later? (24-hour clock)
    int now = 22;
    int later = 0; // TODO
    CHECK_INT(later, 3);

    // --- Part 3: make change using the fewest coins ---
    // Coins: 25, 10, 5, 1 cents. Give change for 93 cents.
    int change = 93;
    int quarters = 0, dimes = 0, nickels = 0, pennies = 0;
    // TODO: compute each count, reducing `change` as you go (%= is handy)
    CHECK_INT(quarters, 3);
    CHECK_INT(dimes, 1);
    CHECK_INT(nickels, 1);
    CHECK_INT(pennies, 3);

    // --- Part 4: digit checksum ---
    // Sum the digits of a 4-digit number using / and %.
    int code = 4096;
    int digit_sum = 0; // TODO
    CHECK_INT(digit_sum, 19);
    // The code is valid when its digit sum is odd and it's above 1000.
    bool valid = false; // TODO
    CHECK(valid);

    return clings_report();
}
