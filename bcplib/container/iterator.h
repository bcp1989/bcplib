/* 
 * File:   iterator.h
 * Author: Yirui Zhang
 *
 * Created on November 1, 2012, 9:00 PM
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

#ifndef ITERATOR_H
#define	ITERATOR_H
#include "bcplib_base.h"
#include "object.h"

DEFINE_CLASS(bcplib_iterator, iterator);

// define iterator interface
typedef iterator (*iterator_create_iterator_t)(id);
#define iterable_interface      iterator_create_iterator_t create_iterator
                                
// define iterator prototype
typedef bool (*iterator_has_next_t)(id);
typedef void* (*iterator_next_t)(id);
typedef void (*iterator_remove_t)(id);
#define iterator_prototype      object_prototype;\
                                id host;\
                                id aux;\
                                iterator_has_next_t has_next;\
                                iterator_next_t next;\
                                iterator_remove_t remove

struct bcplib_iterator {
    iterator_prototype;
};


extern inline void iterator_init(id obj, id host, id aux);
extern inline void iterator_finalize(id obj);
#endif	/* ITERATOR_H */

