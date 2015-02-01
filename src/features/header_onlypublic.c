#include "header_onlypublic.h"

#include "asprintf.h"
#include "string.h"
#include "stdlib.h"

static const string MASK_STR = "§";
static const string UNMASK_STR = "§§";


string public_line(string line){
    string trimmed = string_trim_front(line);
    if (0 == strncmp(trimmed, MASK_STR, strlen(MASK_STR))
        && 0 != strncmp(trimmed, UNMASK_STR, strlen(UNMASK_STR))){
        trimmed += strlen(MASK_STR);
        if (isspace(trimmed[0]))
            trimmed++;
        return trimmed;
    } else {
        return NULL;
    }
}

string header_onlypublic(string name, string source){
    string processed = NULL;
    
    string line = source;
    while (line) {
        string next_line = strstr(line, "\n");
        int length = next_line ? next_line - line + 1 : strlen(line);
        
        string publine = public_line(line);
        
        if (publine && publine < next_line){
            int trimmed_chars = publine - line;
            length -= trimmed_chars;
            
            string appended;
            if (processed){
                asprintf(&appended, "%s%.*s", processed, length, publine);
                free(processed);
            } else {
                asprintf(&appended, "%.*s", length, publine);
            }
            processed = appended;
        }
        
        line = next_line ? next_line + 1 : NULL;
    }
    
    return processed;
}
