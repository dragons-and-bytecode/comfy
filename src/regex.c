#include "regex.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "slre.h"
#include "assert.h"
#include "asprintf.h"

struct _RegexMatcher {
    bool did_match;
    int group_count;
    struct slre_cap* captures;
    string* loaded_groups;
};

bool regex_match(const string pattern, const string subject){
    int x = slre_match(pattern, subject, strlen(subject), NULL, 0, 0);
    assert(x >= 0 || x == -1);
    return x >= 0 ? true : false;
}

int _count_char(const string pattern, char c){
    int len = strlen(pattern);
    int count = 0;
    for (int i = 0; i < len; i++){
        string ptr = strchr(pattern+(i * sizeof(char)), c);
        if (!ptr) break;
        int open_index = ptr - pattern;

        //if bracket is masked continue
        if (open_index >= 1 && '\\' == *(ptr-1) && 
            (open_index < 2 ||'\\' != *(ptr-2))) continue;

        //printf("## %i: (%i) %s\n", i, open_index, ptr);
        i = open_index;
        count++;
    }
    return count;
}

int min(int x, int y){
    return x < y ? x : y;
}

int max(int x, int y){
    return x > y ? x : y;
}

int _count_groups(const string pattern){
    int count_open = _count_char(pattern, '(');
    int count_close = _count_char(pattern, ')');
    
    int max = max(count_open, count_close);
    int min = min(count_open, count_close);
    
    return max - ( max - min);
}

RegexMatcher regex_matcher(const string pattern, const string subject){
    RegexMatcher matcher = malloc(sizeof(struct _RegexMatcher));
    
    matcher->group_count = _count_groups(pattern);
    matcher->captures = malloc(sizeof(struct slre_cap) * matcher->group_count);
    
    int x = slre_match(pattern, subject, strlen(subject), 
                       matcher->captures, matcher->group_count, 0);
    assert(x >= 0 || x == -1);
    matcher->did_match = x >= 0 ? true : false;
    
    if (matcher->did_match){
        matcher->loaded_groups = malloc(sizeof(string) * matcher->group_count);
        for (int i = 0; i < matcher->group_count; i++){
            matcher->loaded_groups[i] = NULL;
        }
    }
    
    //printf("::: %i|%i: %i\n", matcher->did_match, x, matcher->group_count);
    return matcher;
}

bool regex_did_match(RegexMatcher matcher){
    return matcher->did_match;
}

int regex_group_count(RegexMatcher matcher){
    return matcher->group_count;
}

string regex_group(RegexMatcher matcher, int group){
    assert(matcher && group < matcher->group_count);
    if (NULL == matcher->loaded_groups[group]){
        asprintf(&(matcher->loaded_groups[group]), "%.*s", 
                    matcher->captures[group].len, 
                    matcher->captures[group].ptr);
    }
    return matcher->loaded_groups[group];
}

void regex_free_matcher(RegexMatcher matcher){
    if (NULL != matcher){
        if (NULL != matcher->captures){
            free(matcher->captures);
        }
        if (matcher->did_match && NULL != matcher->loaded_groups){
            for(int i = 0; i < matcher->group_count; i++){
                if (NULL != matcher->loaded_groups[i])
                    free(matcher->loaded_groups[i]);
            }
            free(matcher->loaded_groups);
        }
        free(matcher);
    }
}
