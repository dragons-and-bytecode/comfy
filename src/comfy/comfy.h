#ifndef __comfy_h__
#define __comfy_h__

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

void create_guard(const char* filename, FILE* input, FILE* output);

/* [files.c] */


typedef struct {
  char* directory;
  char* name_filter;
} FileListing;

FileListing* files_in         (const char* directoy);
void         files_destroy    (FileListing* this);
void         files_set_filter (FileListing* this, const char* filter);

#endif
