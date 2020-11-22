#include <stdlib.h>
#include <stdio.h>

void handle_memory_error(void* ptr)
{
	if (ptr == NULL)
	{
		fprintf(stderr, "Insufficient memory; exiting...\n");
		exit(1);
	}
}