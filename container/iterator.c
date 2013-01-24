#include "iterator.h"
INIT_CLASS(iterator, object, TYPE_ABSTRACT_CLASS);

BEGIN_IMPL_INITIALIZER(iterator)
init_super(flag);
self->host = next_arg(id);
self->aux = next_arg(id);
END_IMPL_INITIALIZER(iterator)

BEGIN_IMPL_FINALIZER(iterator)
// do nothing
END_IMPL_FINALIZER(iterator)
