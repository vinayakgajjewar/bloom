/*
 * hashf.h
 */

#ifndef HASHF_H
#define HASHF_H

//#include <stdint.h>
#include <stdlib.h>

/*
 * len is the size of the buffer in bytes.
 */
uint32_t djb2(const void *buf, size_t len);


/*
 * len is the size of the buffer in bytes.
 */
uint32_t sdbm(const void *buf, size_t len);

#endif