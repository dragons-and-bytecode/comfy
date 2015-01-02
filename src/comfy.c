/**
 *@file comfy the main program
 *
 */
#include "processor.h"
#include "args.h"
#include "list.h"
#include "unistd.h"

void foreach_single_bundle(List* list, Item item, int index){
    ComfyFileBundle* bundle = (ComfyFileBundle*) item;
    
    printf("%s changed ...\n", bundle->source.name);
    
}

void watch_dir(string source, string target, bool continuous)
{
    if (continuous)
        printf("Watching '%s' ... (exit with Ctrl-C)\n\n", source);
    else
        printf("Compiling from '%s' into '%s'\n", source, target);
    
    processor_init(source, target);
    
    while(true){
        List* bundles = create_bundles();
        
        list_foreach(bundles, foreach_single_bundle);
        
        delete_bundles(bundles);
        
        if (!continuous)
            break;
        //Opportunity to BREAK via SIGABR (Ctrl-C).
        usleep(1000L);
    }
}

int main(int argc, char* argv[])
{
    Options opt = parse_args(argc, argv);
    
    //FILE* input = fopen(argv[1], "r");
    //create_guard(argv[1], input, stdout);
    //fclose(input);
    
    string source = opt.get(&opt, "source", ".");
    string target = opt.get(&opt, "target", ".");

    watch_dir(source, target, opt.get_flag(&opt, "watch"));  

}
