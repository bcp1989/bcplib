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
If a class is named A, you can use 'A_create_xxxx' (xxxx is specific create 
method that may needs extra arguments) functions to create a instance, you can 
use 'A_destroy' function to destroy a instance.
For example, 'arraylist al = arraylist_create();' will create a array list with
default capacity. 'arraylist al = arraylist_destroy(al);' will destroy it.
The creation and destruction function are not OO.

Function call
-------------
If a class is named A, and there is a instance of A called a, you can use 
'a->function_name(a, other_arguments);' to make a function call, remember to 
put the instance itself as the first argument of any function call, it's a
naive way to simulate *this* reference in Java.

Cast
----
Just like Java

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
  the *id* to the type it needs so that user don't have to do the cast when use
  a function of parent class. 
+ Every class type is a pointer type. For example, "arraylist" is actually
  "arraylist_t \*". You can also use your own way to allocate the structure and
  use initialize a class instead of create function. For example, normally, you
  write 'arraylist a = arraylist_create();', here *a* is a pointer type; and you
  can also write 'arraylist_t a;' and then use 'arraylist_init(&a);' to
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
Extends in bcclib is like Java. Class A extends class B means that A has all
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

