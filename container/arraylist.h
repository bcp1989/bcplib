/* 
 * File:   arraylist.h
 * Author: Yirui Zhang
 *
 * Created on November 2, 2012, 4:06 PM
 * 
 *  bcplib is a object-oriented C language library of common data structures and 
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

#ifndef ARRAYLIST_H
#define	ARRAYLIST_H
#include <bcplib/core/bcplib_base.h>
#include <bcplib/container/list.h>
BEGIN_DEFINE_CLASS(arraylist_iterator)
#define arraylist_iterator_prototype   extends(list_iterator)
END_DEFINE_CLASS(arraylist_iterator)
        
BEGIN_DEFINE_CLASS(arraylist)
#define ARRAYLIST_INIT_SIZE     (COLLECTION_INIT_COMPARATOR << 1)
#define ARRAYLIST_INIT_DATA     (ARRAYLIST_INIT_SIZE << 1)
#define ARRAYLIST_INIT_COLLECTION   (ARRAYLIST_INIT_DATA << 1)
// define array prototype
typedef void (*arraylist_trim_to_size_t)(id);
typedef void (*arraylist_ensure_capacity_t)(id, size_t);

#define arraylist_prototype     list_prototype;\
                                void** elements;\
                                size_t capacity;\
                                size_t arraylist_size;\
                                arraylist_trim_to_size_t trim_to_size;\
                                arraylist_ensure_capacity_t ensure_capacity


/* Functions of arraylist class */
/* Collection functions */
extern bool arraylist_remove(id self, void* user_data);
extern void arraylist_clear(id self);
extern size_t arraylist_size(id self);
extern bool arraylist_is_empty(id self);
extern bool arraylist_contains(id self, void* user_data);
/* List functions */
extern void arraylist_add_at(id self, size_t idx, void* user_data);
extern void* arraylist_get(id self, size_t idx);
extern void * arraylist_set(id self, size_t idx, void* user_data);
extern void* arraylist_remove_at(id self, size_t idx);
extern size_t arraylist_index_of(id self, void* user_data);
extern size_t arraylist_last_index_of(id self, void* user_data);
/* List iterator interface */
extern list_iterator arraylist_create_list_iterator(id self, size_t idx);
/* Array list function */
extern void arraylis_trim_to_size(id self);
extern void arraylist_ensure_capacity(id self, size_t new_cap);
/* Iterator functions */
extern void* arraylist_iterator_next(id self);
extern void arraylist_iterator_remove(id self);
/* List iterator functions */
extern void arraylist_list_iterator_add(id self, void* user_data);
extern void arraylist_list_iterator_set(id self, void* user_data);
extern void* arraylist_list_iterator_previous(id self);
END_DEFINE_CLASS(arraylist)

#endif	/* ARRAYLIST_H */

