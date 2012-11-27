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
#include "bcplib_base.h"
#include "object.h"

DEFINE_CLASS(bcplib_bitmap, bitmap);

typedef uint32_t bit_elem;

typedef void (*bitmap_set_t)(bitmap b, size_t idx);
typedef void (*bitmap_clear_t)(bitmap b, size_t idx);
typedef bool (*bitmap_test_t)(bitmap b, size_t idx);
typedef void (*bitmap_flip_t)(bitmap b, size_t idx);
typedef void (*bitmap_set_multiple_t)(bitmap b, size_t n, size_t idxs, ...);
typedef void (*bitmap_clear_multiple_t)(bitmap b, size_t n, size_t idxs, ...);
typedef void (*bitmap_set_all_t)(bitmap b);
typedef void (*bitmap_clear_all_t)(bitmap b);

#define bitmap_prototype        object_prototype;\
                                size_t bit_num;\
                                bit_elem *bits;\
                                bitmap_set_t set;\
                                bitmap_clear_t clear;\
                                bitmap_test_t test;\
                                bitmap_flip_t flip;\
                                bitmap_set_multiple_t set_multiple;\
                                bitmap_clear_multiple_t clear_multiple;\
                                bitmap_set_all_t set_all;\
                                bitmap_clear_all_t clear_all


struct bcplib_bitmap {
    bitmap_prototype;
};

extern bitmap bitmap_create_by_bits_num(size_t bits_num);
extern void bitmap_destroy(id obj);

#endif	/* BITMAP_H */

