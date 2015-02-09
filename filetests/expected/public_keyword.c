#include "public_keyword.h"
/*
 * The public keyword test
 */

#include "simple_comfy.h"
#include "foobar.h"

void stuff(){
    //This has nothing to do with anything
    int x = 1;
}

int** publicifier(void* things[], int x)
{
    int* y = &x;
    return &y;
}
void without_doc(){
    //works without doc string as well.
    int x = 42;
}

int foo(){return 1;}

char** stuffings(int x){
    return NULL;
}
