#include "safe_allocators.h"
#include <stdio.h>	// fprintf()
#include <stdlib.h>	// malloc()

void* safe_malloc(size_t size)
{
	void* p = malloc(size);

	if (p == NULL)
	{
		fprintf(stderr, "Insufficient memory; exiting...\n");
		exit(1);
	}

	else
		return p;
}

void* safe_calloc(size_t nitems, size_t size)
{
	void* p = calloc(nitems, size);

	if (p == NULL)
	{
		fprintf(stderr, "Insufficient memory; exiting...\n");
		exit(1);
	}

	else
		return p;	
}