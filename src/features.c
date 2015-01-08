#include "features.h"

List* create_feature_list(){
    List* lst = list_new();
    list_add(lst, create_auto_incudeguard());
    return lst;
}

void _destroy_feature(List* list, Item item, int index){
    free((Feature*)item);
}

void destroy_feature_list(List* feature_list){
    list_foreach(feature_list, _destroy_feature);
}
