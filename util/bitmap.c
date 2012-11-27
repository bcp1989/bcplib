#include "bitmap.h"
#include <assert.h>
#include <stdlib.h>

#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdarg.h>

INIT_CLASS(bitmap, object, TYPE_FINAL_CLASS);

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

bitmap bitmap_create(size_t bits_num) {
    bitmap ret = malloc_object(bitmap);
    // check malloc result
    if (ret == NULL) {
        return NULL;
    }

    size_t bytes = byte_num(bits_num);
    memset(ret, 0, sizeof (struct bcplib_bitmap));
    ret->bit_num = bits_num;
    ret->bits = (bit_elem *) bcplib_malloc(bytes);
    // check malloc result
    if (ret->bits == NULL) {
        bcplib_free(ret);
        return NULL;
    }

    memset(ret->bits, 0, bytes);
    // init functions
    object_init(ret);
    ret->destroy = bitmap_destroy;
    ret->clear = bitmap_clear;
    ret->clear_all = bitmap_clear_all;
    ret->clear_multiple = bitmap_clear_multiple;
    ret->flip = bitmap_flip;
    ret->set = bitmap_set;
    ret->set_all = bitmap_set_all;
    ret->set_multiple = bitmap_set_multiple;
    ret->test = bitmap_test;
    ret->size = bitmap_size;
    return ret;
}

void bitmap_destroy(id obj) {
    bitmap b = cast(bitmap, obj);
    bcplib_free(b->bits);
    bcplib_free(b);
}

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
