#include <bcplib/bcplib.h>

int my_compare(void* data1, void* data2) {
    return ((*((int *) data1)) - (*((int *) data2)));
}

int main(int argc, char** argv) {
    //arraylist l = create2(arraylist, size, 1000, comparator, my_compare);
    //linkedlist l = linkedlist_create_by_comparator(my_compare);
    linkedlist l = create1(linkedlist, comparator, my_compare);
    iterator itr = l->create_iterator(l);
    printf("%s\n", class_type_of(itr)->name);
    printf("%s %s %s\n", CLASS_TYPE(linkedlist)->name,
            class_type_by_name(linkedlist)->name,
            class_type_of(l)->name);
    printf("itr instanceof iterator: %d\n", 
            instanceof(itr, iterator));
    printf("itr instanceof linkedlist_list_iterator: %d\n", 
            instanceof(itr, linkedlist_list_iterator));
    printf("itr kindof iterator: %d\n", 
            kindof(itr, iterator));
    destroy(itr);
    destroy(l);    
    printf("class info:\n%s %u\n%s %u\n%s %u\n%s %u\n%s %u\n%s %u\n%s %u\n%s %u\n",
            class_type_by_name(bitmap)->name,
            class_type_by_name(bitmap)->size,
            class_type_by_name(object)->name,
            class_type_by_name(object)->size,
            class_type_by_name(collection)->name,
            class_type_by_name(collection)->size,
            class_type_by_name(list)->name,
            class_type_by_name(list)->size,
            class_type_by_name(set)->name,
            class_type_by_name(set)->size,
            class_type_by_name(map)->name,
            class_type_by_name(map)->size,
            class_type_by_name(arraylist)->name,
            class_type_by_name(arraylist)->size,
            class_type_by_name(linkedlist)->name,
            class_type_by_name(linkedlist)->size);
    return (EXIT_SUCCESS);
}
