/* 
 * File:   list_iterator.h
 * Author: Yirui Zhang
 *
 * Created on November 2, 2012, 4:11 PM
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
 * Iterator for list.
 * ^ Element1 -> ^ Element2 -> ... ^ ElementN
 * ^ is the position of cursor.
 */
#ifndef LIST_ITERATOR_H
#define	LIST_ITERATOR_H
#include <bcplib/core/bcplib_base.h>
#include "iterator.h"
BEGIN_DEFINE_CLASS(list_iterator)
// define list iterator prototype
typedef void (*list_iterator_add_t)(id, void*);
typedef void (*list_iterator_set_t)(id, void*);
typedef bool (*list_iterator_has_previous_t)(id);
typedef void* (*list_iterator_previous_t)(id);
typedef size_t (*list_iterator_next_index_t)(id);
typedef size_t (*list_iterator_previous_index_t)(id);
// define prototype
#define list_iterator_prototype iterator_prototype;\
                                size_t cursor;\
                                int change;\
                                list_iterator_add_t add;\
                                list_iterator_set_t set;\
                                list_iterator_has_previous_t has_previous;\
                                list_iterator_previous_t previous;\
                                list_iterator_next_index_t next_index;\
                                list_iterator_previous_index_t previous_index

// define list iterator interface
typedef list_iterator (*list_iterable_create_list_iterator_t)(id, size_t);
#define list_iterable_interface \
        list_iterable_create_list_iterator_t create_list_iterator
                                      
/* Iterator */
extern bool list_iterator_has_next(id self) ;
/* List iterator */
extern bool list_iterator_has_previous(id self);
extern size_t list_iterator_next_index(id self);
extern size_t list_iterator_previous_index(id self);
END_DEFINE_CLASS(list_iterator)
#endif	/* LIST_ITERATOR_H */

