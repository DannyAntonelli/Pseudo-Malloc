#include <stdio.h>
#include <unistd.h>

#include "mymalloc.h"

int main()
{
    mymalloc_init();

    int *ptr = mymalloc(sizeof(int));
    *ptr = 1;
    printf("%d\n", *ptr);

    int *ptr2 = mymalloc(5 * sizeof(int));
    *ptr2 = 2;
    printf("%d\n", *ptr2);

    int *ptr3 = mycalloc(1000, sizeof(int));
    ptr3[1] = 3;
    printf("%d\n", ptr3[0]);
    printf("%d\n", ptr3[1]);

    myfree(ptr);
    myfree(ptr2);

    ptr3 = myrealloc(ptr3, 2000 * sizeof(int));
    ptr3[5] = 4;
    printf("%d\n", ptr3[0]);
    printf("%d\n", ptr3[1]);
    printf("%d\n", ptr3[5]);

    myfree(ptr3);

    return 0;
}
