/* 
 * File:   hashmap.h
 * Author: Yirui Zhang
 *
 * Created on January 25, 2013, 9:52 PM
 * 
 *  blib is a object-oriented c library of common data structures and 
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

#ifndef HASHMAP_H
#define	HASHMAP_H
#include <bcplib/core/bcplib_base.h>
#include <bcplib/container/map.h>
#include <bcplib/container/arraylist.h>
/*----- Begin of class hashmap entry -----*/
BEGIN_DEFINE_CLASS(hashmap_entry)
#define hashmap_entry_prototype     map_entry_prototype;\
                                    hashmap_entry next;\
                                    size_t hash
END_DEFINE_CLASS(hashmap_entry)
/*----- Begin of class hashmap iterator -----*/
BEGIN_DEFINE_CLASS(hashmap_iterator)
#define hashmap_iterator_prototype  iterator_prototype;\
                                    hashmap_entry next_ent;\
                                    size_t next_slot
        
bool hashmap_iterator_has_next(id self);
void* hashmap_iterator_next(id self);
void hashmap_iterator_remove(id self);
END_DEFINE_CLASS(hashmap_iterator)
/*----- Begin of class hashmap key iterator -----*/
BEGIN_DEFINE_CLASS(hashmap_key_iterator)
#define hashmap_key_iterator_prototype    hashmap_iterator_prototype
void* hashmap_key_iterator_next(id self);
END_DEFINE_CLASS(hashmap_key_iterator)
/*----- Begin of class hashmap value iterator -----*/
BEGIN_DEFINE_CLASS(hashmap_value_iterator)
#define hashmap_value_iterator_prototype  hashmap_iterator_prototype
void* hashmap_value_iterator_next(id self);
END_DEFINE_CLASS(hashmap_value_iterator)        
/*----- Begin of class hashmap entry set -----*/
BEGIN_DEFINE_CLASS(hashmap_entry_set)
#define hashmap_entry_set_prototype     set_prototype;\
                                        hashmap _host
iterator hashmap_entry_set_create_iterator(id self);

END_DEFINE_CLASS(hashmap_entry_set)
/*----- Begin of class hashmap key set -----*/
BEGIN_DEFINE_CLASS(hashmap_key_set)
#define hashmap_key_set_prototype       set_prototype
END_DEFINE_CLASS(hashmap_key_set)
/*----- Begin of class hashmap values -----*/
BEGIN_DEFINE_CLASS(hashmap_values)
#define hashmap_values_prototype        collection_prototype
END_DEFINE_CLASS(hashmap_values)
/*----- Begin of class hashmap -----*/
BEGIN_DEFINE_CLASS(hashmap)
#define HASHMAP_INIT_COMPARATOR 1
#define HASHMAP_INIT_HASHER (HASHMAP_INIT_COMPARATOR << 1)
#define HASHMAP_INIT_FACTOR (HASHMAP_INIT_HASHER << 1)
#define HASHMAP_INIT_CAPACITY   (HASHMAP_INIT_FACTOR << 1)
#define HASHMAP_INIT_MAP    (HASHMAP_INIT_CAPACITY << 1)
        
#define hashmap_prototype   map_prototype; \
                            hashmap_entry* _table; \
                            size_t _size; \
                            size_t _capacity; \
                            float _load_factor
/* Functions from map class. */        
void hashmap_clear(id self);
bool hashmap_contains_key(id self, void* key);
bool hashmap_contains_value(id self, void* key, comparator cmp);
set hashmap_entry_set(id self);
void* hashmap_get(id self, void* key);
bool hashmap_is_empty(id self);
set hashmap_key_set(id self);
void* hashmap_put(id self, void* key, void* value);
void hashmap_put_all(id self, id m);
void* hashmap_remove(id self, void* key);
size_t hashmap_size(id self);
collection hashmap_values(id self);
END_DEFINE_CLASS(hashmap)
      
#endif	/* HASHMAP_H */

