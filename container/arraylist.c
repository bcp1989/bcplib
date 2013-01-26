#include "arraylist.h"
#define DEFAULT_SIZE 10
#define MAX_CAPACITY (((size_t) - 1) - 8)

INIT_CLASS(arraylist, list, TYPE_NORMAL_CLASS);
/* Helper function for initialization. */
static void init_by_size(arraylist self, size_t size);
/* Candidate functions */
static void arraylist_add_all_by_data(id self, void** user_data, size_t size);

// initializer
BEGIN_IMPL_INITIALIZER(arraylist)
init_super(flag);
// init. collection functions
self->remove = arraylist_remove;
self->clear = arraylist_clear;
self->size = arraylist_size;
self->is_empty = arraylist_is_empty;
self->contains = arraylist_contains;
// init. list functions
self->add_at = arraylist_add_at;
self->get = arraylist_get;
self->set = arraylist_set;
self->remove_at = arraylist_remove_at;
self->index_of = arraylist_index_of;
self->last_index_of = arraylist_last_index_of;
// init. array list functions
self->trim_to_size = arraylis_trim_to_size;
self->ensure_capacity = arraylist_ensure_capacity;
// init. list iterator interface
self->create_list_iterator = arraylist_create_list_iterator;
// init data
if (bit_test(flag, ARRAYLIST_INIT_SIZE)) {
    init_by_size(self, next_arg(size_t));
} else if (bit_test(flag, ARRAYLIST_INIT_DATA)) {
    void** init_data = next_arg(void**);
    size_t size = next_arg(size_t);
    init_by_size(self, size);
    arraylist_add_all_by_data(self, init_data, size);
} else if (bit_test(flag, ARRAYLIST_INIT_COLLECTION)) {
    collection c = next_arg(collection);
    init_by_size(self, c->size(c));
    self->add_all(self, c);
} else {
    init_by_size(self, DEFAULT_SIZE);
}
END_IMPL_INITIALIZER(arraylist)

// finalizer
BEGIN_IMPL_FINALIZER(arraylist)
bcplib_free(self->elements);
self->elements = NULL;

END_IMPL_FINALIZER(arraylist)

/* Helper function for initialization. */
static
void init_by_size(arraylist self, size_t size) {
    assert(size > 0);
    self->elements = (void**) bcplib_malloc(sizeof (void*) * size);
    self->_size = 0;
    self->_capacity = size;
}

/* Candidate functions */
static
void arraylist_add_all_by_data(id self, void** user_data, size_t size) {
    arraylist al = cast(arraylist, self);
    assert(size > 0);
    al->ensure_capacity(al, al->_size + size);
    size_t i = 0, len = al->_size + size;
    for (i = al->_size; i < len; ++i) {
        al->elements[i] = user_data[i - al->_size];
    }
    al->_size += size;
}

/* Collection functions */
bool arraylist_remove(id self, void* user_data) {
    arraylist al = cast(arraylist, self);
    size_t idx = al->index_of(al, user_data);
    if (idx >= 0) {
        al->remove_at(al, idx);
        return true;
    }
    return false;
}

void arraylist_clear(id self) {
    arraylist al = cast(arraylist, self);
    size_t i = 0;
    for (i = 0; i < al->_size; ++i) {
        al->elements[i] = NULL;
    }
    al->_size = 0;
}

size_t arraylist_size(id self) {
    arraylist al = cast(arraylist, self);
    return al->_size;
}

bool arraylist_is_empty(id self) {
    arraylist al = cast(arraylist, self);
    return al->_size == 0;
}

bool arraylist_contains(id self, void* user_data) {
    arraylist al = cast(arraylist, self);
    return al->index_of(al, user_data) >= 0;
}

/* List functions */
void arraylist_add_at(id self, size_t idx, void* user_data) {
    arraylist al = cast(arraylist, self);
    check_index_range(idx, 0, al->_size + 1);
    al->ensure_capacity(al, al->_size + 1);
    size_t i = 0;
    for (i = al->_size; i > idx; --i) {
        al->elements[i] = al->elements[i - 1];
    }
    al->elements[idx] = user_data;
    ++(al->_size);
}

void* arraylist_get(id self, size_t idx) {
    arraylist al = cast(arraylist, self);
    check_index_range(idx, 0, al->_size);
    return al->elements[idx];
}

void * arraylist_set(id self, size_t idx, void* user_data) {
    arraylist al = cast(arraylist, self);
    check_index_range(idx, 0, al->_size);
    void* ret = al->elements[idx];
    al->elements[idx] = user_data;
    return ret;
}

void* arraylist_remove_at(id self, size_t idx) {
    arraylist al = cast(arraylist, self);
    check_index_range(idx, 0, al->_size);
    void* ret = al->elements[idx];
    size_t i = idx;
    for (i = idx; i < al->_size - 1; ++i) {
        al->elements[i] = al->elements[i + 1];
    }
    --(al->_size);
    return ret;
}

