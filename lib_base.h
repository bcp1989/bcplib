/* 
 * File:   lib_base.h
 * Author: Yirui Zhang
 *
 * Created on November 1, 2012, 5:50 PM
 * 
 *  bcplib is a object-oriented c library of common data structures and 
 *  algorithms. 
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
 */
#ifndef LIB_BASE_H
#define	LIB_BASE_H

#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef bool
#define bool int
#endif

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

#define id void*
#define DEFINE_CLASS(struct_name, class_name) typedef struct struct_name* class_name
#define safe_cast(type, obj) ((type) _safe_cast(obj))



/* 
 * Comparator, it's a function type to let user define a function to compare 
 * its objects.
 */
typedef int (*comparator)(void*, void*);

/* Define Root class, Object */
DEFINE_CLASS(bcplib_object, object);

/* Define function type of 'equals' */
typedef bool (*object_equals_t)(id, id);

/* Prototype of class *Object */
#define object_prototype                     object_equals_t equals

/* C structure for class Object */
struct bcplib_object {
    object_prototype;
};

/* Initialize and finalize functions for class Object */
extern inline void object_init(id);
extern inline void object_finalize(id);

/* Functions of Object */
extern int object_equals(id this, id that);

/* Utilities */
/* Saft cast sub-function */
extern inline id _safe_cast(id obj);
/* malloc function, bcplib version */
extern void* bcplib_malloc(size_t size);
//extern void* bcplib_realloc(void* pointer, size_t new_size);
/* free function, bcplib version */
extern void bcplib_free(void* p);
/* System copy function */
extern void bcplib_array_copy(void** from, void** to, size_t offset, size_t length);
#endif	/* LIB_BASE_H */

