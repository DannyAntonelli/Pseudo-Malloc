#include "bitset.h"

typedef struct
{
    uint8_t *buffer;
    size_t num_bits;
    size_t buffer_size;
} bitset_t;

/**
 * @brief Initializes a bitset.
 *
 * @param bitset The bitset to initialize.
 * @param num_bits The number of bits in the bitset.
 * @param buffer The buffer to use for the bitset.
 * @param buffer_size The size of the buffer.
 */
void bitset_init(bitset_t *bitset, size_t num_bits, uint8_t *buffer, size_t buffer_size)
{
    bitset->buffer = buffer;
    bitset->num_bits = num_bits;
    bitset->buffer_size = buffer_size;
    memset(bitset->buffer, 0, bitset->buffer_size);
}

/**
 * @brief Sets a bit in the bitset.
 *
 * @param bitset The bitset to set the bit in.
 * @param bit The bit to set.
 * @param value The value to set the bit to.
 * @return void
 */
void bitset_set(bitset_t *bitset, size_t bit, bool value)
{
    assert(bit >= 0 && bit < bitset->num_bits);
    size_t byte = bit / 8;
    size_t bit_in_byte = bit % 8;
    uint8_t mask = 1 << bit_in_byte;
    if (value)
    {
        bitset->buffer[byte] |= mask;
    }
    else
    {
        bitset->buffer[byte] &= ~mask;
    }
}

/**
 * @brief Gets a bit in the bitset.
 *
 * @param bitset The bitset to get the bit from.
 * @param bit The bit to get.
 * @return bool The value of the bit.
 */
bool bitset_get(bitset_t *bitset, size_t bit)
{
    assert(bit >= 0 && bit < bitset->num_bits);
    size_t byte = bit / 8;
    size_t bit_in_byte = bit % 8;
    uint8_t mask = 1 << bit_in_byte;
    return (bitset->buffer[byte] & mask) != 0;
}