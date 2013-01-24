#include "bcplib_class.h"
#include "object.h"

bool _is_object(id p) {
    return p != NULL && *((int32_t *) p) == BCPLIB_MAGIC_NUMBER;
}

bool _kindof(id obj, class t) {
    if (!is_object(obj)) return false;
    object o = (object) obj;
    class cls = o->class;
    // note that all class inherits object class by default, even user force
    // its class to inherit something else (which is illegal).
    if (cls == t || t == class_by_name(object)) return true;
    while(cls != t && !is_root_class(cls)) {
        cls = cls->super;
    }
    return cls == t;
}

bool _instanceof(id obj, class t) {
    if (!is_object(obj)) return false;
    return classof(obj) == t;
}

inline
id _cast(id obj, class t) {
    assert(_kindof(obj, t));
    return obj;
}