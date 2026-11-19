// project_numbers.c - solution

#include "clings.h"

int main(void) {
    int fizz = 0, buzz = 0, fizzbuzz = 0;
    for (int i = 1; i <= 100; i++) {
        if (i % 15 == 0) {
            fizzbuzz++;
        } else if (i % 3 == 0) {
            fizz++;
        } else if (i % 5 == 0) {
            buzz++;
        }
    }
    CHECK_INT(fizz, 27);
    CHECK_INT(buzz, 14);
    CHECK_INT(fizzbuzz, 6);

    int steps = 0, peak = 0;
    int n = 27;
    while (n != 1) {
        if (n % 2 == 0) {
            n /= 2;
        } else {
            n = 3 * n + 1;
        }
        if (n > peak) {
            peak = n;
        }
        steps++;
    }
    CHECK_INT(steps, 111);
    CHECK_INT(peak, 9232);

    int prime_count = 0;
    for (int i = 2; i < 100; i++) {
        int is_prime = 1;
        for (int d = 2; d * d <= i; d++) {
            if (i % d == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) {
            prime_count++;
        }
    }
    CHECK_INT(prime_count, 25);

    int perfect_sum = 0;
    for (int i = 2; i < 10000; i++) {
        int divisor_sum = 0;
        for (int d = 1; d < i; d++) {
            if (i % d == 0) {
                divisor_sum += d;
            }
        }
        if (divisor_sum == i) {
            perfect_sum += i;
        }
    }
    CHECK_INT(perfect_sum, 6 + 28 + 496 + 8128);

    return clings_report();
}
