#include <stdlib.h>
#include <stdio.h>

#include "handle_memory_error.h"
#include "rb_tree.h"

rb_node* rb_node_new(int key)
{
	rb_node* new = malloc(sizeof(*new));
	handle_memory_error(new);
	
	new->key = key;
	new->count = 1;
	new->color = RED;

	new->left = new->right = new->parent = NULL;

	return new;
}

rb_tree* rb_new(int key)
{
	rb_node* root = rb_node_new(key);
	root->color = BLACK;

	rb_tree* tree_new = malloc(sizeof(*tree_new));
	handle_memory_error(tree_new);

	tree_new->root = root;

	return tree_new;
}

void rb_destroy_rec(rb_node* n)
{
	if (n == NULL)
		return;

	rb_destroy_rec(n->left);
	rb_destroy_rec(n->right);

	free(n);

	return;
}

void rb_destroy(rb_tree* t)
{
	rb_destroy_rec(t->root);
	free(t);

	return;
}

/*

		r
	   / \
	  p   3	
	 / \
	1 	2

		p
	   / \
	  1	  r
	  	 / \
	  	2	3

*/
void rb_rotate_right(rb_tree* t, rb_node* r)
{
	rb_node* p = r->left;
	rb_node* parent = r->parent;

	if (p == NULL)
	{
		fprintf(stderr, "Invalid right rotation on node %d\n", r->key);
		exit(1);
	}

	// relink p->right to r->left
	r->left = p->right;

	if (p->right != NULL)
		p->right->parent = r;

	// relink r to p->right
	p->right = r;
	r->parent = p;

	// link p to parent
	p->parent = parent;

	if (parent != NULL)
	{
		if (parent->left == r)
			parent->left = p;

		else if (parent->right == r)
			parent->right = p;
	}

	else
		t->root = p;

	return;
}

/*
	  r
	 / \
	1   p
	   / \
	  2   3

	  	p
	   / \
	  r   3
	 / \
	1   2

*/

void rb_rotate_left(rb_tree* t, rb_node* r)
{
	rb_node* p = r->right;
	rb_node* parent = r->parent;

	if (p == NULL)
	{
		fprintf(stderr, "Invalid left rotation on node %d\n", r->key);
	}

	// relink p->left to r->right
	r->right = p->left;

	if (p->left != NULL)
		p->left->parent = r;

	// relink r to p->left
	p->left = r;
	r->parent = p;

	p->parent = parent;

	if (parent != NULL)
	{
		if (parent->left == r)
			parent->left = p;

		else if (parent->right == r)
			parent->right = p;
	}

	else
		t->root = p;

	return;
}

void rb_rebalance(rb_tree* t, rb_node* n)
{
	// case 1: n is the root
	//
	// simply make the root black

	if (n == t->root)
	{
		n->color = BLACK;
		return;
	}

	// case 2: n has a black parent
	//
	// nothing to do, since the NULL children
	// are considered black
	// note: n guaranteed to have a parent
	// (since it isn't the root)

	rb_node* parent = n->parent;

	if (parent->color == BLACK)
		return;

	// case 3: n has a red parent and uncle
	//
	// color parent and uncle black and color
	// grandparent red, then rebalance from
	// the grandparent
	// note: grandparent is guaranteed to exist
	// or the parent would otherwise be black

	rb_node* grandparent = parent->parent;
	rb_node* uncle;

	if (parent == grandparent->left)
		uncle = grandparent->right;

	else
		uncle = grandparent->left;

	if (uncle != NULL && uncle->color == RED)
	{
		parent->color = BLACK;
		uncle->color = BLACK;
		grandparent->color = RED;
		rb_rebalance(t, grandparent);
		return;
	}

	// case 4: n has a red parent and black uncle
	//
	// objective: do a left rotation on the grandparent
	// then color it red and the new grandparent black
	// obstacle: if n is on the "inside" of the
	// grandparent's subtree, after rotation the red
	// grandparent will have a red child
	//
	// subcase 4.1: n is on the "inside" of the grand-
	// parent's subtree
	// solution: rotate the parent and make n the new
	// parent

	if (n == parent->left && parent == grandparent->right)
	{
		rb_rotate_right(t, parent);
		
		// switch n and parent
		rb_node* tmp = n;
		n = parent;
		parent = tmp;
	}

	else if (n == parent->right && parent == grandparent->left)
	{
		rb_rotate_left(t, parent);

		// switch n and parent
		rb_node* tmp = n;
		n = parent;
		parent = tmp;
	}

	// subcase 4.2: n and parent are on the "outside"
	// of the grandparent's subtree
	// solution: rotate the parent to the grandparent's
	// position, then color the parent black and the
	// grandparent red

	if (parent == grandparent->left)
		rb_rotate_right(t, grandparent);

	else
		rb_rotate_left(t, grandparent);

	parent->color = BLACK;
	grandparent->color = RED;

	return;
}

// returns pointer to new node, if inserted successfully,
// or NULL otherwise
rb_node* rb_insert_rec(rb_node* root, int key)
{
	if (root == NULL)
		return NULL;

	if (key > root->key)
	{
		if (root->right == NULL)
		{
			rb_node* new = rb_node_new(key);
			root->right = new;
			new->parent = root;
			return new;
		}

		else
			return rb_insert_rec(root->right, key);
	}

	else if (key < root->key)
	{
		if (root->left == NULL)
		{
			rb_node* new = rb_node_new(key);
			root->left = new;
			new->parent = root;
			return new;
		}

		else
			return rb_insert_rec(root->left, key);
	}

	// for when inserting a repeated node
	else
	{
		root->count++;
		return NULL;
	}

	return NULL;
}

void rb_insert(rb_tree* t, int key)
{
	rb_node* new = rb_insert_rec(t->root, key);

	// for when attempting to insert a repeated node
	// (which does't get inserted at all)
	if (new == NULL)
		return;

	rb_rebalance(t, new);
	
	return;
}

rb_node* rb_find_rec(rb_node* root, int key)
{
	if (root == NULL)
		return NULL;

	if (key > root->key)
		return rb_find_rec(root->right, key);

	else if (key < root->key)
		return rb_find_rec(root->left, key);

	else
		return root;
}

rb_node* rb_find(rb_tree* t, int key)
{
	return rb_find_rec(t->root, key);
}

void rb_in_order_rec(rb_node* n, void (*rb_node_func)(rb_node* n, void* params), void* params)
{
	if (n == NULL)
		return;

	rb_in_order_rec(n->left, rb_node_func, params);
	rb_node_func(n, params);
	rb_in_order_rec(n->right, rb_node_func, params);
}

void rb_in_order(rb_tree* t, void (*rb_node_func)(rb_node* n, void* params), void* params)
{
	rb_in_order_rec(t->root, rb_node_func, params);
}
