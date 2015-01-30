#include "list.h"
#include "stdlib.h"
#include "assert.h"

List* list_new(){
    List* list = malloc(sizeof(List));
    list->items = NULL;
    list->count = 0;
    list->memsize = 0;
    return list;
}

void list_free(List* list){
    if (list){
        if (list->items) free(list->items);
        free(list);
    }
}

void list_add(List* list, ListItem element){
    int count = list->count + 1;
    if (list->memsize < count){
        if (0 == list->memsize){
            list->memsize = 1;
        } else {
            list->memsize = list->memsize * 2;
        }
        list->items = realloc(list->items, list->memsize * sizeof(ListItem));
    }
    
    
    list->items[list->count] = element;
    list->count = count;
}

ListItem list_get(List* list, int i){
    assert(i < list->count);
    return list->items[i];
}

int list_size(List* list){
    assert(list);
    return list->count;
}
