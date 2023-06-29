#pragma once

#include <stdlib.h>

#define BUDDY_MEMORY_LIMIT (1 << 20)
#define BUDDY_MAX_LEVELS 10
#define BUDDY_MIN_BUCKET_SIZE (BUDDY_MEMORY_LIMIT >> (BUDDY_MAX_LEVELS - 1))
#define NUMBER_OF_BUDDIES (1 << BUDDY_MAX_LEVELS) - 1
#define BITSET_SIZE (NUMBER_OF_BUDDIES + 7) >> 3

/**
 * @brief Initialize the memory allocator
 *
 * @return void
 */
void mymalloc_init();

/**
 * @brief Allocate a block of memory
 *
 * @param size Size of the block to allocate
 * @return void* Pointer to the allocated block
 */
void *mymalloc(size_t size);

/**
 * @brief Allocate a block of memory and set it to zero
 *
 * @param nmemb Number of elements
 * @param size Size of each element
 * @return void* Pointer to the allocated block
 */
void *mycalloc(size_t nmemb, size_t size);

/**
 * @brief Reallocate a block of memory
 *
 * @param ptr Pointer to the block to reallocate
 * @param size New size of the block
 * @return void* Pointer to the reallocated block
 */
void *myrealloc(void *ptr, size_t size);

/**
 * @brief Free a block of memory
 *
 * @param ptr Pointer to the block to free
 * @return void
 */
void myfree(void *ptr);
