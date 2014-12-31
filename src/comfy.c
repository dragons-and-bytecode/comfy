/**
 *@file comfy the main program
 *
 */
#include "comfy.h"
#include "args.h"
#include "list.h"
#include "unistd.h"

void watch_dir(string source, string target, bool continuous)
{
    FileListing source_files = files_in(source);
    files_add_filter(&source_files, "!.*");
    files_add_filter(&source_files, "*.comfy");
    files_add_filter(&source_files, "*.h");
    
    if (continuous)
        printf("Watching '%s' ... (exit with Ctrl-C)\n\n", source);
    
    timestamp last_update = 0;
    
    while(true) {
        List* files = files_list(&source_files);
        
        timestamp new_last_update = last_update;
        for (int i = 0; i < files->count; i++){
            FileMetadata* meta = list_get(files, i);  
            if (last_update < meta->last_update){
                
                printf("File %s changed...\n", meta->name);
                
                //TODO do magic
                
                if (new_last_update < meta->last_update)
                    new_last_update = meta->last_update;
            }            
        }
        last_update = new_last_update;
        
        list_free(files);
        
        if (!continuous)
            break;
        //Opportunity to BREAK via SIGABR (Ctrl-C).
        usleep(1000L);
        //TODO how to uus advanced terminal strings (color, set cursor)
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
