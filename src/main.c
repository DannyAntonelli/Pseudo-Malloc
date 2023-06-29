#include <stdio.h>
#include <unistd.h>

#include "mymalloc.h"

int main()
{
    mymalloc_init();

    int *ptr = mymalloc(sizeof(int));
    *ptr = 10;
    printf("%d\n", *ptr);
    int *ptr2 = mymalloc(5 * sizeof(int));

    *ptr2 = 20;
    printf("%d\n", *ptr2);

    int *ptr3 = mymalloc(1000 * sizeof(int));
    *ptr3 = 30;
    printf("%d\n", *ptr3);

    myfree(ptr);
    myfree(ptr2);
    myfree(ptr3);

    int *ptr4 = mymalloc(sizeof(int));
    *ptr4 = 40;
    printf("%d\n", *ptr4);
    myfree(ptr4);

    return 0;
}
