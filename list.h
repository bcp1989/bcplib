/* 
 * File:   list.h
 * Author: Yirui Zhang
 *
 * Created on November 1, 2012, 5:56 PM
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

#ifndef LIST_H
#define	LIST_H
#include "collection.h"
#include "list_iterator.h"
// define class
DEFINE_CLASS(bcplib_list, list);
// define function types
typedef void (*list_add_at_t)(id, size_t, void*);
typedef void* (*list_get_t)(id, size_t);
typedef void* (*list_set_t)(id, size_t, void*);
typedef void* (*list_remove_at_t)(id, size_t);
typedef size_t(*list_index_of_t)(id, void*);
typedef size_t(*list_last_index_of_t)(id, void*);
#define list_prototype  collection_prototype;\
                        list_iterator_interface;\
                        list_add_at_t add_at;\
                        list_get_t get;\
                        list_set_t set;\
                        list_remove_at_t remove_at;\
                        list_index_of_t index_of;\
                        list_last_index_of_t last_index_of
// define structure
typedef struct bcplib_list {
    list_prototype;
} list_t;
// define init. finalize functions.
extern inline void list_init(id obj);
extern inline void list_finalize(id obj);

/* Functions of list */
extern bool list_add(id obj, void* user_data);
extern size_t list_index_of(id, void*);
extern size_t list_last_index_of(id, void*);
extern iterator list_create_iterator(id);
/* utilities */
extern inline void check_index_range(size_t idx, size_t from, size_t to);
#endif	/* LIST_H */

