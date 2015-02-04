#ifndef __files_h__
#define __files_h__

#include "base.h"

struct _Files;
typedef struct _Files Files;

Files* files_list_dir(string dirname);

Files* files_list_files(string dirname, char* file_names[], int files_len);

void files_free_files(Files* files);

int files_count(Files* files);

string files_filepath(Files* files, int index);

bool files_type_is_regular_file(Files* files, int index);

string files_read_file(string file_name);

string files_get_filetype(string file_name);

void files_write_file(string file_name, string content);

#endif
