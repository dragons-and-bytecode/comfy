#ifndef __dependency_tale_h__
#define __dependency_tale_h__

#include "base.h"
#include "files.h"

/**
 * Prints the header files, that needs to be created from .comfy files in the
 * same source directory, in order to successfully compile the given files
 * as C files.
 *
 * More formally, this method querries the given source files for ```#include```
 * directives, which refer to a header name, also availible as a *.comfy file
 * in the given source directory.
 *
 * It then prints a spaces separated list of the found headers. Duplicates
 * will be pronted only once.
 *
 * @param source_dir [description]
 * @param files      [description]
 * @param filecount  [description]
 */
void print_dependency_headers(string source_dir, Files* source_files);

#endif
