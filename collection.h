/* 
 * File:   collection.h
 * Author: Yirui Zhang
 *
 * Created on November 1, 2012, 2:37 PM
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
 * Collection
 * A abstract class that describe the concept collection.
 * 
 * ChangeList
 * ----------
 * 11/1/2012
 * + Class type, class basic functions
 * 
 * TODO
 * ----
 */

#ifndef COLLECTION_H
#define	COLLECTION_H

#include <stdint.h>
#include <stddef.h>
#include "lib_base.h"
#include "iterator.h"

DEFINE_CLASS(bcplib_collection, collection);

typedef bool (*collection_add_t)(id, void*);
typedef bool (*collection_add_all_t)(id, id);
typedef bool (*collection_remove_t)(id, void*);
typedef bool (*collection_remove_all_t)(id, id);
typedef void (*collection_clear_t)(id);
typedef size_t(*collection_size_t)(id);
typedef bool (*collection_is_empty_t)(id);
typedef bool (*collection_contains_t)(id, void*);
typedef bool (*collection_contains_all_t)(id, id);

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

#define COLLECTION_a2b_SUB_CALL(type, obj1, obj2, call) \
        assert(obj1 != NULL && obj2 != NULL);\
        type c1 = (type) obj1;\
        type c2 = (type) obj2;\
        iterator_t c2itr = c2->get_iterator(c2);\
        while (c2itr.has_next(&c2itr)) {\
                if (c1->call(c1, c2itr.next(&c2itr))) {\
                        return false;\
                }\
        }\
        return true

typedef struct bcplib_collection {
    collection_prototype;
} collection_t;

inline void collection_init(id, comparator,
        collection_add_t,
        collection_add_all_t,
        collection_remove_t,
        collection_remove_all_t,
        collection_clear_t,
        collection_size_t,
        collection_is_empty_t,
        collection_contains_t,
        collection_contains_all_t);

#endif	/* COLLECTION_H */

