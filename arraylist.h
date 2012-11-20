/* 
 * File:   arraylist.h
 * Author: Yirui Zhang
 *
 * Created on November 2, 2012, 4:06 PM
 * 
 *  bcplib is a c library of common data structures and algorithms. Not like 
 *  glib, the main design of bcplib is to make all data structures independent, 
 *  which means user only need to include normally several non-system header 
 *  files to use a specific data structure or algorithm.
 *  Currently, bcplib is developed on gcc-4.
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
#include "lib_base.h"
#include "list.h"
DEFINE_CLASS(bcplib_arraylist, arraylist);
// define array prototype
typedef void (*arraylist_trim_to_size_t)(id);
typedef void (*arraylist_ensure_capacity_t)(id, size_t);
#define arraylist_prototype     list_prototype;\
                                void** elements;\
                                size_t capacity;\
                                size_t arraylist_size;\
                                arraylist_trim_to_size_t trim_to_size;\
                                arraylist_ensure_capacity_t ensure_capacity
                                

typedef struct bcplib_arraylist {
    arraylist_prototype;
} arraylist_t;

extern inline void arrayliast_init(id obj);
extern inline void arraylist_init_by_size(id obj, size_t size);
extern inline void arraylist_finalize(id obj);
extern arraylist arraylist_create();
extern arraylist arraylist_create_by_size(size_t size);
extern arraylist arraylist_create_by_comparator(comparator cmp);
extern arraylist arratlist_create_by_size_comparator(size_t size, comparator cmp);
extern arraylist arraylist_create_by_data(void** init_data, size_t size);
extern arraylist arraylist_create_by_collection(id obj);

extern arraylist arraylist_destory(arraylist obj);


#endif	/* ARRAYLIST_H */

