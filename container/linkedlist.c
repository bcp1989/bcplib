#include "linkedlist.h"
// init linkedlist class
INIT_CLASS(linkedlist, list, TYPE_NORMAL_CLASS);

// init linkedlist node class
INIT_CLASS(linkedlist_node, object, TYPE_NORMAL_CLASS);

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

/* Initializer and finalizer */
// Initializer of linkedlist
BEGIN_IMPL_INITIALIZER(linkedlist)
init_super(flag);
// init. linked list functions
self->_size = 0;
self->_head = new(linkedlist_node, INIT_DEFAULT, NULL, NULL, NULL);
self->_head->prev = self->_head;
self->_head->next = self->_head;
self->append = linkedlist_append;
self->prepend = linkedlist_prepend;
self->first = linkedlist_first;
self->last = linkedlist_last;
self->remove_first = linkedlist_remove_first;
self->remove_last = linkedlist_remove_last;
// init. list functions
self->add_at = linkedlist_add_at;
self->get = linkedlist_get;
self->set = linkedlist_set;
self->remove_at = linkedlist_remove_at;
self->index_of = linkedlist_index_of;
self->last_index_of = linkedlist_last_index_of;
// init. collection functions
self->add = linkedlist_add;
self->remove = linkedlist_remove;
self->clear = linkedlist_clear;
self->size = linkedlist_size;
// init. list iterator interface
self->create_list_iterator = linkedlist_create_list_iterator;
END_IMPL_INITIALIZER(linkedlist)

// Finalizer of linkedlist
BEGIN_IMPL_FINALIZER(linkedlist)
bcplib_free(self->_head);
self->_head = NULL;
END_IMPL_FINALIZER(linkedlist)

// Initializer of linkedlist node
BEGIN_IMPL_INITIALIZER(linkedlist_node)
init_super(flag);
linkedlist_node prev = next_arg(linkedlist_node);
linkedlist_node next = next_arg(linkedlist_node);
void* data = next_arg(void*);
self->data = data;
self->prev = prev;
self->next = next;
if (prev != NULL)
    prev->next = self;
if (next != NULL)
    next->prev = self;

END_IMPL_INITIALIZER(linkedlist_node)

// Finalizer of linkedlist node
BEGIN_IMPL_FINALIZER(linkedlist_node)
// do nothing
END_IMPL_FINALIZER(linkedlist_node)

// Finalizer of linkedlist node


/* Utilities */
static inline
void insert_before(linkedlist ll, linkedlist_node org, void* data) {
    new(linkedlist_node, INIT_DEFAULT, org->prev, org, data);
    ++ll->_size;
}

static inline
void insert_after(linkedlist ll, linkedlist_node org, void* data) {
    new(linkedlist_node, INIT_DEFAULT, org, org->next, data);
    ++ll->_size;
}

static inline
linkedlist_node prev_node(linkedlist ll, linkedlist_node node) {
    return node->prev == ll->_head ? NULL : node->prev;
}

static inline
linkedlist_node next_node(linkedlist ll, linkedlist_node node) {
    return node->next == ll->_head ? NULL : node->next;
}

static inline
linkedlist_node first_node(linkedlist ll) {
    return next_node(ll, ll->_head);
}

static inline
linkedlist_node last_node(linkedlist ll) {
    return prev_node(ll, ll->_head);
}

