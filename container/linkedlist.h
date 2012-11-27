/* 
 * File:   linkedlist.h
 * Author: Yirui Zhang
 *
 * Created on November 23, 2012, 5:32 AM
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
 * A implementation of double circled linked list. 
 * Like Java, this linked list never expose its internal node to user.
 * Sub-classes should follow this rule.
 */

#ifndef LINKEDLIST_H
#define	LINKEDLIST_H
#include "list.h"

// define class
DEFINE_CLASS(bcplib_linkedlist, linkedlist);
DEFINE_CLASS(bcplib_list_iterator, linkedlist_list_iterator);
// define function types
typedef void (*linkedlist_append_t)(id, void*);
typedef void (*linkedlist_prepend_t)(id, void*);
typedef void* (*linkedlist_first_t)(id);
typedef void* (*linkedlist_last_t)(id);
typedef void* (*linkedlist_remove_first_t)(id);
typedef void* (*linkedlist_remove_last_t)(id);
// define node types
typedef struct bcplib_linkedlist_node linkedlist_node_t;
typedef linkedlist_node_t* linkedlist_node;
// define prototype
#define linkedlist_prototype    list_prototype;\
                                size_t linkedlist_size;\
                                linkedlist_node head;\
                                linkedlist_append_t append;\
                                linkedlist_prepend_t prepend;\
                                linkedlist_first_t first;\
                                linkedlist_last_t last;\
                                linkedlist_remove_first_t remove_first;\
                                linkedlist_remove_last_t remove_last
// define c structure
struct bcplib_linkedlist{
    linkedlist_prototype;
};
// define init. finalize functions
extern inline void linkedlist_init(id obj);
extern inline void linkedlist_finalize(id obj);
// define creation and destruction
extern linkedlist linkedlist_create();
extern linkedlist linkedlist_create_by_comparator(comparator cmp);
extern void linkedlist_destroy(id obj);
/* Linked List */
extern void linkedlist_append(id obj, void* data);
extern void linkedlist_prepend(id obj, void* data);
extern void* linkedlist_first(id obj);
extern void* linkedlist_last(id obj);
extern void* linkedlist_remove_first(id obj);
extern void* linkedlist_remove_last(id obj);
/* List */
extern void linkedlist_add_at(id obj, size_t idx, void* data);
extern void* linkedlist_get(id obj, size_t idx);
extern void* linkedlist_set(id obj, size_t idx, void* data);
extern void* linkedlist_remove_at(id obj, size_t idx);
extern size_t linkedlist_index_of(id obj, void* data);
extern size_t linkedlist_last_index_of(id obj, void* data);
/* Collection */
extern bool linkedlist_add(id obj, void* data);
extern bool linkedlist_remove(id obj, void* data);
extern void linkedlist_clear(id obj);
extern size_t linkedlist_size(id obj);
/* List iterator interface */
extern list_iterator linkedlist_create_list_iterator(id obj, size_t idx);
/* Iterator functions */
extern void* linkedlist_iterator_next(id obj);
extern void linkedlist_iterator_remove(id obj);
/* List iterator */
extern void linkedlist_list_iterator_destroy(id obj);
extern void linkedlist_list_iterator_add(id obj, void* data);
extern void linkedlist_list_iterator_set(id obj, void* data);
extern void* linkedlist_list_iterator_previous(id obj);
#endif	/* LINKEDLIST_H */

