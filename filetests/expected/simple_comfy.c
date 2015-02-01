#include "simple_comfy.h"
#include "private.h"

    /*
     * The simple (intermediate) way, this is separated is, to have every
     * future header line preceded by a token charakter '°' for now.
     * 
     * The beginning of a line means, that no Non-whitespace charakter is 
     * allowed on this line before the token
     *
     * 1. Every double-token at the beginning of a line is ignored.
     * 2. Every single token line is deleted from the source
     * 3. Every line without a single token is deleted from the header
     * 4. Every first token in a line and following whitespace is deleted in 
     *    the header
     * 4. Every first token in a line and following whitespace is deleted in 
     *    the source
     */


int some_func(int a, const char* boo){
   if (a) {
        //return a
        return a;
    }
    printf(boo);
    return -10;
}

/**
 * Neigther this method, nor it's content should be in the header.
 */
void some_private_func(){
    printf("This stuff is private!");
    /* To have a double token:
    ° This stays in the source and becomes a single tokened line
    */
}
