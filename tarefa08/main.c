#include <stdio.h>
#include <stdlib.h>
#include "rb_tree.h"

int node_key(rb_node* n)
{
	return n == NULL ? -1 : n->key;
}

// for debugging purposes
void rb_node_print(rb_node* n, void* args)
{
	if (n == NULL)
	{
		printf("NULL\n");
		return;
	}

	printf("node: %d, count: %d\nparent: %d\nleft: %d, right: %d\ncolor: %s\n\n",
			n->key, n->count,
			node_key(n->parent),
			node_key(n->left), node_key(n->right),
			n->color == RED ? "RED" : "BLACK");

	return;
}

// checks how many elements to remove until
// the list is "cool"
void rb_func(rb_node* n, void* p_count)
{
	int* count = (int*) p_count;

	if (n->count < n->key)
		*count += n->count;

	else if (n->count > n->key)
		*count += n->count - n->key;

	return;
}

int main(int argc, char const *argv[])
{
	rb_tree* t;

	int n, k; scanf("%d %d", &n, &k);

	for (int i = 0; i < n; i++)
	{
		int d; scanf(" %d", &d);

		if (i == 0)
			t = rb_new(d);

		else
			rb_insert(t, d);
	}

	for (int i = 0; i < k; i++)
	{
		int operation; scanf("%d", &operation);
		int d, count = 0;

		switch(operation)
		{
			case 1:
				scanf(" %d", &d);
				rb_insert(t, d);
				break;

			case 2:
				scanf(" %d", &d);
				rb_node* p = rb_find(t, d);
				printf("%d\n", p != NULL ? p->count : 0);
				break;

			case 3:
				rb_in_order(t, &rb_func, &count);
				printf("%d\n", count);
				break;
		}
	}

	// rb_in_order(t, &rb_node_print, NULL);

	rb_destroy(t);
	return 0;
}