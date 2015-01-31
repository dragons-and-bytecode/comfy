#include "files.h"

#include "dirent.h"
#include "stdio.h"
#include "list.h"
#include "stdlib.h"
#include "asprintf.h"


struct _Files {
    string basepath;
    List* dir_entries;
};

Files* files_list_dir(string dirname){
    Files* files = malloc(sizeof(Files));
    files->basepath = string_copy(dirname);
    
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
        if (files->basepath){
            free(files->basepath);
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

string files_filepath(Files* files, int index){
    string path;
    asprintf(&path, "%s/%s", files->basepath, _files_entry(files, index)->d_name);  
    return path;
}

bool files_type_is_regular_file(Files* files, int index){
    return DT_REG == _files_entry(files, index)->d_type;
}

string files_read_file(string file_name){
    FILE* in = fopen(file_name, "rb");
    if (!in){
        return NULL;
    }
    
    fseek(in, 0, SEEK_END);
    long fsize = ftell(in);
    fseek(in, 0, SEEK_SET);

    string content = malloc(fsize + 1);
    fread(content, fsize, 1, in);
    fclose(in);

    content[fsize] = '\0';
    
    return content;
}
