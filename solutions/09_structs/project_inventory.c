// project_inventory.c - solution

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "clings.h"

#define MAX_ITEMS 4
#define NAME_LEN 16

typedef struct {
    char name[NAME_LEN];
    int quantity;
    int price_cents;
} Item;

typedef struct {
    Item items[MAX_ITEMS];
    size_t count;
} Inventory;

Item *inventory_find(Inventory *inv, const char *name) {
    for (size_t i = 0; i < inv->count; i++) {
        if (strcmp(inv->items[i].name, name) == 0) {
            return &inv->items[i];
        }
    }
    return NULL;
}

bool inventory_add(Inventory *inv, const char *name, int qty, int price_cents) {
    Item *existing = inventory_find(inv, name);
    if (existing != NULL) {
        existing->quantity += qty;
        return true;
    }
    if (inv->count >= MAX_ITEMS || strlen(name) >= NAME_LEN) {
        return false;
    }
    Item *item = &inv->items[inv->count++];
    strcpy(item->name, name); // safe: length checked above
    item->quantity = qty;
    item->price_cents = price_cents;
    return true;
}

long inventory_value(const Inventory *inv) {
    long total = 0;
    for (size_t i = 0; i < inv->count; i++) {
        total += (long)inv->items[i].quantity * inv->items[i].price_cents;
    }
    return total;
}

size_t inventory_low_stock(const Inventory *inv, int threshold,
                           const Item **out, size_t out_cap) {
    size_t n = 0;
    for (size_t i = 0; i < inv->count && n < out_cap; i++) {
        if (inv->items[i].quantity < threshold) {
            out[n++] = &inv->items[i];
        }
    }
    return n;
}

int main(void) {
    Inventory inv = {.count = 0};

    CHECK(inventory_add(&inv, "apple", 10, 50));
    CHECK(inventory_add(&inv, "banana", 2, 25));
    CHECK(inventory_add(&inv, "cherry", 100, 5));
    CHECK_INT(inv.count, 3);

    CHECK(inventory_add(&inv, "apple", 5, 999));
    CHECK_INT(inv.count, 3);

    Item *apple = inventory_find(&inv, "apple");
    CHECK(apple != NULL);
    if (apple) {
        CHECK_INT(apple->quantity, 15);
        CHECK_INT(apple->price_cents, 50);
    }
    CHECK(inventory_find(&inv, "durian") == NULL);

    CHECK(!inventory_add(&inv, "an extremely long fruit name", 1, 1));

    CHECK(inventory_add(&inv, "date", 1, 300));
    CHECK(!inventory_add(&inv, "elderberry", 1, 1));
    CHECK(inventory_add(&inv, "date", 1, 300));
    CHECK_INT(inv.count, 4);

    CHECK_INT(inventory_value(&inv), 750 + 50 + 500 + 600);

    const Item *low[MAX_ITEMS];
    size_t n = inventory_low_stock(&inv, 5, low, MAX_ITEMS);
    CHECK_INT(n, 2);
    if (n == 2) {
        CHECK_STR(low[0]->name, "banana");
        CHECK_STR(low[1]->name, "date");
    }
    CHECK_INT(inventory_low_stock(&inv, 5, low, 1), 1);

    return clings_report();
}
