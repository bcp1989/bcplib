/* 
 * File:   bitmap.h
 * Author: bcp1989
 *
 * Created on June 10, 2012, 3:37 PM
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
 * Bitmap
 * A simple OO implementation of bitmap, can't be extended (but can be 
 * inherited).
 * 
 * ChangeList
 * ----------
 * 11/1/2012
 * + add common function of bitmap, such as set, flip...
 * + change to OO, inherit base class.
 * 
 * TODO
 * ----
 * 1. Add assert test for all function.
 * 2. Need to write separate test module.
 * 3. Change to non-final class.
 */

#ifndef BITMAP_H
#define	BITMAP_H
#include <stddef.h>
#include <stdint.h>
#include "lib_base.h"

DEFINE_CLASS(bcplib_bitmap, bitmap);

typedef uint32_t bit_elem;

typedef struct bcplib_bitmap {
    object_prototype;
    size_t bit_num;
    bit_elem *bits;
    void (*set)(bitmap b, size_t idx);
    void (*clear)(bitmap b, size_t idx);
    bool (*test)(bitmap b, size_t idx);
    void (*flip)(bitmap b, size_t idx);
    void (*set_multiple)(bitmap b, size_t n, size_t idxs, ...);
    void (*clear_multiple)(bitmap b, size_t n, size_t idxs, ...);
    void (*set_all)(bitmap b);
    void (*clear_all)(bitmap b);
}bitmap_t;

extern bitmap bitmap_create(size_t bits_num);
extern bitmap bitmap_destroy(bitmap b);

#endif	/* BITMAP_H */

