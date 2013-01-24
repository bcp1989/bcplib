#include "map.h"

INIT_CLASS(map, object, TYPE_ABSTRACT_CLASS);

BEGIN_IMPL_INITIALIZER(map)
init_super(flag);
END_IMPL_INITIALIZER(map)
        
BEGIN_IMPL_FINALIZER(map)
// do nothing
END_IMPL_FINALIZER(map)

INIT_CLASS(map_entry, object, TYPE_NORMAL_CLASS);
BEGIN_IMPL_INITIALIZER(map_entry)
init_super(flag);
self->key = next_arg(void*);
self->value = next_arg(void*);
END_IMPL_INITIALIZER(map_entry)
        
BEGIN_IMPL_FINALIZER(map_entry)
// do nothing
END_IMPL_FINALIZER(map_entry)