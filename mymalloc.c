#include "mymalloc.h"

void mymalloc_init()
{
    return;
}

void *mymalloc(size_t size)
{
    return NULL;
}

void *mycalloc(size_t nmemb, size_t size)
{
    void *ptr = mymalloc(nmemb * size);
    if (ptr != NULL)
    {
        memset(ptr, 0, nmemb * size);
    }
    return ptr;
}

void *myrealloc(void *ptr, size_t size)
{
    return NULL;
}

void myfree(void *ptr)
{
    return;
}
