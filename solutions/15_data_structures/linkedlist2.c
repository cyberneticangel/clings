// linkedlist2.c - solution

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

size_t list_to_array(const Node *head, int *out, size_t cap) {
    size_t n = 0;
    for (; head != NULL && n < cap; head = head->next) {
        out[n++] = head->value;
    }
    return n;
}

Node *list_reverse(Node *head) {
    Node *prev = NULL;
    while (head != NULL) {
        Node *next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

bool list_remove(Node **head, int value) {
    for (Node **link = head; *link != NULL; link = &(*link)->next) {
        Node *node = *link;
        if (node->value == value) {
            *link = node->next;
            free(node);
            return true;
        }
    }
    return false;
}

int main(void) {
    Node *list = NULL;
    for (int i = 5; i >= 1; i--) {
        list = list_push_front(list, i);
    }

    int out[8];
    list = list_reverse(list);
    CHECK_INT(list_to_array(list, out, 8), 5);
    CHECK_INT(out[0], 5);
    CHECK_INT(out[4], 1);

    CHECK(list_remove(&list, 3));
    CHECK(list_remove(&list, 5));
    CHECK(list_remove(&list, 1));
    CHECK(!list_remove(&list, 99));

    size_t n = list_to_array(list, out, 8);
    CHECK_INT(n, 2);
    CHECK_INT(out[0], 4);
    CHECK_INT(out[1], 2);

    CHECK(list_reverse(NULL) == NULL);

    list_free(list);
    return clings_report();
}
