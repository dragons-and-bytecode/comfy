#ifndef __list_h__
#define __list_h__

typedef void* ListItem;

typedef struct {
    ListItem* items;
    int count;
    int memsize;
} List;


List* list_new();
void list_free(List* list);

int list_size(List* list);
ListItem list_get(List* list, int i);

void list_add(List* list, ListItem element);

#endif
