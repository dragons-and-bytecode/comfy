#include "header_onlypublic.h"

#include "asprintf.h"

string header_onlypublic(string name, string source){
    string xxx;
    asprintf(&xxx, "Baa! - %s", source);
    return xxx;
}
