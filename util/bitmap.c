#include "bitmap.h"
#include <assert.h>
#include <stdlib.h>

#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdarg.h>

#define SHIFT 5 // according to the type of bit_elem
#define ELEM_IDX(idx) ((idx) >> SHIFT)
#define MOD_MASK 0x1f // according to the type of bit_elem
#define ELEM_MASK(idx) (1 << ((idx) & MOD_MASK))
#define BITS_PER_ELEM (sizeof (bit_elem) * CHAR_BIT)

static inline
void assert_basic(bitmap b, size_t idx) {
    assert(idx >= 0 && idx < b->bit_num);
}

static inline
size_t elem_num(size_t bits_num) {
    return (size_t) ceil((double) bits_num / (double) BITS_PER_ELEM);
}

static inline
size_t byte_num(size_t bits_num) {
    return sizeof (bit_elem) * elem_num(bits_num);
}

INIT_CLASS(bitmap, object, TYPE_FINAL_CLASS);
// initializer
BEGIN_IMPL_INITIALIZER(bitmap)
init_super(flag);
size_t bits_num = next_arg(size_t);
// init data
size_t bytes = byte_num(bits_num);
self->bit_num = bits_num;
self->bits = (bit_elem *) bcplib_malloc(bytes);
memset(self->bits, 0, bytes);
// init functions
self->clear = bitmap_clear;
self->clear_all = bitmap_clear_all;
self->clear_multiple = bitmap_clear_multiple;
self->flip = bitmap_flip;
self->set = bitmap_set;
self->set_all = bitmap_set_all;
self->set_multiple = bitmap_set_multiple;
self->test = bitmap_test;
self->size = bitmap_size;
END_IMPL_INITIALIZER(bitmap)

// finalizer
BEGIN_IMPL_FINALIZER(bitmap)
bcplib_free(self->bits);
END_IMPL_FINALIZER(bitmap)

size_t bitmap_size(id obj) {
    bitmap b = cast(bitmap, obj);
    return b->bit_num;
}

void bitmap_set(id obj, size_t idx) {
    bitmap b = cast(bitmap, obj);
    assert_basic(b, idx);
    b->bits[ELEM_IDX(idx)] |= ELEM_MASK(idx);
}

void bitmap_clear(id obj, size_t idx) {
    bitmap b = cast(bitmap, obj);
    assert_basic(b, idx);

    b->bits[ELEM_IDX(idx)] &= ~ELEM_MASK(idx);
}

bool bitmap_test(id obj, size_t idx) {
    bitmap b = cast(bitmap, obj);
    assert_basic(b, idx);

    return (b->bits[ELEM_IDX(idx)] & ELEM_MASK(idx)) != 0;
}

void bitmap_flip(id obj, size_t idx) {
    bitmap b = cast(bitmap, obj);
    assert_basic(b, idx);

    b->bits[ELEM_IDX(idx)] ^= ELEM_MASK(idx);
}

void bitmap_set_multiple(id obj, size_t n, size_t idxs, ...) {
    bitmap b = cast(bitmap, obj);
    // TODO need to check n and the rest of the parameters
    size_t i = 0;
    size_t idx = 0;
    va_list args;
    va_start(args, idxs);
    for (i = 0; i < n; ++i) {
        idx = va_arg(args, size_t);
        bitmap_set(b, idx);
    }
    va_end(args);
}

void bitmap_clear_multiple(id obj, size_t n, size_t idxs, ...) {
    bitmap b = cast(bitmap, obj);
    // TODO need to check n and the rest of the parameters
    size_t i = 0;
    size_t idx = 0;
    va_list args;
    va_start(args, idxs);
    for (i = 0; i < n; ++i) {
        idx = va_arg(args, size_t);
        bitmap_clear(b, idx);
    }
    va_end(args);
}

void bitmap_set_all(id obj) {
    bitmap b = cast(bitmap, obj);

    memset(b->bits, 1, byte_num(b->bit_num));
}

void bitmap_clear_all(id obj) {
    bitmap b = cast(bitmap, obj);

    memset(b->bits, 0, byte_num(b->bit_num));
}
