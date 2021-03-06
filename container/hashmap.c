#include "hashmap.h"
/*----- Begin of hashmap entry class -----*/
INIT_CLASS(hashmap_entry, map_entry, TYPE_NORMAL_CLASS);

BEGIN_IMPL_INITIALIZER(hashmap_entry)
init_super(flag);
self->next = next_arg(hashmap_entry);
self->hash = next_arg(size_t);
END_IMPL_INITIALIZER(hashmap_entry)

BEGIN_IMPL_FINALIZER(hashmap_entry)
// do nothing
END_IMPL_FINALIZER(hashmap_entry)
/*----- Begin of class hashmap iterator -----*/
#define hashmap_iterator_find_next(next_slot, len, next_ent, ents) \
        while ((next_slot) < (len) && ((next_ent) = (ents)[(next_slot)++]) == NULL)
INIT_CLASS(hashmap_iterator, iterator, TYPE_NORMAL_CLASS);
/* Initializer of class hashmap iterator */
BEGIN_IMPL_INITIALIZER(hashmap_iterator)
init_super(flag);
// init functions.
self->has_next = hashmap_iterator_hash_next;
self->next = hashmap_iterator_next;
self->remove = hashmap_iterator_remove;
// init data.
hashmap hm = cast(hashmap, self->host);
self->next_slot = 0;
self->aux = NULL;
hashmap_entry ents = hm->_table;
hashmap_iterator_find_next(self->next_slot, hm->_size, self->next_ent, ents);
END_IMPL_INITIALIZER(hashmap_iterator)
/* Finalizer if class hashmap iterator */
BEGIN_IMPL_FINALIZER(hashmap_iterator)
// do nothing
END_IMPL_FINALIZER(hashmap_iterator)

bool hashmap_iterator_hash_next(id self) {
    hashmap_iterator itr = cast(hashmap_iterator, self);
    return itr->aux != NULL;
}

void* hashmap_iterator_next(id self) {
    hashmap_iterator itr = cast(hashmap_iterator, self);
    hashmap hm = cast(hashmap, itr->host);
    itr->aux = (void*) itr->next_ent;
    itr->next_ent = itr->next_ent->next;
    if (itr->next_ent == NULL) {    // the last elements in the current slot
        hashmap_entry* ents = hm->_table;
        hashmap_iterator_find_next(itr->next_slot, hm->_size, itr->next_ent, ents);
    }
    return itr->aux;
}

void hashmap_iterator_remove(id self) {
    hashmap_iterator itr = cast(hashmap_iterator, self);
    hashmap hm = cast(hashmap, itr->host);
    assert (itr->aux != NULL);
    hashmap_entry curr = cast(hashmap_entry, itr->aux);
    hm->remove(hm, curr->key);
    itr->aux = NULL;
}
/*----- Begin of class hashmap key iterator -----*/
INIT_CLASS(hashmap_key_iterator, hashmap_iterator, TYPE_NORMAL_CLASS);
/* Initializer of class hashmap key iterator */
BEGIN_IMPL_INITIALIZER(hashmap_key_iterator)
init_super(flag);
self->next = hashmap_key_iterator_next;
END_IMPL_INITIALIZER(hashmap_key_iterator)

/* Finalizer of class hashmap key iterator */
BEGIN_IMPL_FINALIZER(hashmap_key_iterator)
// do nothing
END_IMPL_FINALIZER(hashmap_key_iterator)

void* hashmap_key_iterator_next(id self) {
    hashmap_entry ent = (hashmap_entry)hashmap_iterator_next(self);
    return ent->key;
}

/*----- Begin of class hashmap value iterator -----*/
INIT_CLASS(hashmap_value_iterator, hashmap_iterator, TYPE_NORMAL_CLASS);
/* Initializer of class hashmap value iterator */
BEGIN_IMPL_INITIALIZER(hashmap_value_iterator)
init_super(flag);
self->next = hashmap_value_iterator_next;
END_IMPL_INITIALIZER(hashmap_value_iterator)

/* Finalizer of class hashmap value iterator */
BEGIN_IMPL_FINALIZER(hashmap_value_iterator)
// do nothing
END_IMPL_FINALIZER(hashmap_value_iterator)
        
void* hashmap_value_iterator_next(id self) {
    hashmap_entry ent = (hashmap_entry)hashmap_iterator_next(self);
    return ent->value;
}

/*----- Begin of class hashmap entry set -----*/
INIT_CLASS(hashmap_entry_set, set, TYPE_NORMAL_CLASS);
/* Initializer */
BEGIN_IMPL_INITIALIZER(hashmap_entry_set)
init_super(flag);
self->_host = next_arg(hashmap);
END_IMPL_INITIALIZER(hashmap_entry_set)

/* Finalizer*/
BEGIN_IMPL_FINALIZER(hashmap_entry_set)
// do nothing
END_IMPL_FINALIZER(hashmap_entry_set)
        
