#ifndef __files_h__
#define __files_h__

#include "base.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "list.h"

typedef struct {
    string name;
    string path;
    timestamp last_update;
    bool exists;
} FileMetadata;



typedef struct {
  string directory;
  string* filters;
  int filters_size;
} FileListing;

FileMetadata* files_file_metadata(const string filename);
void files_delete_file_metadata(FileMetadata* file);

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
List* files_list(const FileListing* this);

void file_write_content(const string filename, const string content);

#endif
