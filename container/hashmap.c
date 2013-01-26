#include "hashmap.h"
#define DEFAULT_SIZE 16
#define MAX_SIZE    (1 << 30)
#define DEFAULT_LOAD_FACTOR 0.75
INIT_CLASS(hashmap, map, TYPE_NORMAL_CLASS);

static int hashmap_comparator(void* data1, void* data2) {
    return data1 == data2;
}

static size_t hashmap_hasher(void* user_data) {
    return (size_t) user_data;
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
    self->_load_factor = next_arg(float);
} else {
    self->_load_factor = DEFAULT_LOAD_FACTOR;
}
// init table
if (bit_test(flag, HASHMAP_INIT_SIZE)) {
    size_t size = next_arg(size_t);
    // TODO
} else if (bit_test(flag, HASHMAP_INIT_MAP)) {
    map m = next_arg(map);
    // TODO
} else {
    self->_table = bcplib_malloc(sizeof(map_entry) * DEFAULT_SIZE);
}
END_IMPL_INITIALIZER(hashmap)
        
BEGIN_IMPL_FINALIZER(hashmap)
assert(self->_table);
bcplib_free(self->_table);
END_IMPL_FINALIZER(hashmap)