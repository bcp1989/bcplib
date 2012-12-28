#include "linkedlist.h"

INIT_CLASS(linkedlist, list, TYPE_NORMAL_CLASS);
INIT_CLASS(linkedlist_list_iterator, list_iterator, TYPE_NORMAL_CLASS);
// foreach
#define LL_FOREACH_FORWARD(elem, ll) \
        for (elem = first_node(ll); elem != NULL; elem = next_node(ll, elem))
#define LL_FOREACH_BACKWARD(elem, ll) \
        for (elem = last_node(ll); elem != NULL; elem = prev_node(ll, elem))

// utilities functions
static inline linkedlist_node new_node(linkedlist_node, linkedlist_node, void*);
static inline void insert_before(linkedlist, linkedlist_node, void*);
static inline void insert_after(linkedlist, linkedlist_node, void*);
static inline linkedlist_node prev_node(linkedlist, linkedlist_node);
static inline linkedlist_node next_node(linkedlist, linkedlist_node);
static inline linkedlist_node first_node(linkedlist);
static inline linkedlist_node last_node(linkedlist);
static inline void remove_node(linkedlist, linkedlist_node);
static linkedlist_node index_of_node(linkedlist, void*);
//static linkedlist_node last_index_of_node(linkedlist, void*);
static linkedlist_node locate_node(linkedlist, size_t);

/* init, finalize, creation, destruction */
inline
void linkedlist_init(id obj) {
    linkedlist ll = cast(linkedlist, obj);
    // call super.init
    list_init(ll);
    // init. linked list functions
    ll->linkedlist_size = 0;
    ll->head = new_node(NULL, NULL, NULL);
    ll->head->prev = ll->head;
    ll->head->next = ll->head;
    ll->append = linkedlist_append;
    ll->prepend = linkedlist_prepend;
    ll->first = linkedlist_first;
    ll->last = linkedlist_last;
    ll->remove_first = linkedlist_remove_first;
    ll->remove_last = linkedlist_remove_last;
    // init. list functions
    ll->add_at = linkedlist_add_at;
    ll->get = linkedlist_get;
    ll->set = linkedlist_set;
    ll->remove_at = linkedlist_remove_at;
    ll->index_of = linkedlist_index_of;
    ll->last_index_of = linkedlist_last_index_of;
    // init. collection functions
    ll->add = linkedlist_add;
    ll->remove = linkedlist_remove;
    ll->clear = linkedlist_clear;
    ll->size = linkedlist_size;
    // init. list iterator interface
    ll->create_list_iterator = linkedlist_create_list_iterator;
    // init object
    ll->destroy = linkedlist_destroy;
}

inline
void linkedlist_finalize(id obj) {
    linkedlist ll = cast(linkedlist, obj);
    // call super.finalize
    list_finalize(ll);
    bcplib_free(ll->head);
}

linkedlist linkedlist_create_by_comparator(comparator cmp) {
    assert(cmp != NULL);
    linkedlist ll = malloc_object(linkedlist);
    linkedlist_init(ll);
    ll->compare = cmp;
    return ll;
}

linkedlist linkedlist_create() {
    return linkedlist_create_by_comparator(collection_compare);
}

void linkedlist_destroy(id obj) {
    linkedlist ll = cast(linkedlist, obj);
    linkedlist_finalize(ll);
    bcplib_free(ll);
}

/* Utilities */
static inline
linkedlist_node new_node(linkedlist_node prev, linkedlist_node next, void* data) {
    linkedlist_node node = (linkedlist_node) bcplib_malloc(
            sizeof (linkedlist_node_t));
    assert (node != NULL);
    node->data = data;
    node->prev = prev;
    node->next = next;
    if (prev != NULL)
        prev->next = node;
    if (next != NULL)
        next->prev = node;
    return node;
}

static inline
void insert_before(linkedlist ll, linkedlist_node org, void* data) {
    new_node(org->prev, org, data);
    ++ll->linkedlist_size;
}

static inline
void insert_after(linkedlist ll, linkedlist_node org, void* data) {
    new_node(org, org->next, data);
    ++ll->linkedlist_size;
}

static inline
linkedlist_node prev_node(linkedlist ll, linkedlist_node node) {
    return node->prev == ll->head ? NULL : node->prev;
}

