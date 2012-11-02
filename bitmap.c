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

static size_t bitmap_size(bitmap b);
static void bitmap_set(bitmap b, size_t idx);
static void bitmap_clear(bitmap b, size_t idx);
static bool bitmap_test(bitmap b, size_t idx);
static void bitmap_flip(bitmap b, size_t idx);
static void bitmap_set_multiple(bitmap b, size_t n, size_t idxs, ...);
static void bitmap_clear_multiple(bitmap b, size_t n, size_t idxs, ...);
static void bitmap_set_all(bitmap b);
static void bitmap_clear_all(bitmap b);

static inline
void assert_basic(bitmap b, size_t idx) {
    assert(b != NULL);
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
    bitmap ret = (bitmap) malloc(sizeof (struct bcplib_bitmap));
    // check malloc result
    if (ret == NULL) {
        return NULL;
    }

    size_t bytes = byte_num(bits_num);
    memset(ret, 0, sizeof (struct bcplib_bitmap));
    ret->bit_num = bits_num;
    ret->bits = (bit_elem *) malloc(bytes);
    // check malloc result
    if (ret->bits == NULL) {
        free(ret);
        return NULL;
    }

    memset(ret->bits, 0, bytes);
    // init functions
    object_init(ret);
    ret->clear = bitmap_clear;
    ret->clear_all = bitmap_clear_all;
    ret->clear_multiple = bitmap_clear_multiple;
    ret->flip = bitmap_flip;
    ret->set = bitmap_set;
    ret->set_all = bitmap_set_all;
    ret->set_multiple = bitmap_set_multiple;
    ret->test = bitmap_test;
    return ret;
}

bitmap bitmap_destory(bitmap bitmap) {
    if (bitmap == NULL) {
        return NULL;
    }

    free(bitmap->bits);
    free(bitmap);
    return NULL;
}

static
size_t bitmap_size(bitmap b) {
    assert(b != NULL);

    return b->bit_num;
}

static
void bitmap_set(bitmap b, size_t idx) {
    assert_basic(b, idx);

    b->bits[ELEM_IDX(idx)] |= ELEM_MASK(idx);
}

static
void bitmap_clear(bitmap b, size_t idx) {
    assert_basic(b, idx);

    b->bits[ELEM_IDX(idx)] &= ~ELEM_MASK(idx);
}

static
bool bitmap_test(bitmap b, size_t idx) {
    assert_basic(b, idx);

    return (b->bits[ELEM_IDX(idx)] & ELEM_MASK(idx)) != 0;
}

static
void bitmap_flip(bitmap b, size_t idx) {
    assert_basic(b, idx);

    b->bits[ELEM_IDX(idx)] ^= ELEM_MASK(idx);
}

static
void bitmap_set_multiple(bitmap b, size_t n, size_t idxs, ...) {
    assert(b != NULL);
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

static
void bitmap_clear_multiple(bitmap b, size_t n, size_t idxs, ...) {
    assert(b != NULL);
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

static
void bitmap_set_all(bitmap b) {
    assert(b != NULL);
    
    memset(b->bits, 1, byte_num(b->bit_num));
}

static
void bitmap_clear_all(bitmap b) {
    assert(b != NULL);
    
    memset(b->bits, 0, byte_num(b->bit_num));
}
