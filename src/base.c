#include "base.h"
#include "assert.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"

bool string_ends_with(string str, string phrase){
    assert(str);
    assert(phrase);
    
    int str_length = strlen(str);
    int phrase_length = strlen(phrase);
    
    if (str_length < phrase_length)
        return false;
    
    int start_index = str_length - phrase_length;
    
    return 0 == strcmp(&(str[start_index]), phrase);
}

string string_lowercase(string str){
    assert(str);
    
    int str_length = strlen(str);
    string str_lower = malloc((str_length + 1) * sizeof(char));
    for (int i = 0; i < str_length; i++)
        str_lower[i] = tolower(str[i]);
    
    str_lower[str_length] = '\0';
    
    return str_lower;
}
