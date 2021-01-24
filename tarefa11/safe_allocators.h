#ifndef SAFE_MALLOC
#define SAFE_MALLOC

#include <stddef.h> // size_t

// very simple wrapper around malloc()
//
// forwards the pointer returned by malloc()
// or prints an error to stderr and exits if
// malloc() returns NULL
void* safe_malloc(size_t size);

// same thing, but with calloc()
void* safe_calloc(size_t nitems, size_t size);

#endif