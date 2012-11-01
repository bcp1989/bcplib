/* 
 * File:   bitmap.h
 * Author: bcp1989
 *
 * Created on June 10, 2012, 3:37 PM
 * 
 *  bcplib is a c library of common data structures and algorithms. Not like 
 *  glib, the main design of bcplib is to make all data structures independent, 
 *  which means user only need to include normally 1 or 2 non-system header 
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

#ifndef BITMAP_H
#define	BITMAP_H
#include <stddef.h>

typedef struct bitmap {
    size_t bit_num;
    bit_elem *bits;    
    
}BITMAP;

extern struct bitmap *bitmap_create (size_t bits_num);
extern struct bitmap *bitmap_destory (struct bitmap *bitmap);
extern size_t bitmap_size (struct bitmap *b);
extern void bitmap_set (struct bitmap *b, size_t idx);
extern void bitmap_clear (struct bitmap *b, size_t idx);
extern int bitmap_test (struct bitmap *b, size_t idx);
extern void bitmap_flip (struct bitmap *b, size_t idx);
extern void bitmap_set_multiple (struct bitmap *b, size_t n, size_t idxs, ...);
extern void bitmap_clear_multiple (struct bitmap *b, size_t n, size_t idxs, ...);
extern void bitmap_set_all (struct bitmap *b);
extern void bitmap_clear_all (struct bitmap *b);
#endif	/* BITMAP_H */

