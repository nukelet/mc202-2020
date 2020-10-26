#include "big_int.h"

void handle_no_memory_error(void)
{
	fprintf(stderr, "INSUFFICIENT MEMORY");
	exit(1);
}

big_int* create_big_int(void)
{
	node *pFirstDigit = malloc(sizeof(*pFirstDigit));

	if (pFirstDigit == NULL)
		handle_no_memory_error();

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

// big_int* add(big_int* BigInt_A, big_int* BigInt_B)
// {
// 	int carry;

// }

void big_int_to_string(big_int* BigInt, char* buffer)
{
	node *it;
	int i;

	for (it = BigInt->last, i = 0; it != BigInt->first; it = it->previous, i++)
	{
		buffer[i] = (char) it->digit + 48;
	}

	// append \0 to the end
	buffer[i] = '\0';
}

void string_to_big_int(char* buffer, big_int* BigInt)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
		append_to_last(BigInt, (int) buffer[i] - 48);
}