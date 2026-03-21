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