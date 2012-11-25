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
#include "linkedlist.h"

/*
 * bcplib
 */

int my_compare(void* data1, void* data2) {
    assert(data1 != NULL && data2 != NULL);
    return ((*((int *)data1)) - (*((int *) data2)));
}

int main(int argc, char** argv) {
    // simple test for bitmap
    //arraylist l = arraylist_create_by_size_comparator(1000, my_compare);
    linkedlist l = linkedlist_create_by_comparator(my_compare);
    size_t i = 0;
    for (i = 0; i < 10000; ++i) {
        int *tmp = (int *) malloc(sizeof (int));
        *tmp = i;
        l->add(l, tmp);
    }
    int intv = 445;
    printf("index of 445: %d\n", l->index_of(l, &intv));
    iterator itr = l->create_iterator(l);
    while (itr->has_next(itr)) {
        int *tmp = (int *) itr->next(itr);
        //printf("%d\n", *tmp);
        itr->remove(itr);
    }
    l->destroy_iterator(l, itr);
    printf("%d %d\n", l->is_empty(l), l->size(l));
    linkedlist_destroy(l);
    //arraylist_destroy(l);
    printf("%d\n", sizeof (linkedlist_t));
    return (EXIT_SUCCESS);
}

