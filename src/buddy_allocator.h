#pragma once

#include "bitset.h"

#define BUDDY_OCCUPIED 0
#define BUDDY_FREE 1

typedef struct
{
    bitset_t *bitset;
    void *data;
    size_t levels;
    size_t min_bucket_size;
} buddy_allocator_t;

/**
 * @brief Initializes buddy allocator
 *
 * @param allocator The allocator to initialize.
 * @param bitset The bitset to use for the allocator.
 * @param data The data buffer to use for the allocator.
 * @param levels The number of levels in the allocator.
 * @param min_bucket_size The minimum bucket size in the allocator.
 * @return void
 */
void buddy_allocator_init(buddy_allocator_t *allocator, bitset_t *bitset, void *data, size_t levels, size_t min_bucket_size);

/**
 * @brief Allocates a block of memory from the buddy allocator.
 *
 * @param allocator The allocator to allocate from.
 * @param size The size of the block to allocate.
 * @return void* The pointer to the allocated block.
 */
void *buddy_allocator_malloc(buddy_allocator_t *allocator, size_t size);

/**
 * @brief Frees a block of memory from the buddy allocator.
 *
 * @param allocator The allocator to free from.
 * @param ptr The pointer to the block to free.
 * @return void
 */
void buddy_allocator_free(buddy_allocator_t *allocator, void *ptr);
