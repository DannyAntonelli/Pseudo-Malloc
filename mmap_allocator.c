#include <sys/mman.h>

#include "logging.h"
#include "mmap_allocator.h"

void *mmap_malloc(size_t size)
{
    void *ptr = mmap(NULL, size + sizeof(size_t), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED)
    {
        LOG(LOG_LEVEL_ERROR, "mmap failed");
        return NULL;
    }
    *((size_t *)ptr) = size;
    LOG(LOG_LEVEL_INFO, "mmap_malloc(%zu) = %p", size, ptr + sizeof(size_t));
    return ptr + sizeof(size_t);
}

void mmap_free(void *ptr)
{
    size_t size = *((size_t *)(ptr - sizeof(size_t)));
    if (munmap(ptr - sizeof(size_t), size + sizeof(size_t)) == -1)
    {
        LOG(LOG_LEVEL_ERROR, "munmap failed");
        return;
    }
    LOG(LOG_LEVEL_INFO, "mmap_free(%p)", ptr);
}
