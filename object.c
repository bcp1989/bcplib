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
