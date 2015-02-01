#include "base.h"
#include "assert.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"

bool string_ends_with(const string str, const string phrase){
    assert(str);
    assert(phrase);
    
    int str_length = strlen(str);
    int phrase_length = strlen(phrase);
    
    if (str_length < phrase_length)
        return false;
    
    int start_index = str_length - phrase_length;
    
    return 0 == strcmp(&(str[start_index]), phrase);
}

string string_lowercase(const string str){
    assert(str);
    
    int str_length = strlen(str);
    string str_lower = malloc((str_length + 1) * sizeof(char));
    for (int i = 0; i < str_length; i++)
        str_lower[i] = tolower(str[i]);
    
    str_lower[str_length] = '\0';
    
    return str_lower;
}

string string_copy(const string str){
    int len = strlen(str);
    string copy = malloc(sizeof(char) * (len + 1));
    strcpy(copy, str);
    copy[len] = '\0';
    return copy;
}

bool string_equals(const string a, const string b){
    if (!a) return NULL == b;
    if (!b) return false;
    return 0 == strcmp(a, b);
}

bool string_equals_over_length(const string a, const string b, int length){
    if (!a) return NULL == b;
    if (!b) return false;
    return 0 == strncmp(a, b, length);
}

void string_replace_chars(string str, char find, char replace){
  char* found = str;

  while (NULL != found){
    found = strchr(found, find);
    if (NULL != found){
      found[0] = replace;
      found++;
    }
  }
}
