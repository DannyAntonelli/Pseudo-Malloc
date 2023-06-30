#include <string.h>
#include <unistd.h>

#include "bitset.h"
#include "buddy_allocator.h"
#include "logging.h"
#include "mmap_allocator.h"
#include "mymalloc.h"

buddy_allocator_t buddy_allocator;
uint8_t bitset_buffer[BITSET_SIZE];
uint8_t data_buffer[BUDDY_MEMORY_LIMIT];
bitset_t bitset;

bool is_buddy_allocated(void *ptr)
{
    return ptr >= (void *)data_buffer && ptr < (void *)(data_buffer + BUDDY_MEMORY_LIMIT);
}

void mymalloc_init()
{
    bitset_init(&bitset, bitset_buffer, sizeof(bitset_buffer));
    bitset_set(&bitset, 0, BUDDY_FREE);
    buddy_allocator_init(&buddy_allocator, &bitset, (void *)data_buffer, BUDDY_MAX_LEVELS, BUDDY_MIN_BUCKET_SIZE);
}

void *mymalloc(size_t size)
{
    if (size < (size_t)getpagesize() / 4U)
    {
        LOG(LOG_LEVEL_INFO, "Allocating buddy memory: %zu bytes", size);
        return buddy_allocator_malloc(&buddy_allocator, size);
    }
    else
    {
        LOG(LOG_LEVEL_INFO, "Allocating mmap memory: %zu bytes", size);
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
    size_t old_size;
    if (is_buddy_allocated(ptr))
    {
        LOG(LOG_LEVEL_INFO, "Reallocating buddy memory: %zu bytes", size);
        old_size = buddy_allocator_get_allocated_size(&buddy_allocator, ptr);
    }
    else
    {
        LOG(LOG_LEVEL_INFO, "Reallocating mmap memory: %zu bytes", size);
        old_size = mmap_get_allocated_size(ptr);
    }
    void *new_ptr = mymalloc(size);
    size_t copy_size = old_size < size ? old_size : size;
    if (new_ptr != NULL)
    {
        memcpy(new_ptr, ptr, copy_size);
        myfree(ptr);
    }
    return new_ptr;
}

void myfree(void *ptr)
{
    if (is_buddy_allocated(ptr))
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
