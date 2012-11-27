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
#include "set.h"
#include "map.h"

/*
 * bcplib
 */

int my_compare(void* data1, void* data2) {
    return ((*((int *) data1)) - (*((int *) data2)));
}

int main(int argc, char** argv) {
    // simple test for bitmap
    arraylist l = create2(arraylist, size, 1000, comparator, my_compare);
    //linkedlist l = linkedlist_create_by_comparator(my_compare);
    //linkedlist l = create1(linkedlist, comparator, my_compare);
    size_t i = 0;
    for (i = 0; i < 1000; ++i) {
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
    printf("%s\n", CLASS_TYPE_BY_NAME(linkedlist)->name);
    destroy(itr);
    printf("%d %d\n", l->is_empty(l), l->size(l));
    //linkedlist_destroy(l);
    destroy(l);
    printf("%s %u %s %u %s %u %s %u %s %u %s %u %s %u %s %u\n",
            CLASS_TYPE_BY_NAME(bitmap)->name,
            CLASS_TYPE_BY_NAME(bitmap)->size,
            CLASS_TYPE_BY_NAME(object)->name,
            CLASS_TYPE_BY_NAME(object)->size,
            CLASS_TYPE_BY_NAME(collection)->name,
            CLASS_TYPE_BY_NAME(collection)->size,
            CLASS_TYPE_BY_NAME(list)->name,
            CLASS_TYPE_BY_NAME(list)->size,
            CLASS_TYPE_BY_NAME(set)->name,
            CLASS_TYPE_BY_NAME(set)->size,
            CLASS_TYPE_BY_NAME(map)->name,
            CLASS_TYPE_BY_NAME(map)->size,
            CLASS_TYPE_BY_NAME(arraylist)->name,
            CLASS_TYPE_BY_NAME(arraylist)->size,
            CLASS_TYPE_BY_NAME(linkedlist)->name,
            CLASS_TYPE_BY_NAME(linkedlist)->size);
    return (EXIT_SUCCESS);
}

