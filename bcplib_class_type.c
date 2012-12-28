#include "bcplib_class_type.h"
#include <bcplib/object.h>
const class_type_t null_class_type = {NULL, TYPE_ABSTRACT_CLASS, "null", 0};


/* Type */
bool _kindof(id obj, class_type t) {
    if (obj == NULL || t == &(null_class_type)) return false;
    object o = (object)obj;
    class_type tt = o->class_type;
    while(tt != &(null_class_type) && tt != t) {
        tt = tt->parent;
    }
    return tt != &(null_class_type);
}

bool _instanceof(id obj, class_type t) {
    if (obj == NULL) return false;    
    object o = (object) obj;
    return o->class_type == t;
}

inline
id _cast(id obj, class_type t) {
    assert(_kindof(obj, t));
    return obj;
}

id _malloc_object(size_t size, class_type type) {
    id ret = bcplib_malloc(size);
    ((object)ret)->class_type = type;
    return ret;
}