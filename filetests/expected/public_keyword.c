#include "public_keyword.h"
/*
 * The public keyword test
 */

void stuff(){
    //This has nothing to do with anything
    int x = 1;
}

int** publicifier(void* things[], int x)
{
    int* y = &x;
    return &y;
}

public void without_doc(){
    //TODO at the moment the public keyword does only work on methods with
    //     proper documentation
    int x = 42;
}

int foo(){return 1;}

char** stuffings(int x){
    return NULL;
}


