#include "set.h"

INIT_CLASS(set, collection, TYPE_ABSTRACT_CLASS);

BEGIN_IMPL_INITIALIZER(set)
init_super(flag);
// do nothing
END_IMPL_INITIALIZER(set)
        
BEGIN_IMPL_FINALIZER(set)
// do nothing
END_IMPL_FINALIZER(set)