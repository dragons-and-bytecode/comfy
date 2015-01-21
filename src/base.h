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

#define DEBUG(txt, ...) printf("\x1b[36m" "[DEBUG] " txt "\n" "\x1b[0m", __VA_ARGS__)

/*
 * String functions
 */

bool string_ends_with(string str, string phrase);
string string_lowercase(string str);

#endif