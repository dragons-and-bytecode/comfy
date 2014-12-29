#ifndef __args_h__
#define __args_h__

typedef struct _OPTIONS Options;

struct _OPTIONS {
    int argc;
    char** argv;
    
    char* (*get)(Options*, char*, char*);
};


Options parse_args(int argc, char* argv[]);

#endif
