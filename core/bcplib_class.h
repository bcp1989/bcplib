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
#include <stdarg.h>
#include <assert.h>
#include "bcplib_type.h"
/* 
 * Magic number of bcplib, used to detect whether a pointer points to a 
 * bcplib object.
 */
#define BCPLIB_MAGIC_NUMBER     (0xFEEDACED)

/* Class flag used to indicate the type of the class (final, abstract, etc.). */
typedef enum bcplib_class_type_flag {
    TYPE_ABSTRACT_CLASS = 1, TYPE_FINAL_CLASS, TYPE_NORMAL_CLASS
} class_flag_t;

/* Some type definitions about class type. */
typedef struct bcplib_class class_t;
typedef const class_t * class;

/* Function type definition. */
typedef uint64_t init_flag;
typedef void (*class_initializer)(id, class, init_flag, va_list);
typedef void (*class_finalizer)(id, class);

/* Structure of class type */
struct bcplib_class {
    class const super;
    const class_flag_t flag;
    const char* const name;
    const size_t size;
    const class_initializer initializer;
    const class_finalizer finalizer;
};
/*----- Macros related to class type system -----*/
/* Get the class type for a specific name. */
#define class_by_name(class_name) \
        (&(class_name##_class))

/* Check if it's object */
#define is_object(p) \
        (_is_object(p))

/* Check if it's root class */
#define is_root_class(cls) \
        (cls->super == cls)

/* Check if a object is a instance of the specific class type */
#define instanceof(obj, class_name) \
        (_instanceof(obj, class_by_name(class_name)))

/* 
 * Check if a object inherit/extends from the specific class type or is a 
 * instance of the specific class type .
 */
#define kindof(obj, class_name) \
        (_kindof(obj, class_by_name(class_name)))

/* Cast a id pointer to a specific object pointer, including type check */
#define cast(type, obj) \
        ((type) _cast(obj, class_by_name(type)))

/* Get class type by name, end-user version */
#define classof(obj) \
        (cast(object, obj)->class)


/*----- Macros for class definition -----*/
/* Insert prototype of super class. */
#define extends(super_name)     super_name##_prototype
#define implements(super_name)  super_name##_interface
/* Define initializer of a class. */
#define DEFINE_INITIALIZER(class_name) \
        extern void class_name##_initializer(id, class, init_flag, va_list)

/* Define finalizer of a class. */
#define DEFINE_FINALIZER(class_name) \
        extern void class_name##_finalizer(id, class)

/* Macro for class type define. */
#define DEFINE_CLASS_TYPE(class_name) \
        extern const class_t class_name##_class

/* Begin of class definition. */
#define BEGIN_DEFINE_CLASS(class_name) \
        typedef struct bcplib_##class_name class_name##_t; \
        typedef struct bcplib_##class_name* class_name; \
        DEFINE_CLASS_TYPE(class_name);

/* End of class definition. */
#define END_DEFINE_CLASS(class_name) \
        DEFINE_INITIALIZER(class_name); \
        DEFINE_FINALIZER(class_name); \
        struct bcplib_##class_name { \
            class_name##_prototype; \
        };

/*----- Macros for class implementation or initialization -----*/
/* Implementation of the initializer of a class. */
#define BEGIN_IMPL_INITIALIZER(class_name) \
        void class_name##_initializer(id obj, class class, init_flag flag, \
                                        va_list args) { \
            class_name self = (class_name) obj;

/* Initialize super class. */
#define init_super(flag) \
            class->super->initializer(obj, class->super, flag, args)

/* Get the next argument of the argument list. */
#define next_arg(type) (va_arg(args, type))

/* End of implementation of the initializer. */
#define END_IMPL_INITIALIZER(class_name) \
        }

/* Begin of the implementation of a finalizer of a class */
#define BEGIN_IMPL_FINALIZER(class_name) \
        void class_name##_finalizer(id obj, class class) { \
            class_name self = (class_name) obj; \
            class->super->finalizer(self, class->super);

/* End of the implementation of the finalizer. */
#define END_IMPL_FINALIZER(class_name)  }

/* Initialize the class type structure. */
#define INIT_CLASS_TYPE(self_name, super_name, class_flag) \
        const class_t self_name##_class = \
                {.super = class_by_name(super_name),\
                .flag = class_flag,\
                .name = #self_name,\
                .size = sizeof(self_name##_t),\
                .initializer = self_name##_initializer,\
                .finalizer = self_name##_finalizer}

/* Initialize the class. */
#define INIT_CLASS(self_name, super_name, flag) \
        INIT_CLASS_TYPE(self_name, super_name, flag)

/* Detect if a pointer points to a object */
extern bool _is_object(id p);

/* Detect if object is a instance of class t */
extern bool _instanceof(id obj, class t);

/* Detect if object inherits class t */
extern bool _kindof(id obj, class t);

/* Cast object to class t, involves type check */
extern id _cast(id obj, class t);
#endif	/* CLASS_TYPE_H */

