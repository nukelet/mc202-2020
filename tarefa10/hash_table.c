#include "hash_table.h"
#include "safe_allocators.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

list* list_new(char* item)
{
	list* p = safe_malloc(sizeof(*p));

	p->item = item;
	p->next = NULL;

	return p;
}

void list_destroy(list* t)
{
	if (t == NULL)
		return;

	list* next;

	while (t != NULL)
	{
		next = t->next;

		free(t->item);
		free(t);

		t = next;
	}
}

// just runs through the entire list instead
// of doing bookkeeping, since there aren't
// many collisions anyway
void list_append(list* t, char* item)
{
	// go to last element
	while (t->next != NULL)
		t = t->next;

	list* p = list_new(item);

	// append new node
	t->next = p;
}

hash_table* ht_new(size_t size, uint32_t (*hash_func)(char* item))
{
	hash_table* t = safe_malloc(sizeof(*t));

	t->table_size = size;
	t->hash_func = hash_func;

	t->table = safe_calloc(size, sizeof(list*));

	return t;
}

void ht_destroy(hash_table* t)
{
	for (int i = 0; i < t->table_size; i++)
	{
		list_destroy(t->table[i]);
	}

	free(t);
}

void ht_insert(hash_table* t, char* item)
{
	uint32_t hash = t->hash_func(item);

	if (hash > t->table_size)
	{
		// mostly for debugging purposes
		fprintf(stderr, "Hash larger than table size!\n");
		exit(1);
	}

	if (t->table[hash] == NULL)
		t->table[hash] = list_new(item);

	else
		list_append(t->table[hash], item);
}

int ht_lookup(hash_table* t, char* item)
{
	uint32_t hash = t->hash_func(item);

	if (t->table[hash] == NULL)
		return 0;

	for (list* it = t->table[hash]; it != NULL; it = it->next)
		if (strcmp(it->item, item) == 0)
			return 1;

	return 0;
}