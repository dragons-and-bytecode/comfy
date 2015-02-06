#include "comfy_includeheader.h"

#include "header_onlypublic.h"

#include "asprintf.h"
#include "string.h"

string comfy_includeheader(string name, string source){
    if (!header_onlypublic_should_create_header(source))
        return NULL;

    string type = strrchr(name, '.');
    int namelen = type - name;

    string processed;
    asprintf(&processed, "#include \"%.*s.h\"\n%s",
        namelen, name, source);
    return processed;
}
