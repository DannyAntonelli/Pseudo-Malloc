#include <stdint.h>
#include <stdio.h>

#include "mymalloc.h"
#include "unittest.h"

/**
 * @brief Test mymalloc
 *
 * @return int 0 if successful, 1 otherwise.
 */
int test_mymalloc()
{
    mymalloc_init();
    void *ptr = mymalloc(10);
    return ptr == NULL;
}

/**
 * @brief Test mycalloc
 *
 * @return int 0 if successful, 1 otherwise.
 */
int test_mycalloc()
{
    mymalloc_init();
    void *ptr = mycalloc(10, 10);
    for (int i = 0; i < 100; i++)
    {
        if (((uint8_t *)ptr)[i] != 0)
        {
            return 1;
        }
    }
    return ptr == NULL;
}

/**
 * @brief Test myrealloc
 *
 * @return int 0 if successful, 1 otherwise.
 */
int test_myrealloc()
{
    mymalloc_init();
    void *ptr = mymalloc(10);
    ptr = myrealloc(ptr, 20);
    return ptr == NULL;
}

int main()
{
    TEST(test_mymalloc);
    TEST(test_mycalloc);
    TEST(test_myrealloc);

    printf("Tests passed: %d\n", passed);
    printf("Tests failed: %d\n", failed);

    return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
