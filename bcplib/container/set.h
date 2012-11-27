/* 
 * File:   Set.h
 * Author: Yirui Zhang
 *
 * Created on November 24, 2012, 5:42 PM
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
 * Abstract class Set.
 */

#ifndef SET_H
#define	SET_H
#include "collection.h"
// define class
DEFINE_CLASS(bcplib_set, set);
// define prototype
#define set_prototype   collection_prototype
// define c structure
struct bcplib_set {
    set_prototype;
};

extern void set_init(id obj);
extern void set_finalize(id obj);

#endif	/* SET_H */

