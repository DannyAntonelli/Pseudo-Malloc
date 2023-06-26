#pragma once

#include "bitset.h"

typedef struct
{
    bitset_t *bitset;
    void *data;
    size_t levels;
    size_t min_bucket_size;
} buddy_allocator_t;

void buddy_allocator_init(buddy_allocator_t *allocator, bitset_t *bitset, void *data, size_t levels, size_t min_bucket_size);

void *buddy_allocator_malloc(buddy_allocator_t *allocator, size_t size);

void buddy_allocator_free(buddy_allocator_t *allocator, void *ptr);
