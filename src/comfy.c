/**
 *@file comfy the main program
 *
 */
#include "processor.h"
#include "args.h"
#include "list.h"
#include "unistd.h"
#include "features.h"
#include "files.h"

List* features;

void foreach_single_bundle(List* list, Item item, int index){
    ComfyFileBundle* bundle = (ComfyFileBundle*) item;
    printf("%s changed ...\n", bundle->source.name);
    
    processor_load_content(&(bundle->source));
    
    List* targets = processor_create_targets(bundle);
    
    for(int i = 0; i < targets->count; i++){
        ComfyFile* target = list_get(targets, i);
        bool modified_at_all = false;
        
        while(processor_process_file(target, features)){
            modified_at_all = true;
        }
        
        if (modified_at_all || !file_exists(target->name)){
            file_write_content(target->name, target->content);
        }
    }
    
    list_free(targets);
    
    //TODO delete target files
    //TODO write target content to file(s)
}

int watch_dir(string source, string target, bool continuous)
{
    if (continuous)
        printf("Watching '%s' ... (exit with Ctrl-C)\n\n", source);
    else
        printf("Compiling from '%s' into '%s'\n", source, target);
    
    processor_init(source, target);
    
    while(true){
        List* bundles = create_bundles();
        if (!bundles) return 1;
        
        list_foreach(bundles, foreach_single_bundle);
        
        delete_bundles(bundles);
        
        if (!continuous)
            break;
        //Opportunity to BREAK via SIGABR (Ctrl-C).
        usleep(1000L);
    }

    return 0;
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

    int retval = watch_dir(source, target, opt.get_flag(&opt, "watch"));
    
    destroy_feature_list(features);

    return retval;
}
