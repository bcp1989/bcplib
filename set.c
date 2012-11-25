#include "set.h"

extern void set_init(id obj) {
    collection_init(obj);
}

extern void set_finalize(id obj) {
    collection_finalize(obj);
}
