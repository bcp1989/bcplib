bcplib
======
bcplib is a object-oriented C library of common data structures and algorithms. 
The philosophy of bcplib is to build a easy-to-use, easy-to-extend library.
And I also try to make all modules independent so that user may only need
a very limit subset of bcplib to run a specific module. The development of
bcplib is motivated by Java SDK. If you are familiar with Java, you can use
bcplib in a way that you use Java.

Currently, bcplib is developed and tested in gcc 4. When using bcplib, you need
to make sure the structure alignment strategy in specific Compiler won't 
influence the function of bcplib.

Be ware of the number of objects you created. Object in bcplib is space
consuming, in a 32-bit architecture, a *arraylist* object takes up to 104 bytes.
- - -
How to use bcplib
=================
The interface of bcplib is very simple.

Create && destroy Object
------------------------
`class_name A = create(class_name);` for "new" a Object and 
`destory(class_instance);` for "release" a Object.

For constructors with arguments, there are a set of `create` functions named as
`createN();` where *N* is the number of arguments. Currently, only zero to three
arguments are supported. For example, 
`class_name a = create1(class_name, argument1_name, argument1_value);`
will call the specific initialization function with 1 argument.

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
To check if a object is exactly the instance of a class, use
`instanceof`. To check if a object inherits/extends or is a instance of a class,
use `kindof`.

Conventions for developing bcplib
---------------------------------
1. The construction and deconstruction function should be named as
   `class_name_create();` and `class_name_destroy(id obj);`, for constructors
   with arguments, the name should be
   `class_name_create_by_arg1_name_arg2_name(arg1, arg2);`
2. There should be a class_name_prototype macro used to be inherited. For a 
   example of the macro, please see \<bcplib/container/arraylist.h\>
3. Structure name should not be the same with the class name.
4. Call `DEFINE_CLASS` at header file, and call `INIT_CLASS` in the source file.
   Please see any class inside bcplib for more detail.

OO in bcplib
============
Like Java, bcplib support concepts of class, single inherit/extends, interface, 
abstract class, final class. However, some of the concepts are not 100% the same 
as Java. Especially, the concept *inherit* and *extend* in bcplib are different.

Things to know before start
---------------------------
The internal represent of bcplib may be complicated, however, to provide a easy-
to-use library, the interface of bcplib is very simple, even, a little bit 
incompatible with the "normal" rule of software development. 
+ *id*, a universal pointers to *Object* in bcplib, just like *id* in 
  Objective-C. Nearly every *Object Function* takes a *id* as input, to simulate
  the *this* reference. Inside each *Object Function*, the function first cast 
  the *id* to the type it needs so that user don`t have to do the cast when use
  a function of parent class. 
+ Every class type is a pointer type. For example, "arraylist" is actually
  "arraylist_t \*". You can also use your own way to allocate the structure and
  use initialize a class instead of create function. For example, normally, you
  write `arraylist a = arraylist_create();`, here *a* is a pointer type; and you
  can also write `arraylist_t a;` and then use `arraylist_init(&a);` to
  initialize it, here *a* is a structure type.

Class
-----
In bcplib, each class is actually a structure. Every class in bcplib *extends* 
the root class *Object*. We need the following things to define a class:
+ A *prototype* of class, defined by using a macro.
+ Definition for each function type.
+ Functions to *create* and *destroy* a class.
+ Functions to *initialize* and *finalize* a class.

Prototype
---------
In order to let others inherits/extends itself, one *Class* should define a 
prototype of itself. The prototype is defined by using a macro, simply list all 
data and functions.

Inherit
-------
In bcplib, inherit is just use another set of functions to initialize a class.
If class A inherits class B, A cannot have any function or data that B does not 
have. For example, function *arraylist_create_list_iterator* in *arraylist.c* 
create a anonymous class that inherits class *list_iterator* by initializing the
class with some functions defined in *arraylist.c*.

Extends
-------
Extends in bcplib is like Java. Class A extends class B means that A has all
function declarations and data that B has, and A may has its own functions or 
data that B does not have. In the prototype of A, the prototype of B should be 
the first element so that we can cast A to B. However, this trick way is 
depend on the structure alignment strategy in specific Compiler.

Interface
---------
Interface is just a macro contains data or function lists. A class may includes
the interface in any position of its prototype except the first one (first 
element is reserved for the prototype of parent class). We cannot cast a class
to the interface it implements. So the concept interface in bcplib is 
incomplete compared to Java.

Abstract class
--------------
You cannot create a abstract class, so in bcplib, a class without any *create* 
or "destroy" functions can be treated as a abstract class. User can still 
allocate a abstract class and use "init_xxxx" function to initialize it, but 
it's very dangerous, for the definition of such a abstract class may be 
incomplete, any function call may lead unknown error.

Final class
-----------
You cannot extends/inherits a final class in bcplib, since final class does not 
have a prototype as well as *initialize* and *finalize* functions.

