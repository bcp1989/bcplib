#include "iterator.h"

inline
void iterator_init(id user_obj, id host, id first,
        iterator_has_next_t has_next,
        iterator_next_t next) {

    iterator itr = (iterator) user_obj;
    itr->host = host;
    itr->client = first;
    itr->has_next = has_next;
    itr->next = next;
}

iterator iterator_create(id host, id first,
        iterator_has_next_t has_next,
        iterator_next_t next) {
    
    iterator ret = (iterator) malloc(sizeof (iterator_t));
    iterator_init(ret, host, first, has_next, next);
    return ret;
}