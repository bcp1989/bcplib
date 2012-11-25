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
#include "lib_base.h"
#include "iterator.h"
// define class
DEFINE_CLASS(bcplib_list_iterator, list_iterator);
// define list iterator interface
typedef list_iterator (*list_iterator_create_list_iterator_t)(id, size_t);
#define list_iterator_interface \
        list_iterator_create_list_iterator_t create_list_iterator
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
                                list_iterator_previous_index_t previous_index;                                        

// define core structure
typedef struct bcplib_list_iterator {
    list_iterator_prototype;
}list_iterator_t;
// init. and finalize function
extern inline void list_iterator_init(id obj, id host, id aux);
extern inline void list_iterator_finalize(id obj);
/* Iterator */
extern bool list_iterator_has_next(id obj) ;
/* List iterator */
extern bool list_iterator_has_previous(id obj);
extern size_t list_iterator_next_index(id obj);
extern size_t list_iterator_previous_index(id obj);
#endif	/* LIST_ITERATOR_H */

