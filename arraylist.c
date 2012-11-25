#include "arraylist.h"

#define DEFAULT_SIZE 10
#define MAX_CAPACITY (((size_t) - 1) - 8)


/* Candidate functions */
static void arraylist_add_all_by_data(id obj, void** user_data, size_t size);

inline
void arraylist_init(id obj) {
    arraylist_init_by_size(obj, DEFAULT_SIZE);
}

inline
void arraylist_init_by_size(id obj, size_t size) {
    arraylist al = safe_cast(arraylist, obj);
    assert(size > 0);
    // call super.init
    list_init(al);
    // init. collection functions
    al->remove = arraylist_remove;
    al->clear = arraylist_clear;
    al->size = arraylist_size;
    al->is_empty = arraylist_is_empty;
    al->contains = arraylist_contains;
    // init. list functions
    al->add_at = arraylist_add_at;
    al->get = arraylist_get;
    al->set = arraylist_set;
    al->remove_at = arraylist_remove_at;
    al->index_of = arraylist_index_of;
    al->last_index_of = arraylist_last_index_of;
    // init. array list functions
    al->elements = (void**) bcplib_malloc(sizeof (void*) * size);
    al->arraylist_size = 0;
    al->capacity = size;
    al->trim_to_size = arraylis_trim_to_size;
    al->ensure_capacity = arraylist_ensure_capacity;
    // init. list iterator interface
    al->create_list_iterator = arraylist_create_list_iterator;
    al->destroy_list_iterator = arraylist_destroy_list_iterator;
}

inline
void arraylist_finalize(id obj) {
    arraylist al = safe_cast(arraylist, obj);
    // call super.finalize
    list_finalize(al);
    bcplib_free(al->elements);
    al->elements = NULL;
}

arraylist arraylist_create() {
    return arraylist_create_by_size(DEFAULT_SIZE);
}

arraylist arraylist_create_by_size(size_t size) {
    return arraylist_create_by_size_comparator(size, collection_compare);
}

arraylist arraylist_create_by_comparator(comparator cmp) {
    return arraylist_create_by_size_comparator(DEFAULT_SIZE, cmp);
}

arraylist arraylist_create_by_size_comparator(size_t size, comparator cmp) {
    assert (cmp != NULL);
    arraylist al = (arraylist) bcplib_malloc(sizeof (arraylist_t));
    arraylist_init_by_size(al, size);
    al->compare = cmp;
    return al;
}

arraylist arraylist_create_by_data(void** init_data, size_t size) {
    arraylist al = arraylist_create_by_size(size);
    arraylist_add_all_by_data(al, init_data, size);
    return al;
}

arraylist arraylist_create_by_collection(id obj) {
    collection c = safe_cast(collection, obj);
    arraylist al = arraylist_create_by_size(c->size(c));
    al->add_all(al, c);
    return al;
}

arraylist arraylist_destroy(arraylist obj) {
    arraylist_finalize(obj);
    bcplib_free(obj);
    return NULL;
}

/* Candidate functions */
static
void arraylist_add_all_by_data(id obj, void** user_data, size_t size) {
    arraylist al = safe_cast(arraylist, obj);
    assert(size > 0);
    al->ensure_capacity(al, al->arraylist_size + size);
    size_t i = 0, len = al->arraylist_size + size;
    for (i = al->arraylist_size; i < len; ++i) {
        al->elements[i] = user_data[i - al->arraylist_size];
    }
    al->arraylist_size += size;
}

/* Collection functions */
bool arraylist_remove(id obj, void* user_data) {
    arraylist al = safe_cast(arraylist, obj);
    size_t idx = al->index_of(al, user_data);
    if (idx >= 0) {
        al->remove_at(al, idx);
        return true;
    }
    return false;
}

void arraylist_clear(id obj) {
    arraylist al = safe_cast(arraylist, obj);
    size_t i = 0;
    for (i = 0; i < al->arraylist_size; ++i) {
        al->elements[i] = NULL;
    }
    al->arraylist_size = 0;
}

size_t arraylist_size(id obj) {
    arraylist al = safe_cast(arraylist, obj);
    return al->arraylist_size;
}

bool arraylist_is_empty(id obj) {
    arraylist al = safe_cast(arraylist, obj);
    return al->arraylist_size == 0;
}

bool arraylist_contains(id obj, void* user_data) {
    arraylist al = safe_cast(arraylist, obj);
    return al->index_of(al, user_data) >= 0;
}

/* List functions */
void arraylist_add_at(id obj, size_t idx, void* user_data) {
    arraylist al = safe_cast(arraylist, obj);
    check_index_range(idx, 0, al->arraylist_size + 1);
    al->ensure_capacity(al, al->arraylist_size + 1);
    size_t i = 0;
    for (i = al->arraylist_size; i > idx; --i) {
        al->elements[i] = al->elements[i - 1];
    }
    al->elements[idx] = user_data;
    ++(al->arraylist_size);
}

void* arraylist_get(id obj, size_t idx) {
    arraylist al = safe_cast(arraylist, obj);
    check_index_range(idx, 0, al->arraylist_size);
    return al->elements[idx];
}

