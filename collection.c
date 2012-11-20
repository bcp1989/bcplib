#include "collection.h"
#include <stdlib.h>

static bool collection_is_empty(id);
static bool collection_add_all(id, id);
static bool collection_remove_all(id, id);
static bool collection_contains_all(id, id);
static bool collection_compare(void*, void*);
static bool collection_remove(id, void*);
static bool collection_contains(id, void*);

inline
void collection_init(id obj) {
    collection c = (collection) obj;
    object_init(obj);
    c->remove = collection_remove;
    c->contains = collection_contains;
    c->compare = collection_compare;
    c->add_all = collection_add_all;
    c->remove_all = collection_remove_all;
    c->contains_all = collection_contains_all;
    c->is_empty = collection_is_empty;
}

inline
void collection_finalize(id obj) {
    object_finalize(obj);
    // nothing to finalize
}

/* Default functions */
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
bool collection_remove(id obj, void* user_data) {
    assert(obj != NULL);
    collection c = (collection) obj;
    iterator itr = c->create_iterator(c);
    while (itr->has_next(itr)) {
        if (!c->compare(itr->next(itr), user_data)) {
            itr->remove(itr);
            c->destory_iterator(c, itr);
            return true;
        }
    }
    c->destory_iterator(c, itr);
    return false;
}

static
bool collection_contains(id obj, void* user_data) {
    assert(obj != NULL);
    collection c = (collection) obj;
    iterator itr = c->create_iterator(c);
    while (itr->has_next(itr)) {
        if (!c->compare(itr->next(itr), user_data)) {
            c->destory_iterator(c, itr);
            return true;
        }
    }
    c->destory_iterator(c, itr);
    return false;
}

static
bool collection_add_all(id obj1, id obj2) {
    assert(obj1 != NULL && obj2 != NULL);
    collection c1 = (collection) obj1;
    collection c2 = (collection) obj2;
    iterator c2itr = c2->create_iterator(c2);
    bool changed = false;
    while (c2itr->has_next(c2itr)) {
        changed = changed || c1->add(c1, c2itr->next(c2itr));
    }
    c2->destory_iterator(c2, c2itr);
    return changed;
}

static
bool collection_remove_all(id obj1, id obj2) {
    assert(obj1 != NULL && obj2 != NULL);
    collection c1 = (collection) obj1;
    collection c2 = (collection) obj2;
    iterator c1itr = c1->create_iterator(c1);
    bool changed = false;
    while (c1itr->has_next(c1itr)) {
        if (c2->contains(c2, c1itr->next(c1itr))) {
            c1itr->remove(c1itr);
            changed = true;
        }
    }
    c1->destory_iterator(c1, c1itr);
    return changed;
}

static
bool collection_contains_all(id obj1, id obj2) {
    assert(obj1 != NULL && obj2 != NULL);
    collection c1 = (collection) obj1;
    collection c2 = (collection) obj2;
    iterator c2itr = c2->create_iterator(c2);
    while (c2itr->has_next(c2itr)) {
        if (!c1->contains(c1, c2itr->next(c2itr))) {
            c2->destory_iterator(c2, c2itr);
            return false;
        }
    }
    c2->destory_iterator(c2, c2itr);
    return true;
}
