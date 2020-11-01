#ifndef BIG_INT
#define BIG_INT

#include <stdlib.h>
#include <stdio.h>

/*
	Header file declaring the big_int object.

	A big_int object is a (doubly) linked list of decimal digits that is IN REVERSE:
	it starts with a dummy node and is followed by the LEAST SIGNIFICANT DIGIT. It is
	followed by the rest of the digits and then by a sequence of 0's until the position
	defined by MAX_BIG_INT_SIZE.
*/

// macro for the max number of decimal places
// note: has this value because, given the problem constraints,
// n <= 1e24, so the largest possible big_int to be manipulated
// is 1e24 * 1e24 = 1e48, which has 48 digits.
#define MAX_BIG_INT_SIZE 48


// struct definition of the linked list nodes
typedef struct node_
{
	int digit;
	struct node_ *previous, *next;
} node;

// the linked list itself is the set of the first and the last
// elements of the list
typedef struct big_int_
{
	node* first;
	node* last; 
} big_int;

/*
	MEMORY-RELATED FUNCTIONS
*/

/*
	function: handle_memory_error(void)

	PARAMETERS:
	none

	RETURNS:
	none

	DESCRIPTION:
	Very simple error handling function; outputs an error message to stderr
	indicating that there was not enough memory to allocate an object.
*/

void handle_memory_error(void);


/*
	function: create_big_int(void)

	PARAMETERS:
	none

	RETURNS:
	big_int* NewBigInt, a pointer to a new big_int object

	DESCRIPTION:
	Allocates a new big_int object (consisting only of a dummy node
	that has previous = NULL and next = NULL) and returns a pointer to it.
*/

big_int* create_big_int(void);

/*
	function: destroy_big_int(big_int *pBigInt)

	PARAMETERS:
	big_int* pBigInt, a pointer to the big_int object to be destroyed

	RETURNS:
	none

	DESCRIPTION:
	Deallocates a big_int object.
*/
void destroy_big_int(big_int* pBigInt);


/*
	function: get_copy_big_int(big_int* source)

	PARAMETERS:
	big_int* source, the big_int object to be copied

	RETURNS:
	big_int* copy, a copy of the received big_int object

	DESCRIPTION:
	Creates a copy of a big_int object, returning a pointer to it.
*/
big_int* get_copy_big_int(big_int* source);


/*
	function: append_to_last(big_int *pBigInt, int ArgDigit)

	PARAMETERS:
	big_int* pBigInt, big_int to be modified
	int ArgDigit, digit to be inserted into the big_int object

	RETURNS:
	none

	DESCRIPTION:
	Appends a digit to the end of the linked list (attaching a digit
	to the left of the most significant digit).
*/
void append_to_last(big_int* pBigInt, int ArgDigit);

/*
	function: append_to_head(big_int *pBigInt, int ArgDigit)

	PARAMETERS:
	big_int* pBigInt, big_int to be modified
	int ArgDigit, digit to be inserted into the big_int object

	RETURNS:
	none

	DESCRIPTION:
	Appends a digit to the beginning of the linked list (attaching a digit
	to the right of the most significant digit). The digit is inserted after
	the dummy head.
*/

void append_to_head(big_int* pBigInt, int ArgDigit);


/*
	function: pop_last(big_int *pBigInt)

	PARAMETERS:
	big_int* pBigInt, big_int to be modified

	RETURNS:
	none

	DESCRIPTION:
	Deletes the last element in the linked list (i.e. the leftmost digit
	of the big_int object).
*/

void pop_last(big_int *pBigInt);


/*
	ARITHMETIC OPERATIONS
*/


/*
	function: max_big_int(big_int* A, big_int* B)

	PARAMETERS:
	big_int* A, first big_int to be compared
	big_int* B,	second big_int to be compared

	RETURNS:
	big_int* max,	a pointer to the largest big_int

	DESCRIPTION:
	Compares and returns a pointer to the largest big_int object.
	Returns a pointer to the first argument if both numbers are equal.
*/

big_int* max_big_int(big_int* A, big_int* B);


/*
	function: add(big_int* A, big_int* B)

	PARAMETERS:
	big_int* A
	big_int* B

	RETURNS:
	big_int* sum,	a pointer to a big_int object containing the
					sum of A and B

	DESCRIPTION:
	Calculates the sum of A and B and dumps it into a new big_int,
	returning a pointer to it.
*/

big_int* add(big_int* A, big_int* B);


/*
	function: subtract(big_int* A, big_int* B)

	PARAMETERS:
	big_int* A
	big_int* B

	RETURNS:
	big_int* difference,	a pointer to a big_int object containing the
							(unsigned) difference of A and B

	DESCRIPTION:
	Calculates the (unsigned) difference of A and B and dumps it into a 
	new big_int, returning a pointer to it.
*/

big_int* subtract(big_int* BigInt_A, big_int* BigInt_B);


/*
	function: multiply(big_int* A, big_int* B)

	PARAMETERS:
	big_int* A
	big_int* B

	RETURNS:
	big_int* product,	a pointer to a big_int object containing the
						product of A and B

	DESCRIPTION:
	Calculates the product of A and B and dumps it into a 
	new big_int, returning a pointer to it.
*/

big_int* multiply(big_int* BigInt_A, big_int* BigInt_B);


/*
	function: divide(big_int* A, big_int* B)

	PARAMETERS:
	big_int* A
	big_int* B

	RETURNS:
	big_int* quotient,	a pointer to a big_int object containing the
						quotient of A and B

	DESCRIPTION:
	Calculates the quotient of A and B and dumps it into a 
	new big_int, returning a pointer to it. 
	note: does NOT handle division by zero
*/

big_int* divide(big_int* BigInt_A, big_int* BigInt_B);

// dumps a big_int object into a buffer to be printed to stdout
// TODO: make sure that the buffer is large enough to store the
// big_int object
/*
	note that the maximum number of digits of a big_int object,
	according to the problem constraints, is 1e24 * 1e24 = 1e48;
	for that reason, it is assumed that the buffer has at least
	size 49
*/

/*
	INPUT/OUTPUT FUNCTIONS
*/

/*
	function: big_int_to_string(big_int* BigInt, char* buffer, int buffer_size)

	PARAMETERS:
	big_int* BigInt,	big_int number to be converted to string
	char* buffer,		string in which to dump the big_int
	int buffer_size		buffer size

	RETURNS:
	none

	DESCRIPTION:
	Converts a big_int object into a string, dumping each 
	character into the buffer.
	note: char buffer ends with the null terminator ('\0')
*/

void big_int_to_string(big_int* BigInt, char* buffer, int buffer_size);


/*
	function: string_to_big_int(char* buffer, int buffer_size, big_int* BigInt)

	PARAMETERS:
	char* buffer,		buffer containing the digits of the number
						to be converted into a big_int
	int buffer_size		buffer size
	big_int* BigInt,	big_int number in which to dump the contents
						of the buffer

	RETURNS:
	none

	DESCRIPTION:
	Converts a string into a big_int object, dumping the
	contents of the buffer into a big_int.

	note: expects an empty (i.e. containing only a dummy head) big_int
	note: expects the string in the buffer to end with the null terminator ('\0')
*/

void string_to_big_int(char* buffer, int buffer_size, big_int* BigInt);


/*
	function: print_big_int(big_int* BigInt)

	PARAMETERS:
	big_int* BigInt,	big_int number to be printed

	RETURNS:
	none

	DESCRIPTION:
	Prints a big_int to stdin.
*/

void print_big_int(big_int* BigInt);

#endif