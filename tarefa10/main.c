#include "hash_table.h"
#include "safe_allocators.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>

// this is the hash table size
//
// there are at most 100 words in the table,
// so this table size keeps the load factor
// under 10%
// plus, it's a prime (the smallest one \geq 1000)
#define M 1009

// slightly modified version of a very simple and 
// relatively well-known hash function that generates
// a sparse table while also being very fast
//
// refer to http://www.cse.yorku.ca/~oz/hash.html
uint32_t djb2_hash(char* str)
{
	uint32_t hash = 5381;

	for (int i = 0; i < strlen(str); i++)
	{
		hash = (((hash << 5) + hash) + str[i]) % M;
	}

	return hash;
}

int main(int argc, char const *argv[])
{
	int num_words, num_lookups;
	scanf("%d %d", &num_words, &num_lookups);

	hash_table* t = ht_new(M, &djb2_hash);

	for (int i = 0; i < num_words; i++)
	{
		char* str = safe_malloc(30*sizeof(char));
		scanf("%s", str);

		ht_insert(t, str);
	}

	// for (size_t i = 0; i < t->table_size; i++)
	// {
	// 	if (t->table[i] == NULL)
	// 		continue;

	// 	printf("In hash %zu:\n", i);

	// 	for (list* it = t->table[i]; it != NULL; it = it->next)
	// 		printf("%s\n", it->item);
	// }

	for (int i = 0; i < num_lookups; i++)
	{
		char str[30]; scanf("%s", str);

		if (ht_lookup(t, str) == 1)
		{
			printf("verde\n");
			continue;
		}

		int found = 0;

		char typo[30];
		int len = strlen(str);

		// printf("\nsearching for a single added letter\n\n");

		// checks if only one letter has been added
		for (int i = 0; i < len; i++)
		{
			strcpy(typo, str);
			typo[i] = '\0';
			strcat(typo, str+i+1);

			// printf("looking up: %s\n", typo);

			if (ht_lookup(t, typo) == 1)
			{
				printf("amarelo\n");
				found = 1;
				break;
			}
		}

		// printf("\nsearching for a single changed letter\n\n");

		if (found)
			continue;

		// checks if a single letter has been changed
		for (int i = 0; i < len; i++)
		{
			strcpy(typo, str);
			char c = str[i];

			for (int j = 0; j < 26; j++)
			{
				typo[i] = 'a' + j;

				// printf("looking up: %s\n", typo);
				if (ht_lookup(t, typo) == 1)
				{
					printf("amarelo\n");
					found = 1;
					break;
				}
			}

			if (found)
				break;
			
			typo[i] = c;
		}

		if (found)
			continue;

		// printf("\nsearching for a single missing letter\n\n");

		// checks if a single letter has been removed
		for (int i = 0; i < len+1; i++)
		{
			// shifts everything after str[i] (included) to the right
			// in order to insert a character at the index i
			strcpy(typo, str);
			typo[i+1] = '\0';
			strcat(typo, str+i);

			for (int j = 0; j < 26; j++)
			{
				typo[i] = 'a' + j;

				// printf("looking up: %s\n", typo);

				if (ht_lookup(t, typo) == 1)
				{
					printf("amarelo\n");
					found = 1;
					break;
				}
			}

			if (found)
				break;
		}

		if (found)
			continue;

		printf("vermelho\n");
	}

	ht_destroy(t);

	return 0;
}