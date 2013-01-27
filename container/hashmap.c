#include "hashmap.h"
#define DEFAULT_CAPACITY 16
#define MAX_CAPACITY    (1 << 30)
#define DEFAULT_LOAD_FACTOR 0.75
INIT_CLASS(hashmap, map, TYPE_NORMAL_CLASS);

static int hashmap_comparator(void* data1, void* data2) {
    return data1 == data2;
}

static size_t hashmap_hasher(void* user_data) {
    return (size_t) user_data;
}

static void hashmap_init(hashmap self, size_t capacity) {
    self->_size = 0;
    self->_table = bcplib_malloc(sizeof(map_entry) * capacity);
    self->_capacity = DEFAULT_CAPACITY;
}

BEGIN_IMPL_INITIALIZER(hashmap)
init_super(flag);
// init data
// init comparator
if (bit_test(flag, HASHMAP_INIT_COMPARATOR)) {
    self->comparator = next_arg(comparator);
} else {
    self->comparator = hashmap_comparator;
}
// init hasher
if (bit_test(flag, HASHMAP_INIT_HASHER)) {
    self->hasher = next_arg(hasher);
} else {
    self->hasher = hashmap_hasher;
}
// init factor
if (bit_test(flag, HASHMAP_INIT_FACTOR)) {
    self->_load_factor = (float)next_arg(double);
    assert (self->_load_factor > 0 && self->_load_factor <= 1.f);
} else {
    self->_load_factor = DEFAULT_LOAD_FACTOR;
}
// init table related
if (bit_test(flag, HASHMAP_INIT_CAPACITY)) {
    hashmap_init(self, next_arg(size_t));
} else if (bit_test(flag, HASHMAP_INIT_MAP)) {
    map m = next_arg(map);
    hashmap_init(self, bcplib_max(m->size(m), 
            DEFAULT_CAPACITY) / self->_load_factor);
    self->put_all(self, m);
} else {
    hashmap_init(self, DEFAULT_CAPACITY);
}
END_IMPL_INITIALIZER(hashmap)
        
BEGIN_IMPL_FINALIZER(hashmap)
assert(self->_table);
bcplib_free(self->_table);
END_IMPL_FINALIZER(hashmap)