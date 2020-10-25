#ifndef BIG_INT
#define BIG_INT

#include <stdlib.h>
#include <stdio.h>

/*
	big_int is a linked list of digits
*/

// link is a pointer to a node
// typedef struct node_* p_node;

typedef struct node_
{
	int digit;
	struct node_ *previous, *next;
	// TODO: does the list really need to be doubly linked?
} node;

typedef struct big_int_
{
	// the linked list starts with the least significant digit
	// and ends with the most significant digit

	node* first;
	node* last; 
} big_int;


void handle_memory_error(void);

// returns a pointer to the big_int object
big_int* create_big_int(int ArgDigit);

// deallocates a big_int object
void destroy_big_int(big_int *pBigInt);

void append_to_last(big_int *pBigInt, int ArgDigit);
void pop_last(big_int *pBigInt);


// arithmetic operations

big_int* add(big_int* BigInt_A, big_int* BigInt_B);
big_int* subtract(big_int* BigInt_A, big_int* BigInt_B);
big_int* multiply(big_int* BigInt_A, big_int* BigInt_B);
big_int* divide(big_int* BigInt_A, big_int* BigInt_B);

// dumps a big_int object into a buffer to be printed to stdout
/*
	note that the maximum number of digits of a big_int object,
	according to the problem constraints, is 1e24 * 1e24 = 1e48;
	for that reason, the buffer has size 50
*/

#endif