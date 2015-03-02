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

string string_trim_front(const string str){
    string trimmed = str;
    while (trimmed && trimmed[0] != '\0' && isspace(trimmed[0]))
        trimmed++;

    return trimmed;
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

int string_trimmed_length(const string str, int length)
{
    int trim;
    for (trim = 0; 0 < length - trim && isspace(str[trim - 1]); trim++);
    return length - trim;
}

string string_replace_all_in(string str, string find, string replace){
    return string_replace_all_in_sized(str, strlen(str), find, replace);
}

string string_replace_all_in_sized(string str, int length, string find, string replace){
    int find_len =  strlen(find);
    int repl_len = strlen(replace);
    int grow_factor = repl_len - find_len;
    int replacements = 0;
    int old_length = length;

    /*
     * count replacements
     */
    for (int i = 0; i < old_length; replacements++)
    {
        string found = strstr(str+i, find);
        if (found && found - str < old_length){
            i = found - str + find_len;
        } else {
            break;
        }
    }
    /*
     * create new string
     */
    int growth = grow_factor * replacements;
    int new_length =(old_length + growth);
    string newstr = malloc((new_length + 1) * sizeof(char));
    newstr[new_length] = '\0';


    int last_i = 0;
    int i_in_new = 0;
    for (int i = 0; i < old_length;)
    {
        string found = strstr(str+i, find);
        if (found - str >= old_length)
            break;

        if (found){
            i = found - str;
            int copy_size = i - last_i;

            strncpy(newstr + i_in_new, str + last_i, copy_size);
            i_in_new += copy_size;
            strcpy(newstr + i_in_new, replace);
            i_in_new += repl_len;

            i += find_len;
            last_i = i;
        } else {
            break;
        }
    }

    int tail_length = length - last_i;
    if (0 < tail_length)
    {
        strncpy(newstr + i_in_new, str + last_i, tail_length);
    }

    return newstr;
}

static int string_count_lines(string str){
    int i = 0;
    string next = str;
    string end_of_str = str + strlen(str);
    for (i = 0; next < end_of_str and (next = strstr(next, "\n")); i++)
        next++;

    return i;
}

TokenList string_as_lines(const string str)
{
    int count = string_count_lines(str);

    TokenList list = {
        .tokens = malloc(count * sizeof(String)),
        .size = count
    };

    string this = str;
    string next = str;
    string end_of_str = str + strlen(str);
    for (int i = 0; next < end_of_str and (next = strstr(next, "\n")); i++)
    {
        int len = next - this;
        //DEBUG("%i :: %3i :: %3i - %.*s", count, i, len, len, this);
        list.tokens[i] = (String){.text=this, .length=len};

        next++;
        this = next;
    }

    return list;
}
