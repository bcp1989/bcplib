/* 
 * File:   bcplib_base.h
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
#ifndef BCPLIB_BASE_H
#define	BCPLIB_BASE_H

#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "bcplib_class_type.h"
#include "bcplib_type.h"

/* `new` */
#define create(type) (type##_create())
#define create1(type, arg_name, arg) (type##_create_by_##arg_name(arg))
#define create2(type, arg_name1, arg1, arg_name2, arg2) \
        (type##_create_by_##arg_name1##_##arg_name2(arg1, arg2))
// haven't been tested yet
#define create3(type, arg_name1, arg1, arg_name2, arg2, arg_name3, arg3) \
        (type##_create_by_##arg_name1##_##arg_name2##_##arg_name3(arg1, arg2, arg3))
/* `free` */
#define destroy(obj) (obj)->destroy((obj))
/* malloc a object */
#define malloc_object(class_name) \
        ((class_name) _malloc_object(sizeof(class_name##_t), \
                CLASS_TYPE_BY_NAME(class_name)))
/* 
 * Comparator, it's a function type to let user define a function to compare 
 * its objects.
 */
typedef int (*comparator)(void*, void*);

/*
 * Hash function for user to compute hash code of its data.
 */
typedef size_t (*hasher)(void*);



/* Utilities */
/* malloc object */
extern id _malloc_object(size_t size, class_type type);
/* malloc function, bcplib version */
extern void* bcplib_malloc(size_t size);
//extern void* bcplib_realloc(void* pointer, size_t new_size);
/* free function, bcplib version */
extern void bcplib_free(void* p);
/* System copy function */
extern void bcplib_array_copy(void** from, void** to, size_t offset, size_t length);
#endif	/* LIB_BASE_H */