void * arraylist_set(id obj, size_t idx, void* user_data) {
    arraylist al = safe_cast(arraylist, obj);
    check_index_range(idx, 0, al->arraylist_size);
    void* ret = al->elements[idx];
    al->elements[idx] = user_data;
    return ret;
}

void* arraylist_remove_at(id obj, size_t idx) {
    arraylist al = safe_cast(arraylist, obj);
    check_index_range(idx, 0, al->arraylist_size);
    void* ret = al->elements[idx];
    size_t i = idx;
    for (i = idx; i < al->arraylist_size - 1; ++i) {
        al->elements[i] = al->elements[i + 1];
    }
    --(al->arraylist_size);
    return ret;
}

size_t arraylist_index_of(id obj, void* user_data) {
    arraylist al = safe_cast(arraylist, obj);
    size_t i = 0;
    for (i = 0; i < al->arraylist_size; ++i) {
        if (al->compare(al->elements[i], user_data) == 0) {
            return i;
        }
    }
    return -1;
}

size_t arraylist_last_index_of(id obj, void* user_data) {
    arraylist al = safe_cast(arraylist, obj);
    size_t i = 0;
    for (i = al->arraylist_size - 1; i >= 0; --i) {
        if (al->compare(al->elements[i], user_data) == 0) {
            return i;
        }
    }
    return -1;
}

/* List iterator interface */
list_iterator arraylist_create_list_iterator(id obj, size_t idx) {
    arraylist al = safe_cast(arraylist, obj);
    check_index_range(idx, 0, al->arraylist_size + 1);
    list_iterator itr = (list_iterator) bcplib_malloc(sizeof (list_iterator_t));
    list_iterator_init(itr, al, NULL);
    // init iterator functions
    itr->next = arraylist_iterator_next;
    itr->remove = arraylist_iterator_remove;
    // init list iterator functions
    itr->add = arraylist_list_iterator_add;
    itr->set = arraylist_list_iterator_set;
    itr->previous = arraylist_list_iterator_previous;
    itr->cursor = idx;
    return itr;
}

list_iterator arraylist_destroy_list_iterator(id obj, id itr) {
    list_iterator list_itr = safe_cast(list_iterator, itr);
    bcplib_free(list_itr->aux);
    return list_destroy_list_iterator(obj, itr);
}

/* Array list function */
void arraylis_trim_to_size(id obj) {
    arraylist al = safe_cast(arraylist, obj);
    // TODO safe re-alloc!
    void** new_elements = (void**) bcplib_realloc(al->elements, al->arraylist_size);
    if (new_elements == NULL) {
        return;
    }
    bcplib_free(al->elements);
    al->elements = new_elements;
    al->capacity = al->arraylist_size;
}

void arraylist_ensure_capacity(id obj, size_t new_cap) {
    arraylist al = safe_cast(arraylist, obj);
    assert(new_cap <= MAX_CAPACITY);
    if (new_cap <= al->capacity) {
        return;
    } else {
        size_t cap_inc = (al->capacity >> 1);
        size_t times = 0;
        while ((al->capacity + cap_inc) < new_cap) {
            if (times % 2 == 0) {
                cap_inc <<= 1;
            } else {
                cap_inc += (cap_inc << 1);
            }
            // overflow
            if (cap_inc < 0) {
                cap_inc = new_cap - al->capacity;
            }
            ++times;
        }
        //void** new_elements = (void**) bcplib_realloc(al->elements,
        //        cap_inc + al->capacity);
        void** new_elements = (void**) bcplib_malloc(
                sizeof (void *) * (cap_inc + al->capacity));
        size_t i = 0;
        // TODO extract to system copy
        for (i = 0; i < al->capacity; ++i) {
            new_elements[i] = al->elements[i];
        }

        // TODO optimize
        assert(new_elements != NULL);
        bcplib_free(al->elements);
        al->elements = new_elements;
        al->capacity += cap_inc;
    }
}

/* Iterator functions */

void* arraylist_iterator_next(id obj) {
    list_iterator itr = safe_cast(list_iterator, obj);
    assert(itr->has_next(itr));
    arraylist al = safe_cast(arraylist, itr->host);
    itr->change = 1;
    return al->elements[itr->cursor++];
}

void arraylist_iterator_remove(id obj) {
    list_iterator itr = safe_cast(list_iterator, obj);
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
void arraylist_list_iterator_add(id obj, void* user_data) {
    list_iterator itr = safe_cast(list_iterator, obj);
    assert (itr->change != 0);
    arraylist al = safe_cast(arraylist, itr->has_next);
    // TODO document
    al->add_at(al, itr->cursor++, user_data);
    itr->change = 0;
}

void arraylist_list_iterator_set(id obj, void* user_data) {
    list_iterator itr = safe_cast(list_iterator, obj);
    assert (itr->change != 0);
    arraylist al = safe_cast(arraylist, itr->host);
    if (itr->change > 0) {
        al->set(al, itr->cursor - 1, user_data);
    } else {
        al->set(al, itr->cursor, user_data);
    }
}

void* arraylist_list_iterator_previous(id obj) {
    list_iterator itr = safe_cast(list_iterator, obj);
    assert(itr->has_previous(itr));
    arraylist al = safe_cast(arraylist, itr->host);
    itr->change = -1;
    return al->elements[--(itr->cursor)];
}