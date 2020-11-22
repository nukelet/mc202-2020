#ifndef RB_TREE
#define RB_TREE

typedef enum rb_color_
{
	RED,
	BLACK
} rb_color;

typedef struct rb_node_
{
	int key;
	int count;
	rb_color color;

	struct rb_node_ *left;
	struct rb_node_ *right;
	struct rb_node_ *parent; 
} rb_node;

typedef struct rb_tree_
{
	rb_node* root;
} rb_tree;

rb_tree* rb_new(int key);
void rb_destroy(rb_tree* t);

void rb_insert(rb_tree* t, int key);

rb_node* rb_find(rb_tree* t, int key);
void rb_in_order(rb_tree* t, void (*rb_node_func)(rb_node* n, void* params), void* params);

#endif