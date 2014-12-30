/**
 *@file comfy the main program
 *
 */
#include "comfy.h"
#include "args.h"
#include "unistd.h"

void watch_dir(string source, string target)
{
    FileListing source_files = files_in(source);
    files_add_filter(&source_files, "*.comfy");
    files_add_filter(&source_files, "*.h");
    
    printf("Watching '%s' ... (exit with Ctrl-C)\n\n", source);
    
    while(true) {
        //Opportunity to BREAK.
        usleep(1000L);
        
        
        
        //TODO how to uus advanced terminal strings (color, set cursor)
    }
    
}

int main(int argc, char* argv[])
{
    Options opt = parse_args(argc, argv);
    
    printf("source: %s\n", opt.get(&opt, "source", "."));   
    printf("target: %s\n", opt.get(&opt, "target", "."));
    printf("watch : %i\n", opt.get_flag(&opt, "watch"));
    
    //FILE* input = fopen(argv[1], "r");
    //create_guard(argv[1], input, stdout);
    //fclose(input);
    
    string source = opt.get(&opt, "source", ".");
    string target = opt.get(&opt, "target", ".");

    if (opt.get_flag(&opt, "watch"))
    {
        watch_dir(source, target);  
    }
}
