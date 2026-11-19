// linkedlist1.c - solution

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

size_t list_length(const Node *head) {
    size_t n = 0;
    for (const Node *cur = head; cur != NULL; cur = cur->next) {
        n++;
    }
    return n;
}

int list_get(const Node *head, size_t index) {
    const Node *cur = head;
    for (size_t i = 0; i < index; i++) {
        cur = cur->next;
    }
    return cur->value;
}

void list_free(Node *head) {
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

int main(void) {
    Node *list = NULL;
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
