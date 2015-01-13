#ifndef __regex_h__
#define __regex_h__

#include "base.h"

typedef struct _RegexMatcher* RegexMatcher;

bool regex_match(const string pattern, const string source_str);

RegexMatcher regex_matcher(const string pattern, const string source_str);

bool regex_did_match(RegexMatcher matcher);

int regex_group_count(RegexMatcher matcher);

string regex_group(RegexMatcher matcher, int group);

void regex_free_matcher(RegexMatcher matcher);

#endif