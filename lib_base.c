#include "lib_base.h"
#include <assert.h>

/* Function Declarations */
static int object_equals(id this, id that);

/*
 * Init function of abstract class object.
 * Init function never check the parameter, because object is a abstract class
 * and 1 class that inherit it have to check the parameter themself.
 */
inline
void object_init(id user_obj) {
    object obj = (object) user_obj;
    obj->equals = object_equals;
}

inline
void object_finalize(id obj) {
    // do nothing currently
}

static
int object_equals(id this, id that) {
    return this == that;
}

/* Utilities */
inline
id _safe_cast(id obj) {
    assert(obj != NULL);
    return obj;
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