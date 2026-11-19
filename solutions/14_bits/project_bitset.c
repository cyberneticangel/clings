// project_bitset.c - solution

#include <stdbool.h>
#include <stdint.h>

#include "clings.h"

typedef struct {
    uint64_t words[4];
} Bitset;

void bs_add(Bitset *s, unsigned v) {
    s->words[v / 64] |= 1ULL << (v % 64);
}

void bs_remove(Bitset *s, unsigned v) {
    s->words[v / 64] &= ~(1ULL << (v % 64));
}

bool bs_contains(const Bitset *s, unsigned v) {
    return (s->words[v / 64] >> (v % 64)) & 1ULL;
}

int bs_count(const Bitset *s) {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        uint64_t w = s->words[i];
        while (w != 0) {
            w &= w - 1; // clear lowest set bit
            count++;
        }
    }
    return count;
}

Bitset bs_union(Bitset a, Bitset b) {
    Bitset r;
    for (int i = 0; i < 4; i++) {
        r.words[i] = a.words[i] | b.words[i];
    }
    return r;
}

Bitset bs_intersection(Bitset a, Bitset b) {
    Bitset r;
    for (int i = 0; i < 4; i++) {
        r.words[i] = a.words[i] & b.words[i];
    }
    return r;
}

Bitset primes_below_256(void) {
    Bitset s = {{0}};
    for (unsigned i = 2; i < 256; i++) {
        bs_add(&s, i);
    }
    for (unsigned p = 2; p * p < 256; p++) {
        if (bs_contains(&s, p)) {
            for (unsigned m = p * p; m < 256; m += p) {
                bs_remove(&s, m);
            }
        }
    }
    return s;
}

int main(void) {
    Bitset s = {{0}};
    bs_add(&s, 0);
    bs_add(&s, 63);
    bs_add(&s, 64);
    bs_add(&s, 255);
    bs_add(&s, 64);
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
    CHECK(!bs_contains(&primes, 221));

    return clings_report();
}