iterator hashmap_entry_set_create_iterator(id self) {
    hashmap_entry_set hes = cast(hashmap_entry_set, self);
    return new(hashmap_iterator, INIT_DEFAULT, hes, NULL);
}

size_t hashmap_entry_set_size(id self) {
    hashmap_entry_set hes = cast(hashmap_entry_set, self);
    return hes->_host->_size;
}

void hashmap_entry_set_clear(id self) {
    hashmap_entry_set hes = cast(hashmap_entry_set, self);
    hes->_host->clear(hes->_host);
}

bool hashmap_entry_set_contains(id self, void* data) {
    hashmap_entry_set hes = cast(hashmap_entry_set, self);
    hashmap hm = hes->_host;
    if (!kindof(data, hashmap_entry)) {
        return false;
    }
    hashmap_entry ent = (hashmap_entry)data;
    hashmap_entry result = hashmap_get_entry(hm, ent->key);
    return result != NULL && hes->compare(result, ent);
}
        
bool hashmap_entry_set_remove(id self, void* data) {
    hashmap_entry_set hes = cast(hashmap_entry_set, self);
    hashmap hm = hes->_host;
    if (!kindof(data, hashmap_entry)) {
        return false;
    }
    hashmap_entry ent = (hashmap_entry)data;
    // TODO
}
/*----- Begin of class hashmap key set -----*/
INIT_CLASS(hashmap_key_set, set, TYPE_NORMAL_CLASS);

/*----- Begin of class hashmap values -----*/
INIT_CLASS(hashmap_values, collection, TYPE_NORMAL_CLASS);

/*----- Begin of hashmap class -----*/
#define DEFAULT_CAPACITY 16
#define MAX_CAPACITY    (1 << 30)
#define DEFAULT_LOAD_FACTOR 0.75
INIT_CLASS(hashmap, map, TYPE_NORMAL_CLASS);

// Default comparator
static int hashmap_comparator(void* data1, void* data2);
// Default hasher
static size_t hashmap_hasher(void* user_data);
// Sub-init functions
static void hashmap_init(hashmap self, size_t capacity);

BEGIN_IMPL_INITIALIZER(hashmap)
init_super(flag);
// init function pointer
// TODO
// init data
// init comparator
if (bit_test(flag, HASHMAP_INIT_COMPARATOR)) {
    self->comparator = next_arg(comparator);
} else {
    self->comparator = hashmap_comparator;
}
// init hasher
if (bit_test(flag, HASHMAP_INIT_HASHER)) {
    self->hasher = next_arg(hasher);
} else {
    self->hasher = hashmap_hasher;
}
// init factor
if (bit_test(flag, HASHMAP_INIT_FACTOR)) {
    self->_load_factor = (float) next_arg(double);
    assert(self->_load_factor > 0 && self->_load_factor <= 1.f);
} else {
    self->_load_factor = DEFAULT_LOAD_FACTOR;
}
// init table related
if (bit_test(flag, HASHMAP_INIT_CAPACITY)) {
    hashmap_init(self, next_arg(size_t));
} else if (bit_test(flag, HASHMAP_INIT_MAP)) {
    map m = next_arg(map);
    hashmap_init(self, bcplib_max(m->size(m),
            DEFAULT_CAPACITY) / self->_load_factor);
    self->put_all(self, m);
} else {
    hashmap_init(self, DEFAULT_CAPACITY);
}
END_IMPL_INITIALIZER(hashmap)

BEGIN_IMPL_FINALIZER(hashmap)
assert(self->_table);
bcplib_free(self->_table);

END_IMPL_FINALIZER(hashmap)

static
int hashmap_comparator(void* data1, void* data2) {
    return data1 == data2;
}

static
size_t hashmap_hasher(void* user_data) {
    return (size_t) user_data;
}

static
void hashmap_init(hashmap self, size_t capacity) {
    self->_size = 0;
    self->_table = bcplib_calloc(capacity, sizeof (hashmap_entry));
    self->_capacity = DEFAULT_CAPACITY;
}

static inline
size_t hashmap_hash(hashmap hm, void* key) {
    if (key == NULL) {
        return 0;
    } else {
        return hm->hasher(key);
    }
}

static inline
size_t hashmap_index_for(size_t index, size_t size) {
    return index & (size - 1);
}

static inline
bool hashmap_beyond_threshold(hashmap hm) {
    return hm->_size / hm->_capacity > hm->_load_factor;
}

static inline
bool hashmap_key_equals(comparator cmp, 
        size_t h1, size_t h2, void* k1, void* k2) {
    return (h1 == h2) && (k1 == k2 || !cmp(k1, k2));
}

static
hashmap_entry hashmap_get_entry(hashmap hm, void* key) {
    size_t hash = hashmap_hash(hm, key);
    hashmap_entry ent = NULL;
    void* k = NULL;
    // find which slot the key in
    size_t slot_index = hashmap_index_for(hash, hm->_capacity);
    for (ent = hm->_table[slot_index]; ent != NULL; ent = ent->next) {
        // compare hash value of the key then the key itself
        if (hashmap_key_equals(hm->comparator, hash, key, ent->hash, ent->key)) {
            return ent;
        }
    }
    return NULL;
}

