#include "args.h"
#include "stdio.h"
#include "string.h"
#include "assert.h"
#include "stdlib.h"



bool __is_argument_name(Options* options, int index)
{
    assert(0 <= index);
    assert(index < options->argc);
    
    return 0 == strncmp("--", options->argv[index], 2);
}

int __argument_index(Options* self, char* name)
{
    for (int i = 0; i < self->argc; i++)
    {
        if (__is_argument_name(self, i))
        {
            char* arg_name = self->argv[i]+2;
            if (0 == strcmp(name, arg_name))
            {
                return i;
            }
        }
    }
    return -1;
}

char* Options_get(Options* self, char* name, char* default_value)
{
    int i = __argument_index(self, name);
    if (i > 0 && i+1 < self->argc && !__is_argument_name(self, i+1))
    {
        return self->argv[i+1];
    }
    return default_value;
}

bool Options_get_flag(Options* self, char* name)
{
    return 0 <= __argument_index(self, name) ? true : false;
}

int Options_get_unnamed_length(Options* self){
    int l = 0;

    bool last_was_name = false;
    for (int i = 1; i < self->argc; i++){
        if (!last_was_name){
            if (__is_argument_name(self, i)){
                last_was_name = true;
                continue;
            } else {
                l++;
                continue;
            }
        } else {
            last_was_name = false;
        }
    }
    return l;
}

char** Options_get_unnamed(Options* self){
    int size =  self->unnamed_length(self);
    
    char** unnamed_opts = malloc(size * sizeof(char*));

    int j = 0;
    bool last_was_name = false;
    for (int i = 1; i < self->argc; i++){
        if (!last_was_name){
            if (__is_argument_name(self, i)){
                last_was_name = true;
                continue;
            } else {
                unnamed_opts[j++] = self->argv[i];
                continue;
            }
        } else {
            last_was_name = false;
        }
    }

    return unnamed_opts;
}

Options parse_args(int argc, char* argv[])
{
    Options opt;
    opt.argc = argc;
    opt.argv = argv;
    
    opt.get = &Options_get;
    opt.get_flag = &Options_get_flag;
    opt.unnamed_length = &Options_get_unnamed_length;
    opt.unnamed = &Options_get_unnamed;
    return opt;
}

