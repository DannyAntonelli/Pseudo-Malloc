#include <stdio.h>

#include "bitset.h"
#include "unittest.h"

/**
 * @brief Tests the initialization of a bitset.
 *
 * @return int 0 if the test passed, 1 if the test failed.
 */
int test_init()
{
    bitset_t bitset;
    uint8_t buffer[10];
    bitset_init(&bitset, 15, buffer, 10);

    return !(bitset.buffer == buffer && bitset.num_bits == 15 && bitset.buffer_size == 10);
}

/**
 * @brief Tests setting a bit in a bitset.
 *
 * @return int 0 if the test passed, 1 if the test failed.
 */
int test_set()
{
    bitset_t bitset;
    uint8_t buffer[5];
    bitset_init(&bitset, 12, buffer, 5);
    bitset_set(&bitset, 10, true);

    int value = (bitset.buffer[1] & 0b00000100) != 0;
    return value == 1 ? 0 : 1;
}

/**
 * @brief Tests getting a bit in a bitset.
 *
 * @return int 0 if the test passed, 1 if the test failed.
 */
int test_get()
{
    bitset_t bitset;
    uint8_t buffer[5];
    bitset_init(&bitset, 17, buffer, 5);
    bitset.buffer[1] = 0b00000100;

    int value = bitset_get(&bitset, 10);
    return value ? 0 : 1;
}

int main()
{
    TEST(test_init);
    TEST(test_set);
    TEST(test_get);

    printf("Tests passed: %d\n", passed);
    printf("Tests failed: %d\n", failed);

    return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
