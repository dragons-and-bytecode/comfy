#include "files.h"

#include "dirent.h"
#include "stdio.h"
#include "list.h"
#include "stdlib.h"
#include "asprintf.h"
#include "string.h"
#include "sys/stat.h"


struct _Files {
    string basepath;
    List* dir_entries;
};

Files* files_list_files(string dirname, char* file_names[], int files_len){
    Files* files = malloc(sizeof(Files));
    files->basepath = string_copy(dirname);

    files->dir_entries = list_new();

    for(int i = 0; i < files_len; i++){
        list_add(files->dir_entries, string_copy(file_names[i]));
    }

    return files;
}

Files* files_list_dir(string dirname){
    Files* files = malloc(sizeof(Files));
    files->basepath = string_copy(dirname);
    
    files->dir_entries = list_new();
    
    DIR* d = opendir(dirname);
    if (d){
        struct dirent* dir_entry;
        while ((dir_entry = readdir(d))){
            list_add(files->dir_entries, string_copy(dir_entry->d_name));
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

string files_filepath(Files* files, int index){
    string path;
    asprintf(&path, "%s/%s", files->basepath, list_get(files->dir_entries, index));  
    return path;
}

bool files_type_is_regular_file(Files* files, int index){
    FILE* f = fopen(files_filepath(files, index), "r+");
    if (!f) return false;
    fclose(f);
    return true;
}

string files_get_filetype(string file_name){
    string type = strrchr(file_name, '.');
    if (type && strlen(type) > 0){
        type+=1;
    }
    return type;
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

bool file_exists(const string filename){
    struct stat stats;
    return 0 == stat(filename, &stats);
}

void files_write_file(string file_name, string content){
    if (file_exists(file_name)){
        remove(file_name);
        if (file_exists(file_name)){
            ERROR("Could not delete target file %s!", file_name);
            return;
        }
    }
    
    FILE* file = fopen(file_name, "w");
    if (file){
        fputs(content, file);
        fclose(file);
    }
}
