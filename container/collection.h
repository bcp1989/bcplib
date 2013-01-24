/* 
 * File:   collection.h
 * Author: Yirui Zhang
 *
 * Created on November 1, 2012, 2:37 PM
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
 * Collection
 * A abstract class that describe the concept collection. Refer to Java
 * Collection and AbstractCollection.
 * 
 */

#ifndef COLLECTION_H
#define	COLLECTION_H

#include <stdint.h>
#include <stddef.h>
#include <bcplib/core/bcplib_base.h>
#include "iterator.h"
BEGIN_DEFINE_CLASS(collection)
#define COLLECTION_INIT_COMPARATOR  1
// define function types
typedef bool (*collection_add_t)(id, void*);
typedef bool (*collection_add_all_t)(id, id);
typedef bool (*collection_remove_t)(id, void*);
typedef bool (*collection_remove_all_t)(id, id);
typedef void (*collection_clear_t)(id);
typedef size_t(*collection_size_t)(id);
typedef bool (*collection_is_empty_t)(id);
typedef bool (*collection_contains_t)(id, void*);
typedef bool (*collection_contains_all_t)(id, id);
// define class prototype
#define collection_prototype    object_prototype;\
                                iterable_interface;\
                                comparator compare;\
                                collection_add_t add;\
                                collection_add_all_t add_all;\
                                collection_remove_t remove;\
                                collection_remove_all_t remove_all;\
                                collection_clear_t clear;\
                                collection_size_t size;\
                                collection_is_empty_t is_empty;\
                                collection_contains_t contains;\
                                collection_contains_all_t contains_all

/* Function of Collection */
bool collection_is_empty(id self);
bool collection_add_all(id self, id other);
bool collection_remove_all(id self, id other);
bool collection_contains_all(id self, id other);
bool collection_compare(void* user_data1, void* user_data2);
bool collection_remove(id self, void* user_data);
bool collection_contains(id self, void* user_data);

END_DEFINE_CLASS(collection)
#endif	/* COLLECTION_H */

