#include "header_includeguard.h"

#include "asprintf.h"
#include "slre.h"
#include "string.h"

static const string PATTERN_PRAGMA_ONCE = "^\\s*#pragma\\s+once\\s*\\n";
static const string PATTERN_GUARD_START = "^\\s*#ifndef\\s+([a-zA-Z_]+)\\s*\\n"
                                          "\\s*#define\\s+([a-zA-Z_]+)\\s*\\n";
static const string PATTERN_GUARD_END =   "#endif\\s*$";


bool is_already_guarded(string source){
    int pragma_once = slre_match(PATTERN_PRAGMA_ONCE, 
            source, strlen(source), NULL, 0, 0);
    if (0 <= pragma_once)
        return true;
    
    struct slre_cap groups[2];
    int guard_start = slre_match(PATTERN_GUARD_START, 
            source, strlen(source), groups, 2, 0);
    if(0 <= guard_start && string_equals_over_length(
            (const string) groups[0].ptr,
            (const string) groups[1].ptr,
            groups[0].len)){
        
        int guard_end =  slre_match(PATTERN_GUARD_END, 
            source, strlen(source), NULL, 0, 0);
        
        return 0 <= guard_end;
    }
    
    return false;
}

string header_includeguard(string name, string source){
    if (is_already_guarded(source))
        return NULL;
    
    string header_name = string_copy(name);
    string_replace_chars(header_name, '.', '_');
    string_replace_chars(header_name, '/', '_');
    
    string guarded;
    asprintf(&guarded, "#ifndef __%s__\n#define __%s__\n\n%s\n#endif\n",
                header_name,
                header_name,
                source);
    return guarded;
}
