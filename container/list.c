#include "list.h"

inline
void check_index_range(size_t idx, size_t from, size_t to) {
    assert(idx < to && idx >= from);
}

INIT_CLASS(list, collection, TYPE_ABSTRACT_CLASS);
// initializer
BEGIN_IMPL_INITIALIZER(list)
init_super(flag);
self->add = list_add;
self->index_of = list_index_of;
self->last_index_of = list_last_index_of;
self->create_iterator = list_create_iterator;

END_IMPL_INITIALIZER(list)

// finalizer
BEGIN_IMPL_FINALIZER(list)
// do nothing
END_IMPL_FINALIZER(list)

/* Default functions */
iterator list_create_iterator(id obj) {
    list l = (list) obj;
    assert(l != NULL);
    return (iterator) l->create_list_iterator(l, 0);
}

bool list_add(id obj, void* user_data) {
    list l = (list) obj;
    assert(obj != NULL);
    l->add_at(l, l->size(l), user_data);
    return true;
}

size_t list_index_of(id obj, void* user_data) {
    list l = (list) obj;
    assert(obj != NULL);
    list_iterator itr = l->create_list_iterator(l, 0);
    while (itr->has_next(itr)) {
        if (l->compare(itr->next(itr), user_data) == 0) {
            size_t ret = itr->previous_index(itr);
            destroy(itr);
            return ret;
        }
    }
    destroy(itr);
    return -1;
}

size_t list_last_index_of(id obj, void* user_data) {
    list l = (list) obj;
    assert(obj != NULL);
    list_iterator itr = l->create_list_iterator(l, l->size(l));
    while (itr->has_previous(itr)) {
        if (l->compare(itr->previous(itr), user_data) == 0) {
            size_t ret = itr->next_index(itr);
            destroy(itr);
            return ret;
        }
    }
    destroy(itr);
    return -1;
}