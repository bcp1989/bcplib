#include <bcplib/bcplib.h>
#include "tests.h"
#include <stdarg.h>

static int my_compare(void* data1, void* data2) {
    return ((*((int *) data1)) - (*((int *) data2)));
}

int type_system_test(int argc, char** argv) {
    //arraylist l = create2(arraylist, size, 1000, comparator, my_compare);
    //linkedlist l = linkedlist_create_by_comparator(my_compare);
    //test
    linkedlist l = new(linkedlist, COLLECTION_INIT_COMPARATOR, my_compare);

    iterator itr = l->create_iterator(l);
    printf("%s\n", classof(itr)->name);
    printf("%s %s %s\n", class_by_name(linkedlist)->name,
            class_by_name(linkedlist)->name,
            classof(l)->name);
    printf("itr instanceof iterator: %d\n",
            instanceof(itr, iterator));
    printf("itr instanceof list_iterator: %d\n",
            instanceof(itr, list_iterator));
    printf("itr kindof iterator: %d\n",
            kindof(itr, iterator));
    int a = 4;
    printf("%d %d\n", is_object(NULL), is_object(itr));
    destroy(itr);
    destroy(l);
    printf("class info:\n");
    printf("%s %u\n", class_by_name(bitmap)->name, class_by_name(bitmap)->size);
    printf("%s %u\n", class_by_name(object)->name, class_by_name(object)->size);
    printf("%s %u\n", class_by_name(collection)->name, class_by_name(collection)->size);
    printf("%s %u\n", class_by_name(list)->name, class_by_name(list)->size);
    printf("%s %u\n", class_by_name(set)->name, class_by_name(set)->size);
    printf("%s %u\n", class_by_name(map)->name, class_by_name(map)->size);
    printf("%s %u\n", class_by_name(arraylist)->name, class_by_name(arraylist)->size);
    printf("%s %u\n", class_by_name(linkedlist)->name, class_by_name(linkedlist)->size);
    
    return (EXIT_SUCCESS);
}
