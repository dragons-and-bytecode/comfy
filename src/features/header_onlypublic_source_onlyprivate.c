#include "header_onlypublic.h"
#include "source_onlyprivate.h"

#include "asprintf.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"

static const string MASK_STR = "§";
static const string UNMASK_STR = "§§";


static string public_line(string line){
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

typedef struct{
    string text;
    int length;
    bool ignore;
} LineString;

static LineString process_public_line(LineString line){
     string publine = public_line(line.text);   
     int trimmed_chars = publine - line.text;
     
     if (publine && trimmed_chars < line.length){
         return (LineString) {
             .length = line.length - trimmed_chars,
             .text = publine
         };
     } else {
         return (LineString) {.ignore = true};
     }
}

static LineString process_private_line(LineString line){
    string publine = public_line(line.text);   
    int trimmed_chars = publine - line.text;
    
    if (publine && trimmed_chars < line.length){
        return (LineString) {.ignore = true};
    } else {
        return line;
    }
}

static string line_by_line( string name, string source, 
                            LineString (*process)(LineString)){
    string processed = NULL;
    
    string line = source;
    while (line) {
        string next_line = strstr(line, "\n");
        int length = next_line ? next_line - line + 1 : strlen(line);
        
        LineString processed_line = process((LineString) {
            .text = line,
            .length = length
        });
            
        if (!processed_line.ignore){
            string appended;
            if (processed){
                asprintf(&appended, "%s%.*s", 
                        processed, processed_line.length, processed_line.text);
                free(processed);
            } else {
                asprintf(&appended, "%.*s", 
                        processed_line.length, processed_line.text);
            }
            processed = appended;
        }
        
        line = next_line ? next_line + 1 : NULL;
    }
    
    return processed;
}

string header_onlypublic(string name, string source){
    return line_by_line(name, source, process_public_line);
}

string source_onlyprivate(string name, string source){
    return line_by_line(name, source, process_private_line);
}
