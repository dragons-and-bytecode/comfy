/**
 *@file comfy the main program
 * 
 */
#include "comfy.h"

int main(int argc, char* argv[])
{
    FILE* input = fopen(argv[1], "r");
    create_guard(argv[1], input, stdout);
    fclose(input);
}
