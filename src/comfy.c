/**
 *@file comfy the main program
 *
 */
#include "processor.h"
#include "args.h"
#include "list.h"
#include "unistd.h"
#include "features.h"

List* features;

void foreach_single_bundle(List* list, Item item, int index){
    ComfyFileBundle* bundle = (ComfyFileBundle*) item;
    
    printf("%s changed ...\n", bundle->source.name);
    
    //read source file
    //delete target files
    
    while(true){
        bool modified = false;
        
        for (int i = 0; i < features->count; i++){
            Feature* feature = list_get(features, i);
            if (feature->would_modify(bundle)){
                feature->process(bundle);
                modified = true;
            }
        }
        
        if (!modified) break;
    }
    
    //write target content to file(s)
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
    
    features = create_feature_list();

    watch_dir(source, target, opt.get_flag(&opt, "watch"));
    
    destroy_feature_list(features);

}
