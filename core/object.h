/* 
 * File:   object.h
 * Author: Yirui Zhang
 *
 * Created on November 25, 2012, 11:00 PM
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

#ifndef OBJECT_H
#define	OBJECT_H
#include "bcplib_base.h"
BEGIN_DEFINE_CLASS(object)
#define INIT_DEFAULT    0
/* Define function type of 'equals' */
typedef bool (*object_equals_t)(id, id);
/* Prototype of class *Object */
#define object_prototype                     int32_t magic_number;\
                                             class class;\
                                             object_equals_t equals;\
/* Functions of Object */
extern int object_equals(id self, id that);

END_DEFINE_CLASS(object)
#endif	/* OBJECT_H */

