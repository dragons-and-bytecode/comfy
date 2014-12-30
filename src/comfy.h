#ifndef __comfy_h__
#define __comfy_h__

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

void create_guard(const char* filename, FILE* input, FILE* output);

/* [files.c] */

typedef char* string;

typedef long int timestamp;

typedef struct {
    string name;
    string path;
    timestamp last_update;
} FileMetadata;



typedef struct {
  string directory;
  string* filters;
  int filters_size;
} FileListing;

FileListing   files_in         (const string directoy);
void          files_destroy    (FileListing* this);
void          files_add_filter (FileListing* this, const string filter);

/**
 * creates a list of all files in the given filelisting.
 * 
 * The created list will be allocated as an array of FileMetadatas and the 
 * given 'list' pointer pointed at the first element of that array.
 *
 * This method will search for files in any folder in the given listing, but
 * wont include folders in the output.
 *
 * !CAUTION! Any FileMetadata created here, will have to be freed by the user. 
 *
 * @returns the number of FileMetadatas created.
 */
int files_list(const FileListing* this, FileMetadata* list);

#endif
