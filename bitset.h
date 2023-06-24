#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct
{
    uint8_t *buffer;
    size_t num_bits;
    size_t buffer_size;
} bitset_t;

/**
 * @brief Initializes a bitset with an external buffer.
 *
 * @param bitset The bitset to initialize.
 * @param num_bits The number of bits in the bitset.
 * @param buffer The buffer to use for the bitset.
 * @param buffer_size The size of the buffer.
 */
void bitset_init(bitset_t *bitset, size_t num_bits, uint8_t *buffer, size_t buffer_size);

/**
 * @brief Sets a bit in the bitset.
 *
 * @param bitset The bitset to set the bit in.
 * @param bit The bit to set.
 * @param value The value to set the bit to.
 * @return void
 */
void bitset_set(bitset_t *bitset, size_t bit, bool value);

/**
 * @brief Gets a bit in the bitset.
 *
 * @param bitset The bitset to get the bit from.
 * @param bit The bit to get.
 * @return bool The value of the bit.
 */
bool bitset_get(bitset_t *bitset, size_t bit);
