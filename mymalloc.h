#pragma once

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
void myrealloc(void *ptr, size_t size);

/**
 * @brief Free a block of memory
 *
 * @param ptr Pointer to the block to free
 * @return void
 */
void myfree(void *ptr);
