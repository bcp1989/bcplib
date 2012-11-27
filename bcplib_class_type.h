/* 
 * File:   bcplib_class_type.h
 * Author: Yirui Zhang
 *
 * Created on November 25, 2012, 11:10 PM
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

#ifndef BCPLIB_CLASS_TYPE_H
#define	BCPLIB_CLASS_TYPE_H

#include <stddef.h>
#include <stdint.h>
#include <assert.h>
#include "bcplib_type.h"

/* define a class name */
#define DEFINE_CLASS_TYPE(class_name) \
        extern const class_type_t class_name##_class_type

#define INIT_CLASS_TYPE(name, parent, flag) \
        const class_type_t name##_class_type = \
                {CLASS_TYPE_BY_NAME(parent), flag, #name, sizeof(name##_t)}

#define DEFINE_CLASS(struct_name, class_name)\
        typedef struct struct_name class_name##_t;\
        typedef struct struct_name* class_name;\
        DEFINE_CLASS_TYPE(class_name)

#define INIT_CLASS(name, parent, flag) \
        INIT_CLASS_TYPE(name, parent, flag)

#define CLASS_TYPE_BY_NAME(class_name) \
        (&(class_name##_class_type))     

typedef enum bcplib_class_type_flag {
    TYPE_ABSTRACT_CLASS = 1, TYPE_FINAL_CLASS, TYPE_NORMAL_CLASS
} class_type_flag_t;

// define class type structure
typedef struct bcplib_class_type const *class_type;

typedef struct bcplib_class_type {
    class_type parent;
    class_type_flag_t flag;
    const char* name;
    size_t size;
} class_type_t;
extern const class_type_t null_class_type;
#endif	/* CLASS_TYPE_H */

