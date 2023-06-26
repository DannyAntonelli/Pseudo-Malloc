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
