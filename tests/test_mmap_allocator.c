#include <stdio.h>

#include "mmap_allocator.h"
#include "unittest.h"

/**
 * @brief Test mmap_malloc
 *
 * @return int 0 if successful, 1 otherwise.
 */
int test_malloc()
{
    void *ptr = mmap_malloc(10);
    mmap_free(ptr);
    return ptr == NULL;
}

/**
 * @brief Test get_allocated_size
 *
 * @return int 0 if successful, 1 otherwise.
 */
int test_get_allocated_size()
{
    void *ptr = mmap_malloc(10);
    size_t size = mmap_get_allocated_size(ptr);
    mmap_free(ptr);
    return size != 10;
}

int main()
{
    TEST(test_malloc);
    TEST(test_get_allocated_size);

    printf("Tests passed: %d\n", passed);
    printf("Tests failed: %d\n", failed);

    return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}