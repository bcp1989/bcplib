#include "list_iterator.h"
#include "list.h"

INIT_CLASS(list_iterator, iterator, TYPE_ABSTRACT_CLASS);
// initializer
BEGIN_IMPL_INITIALIZER(list_iterator)
init_super(flag);
self->change = 0;
self->has_next = list_iterator_has_next;
self->has_previous = list_iterator_has_previous;
self->next_index = list_iterator_next_index;
self->previous_index = list_iterator_previous_index;

END_IMPL_INITIALIZER(list_iterator)

// finalizer
BEGIN_IMPL_FINALIZER(list_iterator)
// do nothing
END_IMPL_FINALIZER(list_iterator)

/* Iterator */
bool list_iterator_has_next(id self) {
    list_iterator itr = cast(list_iterator, self);
    list l = cast(list, itr->host);
    return itr->next_index(itr) < l->size(l);
}

/* List iterator */
bool list_iterator_has_previous(id self) {
    list_iterator itr = cast(list_iterator, self);
    return itr->previous_index(itr) >= 0;
}

size_t list_iterator_next_index(id self) {
    list_iterator itr = cast(list_iterator, self);
    return itr->cursor;
}

size_t list_iterator_previous_index(id self) {
    list_iterator itr = cast(list_iterator, self);
    return itr->cursor - 1;
}
