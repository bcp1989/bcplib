#include "bcplib_base.h"
#include "object.h"
#include <assert.h>
#include <stdarg.h>

id _new(class type, init_flag flag, ...) {
    object obj = (object)_malloc_object(type);
    va_list args;
    va_start(args, flag);
    class cls = classof(obj);
    cls->initializer(obj, cls, flag, args);
    va_end(args);
    return obj;
}

void _destroy(id obj) {
    object o = cast(object, obj);
    class class = classof(o);
    class->finalizer(o, class);
    bcplib_free(o);
}

id _malloc_object(class type) {
    object ret = (object)bcplib_malloc(type->size);
    ret->class = type;
    ret->magic_number = BCPLIB_MAGIC_NUMBER;
    return ret;
}
/* Utilities */
void* bcplib_malloc(size_t size) {
    return malloc(size);
}

void* bcplib_calloc(size_t nelements, size_t bytes) {
    return calloc(nelements, bytes);
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