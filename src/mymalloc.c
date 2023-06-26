#include <string.h>
#include <unistd.h>

#include "bitset.h"
#include "buddy_allocator.h"
#include "logging.h"
#include "mmap_allocator.h"
#include "mymalloc.h"

buddy_allocator_t buddy_allocator;
uint8_t bitmap_buffer[((1 << BUDDY_MAX_LEVELS) - 6) / 8];
uint8_t data_buffer[BUDDY_MEMORY_LIMIT];

void mymalloc_init()
{
    bitset_t bitset;
    int num_bits = (1 << BUDDY_MAX_LEVELS) - 1;
    bitset_init(&bitset, num_bits, bitmap_buffer, sizeof(bitmap_buffer));
    buddy_allocator_init(&buddy_allocator, &bitset, (void *)data_buffer, BUDDY_MAX_LEVELS, BUDDY_MIN_BUCKET_SIZE);
}

void *mymalloc(size_t size)
{
    if (size < (size_t)getpagesize() / 4U)
    {
        LOG(LOG_LEVEL_INFO, "Allocating buddy memory %zu", size);
        return buddy_allocator_malloc(&buddy_allocator, size);
    }
    else
    {
        LOG(LOG_LEVEL_INFO, "Allocating mmap memory %zu", size);
        return mmap_malloc(size);
    }
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
    if (ptr >= (void *)data_buffer && ptr < (void *)(data_buffer + BUDDY_MEMORY_LIMIT))
    {
        LOG(LOG_LEVEL_INFO, "Freeing buddy memory %p", ptr);
        buddy_allocator_free(&buddy_allocator, ptr);
    }
    else
    {
        LOG(LOG_LEVEL_INFO, "Freeing mmap memory %p", ptr);
        mmap_free(ptr);
    }
}
