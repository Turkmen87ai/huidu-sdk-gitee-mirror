#include "posixPortMemory.h"
#include <stdlib.h>
#include <stdio.h>

void *hdmalloc(uint32_t size)
{
    return malloc(size);
}

void *hdrealloc(void *ptr, uint32_t size)
{
    return realloc(ptr, size);
}

void hdfree(void *ptr)
{
    free(ptr);
}
