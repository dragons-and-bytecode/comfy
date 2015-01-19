#ifndef __processor_h__
#define __processor_h__

#include "base.h"
#include "stdio.h"
#include "list.h"
#include "files.h"

typedef enum {
    FILETYPE_C_SOURCE,
    FILETYPE_C_HEADER,
    FILETYPE_COMFY
} ComfyFileType;

typedef struct {
    string name;
    ComfyFileType type;
    FILE* stream;
    timestamp last_modified;
    bool exists;
    char* content;
} ComfyFile;

typedef struct {
    ComfyFile source;
    ComfyFile target_header;
    ComfyFile target_c;
} ComfyFileBundle;

List* create_bundles();

void delete_bundles(List* bundles);

/**
 * determines wether a given file bundle needs to be processed.
 * 
 * A file bundle will need processing, if:
 *
 * 1. Any of the three files does not exist.
 * 2. The source file is newer than eigther the target_c file or the 
 *    target_header file
 */
bool bundle_needs_processing(ComfyFileBundle* bundle);

void processor_init();

void processor_copy_content(const ComfyFile* from, ComfyFile* to);

void processor_load_content(ComfyFile* file);

List* processor_create_targets(ComfyFileBundle* bundle);

bool processor_process_file(ComfyFile* target, List* features);

#endif
