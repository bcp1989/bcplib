#include "set.h"

INIT_CLASS(set, collection, TYPE_ABSTRACT_CLASS);

extern void set_init(id obj) {
    collection_init(obj);
}

extern void set_finalize(id obj) {
    collection_finalize(obj);
}
