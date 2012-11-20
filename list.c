#include "list.h"
static bool list_add(id obj, void* user_data);
static size_t list_index_of(id, void*);
static size_t list_last_index_of(id, void*);
static iterator list_create_iterator(id);
static iterator list_destory_iterator(id, id);
static list_iterator list_destory_list_iterator(id, id);

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
    l->destory_iterator = list_destory_iterator;
    l->destory_list_iterator = list_destory_list_iterator;
}

inline
void list_finalize(id obj) {
    collection_finalize(obj);
    // nothing to finalize
}

/* Default functions */

static
iterator list_create_iterator(id obj) {
    list l = (list) obj;
    assert(l != NULL);
    return (iterator) l->create_list_iterator(l, 0);
}

static
iterator list_destory_iterator(id obj, id itr) {
    list l = (list) obj;
    assert(l != NULL);
    // EXPERIMENT Can I cast a NULL pointer to any type in common compiler?
    return (iterator) l->destory_list_iterator(l, itr);
}


static
list_iterator list_destory_list_iterator(id obj, id itr) {
    list_iterator list_itr = (list_iterator) safe_cast(list_iterator, itr);
    list_iterator_finalize(list_itr);
    bcplib_free(list_itr);
    return NULL;
}


static
bool list_add(id obj, void* user_data) {
    list l = (list) obj;
    assert(obj != NULL);
    l->add_at(l, l->size(l), user_data);
    return true;
}

static
size_t list_index_of(id obj, void* user_data) {
    list l = (list) obj;
    assert(obj != NULL);
    list_iterator itr = l->create_list_iterator(l, 0);
    while (itr->has_next(itr)) {
        if (l->compare(itr->next(itr), user_data) == 0) {
            size_t ret = itr->previous_index(itr);
            l->destory_list_iterator(l, itr);
            return ret;
        }
    }
    l->destory_list_iterator(l, itr);
    return -1;
}

static
size_t list_last_index_of(id obj, void* user_data) {
    list l = (list) obj;
    assert(obj != NULL);
    list_iterator itr = l->create_list_iterator(l, l->size(l));
    while (itr->has_previous(itr)) {
        if (l->compare(itr->previous(itr), user_data) == 0) {
            size_t ret = itr->next_index(itr);
            l->destory_list_iterator(l, itr);
            return ret;
        }
    }
    l->destory_list_iterator(l, itr);
    return -1;
}