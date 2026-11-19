// bst1.c - solution

#include <stdbool.h>
#include <stdlib.h>

#include "clings.h"

typedef struct Tree {
    int value;
    struct Tree *left;
    struct Tree *right;
} Tree;

Tree *tree_insert(Tree *root, int value) {
    if (root == NULL) {
        Tree *node = malloc(sizeof(*node));
        if (node != NULL) {
            node->value = value;
            node->left = NULL;
            node->right = NULL;
        }
        return node;
    }
    if (value < root->value) {
        root->left = tree_insert(root->left, value);
    } else if (value > root->value) {
        root->right = tree_insert(root->right, value);
    }
    return root;
}

bool tree_contains(const Tree *root, int value) {
    while (root != NULL) {
        if (value == root->value) {
            return true;
        }
        root = value < root->value ? root->left : root->right;
    }
    return false;
}

int tree_height(const Tree *root) {
    if (root == NULL) {
        return 0;
    }
    int l = tree_height(root->left);
    int r = tree_height(root->right);
    return 1 + (l > r ? l : r);
}

void tree_in_order(const Tree *root, int *out, size_t *n) {
    if (root == NULL) {
        return;
    }
    tree_in_order(root->left, out, n);
    out[(*n)++] = root->value;
    tree_in_order(root->right, out, n);
}

void tree_free(Tree *root) {
    if (root == NULL) {
        return;
    }
    tree_free(root->left);
    tree_free(root->right);
    free(root);
}

int main(void) {
    int values[] = {8, 3, 10, 1, 6, 14, 4, 7, 13, 6};
    Tree *root = NULL;
    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        root = tree_insert(root, values[i]);
    }

    CHECK(tree_contains(root, 6));
    CHECK(tree_contains(root, 13));
    CHECK(!tree_contains(root, 5));
    CHECK(!tree_contains(NULL, 1));

    CHECK_INT(tree_height(root), 4);
    CHECK_INT(tree_height(NULL), 0);

    int sorted[16];
    size_t n = 0;
    tree_in_order(root, sorted, &n);
    CHECK_INT(n, 9);
    int expected[] = {1, 3, 4, 6, 7, 8, 10, 13, 14};
    for (size_t i = 0; i < 9 && i < n; i++) {
        CHECK_INT(sorted[i], expected[i]);
    }

    tree_free(root);
    return clings_report();
}
