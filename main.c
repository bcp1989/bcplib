/* 
 * File:   main.c
 * Author: Yirui Zhang
 * Created on October 31, 2012, 11:11 PM
 * 
 *  bcplib is a OO c library of common data structures and algorithms. 
 *  The philosophy of bcplib is to build a easy-to-use, easy-to-extend library.
 *  And I also try to make all modules independent so that user may only need
 *  a very limit subset of bcplib to run a specific module.
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

#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"
#include "arraylist.h"

/*
 * bcplib
 * 
 * ChangeList
 * ----------
 * 11/1/2012
 * + add bitmap
 * + add iterator, collection, lib_base, list
 * 
 * TODO
 * ----
 * 1. document
 * 2. Need to check pointer type inside each function, to make sure the pointer
 *    is inherit/*extends* a specific class. Don't know how right now.
 * 3. arraylist, linkedlist, set, map, hashmap, hashset, treeset, treemap
 */
int main(int argc, char** argv) {
    // simple test for bitmap
    arraylist al = arraylist_create_by_size(1);
    size_t i = 0;
    for (i = 0; i < 15; ++i) {
        int *tmp = (int *) malloc (sizeof(int));
        *tmp = i;
        al->add(al, tmp);
    }
    for (i = 0; i < 15; ++i) {
        int *tmp = (int *)al->remove_at(al, 0);
        printf ("%d\n", *tmp);
        free(tmp);
    }

    return (EXIT_SUCCESS);
}

