#include "header_onlypublic.h"
#include "source_onlyprivate.h"
#include "source_unmask_masked_private.h"

#include "asprintf.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"
#include "slre.h"

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

struct _LineString;
typedef struct _LineString LineString;
struct _LineString {
    string text;
    int length;
    bool ignore;
    LineString* before;
};

static LineString process_public_line(LineString line){
     string publine = public_line(line.text);   
     int trimmed_chars = publine - line.text;
     
     if (publine && trimmed_chars < line.length){
         return (LineString) {
             .length = line.length - trimmed_chars,
             .text = publine,
			 .before = NULL,
			 .ignore = false
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

static LineString unmask_private_line(LineString line){
    struct slre_cap caps[1];
    if (0 <= slre_match("^\\s*§(§)",
                line.text, line.length, caps, 1, 0)){
        
        LineString* before = malloc(sizeof(LineString));
        before->text = line.text;
        before->length = caps[0].ptr - line.text;
        before->before = NULL;
        before->ignore = false;
        
        return (LineString) {
            .text = (string) caps[0].ptr + caps[0].len,
            .length = line.length - before->length - caps[0].len,
            .before = before,
			.ignore = false
        };
    }
    return line;
}

static string append_line_to_text(string text, LineString line){
    if (!line.ignore){
        if (line.before){
            text = append_line_to_text(text, *line.before);
            free(line.before);
            line.before = NULL;
        }
        
        string appended;
        if (text){
            asprintf(&appended, "%s%.*s", text, line.length, line.text);
            free(text);
        } else {
            asprintf(&appended, "%.*s", line.length, line.text);
        }
        text = appended;
    }
    
    return text;
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
            .length = length,
			.before = NULL,
			.ignore = false
        });
            
        processed = append_line_to_text(processed, processed_line);
        
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

string source_unmask_masked_private(string name, string source){
    return line_by_line(name, source, unmask_private_line);
}
