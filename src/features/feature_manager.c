#include "feature_manager.h"
#include "../list.h"

#include "string.h"

static List* header_features;
static List* source_features;
    

void feature_manager_init(){
    header_features = list_new();
    source_features = list_new();
}

void feature_manager_teardown(){
    list_free(header_features);
    header_features = NULL;
    list_free(source_features);
    source_features = NULL;
}

static string _process(string file_name, string content, List* features){
    string processed = content;
    
    for (int i = 0; i < list_size(features); i++){
        string (*feature)(const string source) = list_get(features, i);
        
        processed = feature(processed);
    }
    
    return processed;
}

string feature_manager_process(string file_name, string content){
    string type = strrchr(file_name, '.');
    
    if (string_equals(type, "h")){
        return _process(file_name, content, header_features);
    } else if (string_equals(type, "h")){
        return _process(file_name, content, source_features);
    }
    
    return NULL;
}
