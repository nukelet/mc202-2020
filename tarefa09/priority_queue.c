#include "priority_queue.h"
#include "handle_memory_error.h"
#include "string.h"

#include <stddef.h> // for NULL
#include <stdlib.h> // for malloc() and calloc()
#include <stdio.h> // for fprintf()

/* Constructors and destructors */

Item* item_new(char* name, double rating,
	int origin_x, int origin_y, int destination_x, int destination_y)
{
	Item* p = malloc(sizeof(*p));

	strcpy(p->name, name);
	p->rating = rating;
	p->origin_x = origin_x; p->origin_y = origin_y;
	p->destination_x = destination_x; p->destination_y = destination_y;

	return p;
}

priority_queue* pq_new(int capacity, int (*compare)(Item* a, Item* b))
{
	priority_queue* p = malloc(sizeof(*p));
	handle_memory_error(p);

	p->heap = calloc(capacity, sizeof(Item*));
	handle_memory_error(p->heap);

	p->size = 0;
	p->capacity = capacity;
	p->compare = compare;

	return p;
}

void pq_destroy(priority_queue* p)
{
	for (int i = 0; i < p->size; i++)
	{
		free(p->heap[i]);
	}

	free(p->heap);
	free(p);
}

/* Auxiliary heap functions */

void swap(Item** a, Item** b)
{
	Item* tmp = *a;
	*a = *b;
	*b = tmp;
}

int get_parent(int n)
{
	return (int) (n-1)/2;
}

int get_left_child(int n)
{
	return 2*n + 1;
}

int get_right_child(int n)
{
	return 2*n + 2;
}

void sift_up(priority_queue* p, int n)
{
	int parent;

	while (1)
	{
		parent = get_parent(n);

		// exits loop when heap property checks out
		if (p->compare(p->heap[n], p->heap[parent]) == 1)
			break;

		swap(&p->heap[n], &p->heap[parent]);
		n = parent; parent = get_parent(n);
	}
}

void sift_down(priority_queue* p, int n)
{
	int left, right;

	while (1)
	{
		// the ternary operator expressions make sure
		// never to check an out of bounds index
		left = get_left_child(n);
		left = left < p->size ? left : n;
		
		right = get_right_child(n);
		right = right < p->size ? right : n;
		
		// exits loop when heap property checks out
		if (p->compare(p->heap[left], p->heap[n]) == 1 &&
			p->compare(p->heap[right], p->heap[n]) == 1)
		{
			break;
		}

		// swaps heap[n] with one of its children
		if (p->compare(p->heap[left], p->heap[right]) == 1)
		{
			swap(&p->heap[right], &p->heap[n]);
			n = right;
		}
		
		else
		{
			swap(&p->heap[left], &p->heap[n]);
			n = left;
		}
	}
}


/* Other header functions */

void pq_insert(priority_queue* p, Item* t)
{
	// this is here mostly for debugging
	if (p->size >= p->capacity)
	{
		fprintf(stderr, "Heap overflow; exiting...\n");
		exit(1);
	}

	int n = p->size;
	p->heap[n] = t;

	p->size++;

	sift_up(p, n);
}

Item* pq_delete(priority_queue* p, int n)
{
	if (n > p->size || n < 0)
	{
		fprintf(stderr, "Illegal attempt to delete out of bounds item; exiting...\n");
		exit(1);
	}

	Item* tmp = p->heap[n];

	int last = p->size - 1;
	swap(&p->heap[last], &p->heap[n]);
	p->size--;

	p->heap[last] = NULL;

	if (n == last)
		return tmp;

	sift_down(p, n);
	sift_up(p, n);

	return tmp;
}

Item* pq_pop(priority_queue* p)
{
	Item* tmp = p->heap[0];

	int last = p->size - 1;
	swap(&p->heap[last], &p->heap[0]);
	p->size--;

	p->heap[last] = NULL;
	
	if (p->size == 0)
		return tmp;

	sift_down(p, 0);

	return tmp;
}

int pq_is_empty(priority_queue* p)
{
	if (p->size == 0)
		return 1;

	else
		return 0;
}

int pq_find_by_name(priority_queue* p, char* str)
{
	for (int i = 0; i < p->size; i++)
	{
		if (strcmp(p->heap[i]->name, str) == 0)
			return i;
	}

	return -1;
}