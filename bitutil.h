/*
 * bitutil.h
 */

#ifndef BITUTIL_H
#define BITUTIL_H

#include <stdbool.h>

/*
 * In C, there is no data type that is one bit in size, so we need to implement
 * a bit vector data structure ourselves.
 */
typedef struct bit_vect_s {
    uint32_t *mem;

    /*
     * Keeps track of the number of bits.
     */
    size_t size;
} bit_vect;

bit_vect *bit_vect_new(size_t bits);

void bit_vect_free(bit_vect *vect);

bool bit_vect_get(bit_vect *vect, size_t i);

void bit_vect_set(bit_vect *vect, size_t i, bool val);

#endif