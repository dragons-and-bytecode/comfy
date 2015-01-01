#ifndef __processor_h__
#define __processor_h__

#include "base.h"
#include "stdio.h"
#include "list.h"

typedef struct {
    string name;
    FILE* stream;
    timestamp last_modified;
    bool exists;
} ComfyFile;

typedef struct {
    ComfyFile comfy;
    ComfyFile header;
    ComfyFile source;
} ComfyFileBundle;

List* create_bundles(string source_dir, string target_dir);

/**
 * determines wether a given file bundle needs to be processed.
 * 
 * A file bundle will need processing, if:
 *
 * 1. Any of the three files does not exist.
 * 2. The comfy file is newer than eigther the c file or the header file
 */
bool bundle_needs_processing(ComfyFileBundle bundle);

void processor_init();
void processor_process(ComfyFileBundle bundle);


#endif
