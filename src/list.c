#include "list.h"
#include "stdlib.h"
#include "assert.h"

List* list_new(){
    List* list = malloc(sizeof(List));
    list->items = NULL;
    list->count = 0;
    return list;
}

void list_add(List* list, Item element){
    int count = list->count + 1;
    list->items = realloc(list->items, count * sizeof(element));
    list->items[list->count] = element;
    list->count = count;
}

void list_addall(List* list, List* other){
    assert(list);
    assert(other);
    if (other->count == 0) return;
    
    int count = list->count + other->count;
    list->items = realloc(list->items, count * sizeof(*(other->items)));
    for(int i = 0; i < other->count; i++){
        list->items[list->count + i] = other->items[i];
    }
    list->count = count;
}

void list_free(List* list){
    if (list){
        if (list->items) free(list->items);
        free(list);
    }
}

void list_foreach(List* list, void (*callback)(List*, Item, int)){
    for (int i = 0; i < list->count; i++){
        callback(list, list->items[i], i);
    }
}

Item list_get(List* list, int i){
    assert(i < list->count);
    return list->items[i];
}

/*
// Sample usage

#include "stdio.h"

void debug_item(List* list, Item item, int index){
    if(index > 0) printf(", ");
    printf("\"%s\"", item);
}

void debug(List* list){
    printf("%i : [", list->count);
    list_foreach(list, debug_item);
    printf("]\n");
}

int main(){
    List* cats = list_new();
    debug(cats);
    list_add(cats, "Baltazar");
    list_add(cats, "Scar");
    list_add(cats, "Garfield");
    debug(cats);
    
    List* dogs = list_new();
    list_add(dogs, "Goofy");
    list_add(dogs, "Pluto");
    debug(dogs);
    
    list_addall(cats, dogs);
    debug(cats);
    
    list_free(dogs);
    list_free(cats);
}
*/
