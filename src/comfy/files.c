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



FileListing* files_in(const char* directory){
  assert(NULL != directory);
  FileListing* this = malloc(sizeof(FileListing));
  this->directory = malloc(strlen(directory) * sizeof(char));
  strcpy(this->directory, directory);

  return this;
}

void files_destroy(FileListing* this){
  free(this->directory);
  free(this);
}

void files_set_filter (FileListing* this, const char* filter)
{
  this->name_filter = malloc(strlen(filter) * sizeof(char));
  strcpy(this->name_filter, filter);
}
