#include "collection.h"
#include <stdlib.h>

INIT_CLASS(collection, object, TYPE_ABSTRACT_CLASS);

BEGIN_IMPL_INITIALIZER(collection)
init_super(flag);
self->remove = collection_remove;
self->contains = collection_contains;
self->add_all = collection_add_all;
self->remove_all = collection_remove_all;
self->contains_all = collection_contains_all;
self->is_empty = collection_is_empty;
if(bit_test(flag, COLLECTION_INIT_COMPARATOR)) {
    comparator cmp = next_arg(comparator);
    assert(cmp != NULL);
    self->compare = cmp;
} else {
    self->compare = collection_compare;
}
END_IMPL_INITIALIZER(collection)

BEGIN_IMPL_FINALIZER(collection)
// do nothing
END_IMPL_FINALIZER(collection)


/* Default functions */
bool collection_compare(void* p1, void* p2) {
    return !(p1 == p2);
}

bool collection_is_empty(id self) {
    assert(self != NULL);
    collection c = (collection) self;
    return c->size(c) == 0;
}

bool collection_remove(id self, void* user_data) {
    assert(self != NULL);
    collection c = (collection) self;
    iterator itr = c->create_iterator(c);
    while (itr->has_next(itr)) {
        if (!c->compare(itr->next(itr), user_data)) {
            itr->remove(itr);
            destroy(itr);
            return true;
        }
    }
    destroy(itr);
    return false;
}

bool collection_contains(id self, void* user_data) {
    assert(self != NULL);
    collection c = (collection) self;
    iterator itr = c->create_iterator(c);
    while (itr->has_next(itr)) {
        if (!c->compare(itr->next(itr), user_data)) {
            destroy(itr);
            return true;
        }
    }
    destroy(itr);
    return false;
}

bool collection_add_all(id self, id other) {
    assert(self != NULL && other != NULL);
    collection c1 = (collection) self;
    collection c2 = (collection) other;
    iterator c2itr = c2->create_iterator(c2);
    bool changed = false;
    while (c2itr->has_next(c2itr)) {
        changed = changed || c1->add(c1, c2itr->next(c2itr));
    }
    destroy(c2itr);
    return changed;
}

bool collection_remove_all(id self, id other) {
    assert(self != NULL && other != NULL);
    collection c1 = (collection) self;
    collection c2 = (collection) other;
    iterator c1itr = c1->create_iterator(c1);
    bool changed = false;
    while (c1itr->has_next(c1itr)) {
        if (c2->contains(c2, c1itr->next(c1itr))) {
            c1itr->remove(c1itr);
            changed = true;
        }
    }
    destroy(c1itr);
    return changed;
}

bool collection_contains_all(id self, id other) {
    assert(self != NULL && other != NULL);
    collection c1 = (collection) self;
    collection c2 = (collection) other;
    iterator c2itr = c2->create_iterator(c2);
    while (c2itr->has_next(c2itr)) {
        if (!c1->contains(c1, c2itr->next(c2itr))) {
            destroy(c2itr);
            return false;
        }
    }
    destroy(c2itr);
    return true;
}
