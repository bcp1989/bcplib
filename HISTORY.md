TODO List
---------
 1. document, use doxygen. ||
 2. Test framework. ||||
 3. Need to check pointer type inside each function, to make sure the pointers 
    inherit/*extends* a specific class. Don't know how right now. -
 4. arraylist (done), linkedlist (done), set (developing), map, hashmap, hashset, 
    treeset, treemap. |||
5.  Fix the problems of the 'extends' and 'implements' macros.
6.  Need to update the README.
7.  Find a way to completely support interface.
8.  LONG Optimize the size of structures of classes.

1/26/2013
---------
+ Minor refactor.
+ Add hashmap class (still in process), improve map class.
+ Add string class (waiting for Tire tree, suspend).
+ Update documents.

1/23/2013
---------
+ Improve type system. Now 'is_object' can be used to detect if a pointer points
  to a bcplib object. Now bcplib has its own magic number, which is 
  '0xFEEDACED'.
+ Universal 'new' and 'destroy' function. Now 'new', 'destroy', 'classof' etc. 
  are all selectors, which means all the related data are in meta class 
  structure.
+ Completely new way to define/initialize a class. Instead of defining a 
  structure to contain the content of a class, now user only need to define
  a 'X_prototype' (where *X* represents the class name) and use several 
  macros to define a class, lots of details are hidden behind.
+ As parts of the *hidden* idea, initializer and finalizer of a object must be 
  defined and implemented using related macros ('BEGIN_IMPL_INITIALIZER', 
  'END_IMPL_INITIALIZER', 'BEGIN_IMPL_FINALIZER', and 'END_IMPL_FINALIZER').
+ Old ways of create class (use 'createN' macro) are replaced by the new 'new'.
+ Minor refactor of the project structure.

11/26/2012
----------
+ Refactor project structure

11/25/2012
----------
+ Add type system
+ Change each class to fit to the type system
+ Clean the source file structure

11/24/2012
----------
+ Add linkedlist.
+ Optimize arraylist_list_iterator.
+ Add universal create and destroy mechanism
+ Add definition of map, set

11/19/2012
----------
+ Add list_iterator class, a special list_iterator for all list
  classes.
+ Add arraylist class.

11/1/2012
----------
+ Add bitmap.
+ Add iterator, collection, lib_base, list.