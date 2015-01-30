#include "files.h"

#include "dirent.h"
#include "stdio.h"
#include "list.h"
#include "stdlib.h"

struct _Files {
    List* dir_entries;
};

Files* files_list_dir(string dirname){
    Files* files = malloc(sizeof(Files));
    files->dir_entries = list_new();
    
    DIR* d = opendir(dirname);
    if (d){
        struct dirent* dir_entry;
        while ((dir_entry = readdir(d))){
            list_add(files->dir_entries, dir_entry);
        }
        closedir(d);
    }
    
    return files;
}

void files_free_files(Files* files){
    if (files){
        if (files->dir_entries){
            list_free(files->dir_entries);
            files->dir_entries = NULL;
        }
        free(files);
    }
}

int files_count(Files* files){
    return list_size(files->dir_entries);
}

struct dirent* _files_entry(Files* files, int index){
    return list_get(files->dir_entries, index);
}

string files_filename(Files* files, int index){
    return _files_entry(files, index)->d_name;  
}

bool files_type_is_regular_file(Files* files, int index){
    return DT_REG == _files_entry(files, index)->d_type;
}
