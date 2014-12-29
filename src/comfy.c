/**
 *@file comfy the main program
 *
 */
#include "comfy.h"
#include "args.h"

int main(int argc, char* argv[])
{
    Options opt = parse_args(argc, argv);
    
    printf("source: %s\n", opt.get(&opt, "source", "."));   
    printf("target: %s\n", opt.get(&opt, "target", "."));
    
    //FILE* input = fopen(argv[1], "r");
    //create_guard(argv[1], input, stdout);
    //fclose(input);
    //FileListing source = files_in(argv[1]);
    //files_add_filter(&source, "*.comfy");
    //files_add_filter(&source, "*.h");

    //argp_parse (0, argc, argv, 0, 0, 0);
}
