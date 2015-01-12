#include "regex.h"

#include "stdio.h"
#include "string.h"
#include "slre.h"
#include "assert.h"

bool regex_match(const string pattern, const string subject){
    int x = slre_match(pattern, subject, strlen(subject), NULL, 0, 0);
    assert(x >= 0 || x == -1);
    return x >= 0 ? true : false;
}
