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

List* create_bundles(){
    List* files = files_list(&source_files);
    List* bundles = list_new();
    
    for (int i = 0; i < files->count; i++){
        FileMetadata* file = (FileMetadata*) list_get(files, i);
        
        string tail = rindex(file->name, '.') + 1;
        int name_len = strlen(file->name) - strlen(tail) - 1;
        string name = malloc((1 + name_len) * sizeof(char));
        strncpy(name, file->name, name_len);
        name[name_len] = '\0';

        ComfyFileBundle* bundle = malloc(sizeof(ComfyFileBundle));
        
        string sub_path = _get_intermediate_path(file);        
        
        asprintf(&(bundle->source.name), "%s", file->path);
        bundle->source.last_modified = file->last_update;
        bundle->source.exists = true;
        
        asprintf(&(bundle->target_header.name), "%s%s%s.h", target_dir, sub_path, name);
        
        FileMetadata* t_header = files_file_metadata(bundle->target_header.name);
        // TODO create bundle entries for target_header and target_c
        // TODO refactor bundle creation into it's own method
        // TODO implement logic to ignore bundles, that don't need modification.
        
        list_add(bundles, bundle);
        
        free(sub_path);
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