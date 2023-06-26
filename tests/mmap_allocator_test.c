#include <stdio.h>

#include "../mmap_allocator.h"
#include "unittest.h"

int test_malloc()
{
    void *ptr = mmap_malloc(10);
    return ptr == NULL;
}

int main(int argc, char *argv[])
{
    TEST(test_malloc);

    printf("Tests passed: %d\n", passed);
    printf("Tests failed: %d\n", failed);

    return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}