// project_inventory.c - PROJECT: Shop inventory
//
// You're writing the inventory system for a tiny shop. The Inventory struct
// holds a fixed-size array of items and a count of how many are in use.
// This pulls together arrays, strings, pointers and structs.
//
// Implement:
//
//   Item *inventory_find(Inventory *inv, const char *name)
//       Returns a pointer to the item with that name, or NULL.
//
//   bool inventory_add(Inventory *inv, const char *name, int qty, int price_cents)
//       Adds a new item. If an item with the same name already exists, add
//       qty to its quantity instead (and keep its old price).
//       Returns false if the inventory is full (and a new item was needed),
//       or if the name doesn't fit in the name buffer. Otherwise true.
//
//   long inventory_value(const Inventory *inv)
//       Total value in cents: sum of quantity * price for every item.
//
//   size_t inventory_low_stock(const Inventory *inv, int threshold,
//                              const Item **out, size_t out_cap)
//       Stores pointers to every item with quantity < threshold into `out`
//       (at most out_cap of them). Returns how many were stored.

// I AM NOT DONE

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

// Write your functions here.

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
