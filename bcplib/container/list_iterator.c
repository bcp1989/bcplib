#include "list_iterator.h"
#include "list.h"

INIT_CLASS(list_iterator, iterator, TYPE_ABSTRACT_CLASS);

inline
void list_iterator_init(id obj, id host, id aux) {
    list_iterator list_itr = (list_iterator) obj;
    assert(list_itr != NULL);
    iterator_init(obj, host, aux);
    list_itr->change = 0;
    list_itr->has_next = list_iterator_has_next;
    list_itr->has_previous = list_iterator_has_previous;
    list_itr->next_index = list_iterator_next_index;
    list_itr->previous_index = list_iterator_previous_index;
}

inline
void list_iterator_finalize(id obj) {
    iterator_finalize(obj);
    // nothing to finalize
}
/* Iterator */
bool list_iterator_has_next(id obj) {
    list_iterator itr = safe_cast(list_iterator, obj);
    list l = safe_cast(list, itr->host);
    return itr->next_index(itr) < l->size(l);
}

/* List iterator */
bool list_iterator_has_previous(id obj) {
    list_iterator itr = safe_cast(list_iterator, obj);
    return itr->previous_index(itr) >= 0;
}

size_t list_iterator_next_index(id obj) {
    list_iterator itr = safe_cast(list_iterator, obj);
    return itr->cursor;
}

size_t list_iterator_previous_index(id obj) {
    list_iterator itr = safe_cast(list_iterator, obj);
    return itr->cursor - 1;
}
