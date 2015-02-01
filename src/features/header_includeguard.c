#include "header_includeguard.h"

#include "asprintf.h"

string header_includeguard(string name, string source){
    string xxx;
    asprintf(&xxx, "Boo!");
    return xxx;
}
