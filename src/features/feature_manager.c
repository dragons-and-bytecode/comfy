#include "feature_manager.h"
#include "../list.h"

#include "string.h"
#include "stdlib.h"

#include "header_includeguard.h"
#include "header_onlypublic.h"
#include "source_onlyprivate.h"
#include "comfy_includeheader.h"

static List* header_features;
static List* source_features;
static List* comfy_features;
    

void feature_manager_init(){
    header_features = list_new();
    source_features = list_new();
    comfy_features = list_new();
    
    list_add(header_features, header_onlypublic);
    list_add(header_features, header_includeguard);
    
    list_add(source_features, source_onlyprivate);
    
    list_add(comfy_features, comfy_includeheader);
}

void feature_manager_teardown(){
    list_free(header_features);
    header_features = NULL;
    list_free(source_features);
    source_features = NULL;
    list_free(comfy_features);
    comfy_features = NULL;
}

static string _process(string file_name, string content, List* features){
    string processed = string_copy(content);
    free(content);
    
    for (int i = 0; i < list_size(features); i++){
        string (*feature)(const string, const string) = list_get(features, i);
        
        string next = feature(file_name, processed);
        if (!next){
            continue;
        }
        
        free(processed);
        processed = next;
    }
    
    return processed;
}

string feature_manager_process(string file_name, string content){
    string type = strrchr(file_name, '.') + 1;
    
    if (string_equals(type, "h")){
        return _process(file_name, content, header_features);
    } else if (string_equals(type, "c")){
        return _process(file_name, content, source_features);
    } else if (string_equals(type, "comfy")){
        return _process(file_name, content, comfy_features);
    }
    
    return NULL;
}
