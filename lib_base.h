/* 
 * File:   lib_base.h
 * Author: Yirui Zhang
 *
 * Created on November 1, 2012, 5:50 PM
 * 
 *  bcplib is a OO c library of common data structures and algorithms. 
 *  The philosophy of bcplib is to build a easy-to-use, easy-to-extend library.
 *  And I also try to make all modules independent so that user may only need
 *  a very limit subset of bcplib to run a specific module.
 * 
 *  Copyright (C) <2012>  <Yirui Zhang>
 * 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Lib Base 
 * Lib base contains all base function types and the object that is inherited
 * by nearly all structures in my lib.
 * This module may be separate into different modules if it increases a lot.
 * ChangeList
 * ----------
 * 11/1/2012
 * +
 * 
 * TODO
 * ----
 */
#ifndef LIB_BASE_H
#define	LIB_BASE_H

#include <stddef.h>
#include <assert.h>
#include <stdlib.h>

#ifndef bool
typedef int bool;
#endif

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

#define id void*
#define DEFINE_CLASS(struct_name, class_name) typedef struct struct_name* class_name



/* 
 * Comparator, it's a function type to let user define a function to compare 
 * its objects.
 */
typedef int (*comparator)(void*, void*);

/*
 * Description
 * -----------
 * Base class type, most of modules in bcplib is OO, and they all 
 * inherit/extends the base class type.
 * OO in bcplib
 * ------------
 * *inherit* is using a different set of functions.
 * *extends* is using a different structure but put the prototype of its parent
 * class as the first element in its structure.
 * *final class* have no class prototype so that other class cannot inherit or
 * extends it.
 * *Interface* is simple, in bcplib, a macro that defines a collection of 
 * functions/attributes is treated as a interface.  Not like Java, you can't 
 * cast a class into a interface type (cause a class may put the functions 
 * anywhere). It is just a way to let user know what a class can do.
 * *Abstract class* and "Non-abstract class" can be known by their init.
 * function; a class is a abstract class if there is only *X_init*(where X is
 * the class name), and a non-abstract class should define one or more
 * *X_create_Y* functions where Y indicates the specific way to create a class.
 */
DEFINE_CLASS(bcplib_object, object);
typedef bool (*object_equals_t)(id, id);
#define object_prototype                     object_equals_t equals

struct bcplib_object {
    object_prototype;
};

extern inline void object_init(id);

/* Utilities */
inline bool check_index_range(size_t, size_t);

#endif	/* LIB_BASE_H */