static
void hashmap_resize(hashmap hm, size_t new_cap) {
    size_t old_cap = hm->_capacity;
    if (old_cap == MAX_CAPACITY) {
        return;
    }
    hashmap_entry* old_ents = hm->_table;
    hashmap_entry* new_ents = bcplib_calloc(new_cap, sizeof (hashmap_entry));
    hashmap_entry ent = NULL, next = NULL;
    size_t i = 0, len = hm->_size, new_index = 0;
    for (i = 0; i < len; ++i) {
        for (ent = old_ents[i]; ent != NULL;) {
            next = ent->next;
            new_index = hashmap_index_for(ent->hash, new_cap);
            ent->next = new_ents[new_index];
            new_ents[new_index] = ent;
            ent = next;
        }// for - entry
    }// for - slot
}

static
void hashmap_add_entry(hashmap hm, void* key, void* value) {
    if (hashmap_beyond_threshold(hm)) {
        hashmap_resize(hm, hm->_capacity << 1);
    }
    size_t hash = hashmap_hash(hm, key);
    size_t index = hashmap_index_for(hash, hm->_capacity);
    hashmap_entry old_head = hm->_table[index];
    hm->_table[index] = new(hashmap_entry, INIT_DEFAULT,
            key, value, old_head, hash);
    ++hm->_size;
}

void hashmap_clear(id self) {
    hashmap hm = cast(hashmap, self);
    hashmap_entry* ents = hm->_table;
    size_t i = 0, len = hm->_size;
    hashmap_entry ent = NULL;
    hashmap_entry next = NULL;
    // free each slot
    for (i = 0; i < len; ++i) {
        // free entries in each slot
        for (ent = ents[i]; ent != NULL;) {
            next = ent->next;
            destroy(ent);
            ent = next;
        }
        ents[i] = NULL;
    }
    // reset the size
    hm->_size = 0;
}

bool hashmap_contains_key(id self, void* key) {
    hashmap hm = cast(hashmap, self);
    return hashmap_get_entry(hm, key);
}

bool hashmap_contains_value(id self, void* value, comparator cmp) {
    hashmap hm = cast(hashmap, self);
    size_t i = 0, len = hm->_size;
    hashmap_entry ent = NULL;
    hashmap_entry ents = hm->_table;
    void* k = NULL;
    for (i = 0; i < len; ++i) {
        for (ent = ents[i]; ent != NULL; ent = ent->next) {
            if ((k = ent->value) == value || (cmp != NULL && !cmp(k, value))) {
                return true;
            }// if
        }// for - entry
    }// for - slot
    return false;
}

set hashmap_entry_set(id self) {

}

void* hashmap_get(id self, void* key) {
    hashmap hm = cast(hashmap, self);
    hashmap_entry ent = hashmap_get_entry(hm, key);
    return ent == NULL ? NULL : ent->value;
}

bool hashmap_is_empty(id self) {
    return hashmap_size(self) == 0;
}

set hashmap_key_set(id self) {

}

void* hashmap_put(id self, void* key, void* value) {
    hashmap hm = cast(hashmap, self);
    hashmap_entry ent = hashmap_get_entry(hm, key);
    void* ret = NULL;
    if (ent != NULL) {
        ret = ent->value;
        ent->value = value;
    } else {
        hashmap_add_entry(hm, key, value);
    }
    return ret;
}

void* hashmap_put_all(id self, id m) {
    hashmap hm = cast(hashmap, self);
    map mm = cast(map, m);
    size_t new_keys = mm->size(mm);
    if (new_keys == 0) {
        return;
    } else {
        set entry_set = mm->entry_set(mm);
        iterator itr = entry_set->create_iterator(entry_set);
        while (itr->has_next(itr)) {
            map_entry ent = cast(map_entry, itr->next(itr));
            hm->put(hm, ent->key, ent->value);
        }
        destroy(itr);
        destroy(entry_set);
    }
}

void* hashmap_remove(id self, void* key) {
    hashmap hm = cast(hashmap, self);
    size_t hash = hashmap_hash(hm, key);
    hashmap_entry* ents = hm->_table;
    size_t index = hashmap_index_for(hash, hm->_capacity);
    hashmap_entry curr = ents[index], prev = NULL, next = NULL;
    
    while (curr != NULL) {
        next = curr->next;
        if (hashmap_key_equals(hm->comparator, hash, key, curr->hash, curr->key)) {
            -- hm->_size;
            if (prev == NULL) {
                ents[index] = next;
            } else {
                prev->next = next;
                break;
            }
        }
        prev = curr;
        curr = next;
    }
    void* ret = curr == NULL ? NULL : curr->value;
    destroy(curr);
    return ret;
}

size_t hashmap_size(id self) {
    hashmap hm = cast(hashmap, self);
    return hm->_size;
}

collection hashmap_values(id self) {
    // TODO
}