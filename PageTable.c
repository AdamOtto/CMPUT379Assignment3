#include <stdlib.h>
#include <stdio.h>

typedef struct PageTable {
    int value;
    struct PageTable *parent;
    struct PageTable *left;
    struct PageTable *right;
} PageTable;

// Return the size of PageTable
int sizeOf(PageTable *parent, int size) {
    if (parent != NULL) {
        size = sizeOf(parent->left, size);
        size = sizeOf(parent->right, size);
        size++;
    }
    return size;
}

// Insert page in the PageTable, return true if hit
int insert(PageTable **start, int value, PageTable *parent) {
    PageTable *p = NULL;

    // Insert to an empty PageTable
    if (*start == NULL) {
        p = malloc(sizeof(PageTable));
        p->value = value;
        p->left = NULL;
        p->right = NULL;
        p->parent = parent;

        *start = p;
        return 0;
    }

    if (value < (*start)->value) {
        insert(&((*start)->left), value, *start);
    } else if (value == (*start)->value) {
        return 1;
    } else {
        insert(&((*start)->right), value, *start);
    }
}
