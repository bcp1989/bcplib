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

typedef enum bcplib_class_type_flag {
    TYPE_ABSTRACT_CLASS = 1, TYPE_FINAL_CLASS, TYPE_NORMAL_CLASS
} class_type_flag_t;

// class type structure
typedef struct bcplib_class_type class_type_t;
typedef class_type_t const *class_type;
struct bcplib_class_type {
    const class_type parent;
    const class_type_flag_t flag;
    const char* const name;
    const size_t size;
} ;
// null class type
extern const class_type_t null_class_type;
   
/* Class type */
#define DEFINE_CLASS_TYPE(class_name) \
        extern const class_type_t class_name##_class_type

#define INIT_CLASS_TYPE(name, parent, flag) \
        const class_type_t name##_class_type = \
                {CLASS_TYPE(parent),\
                flag, \
                #name, \
                sizeof(name##_t)}

#define CLASS_TYPE(class_name) \
        (&(class_name##_class_type))  
/* Class */
#define DEFINE_CLASS(struct_name, class_name)\
        typedef struct struct_name class_name##_t;\
        typedef struct struct_name* class_name;\
        DEFINE_CLASS_TYPE(class_name)

#define INIT_CLASS(name, parent, flag) \
        INIT_CLASS_TYPE(name, parent, flag)

/* Initialization function */
#define DEFINE_INIT_FUNCTION(name) \
        extern inline void name##_init(id)
#define DEFINE_INIT_FUNCTION_WITH_1_ARG(name, arg1_name, arg1_type) \
        extern inline void name##_init_by_##arg1_name(id, arg1_type)
#define INIT_INIT_FUNCTION(name) \
        inline void name##_init(id obj) 
/* Destroy function */
#define DEFINE_DESTROY_FUNCTION(name) \
        extern void name##_destroy(id)
#define IMPL_DESTROY_FUNCTION(name) \
        void name##_destroy(id obj) { \
        name name##_ins = cast(name, obj); \
        
            

/* Part of the type system is in class object */
/* Check if a object is a instance of the specific class type */
#define instanceof(obj, class_name) \
        (_instanceof(obj, CLASS_TYPE(class_name)))
/* 
 * Check if a object inherit/extends from the specific class type or is a 
 * instance of the specific class type .
 */
#define kindof(obj, class_name) \
        (_kindof(obj, CLASS_TYPE(class_name)))
/* Allocate a object instance in memory. */
#define malloc_object(class_name) \
        ((class_name) _malloc_object(sizeof(class_name##_t), \
                CLASS_TYPE(class_name)))
/* Cast a id pointer to a specific object pointer, including type check */
#define cast(type, obj) \
        ((type) _cast(obj, CLASS_TYPE(type)))
/* Get class type by name, end-user version */
#define class_type_by_name(type) \
        (CLASS_TYPE(type))
#define class_type_of(obj) \
        (((object)obj)->class_type)

extern bool _instanceof(id obj, class_type t);
extern bool _kindof(id obj, class_type t);
extern id _cast(id obj, class_type t);
#endif	/* CLASS_TYPE_H */

