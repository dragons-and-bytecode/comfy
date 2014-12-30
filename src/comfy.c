/**
 *@file comfy the main program
 *
 */
#include "comfy.h"
#include "args.h"
#include "unistd.h"

void watch_dir(string source, string target, bool continuous)
{
    FileListing source_files = files_in(source);
    files_add_filter(&source_files, "*.comfy");
    files_add_filter(&source_files, "*.h");
    
    if (continuous)
        printf("Watching '%s' ... (exit with Ctrl-C)\n\n", source);
    
    timestamp last_update;
    
    while(true) {
        FileMetadata* files;
        int no_files = files_list(&source_files, files);
        
        timestamp new_last_update = last_update;
        for (int i = 0; i < no_files; i++){            
            if (last_update < files[i].last_update){
                printf("File %s changed...\n", files[i].name);
                
                //TODO do magic
                
                if (new_last_update < last_update)
                    new_last_update = files[i].last_update;
            }            
        }
        last_update = new_last_update;
        
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
