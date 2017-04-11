
#include <stdlib.h>
#include <stdio.h>

typedef struct tree {
	int value;
	struct tree *parent;
	struct tree *left;
	struct tree *right;
} tree;

int get_int(char *prompt);
int traverse(tree *parent, int size);
int insert(tree **root, int value, tree *parent);
void flush_stdin(void);
/*
int main(int argc, char *argv[]) {
        int i;
	int cmd = 0, value = 0;
	tree *root = NULL;
	
	do {
		printf("Avaliable commands\n\n"
				"1 - Insert\n"
				"0 - Quit\n\n");

		cmd = get_int("Command");

		switch (cmd) {
			case 1:
				value = get_int("value to insert");
				int b = insert(&root, value, NULL);
                                if (b) {
                                    printf("Inserted successfully");
                                }
				break;
		}
	
		printf("\n");
		for (i=0; i<120; i++, printf("-"));
		printf("\n");
		
		int si = traverse(root, 0);
		printf("size = %d\n", si);
		
		printf("\n");
		for (i=0; i<120; i++, printf("-"));
		printf("\n\n");

	} while (cmd != 0);

	return 0;
}
*/
// Walk through the tree using In-Order
int traverse(tree *parent, int size) {
	if (parent != NULL) {
		size = traverse(parent->left, size);
		printf("(%d)->", parent->value);
		size = traverse(parent->right, size);
		size++;
	}
	return size;
}

// Insert an element in the PageTable
// Return true if hit
int insert(tree **root, int value, tree *parent) {
	tree *p = NULL;

	// Insert to an empty tree
	if (*root == NULL) {
		p = malloc(sizeof(tree));

		p->value = value;
		p->left = NULL;
		p->right = NULL;
		p->parent = parent;

		*root = p;

		return 0;
	}

	if (value < (*root)->value) {
		insert(&((*root)->left), value, *root);
	} else if (value == (*root)->value) {
		return 1;
	} else {
		insert(&((*root)->right), value, *root);
	}
}

// Get int
int get_int(char *prompt) {
	int value = 0;

	printf("%s: ", prompt);
	scanf("%d", &value);
	
	flush_stdin();

	return value;
}


// Flush input buffer
void flush_stdin(void) {
	while (getc(stdin) != '\n');
}
