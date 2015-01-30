/**
 *@file comfy the main program
 *
 */
#include "base.h"
#include "args.h"
#include "files.h"

#include "stdio.h"

/**
 * 1. 
 */
int main(int argc, char* argv[])
{
    Options opt = parse_args(argc, argv);
    
    string source = opt.get(&opt, "source", ".");
    string target = opt.get(&opt, "target", ".");

    Files* source_files = files_list_dir(source);
    
    for (int i = 0; i < files_count(source_files); i++){
        if (!files_type_is_regular_file(source_files, i))
            continue;
        
        printf("* %s\n", files_filename(source_files, i));
    }
    
    files_free_files(source_files);

    return 0;
}