static inline
void remove_node(linkedlist ll, linkedlist_node node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    destroy(node);
    --ll->_size;
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
void linkedlist_append(id self, void* data) {
    linkedlist ll = cast(linkedlist, self);
    insert_before(ll, ll->_head, data);
}

void linkedlist_prepend(id self, void* data) {
    linkedlist ll = cast(linkedlist, self);
    insert_after(ll, ll->_head, data);
}

void* linkedlist_first(id self) {
    linkedlist ll = cast(linkedlist, self);
    linkedlist_node node = next_node(ll, ll->_head);
    assert(node != NULL);
    return node->data;
}

void* linkedlist_last(id self) {
    linkedlist ll = cast(linkedlist, self);
    linkedlist_node node = prev_node(ll, ll->_head);
    assert(node != NULL);
    return node->data;
}

void* linkedlist_remove_first(id self) {
    linkedlist ll = cast(linkedlist, self);
    linkedlist_node node = next_node(ll, ll->_head);
    assert(node != NULL);
    void* data = node->data;
    remove_node(ll, node);
    return data;
}

void* linkedlist_remove_last(id self) {
    linkedlist ll = cast(linkedlist, self);
    linkedlist_node node = prev_node(ll, ll->_head);
    assert(node != NULL);
    void* data = node->data;
    remove_node(ll, node);
    return data;
}

/* List */
void linkedlist_add_at(id self, size_t idx, void* data) {
    linkedlist ll = cast(linkedlist, self);
    if (idx == 0) {
        ll->prepend(ll, data);
    } else if (idx == ll->size(ll)) {
        ll->append(ll, data);
    } else {
        insert_before(ll, locate_node(ll, idx), data);
    }
}

void* linkedlist_get(id self, size_t idx) {
    linkedlist ll = cast(linkedlist, self);
    return locate_node(ll, idx)->data;
}

void* linkedlist_set(id self, size_t idx, void* data) {
    linkedlist ll = cast(linkedlist, self);
    linkedlist_node node = locate_node(ll, idx);
    void* old_data = node->data;
    node->data = data;
    return old_data;
}

void* linkedlist_remove_at(id self, size_t idx) {
    linkedlist ll = cast(linkedlist, self);
    linkedlist_node node = locate_node(ll, idx);
    void* old_data = node->data;
    remove_node(ll, node);
    return old_data;
}

size_t linkedlist_index_of(id self, void* data) {
    linkedlist ll = cast(linkedlist, self);
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

size_t linkedlist_last_index_of(id self, void* data) {
    linkedlist ll = cast(linkedlist, self);
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
bool linkedlist_add(id self, void* data) {
    linkedlist ll = cast(linkedlist, self);
    ll->append(ll, data);
    return true;
}

bool linkedlist_remove(id self, void* data) {
    linkedlist ll = cast(linkedlist, self);
    linkedlist_node node = index_of_node(ll, data);
    if (node == NULL) return false;
    remove_node(ll, node);
    return true;
}

void linkedlist_clear(id self) {
    linkedlist ll = cast(linkedlist, self);
    while (ll->_size != 0) {
        remove_node(ll, next_node(ll, ll->_head));
    }
}

size_t linkedlist_size(id self) {
    linkedlist ll = cast(linkedlist, self);
    return ll->_size;
}

/* List iterator interface */
INIT_CLASS(linkedlist_iterator, list_iterator, TYPE_NORMAL_CLASS);
BEGIN_IMPL_INITIALIZER(linkedlist_iterator)
init_super(flag);
// init list iterator functions
self->add = linkedlist_list_iterator_add;
self->set = linkedlist_list_iterator_set;
self->previous = linkedlist_list_iterator_previous;
self->cursor = next_arg(size_t);
// init iterator functions
self->next = linkedlist_iterator_next;
self->remove = linkedlist_iterator_remove;

END_IMPL_INITIALIZER(linkedlist_iterator)

BEGIN_IMPL_FINALIZER(linkedlist_iterator)
// do nothing
END_IMPL_FINALIZER(linkedlist_iterator)
list_iterator linkedlist_create_list_iterator(id self, size_t idx) {
    linkedlist ll = cast(linkedlist, self);
    check_index_range(idx, 0, ll->_size + 1);
    list_iterator itr = new(list_iterator, INIT_DEFAULT, ll,
            idx == ll->_size ? ll->_head : locate_node(ll, idx), idx);
    return itr;
}

/* Iterator functions */
void* linkedlist_iterator_next(id self) {
    list_iterator itr = cast(list_iterator, self);
    assert(itr->has_next(itr));
    // test
    assert(itr->aux != NULL);
    linkedlist_node current_node = (linkedlist_node) itr->aux;
    itr->aux = current_node->next;
    ++itr->cursor;
    itr->change = 1;
    return current_node->data;
}

void linkedlist_iterator_remove(id self) {
    list_iterator itr = cast(list_iterator, self);
    assert(itr->change != 0);
    linkedlist ll = cast(linkedlist, itr->host);
    // test
    assert(itr->aux != NULL);
    linkedlist_node current_node = (linkedlist_node) itr->aux;
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

void linkedlist_list_iterator_add(id self, void* data) {
    list_iterator itr = cast(list_iterator, self);
    assert(itr->change != 0);
    linkedlist ll = cast(linkedlist, itr->host);
    linkedlist_node current_node = (linkedlist_node) itr->aux;
    insert_before(ll, current_node, data);
    ++itr->cursor;
    itr->change = 0;
}

void linkedlist_list_iterator_set(id self, void* data) {
    list_iterator itr = cast(list_iterator, self);
    assert(itr->change != 0);
    linkedlist ll = cast(linkedlist, itr->host);
    linkedlist_node current_node = (linkedlist_node) itr->aux;
    linkedlist_node tbs = itr->change > 0 ? prev_node(ll, current_node)
            : current_node;
    tbs->data = data;
}

void* linkedlist_list_iterator_previous(id self) {
    list_iterator itr = cast(list_iterator, self);
    assert(itr->has_previous);
    --itr->cursor;
    linkedlist_node current_node = (linkedlist_node) itr->aux;
    current_node = current_node->prev;
    itr->aux = current_node;
    itr->change = -1;
    return current_node->data;
}