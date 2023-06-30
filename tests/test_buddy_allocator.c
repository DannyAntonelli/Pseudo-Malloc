#include <stdio.h>

#include "bitset.h"
#include "buddy_allocator.h"
#include "unittest.h"

#define BUDDY_MEMORY_LIMIT (1 << 20)
#define BUDDY_MAX_LEVELS 10
#define BUDDY_MIN_BUCKET_SIZE (BUDDY_MEMORY_LIMIT >> (BUDDY_MAX_LEVELS - 1))
#define NUMBER_OF_BUDDIES (1 << BUDDY_MAX_LEVELS) - 1
#define BITSET_SIZE (NUMBER_OF_BUDDIES + 7) >> 3

/**
 * @brief Test the initialization of the allocator
 *
 * @return int 0 if the test passed, 1 otherwise
 */
int test_init()
{
    buddy_allocator_t allocator;
    bitset_t bitset;
    uint8_t buffer[BITSET_SIZE];
    uint8_t data[BUDDY_MEMORY_LIMIT];
    bitset_init(&bitset, buffer, sizeof(buffer));
    buddy_allocator_init(&allocator, &bitset, (void *)data, BUDDY_MAX_LEVELS, BUDDY_MIN_BUCKET_SIZE);

    return !(allocator.bitset == &bitset &&
             allocator.data == data &&
             allocator.levels == BUDDY_MAX_LEVELS &&
             allocator.min_bucket_size == BUDDY_MIN_BUCKET_SIZE);
}

/**
 * @brief Test the allocation of a block of memory
 *
 * @return int 0 if the test passed, 1 otherwise
 */
int test_alloc()
{
    buddy_allocator_t allocator;
    bitset_t bitset;
    uint8_t buffer[BITSET_SIZE] = {0};
    uint8_t data[BUDDY_MEMORY_LIMIT] = {0};
    bitset_init(&bitset, buffer, sizeof(buffer));
    bitset_set(&bitset, 0, BUDDY_FREE);
    buddy_allocator_init(&allocator, &bitset, (void *)data, BUDDY_MAX_LEVELS, BUDDY_MIN_BUCKET_SIZE);

    void *ptr = buddy_allocator_malloc(&allocator, 1);
    buddy_allocator_free(&allocator, ptr);

    return ptr == NULL;
}

/**
 * @brief Test the allocation of a block of memory that exceeds the memory limit
 *
 * @return int 0 if the test passed, 1 otherwise
 */
int test_memory_limit_exceeded()
{
    buddy_allocator_t allocator;
    bitset_t bitset;
    uint8_t buffer[BITSET_SIZE] = {0};
    uint8_t data[BUDDY_MEMORY_LIMIT] = {0};
    bitset_init(&bitset, buffer, sizeof(buffer));
    bitset_set(&bitset, 0, BUDDY_FREE);
    buddy_allocator_init(&allocator, &bitset, (void *)data, BUDDY_MAX_LEVELS, BUDDY_MIN_BUCKET_SIZE);

    void *ptr1 = buddy_allocator_malloc(&allocator, BUDDY_MEMORY_LIMIT - sizeof(size_t));
    void *ptr2 = buddy_allocator_malloc(&allocator, 1);
    buddy_allocator_free(&allocator, ptr1);

    return ptr1 == NULL || ptr2 != NULL;
}

/**
 * @brief Test allocating and freeing a block of memory and then allocating a block of the same size
 *
 * @return int 0 if the test passed, 1 otherwise
 */
int test_free_and_alloc_same_address()
{
    buddy_allocator_t allocator;
    bitset_t bitset;
    uint8_t buffer[BITSET_SIZE] = {0};
    uint8_t data[BUDDY_MEMORY_LIMIT] = {0};
    bitset_init(&bitset, buffer, sizeof(buffer));
    bitset_set(&bitset, 0, BUDDY_FREE);
    buddy_allocator_init(&allocator, &bitset, (void *)data, BUDDY_MAX_LEVELS, BUDDY_MIN_BUCKET_SIZE);

    void *ptr1 = buddy_allocator_malloc(&allocator, 1);
    buddy_allocator_free(&allocator, ptr1);
    void *ptr2 = buddy_allocator_malloc(&allocator, 1);
    buddy_allocator_free(&allocator, ptr2);

    return ptr1 != ptr2;
}

int main()
{
    TEST(test_init);
    TEST(test_alloc);
    TEST(test_memory_limit_exceeded);
    TEST(test_free_and_alloc_same_address);

    printf("Tests passed: %d\n", passed);
    printf("Tests failed: %d\n", failed);

    return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
