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

#ifndef NULL
#define NULL 0
#endif

#define DEBUG(txt, ...) printf("\x1b[36m" "[DEBUG] " txt "\n" "\x1b[0m", __VA_ARGS__)
#define INFO(txt, ...) printf("\x1B[32m" txt "\n" "\x1b[0m", __VA_ARGS__)

#define ERROR(txt, ...) printf("\x1b[31m" "[ERROR] " txt "\n" "\x1b[0m", __VA_ARGS__)

/*
 * String functions
 */

bool string_ends_with(const string str, const string phrase);
string string_lowercase(const string str);
string string_copy(const string str);
string string_trim_front(const string str);

bool string_equals(const string a, const string b);
bool string_equals_over_length(const string a, const string b, int length);

void string_replace_chars(string str, char find, char replace);
#endif
