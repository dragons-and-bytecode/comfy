/**
 *@file comfy the main program
 *
 */
#include "base.h"
#include "args.h"
#include "files.h"
#include "features/feature_manager.h"

#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "asprintf.h"
#include "string.h"

string get_pure_name(string base, string name){    
    string pure = name + strlen(base);
    if ('/' == pure[0] || '\\' == pure[0])
        pure++;
    return pure;
}

string new_filename_with_type(string file_name, string type){
    string old_type = strrchr(file_name, '.');
    int base_length = strlen(file_name) - strlen(old_type);
    int length = base_length + strlen(type);
    
    string base_name = malloc((length + 1) * sizeof(char));
    sprintf(base_name, "%.*s.%s", base_length, file_name, type);
    return base_name;
}

string process_through_features(string base_dir, 
                                string file_name, 
                                string source_content){
                                    
    string target_content = string_copy(source_content);
    string simple_name = get_pure_name(base_dir, file_name);

    return feature_manager_process( simple_name, target_content);                       
}

void make_target_file(string base_dir, string file_name, string source_content){
    string processed_content = process_through_features(base_dir, 
                                                        file_name,
                                                        source_content);
    files_write_file(file_name, processed_content);
    
    free(processed_content); 
}

void make_targets(string source_name, string source_base, string target_base){
    string source_content = files_read_file(source_name);
    if (!source_content){
        ERROR("Could not read %s.", source_name);
        return;
    }
    
    string type = files_get_filetype(source_name);
    string pure_name = get_pure_name(source_base, source_name);
    string target_name;
    asprintf(&target_name, "%s/%s", target_base, pure_name);
    
    if (string_equals(type, "h")){
        make_target_file(target_base, target_name, source_content);
    } else if (string_equals(type, "c")){
        make_target_file(target_base, target_name, source_content);
    } else if (string_equals(type, "comfy")){
        string comfy_content = process_through_features(target_base, 
                                                        target_name,
                                                        source_content);
        
        string target_c_name = new_filename_with_type(target_name, "c");
        string target_h_name = new_filename_with_type(target_name, "h");
        
        make_target_file(target_base, target_c_name, comfy_content);
        make_target_file(target_base, target_h_name, comfy_content);
        
        free(target_h_name);
        free(target_c_name);
        free(comfy_content);
    }    
    /*
     * Let any feature simply create an output_content string, from
     * an input string and a file type (header or source)
     */
    
    free(target_name);
    free(source_content);
}

/**
 * 1. 
 */
int main(int argc, char* argv[])
{
    Options opt = parse_args(argc, argv);
    
    string source = opt.get(&opt, "source", ".");
    string target = opt.get(&opt, "target", ".");

    feature_manager_init();

    Files* source_files = files_list_dir(source);
    
    for (int i = 0; i < files_count(source_files); i++){
        if (!files_type_is_regular_file(source_files, i)){
            continue;
        }
        
        printf("* %s\n", files_filepath(source_files, i));
        
        make_targets(files_filepath(source_files, i), source, target);
    }
    
    files_free_files(source_files);
    
    feature_manager_teardown();

    return 0;
}