static inline
linkedlist_node next_node(linkedlist ll, linkedlist_node node) {
    return node->next == ll->head ? NULL : node->next;
}

static inline
linkedlist_node first_node(linkedlist ll) {
    return next_node(ll, ll->head);
}

static inline
linkedlist_node last_node(linkedlist ll) {
    return prev_node(ll, ll->head);
}

static inline
void remove_node(linkedlist ll, linkedlist_node node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    bcplib_free(node);
    --ll->linkedlist_size;
}

static
linkedlist_node index_of_node(linkedlist ll, void* data) {
    linkedlist_node node = NULL;
    void* tmp = NULL;

    LL_FOREACH_FORWARD(node, ll) {
        tmp = node->data;
        if (ll->compare(tmp, data) == 0) {
            return node;
        }
    }
    return NULL;
}

//static
//linkedlist_node last_index_of_node(linkedlist ll, void* data) {
//    linkedlist_node node = NULL;
//    void* tmp = NULL;
//
//    LL_FOREACH_BACKWARD(node, ll) {
//        tmp = node->data;
//        if (ll->compare(tmp, data) == 0) {
//            return node;
//        }
//    }
//    return NULL;
//}

static
linkedlist_node locate_node(linkedlist ll, size_t idx) {
    check_index_range(idx, 0, ll->size(ll));
    size_t count = 0;
    linkedlist_node node = NULL;

    LL_FOREACH_FORWARD(node, ll) {
        if ((count++) == idx) break;
    }
    return node;
}

/* Linked List */
void linkedlist_append(id obj, void* data) {
    linkedlist ll = cast(linkedlist, obj);
    insert_before(ll, ll->head, data);
}

void linkedlist_prepend(id obj, void* data) {
    linkedlist ll = cast(linkedlist, obj);
    insert_after(ll, ll->head, data);
}

void* linkedlist_first(id obj) {
    linkedlist ll = cast(linkedlist, obj);
    linkedlist_node node = next_node(ll, ll->head);
    assert(node != NULL);
    return node->data;
}

void* linkedlist_last(id obj) {
    linkedlist ll = cast(linkedlist, obj);
    linkedlist_node node = prev_node(ll, ll->head);
    assert(node != NULL);
    return node->data;
}

void* linkedlist_remove_first(id obj) {
    linkedlist ll = cast(linkedlist, obj);
    linkedlist_node node = next_node(ll, ll->head);
    assert(node != NULL);
    void* data = node->data;
    remove_node(ll, node);
    return data;
}

void* linkedlist_remove_last(id obj) {
    linkedlist ll = cast(linkedlist, obj);
    linkedlist_node node = prev_node(ll, ll->head);
    assert(node != NULL);
    void* data = node->data;
    remove_node(ll, node);
    return data;
}

/* List */
void linkedlist_add_at(id obj, size_t idx, void* data) {
    linkedlist ll = cast(linkedlist, obj);
    if (idx == 0) {
        ll->prepend(ll, data);
    } else if (idx == ll->size(ll)) {
        ll->append(ll, data);
    } else {
        insert_before(ll, locate_node(ll, idx), data);
    }
}

void* linkedlist_get(id obj, size_t idx) {
    linkedlist ll = cast(linkedlist, obj);
    return locate_node(ll, idx)->data;
}

void* linkedlist_set(id obj, size_t idx, void* data) {
    linkedlist ll = cast(linkedlist, obj);
    linkedlist_node node = locate_node(ll, idx);
    void* old_data = node->data;
    node->data = data;
    return old_data;
}

void* linkedlist_remove_at(id obj, size_t idx) {
    linkedlist ll = cast(linkedlist, obj);
    linkedlist_node node = locate_node(ll, idx);
    void* old_data = node->data;
    remove_node(ll, node);
    return old_data;
}

size_t linkedlist_index_of(id obj, void* data) {
    linkedlist ll = cast(linkedlist, obj);
    linkedlist_node node = NULL;
    size_t count = 0;
    void* tmp = NULL;

    LL_FOREACH_FORWARD(node, ll) {
        tmp = node->data;
        if (ll->compare(tmp, data) == 0) {
            return count;
        }
        ++count;
    }
    return -1;
}

