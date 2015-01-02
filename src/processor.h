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

/**
 * Processes a given source file by following this order:
 * 1. read the source file
 * 2. for each feature
 * 2.1.  process bundle in feature
 * 3. if target_header content has been created:
 * 3.1. delete possibly existing target header
 * 3.2. write new target header
 * 4. if target_c content has been created:
 * 4.1. delete possibly existing target c file
 * 4.2. write new target c file
 */
void processor_process(ComfyFileBundle* bundle);


#endif
