#include "comfy.h"
#include "dirent.h"
#include "assert.h"
#include "string.h"

void print_file(const char* filename){
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

int __files_list(const FileListing* this, 
                 FileMetadata* list,
                 string path){

    DIR* d;
    d = opendir(path);
    if (!d)
        return -1;
    
    struct dirent *dir;
    
    int count = 0;
    
    while ((dir = readdir(d)) != NULL) {
        if (0 == strcmp(".", dir->d_name) || 0 == strcmp("..", dir->d_name))
            continue;
        
        string inner_path; 
        asprintf(&inner_path, "%s/%s", path, dir->d_name);
        int inner_count = __files_list(this, list, inner_path);
        if (0 > inner_count){
            printf("%s\n", dir->d_name);
        } else {
            count += inner_count; 
        }
        free(inner_path);
    }
    
    closedir(d);
    return count;
}

int files_list(const FileListing* this, FileMetadata* list)
{    
    return __files_list(this, list, this->directory);
}
