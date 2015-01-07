#include "files.h"
#include "dirent.h"
#include "assert.h"
#include "string.h"
#include "sys/stat.h"
#include "list.h"
#include "fnmatch.h"

void print_file(const string filename){
  printf("%s", filename);
}

FileListing files_in(const string directory){
  assert(NULL != directory);
  FileListing this = {
      .directory = directory,
      .filters = malloc(sizeof(string))
  };
  this.filters[0] = NULL;
  this.filters_size = 0;
  return this;
}

void files_add_filter (FileListing* this, const string filter)
{
    int size = this->filters_size + 1;
    
    realloc(this->filters, sizeof(string) * size);
    this->filters[this->filters_size] = filter;
    this->filters_size = size;
    
}

bool files_filter_file(const FileListing* this, const string filename){
    for (int i = 0; i < this->filters_size; i++){
        string filter = this->filters[i];
        bool negate = false;
        if (0 == strncmp("!", filter, 1)){
            filter++;
            negate = true;
        }
        
        if(0 == fnmatch(filter, filename, 0)){
            return negate ? false : true;
        }
    }
    return false;
}

FileMetadata* files_file_metadata(const string filename){
    struct stat stats;
    int statval = stat(filename, &stats);
    
    string path;
    asprintf(&path, "%s", filename);
    
    FileMetadata* f_data = malloc(sizeof(FileMetadata));
    f_data->name = rindex(path, '/')+1;
    f_data->path = path;
    f_data->last_update = stats.st_mtime;
    
    f_data->exists = (0 == statval); 
    
    return f_data;
}

void files_delete_file_metadata(FileMetadata* file){
    if (file){
        if (file->path){
            free(file->path);
        }
        free(file);
    }
}

List* __files_list(const FileListing* this, string path){
    DIR* d;
    d = opendir(path);
    if (!d)
        return NULL;
    
    struct dirent *dir;
    
    List* list = list_new();
    
    while ((dir = readdir(d)) != NULL) {
        if (0 == strcmp(".", dir->d_name) || 0 == strcmp("..", dir->d_name))
            continue;
        
        string inner_path; 
        asprintf(&inner_path, "%s/%s", path, dir->d_name);
        
        List* inner_list = __files_list(this, inner_path);
        
        if (inner_list){
            list_addall(list, inner_list);
            list_free(inner_list);
            
        } else if (files_filter_file(this, dir->d_name)){
            
            
            struct stat stats;
            stat(inner_path, &stats);
            list_add(list, files_file_metadata(inner_path));
        } 
        
        free(inner_path);
        
    }
    
    closedir(d);
    return list;
}

List* files_list(const FileListing* this)
{
    return __files_list(this, this->directory);
}
