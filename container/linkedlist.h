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
/* Begin of class linkedlist_iterator. */
BEGIN_DEFINE_CLASS(linkedlist_iterator)
#define linkedlist_iterator_prototype      extends(list_iterator)
END_DEFINE_CLASS(linkedlist_iterator)
        
/* Begin of class linkedlist node. */
BEGIN_DEFINE_CLASS(linkedlist_node)
// node prototype
#define linkedlist_node_prototype   extends(object);\
                                    linkedlist_node prev;\
                                    linkedlist_node next;\
                                    void* data
END_DEFINE_CLASS(linkedlist_node)
        
/* Begin of class linkedlist. */
BEGIN_DEFINE_CLASS(linkedlist)
// define function types
typedef void (*linkedlist_append_t)(id, void*);
typedef void (*linkedlist_prepend_t)(id, void*);
typedef void* (*linkedlist_first_t)(id);
typedef void* (*linkedlist_last_t)(id);
typedef void* (*linkedlist_remove_first_t)(id);
typedef void* (*linkedlist_remove_last_t)(id);
// linkedlist prototype
#define linkedlist_prototype    list_prototype;\
                                size_t linkedlist_size;\
                                linkedlist_node head;\
                                linkedlist_append_t append;\
                                linkedlist_prepend_t prepend;\
                                linkedlist_first_t first;\
                                linkedlist_last_t last;\
                                linkedlist_remove_first_t remove_first;\
                                linkedlist_remove_last_t remove_last

/* Linked List */
extern void linkedlist_append(id self, void* data);
extern void linkedlist_prepend(id self, void* data);
extern void* linkedlist_first(id self);
extern void* linkedlist_last(id self);
extern void* linkedlist_remove_first(id self);
extern void* linkedlist_remove_last(id self);
/* List */
extern void linkedlist_add_at(id self, size_t idx, void* data);
extern void* linkedlist_get(id self, size_t idx);
extern void* linkedlist_set(id self, size_t idx, void* data);
extern void* linkedlist_remove_at(id self, size_t idx);
extern size_t linkedlist_index_of(id self, void* data);
extern size_t linkedlist_last_index_of(id self, void* data);
/* Collection */
extern bool linkedlist_add(id self, void* data);
extern bool linkedlist_remove(id self, void* data);
extern void linkedlist_clear(id self);
extern size_t linkedlist_size(id self);
/* List iterator interface */
extern list_iterator linkedlist_create_list_iterator(id self, size_t idx);
/* Iterator functions */
extern void* linkedlist_iterator_next(id self);
extern void linkedlist_iterator_remove(id self);
/* List iterator */
extern void linkedlist_list_iterator_add(id self, void* data);
extern void linkedlist_list_iterator_set(id self, void* data);
extern void* linkedlist_list_iterator_previous(id self);
END_DEFINE_CLASS(linkedlist)

#endif	/* LINKEDLIST_H */

