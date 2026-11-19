// fnptr2.c - solution

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
    return (*x > *y) - (*x < *y);
}

int compare_by_age(const void *a, const void *b) {
    const Person *x = a;
    const Person *y = b;
    return (x->age > y->age) - (x->age < y->age);
}

int compare_by_name(const void *a, const void *b) {
    const Person *x = a;
    const Person *y = b;
    return strcmp(x->name, y->name);
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
