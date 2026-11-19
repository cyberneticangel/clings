// project_bitset.c - PROJECT: Bitset & the Sieve of Eratosthenes
//
// A bitset stores a set of small non-negative integers using ONE BIT per
// possible value. Here, values 0..255 fit in 256 bits = four uint64_t words.
// Value v lives in word v / 64, at bit v % 64.
//
// Implement:
//   void bs_add(Bitset *s, unsigned v)
//   void bs_remove(Bitset *s, unsigned v)
//   bool bs_contains(const Bitset *s, unsigned v)
//   int  bs_count(const Bitset *s)                 number of values in the set
//   Bitset bs_union(Bitset a, Bitset b)            values in a OR b
//   Bitset bs_intersection(Bitset a, Bitset b)     values in a AND b
//
// Then use your bitset to implement the Sieve of Eratosthenes:
//   Bitset primes_below_256(void)
//     Start with every number 2..255 in the set. For each p still in the
//     set (with p * p < 256), remove all multiples of p starting at p * p.
//     What's left are the primes.
//
// Use 1ULL (unsigned long long), not 1, when shifting by up to 63 bits!

// I AM NOT DONE

#include <stdbool.h>
#include <stdint.h>

#include "clings.h"

typedef struct {
    uint64_t words[4];
} Bitset;

// Write your functions here.

int main(void) {
    Bitset s = {{0}};
    bs_add(&s, 0);
    bs_add(&s, 63);
    bs_add(&s, 64);
    bs_add(&s, 255);
    bs_add(&s, 64);  // already there
    CHECK(bs_contains(&s, 0));
    CHECK(bs_contains(&s, 63));
    CHECK(bs_contains(&s, 64));
    CHECK(bs_contains(&s, 255));
    CHECK(!bs_contains(&s, 1));
    CHECK_INT(bs_count(&s), 4);

    bs_remove(&s, 63);
    CHECK(!bs_contains(&s, 63));
    CHECK_INT(bs_count(&s), 3);

    Bitset evens = {{0}}, small = {{0}};
    for (unsigned i = 0; i < 256; i += 2) bs_add(&evens, i);
    for (unsigned i = 0; i < 10; i++) bs_add(&small, i);

    Bitset u = bs_union(evens, small);
    Bitset in = bs_intersection(evens, small);
    CHECK_INT(bs_count(&u), 128 + 5);
    CHECK_INT(bs_count(&in), 5);
    CHECK(bs_contains(&in, 8));
    CHECK(!bs_contains(&in, 9));

    Bitset primes = primes_below_256();
    CHECK_INT(bs_count(&primes), 54);
    CHECK(bs_contains(&primes, 2));
    CHECK(bs_contains(&primes, 251));
    CHECK(!bs_contains(&primes, 1));
    CHECK(!bs_contains(&primes, 221)); // 13 * 17

    return clings_report();
}
