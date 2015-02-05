#include "../base.h"

/**
 * The public keyword does a few things:
 *
 * If a method is declared as 'public', it is noticed by the regex parser
 * as:
 *
 * 1. An (optional) documentation block
 * 2. the 'public' keyword
 * 3. other keywords and the return value in no particular order
 * 4. an identifier/name
 * 5. the parameters section
 * 
 * We don't care about the method body here.
 *
 * The keyword is the extendedn, in that:
 * 
 * 1. the keyword is removed from the method head.
 * 2. the method head is duplicated as an abstract definition (ending with ';')
 *    above the original method head.
 * 3. Every line, starting with the first line of the documentation block and
 *    ending with the last line of the new (abstract) method definition is
 *    prepended with '§', so that it will be printed into the header.
 */
string comfy_keyword_public(string name, string source);

