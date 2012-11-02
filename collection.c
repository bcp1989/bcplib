#include "collection.h"
#include <stdlib.h>

static bool collection_is_empty(id);
static bool collection_add_all(id, id);
static bool collection_remove_all(id, id);
static bool collection_contains_all(id, id);
static bool collection_compare(void*, void*);

inline
void collection_init(id obj, comparator cmp,
        collection_add_t add,
        collection_add_all_t add_all,
        collection_remove_t remove,
        collection_remove_all_t remove_all,
        collection_clear_t clear,
        collection_size_t size,
        collection_is_empty_t is_empty,
        collection_contains_t contains,
        collection_contains_all_t contains_all) {

    assert(obj != NULL && add != NULL && remove != NULL &&
            remove != NULL && clear != NULL && size != NULL &&
            contains != NULL);

    collection c = (collection) obj;
    c->add = add;
    c->remove = remove;
    c->clear = clear;
    c->size = size;
    c->contains = contains;
    
    c->compare = cmp == NULL ? collection_compare : cmp;
    c->add_all = add_all == NULL ? collection_add_all : add_all;
    c->remove_all = remove_all == NULL ? collection_remove_all : remove_all;
    c->contains_all = contains_all == NULL ?
            collection_contains_all : contains_all;
    c->is_empty = is_empty == NULL ? collection_is_empty : is_empty;
}

static
bool collection_compare(void* p1, void* p2) {
    return p1 == p2;
}

static
bool collection_is_empty(id obj) {
    assert(obj != NULL);
    collection c = (collection) obj;
    return c->size(c) == 0;
}

static
bool collection_add_all(id obj1, id obj2) {
    COLLECTION_a2b_SUB_CALL(collection, obj1, obj2, add);
}

static
bool collection_remove_all(id obj1, id obj2) {
    COLLECTION_a2b_SUB_CALL(collection, obj1, obj2, remove);
}

static
bool collection_contains_all(id obj1, id obj2) {
    COLLECTION_a2b_SUB_CALL(collection, obj1, obj2, contains);
}
