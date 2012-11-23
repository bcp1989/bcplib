/* 
 * File:   main.c
 * Author: Yirui Zhang
 * Created on October 31, 2012, 11:11 PM
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

#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"
#include "arraylist.h"

/*
 * bcplib
 */
int main(int argc, char** argv) {
    // simple test for bitmap
    arraylist al = arraylist_create_by_size(1000);
    size_t i = 0;
    for (i = 0; i < 10000; ++i) {
        int *tmp = (int *) malloc(sizeof (int));
        *tmp = i;
        ((collection)al)->add(al, tmp);
    }

    iterator itr = al->create_iterator(al);
    while (itr->has_next(itr)) {
        int *tmp = (int *)itr->next(itr);
        printf ("%d\n", *tmp);
        itr->remove(itr);
    }
    al->destory_iterator(al, itr);
    printf ("%d %d\n", al->is_empty(al), al->size(al));
    arraylist_destroy(al);
    return (EXIT_SUCCESS);
}

