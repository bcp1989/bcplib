#include "list_iterator.h"

inline
void list_iterator_init(id obj, id host, id first) {
    list_iterator list_itr = (list_iterator) obj;
    assert(list_itr != NULL);
    iterator_init(obj, host, first);
}

inline
void list_iterator_finalize(id obj) {
    iterator_finalize(obj);
    // nothing to finalize
}
