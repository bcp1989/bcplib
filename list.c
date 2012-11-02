#include "list.h"
static bool list_remove(id, void*);
static void* list_remove_at(id, size_t);
static bool list_contains(id, void*);
static size_t list_index_of(id, void*);
static size_t list_last_index_of(id, void*);

inline
void list_init(id obj, comparator cmp,
        collection_add_t c_add,
        collection_add_all_t c_add_all,
        collection_remove_t c_remove,
        collection_remove_all_t c_remove_all,
        collection_clear_t c_clear,
        collection_size_t c_size,
        collection_is_empty_t c_is_empty,
        collection_contains_t c_contains,
        collection_contains_all_t c_contains_all,
        // list functions
        list_add_at_t add_at,
        list_get_t get,
        list_set_t set,
        list_remove_at_t remove_at,
        list_index_of_t index_of,
        list_last_index_of_t last_index_of) {
    
    list l = (list) obj;
    assert(obj != NULL && get != NULL && add_at != NULL && set != NULL);
    assert(c_remove != NULL || remove_at != NULL);
    
    c_contains = c_contains == NULL ? list_contains : c_contains;
    c_remove = c_remove == NULL ? list_remove : c_remove;    
    collection_init(l, cmp, c_add, c_add_all, c_remove, c_remove_all, c_clear,
            c_size, c_is_empty, c_contains, c_contains_all);
    l->index_of = index_of == NULL ? list_index_of : index_of;
    l->last_index_of = last_index_of == NULL ? 
        list_last_index_of : last_index_of;
    l->remove_at = remove_at == NULL ? list_remove_at : remove_at;
    l->add_at = add_at;
    l->get = get;
    l->set = set;
}

static
bool list_remove(id obj, void* user_data) {
    list l = (list) obj;
    assert(obj != NULL);
    
    size_t idx = l->index_of(l, user_data);
    if (idx < 0) {
        return false;
    }
    //NOTE only remove once!
    l->remove_at(l, idx);
    return true;
}

static
void* list_remove_at(id obj, size_t idx) {
    list l = (list) obj;
    assert(obj != NULL && check_index_range(l->size(l), idx));

    void* user_data = l->get(l, idx);
    // NOTE haven't process the return value
    l->remove(l, user_data);
    return user_data;
}

static
bool list_contains(id obj, void* user_data) {
    list l = (list) obj;
    assert(obj != NULL);
    return l->index_of(l, user_data) >= 0;
}

static
size_t list_index_of(id obj, void* user_data) {
    list l = (list) obj;
    assert(obj != NULL);
    size_t i = 0, len = l->size(l);
    void* p = NULL;
    for (i = 0; i < len; ++i) {
        p = l->get(l, i);
        if (l->compare(p, user_data) == 0) {
            return i;
        }
    }
    return -1;
}

static
size_t list_last_index_of(id obj, void* user_data) {
    list l = (list) obj;
    assert(obj != NULL);
    size_t i = 0, len = l->size(l);
    void* p = NULL;
    for (i = len - 1; i >= 0; --i) {
        p = l->get(l, i);
        if (l->compare(p, user_data) == 0) {
            return i;
        }
    }
    return -1;
}