#include "bcplib_base.h"
#include "object.h"
#include <assert.h>

/* Utilities */
id _malloc_object(size_t size, class_type type) {
    id ret = bcplib_malloc(size);
    ((object)ret)->class_type = type;
    return ret;
}

void* bcplib_malloc(size_t size) {
    return malloc(size);
}

void* bcplib_realloc(void* pointer, size_t new_size) {

    return realloc(pointer, new_size);
}

void bcplib_free(void* p) {
    free(p);
}

void bcplib_array_copy(void** from, void** to, size_t offset, size_t length) {
    assert(from != NULL && to != NULL);
    assert(offset >= 0 && length >= 0);
    size_t i = 0;
    for (i = 0; i < length; ++i) {
        to[i] = from[offset + i];
    }
}