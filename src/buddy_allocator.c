#include <assert.h>
#include <sys/types.h>

#include "buddy_allocator.h"
#include "logging.h"

/**
 * @brief Gets the index of the parent of a node.
 *
 * @param idx The index of the node.
 * @return size_t The index of the parent.
 */
size_t parent(size_t idx)
{
    return (idx - 1) / 2;
}

/**
 * @brief Gets the index of the left child of a node.
 *
 * @param idx The index of the node.
 * @return size_t The index of the left child.
 */
size_t left_child(size_t idx)
{
    return 2 * idx + 1;
}

/**
 * @brief Gets the index of the right child of a node.
 *
 * @param idx The index of the node.
 * @return size_t The index of the right child.
 */
size_t right_child(size_t idx)
{
    return 2 * idx + 2;
}

void buddy_allocator_init(buddy_allocator_t *allocator, bitset_t *bitset, void *data, size_t levels, size_t min_bucket_size)
{
    allocator->bitset = bitset;
    allocator->data = data;
    allocator->levels = levels;
    allocator->min_bucket_size = min_bucket_size;
}

/**
 * @brief Gets the minimum level for a given size.
 *
 * @param allocator The allocator to get the level from.
 * @param size The size to get the level for.
 * @return size_t The level.
 */
size_t buddy_allocator_get_min_level(buddy_allocator_t *allocator, size_t size)
{
    size_t curr_size = allocator->min_bucket_size;
    size_t level = allocator->levels - 1;
    while (curr_size < size)
    {
        curr_size *= 2;
        level--;
    }
    return level;
}

/**
 * @brief Searches for a free buddy in the allocator.
 *
 * @param bitset The bitset to search.
 * @param level The level of the buddy to search for.
 * @return ssize_t The index of the buddy or -1 if none available.
 */
ssize_t search_free_buddy(bitset_t *bitset, size_t level)
{
    size_t start_idx = (1 << level) - 1;
    size_t end_idx = (1 << (level + 1)) - 1;
    for (size_t i = start_idx; i < end_idx; ++i)
    {
        if (bitset_get(bitset, i) == BUDDY_FREE)
        {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Gets a free buddy from the allocator.
 *
 * @param allocator The allocator to get from.
 * @param level The level of the buddy to get.
 * @return ssize_t The index of the buddy or -1 if none available.
 */
ssize_t buddy_allocator_get_free_buddy_idx(buddy_allocator_t *allocator, ssize_t level)
{
    assert(level <= (ssize_t)allocator->levels);

    if (level < 0)
    {
        return -1;
    }

    ssize_t idx = search_free_buddy(allocator->bitset, level);
    if (idx != -1)
    {
        bitset_set(allocator->bitset, idx, BUDDY_OCCUPIED);
        return idx;
    }

    ssize_t parent_idx = buddy_allocator_get_free_buddy_idx(allocator, level - 1);

    if (parent_idx == -1)
    {
        return -1;
    }

    bitset_set(allocator->bitset, right_child(parent_idx), BUDDY_FREE);

    return left_child(parent_idx);
}

/**
 * @brief Releases a buddy in the allocator.
 *
 * @param allocator The allocator to release from.
 * @param idx The index of the buddy to release.
 * @return void
 */
void buddy_allocator_release_buddy(buddy_allocator_t *allocator, size_t idx)
{
    assert(idx < (size_t)(1 << allocator->levels) - 1);

    bitset_set(allocator->bitset, idx, BUDDY_FREE);

    while (idx != 0)
    {
        size_t parent_idx = parent(idx);
        if (bitset_get(allocator->bitset, left_child(parent_idx)) == BUDDY_FREE &&
            bitset_get(allocator->bitset, right_child(parent_idx)) == BUDDY_FREE)
        {
            bitset_set(allocator->bitset, parent_idx, BUDDY_FREE);
            bitset_set(allocator->bitset, left_child(parent_idx), BUDDY_OCCUPIED);
            bitset_set(allocator->bitset, right_child(parent_idx), BUDDY_OCCUPIED);
        }
        else
        {
            break;
        }
        idx = parent_idx;
    }
}

void *buddy_allocator_malloc(buddy_allocator_t *allocator, size_t size)
{
    size_t level = buddy_allocator_get_min_level(allocator, size + sizeof(size_t));
    ssize_t idx = buddy_allocator_get_free_buddy_idx(allocator, level);
    if (idx == -1)
    {
        LOG(LOG_LEVEL_ERROR, "No free buddy found");
        return NULL;
    }

    size_t buddy_size = allocator->min_bucket_size * (1 << (allocator->levels - level - 1));
    size_t idx_in_level = idx - ((1 << level) - 1);
    size_t *ptr = (size_t *)(allocator->data + (buddy_size * idx_in_level));
    *ptr = (size_t)idx;

    LOG(LOG_LEVEL_INFO, "Allocated buddy at index %zu", idx);
    return (void *)(ptr + 1);
}

void buddy_allocator_free(buddy_allocator_t *allocator, void *ptr)
{
    size_t idx = *((size_t *)ptr - 1);
    LOG(LOG_LEVEL_INFO, "Freeing buddy at index %zu", idx);
    buddy_allocator_release_buddy(allocator, idx);
}
