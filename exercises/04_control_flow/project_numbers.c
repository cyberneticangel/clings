// project_numbers.c - PROJECT: Number explorer
//
// Use loops and conditions to answer four classic number puzzles.
// Everything goes in main; you'll learn to split code into functions in the
// next section.

// I AM NOT DONE

#include "clings.h"

int main(void) {
    // --- Part 1: FizzBuzz counting ---
    // For the numbers 1 to 100, count how many would print "Fizz" (divisible
    // by 3 only), "Buzz" (by 5 only), and "FizzBuzz" (by both).
    int fizz = 0, buzz = 0, fizzbuzz = 0;
    // TODO
    CHECK_INT(fizz, 27);
    CHECK_INT(buzz, 14);
    CHECK_INT(fizzbuzz, 6);

    // --- Part 2: Collatz ---
    // Start at n = 27. Repeat until n is 1:
    //     if n is even, n = n / 2, otherwise n = 3n + 1
    // Count the steps, and track the highest value reached.
    int steps = 0, peak = 0;
    // TODO
    CHECK_INT(steps, 111);
    CHECK_INT(peak, 9232);

    // --- Part 3: primes ---
    // Count the primes below 100. (A prime has no divisors between 2 and
    // itself. You only need to test divisors d where d * d <= n.)
    int prime_count = 0;
    // TODO: nested loops, with `break` when you find a divisor
    CHECK_INT(prime_count, 25);

    // --- Part 4: perfect numbers ---
    // A perfect number equals the sum of its divisors smaller than itself:
    // 6 = 1 + 2 + 3. Find the sum of all perfect numbers below 10000.
    int perfect_sum = 0;
    // TODO
    CHECK_INT(perfect_sum, 6 + 28 + 496 + 8128);

    return clings_report();
}
