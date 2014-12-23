#include "comfy.h"
#include "dirent.h"
#include "assert.h"

void print_file(const char* filename){
  printf("%s", filename);
}

void each_file(const char* dir_name, void (*action)(const char* filename)){
  DIR           *d;
  struct dirent *dir;
  d = opendir(dir_name);
  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
      printf("%s\n", dir->d_name);
    }

    closedir(d);
  }
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