size_t arraylist_index_of(id self, void* user_data) {
    arraylist al = cast(arraylist, self);
    size_t i = 0;
    for (i = 0; i < al->_size; ++i) {
        if (al->compare(al->elements[i], user_data) == 0) {
            return i;
        }
    }
    return -1;
}

size_t arraylist_last_index_of(id self, void* user_data) {
    arraylist al = cast(arraylist, self);
    size_t i = 0;
    for (i = al->_size - 1; i >= 0; --i) {
        if (al->compare(al->elements[i], user_data) == 0) {
            return i;
        }
    }
    return -1;
}

/* List iterator interface */
INIT_CLASS(arraylist_iterator, list_iterator, TYPE_NORMAL_CLASS);
// initializer
BEGIN_IMPL_INITIALIZER(arraylist_iterator)
init_super(flag);
// init iterator functions
self->next = arraylist_iterator_next;
self->remove = arraylist_iterator_remove;
// init list iterator functions
self->add = arraylist_list_iterator_add;
self->set = arraylist_list_iterator_set;
self->previous = arraylist_list_iterator_previous;
self->cursor = next_arg(size_t);
END_IMPL_INITIALIZER(arraylist_iterator)
// finalizer
BEGIN_IMPL_FINALIZER(arraylist_iterator)
// do nothing
END_IMPL_FINALIZER(arraylist_iterator)
list_iterator arraylist_create_list_iterator(id self, size_t idx) {
    arraylist al = cast(arraylist, self);
    check_index_range(idx, 0, al->_size + 1);
    return new(arraylist_iterator, INIT_DEFAULT, al, NULL, idx);
}

/* Array list function */
void arraylis_trim_to_size(id self) {
    arraylist al = cast(arraylist, self);
    // TODO safe re-alloc!
    void** new_elements = (void**) bcplib_malloc(al->_size * sizeof (void*));
    assert(new_elements != NULL);
    bcplib_array_copy(al->elements, new_elements, 0, al->_size);
    bcplib_free(al->elements);
    al->elements = new_elements;
    al->_capacity = al->_size;
}

void arraylist_ensure_capacity(id self, size_t new_cap) {
    arraylist al = cast(arraylist, self);
    assert(new_cap <= MAX_CAPACITY);
    if (new_cap <= al->_capacity) {
        return;
    } else {
        size_t cap_inc = (al->_capacity >> 1);
        size_t times = 0;
        while ((al->_capacity + cap_inc) < new_cap) {
            if (times % 2 == 0) {
                cap_inc <<= 1;
            } else {
                cap_inc += (cap_inc << 1);
            }
            // overflow
            if (cap_inc < 0) {
                cap_inc = new_cap - al->_capacity;
            }
            ++times;
        }
        //void** new_elements = (void**) bcplib_realloc(al->elements,
        //        cap_inc + al->capacity);
        void** new_elements = (void**) bcplib_malloc(
                sizeof (void *) * (cap_inc + al->_capacity));
        size_t i = 0;
        // TODO extract to system copy
        for (i = 0; i < al->_capacity; ++i) {
            new_elements[i] = al->elements[i];
        }

        // TODO optimize
        assert(new_elements != NULL);
        bcplib_free(al->elements);
        al->elements = new_elements;
        al->_capacity += cap_inc;
    }
}

/* Iterator functions */

void* arraylist_iterator_next(id self) {
    list_iterator itr = cast(list_iterator, self);
    assert(itr->has_next(itr));
    arraylist al = cast(arraylist, itr->host);
    itr->change = 1;
    return al->elements[itr->cursor++];
}

void arraylist_iterator_remove(id self) {
    list_iterator itr = cast(list_iterator, self);
    assert(itr->change != 0);
    arraylist al = (arraylist) (itr->host);

    if (itr->change > 0) {
        al->remove_at(al, --itr->cursor);
    } else {
        al->remove_at(al, itr->cursor);
    }
    itr->change = 0;
}

/* List iterator functions */
void arraylist_list_iterator_add(id self, void* user_data) {
    list_iterator itr = cast(list_iterator, self);
    assert(itr->change != 0);
    arraylist al = cast(arraylist, itr->has_next);
    // TODO document
    al->add_at(al, itr->cursor++, user_data);
    itr->change = 0;
}

void arraylist_list_iterator_set(id self, void* user_data) {
    list_iterator itr = cast(list_iterator, self);
    assert(itr->change != 0);
    arraylist al = cast(arraylist, itr->host);
    if (itr->change > 0) {
        al->set(al, itr->cursor - 1, user_data);
    } else {
        al->set(al, itr->cursor, user_data);
    }
}

void* arraylist_list_iterator_previous(id self) {
    list_iterator itr = cast(list_iterator, self);
    assert(itr->has_previous(itr));
    arraylist al = cast(arraylist, itr->host);
    itr->change = -1;
    return al->elements[--(itr->cursor)];
}