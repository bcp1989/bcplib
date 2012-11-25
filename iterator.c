#include "iterator.h"

inline
void iterator_init(id user_obj, id host, id aux) {
    iterator itr = (iterator) user_obj;
    assert (itr != NULL);
    object_init(itr);
    itr->host = host;
    itr->aux = aux;
}

inline
void iterator_finalize(id obj) {
    object_finalize(obj);
    // nothing to inalize
}
