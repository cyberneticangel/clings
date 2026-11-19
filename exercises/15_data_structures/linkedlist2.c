// linkedlist2.c
//
// Two classic linked list operations:
//
//   list_reverse: reverse the list in place by re-pointing every `next`.
//
//   list_remove: remove (and free) the first node with a given value.
//     The tricky case is removing the head, since the caller's head pointer
//     must change. Taking a *pointer to the head pointer* (Node **) solves
//     this neatly: walk a `Node **link` through the list, and when you find
//     the node, do `*link = node->next`.
//
// The helpers from linkedlist1 are provided.

// I AM NOT DONE

#include <stdbool.h>
#include <stdlib.h>

#include "clings.h"

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node *list_push_front(Node *head, int value) {
    Node *node = malloc(sizeof(*node));
    if (node == NULL) {
        return head;
    }
    node->value = value;
    node->next = head;
    return node;
}

void list_free(Node *head) {
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

// Writes the list's values into out (at most cap), returns how many.
size_t list_to_array(const Node *head, int *out, size_t cap) {
    size_t n = 0;
    for (; head != NULL && n < cap; head = head->next) {
        out[n++] = head->value;
    }
    return n;
}

// Reverses the list and returns the new head.
Node *list_reverse(Node *head) {
    // TODO
}

// Removes the first node whose value equals `value`.
// Returns true if a node was removed.
bool list_remove(Node **head, int value) {
    // TODO
}

int main(void) {
    Node *list = NULL;
    for (int i = 5; i >= 1; i--) {
        list = list_push_front(list, i);   // 1 2 3 4 5
    }

    int out[8];
    list = list_reverse(list);
    CHECK_INT(list_to_array(list, out, 8), 5);
    CHECK_INT(out[0], 5);
    CHECK_INT(out[4], 1);

    CHECK(list_remove(&list, 3));          // middle: 5 4 2 1
    CHECK(list_remove(&list, 5));          // head:   4 2 1
    CHECK(list_remove(&list, 1));          // tail:   4 2
    CHECK(!list_remove(&list, 99));        // not there

    size_t n = list_to_array(list, out, 8);
    CHECK_INT(n, 2);
    CHECK_INT(out[0], 4);
    CHECK_INT(out[1], 2);

    CHECK(list_reverse(NULL) == NULL);

    list_free(list);
    return clings_report();
}
