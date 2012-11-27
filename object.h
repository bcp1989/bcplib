/* 
 * File:   object.h
 * Author: Yirui Zhang
 *
 * Created on November 25, 2012, 11:00 PM
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

#ifndef OBJECT_H
#define	OBJECT_H
#include "bcplib_base.h"

/* Define Root class, Object */
DEFINE_CLASS(bcplib_object, object);

/* Define function type of 'equals' */
typedef bool (*object_equals_t)(id, id);
typedef void (*object_destroy_t)(id);
/* Prototype of class *Object */
#define object_prototype                     class_type class_type;\
                                             object_equals_t equals;\
                                             object_destroy_t destroy
/* C structure for class Object */
struct bcplib_object {
    object_prototype;
};
/* Initialize and finalize functions for class Object */
extern inline void object_init(id);
extern inline void object_finalize(id);
/* Functions of Object */
extern int object_equals(id this, id that);

/* Part of the type system is in class object */
/* Check if a object is a instance of the specific class type */
#define instanceof(obj, class_name) \
        (_instanceof(obj, CLASS_TYPE_BY_NAME(class_name)))
/* 
 * Check if a object inherit/extends from the specific class type or is a 
 * instance of the specific class type .
 */
#define kindof(obj, class_name) \
        (_kindof(obj, CLASS_TYPE_BY_NAME(class_name)))
/* Allocate a object instance in memory. */
#define malloc_object(class_name) \
        ((class_name) _malloc_object(sizeof(class_name##_t), \
                CLASS_TYPE_BY_NAME(class_name)))
/* Cast a id pointer to a specific object pointer, including type check */
#define cast(type, obj) \
        ((type) _cast(obj, CLASS_TYPE_BY_NAME(type)))
/* Get class type by name, end-user version */
#define class_typeof(type) \
        (CLASS_TYPE_BY_NAME(type))

extern bool _instanceof(id obj, class_type t);
extern bool _kindof(id obj, class_type t);
extern id _cast(id obj, class_type t);
#endif	/* OBJECT_H */