size_t linkedlist_last_index_of(id obj, void* data) {
    linkedlist ll = cast(linkedlist, obj);
    linkedlist_node node = NULL;
    size_t count = ll->size(ll) - 1;
    void* tmp = NULL;

    LL_FOREACH_BACKWARD(node, ll) {
        tmp = node->data;
        if (ll->compare(tmp, data) == 0) {
            return count;
        }
        --count;
    }
    return -1;
}

/* Collection */
bool linkedlist_add(id obj, void* data) {
    linkedlist ll = cast(linkedlist, obj);
    ll->append(ll, data);
    return true;
}

bool linkedlist_remove(id obj, void* data) {
    linkedlist ll = cast(linkedlist, obj);
    linkedlist_node node = index_of_node(ll, data);
    if (node == NULL) return false;
    remove_node(ll, node);
    return true;
}

void linkedlist_clear(id obj) {
    linkedlist ll = cast(linkedlist, obj);
    while (ll->linkedlist_size != 0) {
        remove_node(ll, next_node(ll, ll->head));
    }
}

size_t linkedlist_size(id obj) {
    linkedlist ll = cast(linkedlist, obj);
    return ll->linkedlist_size;
}

/* List iterator interface */
list_iterator linkedlist_create_list_iterator(id obj, size_t idx) {
    linkedlist ll = cast(linkedlist, obj);
    check_index_range(idx, 0, ll->linkedlist_size + 1);
    list_iterator itr = malloc_object(linkedlist_list_iterator);
    list_iterator_init(itr, ll,
            idx == ll->linkedlist_size ? ll->head : locate_node(ll, idx));
    // init object
    itr->destroy = linkedlist_list_iterator_destroy;
    // init list iterator functions
    itr->add = linkedlist_list_iterator_add;
    itr->set = linkedlist_list_iterator_set;
    itr->previous = linkedlist_list_iterator_previous;
    itr->cursor = idx;
    // init iterator functions
    itr->next = linkedlist_iterator_next;
    itr->remove = linkedlist_iterator_remove;
    return itr;
}

/* Iterator functions */
void* linkedlist_iterator_next(id obj) {
    list_iterator itr = cast(list_iterator, obj);
    assert(itr->has_next(itr));
    // test
    assert(itr->aux != NULL);
    linkedlist_node current_node = (linkedlist_node)itr->aux;
    itr->aux = current_node->next;
    ++itr->cursor;
    itr->change = 1;
    return current_node->data;
}

void linkedlist_iterator_remove(id obj) {
    list_iterator itr = cast(list_iterator, obj);
    assert(itr->change != 0);
    linkedlist ll = cast(linkedlist, itr->host);
    // test
    assert(itr->aux != NULL);
    linkedlist_node current_node = (linkedlist_node)itr->aux;
    if (itr->change > 0) {
        --itr->cursor;
        remove_node(ll, prev_node(ll, current_node));
    } else {
        linkedlist_node tbd = current_node;
        current_node = next_node(ll, current_node);
        remove_node(ll, tbd);
    }
    itr->change = 0;
}

/* List iterator */
void linkedlist_list_iterator_destroy(id obj) {
    list_iterator itr = cast(list_iterator, obj);
    bcplib_free(itr);
}

void linkedlist_list_iterator_add(id obj, void* data) {
    list_iterator itr = cast(list_iterator, obj);
    assert(itr->change != 0);
    linkedlist ll = cast(linkedlist, itr->host);
    linkedlist_node current_node = (linkedlist_node)itr->aux;
    insert_before(ll, current_node, data);
    ++itr->cursor;
    itr->change = 0;
}

void linkedlist_list_iterator_set(id obj, void* data) {
    list_iterator itr = cast(list_iterator, obj);
    assert(itr->change != 0);
    linkedlist ll = cast(linkedlist, itr->host);
    linkedlist_node current_node = (linkedlist_node)itr->aux;
    linkedlist_node tbs = itr->change > 0 ? prev_node(ll, current_node)
            : current_node;
    tbs->data = data;
}

void* linkedlist_list_iterator_previous(id obj) {
    list_iterator itr = cast(list_iterator, obj);
    assert(itr->has_previous);
    --itr->cursor;
    linkedlist_node current_node = (linkedlist_node)itr->aux;
    current_node = current_node->prev;
    itr->aux = current_node;
    itr->change = -1;
    return current_node->data;
}