#include "lib_base.h"
#include <assert.h>

/* Function Declarations */
static int object_equals(id this, id that);

/*
 * Init function of abstract class object.
 * Init function never check the parameter, because object is a abstract class
 * and 1 class that inherit it have to check the parameter themself.
 */
inline
void object_init(id user_obj) {
    object obj = (object)user_obj;
    obj->equals = object_equals;
}

static
int object_equals(id this, id that) {
    return this == that;
}

/* Utilities */

inline 
bool check_index_range(size_t size, size_t idx) {
    return idx >= 0 && idx < size;
}