#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include <stddef.h> // for size_t

typedef struct Item_ 
{
	char name[16];
	double rating;
	int origin_x, origin_y;
	int destination_x, destination_y;
} Item;

Item* item_new(char* name, double rating,
	int origin_x, int origin_y, int destination_x, int destination_y);

typedef struct priority_queue_
{
	// the heap is implemented as an array
	// of pointers to Item objects
	Item** heap;

	// for Item* t, let Item* t_parent; 
	// the heap is organized in a way that
	// enforces that compare(t, t_parent) == 1
	// note: the function must make sure that
	// compare(t, t) == 1
	int (*compare)(Item* a, Item* b);

	size_t capacity;
	size_t size;
} priority_queue;

priority_queue* pq_new(int capacity, int (*compare)(Item* a, Item* b));
void pq_destroy(priority_queue* p);

void pq_insert(priority_queue* p, Item* t);
Item* pq_delete(priority_queue* p, int n);

Item* pq_pop(priority_queue* p);

int pq_is_empty(priority_queue* p);
int pq_find_by_name(priority_queue* p, char* str);

#endif