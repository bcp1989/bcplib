/* 
 * File:   string.h
 * Author: Yirui Zhang
 *
 * Created on January 25, 2013, 12:13 AM
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

#ifndef STRING_H
#define	STRING_H
#include <bcplib/core/bcplib_base.h>
BEGIN_DEFINE_CLASS(string)
typedef enum {
    LOWER_CASE = 1, UPPER_CASE
}string_case_t;
typedef size_t (*string_length_t)(id);
typedef char (*string_char_at_t)(id, size_t);
typedef string (*string_concat_t)(id, id);
typedef bool (*string_start_with_t)(id, id);
typedef bool (*string_end_with_t)(id, id);
typedef size_t (*string_index_of)(id, id, size_t, size_t);
typedef string (*string_sub_string)(id, size_t, size_t);
typedef string (*string_change_case)(id, )
// prototype of string class
#define string_prototype    object_prototype; \
                            char* _value; \
                            size_t _length; \
                            
                            
END_DEFINE_CLASS(string)
#endif	/* STRING_H */

