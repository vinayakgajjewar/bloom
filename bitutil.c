/*
 * bitutil.c
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "bitutil.h"

#define BITS_IN_TYPE(type) (CHAR_BIT * sizeof(type))

/*
 * The input parameter bits may not be a multiple of 32, so we need to account
 * for that.
 */
bit_vect *bit_vect_new(size_t bits) {
    bit_vect *vect = malloc(sizeof(*vect));
    if (vect == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }
    size_t num_elems = bits / BITS_IN_TYPE(uint32_t);
    if (bits % BITS_IN_TYPE(uint32_t) != 0) {
        num_elems++;
    }
    vect->mem = calloc(num_elems, sizeof(*(vect->mem)));
    if (vect->mem == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }
    vect->size = bits;
    return vect;
}

void bit_vect_free(bit_vect *vect) {
    free(vect->mem);
    free(vect);
}

/*
 * TODO
 * I am not quite sure how the calculation for the bit offset works.
 *
 * The calculation for the chunk offset works because integer division in C just
 * discards the fractional portion.
 */
bool bit_vect_get(bit_vect *vect, size_t i) {
    if (i >= vect->size) {
        fprintf(stderr, "Out of bounds; i=%zu, sz=%zu", i, vect->size);
    }
    size_t chunk_offset = i / BITS_IN_TYPE(uint32_t);
    size_t bit_offset = i & (BITS_IN_TYPE(uint32_t) - 1);
    uint32_t byte = vect->mem[chunk_offset];
    return (byte >> bit_offset) & 1;
}

void bit_vect_set(bit_vect *vect, size_t i, bool val) {
    if (i >= vect->size) {
        fprintf(stderr, "Out of bounds: i=%zu, sz=%zu", i, vect->size);
        exit(EXIT_FAILURE);
    }
    size_t chunk_offset = i / BITS_IN_TYPE(uint32_t);
    size_t bit_offset = i & (BITS_IN_TYPE(uint32_t) - 1);
    uint32_t *byte = &(vect->mem[chunk_offset]);
    if (val) {
        *byte |= ((uint32_t) 1) << bit_offset;
    } else {
        *byte &= ~(1 << bit_offset);
    }
}