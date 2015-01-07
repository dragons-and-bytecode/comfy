#include "processor.h"
#include "files.h"

static FileListing source_files;
static string target_dir;

string _get_intermediate_path(FileMetadata* file){
    int root_len = strlen(source_files.directory);
    int sub_path_length = strlen(file->path) - root_len - strlen(file->name);
    
    string sub_path = malloc(sizeof(char) * (1 + sub_path_length));
    strncpy(sub_path, &(file->path[root_len]), sub_path_length);
    sub_path[sub_path_length] = '\0';
    return sub_path;
}

string _get_bundle_name(string source_file){
    string tail = rindex(source_file, '.') + 1;
    int name_len = strlen(source_file) - strlen(tail) - 1;
    string name = malloc((1 + name_len) * sizeof(char));
    strncpy(name, source_file, name_len);
    name[name_len] = '\0';
    return name;
}

void _bundle_set_target(ComfyFile* target, 
                            FileMetadata* source_file,
                            string filetype){
    string name = _get_bundle_name(source_file->name);
    
    string sub_path = _get_intermediate_path(source_file);        
    asprintf(&(target->name), "%s%s%s.%s", target_dir, sub_path, name, filetype);
    
    FileMetadata* meta = files_file_metadata(target->name);
    target->exists = meta->exists;
    target->last_modified = target->exists ? meta->last_update : 0;
    
    free(sub_path);
    free(name);
}

/**
 * Any bundle needs processing if:
 * * the target_header file does not exists, or is older than the source file.
 * * the source file is a 'comfy' file AND the target 'c' file does not exist
 *   or is older than the source file.
 */
bool _bundle_needs_processing(ComfyFileBundle* bundle){
    if (!bundle->target_header.exists)
        return true;
    if (bundle->target_header.last_modified < bundle->source.last_modified)
        return true;
    
    string lower_name = string_lowercase(bundle->source.name);
    if (string_ends_with(lower_name, ".comfy")){
        free(lower_name);
        
        if (!bundle->target_c.exists)
            return true;
        if (bundle->target_c.last_modified < bundle->source.last_modified)
            return true;
        
        return false;
    } else {
        free(lower_name);
        return false;
    }
}

List* create_bundles(){
    List* files = files_list(&source_files);
    List* bundles = list_new();
    
    //foreach file in files {...}
    for (int i = 0; i < files->count; i++){
        FileMetadata* file = (FileMetadata*) list_get(files, i);
        
        ComfyFileBundle* bundle = malloc(sizeof(ComfyFileBundle));
        
        asprintf(&(bundle->source.name), "%s", file->path);
        bundle->source.last_modified = file->last_update;
        bundle->source.exists = true;

        _bundle_set_target(&(bundle->target_header), file, "h");        
        _bundle_set_target(&(bundle->target_c),      file, "c");
        
        if (_bundle_needs_processing(bundle)){
            list_add(bundles, bundle);
        } else {
            free(bundle);
        }
        
        files_delete_file_metadata(file);
        
    }
    
    list_free(files);
    return bundles;
}

void _delete_bundle(List* bundles, Item item, int index){
    ComfyFileBundle* bundle = (ComfyFileBundle*) item;
    if (bundle){
        
        
        free(bundle);
    }
}

void delete_bundles(List* bundles){
    list_foreach(bundles, _delete_bundle);
    list_free(bundles);
}

bool bundle_needs_processing(ComfyFileBundle* bundle){return false;}

void processor_init(string source_dir, string _target_dir){
    source_files = files_in(source_dir);
    files_add_filter(&source_files, "!.*");
    files_add_filter(&source_files, "*.comfy");
    files_add_filter(&source_files, "*.h");
    
    target_dir = _target_dir;
}
//bool processor_would_modify(ComfyFileBundle bundle){return false;}

void processor_process(ComfyFileBundle* bundle){
    
}