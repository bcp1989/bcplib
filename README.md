bcplib (deprecated and a new version which has a robust type system is in developing :-)
======
bcplib is a object-oriented C library of common data structures and algorithms. 
The philosophy of bcplib is to build a easy-to-use, easy-to-extend library.
And I also try to make all modules independent so that user may only need
a very limit subset of bcplib to run a specific module. The development of
bcplib is motivated by Java SDK. If you are familiar with Java, you can use
bcplib in a way that you use Java.

Currently, bcplib is developed and tested in GCC 4 and C99 (well...currently I 
only use variadic macros) standard. When using bcplib, you need to make sure the 
structure alignment strategy in specific Compiler won't influence the function 
of bcplib.

Be ware of the number of objects you created. Object in bcplib is space
consuming, in a 32-bit architecture, a *arraylist* object takes up to 104 bytes.
- - -
How to use bcplib
=================
The interface of bcplib is very simple.

Create && destroy Object
------------------------
`class_name A = new(class_name, init_flag, arg1, arg2,...);` to "new" a Object 
and `destory(class_instance);` to "release" a Object. Note that here the 
`init_flag` is a hint of the initializer to simulate *override* and the 
developer can use it in any way it like.

Function call
-------------
If a class is named A, and there is a instance of A called a, you can use 
`a->function_name(a, other_arguments);` to make a function call, remember to 
put the instance itself as the first argument of any function call, it's a
naive way to simulate *this* reference in Java.

Cast
----
Just like Java. If class A extends/inherits class B, you can use a instance 
of A where you need a instance of B. You can directly cast A to B. 

For example, you can have a array of instance of class *collection*, and each 
instance may be a *arraylist*, *linkedlist* or other class that inherits/extends
from *collection*.

There are two ways to cast a object from one class to another. You can just type
either `(class_A_name) class_B_instance_var` or 
`cast(class_A_name, class_B_instance_var)`
to cast a instance variable of class B to class A. The different is that the
later one will do the type check.

Class Type
----------
Every object has a class type structure to indicate the type of the object.
+ To check if a object is exactly the instance of a class, use
    `instanceof`. 
+ To check if a object inherits/extends or is a instance of a class,
    use `kindof`. 
+ To check whether a c pointer points to a object or something else, use 
    `is_object`.
+ To get the class type of a object instance, use `classof`.
+ To get the class type of a given class name, use `class_by_name`.


Conventions for developing bcplib
---------------------------------
Please see convention.md for the latest convention list.
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



