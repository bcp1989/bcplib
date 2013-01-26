+ User must define a 'X_prototype' macro which includes all attributes and
    methods for their class.
+ User must define a 'X_interface' macro which includes all attributes and 
    methods for their interface.
+ Inside the prototype, 'extends' should always be the first elements.
+ All macros in upper letters should be used outside function blocks, 
    all macros in lower letters should be used inside function blocks.
+ Inside initializer and finalizer functions, 'self' is a keywords can be used
    as a pointer to the object instance, and 'flag' is a extra information to
    decide how to initialize the object instance ('overload'). User can use
    the flag in any way they like (or Please see the class in bcplib for
    recommend style). Note that 'INIT_DEFAULT' is preserved to indicate the
    default initializer and its value is 0.
    Note that in bcplib, some flag value are conflict with each other, I solve
    it by simply set a priority of flags. Flags with low priority won't valid 
    if a flag with higher priority is set.
+ The range of size_t is from -1 to (2^8)^(sizeof(size_t) - 1. If you cast 
    size_t into some signed number, -1 will be the max value of the size_t,
    so I preserve the max value to represent -1 so that many functions can be
    benefit it.