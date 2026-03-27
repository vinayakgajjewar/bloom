/*
 * hashf.c
 */

#include "hashf.h"

#define DJB2_INIT 5381

uint32_t djb2(const void *buf, size_t len) {
    uint32_t hash = DJB2_INIT;
    const uint8_t *data = buf;
    for (size_t i = 0; i < len; i++) {
        hash = ((hash << 5) + hash) + data[i];
    }
    return hash;
}

uint32_t sdbm(const void *buf, size_t len) {
    uint32_t hash = 0;
    const uint8_t *data = buf;
    for (size_t i = 0; i < len; i++) {
        hash = data[i] + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}