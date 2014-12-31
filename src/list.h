#ifndef __list_h__
#define __list_h__

typedef void* Item;

typedef struct {
    Item* items;
    int count;
} List;


List* list_new();
void list_add(List* list, Item element);
void list_addall(List* list, List* other);
void list_free(List* list);
void list_foreach(List* list, void (*callback)(List*, Item, int));

Item list_get(List* list, int i);

#endif
