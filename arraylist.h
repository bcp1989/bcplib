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
#include "bcplib_base.h"
#include "list.h"

DEFINE_CLASS(bcplib_arraylist, arraylist);
DEFINE_CLASS(bcplib_list_iterator, arraylist_list_iterator);
// define array prototype
typedef void (*arraylist_trim_to_size_t)(id);
typedef void (*arraylist_ensure_capacity_t)(id, size_t);
#define arraylist_prototype     list_prototype;\
                                void** elements;\
                                size_t capacity;\
                                size_t arraylist_size;\
                                arraylist_trim_to_size_t trim_to_size;\
                                arraylist_ensure_capacity_t ensure_capacity

struct bcplib_arraylist {
    arraylist_prototype;
};

// init. and finalize
extern inline void arrayliast_init(id obj);
extern inline void arraylist_init_by_size(id obj, size_t size);
extern inline void arraylist_finalize(id obj);
// Creation
extern arraylist arraylist_create();
extern arraylist arraylist_create_by_size(size_t size);
extern arraylist arraylist_create_by_comparator(comparator cmp);
extern arraylist arraylist_create_by_size_comparator(size_t size, comparator cmp);
extern arraylist arraylist_create_by_data(void** init_data, size_t size);
extern arraylist arraylist_create_by_collection(id obj);
// Destruction functions.
extern void arraylist_destroy(id obj);

/* Functions of arraylist class */
/* Collection functions */
extern bool arraylist_remove(id obj, void* user_data);
extern void arraylist_clear(id obj);
extern size_t arraylist_size(id obj);
extern bool arraylist_is_empty(id obj);
extern bool arraylist_contains(id obj, void* user_data);
/* List functions */
extern void arraylist_add_at(id obj, size_t idx, void* user_data);
extern void* arraylist_get(id obj, size_t idx);
extern void * arraylist_set(id obj, size_t idx, void* user_data);
extern void* arraylist_remove_at(id obj, size_t idx);
extern size_t arraylist_index_of(id obj, void* user_data);
extern size_t arraylist_last_index_of(id obj, void* user_data);
/* List iterator interface */
extern list_iterator arraylist_create_list_iterator(id obj, size_t idx);
/* Array list function */
extern void arraylis_trim_to_size(id obj);
extern void arraylist_ensure_capacity(id obj, size_t new_cap);
/* Iterator functions */
extern void* arraylist_iterator_next(id obj);
extern void arraylist_iterator_remove(id obj);
/* List iterator functions */
extern void arraylist_list_iterator_destroy(id obj);
extern void arraylist_list_iterator_add(id obj, void* user_data);
extern void arraylist_list_iterator_set(id obj, void* user_data);
extern void* arraylist_list_iterator_previous(id obj);
#endif	/* ARRAYLIST_H */

