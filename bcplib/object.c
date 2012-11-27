#include "object.h"

INIT_CLASS(object, null, TYPE_ABSTRACT_CLASS);

/*
 * Init function of abstract class object.
 * Init function never check the parameter, because object is a abstract class
 * and 1 class that inherit it have to check the parameter themself.
 */
inline
void object_init(id user_obj) {
    object obj = (object) user_obj;
    obj->equals = object_equals;
}

inline
void object_finalize(id obj) {
    // do nothing currently
}

int object_equals(id this, id that) {
    return this == that;
}

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
id _safe_cast(id obj, class_type t) {
    assert(_kindof(obj, t));
    return obj;
}
