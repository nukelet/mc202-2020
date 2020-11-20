#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "handle_memory_error.h"

typedef struct node_ 
{
	struct node_* left;
	struct node_* right;
	struct node_* parent;

	int key;
	char* msg;
} node;

typedef struct tree_
{
	node* root;
} tree;

node* node_new(int key, char* msg)
{
	node* new = malloc(sizeof(*new));
	handle_memory_error(new);

	new->left = new->right = new->parent = NULL;
	new->key = key;
	new->msg = malloc(strlen(msg)*sizeof(char) + 1);
	strcpy(new->msg, msg);

	return new;
}

void node_destroy(node* n)
{
	free(n->msg);
	free(n);
}

// for debug purposes
void node_print(node* n)
{
	// -1 is the "parent" of the root node
	if (n == NULL)
	{
		printf("NULL\n");
		return;
	}

	int parent = n->parent == NULL ? -1 : n->parent->key;
	int left = n->left == NULL ? -1 : n->left->key;
	int right = n->right == NULL ? -1 : n->right->key;
	printf("node: %d, parent: %d, left: %d, right: %d\nmsg: \"%s\"\n", n->key, parent, left, right, n->msg);

	return;
}

void node_copy(node* dest, node* src)
{
	dest->key = src->key;
	free(dest->msg); dest->msg = malloc(strlen(src->msg)*sizeof(char) + 1);
	strcpy(dest->msg, src->msg);

	return;
}

void traverse(node* n)
{
	if (n == NULL)
		return;

	traverse(n->left); traverse(n->right);
	printf("%d", n->key);
	
}

void in_order(node* n)
{
	if (n == NULL)
		return;

	in_order(n->left);
	node_print(n);
	in_order(n->right);
}

node* insert(node* n, int key, char* msg)
{
	if (n == NULL)
	{
		node* new = node_new(key, msg);

		return new;
	}

	else if (key == n->key)
	{
		fprintf(stderr, "Node with key %d is already in the tree\n", key);
		exit(1);
	}

	else if (key > n->key)
	{
		n->right = insert(n->right, key, msg);
		n->right->parent = n;
	}

	else if (key < n->key)
	{
		n->left = insert(n->left, key, msg);
		n->left->parent = n;
	}

	return n;
}

int is_left_child(node* n)
{
	node* p = n->parent;
	if (p == NULL || n == p->right)
		return 0;
	else
		return 1;
}

int is_right_child(node* n)
{
	node* p = n->parent;
	if (p == NULL || n == p->left)
		return 0;
	else
		return 1;
}

node* min(node* n)
{
	if (n->left == NULL)
		return n;

	else
		return min(n->left);
}

// returns NULL if there is no successor
node* successor(node* n)
{
	if (n->right != NULL)
	{
		return min(n->right);
	}

	else
	{
		node* p = n->parent;
		while(1)
		{
			if (p == NULL || is_left_child(n))
				return p;
			else
			{
				n = p; p = p->parent;
			}
		}
	}
}

node* find(node* n, int key)
{
	if (n == NULL)
		return NULL;

	if (key > n->key)
		return find(n->right, key);

	else if (key < n->key)
		return find(n->left, key);

	else
		return n;
}

void delete_node(node* p)
{
	// safety measure, so that we can do 
	// delete_node(find(tree, key))
	if (p == NULL)
	{
		fprintf(stderr, "\ncan't delete null node\n\n");
		return;
	}

	// 1st case: node is a leaf
	if (p->left == NULL && p->right == NULL)
	{
		if (is_left_child(p))
			p->parent->left = NULL;

		else if (is_right_child(p))
			p->parent->right = NULL;

		node_destroy(p);
		return;
	}

	// 2nd case: node has only one subtree
	if (p->left != NULL && p->right == NULL)
	{
		if (is_left_child(p))
			p->parent->left = p->left;

		else if (is_right_child(p))
			p->parent->right = p->left;

		// handles deleting the root node
		else
		{
			// copies child to root, then unlinks
			// and deletes child
			node* tmp = p->left;
			node_copy(p, tmp);
			p->left = tmp->left; p->right = tmp->right;

			if (tmp->left != NULL)
				tmp->left->parent = p;

			if (tmp->right != NULL)
				tmp->right->parent = p;

			node_destroy(tmp);

			return;
		}

		p->left->parent = p->parent;
		node_destroy(p);
		return;
	}

	if (p->left == NULL && p->right != NULL)
	{
		if (is_left_child(p))
			p->parent->left = p->right;

		else if (is_right_child(p))
			p->parent->right = p->right;

		// handles deleting the root node
		else
		{
			// copies child to root, then unlinks
			// and deletes child
			node* tmp = p->right;
			node_copy(p, tmp);
			p->left = tmp->left; p->right = tmp->right;

			if (tmp->left != NULL)
				tmp->left->parent = p;

			if (tmp->right != NULL)
				tmp->right->parent = p;

			node_destroy(tmp);

			return;
		}

		p->right->parent = p->parent;
		node_destroy(p);
		return;
	}

	// 3rd case: node has two subtrees

	node* s = successor(p);

	// copy the contents of successor node, which always
	// exists if p has a right subtree
	node_copy(p, s);

	// delete successor node
	delete_node(s);
}

void tree_destroy(node* n)
{
	if (n == NULL)
		return;

	tree_destroy(n->left);
	tree_destroy(n->right);
	node_destroy(n);
}

void message_print(node* n)
{
	if (n == NULL)
		return;

	message_print(n->left);

	printf("%s", n->msg);

	message_print(n->right);
}

int main(int argc, char const *argv[])
{
	int m, n;

	while (scanf("%d %d", &m, &n) == 2)
	{
		node* t;
		for (int i = 0; i < m; i++)
		{
			int key;
			char msg[6];
			scanf("%d \"%[^\"]\"", &key, msg);

			if (i == 0)
				t = node_new(key, msg);

			else
				insert(t, key, msg);

		}

		for (int c = 0; c < n; c++)
		{
			int s;
			
			scanf("%d", &s);

			int flag = 0;

			node *i, *j, *k;

			node* n_min = min(t);

			for (i = n_min; i != NULL; i = successor(i))
			{
				for (j = n_min; j != NULL; j = successor(j))
				{
					k = find(t, s- i->key - j->key);

					if (i == j || j == k || k == i || k == NULL)
						continue;

					int sum = i->key + j->key + k->key;

					if (sum == s)
					{
						flag = 1;
						break;
					}
				}

				if (flag)
					break;
			}

			node* triplet = node_new(i->key, i->msg);
			insert(triplet, j->key, j->msg);
			insert(triplet, k->key, k->msg);

			int size = 0;

			for (node* it = min(triplet); it != NULL; it = successor(it))
				size += strlen(it->msg);

			char* tmp = malloc(size*sizeof(char) + 1);
			tmp[0] = '\0';

			for (node* it = min(triplet); it != NULL; it = successor(it))
			{
				strcat(tmp, it->msg);
			}

			insert(t, s, tmp);

			for (node* it = min(triplet); it != NULL; it = successor(it))
				delete_node(find(t, it->key));
			
			free(tmp);


			tree_destroy(triplet);
		}

		message_print(t); printf("\n");

		tree_destroy(t);
	}

	return 0;
}