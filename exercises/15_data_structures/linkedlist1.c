// linkedlist1.c
//
// A linked list is a chain of heap-allocated nodes. Each node holds a value
// and a pointer to the next node. The last node's `next` is NULL.
//
//     head -> [3 | *] -> [2 | *] -> [1 | NULL]
//
// Unlike an array, you can add or remove at the front in constant time, but
// you can't jump straight to the n-th element.
//
// Implement the four functions. Every node you malloc must be freed in
// `list_free`, or LeakSanitizer will complain.

// I AM NOT DONE

#include <stdlib.h>

#include "clings.h"

typedef struct Node {
    int value;
    struct Node *next;   // a struct can point to its own type
} Node;

// Creates a new node holding `value` in front of `head`; returns the new head.
Node *list_push_front(Node *head, int value) {
    // TODO
}

size_t list_length(const Node *head) {
    // TODO
}

// Returns the value at position `index` (0 = head). Assumes index is valid.
int list_get(const Node *head, size_t index) {
    // TODO
}

// Frees every node.
void list_free(Node *head) {
    // TODO: careful! You can't read node->next after freeing node.
}

int main(void) {
    Node *list = NULL;   // an empty list
    CHECK_INT(list_length(list), 0);

    list = list_push_front(list, 1);
    list = list_push_front(list, 2);
    list = list_push_front(list, 3);

    CHECK_INT(list_length(list), 3);
    CHECK_INT(list_get(list, 0), 3);
    CHECK_INT(list_get(list, 1), 2);
    CHECK_INT(list_get(list, 2), 1);

    list_free(list);

    return clings_report();
}
