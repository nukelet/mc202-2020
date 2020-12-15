#ifndef HASH_TABLE
#define HASH_TABLE

#include <stddef.h> // size_t
#include <stdint.h> // uint32_t

// note: expects the string item to
// have been malloc'd
typedef struct list_
{
	char* item;
	struct list_* next;
} list;

list* list_new(char* item);
void list_destroy(list* t);
void list_append(list* t, char* item);

typedef struct hash_table_
{
	list** table;

	size_t table_size;

	// the hash function itself
	uint32_t (*hash_func)(char* item);
} hash_table;

hash_table* ht_new(size_t size, uint32_t (*hash_func)(char* item));
void ht_destroy(hash_table* t);

void ht_insert(hash_table* t, char* item);

// returns 1 when the item is in the table,
// and 0 otherwise
int ht_lookup(hash_table* t, char* item);

#endif