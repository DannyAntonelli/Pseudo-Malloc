#include "bitset.h"
#include <assert.h>
#include <string.h>

void bitset_init(bitset_t *bitset, size_t num_bits, uint8_t *buffer, size_t buffer_size)
{
    bitset->buffer = buffer;
    bitset->num_bits = num_bits;
    bitset->buffer_size = buffer_size;
    memset(bitset->buffer, 0, bitset->buffer_size);
}

void bitset_set(bitset_t *bitset, size_t bit, bool value)
{
    assert(bit < bitset->num_bits);
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

bool bitset_get(bitset_t *bitset, size_t bit)
{
    assert(bit < bitset->num_bits);
    size_t byte = bit / 8;
    size_t bit_in_byte = bit % 8;
    uint8_t mask = 1 << bit_in_byte;
    return (bitset->buffer[byte] & mask) != 0;
}