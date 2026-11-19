// structs3.c - solution

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

const Person *oldest(const Person *people, size_t count) {
    const Person *best = &people[0];
    for (size_t i = 1; i < count; i++) {
        if (people[i].age > best->age) {
            best = &people[i];
        }
    }
    return best;
}

int count_in_city(const Person *people, size_t count, const char *city) {
    int n = 0;
    for (size_t i = 0; i < count; i++) {
        if (strcmp(people[i].address.city, city) == 0) {
            n++;
        }
    }
    return n;
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
