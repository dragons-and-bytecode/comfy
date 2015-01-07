#ifndef __base_h__
#define __base_h__

typedef char* string;
typedef long int timestamp;
typedef int bool;

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

/*
 * String functions
 */

bool string_ends_with(string str, string phrase);
string string_lowercase(string str);

#endif