// fnptr2.c
//
// The standard library's `qsort` can sort an array of ANY type, because you
// give it a *comparison function*:
//
//     void qsort(void *base, size_t count, size_t size,
//                int (*compar)(const void *, const void *));
//
// `void *` is a generic pointer: it can point to anything, and you have to
// convert it back to the real type before using it.
//
// The comparator gets pointers to two elements and must return
//     a negative number if a should come before b,
//     0 if they're equal,
//     a positive number if a should come after b.
//
// Implement the three comparators.

// I AM NOT DONE

#include <stdlib.h>
#include <string.h>

#include "clings.h"

typedef struct {
    char name[16];
    int age;
} Person;

int compare_ints(const void *a, const void *b) {
    const int *x = a;
    const int *y = b;
    // TODO: Careful, `return *x - *y` can overflow! Compare instead.
}

int compare_by_age(const void *a, const void *b) {
    // TODO
}

int compare_by_name(const void *a, const void *b) {
    // TODO
}

int main(void) {
    int nums[] = {5, -3, 2147483647, 0, -2147483647, 42};
    qsort(nums, 6, sizeof(nums[0]), compare_ints);
    CHECK_INT(nums[0], -2147483647);
    CHECK_INT(nums[1], -3);
    CHECK_INT(nums[5], 2147483647);

    Person people[] = {{"Carol", 35}, {"Alice", 41}, {"Bob", 29}};

    qsort(people, 3, sizeof(Person), compare_by_age);
    CHECK_STR(people[0].name, "Bob");
    CHECK_STR(people[2].name, "Alice");

    qsort(people, 3, sizeof(Person), compare_by_name);
    CHECK_STR(people[0].name, "Alice");
    CHECK_STR(people[1].name, "Bob");
    CHECK_STR(people[2].name, "Carol");

    return clings_report();
}
