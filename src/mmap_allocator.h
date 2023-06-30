#include <stdlib.h>

/**
 * @brief Allocate memory using mmap
 *
 * @param size Size of memory to allocate
 * @return void* Pointer to allocated memory
 */
void *mmap_malloc(size_t size);

/**
 * @brief Free memory allocated using mmap
 *
 * @param ptr Pointer to memory to free
 * @return void
 */
void mmap_free(void *ptr);

/**
 * @brief Get the allocated size of a block of memory
 *
 * @param ptr Pointer to memory to get the size of
 * @return size_t Size of memory
 */
size_t mmap_get_allocated_size(void *ptr);
