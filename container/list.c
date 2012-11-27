#include "list.h"

INIT_CLASS(list, collection, TYPE_ABSTRACT_CLASS);

inline
void check_index_range(size_t idx, size_t from, size_t to) {
    assert(idx < to && idx >= from);
}

inline
void list_init(id obj) {
    list l = (list) obj;
    collection_init(l);
    l->add = list_add;
    l->index_of = list_index_of;
    l->last_index_of = list_last_index_of;
    l->create_iterator = list_create_iterator;
}

inline
void list_finalize(id obj) {
    collection_finalize(obj);
    // nothing to finalize
}

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