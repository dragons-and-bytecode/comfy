#ifndef __comfy_h__
#define __comfy_h__

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

void create_guard(const char* filename, FILE* input, FILE* output);

/* [files.c] */

typedef char* string;

typedef struct {
  string directory;
  string* filters;
  int filters_size;
} FileListing;

FileListing  files_in         (const string directoy);
void         files_destroy    (FileListing this);
void         files_add_filter (FileListing* this, const string filter);

#endif
