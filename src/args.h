#ifndef __args_h__
#define __args_h__

#define bool int
#define true 1
#define false 0

typedef struct _OPTIONS Options;

struct _OPTIONS {
    int argc;
    char** argv;
    
    char* (*get)(Options*, char*, char*);
    bool (*get_flag)(Options*, char*);
};


Options parse_args(int argc, char* argv[]);

#endif
