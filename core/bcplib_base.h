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
 * Internal base header for developing bcplib.
 */
#ifndef BCPLIB_BASE_H
#define	BCPLIB_BASE_H

#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "bcplib_class.h"
#include "bcplib_type.h"

/* `new` */
#define new(type, flag, ...) \
        (_new(class_by_name(type), flag,##__VA_ARGS__))

#define destroy(obj) \
        (_destroy(obj))

/* `new` */
extern id _new(class type, init_flag flag, ...);

/* `destory` function */
extern void _destroy(id obj);

/*----- Utilities -----*/
/* Find the max value. */
#define bcplib_max(a, b) \
        ( (a) > (b) ? (a) : (b))

/* Allocate a object instance in memory. */
#define malloc_object(class_name) \
        ((class_name) _malloc_object(class_by_name(class_name)))

/* Test a bit */
#define bit_test(flag, bit) \
        (((flag) & (bit)) == bit)

/* Malloc object */
extern id _malloc_object(class type);

/* Malloc function, bcplib version */
extern void* bcplib_malloc(size_t size);

/* Free function, bcplib version */
extern void bcplib_free(void* p);

/* System copy function */
extern void bcplib_array_copy(void** from, void** to, size_t offset, size_t length);
#endif	/* LIB_BASE_H */

