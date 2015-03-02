#include "opaque_keyword.h"
/**
 * Create a public typedef for a struct, that:
 * 1. contains an unfinished struct type in the header (```struct _foo;```)
 * 2. contains the actual typedef in the header
 * 3. contains the actual body of the struct in the c source file.
 */

struct _Rainbow{
    int length;
    int* colors;
    bool has_gold;
};
