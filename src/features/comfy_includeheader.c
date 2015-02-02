#include "comfy_includeheader.h"

#include "asprintf.h"
#include "string.h"

string comfy_includeheader(string name, string source){
    string type = strrchr(name, '.');
    int namelen = type - name;
    
    string processed;
    asprintf(&processed, "#include \"%.*s.h\"\n%s",
        namelen, name, source);
    return processed;
}
