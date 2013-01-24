#include "object.h"
/* Initialize class. */
INIT_CLASS(object, object, TYPE_ABSTRACT_CLASS);

/* Implementation of the initializer of object */
BEGIN_IMPL_INITIALIZER(object)
self->equals = object_equals;
END_IMPL_INITIALIZER(object)


/* 
 * The finalizer of object is special, cause it doesn't call the initialzer
 * of the super class, which means I can't use the standard macro.
 */
void object_finalizer(id obj, class class) {
    // do nothing currently
}

int object_equals(id this, id that) {
    return this == that;
}
