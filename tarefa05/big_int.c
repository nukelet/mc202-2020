#include "big_int.h"

void handle_no_memory_error()
{
	fprintf(stderr, "INSUFFICIENT MEMORY");
	exit(1);
}

big_int* create_big_int(int ArgDigit)
{
	node *pFirstDigit = malloc(sizeof(*pFirstDigit));

	if (pFirstDigit == NULL)
		handle_no_memory_error();

	pFirstDigit->digit = ArgDigit;
	pFirstDigit->previous = NULL;
	pFirstDigit->next = NULL;

	big_int *pBigInt = malloc(sizeof(*pBigInt));

	if (pBigInt == NULL)
		handle_no_memory_error();

	pBigInt->first = pFirstDigit;
	pBigInt->last = pFirstDigit;

	return pBigInt;

}

void destroy_big_int(big_int *pBigInt)
{
	node *it, *next = NULL;

	for (it = pBigInt->first; it != pBigInt->last; it = next)
	{
		next = it->next;
		free(it);
	}

	// destroys the last element
	free(it);

	// destroys the big_int object itself
	free(pBigInt);

	return;
}

void append_to_last(big_int *pBigInt, int ArgDigit)
{
	node *pNewTail = malloc(sizeof(*pNewTail));

	if (pNewTail == NULL)
		handle_no_memory_error();

	pNewTail->digit = ArgDigit;

	// attach new tail
	pBigInt->last->next = pNewTail;
	
	// link new tail to previous element
	pNewTail->previous = pBigInt->last;
	pNewTail->next = NULL;

	// update pointer to tail
	pBigInt->last = pNewTail;

	return;
}

void pop_last(big_int *pBigInt)
{
	node *tail = pBigInt->last;

	pBigInt->last = tail->previous;
	tail->previous->next = NULL;

	free(tail);

	return;
}