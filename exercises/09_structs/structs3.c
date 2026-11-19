// structs3.c
//
// Structs can contain arrays, other structs, and you can have arrays of
// structs. Let's model a tiny address book.
//
// Implement `oldest` and `count_in_city`.

// I AM NOT DONE

#include <stddef.h>
#include <string.h>

#include "clings.h"

typedef struct {
    char city[32];
    char country[32];
} Address;

typedef struct {
    char name[32];
    int age;
    Address address;
} Person;

// Returns a pointer to the oldest person in the array.
const Person *oldest(const Person *people, size_t count) {
    // TODO
}

// Returns how many people live in `city`.
int count_in_city(const Person *people, size_t count, const char *city) {
    // TODO
}

int main(void) {
    Person people[] = {
        {"Ada", 36, {"London", "UK"}},
        {"Grace", 85, {"New York", "USA"}},
        {"Linus", 54, {"Portland", "USA"}},
        {"Alan", 41, {"London", "UK"}},
    };
    size_t n = sizeof(people) / sizeof(people[0]);

    const Person *o = oldest(people, n);
    CHECK_STR(o->name, "Grace");
    CHECK_STR(o->address.country, "USA");

    CHECK_INT(count_in_city(people, n, "London"), 2);
    CHECK_INT(count_in_city(people, n, "Portland"), 1);
    CHECK_INT(count_in_city(people, n, "Paris"), 0);

    return clings_report();
}
