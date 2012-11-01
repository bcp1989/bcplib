#include "bitmap.h"
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdarg.h>

#define SHIFT 5 // according to the type of bit_elem
#define ELEM_IDX(idx) ((idx) >> SHIFT)
#define MOD_MASK 0x1f // according to the type of bit_elem
#define ELEM_MASK(idx) (1 << ((idx) & MOD_MASK))
#define BITS_PER_ELEM (sizeof (bit_elem) * CHAR_BIT)

typedef uint32_t bit_elem;

struct bitmap {
    size_t bit_num;
    bit_elem *bits;    
};

static inline 
void assert_basic (struct bitmap *b, size_t idx) {
    assert (b != NULL);
    assert (idx >= 0 && idx < b->bit_num);
}

static inline
size_t elem_num (size_t bits_num) {
    return (size_t) ceil ((double) bits_num / (double) BITS_PER_ELEM);
}

static inline
size_t byte_num (size_t bits_num) {
    return sizeof (bit_elem) * elem_num (bits_num);
}


struct bitmap *bitmap_create (size_t bits_num) {
    struct bitmap *ret = (struct bitmap *) malloc (sizeof (struct bitmap));
    // check malloc result
    if (ret == NULL) {
        return NULL;
    }
    
    size_t bytes = byte_num (bits_num);
    memset (ret, 0, sizeof (struct bitmap));
    ret->bit_num = bits_num;
    ret->bits = (bit_elem *) malloc (bytes);
    // check malloc result
    if (ret->bits == NULL) {
        free (ret);
        return NULL;
    }
    
    memset (ret->bits, 0, bytes);
    return ret;
}

struct bitmap *bitmap_destory (struct bitmap *bitmap) {
    if (bitmap == NULL) {
        return NULL;
    }
    
    free (bitmap->bits);
    free (bitmap);
    return NULL;
}

size_t bitmap_size (struct bitmap *b) {
    assert (b != NULL);
    
    return b->bit_num;
}

void bitmap_set (struct bitmap *b, size_t idx) {
    assert_basic (b, idx);
    
    b->bits[ELEM_IDX (idx)] |= ELEM_MASK (idx);
}

void bitmap_clear (struct bitmap *b, size_t idx) {
    assert_basic (b, idx);
    
    b->bits[ELEM_IDX (idx)] &= ~ ELEM_MASK (idx);
}

int bitmap_test (struct bitmap *b, size_t idx) {
    assert_basic (b, idx);
    
    return b->bits[ELEM_IDX (idx)] & ELEM_MASK (idx);
}

void bitmap_flip (struct bitmap *b, size_t idx) {
    assert_basic (b, idx);
    
    b->bits[ELEM_IDX (idx)] ^= ELEM_MASK (idx);
}

void bitmap_set_multiple (struct bitmap *b, size_t n, size_t idxs, ...) {
    size_t i = 0;
    size_t idx = 0;
    va_list args;
	va_start (args, idxs);
    for (i = 0; i < n; ++i) {
        idx = va_arg (args, size_t);
        bitmap_set (b, idx);
    }
	va_end (args);
}

void bitmap_clear_multiple (struct bitmap *b, size_t n, size_t idxs, ...) {
    size_t i = 0;
    size_t idx = 0;
    va_list args;
	va_start (args, idxs);
    for (i = 0; i < n; ++i) {
        idx = va_arg (args, size_t);
        bitmap_clear (b, idx);
    }
	va_end (args);
}

void bitmap_set_all (struct bitmap *b) {
    assert (b != NULL);
    memset (b->bits, 1, byte_num (b->bit_num));
}

void bitmap_clear_all (struct bitmap *b) {
    assert (b != NULL);
    memset (b->bits, 0, byte_num (b->bit_num));
}
