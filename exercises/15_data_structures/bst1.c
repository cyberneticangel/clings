// bst1.c
//
// A binary search tree: every node has up to two children. Everything in
// the left subtree is smaller than the node; everything in the right
// subtree is larger. That makes lookups fast (on a balanced tree).
//
//             8
//           /   \
//          3     10
//         / \      \
//        1   6      14
//
// Trees are naturally recursive: most operations are "handle this node,
// then recurse into the left and/or right child".
//
// Implement the functions. Ignore duplicate values on insert.

// I AM NOT DONE

#include <stdbool.h>
#include <stdlib.h>

#include "clings.h"

typedef struct Tree {
    int value;
    struct Tree *left;
    struct Tree *right;
} Tree;

// Inserts value and returns the (possibly new) root.
Tree *tree_insert(Tree *root, int value) {
    // TODO
}

bool tree_contains(const Tree *root, int value) {
    // TODO
}

// Number of nodes on the longest path from the root to a leaf.
// An empty tree has height 0.
int tree_height(const Tree *root) {
    // TODO
}

// Writes values in sorted order (left, node, right) into out.
// `*n` is the number written so far; update it as you go.
void tree_in_order(const Tree *root, int *out, size_t *n) {
    // TODO
}

void tree_free(Tree *root) {
    // TODO
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
    CHECK_INT(n, 9);   // the duplicate 6 was ignored
    int expected[] = {1, 3, 4, 6, 7, 8, 10, 13, 14};
    for (size_t i = 0; i < 9 && i < n; i++) {
        CHECK_INT(sorted[i], expected[i]);
    }

    tree_free(root);
    return clings_report();
}
