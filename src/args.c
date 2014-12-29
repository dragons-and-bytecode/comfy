#include "args.h"
#include "stdio.h"
#include "string.h"
#include "assert.h"
#include "stdlib.h"

#define bool int

bool __is_argument_name(Options* options, int index)
{
    assert(0 <= index);
    assert(index < options->argc);
    
    return 0 == strncmp("--", options->argv[index], 2);
}

char* Options_get(Options* self, char* name, char* default_value)
{
    for (int i = 0; i < self->argc; i++){
        if (__is_argument_name(self, i)){
            char* arg_name = self->argv[i]+2;
            if (0 == strcmp(name, arg_name)){
                if (i+1 < self->argc && !__is_argument_name(self, i+1)){
                    return self->argv[i+1];
                }
            }
        }
    }
    
    return default_value;
}

Options parse_args(int argc, char* argv[])
{
    Options opt;
    opt.argc = argc;
    opt.argv = argv;
    
    opt.get = &Options_get;
    return opt;
}

