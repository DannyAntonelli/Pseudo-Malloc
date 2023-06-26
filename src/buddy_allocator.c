#include "buddy_allocator.h"

void buddy_allocator_init(buddy_allocator_t *allocator, bitset_t *bitset, void *data, size_t levels, size_t min_bucket_size)
{
    allocator->bitset = bitset;
    allocator->data = data;
    allocator->levels = levels;
    allocator->min_bucket_size = min_bucket_size;
}

void *buddy_allocator_malloc(buddy_allocator_t *allocator, size_t size)
{
    return NULL;
}

void buddy_allocator_free(buddy_allocator_t *allocator, void *ptr)
{
    return;
}
